// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongBall.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class PINGPONG_API APongBall : public AActor
{
    GENERATED_BODY()

public:
    APongBall();

    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    TObjectPtr<UProjectileMovementComponent> MovementComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    TObjectPtr<USphereComponent> SphereComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Math")
    float IncreaseDistanceBetweenPlayerAndBall = 100.0f;
};
