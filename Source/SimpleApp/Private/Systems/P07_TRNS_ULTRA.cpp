#include "P07_TRNS_ULTRA.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP07_TRNS_ULTRA::UP07_TRNS_ULTRA()
{
    PrimaryComponentTick.bCanEverTick = false;
    UltraTranscendenceLevel = 0;
    MaxUltraTranscendenceLevel = 100;
    bIsUltraTranscendenceActive = false;
    UltraTranscendencePowerCost = 40.0f;
    UltraTranscendenceThreshold = 40.0f;
    
    // Initialize ultra transcendence properties
    UltraTranscendencePower = 0.0f;
    UltraRealityDominion = 0.0f;
    UltraTranscendenceRecursion = 0.0f;
    UltraInfiniteConsciousness = 0.0f;
    UltraConceptualEvolution = 0.0f;
    UltraTranscendenceAuthority = 0.0f;
}

void UP07_TRNS_ULTRA::BeginPlay()
{
    Super::BeginPlay();
    UpdateUltraTranscendenceStats();
}

void UP07_TRNS_ULTRA::ActivateUltraTranscendence()
{
    if (!bIsUltraTranscendenceActive && CanActivateUltraTranscendence())
    {
        bIsUltraTranscendenceActive = true;
        OnUltraTranscendenceActivated.Broadcast(UltraTranscendenceLevel);
        OnUltraTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Ultra Transcendence System Activated at Level: %d"), UltraTranscendenceLevel);
    }
}

void UP07_TRNS_ULTRA::DeactivateUltraTranscendence()
{
    if (bIsUltraTranscendenceActive)
    {
        bIsUltraTranscendenceActive = false;
        OnUltraTranscendenceDeactivated.Broadcast(UltraTranscendenceLevel);
        OnUltraTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Ultra Transcendence System Deactivated."));
    }
}

void UP07_TRNS_ULTRA::SetUltraTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxUltraTranscendenceLevel)
    {
        int32 OldLevel = UltraTranscendenceLevel;
        UltraTranscendenceLevel = NewLevel;
        UpdateUltraTranscendenceStats();
        OnUltraTranscendenceLevelChanged.Broadcast(OldLevel, UltraTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Ultra Transcendence Level set to: %d"), UltraTranscendenceLevel);
        
        if (UltraTranscendenceLevel >= MaxUltraTranscendenceLevel)
        {
            OnUltraTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Ultra Transcendence Max Level Reached!"));
        }
    }
}

void UP07_TRNS_ULTRA::UseUltraTranscendencePower()
{
    if (bIsUltraTranscendenceActive && UltraTranscendenceLevel > 0)
    {
        OnUltraTranscendencePowerUsed.Broadcast(UltraTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Ultra Transcendence Power Used: %.2f"), UltraTranscendencePowerCost);
    }
    else
    {
        OnUltraTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Ultra Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UP07_TRNS_ULTRA::PerformUltraTranscendenceAbility()
{
    if (bIsUltraTranscendenceActive && UltraTranscendenceLevel >= UltraTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Ultra Transcendence Ability at Level %d!"), UltraTranscendenceLevel);
        OnUltraTranscendenceAbilityPerformed.Broadcast(UltraTranscendenceLevel);
        UseUltraTranscendencePower();
        
        // Perform ultra transcendence ability based on level
        switch (UltraTranscendenceLevel / 20)
        {
            case 0:
                ExerciseUltraRealityDominion();
                break;
            case 1:
                TranscendUltraRecursion();
                break;
            case 2:
                AccessUltraInfiniteConsciousness();
                break;
            case 3:
                EvolveUltraConceptually();
                break;
            case 4:
            case 5:
                WieldUltraTranscendenceAuthority();
                break;
            default:
                WieldUltraTranscendenceAuthority();
                break;
        }
    }
    }
    else if (UltraTranscendenceLevel < UltraTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ultra Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), UltraTranscendenceThreshold, UltraTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Ultra Transcendence is not active, cannot perform ability."));
    }
}

bool UP07_TRNS_ULTRA::IsUltraTranscendenceActive() const
{
    return bIsUltraTranscendenceActive;
}

int32 UP07_TRNS_ULTRA::GetUltraTranscendenceLevel() const
{
    return UltraTranscendenceLevel;
}

float UP07_TRNS_ULTRA::GetUltraTranscendencePowerCost() const
{
    return UltraTranscendencePowerCost;
}

void UP07_TRNS_ULTRA::ExerciseUltraRealityDominion()
{
    if (bIsUltraTranscendenceActive)
    {
        float DominionPower = UltraRealityDominion * (UltraTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Ultra Reality Dominion with power: %.2f"), DominionPower);
        // Apply ultra reality dominion effects
    }
}

void UP07_TRNS_ULTRA::TranscendUltraRecursion()
{
    if (bIsUltraTranscendenceActive)
    {
        float RecursionPower = UltraTranscendenceRecursion * (UltraTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Ultra Recursion with power: %.2f"), RecursionPower);
        // Apply ultra transcendence recursion effects
    }
}

void UP07_TRNS_ULTRA::AccessUltraInfiniteConsciousness()
{
    if (bIsUltraTranscendenceActive)
    {
        float ConsciousnessPower = UltraInfiniteConsciousness * (UltraTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Ultra Infinite Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply ultra infinite consciousness effects
    }
}

void UP07_TRNS_ULTRA::EvolveUltraConceptually()
{
    if (bIsUltraTranscendenceActive)
    {
        float EvolutionPower = UltraConceptualEvolution * (UltraTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Ultra Conceptually with power: %.2f"), EvolutionPower);
        // Apply ultra conceptual evolution effects
    }
}

void UP07_TRNS_ULTRA::WieldUltraTranscendenceAuthority()
{
    if (bIsUltraTranscendenceActive)
    {
        float AuthorityPower = UltraTranscendenceAuthority * (UltraTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Ultra Transcendence Authority with power: %.2f"), AuthorityPower);
        // Apply ultra transcendence authority effects
    }
}

bool UP07_TRNS_ULTRA::CanActivateUltraTranscendence() const
{
    return UltraTranscendenceLevel > 0;
}

void UP07_TRNS_ULTRA::UpdateUltraTranscendenceStats()
{
    // Update ultra transcendence properties based on level
    UltraTranscendencePower = UltraTranscendenceLevel * 5.0f;
    UltraRealityDominion = UltraTranscendenceLevel * 5.2f;
    UltraTranscendenceRecursion = UltraTranscendenceLevel * 5.1f;
    UltraInfiniteConsciousness = UltraTranscendenceLevel * 4.9f;
    UltraConceptualEvolution = UltraTranscendenceLevel * 5.0f;
    UltraTranscendenceAuthority = UltraTranscendenceLevel * 5.3f;
}

void UP07_TRNS_ULTRA::OnUltraTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsUltraTranscendenceActive)
    {
        // Apply ultra transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Ultra Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove ultra transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Ultra Transcendence state changed to INACTIVE"));
    }
}
