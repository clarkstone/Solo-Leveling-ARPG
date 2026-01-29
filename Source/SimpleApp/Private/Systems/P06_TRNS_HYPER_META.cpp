#include "P06_TRNS_HYPER_META.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP06_TRNS_HYPER_META::UP06_TRNS_HYPER_META()
{
    PrimaryComponentTick.bCanEverTick = false;
    HyperMetaTranscendenceLevel = 0;
    MaxHyperMetaTranscendenceLevel = 100;
    bIsHyperMetaTranscendenceActive = false;
    HyperMetaTranscendencePowerCost = 40.0f;
    HyperMetaTranscendenceThreshold = 40.0f;
    
    // Initialize hyper meta transcendence properties
    HyperMetaRealityDominion = 0.0f;
    HyperTranscendenceRecursion = 0.0f;
    HyperMetaInfiniteConsciousness = 0.0f;
    HyperConceptualEvolution = 0.0f;
    HyperMetaTranscendenceAuthority = 0.0f;
}

void UP06_TRNS_HYPER_META::BeginPlay()
{
    Super::BeginPlay();
    UpdateHyperMetaTranscendenceStats();
}

void UP06_TRNS_HYPER_META::ActivateHyperMetaTranscendence()
{
    if (!bIsHyperMetaTranscendenceActive && CanActivateHyperMetaTranscendence())
    {
        bIsHyperMetaTranscendenceActive = true;
        OnHyperMetaTranscendenceActivated.Broadcast(HyperMetaTranscendenceLevel);
        OnHyperMetaTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Hyper Meta Transcendence System Activated at Level: %d"), HyperMetaTranscendenceLevel);
    }
}

void UP06_TRNS_HYPER_META::DeactivateHyperMetaTranscendence()
{
    if (bIsHyperMetaTranscendenceActive)
    {
        bIsHyperMetaTranscendenceActive = false;
        OnHyperMetaTranscendenceDeactivated.Broadcast(HyperMetaTranscendenceLevel);
        OnHyperMetaTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Hyper Meta Transcendence System Deactivated."));
    }
}

void UP06_TRNS_HYPER_META::SetHyperMetaTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxHyperMetaTranscendenceLevel)
    {
        int32 OldLevel = HyperMetaTranscendenceLevel;
        HyperMetaTranscendenceLevel = NewLevel;
        UpdateHyperMetaTranscendenceStats();
        OnHyperMetaTranscendenceLevelChanged.Broadcast(OldLevel, HyperMetaTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Hyper Meta Transcendence Level set to: %d"), HyperMetaTranscendenceLevel);
        
        if (HyperMetaTranscendenceLevel >= MaxHyperMetaTranscendenceLevel)
        {
            OnHyperMetaTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Hyper Meta Transcendence Max Level Reached!"));
        }
    }
}

void UP06_TRNS_HYPER_META::UseHyperMetaTranscendencePower()
{
    if (bIsHyperMetaTranscendenceActive && HyperMetaTranscendenceLevel > 0)
    {
        OnHyperMetaTranscendencePowerUsed.Broadcast(HyperMetaTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Hyper Meta Transcendence Power Used: %.2f"), HyperMetaTranscendencePowerCost);
    }
    else
    {
        OnHyperMetaTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Hyper Meta Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UP06_TRNS_HYPER_META::PerformHyperMetaTranscendenceAbility()
{
    if (bIsHyperMetaTranscendenceActive && HyperMetaTranscendenceLevel >= HyperMetaTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Hyper Meta Transcendence Ability at Level %d!"), HyperMetaTranscendenceLevel);
        OnHyperMetaTranscendenceAbilityPerformed.Broadcast(HyperMetaTranscendenceLevel);
        UseHyperMetaTranscendencePower();
        
        // Perform hyper meta transcendence ability based on level
        switch (HyperMetaTranscendenceLevel / 20)
        {
            case 0:
                ExerciseHyperMetaRealityDominion();
                break;
            case 1:
                TranscendHyperMetaRecursion();
                break;
            case 2:
                AccessHyperMetaInfiniteConsciousness();
                break;
            case 3:
                EvolveHyperMetaConceptually();
                break;
            case 4:
            case 5:
                WieldHyperMetaTranscendenceAuthority();
                break;
            default:
                WieldHyperMetaTranscendenceAuthority();
                break;
        }
    }
    }
    else if (HyperMetaTranscendenceLevel < HyperMetaTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hyper Meta Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), HyperMetaTranscendenceThreshold, HyperMetaTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Hyper Meta Transcendence is not active, cannot perform ability."));
    }
}

bool UP06_TRNS_HYPER_META::IsHyperMetaTranscendenceActive() const
{
    return bIsHyperMetaTranscendenceActive;
}

int32 UP06_TRNS_HYPER_META::GetHyperMetaTranscendenceLevel() const
{
    return HyperMetaTranscendenceLevel;
}

float UP06_TRNS_HYPER_META::GetHyperMetaTranscendencePowerCost() const
{
    return HyperMetaTranscendencePowerCost;
}

void UP06_TRNS_HYPER_META::ExerciseHyperMetaRealityDominion()
{
    if (bIsHyperMetaTranscendenceActive)
    {
        float DominionPower = HyperMetaRealityDominion * (HyperMetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Hyper Meta Reality Dominion with power: %.2f"), DominionPower);
        // Apply hyper meta reality dominion effects
    }
}

void UP06_TRNS_HYPER_META::TranscendHyperMetaRecursion()
{
    if (bIsHyperMetaTranscendenceActive)
    {
        float RecursionPower = HyperTranscendenceRecursion * (HyperMetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Hyper Meta Recursion with power: %.2f"), RecursionPower);
        // Apply hyper meta transcendence recursion effects
    }
}

void UP06_TRNS_HYPER_META::AccessHyperMetaInfiniteConsciousness()
{
    if (bIsHyperMetaTranscendenceActive)
    {
        float ConsciousnessPower = HyperMetaInfiniteConsciousness * (HyperMetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Hyper Meta Infinite Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply hyper meta infinite consciousness effects
    }
}

void UP06_TRNS_HYPER_META::EvolveHyperMetaConceptually()
{
    if (bIsHyperMetaTranscendenceActive)
    {
        float EvolutionPower = HyperConceptualEvolution * (HyperMetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Hyper Meta Conceptually with power: %.2f"), EvolutionPower);
        // Apply hyper meta conceptual evolution effects
    }
}

void UP06_TRNS_HYPER_META::WieldHyperMetaTranscendenceAuthority()
{
    if (bIsHyperMetaTranscendenceActive)
    {
        float AuthorityPower = HyperMetaTranscendenceAuthority * (HyperMetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Hyper Meta Transcendence Authority with power: %.2f"), AuthorityPower);
        // Apply hyper meta transcendence authority effects
    }
}

bool UP06_TRNS_HYPER_META::CanActivateHyperMetaTranscendence() const
{
    return HyperMetaTranscendenceLevel > 0;
}

void UP06_TRNS_HYPER_META::UpdateHyperMetaTranscendenceStats()
{
    // Update hyper meta transcendence properties based on level
    HyperMetaRealityDominion = HyperMetaTranscendenceLevel * 5.0f;
    HyperTranscendenceRecursion = HyperMetaTranscendenceLevel * 4.8f;
    HyperMetaInfiniteConsciousness = HyperMetaTranscendenceLevel * 4.6f;
    HyperConceptualEvolution = HyperMetaTranscendenceLevel * 4.7f;
    HyperMetaTranscendenceAuthority = HyperMetaTranscendenceLevel * 5.2f;
}

void UP06_TRNS_HYPER_META::OnHyperMetaTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsHyperMetaTranscendenceActive)
    {
        // Apply hyper meta transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Hyper Meta Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove hyper meta transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Hyper Meta Transcendence state changed to INACTIVE"));
    }
}
