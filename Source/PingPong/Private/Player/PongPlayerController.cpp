// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PongPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/PongHUD.h"

APongPlayerController::APongPlayerController()
{
    bReplicates = true;
}

void APongPlayerController::ClientInitOverlay_Implementation()
{
    APongHUD* ThisHUD = GetHUD<APongHUD>();
    if (!ThisHUD) return;

    ThisHUD->InitOverlay();
}

void APongPlayerController::ClientDelayToStart_Implementation(float Time)
{
    APongHUD* ThisHUD = GetHUD<APongHUD>();
    if (!ThisHUD) return;

    ThisHUD->OnDelayToStart(Time);
}

void APongPlayerController::ClientStartGame_Implementation()
{
    SetShowMouseCursor(false);
    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);
}

void APongPlayerController::ClientReceiveMessageFromPlayer_Implementation(const FString& Msg)
{
    APongHUD* ThisHUD = GetHUD<APongHUD>();
    if (!ThisHUD) return;

    ThisHUD->OnReceiveMessage(Msg);
}

void APongPlayerController::ServerSendMessageToPlayer_Implementation(const FString& Msg)
{
    const APlayerState* PS = GetPlayerState<APlayerState>();
    if (!PS) return;

    const FString ReturnMsg = FString::Printf(TEXT("%s: %s"), *PS->GetPlayerName(), *Msg);

    AGameStateBase* GS = UGameplayStatics::GetGameState(this);
    if (!GS) return;

    for (auto& ThisPS : GS->PlayerArray)
    {
        if (!ThisPS) continue;

        APongPlayerController* ThisPC = Cast<APongPlayerController>(ThisPS->GetPlayerController());
        if (!ThisPC) continue;

        if (ThisPS->GetPlayerId() != PS->GetPlayerId())
        {
            ThisPC->ClientReceiveMessageFromPlayer(ReturnMsg);
        }
        else
        {
            ThisPC->ClientReceiveMessageFromPlayer(FString::Printf(TEXT("%s: %s"), TEXT("You"), *Msg));
        }
    }
}

void APongPlayerController::SetUIMode()
{
    SetShowMouseCursor(true);
    FInputModeUIOnly InputMode;
    SetInputMode(InputMode);
}

void APongPlayerController::ClientGameOver_Implementation(const FString& Winner)
{
    APongHUD* ThisHUD = GetHUD<APongHUD>();
    if (!ThisHUD) return;

    ThisHUD->OnGameOver(Winner);

    SetUIMode();
    DisableInput(this);
}

void APongPlayerController::BeginPlay()
{
    Super::BeginPlay();

    check(MappingContext);

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
        GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(MappingContext, 0);
    }

    SetUIMode();
}

void APongPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

    EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &APongPlayerController::Move);
    EnhancedInputComponent->BindAction(ActionOpenChat, ETriggerEvent::Started, this, &APongPlayerController::OpenChat);
}

void APongPlayerController::Move(const FInputActionValue& InputActionValue)
{
    const float Input = InputActionValue.Get<float>();
    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    if (FMath::IsNearlyZero(Input)) return;

    APawn* ControlledPawn = GetPawn();
    if (!ControlledPawn) return;

    ControlledPawn->AddMovementInput(RightDirection, Input);
}

void APongPlayerController::OpenChat(const FInputActionValue& InputActionValue)
{
    const bool bInput = InputActionValue.Get<bool>();
    if (!bInput) return;

    APongHUD* ThisHUD = GetHUD<APongHUD>();
    if (!ThisHUD) return;

    ThisHUD->OnOpenChat();
}
