// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PongPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PINGPONG_API APongPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    APongPlayerController();

    UFUNCTION(Client, Reliable)
    void ClientInitOverlay();

    UFUNCTION(Client, Reliable)
    void ClientDelayToStart(float Time);

    UFUNCTION(Client, Reliable)
    void ClientStartGame();

    UFUNCTION(Client, Reliable)
    void ClientGameOver(const FString& Winner);

    UFUNCTION(Client, Reliable)
    void ClientReceiveMessageFromPlayer(const FString& Msg);

    UFUNCTION(Server, Reliable, BlueprintCallable)
    void ServerSendMessageToPlayer(const FString& Msg);

protected:
    void SetUIMode();

    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputMappingContext> MappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> ActionMove;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> ActionOpenChat;

private:
    void Move(const struct FInputActionValue& InputActionValue);

    void OpenChat(const struct FInputActionValue& InputActionValue);
};
