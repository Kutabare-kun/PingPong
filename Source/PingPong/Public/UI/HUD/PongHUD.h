// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PongHUD.generated.h"

class UPongScoreWidgetController;
class UPongUserWidget;

struct FWidgetControllerParams;

UCLASS()
class PINGPONG_API APongHUD : public AHUD
{
    GENERATED_BODY()

public:
    UPongScoreWidgetController* GetScoreWidgetController(const FWidgetControllerParams& WidgetControllerParams);

    UFUNCTION(BlueprintCallable)
    void InitOverlay();

    UFUNCTION(BlueprintImplementableEvent, Category = "Timer")
    void OnDelayToStart(float Time);

    UFUNCTION(BlueprintImplementableEvent, Category = "Game Over")
    void OnGameOver(const FString& Winner);

    UFUNCTION(BlueprintImplementableEvent, Category = "Message")
    void OnReceiveMessage(const FString& Msg);

    UFUNCTION(BlueprintImplementableEvent, Category = "Message")
    void OnOpenChat();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> OverlayWidgetClass;

    UPROPERTY(BlueprintReadOnly, Category = "UI")
    TObjectPtr<UUserWidget> OverlayWidget;

    UPROPERTY(EditDefaultsOnly, Category = "WidgetController")
    TSubclassOf<UPongScoreWidgetController> ScoreWidgetControllerClass;

    UPROPERTY()
    TObjectPtr<UPongScoreWidgetController> ScoreWidgetController;
};
