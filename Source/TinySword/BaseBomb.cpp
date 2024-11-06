// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBomb.h"
#include "BombAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


void ABaseBomb::BeginPlay()
{
    Super::BeginPlay(); 
    Health = MaxHealth; 
    GetCharacterMovement()->MaxWalkSpeed = Speed;
    Damage = 10.0f;
}


bool ABaseBomb::IsDead() const
{
   return Health <= 0;
}

float ABaseBomb::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    if(!IsDead())
    {
        ActualDamage = FMath::Min(Health, ActualDamage); 
        Health -= ActualDamage;
        if (IsDead())
        {
            Destroy();
        }
    }
    return ActualDamage;
}

void ABaseBomb::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABaseBomb::DealRadialDamage()
{
    //Damage = 10.0f; // 에디터에서 변경 가능하도록 바꿔야 함 
    FVector Origin = GetActorLocation();
    float DamageRadius = 100.0f; //
    TArray<AActor*> IgnoreActors;
    AController* InstigatedByController = nullptr;

    TArray<AActor*> DamagedActors;

    UGameplayStatics::ApplyRadialDamage(
        this, 
        Damage,
        Origin,
        DamageRadius,
        UDamageType::StaticClass(),
        DamagedActors, 
        this, 
        GetInstigatorController(), 
        true
    );

    // DrawDebugSphere(
    //     GetWorld(),
    //     Origin,
    //     DamageRadius,
    //     32,                   // 스피어의 세그먼트 수 (숫자가 클수록 매끄러워짐)
    //     FColor::Red,          // 색상
    //     false,                // 일회성 그리기 (true면 영구 표시)
    //     20.0f                  // 지속 시간 (초 단위)
    // );

    for (AActor* Actor : DamagedActors)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s took damage!"), *Actor->GetName());
    }
}
