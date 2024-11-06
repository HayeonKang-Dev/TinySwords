// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGoldMine.generated.h"

UCLASS()
class TINYSWORD_API ABaseGoldMine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGoldMine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DropGoldBag();

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="GoldMine")
	static bool GoldMineCollapse(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="GoldMine")
	float Durability;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxDurability = 100; 

	

};
