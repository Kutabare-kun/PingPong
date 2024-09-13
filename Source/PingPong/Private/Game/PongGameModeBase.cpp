// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PongGameModeBase.h"

#include "EngineUtils.h"
#include "Actor/PongBall.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Player/PongPlayerController.h"
#include "Character/PongPlayer.h"

void APongGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
    {
        FreePlayerStarts.Add(*It);
    }

    // Shuffle PlayerStarts
    for (int32 Index = 0; Index < FreePlayerStarts.Num(); ++Index)
    {
        FreePlayerStarts.Swap(Index, FMath::RandRange(Index, FreePlayerStarts.Num() - 1));
    }
}

void APongGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
                               FString& ErrorMessage)
{
    if (FreePlayerStarts.IsEmpty())
    {
        ErrorMessage = TEXT("Server Full, Please try again later");
    }

    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

FString APongGameModeBase::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
                                       const FString& Options, const FString& Portal)
{
    if (FreePlayerStarts.IsEmpty())
    {
        return TEXT("No Free Player Starts, InitNewPlayer Failed");
    }

    APlayerStart* StartSpot = FreePlayerStarts.Pop();
    NewPlayerController->StartSpot = StartSpot;
    DefaultPawnClass = StartSpot->PlayerStartTag == TEXT("Red") ? RedPlayerClass : BluePlayerClass;

    return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

void APongGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    Super::HandleStartingNewPlayer_Implementation(NewPlayer);

    APongPlayerController* PC = Cast<APongPlayerController>(NewPlayer);
    PC->ClientInitOverlay();

    if (GetNumPlayers() == PlayersToStart)
    {
        DelayToStart();
    }
}

void APongGameModeBase::PlayerAddScore(const APawn* Player) const
{
    if (bWinCondition) return;

    APlayerState* PS = Player->GetPlayerState();
    if (!PS) return;

    PS->SetScore(PS->GetScore() + 1);
    bWinCondition = PS->GetScore() >= GameWinScore;
    if (bWinCondition)
    {
        AGameStateBase* GS = GetGameState<AGameStateBase>();
        if (!GS) return;

        for (const auto& PlayerState : GS->PlayerArray)
        {
            APongPlayerController* PC = Cast<APongPlayerController>(PlayerState->GetPlayerController());
            if (!PC) continue;

            PC->ClientGameOver(Player->Tags[0].ToString());
        }
    }
    else
    {
        if (Player->Tags.IsEmpty())
        {
            UE_LOG(LogTemp, Error, TEXT("[%s] Player Tags is Empty"), *GetNameSafe(Player));
            return;
        }

        const bool bIsRed = Player->Tags[0] == FName("Red");
        SpawnBall(!bIsRed);
    }
}

void APongGameModeBase::SpawnGate(APawn* Player) const
{
    const FVector InstigatorLocation = Player->GetActorLocation();
    const FVector ForwardVector = Player->GetActorForwardVector();
    const FVector SpawnLocation = InstigatorLocation + ForwardVector * DistanceSpawnGate;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Instigator = Player;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    GetWorld()->SpawnActor<AActor>(GateClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
}

void APongGameModeBase::DelayToStart()
{
    AGameStateBase* GS = GetGameState<AGameStateBase>();
    if (!GS) return;

    GetWorldTimerManager().SetTimer(DelayToStartTimerHandle, this, &APongGameModeBase::StartGame, 5.0f, false);

    for (const auto& PlayerState : GS->PlayerArray)
    {
        APongPlayerController* PC = Cast<APongPlayerController>(PlayerState->GetPlayerController());
        if (!PC) continue;

        PC->ClientDelayToStart(GetWorldTimerManager().GetTimerRemaining(DelayToStartTimerHandle));
    }
}

void APongGameModeBase::StartGame() const
{
    AGameStateBase* GS = GetGameState<AGameStateBase>();
    if (!GS) return;

    for (const auto& PlayerState : GS->PlayerArray)
    {
        APongPlayerController* PC = Cast<APongPlayerController>(PlayerState->GetPlayerController());
        if (!PC) continue;

        PC->ClientStartGame();
    }

    const bool bIsRedTurn = bSpawnBallWithoutRandom ? bRedPlayer : FMath::RandBool();
    SpawnBall(bIsRedTurn);
}

void APongGameModeBase::SpawnBall(const bool ToRedPlayerDirection) const
{
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    FRotator BallSpawnRotation = BallSpawnRotationToPlayer;
    BallSpawnRotation.Yaw += ToRedPlayerDirection ? 180.0f : 0.0f;
    BallSpawnRotation.Yaw += FMath::RandRange(-YawBallSpread, YawBallSpread);

    GetWorld()->SpawnActor<AActor>(BallClass, BallSpawnLocation, BallSpawnRotation, SpawnParams);
}