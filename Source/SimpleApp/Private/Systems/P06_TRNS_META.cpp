#include "P06_TRNS_META.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP06_TRNS_META::UP06_TRNS_META()
{
    PrimaryComponentTick.bCanEverTick = false;
    MetaTranscendenceLevel = 0;
    MaxMetaTranscendenceLevel = 100;
    bIsMetaTranscendenceActive = false;
    MetaTranscendencePowerCost = 35.0f;
    MetaTranscendenceThreshold = 35.0f;
    
    // Initialize meta transcendence properties
    MetaRealityDominion = 0.0f;
    TranscendenceRecursion = 0.0f;
    MetaInfiniteConsciousness = 0.0f;
    ConceptualEvolution = 0.0f;
    MetaTranscendenceAuthority = 0.0f;
}

void UP06_TRNS_META::BeginPlay()
{
    Super::BeginPlay();
    UpdateMetaTranscendenceStats();
}

void UP06_TRNS_META::ActivateMetaTranscendence()
{
    if (!bIsMetaTranscendenceActive && CanActivateMetaTranscendence())
    {
        bIsMetaTranscendenceActive = true;
        OnMetaTranscendenceActivated.Broadcast(MetaTranscendenceLevel);
        OnMetaTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Meta Transcendence System Activated at Level: %d"), MetaTranscendenceLevel);
    }
}

void UP06_TRNS_META::DeactivateMetaTranscendence()
{
    if (bIsMetaTranscendenceActive)
    {
        bIsMetaTranscendenceActive = false;
        OnMetaTranscendenceDeactivated.Broadcast(MetaTranscendenceLevel);
        OnMetaTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Meta Transcendence System Deactivated."));
    }
}

void UP06_TRNS_META::SetMetaTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxMetaTranscendenceLevel)
    {
        int32 OldLevel = MetaTranscendenceLevel;
        MetaTranscendenceLevel = NewLevel;
        UpdateMetaTranscendenceStats();
        OnMetaTranscendenceLevelChanged.Broadcast(OldLevel, MetaTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Meta Transcendence Level set to: %d"), MetaTranscendenceLevel);
        
        if (MetaTranscendenceLevel >= MaxMetaTranscendenceLevel)
        {
            OnMetaTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Meta Transcendence Max Level Reached!"));
        }
    }
}

void UP06_TRNS_META::UseMetaTranscendencePower()
{
    if (bIsMetaTranscendenceActive && MetaTranscendenceLevel > 0)
    {
        OnMetaTranscendencePowerUsed.Broadcast(MetaTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Meta Transcendence Power Used: %.2f"), MetaTranscendencePowerCost);
    }
    else
    {
        OnMetaTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Meta Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UP06_TRNS_META::PerformMetaTranscendenceAbility()
{
    if (bIsMetaTranscendenceActive && MetaTranscendenceLevel >= MetaTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Meta Transcendence Ability at Level %d!"), MetaTranscendenceLevel);
        OnMetaTranscendenceAbilityPerformed.Broadcast(MetaTranscendenceLevel);
        UseMetaTranscendencePower();
        
        // Perform meta transcendence ability based on level
        switch (MetaTranscendenceLevel / 20)
        {
            case 0:
                ExerciseMetaRealityDominion();
                break;
            case 1:
                TranscendRecursion();
                break;
            case 2:
                AccessMetaInfiniteConsciousness();
                break;
            case 3:
                EvolveConceptually();
                break;
            case 4:
            case 5:
                WieldMetaTranscendenceAuthority();
                break;
            default:
                WieldMetaTranscendenceAuthority();
                break;
        }
    }
    }
    else if (MetaTranscendenceLevel < MetaTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Meta Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), MetaTranscendenceThreshold, MetaTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Meta Transcendence is not active, cannot perform ability."));
    }
}

bool UP06_TRNS_META::IsMetaTranscendenceActive() const
{
    return bIsMetaTranscendenceActive;
}

int32 UP06_TRNS_META::GetMetaTranscendenceLevel() const
{
    return MetaTranscendenceLevel;
}

float UP06_TRNS_META::GetMetaTranscendencePowerCost() const
{
    return MetaTranscendencePowerCost;
}

void UP06_TRNS_META::ExerciseMetaRealityDominion()
{
    if (bIsMetaTranscendenceActive)
    {
        float DominionPower = MetaRealityDominion * (MetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Meta Reality Dominion with power: %.2f"), DominionPower);
        // Apply meta reality dominion effects
    }
}

void UP06_TRNS_META::TranscendRecursion()
{
    if (bIsMetaTranscendenceActive)
    {
        float RecursionPower = TranscendenceRecursion * (MetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Recursion with power: %.2f"), RecursionPower);
        // Apply transcendence recursion effects
    }
}

void UP06_TRNS_META::AccessMetaInfiniteConsciousness()
{
    if (bIsMetaTranscendenceActive)
    {
        float ConsciousnessPower = MetaInfiniteConsciousness * (MetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Meta-Infinite Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply meta-infinite consciousness effects
    }
}

void UP06_TRNS_META::EvolveConceptually()
{
    if (bIsMetaTranscendenceActive)
    {
        float EvolutionPower = ConceptualEvolution * (MetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually with power: %.2f"), EvolutionPower);
        // Apply conceptual evolution effects
    }
}

void UP06_TRNS_META::WieldMetaTranscendenceAuthority()
{
    if (bIsMetaTranscendenceActive)
    {
        float AuthorityPower = MetaTranscendenceAuthority * (MetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Meta Transcendence Authority with power: %.2f"), AuthorityPower);
        // Apply meta transcendence authority effects
    }
}

bool UP06_TRNS_META::CanActivateMetaTranscendence() const
{
    return MetaTranscendenceLevel > 0;
}

void UP06_TRNS_META::UpdateMetaTranscendenceStats()
{
    // Update meta transcendence properties based on level
    MetaRealityDominion = MetaTranscendenceLevel * 4.0f;
    TranscendenceRecursion = MetaTranscendenceLevel * 3.8f;
    MetaInfiniteConsciousness = MetaTranscendenceLevel * 3.7f;
    ConceptualEvolution = MetaTranscendenceLevel * 3.9f;
    MetaTranscendenceAuthority = MetaTranscendenceLevel * 4.2f;
}

void UP06_TRNS_META::OnMetaTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsMetaTranscendenceActive)
    {
        // Apply meta transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Meta Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove meta transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Meta Transcendence state changed to INACTIVE"));
    }
}
