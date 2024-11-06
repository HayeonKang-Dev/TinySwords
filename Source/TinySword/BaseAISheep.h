// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DamageEvents.h"
#include "PaperCharacter.h"
#include "GameFramework/Character.h"
#include "BaseAISheep.generated.h"

/**
 * 
 */
UCLASS()
class TINYSWORD_API ABaseAISheep : public APaperCharacter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	bool IsDead() const; 

	void SpawnMeat();

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TakeDamageFrom(AActor* Attacker); // 공격한 주체 알아내기

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed")
	float BoostedSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed")
	float NormalSpeed = 30.f; 
	
	// 속도 증가 시간 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed")
	float SpeedBoostDuration = 3.f; 

protected:
	virtual void BeginPlay() override;

	FTimerHandle SpeedBoostTimerHandle;

	void ResetSpeed();

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100; 

	UPROPERTY(VisibleAnywhere)
	float Health;

	void MoveRight(float AxisValue); 




};
