// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PongPlayerState.h"

APongPlayerState::APongPlayerState()
{
    SetReplicates(true);
    NetUpdateFrequency = 10.0f;
}

void APongPlayerState::OnRep_Score()
{
    Super::OnRep_Score();

    OnScoreChanged.Broadcast(GetPlayerId(), GetScore());
}
