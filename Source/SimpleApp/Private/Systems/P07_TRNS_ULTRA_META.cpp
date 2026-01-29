#include "P07_TRNS_ULTRA_META.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP07_TRNS_ULTRA_META::UP07_TRNS_ULTRA_META()
{
    PrimaryComponentTick.bCanEverTick = false;
    UltraMetaTranscendenceLevel = 0;
    MaxUltraMetaTranscendenceLevel = 100;
    bIsUltraMetaTranscendenceActive = false;
    UltraMetaTranscendencePowerCost = 45.0f;
    UltraMetaTranscendenceThreshold = 45.0f;
    
    // Initialize ultra meta transcendence properties
    UltraMetaRealityDominion = 0.0f;
    UltraTranscendenceRecursion = 0.0f;
    UltraMetaInfiniteConsciousness = 0.0f;
    UltraConceptualEvolution = 0.0f;
    UltraMetaTranscendenceAuthority = 0.0f;
}

void UP07_TRNS_ULTRA_META::BeginPlay()
{
    Super::BeginPlay();
    UpdateUltraMetaTranscendenceStats();
}

void UP07_TRNS_ULTRA_META::ActivateUltraMetaTranscendence()
{
    if (!bIsUltraMetaTranscendenceActive && CanActivateUltraMetaTranscendence())
    {
        bIsUltraMetaTranscendenceActive = true;
        OnUltraMetaTranscendenceActivated.Broadcast(UltraMetaTranscendenceLevel);
        OnUltraMetaTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Ultra Meta Transcendence System Activated at Level: %d"), UltraMetaTranscendenceLevel);
    }
}

void UP07_TRNS_ULTRA_META::DeactivateUltraMetaTranscendence()
{
    if (bIsUltraMetaTranscendenceActive)
    {
        bIsUltraMetaTranscendenceActive = false;
        OnUltraMetaTranscendenceDeactivated.Broadcast(UltraMetaTranscendenceLevel);
        OnUltraMetaTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Ultra Meta Transcendence System Deactivated."));
    }
}

void UP07_TRNS_ULTRA_META::SetUltraMetaTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxUltraMetaTranscendenceLevel)
    {
        int32 OldLevel = UltraMetaTranscendenceLevel;
        UltraMetaTranscendenceLevel = NewLevel;
        UpdateUltraMetaTranscendenceStats();
        OnUltraMetaTranscendenceLevelChanged.Broadcast(OldLevel, UltraMetaTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Ultra Meta Transcendence Level set to: %d"), UltraMetaTranscendenceLevel);
        
        if (UltraMetaTranscendenceLevel >= MaxUltraMetaTranscendenceLevel)
        {
            OnUltraMetaTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Ultra Meta Transcendence Max Level Reached!"));
        }
    }
}

void UP07_TRNS_ULTRA_META::UseUltraMetaTranscendencePower()
{
    if (bIsUltraMetaTranscendenceActive && UltraMetaTranscendenceLevel > 0)
    {
        OnUltraMetaTranscendencePowerUsed.Broadcast(UltraMetaTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Ultra Meta Transcendence Power Used: %.2f"), UltraMetaTranscendencePowerCost);
    }
    else
    {
        OnUltraMetaTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Ultra Meta Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UP07_TRNS_ULTRA_META::PerformUltraMetaTranscendenceAbility()
{
    if (bIsUltraMetaTranscendenceActive && UltraMetaTranscendenceLevel >= UltraMetaTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Ultra Meta Transcendence Ability at Level %d!"), UltraMetaTranscendenceLevel);
        OnUltraMetaTranscendenceAbilityPerformed.Broadcast(UltraMetaTranscendenceLevel);
        UseUltraMetaTranscendencePower();
        
        // Perform ultra meta transcendence ability based on level
        switch (UltraMetaTranscendenceLevel / 20)
        {
            case 0:
                ExerciseUltraMetaRealityDominion();
                break;
            case 1:
                TranscendUltraMetaRecursion();
                break;
            case 2:
                AccessUltraMetaInfiniteConsciousness();
                break;
            case 3:
                EvolveUltraMetaConceptually();
                break;
            case 4:
            case 5:
                WieldUltraMetaTranscendenceAuthority();
                break;
            default:
                WieldUltraMetaTranscendenceAuthority();
                break;
        }
    }
    }
    else if (UltraMetaTranscendenceLevel < UltraMetaTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ultra Meta Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), UltraMetaTranscendenceThreshold, UltraMetaTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Ultra Meta Transcendence is not active, cannot perform ability."));
    }
}

bool UP07_TRNS_ULTRA_META::IsUltraMetaTranscendenceActive() const
{
    return bIsUltraMetaTranscendenceActive;
}

int32 UP07_TRNS_ULTRA_META::GetUltraMetaTranscendenceLevel() const
{
    return UltraMetaTranscendenceLevel;
}

float UP07_TRNS_ULTRA_META::GetUltraMetaTranscendencePowerCost() const
{
    return UltraMetaTranscendencePowerCost;
}

void UP07_TRNS_ULTRA_META::ExerciseUltraMetaRealityDominion()
{
    if (bIsUltraMetaTranscendenceActive)
    {
        float DominionPower = UltraMetaRealityDominion * (UltraMetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Ultra Meta Reality Dominion with power: %.2f"), DominionPower);
        // Apply ultra meta reality dominion effects
    }
}

void UP07_TRNS_ULTRA_META::TranscendUltraMetaRecursion()
{
    if (bIsUltraMetaTranscendenceActive)
    {
        float RecursionPower = UltraTranscendenceRecursion * (UltraMetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Ultra Meta Recursion with power: %.2f"), RecursionPower);
        // Apply ultra meta transcendence recursion effects
    }
}

void UP07_TRNS_ULTRA_META::AccessUltraMetaInfiniteConsciousness()
{
    if (bIsUltraMetaTranscendenceActive)
    {
        float ConsciousnessPower = UltraMetaInfiniteConsciousness * (UltraMetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Ultra Meta Infinite Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply ultra meta infinite consciousness effects
    }
}

void UP07_TRNS_ULTRA_META::EvolveUltraMetaConceptually()
{
    if (bIsUltraMetaTranscendenceActive)
    {
        float EvolutionPower = UltraConceptualEvolution * (UltraMetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Ultra Meta Conceptually with power: %.2f"), EvolutionPower);
        // Apply ultra meta conceptual evolution effects
    }
}

void UP07_TRNS_ULTRA_META::WieldUltraMetaTranscendenceAuthority()
{
    if (bIsUltraMetaTranscendenceActive)
    {
        float AuthorityPower = UltraMetaTranscendenceAuthority * (UltraMetaTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Ultra Meta Transcendence Authority with power: %.2f"), AuthorityPower);
        // Apply ultra meta transcendence authority effects
    }
}

bool UP07_TRNS_ULTRA_META::CanActivateUltraMetaTranscendence() const
{
    return UltraMetaTranscendenceLevel > 0;
}

void UP07_TRNS_ULTRA_META::UpdateUltraMetaTranscendenceStats()
{
    // Update ultra meta transcendence properties based on level
    UltraMetaRealityDominion = UltraMetaTranscendenceLevel * 5.5f;
    UltraTranscendenceRecursion = UltraMetaTranscendenceLevel * 5.3f;
    UltraMetaInfiniteConsciousness = UltraMetaTranscendenceLevel * 5.1f;
    UltraConceptualEvolution = UltraMetaTranscendenceLevel * 5.2f;
    UltraMetaTranscendenceAuthority = UltraMetaTranscendenceLevel * 5.7f;
}

void UP07_TRNS_ULTRA_META::OnUltraMetaTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsUltraMetaTranscendenceActive)
    {
        // Apply ultra meta transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Ultra Meta Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove ultra meta transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Ultra Meta Transcendence state changed to INACTIVE"));
    }
}
