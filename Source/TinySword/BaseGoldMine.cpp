// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGoldMine.h"
#include "PaperSpriteComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABaseGoldMine::ABaseGoldMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGoldMine::BeginPlay()
{
	Super::BeginPlay();
	Durability = MaxDurability;
	
}

// Called every frame
void ABaseGoldMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseGoldMine::GoldMineCollapse(float Value)
{
    if (Value <= 0) return true;
	else return false;
}

float ABaseGoldMine::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	DamageAmount = FMath::Min(Durability, DamageAmount); 
    Durability -= DamageAmount; 

	if (Durability > 0)
	{
		DropGoldBag();
	}
	return DamageAmount;
}

void ABaseGoldMine::DropGoldBag()
{
	UE_LOG(LogTemp, Warning, TEXT("entered in drop gold bag function!"));
	int RandomValue = FMath::RandRange(0, 1); 
	if (RandomValue == 0)
	{
		UObject* SpawnActor = StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Blueprints/BP_GoldBag.BP_GoldBag"));
		UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
		UWorld* World = GetWorld();
		if(!SpawnActor || !GeneratedBP || !GeneratedBP->GeneratedClass || !World)
		{
			UE_LOG(LogTemp, Warning, TEXT("cannot roading"));
			return;
		}

		// Gold Bag Drop 
		FActorSpawnParameters SpawnParams; 
		SpawnParams.Owner = this; 
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// fix z 
		FVector SpawnLocation = GetActorLocation(); 
		SpawnLocation.Y += 60.f;
		float RandomOffsetX = UKismetMathLibrary::RandomFloatInRange(-30.0f, 30.0f);
		float RandomOffsetY = UKismetMathLibrary::RandomFloatInRange(-10.0f, 10.0f);
		SpawnLocation.X += RandomOffsetX;
		SpawnLocation.Y += RandomOffsetY;
		World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, SpawnLocation, GetActorRotation(), SpawnParams);
		
	}
}
