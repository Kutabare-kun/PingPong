// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PongBlueprintFunctionLibrary.generated.h"

class UPongScoreWidgetController;

UCLASS()
class PINGPONG_API UPongBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "WidgetController")
    static UPongScoreWidgetController* GetScoreWidgetController(APlayerController* PlayerController);
};
