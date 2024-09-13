// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayFramework/PongBlueprintFunctionLibrary.h"

#include "Player/PongPlayerState.h"
#include "UI/HUD/PongHUD.h"
#include "UI/WidgetController/PongWidgetController.h"

UPongScoreWidgetController* UPongBlueprintFunctionLibrary::GetScoreWidgetController(APlayerController* PlayerController)
{
    if (!PlayerController) return nullptr;

    APongHUD* HUD = Cast<APongHUD>(PlayerController->GetHUD());
    if (!HUD) return nullptr;

    APongPlayerState* PS = Cast<APongPlayerState>(PlayerController->PlayerState);
    if (!PS) return nullptr;

    const FWidgetControllerParams WidgetControllerParams(PlayerController, PS);
    return HUD->GetScoreWidgetController(WidgetControllerParams);
}
