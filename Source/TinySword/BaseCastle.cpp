// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCastle.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"



// Sets default values
ABaseCastle::ABaseCastle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Component
	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite")); 
	Sprite->SetupAttachment(RootComponent);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(Sprite);

}

float ABaseCastle::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Castle's TakeDmage function called!"));
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ActualDamage = FMath::Min(Durability, ActualDamage);
	if (!IsCollapse())
	{
		Durability -= ActualDamage; 
		if (IsCollapse())
		{
			OnCollapse();
		}
	}
	return ActualDamage;
}

// Called when the game starts or when spawned
void ABaseCastle::BeginPlay()
{
	Super::BeginPlay();
	
	///
	if (Sprite)
	{
		RootComponent = Sprite; 
	}
}


// Called every frame
void ABaseCastle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

bool ABaseCastle::IsCollapse()
{
	return Durability <= 0;
}

void ABaseCastle::OnCollapse()
{
	if(CollapseFlipbook)
		{
			Sprite->SetFlipbook(CollapseFlipbook);
		}

		if (BoxCollider)
		{
			BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
}
