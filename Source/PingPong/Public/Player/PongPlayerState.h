// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PongPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChanged, int32, PlayerId, float, Score);

UCLASS()
class PINGPONG_API APongPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    APongPlayerState();

    virtual void OnRep_Score() override;

    FOnChanged OnScoreChanged;
};
