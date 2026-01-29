#include "P09_TRNS_ABSOLUTE.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP09_TRNS_ABSOLUTE::UP09_TRNS_ABSOLUTE()
{
    PrimaryComponentTick.bCanEverTick = false;
    AbsoluteTranscendenceLevel = 0;
    MaxAbsoluteTranscendenceLevel = 100;
    bIsAbsoluteTranscendenceActive = false;
    AbsoluteTranscendencePowerCost = 50.0f;
    AbsoluteTranscendenceThreshold = 50.0f;
    
    // Initialize absolute transcendence properties
    AbsoluteRealityDominion = 0.0f;
    AbsoluteTranscendenceRecursion = 0.0f;
    AbsoluteInfiniteConsciousness = 0.0f;
    AbsoluteConceptualEvolution = 0.0f;
    AbsoluteTranscendenceAuthority = 0.0f;
}

void UP09_TRNS_ABSOLUTE::BeginPlay()
{
    Super::BeginPlay();
    UpdateAbsoluteTranscendenceStats();
}

void UP09_TRNS_ABSOLUTE::ActivateAbsoluteTranscendence()
{
    if (!bIsAbsoluteTranscendenceActive && CanActivateAbsoluteTranscendence())
    {
        bIsAbsoluteTranscendenceActive = true;
        OnAbsoluteTranscendenceActivated.Broadcast(AbsoluteTranscendenceLevel);
        OnAbsoluteTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Absolute Transcendence System Activated at Level: %d"), AbsoluteTranscendenceLevel);
    }
}

void UP09_TRNS_ABSOLUTE::DeactivateAbsoluteTranscendence()
{
    if (bIsAbsoluteTranscendenceActive)
    {
        bIsAbsoluteTranscendenceActive = false;
        OnAbsoluteTranscendenceDeactivated.Broadcast(AbsoluteTranscendenceLevel);
        OnAbsoluteTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Absolute Transcendence System Deactivated."));
    }
}

void UP09_TRNS_ABSOLUTE::SetAbsoluteTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxAbsoluteTranscendenceLevel)
    {
        int32 OldLevel = AbsoluteTranscendenceLevel;
        AbsoluteTranscendenceLevel = NewLevel;
        UpdateAbsoluteTranscendenceStats();
        OnAbsoluteTranscendenceLevelChanged.Broadcast(OldLevel, AbsoluteTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Absolute Transcendence Level set to: %d"), AbsoluteTranscendenceLevel);
        
        if (AbsoluteTranscendenceLevel >= MaxAbsoluteTranscendenceLevel)
        {
            OnAbsoluteTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Absolute Transcendence Max Level Reached!"));
        }
    }
}

void UP09_TRNS_ABSOLUTE::UseAbsoluteTranscendencePower()
{
    if (bIsAbsoluteTranscendenceActive && AbsoluteTranscendenceLevel > 0)
    {
        OnAbsoluteTranscendencePowerUsed.Broadcast(AbsoluteTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Absolute Transcendence Power Used: %.2f"), AbsoluteTranscendencePowerCost);
    }
    else
    {
        OnAbsoluteTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Absolute Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UP09_TRNS_ABSOLUTE::PerformAbsoluteTranscendenceAbility()
{
    if (bIsAbsoluteTranscendenceActive && AbsoluteTranscendenceLevel >= AbsoluteTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Absolute Transcendence Ability at Level %d!"), AbsoluteTranscendenceLevel);
        OnAbsoluteTranscendenceAbilityPerformed.Broadcast(AbsoluteTranscendenceLevel);
        UseAbsoluteTranscendencePower();
        
        // Perform absolute transcendence ability based on level
        switch (AbsoluteTranscendenceLevel / 20)
        {
            case 0:
                ExerciseAbsoluteRealityDominion();
                break;
            case 1:
                TranscendAbsoluteRecursion();
                break;
            case 2:
                AccessAbsoluteInfiniteConsciousness();
                break;
            case 3:
                EvolveConceptually();
                break;
            case 4:
            case 5:
                WieldAbsoluteTranscendenceAuthority();
                break;
            default:
                WieldAbsoluteTranscendenceAuthority();
                break;
        }
    }
    }
    else if (AbsoluteTranscendenceLevel < AbsoluteTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Absolute Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), AbsoluteTranscendenceThreshold, AbsoluteTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Absolute Transcendence is not active, cannot perform ability."));
    }
}

bool UP09_TRNS_ABSOLUTE::IsAbsoluteTranscendenceActive() const
{
    return bIsAbsoluteTranscendenceActive;
}

int32 UP09_TRNS_ABSOLUTE::GetAbsoluteTranscendenceLevel() const
{
    return AbsoluteTranscendenceLevel;
}

float UP09_TRNS_ABSOLUTE::GetAbsoluteTranscendencePowerCost() const
{
    return AbsoluteTranscendencePowerCost;
}

void UP09_TRNS_ABSOLUTE::ExerciseAbsoluteRealityDominion()
{
    if (bIsAbsoluteTranscendenceActive)
    {
        float DominionPower = AbsoluteRealityDominion * (AbsoluteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Absolute Reality Dominion with power: %.2f"), DominionPower);
        // Apply absolute reality dominion effects
    }
}

void UP09_TRNS_ABSOLUTE::TranscendAbsoluteRecursion()
{
    if (bIsAbsoluteTranscendenceActive)
    {
        float RecursionPower = AbsoluteTranscendenceRecursion * (AbsoluteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Absolute Recursion with power: %.2f"), RecursionPower);
        // Apply absolute transcendence recursion effects
    }
}

void UP09_TRNS_ABSOLUTE::AccessAbsoluteInfiniteConsciousness()
{
    if (bIsAbsoluteTranscendenceActive)
    {
        float ConsciousnessPower = AbsoluteInfiniteConsciousness * (AbsoluteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Absolute Infinite Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply absolute infinite consciousness effects
    }
}

void UP09_TRNS_ABSOLUTE::EvolveConceptually()
{
    if (bIsAbsoluteTranscendenceActive)
    {
        float EvolutionPower = AbsoluteConceptualEvolution * (AbsoluteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually with power: %.2f"), EvolutionPower);
        // Apply absolute conceptual evolution effects
    }
}

void UP09_TRNS_ABSOLUTE::WieldAbsoluteTranscendenceAuthority()
{
    if (bIsAbsoluteTranscendenceActive)
    {
        float AuthorityPower = AbsoluteTranscendenceAuthority * (AbsoluteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Absolute Transcendence Authority with power: %.2f"), AuthorityPower);
        // Apply absolute transcendence authority effects
    }
}

bool UP09_TRNS_ABSOLUTE::CanActivateAbsoluteTranscendence() const
{
    return AbsoluteTranscendenceLevel > 0;
}

void UP09_TRNS_ABSOLUTE::UpdateAbsoluteTranscendenceStats()
{
    // Update absolute transcendence properties based on level
    AbsoluteRealityDominion = AbsoluteTranscendenceLevel * 6.0f;
    AbsoluteTranscendenceRecursion = AbsoluteTranscendenceLevel * 5.8f;
    AbsoluteInfiniteConsciousness = AbsoluteTranscendenceLevel * 5.6f;
    AbsoluteConceptualEvolution = AbsoluteTranscendenceLevel * 5.7f;
    AbsoluteTranscendenceAuthority = AbsoluteTranscendenceLevel * 6.2f;
}

void UP09_TRNS_ABSOLUTE::OnAbsoluteTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsAbsoluteTranscendenceActive)
    {
        // Apply absolute transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Absolute Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove absolute transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Absolute Transcendence state changed to INACTIVE"));
    }
}
