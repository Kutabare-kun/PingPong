// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PongPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Game/PongGameModeBase.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


APongPlayer::APongPlayer()
{
    PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    BoxComponent->SetCollisionProfileName(TEXT("Pawn"));
    SetRootComponent(BoxComponent);

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComponent->SetupAttachment(GetRootComponent());

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    SpringArmComponent->SetupAttachment(GetRootComponent());

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComponent->SetupAttachment(SpringArmComponent);

    MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComp"));
    MovementComponent->SetUpdatedComponent(GetRootComponent());

    // Networking
    bReplicates = true;
    SetReplicatingMovement(true);

    // Force to Spawn
    SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

void APongPlayer::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        SpawnOwnGate();
    }
}

void APongPlayer::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Client
    if (Controller && Controller->GetLocalRole() == ROLE_AutonomousProxy)
    {
        // Little optimization to avoid sending the same transform multiple times
        const FTransform CurrentTransform = GetActorTransform();
        if (CurrentTransform.Equals(PreviousTransform) == false)
        {
            UpdateServerTransform(CurrentTransform);

            // Cashed the transform
            PreviousTransform = CurrentTransform;
        }
    }
}

void APongPlayer::SpawnOwnGate()
{
    const APongGameModeBase* GM = Cast<APongGameModeBase>(UGameplayStatics::GetGameMode(this));
    check(GM);

    GM->SpawnGate(this);
}

// Little optimization via UPD (Unreliable)
// Trust to player to send the transform
void APongPlayer::UpdateServerTransform_Implementation(const FTransform& Transform)
{
    // Server Replicated to other client via OnRep_ReplicatedMovement
    SetActorTransform(Transform);
}


