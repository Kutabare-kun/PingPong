// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "PongGameModeBase.generated.h"

class APongBall;
class APongPlayer;

UCLASS()
class PINGPONG_API APongGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

    virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

    virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;

    virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

    void PlayerAddScore(const APawn* Player) const;

    void SpawnGate(APawn* Player) const;

protected:
    UPROPERTY(EditAnywhere, Category = "Players")
    int32 PlayersToStart = 2;

    UPROPERTY(EditAnywhere, Category = "Spawn|Player")
    TSubclassOf<APongPlayer> RedPlayerClass;

    UPROPERTY(EditAnywhere, Category = "Spawn|Player")
    TSubclassOf<APongPlayer> BluePlayerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Spawn|Ball")
    TSubclassOf<APongBall> BallClass;

    UPROPERTY(EditDefaultsOnly, Category = "Spawn|Gate")
    TSubclassOf<AActor> GateClass;

    UPROPERTY(EditDefaultsOnly, Category = "Spawn|Ball")
    FVector BallSpawnLocation;

    UPROPERTY(EditDefaultsOnly, Category = "Spawn|Ball")
    FRotator BallSpawnRotationToPlayer;

    UPROPERTY(EditDefaultsOnly, Category = "Gamerule")
    int GameWinScore = 5;

    UPROPERTY(EditDefaultsOnly, Category = "Gamerule|Ball")
    float YawBallSpread = 45.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Gamerule|Gate")
    float DistanceSpawnGate = 4000.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Gamerule|Spawn")
    bool bSpawnBallWithoutRandom = false;

    UPROPERTY(EditDefaultsOnly, Category = "Gamerule|Spawn", meta = (EditCondition = "bSpawnBallWithoutRandom"))
    bool bRedPlayer;

    mutable bool bWinCondition = false;

private:
    void DelayToStart();

    UFUNCTION()
    void StartGame() const;

    void SpawnBall(const bool ToRedPlayerDirection) const;

    UPROPERTY(VisibleAnywhere, Category = "Spawn|Player")
    TArray<APlayerStart*> FreePlayerStarts;

    FTimerHandle DelayToStartTimerHandle;
};
