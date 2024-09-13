// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PongPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class UFloatingPawnMovement;

UCLASS()
class PINGPONG_API APongPlayer : public APawn
{
    GENERATED_BODY()

public:
    APongPlayer();

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UFloatingPawnMovement> MovementComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UCameraComponent> CameraComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USpringArmComponent> SpringArmComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBoxComponent> BoxComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> MeshComponent;

private:
    UFUNCTION(Server, Unreliable)
    void UpdateServerTransform(const FTransform& Transform);

    UFUNCTION()
    void SpawnOwnGate();

    FTransform PreviousTransform;
};
