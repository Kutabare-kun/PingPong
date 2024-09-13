// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/PongHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/PongScoreWidgetController.h"

UPongScoreWidgetController* APongHUD::GetScoreWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
    if (!ScoreWidgetController)
    {
        ScoreWidgetController = NewObject<UPongScoreWidgetController>(this, ScoreWidgetControllerClass);
        ScoreWidgetController->SetWidgetControllerParams(WidgetControllerParams);
        ScoreWidgetController->BindCallbacksToDependencies();
    }

    return ScoreWidgetController;
}

void APongHUD::InitOverlay()
{
    OverlayWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
    OverlayWidget->AddToViewport();
}