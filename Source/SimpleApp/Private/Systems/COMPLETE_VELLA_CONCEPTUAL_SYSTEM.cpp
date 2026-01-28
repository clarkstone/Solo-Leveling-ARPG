#include "COMPLETE_VELLA_CONCEPTUAL_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    VellaConceptualLevel = 0;
    MaxVellaConceptualLevel = 100;
    bIsVellaConceptualActive = false;
    VellaConceptualPowerCost = 40.0f;
    VellaConceptualThreshold = 95.0f;
    
    // Initialize vella-conceptual properties
    VellascaleConceptMastery = 0.0f;
    AbsoluteSupremeUltraHyperMetaIdeaGeneration = 0.0f;
    ConceptualAbsoluteSupremeUltraHyperEvolution = 0.0f;
    AbstractAbsoluteSupremeUltraHyperRealityCreation = 0.0f;
    UltimateConceptualAbsoluteSupremeUltimacy = 0.0f;
}

void UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateVellaConceptualStats();
}

void UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::ActivateVellaConceptual()
{
    if (!bIsVellaConceptualActive && CanActivateVellaConceptual())
    {
        bIsVellaConceptualActive = true;
        OnVellaConceptualActivated.Broadcast(VellaConceptualLevel);
        OnVellaConceptualStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Vella-Conceptual System Activated at Level: %d"), VellaConceptualLevel);
    }
}

void UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::DeactivateVellaConceptual()
{
    if (bIsVellaConceptualActive)
    {
        bIsVellaConceptualActive = false;
        OnVellaConceptualDeactivated.Broadcast(VellaConceptualLevel);
        OnVellaConceptualStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Vella-Conceptual System Deactivated."));
    }
}

void UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::SetVellaConceptualLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxVellaConceptualLevel)
    {
        int32 OldLevel = VellaConceptualLevel;
        VellaConceptualLevel = NewLevel;
        UpdateVellaConceptualStats();
        OnVellaConceptualLevelChanged.Broadcast(OldLevel, VellaConceptualLevel);
        UE_LOG(LogTemp, Warning, TEXT("Vella-Conceptual Level set to: %d"), VellaConceptualLevel);
        
        if (VellaConceptualLevel >= MaxVellaConceptualLevel)
        {
            OnVellaConceptualMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Vella-Conceptual Max Level Reached!"));
        }
    }
}

void UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::UseVellaConceptualPower()
{
    if (bIsVellaConceptualActive && VellaConceptualLevel > 0)
    {
        OnVellaConceptualPowerUsed.Broadcast(VellaConceptualPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Vella-Conceptual Power Used: %.2f"), VellaConceptualPowerCost);
    }
    else
    {
        OnVellaConceptualPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Vella-Conceptual Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::PerformVellaConceptualAbility()
{
    if (bIsVellaConceptualActive && VellaConceptualLevel >= VellaConceptualThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Vella-Conceptual Ability at Level %d!"), VellaConceptualLevel);
        OnVellaConceptualAbilityPerformed.Broadcast(VellaConceptualLevel);
        UseVellaConceptualPower();
        
        // Perform vella-conceptual ability based on level
        switch (VellaConceptualLevel / 20)
        {
            case 0:
                MasterVellascaleConcepts();
                break;
            case 1:
                GenerateAbsoluteSupremeUltraHyperMetaIdeas();
                break;
            case 2:
                EvolveConceptuallyAbsoluteSupremeUltraHyper();
                break;
            case 3:
                CreateAbstractAbsoluteSupremeUltraHyperReality();
                break;
            case 4:
            case 5:
                ExerciseUltimateConceptualAbsoluteSupremeUltimacy();
                break;
            default:
                ExerciseUltimateConceptualAbsoluteSupremeUltimacy();
                break;
        }
    }
    else if (VellaConceptualLevel < VellaConceptualThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Vella-Conceptual Level too low to perform ability. Required: %.0f, Current: %d"), VellaConceptualThreshold, VellaConceptualLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Vella-Conceptual is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::IsVellaConceptualActive() const
{
    return bIsVellaConceptualActive;
}

int32 UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::GetVellaConceptualLevel() const
{
    return VellaConceptualLevel;
}

float UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::GetVellaConceptualPowerCost() const
{
    return VellaConceptualPowerCost;
}

void UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::MasterVellascaleConcepts()
{
    if (bIsVellaConceptualActive)
    {
        float ConceptMastery = VellascaleConceptMastery * (VellaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Vellascale Concepts with power: %.2f"), ConceptMastery);
        // Apply vellascale concept mastery effects
    }
}

void UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::GenerateAbsoluteSupremeUltraHyperMetaIdeas()
{
    if (bIsVellaConceptualActive)
    {
        float IdeaGeneration = AbsoluteSupremeUltraHyperMetaIdeaGeneration * (VellaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Generating Absolute-Supreme-Ultra-Hyper-Meta Ideas with power: %.2f"), IdeaGeneration);
        // Apply absolute-supreme-ultra-hyper-meta idea generation effects
    }
}

void UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::EvolveConceptuallyAbsoluteSupremeUltraHyper()
{
    if (bIsVellaConceptualActive)
    {
        float EvolutionPower = ConceptualAbsoluteSupremeUltraHyperEvolution * (VellaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually Absolute-Supreme-Ultra-Hyper with power: %.2f"), EvolutionPower);
        // Apply conceptual absolute-supreme-ultra-hyper evolution effects
    }
}

void UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::CreateAbstractAbsoluteSupremeUltraHyperReality()
{
    if (bIsVellaConceptualActive)
    {
        float RealityCreation = AbstractAbsoluteSupremeUltraHyperRealityCreation * (VellaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Creating Abstract Absolute-Supreme-Ultra-Hyper Reality with power: %.2f"), RealityCreation);
        // Apply abstract absolute-supreme-ultra-hyper reality creation effects
    }
}

void UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::ExerciseUltimateConceptualAbsoluteSupremeUltimacy()
{
    if (bIsVellaConceptualActive)
    {
        float ConceptualUltimacy = UltimateConceptualAbsoluteSupremeUltimacy * (VellaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Ultimate Conceptual Absolute Supreme Ultimacy with power: %.2f"), ConceptualUltimacy);
        // Apply ultimate conceptual absolute supreme ultimacy effects
    }
}

bool UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::CanActivateVellaConceptual() const
{
    return VellaConceptualLevel > 0;
}

void UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::UpdateVellaConceptualStats()
{
    // Update vella-conceptual properties based on level
    VellascaleConceptMastery = VellaConceptualLevel * 13.5f;
    AbsoluteSupremeUltraHyperMetaIdeaGeneration = VellaConceptualLevel * 13.3f;
    ConceptualAbsoluteSupremeUltraHyperEvolution = VellaConceptualLevel * 13.2f;
    AbstractAbsoluteSupremeUltraHyperRealityCreation = VellaConceptualLevel * 13.1f;
    UltimateConceptualAbsoluteSupremeUltimacy = VellaConceptualLevel * 14.0f;
}

void UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM::OnVellaConceptualStateChanged()
{
    // Handle state change effects
    if (bIsVellaConceptualActive)
    {
        // Apply vella-conceptual activation effects
        UE_LOG(LogTemp, Warning, TEXT("Vella-Conceptual state changed to ACTIVE"));
    }
    else
    {
        // Remove vella-conceptual effects
        UE_LOG(LogTemp, Warning, TEXT("Vella-Conceptual state changed to INACTIVE"));
    }
}
