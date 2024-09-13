// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PongWidgetController.generated.h"

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
    GENERATED_BODY()

    FWidgetControllerParams()
    {
    }

    FWidgetControllerParams(APlayerController* PC, APlayerState* PS)
        : PlayerController(PC), PlayerState(PS)
    {
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<APlayerController> PlayerController = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<APlayerState> PlayerState = nullptr;
};

UCLASS(Abstract)
class PINGPONG_API UPongWidgetController : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams);

    UFUNCTION(BlueprintCallable)
    virtual void BroadcastInitialValues() PURE_VIRTUAL(UWidgetController::BroadcastInitialValues, ;);

    UFUNCTION()
    virtual void BindCallbacksToDependencies() PURE_VIRTUAL(UWidgetController::BindCallbacksToDependencies, ;);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
    TObjectPtr<APlayerController> PlayerController;

    UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
    TObjectPtr<APlayerState> PlayerState;
};
