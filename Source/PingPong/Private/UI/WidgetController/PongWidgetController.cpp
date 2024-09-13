// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/PongWidgetController.h"

void UPongWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
    PlayerController = WidgetControllerParams.PlayerController;
    PlayerState = WidgetControllerParams.PlayerState;
}