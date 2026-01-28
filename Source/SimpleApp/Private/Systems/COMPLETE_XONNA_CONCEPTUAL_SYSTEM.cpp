#include "COMPLETE_XONNA_CONCEPTUAL_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    XonnaConceptualLevel = 0;
    MaxXonnaConceptualLevel = 100;
    bIsXonnaConceptualActive = false;
    XonnaConceptualPowerCost = 30.0f;
    XonnaConceptualThreshold = 85.0f;
    
    // Initialize xonna-conceptual properties
    XonnascaleConceptMastery = 0.0f;
    UltraHyperMetaIdeaGeneration = 0.0f;
    ConceptualUltraHyperEvolution = 0.0f;
    AbstractUltraHyperRealityCreation = 0.0f;
    UltimateConceptualUltimacy = 0.0f;
}

void UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateXonnaConceptualStats();
}

void UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::ActivateXonnaConceptual()
{
    if (!bIsXonnaConceptualActive && CanActivateXonnaConceptual())
    {
        bIsXonnaConceptualActive = true;
        OnXonnaConceptualActivated.Broadcast(XonnaConceptualLevel);
        OnXonnaConceptualStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Xonna-Conceptual System Activated at Level: %d"), XonnaConceptualLevel);
    }
}

void UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::DeactivateXonnaConceptual()
{
    if (bIsXonnaConceptualActive)
    {
        bIsXonnaConceptualActive = false;
        OnXonnaConceptualDeactivated.Broadcast(XonnaConceptualLevel);
        OnXonnaConceptualStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Xonna-Conceptual System Deactivated."));
    }
}

void UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::SetXonnaConceptualLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxXonnaConceptualLevel)
    {
        int32 OldLevel = XonnaConceptualLevel;
        XonnaConceptualLevel = NewLevel;
        UpdateXonnaConceptualStats();
        OnXonnaConceptualLevelChanged.Broadcast(OldLevel, XonnaConceptualLevel);
        UE_LOG(LogTemp, Warning, TEXT("Xonna-Conceptual Level set to: %d"), XonnaConceptualLevel);
        
        if (XonnaConceptualLevel >= MaxXonnaConceptualLevel)
        {
            OnXonnaConceptualMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Xonna-Conceptual Max Level Reached!"));
        }
    }
}

void UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::UseXonnaConceptualPower()
{
    if (bIsXonnaConceptualActive && XonnaConceptualLevel > 0)
    {
        OnXonnaConceptualPowerUsed.Broadcast(XonnaConceptualPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Xonna-Conceptual Power Used: %.2f"), XonnaConceptualPowerCost);
    }
    else
    {
        OnXonnaConceptualPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Xonna-Conceptual Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::PerformXonnaConceptualAbility()
{
    if (bIsXonnaConceptualActive && XonnaConceptualLevel >= XonnaConceptualThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Xonna-Conceptual Ability at Level %d!"), XonnaConceptualLevel);
        OnXonnaConceptualAbilityPerformed.Broadcast(XonnaConceptualLevel);
        UseXonnaConceptualPower();
        
        // Perform xonna-conceptual ability based on level
        switch (XonnaConceptualLevel / 20)
        {
            case 0:
                MasterXonnascaleConcepts();
                break;
            case 1:
                GenerateUltraHyperMetaIdeas();
                break;
            case 2:
                EvolveConceptuallyUltraHyper();
                break;
            case 3:
                CreateAbstractUltraHyperReality();
                break;
            case 4:
            case 5:
                ExerciseUltimateConceptualUltimacy();
                break;
            default:
                ExerciseUltimateConceptualUltimacy();
                break;
        }
    }
    else if (XonnaConceptualLevel < XonnaConceptualThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Xonna-Conceptual Level too low to perform ability. Required: %.0f, Current: %d"), XonnaConceptualThreshold, XonnaConceptualLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Xonna-Conceptual is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::IsXonnaConceptualActive() const
{
    return bIsXonnaConceptualActive;
}

int32 UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::GetXonnaConceptualLevel() const
{
    return XonnaConceptualLevel;
}

float UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::GetXonnaConceptualPowerCost() const
{
    return XonnaConceptualPowerCost;
}

void UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::MasterXonnascaleConcepts()
{
    if (bIsXonnaConceptualActive)
    {
        float ConceptMastery = XonnascaleConceptMastery * (XonnaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Xonnascale Concepts with power: %.2f"), ConceptMastery);
        // Apply xonnascale concept mastery effects
    }
}

void UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::GenerateUltraHyperMetaIdeas()
{
    if (bIsXonnaConceptualActive)
    {
        float IdeaGeneration = UltraHyperMetaIdeaGeneration * (XonnaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Generating Ultra-Hyper-Meta Ideas with power: %.2f"), IdeaGeneration);
        // Apply ultra-hyper-meta idea generation effects
    }
}

void UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::EvolveConceptuallyUltraHyper()
{
    if (bIsXonnaConceptualActive)
    {
        float EvolutionPower = ConceptualUltraHyperEvolution * (XonnaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually Ultra-Hyper with power: %.2f"), EvolutionPower);
        // Apply conceptual ultra-hyper evolution effects
    }
}

void UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::CreateAbstractUltraHyperReality()
{
    if (bIsXonnaConceptualActive)
    {
        float RealityCreation = AbstractUltraHyperRealityCreation * (XonnaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Creating Abstract Ultra-Hyper Reality with power: %.2f"), RealityCreation);
        // Apply abstract ultra-hyper reality creation effects
    }
}

void UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::ExerciseUltimateConceptualUltimacy()
{
    if (bIsXonnaConceptualActive)
    {
        float ConceptualUltimacy = UltimateConceptualUltimacy * (XonnaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Ultimate Conceptual Ultimacy with power: %.2f"), ConceptualUltimacy);
        // Apply ultimate conceptual ultimacy effects
    }
}

bool UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::CanActivateXonnaConceptual() const
{
    return XonnaConceptualLevel > 0;
}

void UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::UpdateXonnaConceptualStats()
{
    // Update xonna-conceptual properties based on level
    XonnascaleConceptMastery = XonnaConceptualLevel * 7.8f;
    UltraHyperMetaIdeaGeneration = XonnaConceptualLevel * 7.6f;
    ConceptualUltraHyperEvolution = XonnaConceptualLevel * 7.5f;
    AbstractUltraHyperRealityCreation = XonnaConceptualLevel * 7.4f;
    UltimateConceptualUltimacy = XonnaConceptualLevel * 8.2f;
}

void UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM::OnXonnaConceptualStateChanged()
{
    // Handle state change effects
    if (bIsXonnaConceptualActive)
    {
        // Apply xonna-conceptual activation effects
        UE_LOG(LogTemp, Warning, TEXT("Xonna-Conceptual state changed to ACTIVE"));
    }
    else
    {
        // Remove xonna-conceptual effects
        UE_LOG(LogTemp, Warning, TEXT("Xonna-Conceptual state changed to INACTIVE"));
    }
}
