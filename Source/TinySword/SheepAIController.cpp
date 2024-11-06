// Fill out your copyright notice in the Description page of Project Settings.


#include "SheepAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseAISheep.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem.h"



void ASheepAIController::BeginPlay()
{
    Super::BeginPlay(); 

    // if (AIBehavior != nullptr)
    // {
    //     RunBehaviorTree(AIBehavior); 
    //     // FVector Location = GetCharacter()->GetActorLocation(); 
    //     // float Radius = 500.f; 
    //     // FNavLocation RandomPoint; 

    //     // UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()); 
    //     // if (NavSystem && NavSystem->GetRandomPointInNavigableRadius(GetWorld(), Location, Radius, RandomPoint))
    //     // {
    //     //     UE_LOG(LogTemp, Warning, TEXT("Random Point Found: %s"), *RandomPoint.Location.ToString());
    //     //     UNavigationSystemV1::SimpleMoveToLocation(GetController(), RandomPoint);
    //     // }
    //     // else
    //     // {
    //     //     UE_LOG(LogTemp, Warning, TEXT("No Nav found"));
    //     // }
    //     // GetBlackboardComponent()->SetValueAsVector(TEXT("MoveToLocation"), Location);
    //     // GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetCharacter()->GetActorLocation());
    // }
}



bool ASheepAIController::IsDead() const
{
    ABaseAISheep* ControlledCharacter = Cast<ABaseAISheep>(GetPawn()); 

    if (ControlledCharacter != nullptr)
    {
        return ControlledCharacter->IsDead();
    }
    return true;
}

void ASheepAIController::Tick(float DeltaTime)
{
}

void ASheepAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    GetWorldTimerManager().SetTimer(Timer, this, &ASheepAIController::MoveRandomPos, 3.f, true, 0.f);
}

void ASheepAIController::OnUnPossess()
{
    Super::OnUnPossess();

    GetWorldTimerManager().ClearTimer(Timer);
}

void ASheepAIController::FleeFrom(const FVector &AttackLocation)
{
    
    FVector SheepLocation = GetPawn()->GetActorLocation(); 

    // 공격주체와 반대 방향 벡터 구하기 
    FVector FleeDirection = (SheepLocation - AttackLocation).GetSafeNormal(); 
    float FleeDistance = 1000.f; // 도망갈 거리 
    FVector FleeLocation = SheepLocation + FleeDirection * FleeDistance; 

    // 도망갈 위치(FleeLocatoin)가 이동 가능한 공간인지 확인 후 이동 
    UNavigationSystemV1* NaviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
    if (NaviSystem)
    {
        FNavLocation NavLocation;
        if (NaviSystem->GetRandomPointInNavigableRadius(FleeLocation, 50.f, NavLocation))
        {
            UE_LOG(LogTemp, Warning, TEXT("Flee function called!"));
            UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NavLocation.Location); 
        }
    }
}

void ASheepAIController::MoveRandomPos()
{
    UNavigationSystemV1* NaviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
    if (!IsValid(NaviSystem))
    {
        return;
    }
    FNavLocation RandomPos; 
    if (NaviSystem->GetRandomPointInNavigableRadius(GetPawn()->GetActorLocation(), 200.f, RandomPos))
    {
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomPos);
    }
}