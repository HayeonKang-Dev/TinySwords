// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"
#include "BaseCastle.generated.h"

UCLASS()
class TINYSWORD_API ABaseCastle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCastle();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UPaperFlipbookComponent* Sprite; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBoxComponent* BoxCollider; 

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* CollapseFlipbook;

	void OnCollapse();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="State")
	float Durability = 100.f; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TagId")
	int TagId = 0; 

	bool IsCollapse();

};
