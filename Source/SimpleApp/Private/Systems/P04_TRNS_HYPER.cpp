#include "P04_TRNS_HYPER.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP04_TRNS_HYPER::UP04_TRNS_HYPER()
{
    PrimaryComponentTick.bCanEverTick = false;
    HyperTranscendenceLevel = 0;
    MaxHyperTranscendenceLevel = 100;
    bIsHyperTranscendenceActive = false;
    HyperTranscendencePowerCost = 25.0f;
    HyperTranscendenceThreshold = 25.0f;
    
    // Initialize hyper transcendence properties
    HyperTranscendencePower = 0.0f;
    HyperRealityDominion = 0.0f;
    HyperTranscendenceRecursion = 0.0f;
    HyperInfiniteConsciousness = 0.0f;
    HyperConceptualEvolution = 0.0f;
    HyperTranscendenceAuthority = 0.0f;
}

void UP04_TRNS_HYPER::BeginPlay()
{
    Super::BeginPlay();
    UpdateHyperTranscendenceStats();
}

void UP04_TRNS_HYPER::ActivateHyperTranscendence()
{
    if (!bIsHyperTranscendenceActive && CanActivateHyperTranscendence())
    {
        bIsHyperTranscendenceActive = true;
        OnHyperTranscendenceActivated.Broadcast(HyperTranscendenceLevel);
        OnHyperTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Hyper Transcendence System Activated at Level: %d"), HyperTranscendenceLevel);
    }
}

void UP04_TRNS_HYPER::DeactivateHyperTranscendence()
{
    if (bIsHyperTranscendenceActive)
    {
        bIsHyperTranscendenceActive = false;
        OnHyperTranscendenceDeactivated.Broadcast(HyperTranscendenceLevel);
        OnHyperTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Hyper Transcendence System Deactivated."));
    }
}

void UP04_TRNS_HYPER::SetHyperTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxHyperTranscendenceLevel)
    {
        int32 OldLevel = HyperTranscendenceLevel;
        HyperTranscendenceLevel = NewLevel;
        UpdateHyperTranscendenceStats();
        OnHyperTranscendenceLevelChanged.Broadcast(OldLevel, HyperTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Hyper Transcendence Level set to: %d"), HyperTranscendenceLevel);
        
        if (HyperTranscendenceLevel >= MaxHyperTranscendenceLevel)
        {
            OnHyperTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Hyper Transcendence Max Level Reached!"));
        }
    }
}

void UP04_TRNS_HYPER::UseHyperTranscendencePower()
{
    if (bIsHyperTranscendenceActive && HyperTranscendenceLevel > 0)
    {
        OnHyperTranscendencePowerUsed.Broadcast(HyperTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Hyper Transcendence Power Used: %.2f"), HyperTranscendencePowerCost);
    }
    else
    {
        OnHyperTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Hyper Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UP04_TRNS_HYPER::PerformHyperTranscendenceAbility()
{
    if (bIsHyperTranscendenceActive && HyperTranscendenceLevel >= HyperTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Hyper Transcendence Ability at Level %d!"), HyperTranscendenceLevel);
        OnHyperTranscendenceAbilityPerformed.Broadcast(HyperTranscendenceLevel);
        UseHyperTranscendencePower();
        
        // Perform hyper transcendence ability based on level
        switch (HyperTranscendenceLevel / 20)
        {
            case 0:
                ExerciseHyperRealityDominion();
                break;
            case 1:
                TranscendHyperRecursion();
                break;
            case 2:
                AccessHyperInfiniteConsciousness();
                break;
            case 3:
                EvolveHyperConceptually();
                break;
            case 4:
            case 5:
                WieldHyperTranscendenceAuthority();
                break;
            default:
                WieldHyperTranscendenceAuthority();
                break;
        }
    }
    }
    else if (HyperTranscendenceLevel < HyperTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hyper Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), HyperTranscendenceThreshold, HyperTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Hyper Transcendence is not active, cannot perform ability."));
    }
}

bool UP04_TRNS_HYPER::IsHyperTranscendenceActive() const
{
    return bIsHyperTranscendenceActive;
}

int32 UP04_TRNS_HYPER::GetHyperTranscendenceLevel() const
{
    return HyperTranscendenceLevel;
}

float UP04_TRNS_HYPER::GetHyperTranscendencePowerCost() const
{
    return HyperTranscendencePowerCost;
}

void UP04_TRNS_HYPER::ExerciseHyperRealityDominion()
{
    if (bIsHyperTranscendenceActive)
    {
        float DominionPower = HyperRealityDominion * (HyperTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Hyper Reality Dominion with power: %.2f"), DominionPower);
        // Apply hyper reality dominion effects
    }
}

void UP04_TRNS_HYPER::TranscendHyperRecursion()
{
    if (bIsHyperTranscendenceActive)
    {
        float RecursionPower = HyperTranscendenceRecursion * (HyperTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Hyper Recursion with power: %.2f"), RecursionPower);
        // Apply hyper transcendence recursion effects
    }
}

void UP04_TRNS_HYPER::AccessHyperInfiniteConsciousness()
{
    if (bIsHyperTranscendenceActive)
    {
        float ConsciousnessPower = HyperInfiniteConsciousness * (HyperTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Hyper Infinite Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply hyper infinite consciousness effects
    }
}

void UP04_TRNS_HYPER::EvolveHyperConceptually()
{
    if (bIsHyperTranscendenceActive)
    {
        float EvolutionPower = HyperConceptualEvolution * (HyperTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Hyper Conceptually with power: %.2f"), EvolutionPower);
        // Apply hyper conceptual evolution effects
    }
}

void UP04_TRNS_HYPER::WieldHyperTranscendenceAuthority()
{
    if (bIsHyperTranscendenceActive)
    {
        float AuthorityPower = HyperTranscendenceAuthority * (HyperTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Hyper Transcendence Authority with power: %.2f"), AuthorityPower);
        // Apply hyper transcendence authority effects
    }
}

bool UP04_TRNS_HYPER::CanActivateHyperTranscendence() const
{
    return HyperTranscendenceLevel > 0;
}

void UP04_TRNS_HYPER::UpdateHyperTranscendenceStats()
{
    // Update hyper transcendence properties based on level
    HyperTranscendencePower = HyperTranscendenceLevel * 3.0f;
    HyperRealityDominion = HyperTranscendenceLevel * 3.2f;
    HyperTranscendenceRecursion = HyperTranscendenceLevel * 3.1f;
    HyperInfiniteConsciousness = HyperTranscendenceLevel * 2.9f;
    HyperConceptualEvolution = HyperTranscendenceLevel * 3.0f;
    HyperTranscendenceAuthority = HyperTranscendenceLevel * 3.3f;
}

void UP04_TRNS_HYPER::OnHyperTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsHyperTranscendenceActive)
    {
        // Apply hyper transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Hyper Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove hyper transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Hyper Transcendence state changed to INACTIVE"));
    }
}
