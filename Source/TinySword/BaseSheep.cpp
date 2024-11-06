// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSheep.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h" 
#include "BaseMeat.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseSheep::ABaseSheep()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseSheep::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth; 
	
}

// Called every frame
void ABaseSheep::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABaseSheep::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); 
    FVector ActorLocation = GetActorLocation();
	TSubclassOf<ABaseMeat> Meat = ABaseMeat::StaticClass();
	if (Health > 0)
	{
		Health -= ActualDamage; 
		if (Health <= 0)
		{
			Destroy();
			SpawnMeath();
		}
	}
	return ActualDamage;
}

void ABaseSheep::SpawnMeath()
{
	// BP_Meat 블루프린트 로드 
	UObject* SpawnActor = StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Blueprints/BP_Meat.BP_Meat"));

	// 블루프린트에서 생성된 클래스 가져오기
	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
	
	// 현재 월드 가져오기 
	UWorld* World = GetWorld();

	// 하나라도 충족 안되면 return 
	if (!SpawnActor || !GeneratedBP || !GeneratedBP->GeneratedClass || !World)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot Road"));
		return;
	}

	FActorSpawnParameters SpawnParams; 
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
}
