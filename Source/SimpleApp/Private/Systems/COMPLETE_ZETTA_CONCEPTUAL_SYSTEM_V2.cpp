#include "COMPLETE_ZETTA_CONCEPTUAL_SYSTEM_V2.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    ZettaConceptualLevel = 0;
    MaxZettaConceptualLevel = 100;
    bIsZettaConceptualActive = false;
    ZettaConceptualPowerCost = 50.0f;
    ZettaConceptualThreshold = 100.0f;
    
    // Initialize zetta-conceptual properties
    ZettascaleConceptMastery = 0.0f;
    UltimateAbsoluteSupremeUltraHyperMetaIdeaGeneration = 0.0f;
    ConceptualUltimateAbsoluteSupremeUltraHyperEvolution = 0.0f;
    AbstractUltimateAbsoluteSupremeUltraHyperRealityCreation = 0.0f;
    UltimateConceptualUltimateAbsoluteSupremeUltimacy = 0.0f;
}

void UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateZettaConceptualStats();
}

void UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::ActivateZettaConceptual()
{
    if (!bIsZettaConceptualActive && CanActivateZettaConceptual())
    {
        bIsZettaConceptualActive = true;
        OnZettaConceptualActivated.Broadcast(ZettaConceptualLevel);
        OnZettaConceptualStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Zetta-Conceptual System Activated at Level: %d"), ZettaConceptualLevel);
    }
}

void UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::DeactivateZettaConceptual()
{
    if (bIsZettaConceptualActive)
    {
        bIsZettaConceptualActive = false;
        OnZettaConceptualDeactivated.Broadcast(ZettaConceptualLevel);
        OnZettaConceptualStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Zetta-Conceptual System Deactivated."));
    }
}

void UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::SetZettaConceptualLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxZettaConceptualLevel)
    {
        int32 OldLevel = ZettaConceptualLevel;
        ZettaConceptualLevel = NewLevel;
        UpdateZettaConceptualStats();
        OnZettaConceptualLevelChanged.Broadcast(OldLevel, ZettaConceptualLevel);
        UE_LOG(LogTemp, Warning, TEXT("Zetta-Conceptual Level set to: %d"), ZettaConceptualLevel);
        
        if (ZettaConceptualLevel >= MaxZettaConceptualLevel)
        {
            OnZettaConceptualMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Zetta-Conceptual Max Level Reached!"));
        }
    }
}

void UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::UseZettaConceptualPower()
{
    if (bIsZettaConceptualActive && ZettaConceptualLevel > 0)
    {
        OnZettaConceptualPowerUsed.Broadcast(ZettaConceptualPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Zetta-Conceptual Power Used: %.2f"), ZettaConceptualPowerCost);
    }
    else
    {
        OnZettaConceptualPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Zetta-Conceptual Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::PerformZettaConceptualAbility()
{
    if (bIsZettaConceptualActive && ZettaConceptualLevel >= ZettaConceptualThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Zetta-Conceptual Ability at Level %d!"), ZettaConceptualLevel);
        OnZettaConceptualAbilityPerformed.Broadcast(ZettaConceptualLevel);
        UseZettaConceptualPower();
        
        // Perform zetta-conceptual ability based on level
        switch (ZettaConceptualLevel / 20)
        {
            case 0:
                MasterZettascaleConcepts();
                break;
            case 1:
                GenerateUltimateAbsoluteSupremeUltraHyperMetaIdeas();
                break;
            case 2:
                EvolveConceptuallyUltimateAbsoluteSupremeUltraHyper();
                break;
            case 3:
                CreateAbstractUltimateAbsoluteSupremeUltraHyperReality();
                break;
            case 4:
            case 5:
                ExerciseUltimateConceptualUltimateAbsoluteSupremeUltimacy();
                break;
            default:
                ExerciseUltimateConceptualUltimateAbsoluteSupremeUltimacy();
                break;
        }
    }
    else if (ZettaConceptualLevel < ZettaConceptualThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Zetta-Conceptual Level too low to perform ability. Required: %.0f, Current: %d"), ZettaConceptualThreshold, ZettaConceptualLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Zetta-Conceptual is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::IsZettaConceptualActive() const
{
    return bIsZettaConceptualActive;
}

int32 UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::GetZettaConceptualLevel() const
{
    return ZettaConceptualLevel;
}

float UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::GetZettaConceptualPowerCost() const
{
    return ZettaConceptualPowerCost;
}

void UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::MasterZettascaleConcepts()
{
    if (bIsZettaConceptualActive)
    {
        float ConceptMastery = ZettascaleConceptMastery * (ZettaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Zettascale Concepts with power: %.2f"), ConceptMastery);
        // Apply zettascale concept mastery effects
    }
}

void UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::GenerateUltimateAbsoluteSupremeUltraHyperMetaIdeas()
{
    if (bIsZettaConceptualActive)
    {
        float IdeaGeneration = UltimateAbsoluteSupremeUltraHyperMetaIdeaGeneration * (ZettaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Generating Ultimate-Absolute-Supreme-Ultra-Hyper-Meta Ideas with power: %.2f"), IdeaGeneration);
        // Apply ultimate-absolute-supreme-ultra-hyper-meta idea generation effects
    }
}

void UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::EvolveConceptuallyUltimateAbsoluteSupremeUltraHyper()
{
    if (bIsZettaConceptualActive)
    {
        float EvolutionPower = ConceptualUltimateAbsoluteSupremeUltraHyperEvolution * (ZettaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually Ultimate-Absolute-Supreme-Ultra-Hyper with power: %.2f"), EvolutionPower);
        // Apply conceptual ultimate-absolute-supreme-ultra-hyper evolution effects
    }
}

void UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::CreateAbstractUltimateAbsoluteSupremeUltraHyperReality()
{
    if (bIsZettaConceptualActive)
    {
        float RealityCreation = AbstractUltimateAbsoluteSupremeUltraHyperRealityCreation * (ZettaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Creating Abstract Ultimate-Absolute-Supreme-Ultra-Hyper Reality with power: %.2f"), RealityCreation);
        // Apply abstract ultimate-absolute-supreme-ultra-hyper reality creation effects
    }
}

void UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::ExerciseUltimateConceptualUltimateAbsoluteSupremeUltimacy()
{
    if (bIsZettaConceptualActive)
    {
        float ConceptualUltimacy = UltimateConceptualUltimateAbsoluteSupremeUltimacy * (ZettaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Ultimate Conceptual Ultimate Absolute Supreme Ultimacy with power: %.2f"), ConceptualUltimacy);
        // Apply ultimate conceptual ultimate absolute supreme ultimacy effects
    }
}

bool UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::CanActivateZettaConceptual() const
{
    return ZettaConceptualLevel > 0;
}

void UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::UpdateZettaConceptualStats()
{
    // Update zetta-conceptual properties based on level
    ZettascaleConceptMastery = ZettaConceptualLevel * 17.5f;
    UltimateAbsoluteSupremeUltraHyperMetaIdeaGeneration = ZettaConceptualLevel * 17.3f;
    ConceptualUltimateAbsoluteSupremeUltraHyperEvolution = ZettaConceptualLevel * 17.2f;
    AbstractUltimateAbsoluteSupremeUltraHyperRealityCreation = ZettaConceptualLevel * 17.1f;
    UltimateConceptualUltimateAbsoluteSupremeUltimacy = ZettaConceptualLevel * 18.0f;
}

void UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM::OnZettaConceptualStateChanged()
{
    // Handle state change effects
    if (bIsZettaConceptualActive)
    {
        // Apply zetta-conceptual activation effects
        UE_LOG(LogTemp, Warning, TEXT("Zetta-Conceptual state changed to ACTIVE"));
    }
    else
    {
        // Remove zetta-conceptual effects
        UE_LOG(LogTemp, Warning, TEXT("Zetta-Conceptual state changed to INACTIVE"));
    }
}
