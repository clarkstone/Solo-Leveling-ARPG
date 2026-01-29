#include "P12_TRNS_OMEGA_INFINITE_ETERNAL.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP12_TRNS_OMEGA_INFINITE_ETERNAL::UP12_TRNS_OMEGA_INFINITE_ETERNAL()
{
    PrimaryComponentTick.bCanEverTick = false;
    OmegaInfiniteEternalTranscendenceLevel = 0;
    MaxOmegaInfiniteEternalTranscendenceLevel = 100;
    bIsOmegaInfiniteEternalTranscendenceActive = false;
    OmegaInfiniteEternalTranscendencePowerCost = 65.0f;
    OmegaInfiniteEternalTranscendenceThreshold = 65.0f;
    
    // Initialize omega infinite eternal transcendence properties
    OmegaInfiniteEternalRealityDominion = 0.0f;
    OmegaInfiniteEternalTranscendenceRecursion = 0.0f;
    OmegaInfiniteEternalInfiniteConsciousness = 0.0f;
    OmegaInfiniteEternalConceptualEvolution = 0.0f;
    OmegaInfiniteEternalTranscendenceAuthority = 0.0f;
}

void UP12_TRNS_OMEGA_INFINITE_ETERNAL::BeginPlay()
{
    Super::BeginPlay();
    UpdateOmegaInfiniteEternalTranscendenceStats();
}

void UP12_TRNS_OMEGA_INFINITE_ETERNAL::ActivateOmegaInfiniteEternalTranscendence()
{
    if (!bIsOmegaInfiniteEternalTranscendenceActive && CanActivateOmegaInfiniteEternalTranscendence())
    {
        bIsOmegaInfiniteEternalTranscendenceActive = true;
        OnOmegaInfiniteEternalTranscendenceActivated.Broadcast(OmegaInfiniteEternalTranscendenceLevel);
        OnOmegaInfiniteEternalTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Transcendence System Activated at Level: %d"), OmegaInfiniteEternalTranscendenceLevel);
    }
}

void UP12_TRNS_OMEGA_INFINITE_ETERNAL::DeactivateOmegaInfiniteEternalTranscendence()
{
    if (bIsOmegaInfiniteEternalTranscendenceActive)
    {
        bIsOmegaInfiniteEternalTranscendenceActive = false;
        OnOmegaInfiniteEternalTranscendenceDeactivated.Broadcast(OmegaInfiniteEternalTranscendenceLevel);
        OnOmegaInfiniteEternalTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Transcendence System Deactivated."));
    }
}

void UP12_TRNS_OMEGA_INFINITE_ETERNAL::SetOmegaInfiniteEternalTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxOmegaInfiniteEternalTranscendenceLevel)
    {
        int32 OldLevel = OmegaInfiniteEternalTranscendenceLevel;
        OmegaInfiniteEternalTranscendenceLevel = NewLevel;
        UpdateOmegaInfiniteEternalTranscendenceStats();
        OnOmegaInfiniteEternalTranscendenceLevelChanged.Broadcast(OldLevel, OmegaInfiniteEternalTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Transcendence Level set to: %d"), OmegaInfiniteEternalTranscendenceLevel);
        
        if (OmegaInfiniteEternalTranscendenceLevel >= MaxOmegaInfiniteEternalTranscendenceLevel)
        {
            OnOmegaInfiniteEternalTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Transcendence Max Level Reached!"));
        }
    }
}

void UP12_TRNS_OMEGA_INFINITE_ETERNAL::UseOmegaInfiniteEternalTranscendencePower()
{
    if (bIsOmegaInfiniteEternalTranscendenceActive && OmegaInfiniteEternalTranscendenceLevel > 0)
    {
        OnOmegaInfiniteEternalTranscendencePowerUsed.Broadcast(OmegaInfiniteEternalTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Transcendence Power Used: %.2f"), OmegaInfiniteEternalTranscendencePowerCost);
    }
    else
    {
        OnOmegaInfiniteEternalTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UP12_TRNS_OMEGA_INFINITE_ETERNAL::PerformOmegaInfiniteEternalTranscendenceAbility()
{
    if (bIsOmegaInfiniteEternalTranscendenceActive && OmegaInfiniteEternalTranscendenceLevel >= OmegaInfiniteEternalTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Omega Infinite Eternal Transcendence Ability at Level %d!"), OmegaInfiniteEternalTranscendenceLevel);
        OnOmegaInfiniteEternalTranscendenceAbilityPerformed.Broadcast(OmegaInfiniteEternalTranscendenceLevel);
        UseOmegaInfiniteEternalTranscendencePower();
        
        // Perform omega infinite eternal transcendence ability based on level
        switch (OmegaInfiniteEternalTranscendenceLevel / 20)
        {
            case 0:
                ExerciseOmegaInfiniteEternalRealityDominion();
                break;
            case 1:
                TranscendOmegaInfiniteEternalRecursion();
                break;
            case 2:
                AccessOmegaInfiniteEternalInfiniteConsciousness();
                break;
            case 3:
                EvolveConceptually();
                break;
            case 4:
            case 5:
                WieldOmegaInfiniteEternalTranscendenceAuthority();
                break;
            default:
                WieldOmegaInfiniteEternalTranscendenceAuthority();
                break;
        }
    }
    }
    else if (OmegaInfiniteEternalTranscendenceLevel < OmegaInfiniteEternalTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), OmegaInfiniteEternalTranscendenceThreshold, OmegaInfiniteEternalTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Transcendence is not active, cannot perform ability."));
    }
}

bool UP12_TRNS_OMEGA_INFINITE_ETERNAL::IsOmegaInfiniteEternalTranscendenceActive() const
{
    return bIsOmegaInfiniteEternalTranscendenceActive;
}

int32 UP12_TRNS_OMEGA_INFINITE_ETERNAL::GetOmegaInfiniteEternalTranscendenceLevel() const
{
    return OmegaInfiniteEternalTranscendenceLevel;
}

float UP12_TRNS_OMEGA_INFINITE_ETERNAL::GetOmegaInfiniteEternalTranscendencePowerCost() const
{
    return OmegaInfiniteEternalTranscendencePowerCost;
}

void UP12_TRNS_OMEGA_INFINITE_ETERNAL::ExerciseOmegaInfiniteEternalRealityDominion()
{
    if (bIsOmegaInfiniteEternalTranscendenceActive)
    {
        float DominionPower = OmegaInfiniteEternalRealityDominion * (OmegaInfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Omega Infinite Eternal Reality Dominion with power: %.2f"), DominionPower);
        // Apply omega infinite eternal reality dominion effects
    }
}

void UP12_TRNS_OMEGA_INFINITE_ETERNAL::TranscendOmegaInfiniteEternalRecursion()
{
    if (bIsOmegaInfiniteEternalTranscendenceActive)
    {
        float RecursionPower = OmegaInfiniteEternalTranscendenceRecursion * (OmegaInfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Omega Infinite Eternal Recursion with power: %.2f"), RecursionPower);
        // Apply omega infinite eternal transcendence recursion effects
    }
}

void UP12_TRNS_OMEGA_INFINITE_ETERNAL::AccessOmegaInfiniteEternalInfiniteConsciousness()
{
    if (bIsOmegaInfiniteEternalTranscendenceActive)
    {
        float ConsciousnessPower = OmegaInfiniteEternalInfiniteConsciousness * (OmegaInfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Omega Infinite Eternal Infinite Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply omega infinite eternal infinite consciousness effects
    }
}

void UP12_TRNS_OMEGA_INFINITE_ETERNAL::EvolveConceptually()
{
    if (bIsOmegaInfiniteEternalTranscendenceActive)
    {
        float EvolutionPower = OmegaInfiniteEternalConceptualEvolution * (OmegaInfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually with power: %.2f"), EvolutionPower);
        // Apply omega infinite eternal conceptual evolution effects
    }
}

void UP12_TRNS_OMEGA_INFINITE_ETERNAL::WieldOmegaInfiniteEternalTranscendenceAuthority()
{
    if (bIsOmegaInfiniteEternalTranscendenceActive)
    {
        float AuthorityPower = OmegaInfiniteEternalTranscendenceAuthority * (OmegaInfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Omega Infinite Eternal Transcendence Authority with power: %.2f"), AuthorityPower);
        // Apply omega infinite eternal transcendence authority effects
    }
}

bool UP12_TRNS_OMEGA_INFINITE_ETERNAL::CanActivateOmegaInfiniteEternalTranscendence() const
{
    return OmegaInfiniteEternalTranscendenceLevel > 0;
}

void UP12_TRNS_OMEGA_INFINITE_ETERNAL::UpdateOmegaInfiniteEternalTranscendenceStats()
{
    // Update omega infinite eternal transcendence properties based on level
    OmegaInfiniteEternalRealityDominion = OmegaInfiniteEternalTranscendenceLevel * 7.5f;
    OmegaInfiniteEternalTranscendenceRecursion = OmegaInfiniteEternalTranscendenceLevel * 7.3f;
    OmegaInfiniteEternalInfiniteConsciousness = OmegaInfiniteEternalTranscendenceLevel * 7.1f;
    OmegaInfiniteEternalConceptualEvolution = OmegaInfiniteEternalTranscendenceLevel * 7.2f;
    OmegaInfiniteEternalTranscendenceAuthority = OmegaInfiniteEternalTranscendenceLevel * 7.7f;
}

void UP12_TRNS_OMEGA_INFINITE_ETERNAL::OnOmegaInfiniteEternalTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsOmegaInfiniteEternalTranscendenceActive)
    {
        // Apply omega infinite eternal transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove omega infinite eternal transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Transcendence state changed to INACTIVE"));
    }
}
