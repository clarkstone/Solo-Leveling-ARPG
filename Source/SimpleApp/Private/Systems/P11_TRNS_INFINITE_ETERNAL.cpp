#include "P11_TRNS_INFINITE_ETERNAL.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP11_TRNS_INFINITE_ETERNAL::UP11_TRNS_INFINITE_ETERNAL()
{
    PrimaryComponentTick.bCanEverTick = false;
    InfiniteEternalTranscendenceLevel = 0;
    MaxInfiniteEternalTranscendenceLevel = 100;
    bIsInfiniteEternalTranscendenceActive = false;
    InfiniteEternalTranscendencePowerCost = 60.0f;
    InfiniteEternalTranscendenceThreshold = 60.0f;
    
    // Initialize infinite eternal transcendence properties
    InfiniteEternalRealityDominion = 0.0f;
    InfiniteEternalTranscendenceRecursion = 0.0f;
    InfiniteEternalInfiniteConsciousness = 0.0f;
    InfiniteEternalConceptualEvolution = 0.0f;
    InfiniteEternalTranscendenceAuthority = 0.0f;
}

void UP11_TRNS_INFINITE_ETERNAL::BeginPlay()
{
    Super::BeginPlay();
    UpdateInfiniteEternalTranscendenceStats();
}

void UP11_TRNS_INFINITE_ETERNAL::ActivateInfiniteEternalTranscendence()
{
    if (!bIsInfiniteEternalTranscendenceActive && CanActivateInfiniteEternalTranscendence())
    {
        bIsInfiniteEternalTranscendenceActive = true;
        OnInfiniteEternalTranscendenceActivated.Broadcast(InfiniteEternalTranscendenceLevel);
        OnInfiniteEternalTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Transcendence System Activated at Level: %d"), InfiniteEternalTranscendenceLevel);
    }
}

void UP11_TRNS_INFINITE_ETERNAL::DeactivateInfiniteEternalTranscendence()
{
    if (bIsInfiniteEternalTranscendenceActive)
    {
        bIsInfiniteEternalTranscendenceActive = false;
        OnInfiniteEternalTranscendenceDeactivated.Broadcast(InfiniteEternalTranscendenceLevel);
        OnInfiniteEternalTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Transcendence System Deactivated."));
    }
}

void UP11_TRNS_INFINITE_ETERNAL::SetInfiniteEternalTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxInfiniteEternalTranscendenceLevel)
    {
        int32 OldLevel = InfiniteEternalTranscendenceLevel;
        InfiniteEternalTranscendenceLevel = NewLevel;
        UpdateInfiniteEternalTranscendenceStats();
        OnInfiniteEternalTranscendenceLevelChanged.Broadcast(OldLevel, InfiniteEternalTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Transcendence Level set to: %d"), InfiniteEternalTranscendenceLevel);
        
        if (InfiniteEternalTranscendenceLevel >= MaxInfiniteEternalTranscendenceLevel)
        {
            OnInfiniteEternalTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Transcendence Max Level Reached!"));
        }
    }
}

void UP11_TRNS_INFINITE_ETERNAL::UseInfiniteEternalTranscendencePower()
{
    if (bIsInfiniteEternalTranscendenceActive && InfiniteEternalTranscendenceLevel > 0)
    {
        OnInfiniteEternalTranscendencePowerUsed.Broadcast(InfiniteEternalTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Transcendence Power Used: %.2f"), InfiniteEternalTranscendencePowerCost);
    }
    else
    {
        OnInfiniteEternalTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UP11_TRNS_INFINITE_ETERNAL::PerformInfiniteEternalTranscendenceAbility()
{
    if (bIsInfiniteEternalTranscendenceActive && InfiniteEternalTranscendenceLevel >= InfiniteEternalTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Infinite Eternal Transcendence Ability at Level %d!"), InfiniteEternalTranscendenceLevel);
        OnInfiniteEternalTranscendenceAbilityPerformed.Broadcast(InfiniteEternalTranscendenceLevel);
        UseInfiniteEternalTranscendencePower();
        
        // Perform infinite eternal transcendence ability based on level
        switch (InfiniteEternalTranscendenceLevel / 20)
        {
            case 0:
                ExerciseInfiniteEternalRealityDominion();
                break;
            case 1:
                TranscendInfiniteEternalRecursion();
                break;
            case 2:
                AccessInfiniteEternalInfiniteConsciousness();
                break;
            case 3:
                EvolveConceptually();
                break;
            case 4:
            case 5:
                WieldInfiniteEternalTranscendenceAuthority();
                break;
            default:
                WieldInfiniteEternalTranscendenceAuthority();
                break;
        }
    }
    }
    else if (InfiniteEternalTranscendenceLevel < InfiniteEternalTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), InfiniteEternalTranscendenceThreshold, InfiniteEternalTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Transcendence is not active, cannot perform ability."));
    }
}

bool UP11_TRNS_INFINITE_ETERNAL::IsInfiniteEternalTranscendenceActive() const
{
    return bIsInfiniteEternalTranscendenceActive;
}

int32 UP11_TRNS_INFINITE_ETERNAL::GetInfiniteEternalTranscendenceLevel() const
{
    return InfiniteEternalTranscendenceLevel;
}

float UP11_TRNS_INFINITE_ETERNAL::GetInfiniteEternalTranscendencePowerCost() const
{
    return InfiniteEternalTranscendencePowerCost;
}

void UP11_TRNS_INFINITE_ETERNAL::ExerciseInfiniteEternalRealityDominion()
{
    if (bIsInfiniteEternalTranscendenceActive)
    {
        float DominionPower = InfiniteEternalRealityDominion * (InfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Infinite Eternal Reality Dominion with power: %.2f"), DominionPower);
        // Apply infinite eternal reality dominion effects
    }
}

void UP11_TRNS_INFINITE_ETERNAL::TranscendInfiniteEternalRecursion()
{
    if (bIsInfiniteEternalTranscendenceActive)
    {
        float RecursionPower = InfiniteEternalTranscendenceRecursion * (InfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Infinite Eternal Recursion with power: %.2f"), RecursionPower);
        // Apply infinite eternal transcendence recursion effects
    }
}

void UP11_TRNS_INFINITE_ETERNAL::AccessInfiniteEternalInfiniteConsciousness()
{
    if (bIsInfiniteEternalTranscendenceActive)
    {
        float ConsciousnessPower = InfiniteEternalInfiniteConsciousness * (InfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Infinite Eternal Infinite Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply infinite eternal infinite consciousness effects
    }
}

void UP11_TRNS_INFINITE_ETERNAL::EvolveConceptually()
{
    if (bIsInfiniteEternalTranscendenceActive)
    {
        float EvolutionPower = InfiniteEternalConceptualEvolution * (InfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually with power: %.2f"), EvolutionPower);
        // Apply infinite eternal conceptual evolution effects
    }
}

void UP11_TRNS_INFINITE_ETERNAL::WieldInfiniteEternalTranscendenceAuthority()
{
    if (bIsInfiniteEternalTranscendenceActive)
    {
        float AuthorityPower = InfiniteEternalTranscendenceAuthority * (InfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Infinite Eternal Transcendence Authority with power: %.2f"), AuthorityPower);
        // Apply infinite eternal transcendence authority effects
    }
}

bool UP11_TRNS_INFINITE_ETERNAL::CanActivateInfiniteEternalTranscendence() const
{
    return InfiniteEternalTranscendenceLevel > 0;
}

void UP11_TRNS_INFINITE_ETERNAL::UpdateInfiniteEternalTranscendenceStats()
{
    // Update infinite eternal transcendence properties based on level
    InfiniteEternalRealityDominion = InfiniteEternalTranscendenceLevel * 7.0f;
    InfiniteEternalTranscendenceRecursion = InfiniteEternalTranscendenceLevel * 6.8f;
    InfiniteEternalInfiniteConsciousness = InfiniteEternalTranscendenceLevel * 6.6f;
    InfiniteEternalConceptualEvolution = InfiniteEternalTranscendenceLevel * 6.7f;
    InfiniteEternalTranscendenceAuthority = InfiniteEternalTranscendenceLevel * 7.2f;
}

void UP11_TRNS_INFINITE_ETERNAL::OnInfiniteEternalTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsInfiniteEternalTranscendenceActive)
    {
        // Apply infinite eternal transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove infinite eternal transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Transcendence state changed to INACTIVE"));
    }
}
