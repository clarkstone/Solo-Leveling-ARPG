#include "P05_TRNS_BEYOND.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP05_TRNS_BEYOND::UP05_TRNS_BEYOND()
{
    PrimaryComponentTick.bCanEverTick = false;
    BeyondTranscendenceLevel = 0;
    MaxBeyondTranscendenceLevel = 100;
    bIsBeyondTranscendenceActive = false;
    BeyondTranscendencePowerCost = 30.0f;
    BeyondTranscendenceThreshold = 30.0f;
    
    // Initialize beyond transcendence properties
    BeyondTranscendencePower = 0.0f;
    BeyondRealityDominion = 0.0f;
    BeyondTranscendenceRecursion = 0.0f;
    BeyondInfiniteConsciousness = 0.0f;
    BeyondConceptualEvolution = 0.0f;
    BeyondTranscendenceAuthority = 0.0f;
}

void UP05_TRNS_BEYOND::BeginPlay()
{
    Super::BeginPlay();
    UpdateBeyondTranscendenceStats();
}

void UP05_TRNS_BEYOND::ActivateBeyondTranscendence()
{
    if (!bIsBeyondTranscendenceActive && CanActivateBeyondTranscendence())
    {
        bIsBeyondTranscendenceActive = true;
        OnBeyondTranscendenceActivated.Broadcast(BeyondTranscendenceLevel);
        OnBeyondTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Beyond Transcendence System Activated at Level: %d"), BeyondTranscendenceLevel);
    }
}

void UP05_TRNS_BEYOND::DeactivateBeyondTranscendence()
{
    if (bIsBeyondTranscendenceActive)
    {
        bIsBeyondTranscendenceActive = false;
        OnBeyondTranscendenceDeactivated.Broadcast(BeyondTranscendenceLevel);
        OnBeyondTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Beyond Transcendence System Deactivated."));
    }
}

void UP05_TRNS_BEYOND::SetBeyondTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxBeyondTranscendenceLevel)
    {
        int32 OldLevel = BeyondTranscendenceLevel;
        BeyondTranscendenceLevel = NewLevel;
        UpdateBeyondTranscendenceStats();
        OnBeyondTranscendenceLevelChanged.Broadcast(OldLevel, BeyondTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Beyond Transcendence Level set to: %d"), BeyondTranscendenceLevel);
        
        if (BeyondTranscendenceLevel >= MaxBeyondTranscendenceLevel)
        {
            OnBeyondTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Beyond Transcendence Max Level Reached!"));
        }
    }
}

void UP05_TRNS_BEYOND::UseBeyondTranscendencePower()
{
    if (bIsBeyondTranscendenceActive && BeyondTranscendenceLevel > 0)
    {
        OnBeyondTranscendencePowerUsed.Broadcast(BeyondTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Beyond Transcendence Power Used: %.2f"), BeyondTranscendencePowerCost);
    }
    else
    {
        OnBeyondTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Beyond Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UP05_TRNS_BEYOND::PerformBeyondTranscendenceAbility()
{
    if (bIsBeyondTranscendenceActive && BeyondTranscendenceLevel >= BeyondTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Beyond Transcendence Ability at Level %d!"), BeyondTranscendenceLevel);
        OnBeyondTranscendenceAbilityPerformed.Broadcast(BeyondTranscendenceLevel);
        UseBeyondTranscendencePower();
        
        // Perform beyond transcendence ability based on level
        switch (BeyondTranscendenceLevel / 20)
        {
            case 0:
                ExerciseBeyondRealityDominion();
                break;
            case 1:
                TranscendBeyondRecursion();
                break;
            case 2:
                AccessBeyondConsciousness();
                break;
            case 3:
                EvolveBeyondConceptually();
                break;
            case 4:
            case 5:
                WieldBeyondTranscendenceAuthority();
                break;
            default:
                WieldBeyondTranscendenceAuthority();
                break;
        }
    }
    }
    else if (BeyondTranscendenceLevel < BeyondTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Beyond Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), BeyondTranscendenceThreshold, BeyondTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Beyond Transcendence is not active, cannot perform ability."));
    }
}

bool UP05_TRNS_BEYOND::IsBeyondTranscendenceActive() const
{
    return bIsBeyondTranscendenceActive;
}

int32 UP05_TRNS_BEYOND::GetBeyondTranscendenceLevel() const
{
    return BeyondTranscendenceLevel;
}

float UP05_TRNS_BEYOND::GetBeyondTranscendencePowerCost() const
{
    return BeyondTranscendencePowerCost;
}

void UP05_TRNS_BEYOND::ExerciseBeyondRealityDominion()
{
    if (bIsBeyondTranscendenceActive)
    {
        float DominionPower = BeyondRealityDominion * (BeyondTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Beyond Reality Dominion with power: %.2f"), DominionPower);
        // Apply beyond reality dominion effects
    }
}

void UP05_TRNS_BEYOND::TranscendBeyondRecursion()
{
    if (bIsBeyondTranscendenceActive)
    {
        float RecursionPower = BeyondTranscendenceRecursion * (BeyondTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Beyond Recursion with power: %.2f"), RecursionPower);
        // Apply beyond transcendence recursion effects
    }
}

void UP05_TRNS_BEYOND::AccessBeyondConsciousness()
{
    if (bIsBeyondTranscendenceActive)
    {
        float ConsciousnessPower = BeyondInfiniteConsciousness * (BeyondTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Beyond Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply beyond consciousness effects
    }
}

void UP05_TRNS_BEYOND::EvolveBeyondConceptually()
{
    if (bIsBeyondTranscendenceActive)
    {
        float EvolutionPower = BeyondConceptualEvolution * (BeyondTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Beyond Conceptually with power: %.2f"), EvolutionPower);
        // Apply beyond conceptual evolution effects
    }
}

void UP05_TRNS_BEYOND::WieldBeyondTranscendenceAuthority()
{
    if (bIsBeyondTranscendenceActive)
    {
        float AuthorityPower = BeyondTranscendenceAuthority * (BeyondTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Beyond Transcendence Authority with power: %.2f"), AuthorityPower);
        // Apply beyond transcendence authority effects
    }
}

bool UP05_TRNS_BEYOND::CanActivateBeyondTranscendence() const
{
    return BeyondTranscendenceLevel > 0;
}

void UP05_TRNS_BEYOND::UpdateBeyondTranscendenceStats()
{
    // Update beyond transcendence properties based on level
    BeyondTranscendencePower = BeyondTranscendenceLevel * 4.5f;
    BeyondRealityDominion = BeyondTranscendenceLevel * 4.7f;
    BeyondTranscendenceRecursion = BeyondTranscendenceLevel * 4.6f;
    BeyondInfiniteConsciousness = BeyondTranscendenceLevel * 4.4f;
    BeyondConceptualEvolution = BeyondTranscendenceLevel * 4.5f;
    BeyondTranscendenceAuthority = BeyondTranscendenceLevel * 4.8f;
}

void UP05_TRNS_BEYOND::OnBeyondTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsBeyondTranscendenceActive)
    {
        // Apply beyond transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Beyond Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove beyond transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Beyond Transcendence state changed to INACTIVE"));
    }
}
