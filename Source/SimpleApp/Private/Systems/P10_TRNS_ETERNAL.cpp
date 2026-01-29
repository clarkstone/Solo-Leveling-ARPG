#include "P10_TRNS_ETERNAL.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP10_TRNS_ETERNAL::UP10_TRNS_ETERNAL()
{
    PrimaryComponentTick.bCanEverTick = false;
    EternalTranscendenceLevel = 0;
    MaxEternalTranscendenceLevel = 100;
    bIsEternalTranscendenceActive = false;
    EternalTranscendencePowerCost = 55.0f;
    EternalTranscendenceThreshold = 55.0f;
    
    // Initialize eternal transcendence properties
    EternalRealityDominion = 0.0f;
    EternalTranscendenceRecursion = 0.0f;
    EternalInfiniteConsciousness = 0.0f;
    EternalConceptualEvolution = 0.0f;
    EternalTranscendenceAuthority = 0.0f;
}

void UP10_TRNS_ETERNAL::BeginPlay()
{
    Super::BeginPlay();
    UpdateEternalTranscendenceStats();
}

void UP10_TRNS_ETERNAL::ActivateEternalTranscendence()
{
    if (!bIsEternalTranscendenceActive && CanActivateEternalTranscendence())
    {
        bIsEternalTranscendenceActive = true;
        OnEternalTranscendenceActivated.Broadcast(EternalTranscendenceLevel);
        OnEternalTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Eternal Transcendence System Activated at Level: %d"), EternalTranscendenceLevel);
    }
}

void UP10_TRNS_ETERNAL::DeactivateEternalTranscendence()
{
    if (bIsEternalTranscendenceActive)
    {
        bIsEternalTranscendenceActive = false;
        OnEternalTranscendenceDeactivated.Broadcast(EternalTranscendenceLevel);
        OnEternalTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Eternal Transcendence System Deactivated."));
    }
}

void UP10_TRNS_ETERNAL::SetEternalTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxEternalTranscendenceLevel)
    {
        int32 OldLevel = EternalTranscendenceLevel;
        EternalTranscendenceLevel = NewLevel;
        UpdateEternalTranscendenceStats();
        OnEternalTranscendenceLevelChanged.Broadcast(OldLevel, EternalTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Eternal Transcendence Level set to: %d"), EternalTranscendenceLevel);
        
        if (EternalTranscendenceLevel >= MaxEternalTranscendenceLevel)
        {
            OnEternalTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Eternal Transcendence Max Level Reached!"));
        }
    }
}

void UP10_TRNS_ETERNAL::UseEternalTranscendencePower()
{
    if (bIsEternalTranscendenceActive && EternalTranscendenceLevel > 0)
    {
        OnEternalTranscendencePowerUsed.Broadcast(EternalTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Eternal Transcendence Power Used: %.2f"), EternalTranscendencePowerCost);
    }
    else
    {
        OnEternalTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Eternal Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UP10_TRNS_ETERNAL::PerformEternalTranscendenceAbility()
{
    if (bIsEternalTranscendenceActive && EternalTranscendenceLevel >= EternalTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Eternal Transcendence Ability at Level %d!"), EternalTranscendenceLevel);
        OnEternalTranscendenceAbilityPerformed.Broadcast(EternalTranscendenceLevel);
        UseEternalTranscendencePower();
        
        // Perform eternal transcendence ability based on level
        switch (EternalTranscendenceLevel / 20)
        {
            case 0:
                ExerciseEternalRealityDominion();
                break;
            case 1:
                TranscendEternalRecursion();
                break;
            case 2:
                AccessEternalInfiniteConsciousness();
                break;
            case 3:
                EvolveConceptually();
                break;
            case 4:
            case 5:
                WieldEternalTranscendenceAuthority();
                break;
            default:
                WieldEternalTranscendenceAuthority();
                break;
        }
    }
    }
    else if (EternalTranscendenceLevel < EternalTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Eternal Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), EternalTranscendenceThreshold, EternalTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Eternal Transcendence is not active, cannot perform ability."));
    }
}

bool UP10_TRNS_ETERNAL::IsEternalTranscendenceActive() const
{
    return bIsEternalTranscendenceActive;
}

int32 UP10_TRNS_ETERNAL::GetEternalTranscendenceLevel() const
{
    return EternalTranscendenceLevel;
}

float UP10_TRNS_ETERNAL::GetEternalTranscendencePowerCost() const
{
    return EternalTranscendencePowerCost;
}

void UP10_TRNS_ETERNAL::ExerciseEternalRealityDominion()
{
    if (bIsEternalTranscendenceActive)
    {
        float DominionPower = EternalRealityDominion * (EternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Eternal Reality Dominion with power: %.2f"), DominionPower);
        // Apply eternal reality dominion effects
    }
}

void UP10_TRNS_ETERNAL::TranscendEternalRecursion()
{
    if (bIsEternalTranscendenceActive)
    {
        float RecursionPower = EternalTranscendenceRecursion * (EternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Eternal Recursion with power: %.2f"), RecursionPower);
        // Apply eternal transcendence recursion effects
    }
}

void UP10_TRNS_ETERNAL::AccessEternalInfiniteConsciousness()
{
    if (bIsEternalTranscendenceActive)
    {
        float ConsciousnessPower = EternalInfiniteConsciousness * (EternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Eternal Infinite Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply eternal infinite consciousness effects
    }
}

void UP10_TRNS_ETERNAL::EvolveConceptually()
{
    if (bIsEternalTranscendenceActive)
    {
        float EvolutionPower = EternalConceptualEvolution * (EternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually with power: %.2f"), EvolutionPower);
        // Apply eternal conceptual evolution effects
    }
}

void UP10_TRNS_ETERNAL::WieldEternalTranscendenceAuthority()
{
    if (bIsEternalTranscendenceActive)
    {
        float AuthorityPower = EternalTranscendenceAuthority * (EternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Eternal Transcendence Authority with power: %.2f"), AuthorityPower);
        // Apply eternal transcendence authority effects
    }
}

bool UP10_TRNS_ETERNAL::CanActivateEternalTranscendence() const
{
    return EternalTranscendenceLevel > 0;
}

void UP10_TRNS_ETERNAL::UpdateEternalTranscendenceStats()
{
    // Update eternal transcendence properties based on level
    EternalRealityDominion = EternalTranscendenceLevel * 6.5f;
    EternalTranscendenceRecursion = EternalTranscendenceLevel * 6.3f;
    EternalInfiniteConsciousness = EternalTranscendenceLevel * 6.1f;
    EternalConceptualEvolution = EternalTranscendenceLevel * 6.2f;
    EternalTranscendenceAuthority = EternalTranscendenceLevel * 6.7f;
}

void UP10_TRNS_ETERNAL::OnEternalTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsEternalTranscendenceActive)
    {
        // Apply eternal transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Eternal Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove eternal transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Eternal Transcendence state changed to INACTIVE"));
    }
}
