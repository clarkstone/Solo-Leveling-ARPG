#include "COMPLETE_INFINITE_TRANSCENDENCE_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    InfiniteTranscendenceLevel = 0;
    MaxInfiniteTranscendenceLevel = 100;
    bIsInfiniteTranscendenceActive = false;
    InfiniteTranscendencePowerCost = 15.0f;
    InfiniteTranscendenceThreshold = 60.0f;
    
    // Initialize infinite-transcendence properties
    InfiniteRealityManipulation = 0.0f;
    EternalExistenceControl = 0.0f;
    OmniversalAwareness = 0.0f;
    InfiniteTimeMastery = 0.0f;
    AbsoluteConceptualAuthority = 0.0f;
}

void UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateInfiniteTranscendenceStats();
}

void UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::ActivateInfiniteTranscendence()
{
    if (!bIsInfiniteTranscendenceActive && CanActivateInfiniteTranscendence())
    {
        bIsInfiniteTranscendenceActive = true;
        OnInfiniteTranscendenceActivated.Broadcast(InfiniteTranscendenceLevel);
        OnInfiniteTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Infinite-Transcendence System Activated at Level: %d"), InfiniteTranscendenceLevel);
    }
}

void UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::DeactivateInfiniteTranscendence()
{
    if (bIsInfiniteTranscendenceActive)
    {
        bIsInfiniteTranscendenceActive = false;
        OnInfiniteTranscendenceDeactivated.Broadcast(InfiniteTranscendenceLevel);
        OnInfiniteTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Infinite-Transcendence System Deactivated."));
    }
}

void UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::SetInfiniteTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxInfiniteTranscendenceLevel)
    {
        int32 OldLevel = InfiniteTranscendenceLevel;
        InfiniteTranscendenceLevel = NewLevel;
        UpdateInfiniteTranscendenceStats();
        OnInfiniteTranscendenceLevelChanged.Broadcast(OldLevel, InfiniteTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Infinite-Transcendence Level set to: %d"), InfiniteTranscendenceLevel);
        
        if (InfiniteTranscendenceLevel >= MaxInfiniteTranscendenceLevel)
        {
            OnInfiniteTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Infinite-Transcendence Max Level Reached!"));
        }
    }
}

void UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::UseInfiniteTranscendencePower()
{
    if (bIsInfiniteTranscendenceActive && InfiniteTranscendenceLevel > 0)
    {
        OnInfiniteTranscendencePowerUsed.Broadcast(InfiniteTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Infinite-Transcendence Power Used: %.2f"), InfiniteTranscendencePowerCost);
    }
    else
    {
        OnInfiniteTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Infinite-Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::PerformInfiniteTranscendenceAbility()
{
    if (bIsInfiniteTranscendenceActive && InfiniteTranscendenceLevel >= InfiniteTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Infinite-Transcendence Ability at Level %d!"), InfiniteTranscendenceLevel);
        OnInfiniteTranscendenceAbilityPerformed.Broadcast(InfiniteTranscendenceLevel);
        UseInfiniteTranscendencePower();
        
        // Perform infinite-transcendence ability based on level
        switch (InfiniteTranscendenceLevel / 20)
        {
            case 0:
                ManipulateInfiniteReality();
                break;
            case 1:
                ControlEternalExistence();
                break;
            case 2:
                AccessOmniversalAwareness();
                break;
            case 3:
                MasterInfiniteTime();
                break;
            case 4:
            case 5:
                ExerciseConceptualAuthority();
                break;
            default:
                ExerciseConceptualAuthority();
                break;
        }
    }
    else if (InfiniteTranscendenceLevel < InfiniteTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Infinite-Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), InfiniteTranscendenceThreshold, InfiniteTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Infinite-Transcendence is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::IsInfiniteTranscendenceActive() const
{
    return bIsInfiniteTranscendenceActive;
}

int32 UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::GetInfiniteTranscendenceLevel() const
{
    return InfiniteTranscendenceLevel;
}

float UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::GetInfiniteTranscendencePowerCost() const
{
    return InfiniteTranscendencePowerCost;
}

void UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::ManipulateInfiniteReality()
{
    if (bIsInfiniteTranscendenceActive)
    {
        float ManipulationPower = InfiniteRealityManipulation * (InfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Manipulating Infinite Reality with power: %.2f"), ManipulationPower);
        // Apply infinite reality manipulation effects
    }
}

void UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::ControlEternalExistence()
{
    if (bIsInfiniteTranscendenceActive)
    {
        float ExistenceControl = EternalExistenceControl * (InfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Eternal Existence with power: %.2f"), ExistenceControl);
        // Apply eternal existence control effects
    }
}

void UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::AccessOmniversalAwareness()
{
    if (bIsInfiniteTranscendenceActive)
    {
        float AwarenessLevel = OmniversalAwareness * (InfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Omniversal Awareness at level: %.2f"), AwarenessLevel);
        // Apply omniversal awareness effects
    }
}

void UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::MasterInfiniteTime()
{
    if (bIsInfiniteTranscendenceActive)
    {
        float TimeMastery = InfiniteTimeMastery * (InfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Infinite Time with power: %.2f"), TimeMastery);
        // Apply infinite time mastery effects
    }
}

void UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::ExerciseConceptualAuthority()
{
    if (bIsInfiniteTranscendenceActive)
    {
        float ConceptualPower = AbsoluteConceptualAuthority * (InfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Conceptual Authority with power: %.2f"), ConceptualPower);
        // Apply conceptual authority effects
    }
}

bool UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::CanActivateInfiniteTranscendence() const
{
    return InfiniteTranscendenceLevel > 0;
}

void UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::UpdateInfiniteTranscendenceStats()
{
    // Update infinite-transcendence properties based on level
    InfiniteRealityManipulation = InfiniteTranscendenceLevel * 2.5f;
    EternalExistenceControl = InfiniteTranscendenceLevel * 2.3f;
    OmniversalAwareness = InfiniteTranscendenceLevel * 2.7f;
    InfiniteTimeMastery = InfiniteTranscendenceLevel * 2.4f;
    AbsoluteConceptualAuthority = InfiniteTranscendenceLevel * 2.6f;
}

void UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM::OnInfiniteTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsInfiniteTranscendenceActive)
    {
        // Apply infinite-transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Infinite-Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove infinite-transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Infinite-Transcendence state changed to INACTIVE"));
    }
}
