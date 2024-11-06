// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DamageEvents.h"
#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "TopDown_PaperZDCharacter.generated.h"


/**
 * 
 */
UCLASS()
class TINYSWORD_API ATopDown_PaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="SpriteFlip")
	static bool IsMovingRight(float Value);

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION()
	void Attack();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void IncreaseMoney(float Amount);

	void IncreaseHealth(float Amount);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth = 100;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="State")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
	float Money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	bool IsAttack = false; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TagId")
	int TagId = 0; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

private:
	


	
};
