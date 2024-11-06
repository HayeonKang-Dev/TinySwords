// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAISheep.h"
#include "BaseMeat.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookComponent.h"
#include "SheepAIController.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"


void ABaseAISheep::BeginPlay()
{
    Super::BeginPlay(); 
    Health = MaxHealth; 

    // PreviousLocation = GetActorLocation();
}



void ABaseAISheep::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool ABaseAISheep::IsDead() const
{
    return Health <= 0;
}



float ABaseAISheep::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); 
    ActualDamage = FMath::Min(Health, ActualDamage); 
    FVector ActorLocation = GetActorLocation(); 
    TSubclassOf<ABaseMeat> Meat = ABaseMeat::StaticClass(); 
    if (!IsDead())
    {
        Health -= ActualDamage;
        if (IsDead())
        {
            Destroy(); 
            SpawnMeat();
        }
    }
    return ActualDamage;
}

void ABaseAISheep::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent); 
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseAISheep::MoveRight);
}



void ABaseAISheep::SpawnMeat()
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

    // Adjust Spawn Location (Lower Z)
    FVector SpawnLocation = GetActorLocation(); 
    SpawnLocation.Z = 45.f;
	World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, SpawnLocation, GetActorRotation(), SpawnParams);
}

void ABaseAISheep::MoveRight(float AxisValue)
{
    AddMovementInput(GetActorRightVector() * AxisValue); 
}



void ABaseAISheep::TakeDamageFrom(AActor *Attacker)
{
    
    if (Attacker == nullptr) return;
    FVector AttackLocation = Attacker->GetActorLocation(); 
    ASheepAIController* SheepAIController = Cast<ASheepAIController>(GetController()); 
    if (SheepAIController) 
    {
        UE_LOG(LogTemp, Warning, TEXT("TakeDamageFrom function called!"));
        // 속도 증가
        GetCharacterMovement()->MaxWalkSpeed = BoostedSpeed;
        // Set Timer
        GetWorld()->GetTimerManager().SetTimer(SpeedBoostTimerHandle, this, &ABaseAISheep::ResetSpeed, SpeedBoostDuration, false);

        SheepAIController->FleeFrom(AttackLocation);
    }
}

void ABaseAISheep::ResetSpeed()
{
    GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}