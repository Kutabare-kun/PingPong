// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PongGate.h"

#include "Components/BoxComponent.h"

APongGate::APongGate()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoXCollision"));
    SetRootComponent(BoxComponent);

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComponent->SetupAttachment(BoxComponent);

    bReplicates = true;
}