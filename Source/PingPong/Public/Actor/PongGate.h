// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongGate.generated.h"

class UBoxComponent;

UCLASS()
class PINGPONG_API APongGate : public AActor
{
    GENERATED_BODY()

public:
    APongGate();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBoxComponent> BoxComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> MeshComponent;
};
