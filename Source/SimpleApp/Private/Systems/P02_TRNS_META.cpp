#include "P02_TRNS_META.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP02_TRNS_META::UP02_TRNS_META()
{
    PrimaryComponentTick.bCanEverTick = false;
    MetaTranscendenceLevel = 0;
    MaxMetaTranscendenceLevel = 100;
    bIsMetaTranscendenceActive = false;
    MetaTranscendencePowerCost = 15.0f;
    MetaTranscendenceThreshold = 15.0f;
    
    // Initialize meta transcendence properties
    MetaRealityDominion = 0.0f;
    TranscendenceRecursion = 0.0f;
    MetaInfiniteConsciousness = 0.0f;
    ConceptualEvolution = 0.0f;
    MetaAuthority = 0.0f;
}

void UP02_TRNS_META::BeginPlay()
{
    Super::BeginPlay();
    UpdateMetaTranscendenceStats();
}

void UP02_TRNS_META::ActivateMetaTranscendence()
{
    if (!bIsMetaTranscendenceActive && CanActivateMetaTranscendence())
    {
        bIsMetaTranscendenceActive = true;
        OnMetaTranscendenceActivated.Broadcast(MetaTranscendenceLevel);
        OnMetaTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Meta Transcendence System Activated at Level: %d"), MetaTranscendenceLevel);
    }
}

void UP02_TRNS_META::DeactivateMetaTranscendence()
{
    if (bIsMetaTranscendenceActive)
    {
        bIsMetaTranscendenceActive = false;
        OnMetaTranscendenceDeactivated.Broadcast(MetaTranscendenceLevel);
        OnMetaTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Meta Transcendence System Deactivated."));
    }
}

void UP02_TRNS_META::SetMetaTranscendenceLevel(int32 NewLevel)
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
            UE_LOG(LogTemp, TEXT("Meta Transcendence Max Level Reached!"));
        }
    }
}

void UP02_TRNS_META::UseMetaTranscendencePower()
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

void UP02_TRNS_META::PerformMetaTranscendenceAbility()
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
                WieldMetaAuthority();
                break;
            default:
                WieldMetaAuthority();
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

bool UP02_TRNS_META::IsMetaTranscendenceActive() const
{
    return bIsMetaTranscendenceActive;
}

int32 UP02_TRNS_META::GetMetaTranscendenceLevel() const
{
    return MetaTranscendenceLevel;
}

float UP02_TRNS_META::GetMetaTranscendencePowerCost() const
{
    return MetaTranscendencePowerCost;
}

void UP02_TRNS_META::ExerciseMetaRealityDominion()
{
    if (bIsMetaTranscendenceActive)
    {
        float DominionPower = MetaRealityDominion * (MetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, TEXT("Exercising Meta Reality Dominion with power: %.2f"), DominionPower);
        // Apply meta reality dominion effects
    }
}

void UP02_TRNS_META::TranscendRecursion()
{
    if (bIsMetaTranscendenceActive)
    {
        float RecursionPower = TranscendenceRecursion * (MetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Recursion with power: %.2f"), RecursionPower);
        // Apply transcendence recursion effects
    }
}

void UP02_TRNS_META::AccessMetaInfiniteConsciousness()
{
    if (bIsMetaTranscendenceActive)
    {
        float ConsciousnessPower = MetaInfiniteConsciousness * (MetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Meta-Infinite Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply meta-infinite consciousness effects
    }
}

void UP02_TRNS_META::EvolveConceptually()
{
    if (bIsMetaTranscendenceActive)
    {
        float EvolutionPower = ConceptualEvolution * (MetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually with power: %.2f"), EvolutionPower);
        // Apply conceptual evolution effects
    }
}

void UP02_TRNS_META::WieldMetaAuthority()
{
    if (bIsMetaTranscendenceActive)
    {
        float AuthorityPower = MetaAuthority * (MetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, TEXT("Wielding Meta Authority with power: %.2f"), AuthorityPower);
        // Apply meta authority effects
    }
}

bool UP02_TRNS_META::CanActivateMetaTranscendence() const
{
    return MetaTranscendenceLevel > 0;
}

void UP02_TRNS_META::UpdateMetaTranscendenceStats()
{
    // Update meta transcendence properties based on level
    MetaRealityDominion = MetaTranscendenceLevel * 2.5f;
    TranscendenceRecursion = MetaTranscendenceLevel * 2.3f;
    MetaInfiniteConsciousness = MetaTranscendenceLevel * 2.1f;
    ConceptualEvolution = MetaTranscendenceLevel * 2.2f;
    MetaAuthority = MetaTranscendenceLevel * 2.4f;
}

void UP02_TRNS_META::OnMetaTranscendenceStateChanged()
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
