// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PongUserWidget.generated.h"

UCLASS(Abstract)
class PINGPONG_API UPongUserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "WidgetController")
    void SetWidgetController(UObject* InWidgetController);

    UFUNCTION(BlueprintImplementableEvent, Category = "WidgetController")
    void WidgetControllerSet();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
    TObjectPtr<UObject> WidgetController;
};
