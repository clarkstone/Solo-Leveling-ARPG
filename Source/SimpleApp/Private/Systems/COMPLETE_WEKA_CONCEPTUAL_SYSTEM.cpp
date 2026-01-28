#include "COMPLETE_WEKA_CONCEPTUAL_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    WekaConceptualLevel = 0;
    MaxWekaConceptualLevel = 100;
    bIsWekaConceptualActive = false;
    WekaConceptualPowerCost = 35.0f;
    WekaConceptualThreshold = 90.0f;
    
    // Initialize weka-conceptual properties
    WekascaleConceptMastery = 0.0f;
    SupremeUltraHyperMetaIdeaGeneration = 0.0f;
    ConceptualSupremeUltraHyperEvolution = 0.0f;
    AbstractSupremeUltraHyperRealityCreation = 0.0f;
    UltimateConceptualSupremeUltimacy = 0.0f;
}

void UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateWekaConceptualStats();
}

void UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::ActivateWekaConceptual()
{
    if (!bIsWekaConceptualActive && CanActivateWekaConceptual())
    {
        bIsWekaConceptualActive = true;
        OnWekaConceptualActivated.Broadcast(WekaConceptualLevel);
        OnWekaConceptualStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Weka-Conceptual System Activated at Level: %d"), WekaConceptualLevel);
    }
}

void UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::DeactivateWekaConceptual()
{
    if (bIsWekaConceptualActive)
    {
        bIsWekaConceptualActive = false;
        OnWekaConceptualDeactivated.Broadcast(WekaConceptualLevel);
        OnWekaConceptualStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Weka-Conceptual System Deactivated."));
    }
}

void UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::SetWekaConceptualLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxWekaConceptualLevel)
    {
        int32 OldLevel = WekaConceptualLevel;
        WekaConceptualLevel = NewLevel;
        UpdateWekaConceptualStats();
        OnWekaConceptualLevelChanged.Broadcast(OldLevel, WekaConceptualLevel);
        UE_LOG(LogTemp, Warning, TEXT("Weka-Conceptual Level set to: %d"), WekaConceptualLevel);
        
        if (WekaConceptualLevel >= MaxWekaConceptualLevel)
        {
            OnWekaConceptualMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Weka-Conceptual Max Level Reached!"));
        }
    }
}

void UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::UseWekaConceptualPower()
{
    if (bIsWekaConceptualActive && WekaConceptualLevel > 0)
    {
        OnWekaConceptualPowerUsed.Broadcast(WekaConceptualPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Weka-Conceptual Power Used: %.2f"), WekaConceptualPowerCost);
    }
    else
    {
        OnWekaConceptualPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Weka-Conceptual Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::PerformWekaConceptualAbility()
{
    if (bIsWekaConceptualActive && WekaConceptualLevel >= WekaConceptualThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Weka-Conceptual Ability at Level %d!"), WekaConceptualLevel);
        OnWekaConceptualAbilityPerformed.Broadcast(WekaConceptualLevel);
        UseWekaConceptualPower();
        
        // Perform weka-conceptual ability based on level
        switch (WekaConceptualLevel / 20)
        {
            case 0:
                MasterWekascaleConcepts();
                break;
            case 1:
                GenerateSupremeUltraHyperMetaIdeas();
                break;
            case 2:
                EvolveConceptuallySupremeUltraHyper();
                break;
            case 3:
                CreateAbstractSupremeUltraHyperReality();
                break;
            case 4:
            case 5:
                ExerciseUltimateConceptualSupremeUltimacy();
                break;
            default:
                ExerciseUltimateConceptualSupremeUltimacy();
                break;
        }
    }
    else if (WekaConceptualLevel < WekaConceptualThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Weka-Conceptual Level too low to perform ability. Required: %.0f, Current: %d"), WekaConceptualThreshold, WekaConceptualLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Weka-Conceptual is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::IsWekaConceptualActive() const
{
    return bIsWekaConceptualActive;
}

int32 UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::GetWekaConceptualLevel() const
{
    return WekaConceptualLevel;
}

float UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::GetWekaConceptualPowerCost() const
{
    return WekaConceptualPowerCost;
}

void UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::MasterWekascaleConcepts()
{
    if (bIsWekaConceptualActive)
    {
        float ConceptMastery = WekascaleConceptMastery * (WekaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Wekascale Concepts with power: %.2f"), ConceptMastery);
        // Apply wekascale concept mastery effects
    }
}

void UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::GenerateSupremeUltraHyperMetaIdeas()
{
    if (bIsWekaConceptualActive)
    {
        float IdeaGeneration = SupremeUltraHyperMetaIdeaGeneration * (WekaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Generating Supreme-Ultra-Hyper-Meta Ideas with power: %.2f"), IdeaGeneration);
        // Apply supreme-ultra-hyper-meta idea generation effects
    }
}

void UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::EvolveConceptuallySupremeUltraHyper()
{
    if (bIsWekaConceptualActive)
    {
        float EvolutionPower = ConceptualSupremeUltraHyperEvolution * (WekaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually Supreme-Ultra-Hyper with power: %.2f"), EvolutionPower);
        // Apply conceptual supreme-ultra-hyper evolution effects
    }
}

void UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::CreateAbstractSupremeUltraHyperReality()
{
    if (bIsWekaConceptualActive)
    {
        float RealityCreation = AbstractSupremeUltraHyperRealityCreation * (WekaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Creating Abstract Supreme-Ultra-Hyper Reality with power: %.2f"), RealityCreation);
        // Apply abstract supreme-ultra-hyper reality creation effects
    }
}

void UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::ExerciseUltimateConceptualSupremeUltimacy()
{
    if (bIsWekaConceptualActive)
    {
        float ConceptualUltimacy = UltimateConceptualSupremeUltimacy * (WekaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Ultimate Conceptual Supreme Ultimacy with power: %.2f"), ConceptualUltimacy);
        // Apply ultimate conceptual supreme ultimacy effects
    }
}

bool UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::CanActivateWekaConceptual() const
{
    return WekaConceptualLevel > 0;
}

void UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::UpdateWekaConceptualStats()
{
    // Update weka-conceptual properties based on level
    WekascaleConceptMastery = WekaConceptualLevel * 10.5f;
    SupremeUltraHyperMetaIdeaGeneration = WekaConceptualLevel * 10.3f;
    ConceptualSupremeUltraHyperEvolution = WekaConceptualLevel * 10.2f;
    AbstractSupremeUltraHyperRealityCreation = WekaConceptualLevel * 10.1f;
    UltimateConceptualSupremeUltimacy = WekaConceptualLevel * 11.0f;
}

void UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM::OnWekaConceptualStateChanged()
{
    // Handle state change effects
    if (bIsWekaConceptualActive)
    {
        // Apply weka-conceptual activation effects
        UE_LOG(LogTemp, Warning, TEXT("Weka-Conceptual state changed to ACTIVE"));
    }
    else
    {
        // Remove weka-conceptual effects
        UE_LOG(LogTemp, Warning, TEXT("Weka-Conceptual state changed to INACTIVE"));
    }
}
