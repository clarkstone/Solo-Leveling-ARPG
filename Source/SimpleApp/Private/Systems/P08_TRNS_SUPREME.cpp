#include "P08_TRNS_SUPREME.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP08_TRNS_SUPREME::UP08_TRNS_SUPREME()
{
    PrimaryComponentTick.bCanEverTick = false;
    SupremeTranscendenceLevel = 0;
    MaxSupremeTranscendenceLevel = 100;
    bIsSupremeTranscendenceActive = false;
    SupremeTranscendencePowerCost = 45.0f;
    SupremeTranscendenceThreshold = 45.0f;
    
    // Initialize supreme transcendence properties
    SupremeRealityDominion = 0.0f;
    SupremeTranscendenceRecursion = 0.0f;
    SupremeInfiniteConsciousness = 0.0f;
    SupremeConceptualEvolution = 0.0f;
    SupremeTranscendenceAuthority = 0.0f;
}

void UP08_TRNS_SUPREME::BeginPlay()
{
    Super::BeginPlay();
    UpdateSupremeTranscendenceStats();
}

void UP08_TRNS_SUPREME::ActivateSupremeTranscendence()
{
    if (!bIsSupremeTranscendenceActive && CanActivateSupremeTranscendence())
    {
        bIsSupremeTranscendenceActive = true;
        OnSupremeTranscendenceActivated.Broadcast(SupremeTranscendenceLevel);
        OnSupremeTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Supreme Transcendence System Activated at Level: %d"), SupremeTranscendenceLevel);
    }
}

void UP08_TRNS_SUPREME::DeactivateSupremeTranscendence()
{
    if (bIsSupremeTranscendenceActive)
    {
        bIsSupremeTranscendenceActive = false;
        OnSupremeTranscendenceDeactivated.Broadcast(SupremeTranscendenceLevel);
        OnSupremeTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Supreme Transcendence System Deactivated."));
    }
}

void UP08_TRNS_SUPREME::SetSupremeTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxSupremeTranscendenceLevel)
    {
        int32 OldLevel = SupremeTranscendenceLevel;
        SupremeTranscendenceLevel = NewLevel;
        UpdateSupremeTranscendenceStats();
        OnSupremeTranscendenceLevelChanged.Broadcast(OldLevel, SupremeTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Supreme Transcendence Level set to: %d"), SupremeTranscendenceLevel);
        
        if (SupremeTranscendenceLevel >= MaxSupremeTranscendenceLevel)
        {
            OnSupremeTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Supreme Transcendence Max Level Reached!"));
        }
    }
}

void UP08_TRNS_SUPREME::UseSupremeTranscendencePower()
{
    if (bIsSupremeTranscendenceActive && SupremeTranscendenceLevel > 0)
    {
        OnSupremeTranscendencePowerUsed.Broadcast(SupremeTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Supreme Transcendence Power Used: %.2f"), SupremeTranscendencePowerCost);
    }
    else
    {
        OnSupremeTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Supreme Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UP08_TRNS_SUPREME::PerformSupremeTranscendenceAbility()
{
    if (bIsSupremeTranscendenceActive && SupremeTranscendenceLevel >= SupremeTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Supreme Transcendence Ability at Level %d!"), SupremeTranscendenceLevel);
        OnSupremeTranscendenceAbilityPerformed.Broadcast(SupremeTranscendenceLevel);
        UseSupremeTranscendencePower();
        
        // Perform supreme transcendence ability based on level
        switch (SupremeTranscendenceLevel / 20)
        {
            case 0:
                ExerciseSupremeRealityDominion();
                break;
            case 1:
                TranscendSupremeRecursion();
                break;
            case 2:
                AccessSupremeInfiniteConsciousness();
                break;
            case 3:
                EvolveConceptually();
                break;
            case 4:
            case 5:
                WieldSupremeTranscendenceAuthority();
                break;
            default:
                WieldSupremeTranscendenceAuthority();
                break;
        }
    }
    }
    else if (SupremeTranscendenceLevel < SupremeTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Supreme Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), SupremeTranscendenceThreshold, SupremeTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Supreme Transcendence is not active, cannot perform ability."));
    }
}

bool UP08_TRNS_SUPREME::IsSupremeTranscendenceActive() const
{
    return bIsSupremeTranscendenceActive;
}

int32 UP08_TRNS_SUPREME::GetSupremeTranscendenceLevel() const
{
    return SupremeTranscendenceLevel;
}

float UP08_TRNS_SUPREME::GetSupremeTranscendencePowerCost() const
{
    return SupremeTranscendencePowerCost;
}

void UP08_TRNS_SUPREME::ExerciseSupremeRealityDominion()
{
    if (bIsSupremeTranscendenceActive)
    {
        float DominionPower = SupremeRealityDominion * (SupremeTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Supreme Reality Dominion with power: %.2f"), DominionPower);
        // Apply supreme reality dominion effects
    }
}

void UP08_TRNS_SUPREME::TranscendSupremeRecursion()
{
    if (bIsSupremeTranscendenceActive)
    {
        float RecursionPower = SupremeTranscendenceRecursion * (SupremeTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Supreme Recursion with power: %.2f"), RecursionPower);
        // Apply transcendence recursion effects
    }
}

void UP08_TRNS_SUPREME::AccessSupremeInfiniteConsciousness()
{
    if (bIsSupremeTranscendenceActive)
    {
        float ConsciousnessPower = SupremeInfiniteConsciousness * (SupremeTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Supreme Infinite Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply infinite consciousness effects
    }
}

void UP08_TRNS_SUPREME::EvolveConceptually()
{
    if (bIsSupremeTranscendenceActive)
    {
        float EvolutionPower = SupremeConceptualEvolution * (SupremeTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually with power: %.2f"), EvolutionPower);
        // Apply conceptual evolution effects
    }
}

void UP08_TRNS_SUPREME::WieldSupremeTranscendenceAuthority()
{
    if (bIsSupremeTranscendenceActive)
    {
        float AuthorityPower = SupremeTranscendenceAuthority * (SupremeTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Supreme Transcendence Authority with power: %.2f"), AuthorityPower);
        // Apply supreme transcendence authority effects
    }
}

bool UP08_TRNS_SUPREME::CanActivateSupremeTranscendence() const
{
    return SupremeTranscendenceLevel > 0;
}

void UP08_TRNS_SUPREME::UpdateSupremeTranscendenceStats()
{
    // Update supreme transcendence properties based on level
    SupremeRealityDominion = SupremeTranscendenceLevel * 5.5f;
    SupremeTranscendenceRecursion = SupremeTranscendenceLevel * 5.3f;
    SupremeInfiniteConsciousness = SupremeTranscendenceLevel * 5.1f;
    SupremeConceptualEvolution = SupremeTranscendenceLevel * 5.2f;
    SupremeTranscendenceAuthority = SupremeTranscendenceLevel * 5.4f;
}

void UP08_TRNS_SUPREME::OnSupremeTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsSupremeTranscendenceActive)
    {
        // Apply supreme transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Supreme Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove supreme transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Supreme Transcendence state changed to INACTIVE"));
    }
}
