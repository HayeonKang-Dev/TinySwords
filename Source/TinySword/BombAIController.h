// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BombAIController.generated.h"

/**
 * 
 */
UCLASS()
class TINYSWORD_API ABombAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior; 

	//FTimerHandle CountdownTimerHandle; 

	float ElapsedTime = 0.f; 

protected:
	virtual void BeginPlay() override;

	

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Destination")
	FVector EnemyCastleLocation;

	virtual void Tick(float DeltaSeconds) override;

	bool IsDead() const; 

	void MoveToCastle(const FVector &CastleLocation);

	//void SetCountdownTimer();

	//UFUNCTION()
	//void OnArrivalDelayComplete();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Explosion")
	bool bIsReadyToExplode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Explosion")
	bool bHasArrived;

	FVector GetRandomCastleLocation();

};