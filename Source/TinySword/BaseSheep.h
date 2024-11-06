// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseMeat.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSheep.generated.h"


UCLASS()
class TINYSWORD_API ABaseSheep : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSheep();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void SpawnMeath();

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100; 

	UPROPERTY(VisibleAnywhere)
	float Health;


};
