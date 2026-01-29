#include "P13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL()
{
    PrimaryComponentTick.bCanEverTick = false;
    OmegaOmegaInfiniteEternalTranscendenceLevel = 0;
    MaxOmegaOmegaInfiniteEternalTranscendenceLevel = 100;
    bIsOmegaOmegaInfiniteEternalTranscendenceActive = false;
    OmegaOmegaInfiniteEternalTranscendencePowerCost = 70.0f;
    OmegaOmegaInfiniteEternalTranscendenceThreshold = 70.0f;
    
    // Initialize omega omega infinite eternal transcendence properties
    OmegaOmegaInfiniteEternalRealityDominion = 0.0f;
    OmegaOmegaInfiniteEternalTranscendenceRecursion = 0.0f;
    OmegaOmegaInfiniteEternalInfiniteConsciousness = 0.0f;
    OmegaOmegaInfiniteEternalConceptualEvolution = 0.0f;
    OmegaOmegaInfiniteEternalTranscendenceAuthority = 0.0f;
}

void UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::BeginPlay()
{
    Super::BeginPlay();
    UpdateOmegaOmegaInfiniteEternalTranscendenceStats();
}

void UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::ActivateOmegaOmegaInfiniteEternalTranscendence()
{
    if (!bIsOmegaOmegaInfiniteEternalTranscendenceActive && CanActivateOmegaOmegaInfiniteEternalTranscendence())
    {
        bIsOmegaOmegaInfiniteEternalTranscendenceActive = true;
        OnOmegaOmegaInfiniteEternalTranscendenceActivated.Broadcast(OmegaOmegaInfiniteEternalTranscendenceLevel);
        OnOmegaOmegaInfiniteEternalTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Transcendence System Activated at Level: %d"), OmegaOmegaInfiniteEternalTranscendenceLevel);
    }
}

void UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::DeactivateOmegaOmegaInfiniteEternalTranscendence()
{
    if (bIsOmegaOmegaInfiniteEternalTranscendenceActive)
    {
        bIsOmegaOmegaInfiniteEternalTranscendenceActive = false;
        OnOmegaOmegaInfiniteEternalTranscendenceDeactivated.Broadcast(OmegaOmegaInfiniteEternalTranscendenceLevel);
        OnOmegaOmegaInfiniteEternalTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Transcendence System Deactivated."));
    }
}

void UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::SetOmegaOmegaInfiniteEternalTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxOmegaOmegaInfiniteEternalTranscendenceLevel)
    {
        int32 OldLevel = OmegaOmegaInfiniteEternalTranscendenceLevel;
        OmegaOmegaInfiniteEternalTranscendenceLevel = NewLevel;
        UpdateOmegaOmegaInfiniteEternalTranscendenceStats();
        OnOmegaOmegaInfiniteEternalTranscendenceLevelChanged.Broadcast(OldLevel, OmegaOmegaInfiniteEternalTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Transcendence Level set to: %d"), OmegaOmegaInfiniteEternalTranscendenceLevel);
        
        if (OmegaOmegaInfiniteEternalTranscendenceLevel >= MaxOmegaOmegaInfiniteEternalTranscendenceLevel)
        {
            OnOmegaOmegaInfiniteEternalTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Transcendence Max Level Reached!"));
        }
    }
}

void UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::UseOmegaOmegaInfiniteEternalTranscendencePower()
{
    if (bIsOmegaOmegaInfiniteEternalTranscendenceActive && OmegaOmegaInfiniteEternalTranscendenceLevel > 0)
    {
        OnOmegaOmegaInfiniteEternalTranscendencePowerUsed.Broadcast(OmegaOmegaInfiniteEternalTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Transcendence Power Used: %.2f"), OmegaOmegaInfiniteEternalTranscendencePowerCost);
    }
    else
    {
        OnOmegaOmegaInfiniteEternalTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::PerformOmegaOmegaInfiniteEternalTranscendenceAbility()
{
    if (bIsOmegaOmegaInfiniteEternalTranscendenceActive && OmegaOmegaInfiniteEternalTranscendenceLevel >= OmegaOmegaInfiniteEternalTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Omega Omega Infinite Eternal Transcendence Ability at Level %d!"), OmegaOmegaInfiniteEternalTranscendenceLevel);
        OnOmegaOmegaInfiniteEternalTranscendenceAbilityPerformed.Broadcast(OmegaOmegaInfiniteEternalTranscendenceLevel);
        UseOmegaOmegaInfiniteEternalTranscendencePower();
        
        // Perform omega omega infinite eternal transcendence ability based on level
        switch (OmegaOmegaInfiniteEternalTranscendenceLevel / 20)
        {
            case 0:
                ExerciseOmegaOmegaInfiniteEternalRealityDominion();
                break;
            case 1:
                TranscendOmegaOmegaInfiniteEternalRecursion();
                break;
            case 2:
                AccessOmegaOmegaInfiniteEternalInfiniteConsciousness();
                break;
            case 3:
                EvolveConceptually();
                break;
            case 4:
            case 5:
                WieldOmegaOmegaInfiniteEternalTranscendenceAuthority();
                break;
            default:
                WieldOmegaOmegaInfiniteEternalTranscendenceAuthority();
                break;
        }
    }
    }
    else if (OmegaOmegaInfiniteEternalTranscendenceLevel < OmegaOmegaInfiniteEternalTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), OmegaOmegaInfiniteEternalTranscendenceThreshold, OmegaOmegaInfiniteEternalTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Transcendence is not active, cannot perform ability."));
    }
}

bool UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::IsOmegaOmegaInfiniteEternalTranscendenceActive() const
{
    return bIsOmegaOmegaInfiniteEternalTranscendenceActive;
}

int32 UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::GetOmegaOmegaInfiniteEternalTranscendenceLevel() const
{
    return OmegaOmegaInfiniteEternalTranscendenceLevel;
}

float UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::GetOmegaOmegaInfiniteEternalTranscendencePowerCost() const
{
    return OmegaOmegaInfiniteEternalTranscendencePowerCost;
}

void UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::ExerciseOmegaOmegaInfiniteEternalRealityDominion()
{
    if (bIsOmegaOmegaInfiniteEternalTranscendenceActive)
    {
        float DominionPower = OmegaOmegaInfiniteEternalRealityDominion * (OmegaOmegaInfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Omega Omega Infinite Eternal Reality Dominion with power: %.2f"), DominionPower);
        // Apply omega omega infinite eternal reality dominion effects
    }
}

void UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::TranscendOmegaOmegaInfiniteEternalRecursion()
{
    if (bIsOmegaOmegaInfiniteEternalTranscendenceActive)
    {
        float RecursionPower = OmegaOmegaInfiniteEternalTranscendenceRecursion * (OmegaOmegaInfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Omega Omega Infinite Eternal Recursion with power: %.2f"), RecursionPower);
        // Apply omega omega infinite eternal transcendence recursion effects
    }
}

void UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::AccessOmegaOmegaInfiniteEternalInfiniteConsciousness()
{
    if (bIsOmegaOmegaInfiniteEternalTranscendenceActive)
    {
        float ConsciousnessPower = OmegaOmegaInfiniteEternalInfiniteConsciousness * (OmegaOmegaInfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Omega Omega Infinite Eternal Infinite Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply omega omega infinite eternal infinite consciousness effects
    }
}

void UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::EvolveConceptually()
{
    if (bIsOmegaOmegaInfiniteEternalTranscendenceActive)
    {
        float EvolutionPower = OmegaOmegaInfiniteEternalConceptualEvolution * (OmegaOmegaInfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually with power: %.2f"), EvolutionPower);
        // Apply omega omega infinite eternal conceptual evolution effects
    }
}

void UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::WieldOmegaOmegaInfiniteEternalTranscendenceAuthority()
{
    if (bIsOmegaOmegaInfiniteEternalTranscendenceActive)
    {
        float AuthorityPower = OmegaOmegaInfiniteEternalTranscendenceAuthority * (OmegaOmegaInfiniteEternalTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Omega Omega Infinite Eternal Transcendence Authority with power: %.2f"), AuthorityPower);
        // Apply omega omega infinite eternal transcendence authority effects
    }
}

bool UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::CanActivateOmegaOmegaInfiniteEternalTranscendence() const
{
    return OmegaOmegaInfiniteEternalTranscendenceLevel > 0;
}

void UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::UpdateOmegaOmegaInfiniteEternalTranscendenceStats()
{
    // Update omega omega infinite eternal transcendence properties based on level
    OmegaOmegaInfiniteEternalRealityDominion = OmegaOmegaInfiniteEternalTranscendenceLevel * 8.0f;
    OmegaOmegaInfiniteEternalTranscendenceRecursion = OmegaOmegaInfiniteEternalTranscendenceLevel * 7.8f;
    OmegaOmegaInfiniteEternalInfiniteConsciousness = OmegaOmegaInfiniteEternalTranscendenceLevel * 7.6f;
    OmegaOmegaInfiniteEternalConceptualEvolution = OmegaOmegaInfiniteEternalTranscendenceLevel * 7.7f;
    OmegaOmegaInfiniteEternalTranscendenceAuthority = OmegaOmegaInfiniteEternalTranscendenceLevel * 8.2f;
}

void UP13_TRNS_OMEGA_OMEGA_INFINITE_ETERNAL::OnOmegaOmegaInfiniteEternalTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsOmegaOmegaInfiniteEternalTranscendenceActive)
    {
        // Apply omega omega infinite eternal transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove omega omega infinite eternal transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Transcendence state changed to INACTIVE"));
    }
}
