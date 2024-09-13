// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PongWidgetController.h"
#include "PongScoreWidgetController.generated.h"

UCLASS(BlueprintType, Blueprintable)
class PINGPONG_API UPongScoreWidgetController : public UPongWidgetController
{
    GENERATED_BODY()

public:
    virtual void BroadcastInitialValues() override;
    virtual void BindCallbacksToDependencies() override;

protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "WidgetController")
    void OnScoreChangedCallback(int32 PlayerId, float Score);
};
