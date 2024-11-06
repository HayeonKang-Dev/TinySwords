// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SheepAIController.generated.h"

/**
 * 
 */
UCLASS()
class TINYSWORD_API ASheepAIController : public AAIController
{
	GENERATED_BODY()

public: 
	bool IsDead() const; 

	virtual void Tick(float DeltaTime) override;

	void FleeFrom(const FVector& AttackLocation);

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;
	
private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior; 

	void MoveRandomPos();

	FTimerHandle Timer;
};
