// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h" // PaperZDCharacter
#include "BaseBomb.generated.h"

/**
 * 
 */
UCLASS()
class TINYSWORD_API ABaseBomb : public APaperCharacter // APaperZDCharacter
{
	GENERATED_BODY()
	
public:
	bool IsDead() const; 

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Damage")
	void DealRadialDamage();

	UPROPERTY(VisibleAnywhere)
	float Health; 

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TagId")
	int TagId = 0; 

protected:
	virtual void BeginPlay() override;

	FTimerHandle BombExplosionTimerHandle; 

	

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 70.f; 

	UPROPERTY(EditAnywhere)
	float Speed = 50.f; 
};
