// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/PongUserWidget.h"

void UPongUserWidget::SetWidgetController(UObject* InWidgetController)
{
    if (!InWidgetController) return;

    WidgetController = InWidgetController;
    WidgetControllerSet();
}
