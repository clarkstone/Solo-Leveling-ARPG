#include "P04_TRNS_INFINITE.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP04_TRNS_INFINITE::UP04_TRNS_INFINITE()
{
    PrimaryComponentTick.bCanEverTick = false;
    InfiniteTranscendenceLevel = 0;
    MaxInfiniteTranscendenceLevel = 100;
    bIsInfiniteTranscendenceActive = false;
    InfiniteTranscendencePowerCost = 25.0f;
    InfiniteTranscendenceThreshold = 25.0f;
    
    // Initialize infinite transcendence properties
    InfiniteTranscendencePower = 0.0f;
    InfiniteRealityDominion = 0.0f;
    InfiniteTranscendenceRecursion = 0.0f;
    InfiniteInfiniteConsciousness = 0.0f;
    InfiniteConceptualEvolution = 0.0f;
    InfiniteTranscendenceAuthority = 0.0f;
}

void UP04_TRNS_INFINITE::BeginPlay()
{
    Super::BeginPlay();
    UpdateInfiniteTranscendenceStats();
}

void UP04_TRNS_INFINITE::ActivateInfiniteTranscendence()
{
    if (!bIsInfiniteTranscendenceActive && CanActivateInfiniteTranscendence())
    {
        bIsInfiniteTranscendenceActive = true;
        OnInfiniteTranscendenceActivated.Broadcast(InfiniteTranscendenceLevel);
        OnInfiniteTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Transcendence System Activated at Level: %d"), InfiniteTranscendenceLevel);
    }
}

void UP04_TRNS_INFINITE::DeactivateInfiniteTranscendence()
{
    if (bIsInfiniteTranscendenceActive)
    {
        bIsInfiniteTranscendenceActive = false;
        OnInfiniteTranscendenceDeactivated.Broadcast(InfiniteTranscendenceLevel);
        OnInfiniteTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Transcendence System Deactivated."));
    }
}

void UP04_TRNS_INFINITE::SetInfiniteTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxInfiniteTranscendenceLevel)
    {
        int32 OldLevel = InfiniteTranscendenceLevel;
        InfiniteTranscendenceLevel = NewLevel;
        UpdateInfiniteTranscendenceStats();
        OnInfiniteTranscendenceLevelChanged.Broadcast(OldLevel, InfiniteTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Infinite Transcendence Level set to: %d"), InfiniteTranscendenceLevel);
        
        if (InfiniteTranscendenceLevel >= MaxInfiniteTranscendenceLevel)
        {
            OnInfiniteTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Infinite Transcendence Max Level Reached!"));
        }
    }
}

void UP04_TRNS_INFINITE::UseInfiniteTranscendencePower()
{
    if (bIsInfiniteTranscendenceActive && InfiniteTranscendenceLevel > 0)
    {
        OnInfiniteTranscendencePowerUsed.Broadcast(InfiniteTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Infinite Transcendence Power Used: %.2f"), InfiniteTranscendencePowerCost);
    }
    else
    {
        OnInfiniteTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UP04_TRNS_INFINITE::PerformInfiniteTranscendenceAbility()
{
    if (bIsInfiniteTranscendenceActive && InfiniteTranscendenceLevel >= InfiniteTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Infinite Transcendence Ability at Level %d!"), InfiniteTranscendenceLevel);
        OnInfiniteTranscendenceAbilityPerformed.Broadcast(InfiniteTranscendenceLevel);
        UseInfiniteTranscendencePower();
        
        // Perform infinite transcendence ability based on level
        switch (InfiniteTranscendenceLevel / 20)
        {
            case 0:
                ExerciseInfiniteRealityDominion();
                break;
            case 1:
                TranscendInfiniteRecursion();
                break;
            case 2:
                AccessInfiniteConsciousness();
                break;
            case 3:
                EvolveInfiniteConceptually();
                break;
            case 4:
            case 5:
                WieldInfiniteTranscendenceAuthority();
                break;
            default:
                WieldInfiniteTranscendenceAuthority();
                break;
        }
    }
    }
    else if (InfiniteTranscendenceLevel < InfiniteTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Infinite Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), InfiniteTranscendenceThreshold, InfiniteTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Infinite Transcendence is not active, cannot perform ability."));
    }
}

bool UP04_TRNS_INFINITE::IsInfiniteTranscendenceActive() const
{
    return bIsInfiniteTranscendenceActive;
}

int32 UP04_TRNS_INFINITE::GetInfiniteTranscendenceLevel() const
{
    return InfiniteTranscendenceLevel;
}

float UP04_TRNS_INFINITE::GetInfiniteTranscendencePowerCost() const
{
    return InfiniteTranscendencePowerCost;
}

void UP04_TRNS_INFINITE::ExerciseInfiniteRealityDominion()
{
    if (bIsInfiniteTranscendenceActive)
    {
        float DominionPower = InfiniteRealityDominion * (InfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Infinite Reality Dominion with power: %.2f"), DominionPower);
        // Apply infinite reality dominion effects
    }
}

void UP04_TRNS_INFINITE::TranscendInfiniteRecursion()
{
    if (bIsInfiniteTranscendenceActive)
    {
        float RecursionPower = InfiniteTranscendenceRecursion * (InfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Infinite Recursion with power: %.2f"), RecursionPower);
        // Apply infinite transcendence recursion effects
    }
}

void UP04_TRNS_INFINITE::AccessInfiniteConsciousness()
{
    if (bIsInfiniteTranscendenceActive)
    {
        float ConsciousnessPower = InfiniteInfiniteConsciousness * (InfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Infinite Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply infinite consciousness effects
    }
}

void UP04_TRNS_INFINITE::EvolveInfiniteConceptually()
{
    if (bIsInfiniteTranscendenceActive)
    {
        float EvolutionPower = InfiniteConceptualEvolution * (InfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Infinite Conceptually with power: %.2f"), EvolutionPower);
        // Apply infinite conceptual evolution effects
    }
}

void UP04_TRNS_INFINITE::WieldInfiniteTranscendenceAuthority()
{
    if (bIsInfiniteTranscendenceActive)
    {
        float AuthorityPower = InfiniteTranscendenceAuthority * (InfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Infinite Transcendence Authority with power: %.2f"), AuthorityPower);
        // Apply infinite transcendence authority effects
    }
}

bool UP04_TRNS_INFINITE::CanActivateInfiniteTranscendence() const
{
    return InfiniteTranscendenceLevel > 0;
}

void UP04_TRNS_INFINITE::UpdateInfiniteTranscendenceStats()
{
    // Update infinite transcendence properties based on level
    InfiniteTranscendencePower = InfiniteTranscendenceLevel * 4.0f;
    InfiniteRealityDominion = InfiniteTranscendenceLevel * 4.2f;
    InfiniteTranscendenceRecursion = InfiniteTranscendenceLevel * 4.1f;
    InfiniteInfiniteConsciousness = InfiniteTranscendenceLevel * 3.9f;
    InfiniteConceptualEvolution = InfiniteTranscendenceLevel * 4.0f;
    InfiniteTranscendenceAuthority = InfiniteTranscendenceLevel * 4.3f;
}

void UP04_TRNS_INFINITE::OnInfiniteTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsInfiniteTranscendenceActive)
    {
        // Apply infinite transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Infinite Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove infinite transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Infinite Transcendence state changed to INACTIVE"));
    }
}
