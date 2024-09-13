// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PongBall.h"

#include "Actor/PongGate.h"
#include "Character/PongPlayer.h"
#include "Components/SphereComponent.h"
#include "Game/PongGameModeBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APongBall::APongBall()
{
    PrimaryActorTick.bCanEverTick = true;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APongBall::OnOverlap);
    SetRootComponent(SphereComponent);

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComponent->SetupAttachment(GetRootComponent());
    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
    MovementComponent->bRotationFollowsVelocity = true;
    MovementComponent->bInitialVelocityInLocalSpace = true;
    MovementComponent->ProjectileGravityScale = 0.0f;
    MovementComponent->InitialSpeed = 400.0f;

    bReplicates = true;
    SetReplicatingMovement(true);
}

void APongBall::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    const APongGate* Gate = Cast<APongGate>(OtherActor);
    if (HasAuthority() && Gate)
    {
        const APongGameModeBase* GM = Cast<APongGameModeBase>(UGameplayStatics::GetGameMode(this));

        GM->PlayerAddScore(Gate->GetInstigator());
        Destroy();
    }

    if (!Gate)
    {
        APongPlayer* ThisPlayer = Cast<APongPlayer>(OtherActor);
        if (!ThisPlayer)
        {
            const FVector ForwardVector = GetActorForwardVector();
            const FVector ProjectionNormalize = UKismetMathLibrary::ProjectVectorOnToVector(ForwardVector, SweepResult.ImpactNormal);
            FVector DesiredForwardVec = ForwardVector - 2 * ProjectionNormalize;
            DesiredForwardVec.Z = 0.0f;

            MovementComponent->Velocity = DesiredForwardVec * MovementComponent->InitialSpeed;
        }
        else
        {
            // Back vector is increase the distance between the ball and the player
            // That give to decrease angle
            const FVector PlayerCenterLocation = ThisPlayer->GetActorLocation() + ThisPlayer->GetActorForwardVector() * IncreaseDistanceBetweenPlayerAndBall * -1.0f;
            FVector Direction = SweepResult.ImpactPoint - PlayerCenterLocation;
            Direction.Z = 0;

            MovementComponent->Velocity = Direction.GetSafeNormal() * MovementComponent->InitialSpeed;
        }
    }
}
