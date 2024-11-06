// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDown_PaperZDCharacter.h"
#include "Components/CapsuleComponent.h"
#include "BaseSheep.h"
#include "Engine/EngineTypes.h" 
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "SheepAIController.h"
#include "BaseAISheep.h" 


void ATopDown_PaperZDCharacter::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;
    Money = 0;

}

void ATopDown_PaperZDCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool ATopDown_PaperZDCharacter::IsDead() const
{
	return Health <= 0;
}



void ATopDown_PaperZDCharacter::Attack()
{
    UE_LOG(LogTemp, Warning, TEXT("Attack Function Called!"));
    IsAttack = true; 
    FVector Start, ForwardVector, End;
    // Dynamite에 부착된 Collision 얻기 
    USphereComponent* SphereCollision = FindComponentByClass<USphereComponent>();
    if (SphereCollision)
    {
        // 공격 판정 범위 산정 By Radius from Sphere Collision
        float Radius = SphereCollision->GetUnscaledSphereRadius();
        Start = SphereCollision->GetComponentLocation();
        Start.X -= Radius;
        End = Start;
        End.X += Radius;
    }

    FHitResult HitResult; 
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    // Line Trace 
    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, CollisionParams))
    {
        UE_LOG(LogTemp, Warning, TEXT("LineTrace Hit!"));
        AActor* HitActor = Cast<AActor>(HitResult.GetActor()); /// ABaseSheep->AActor
        if (HitActor) 
        {
            UE_LOG(LogTemp, Warning, TEXT("Visibility Hit!"));
            FDamageEvent DamageEvent;
            HitActor->TakeDamage(Damage, DamageEvent, nullptr, this);
            
            // 공격대상이 양인지 확인 (반대방향으로 도망가게 하기 위해)
            if (HitActor->IsA<ABaseAISheep>())
            {
                ABaseAISheep* TargetIsSheep = Cast<ABaseAISheep>(HitActor);
                TargetIsSheep->TakeDamageFrom(this);
            }
        }
    }
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 10.0f, 0, 5.0f);
    // IsAttack = false; 
}


void ATopDown_PaperZDCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ATopDown_PaperZDCharacter::Attack);
}



float ATopDown_PaperZDCharacter::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    UE_LOG(LogTemp, Warning, TEXT("Attack function called!"));
    float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); 
	// 남아있는 체력 
	DamageToApply = FMath::Min(Health, DamageToApply); 
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

    if (IsDead())
    {
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
        // APlayerController* PlayerController = Cast<APlayerController>(GetController()); // blueprint의 tick에서 구현 
        // if (PlayerController)
        // {
        //     PlayerController->DisableInput(PlayerController);
        // }
    }
    return DamageToApply;
}

void ATopDown_PaperZDCharacter::IncreaseMoney(float Amount)
{
    Money += Amount; 
}

void ATopDown_PaperZDCharacter::IncreaseHealth(float Amount)
{
    Health += Amount; 
}

bool ATopDown_PaperZDCharacter::IsMovingRight(float Value)
{
    if (Value == 1) return true;
    else if (Value == -1) return false;
    else return true;
}

