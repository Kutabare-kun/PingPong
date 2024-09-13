// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/PongScoreWidgetController.h"

#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PongPlayerState.h"

void UPongScoreWidgetController::BroadcastInitialValues()
{
    AGameStateBase* GS = UGameplayStatics::GetGameState(PlayerController);
    check(GS);

    if (!GS) return;
    for (APlayerState* PS : GS->PlayerArray)
    {
        if (const APongPlayerState* PongPlayerState = Cast<APongPlayerState>(PS))
        {
            PongPlayerState->OnScoreChanged.Broadcast(PongPlayerState->GetPlayerId(), PongPlayerState->GetScore());
        }
    }
}

void UPongScoreWidgetController::BindCallbacksToDependencies()
{
    AGameStateBase* GS = UGameplayStatics::GetGameState(PlayerController);
    check(GS);

    if (!GS) return;
    for (APlayerState* PS : GS->PlayerArray)
    {
        if (APongPlayerState* PongPlayerState = Cast<APongPlayerState>(PS))
        {
            PongPlayerState->OnScoreChanged.AddDynamic(this, &UPongScoreWidgetController::OnScoreChangedCallback);
        }
    }
}
