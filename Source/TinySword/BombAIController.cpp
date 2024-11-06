// Fill out your copyright notice in the Description page of Project Settings.


#include "BombAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BaseCastle.h"
#include "BaseBomb.h"
#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"



void ABombAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!IsDead())
    {
        MoveToCastle(EnemyCastleLocation);
        if (APawn* ControlledPawn = GetPawn())
        {
            if (ABaseBomb* Bomb = Cast<ABaseBomb>(GetPawn()))
            {
                if(IsValid(Bomb))
                {
                    const float DistanceSquared = FVector::DistSquared(Bomb->GetActorLocation(), EnemyCastleLocation);
                    if (DistanceSquared <= FMath::Square(10.0f))
                    {
                        if (!bHasArrived)
                        {
                            bHasArrived = true; 
                        }
                        else if (bHasArrived && !bIsReadyToExplode)
                        {
                            ElapsedTime += DeltaSeconds;
                            if (ElapsedTime >= 1.5f)
                            {
                                bIsReadyToExplode = true;
                                UE_LOG(LogTemp, Warning, TEXT("bIsReadyToExplode: %b"), bIsReadyToExplode);
                            }
                        }
                    }
                    
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Bomb is not valid..."));
            }
        }
    }

    if (bIsReadyToExplode)
    {
        // DealRadialDamage();
        ABaseBomb* ControlledBomb = Cast<ABaseBomb>(GetPawn());
        
        if(ControlledBomb)
        {
            ControlledBomb->DealRadialDamage();
            ControlledBomb->Health=0.0f;
            ControlledBomb->Destroy();
        }
    }
}


void ABombAIController::BeginPlay()
{
    Super::BeginPlay(); 
    bIsReadyToExplode = false;
    bHasArrived = false;
    UE_LOG(LogTemp, Warning, TEXT("Enter in BombAIController's BeginPlay function"));
    FVector CurrentLocation;
    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior); 
        APawn* BombPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        if (ABaseBomb* Bomb = Cast<ABaseBomb>(GetPawn()))
        {
            CurrentLocation = Bomb->GetActorLocation();
            EnemyCastleLocation = GetRandomCastleLocation();
            FVector NewLocation(EnemyCastleLocation.X, EnemyCastleLocation.Y, CurrentLocation.Z);
            EnemyCastleLocation = NewLocation; 
            GetBlackboardComponent()->SetValueAsVector(TEXT("EnemyCastleLocation"), NewLocation);

            UE_LOG(LogTemp, Warning, TEXT("EnemyCastleLocation: %s"), *EnemyCastleLocation.ToString());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Controlled Pawn is not a valid ABaseBomb!"));
        }
        
    }


}




FVector ABombAIController::GetRandomCastleLocation()
{
    TArray<AActor*> FoundCastles;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCastle::StaticClass(), FoundCastles);

    if (FoundCastles.Num() > 0)
    {
        int32 RandomIdx = FMath::RandRange(0, FoundCastles.Num()-1); // -1
        AActor* RandomCastle = FoundCastles[RandomIdx];

        if (RandomCastle)
        {
            FVector CastleLocation = RandomCastle->GetActorLocation();
            //CastleLocation.Z = 60.f;
            CastleLocation.Y += 100.f; // Nav Mesh로 이동 불가해, 그 앞까지 이동하게 
            return CastleLocation;
            
        }
    }   
    UE_LOG(LogTemp, Warning, TEXT("No Actor Found"));
    return FVector::ZeroVector;
    //return RandomCastleLocation;



}

void ABombAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
}

void ABombAIController::OnUnPossess()
{
    Super::OnUnPossess();
}

bool ABombAIController::IsDead() const
{
    ABaseBomb* ControlledCharacter = Cast<ABaseBomb>(GetPawn());

    if (ControlledCharacter != nullptr)
    {
        return ControlledCharacter->IsDead();
    }
    return true; // Pawn 컨트롤하고 있지 않다면 컨트롤러 사망과 마찬가지 
}

void ABombAIController::MoveToCastle(const FVector &CastleLocation)
{
    FNavLocation ClosetPoint;
    if (CastleLocation != FVector::ZeroVector)
    {    
        UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
        if (NavSystem && NavSystem->ProjectPointToNavigation(CastleLocation, ClosetPoint, FVector(0.0f, 0.0f, 0.0f))) // 100 100 100
        {
            // ClosestPoint로 폭탄을 이동
            UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, ClosetPoint.Location);
        }

    }
}

    ///
    

