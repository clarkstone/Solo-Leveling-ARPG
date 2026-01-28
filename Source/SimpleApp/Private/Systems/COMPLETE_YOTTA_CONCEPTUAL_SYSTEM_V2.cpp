#include "COMPLETE_YOTTA_CONCEPTUAL_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    YottaConceptualLevel = 0;
    MaxYottaConceptualLevel = 100;
    bIsYottaConceptualActive = false;
    YottaConceptualPowerCost = 55.0f;
    YottaConceptualThreshold = 100.0f;
    
    // Initialize yotta-conceptual properties
    YottascaleConceptMastery = 0.0f;
    FinalUltimateAbsoluteSupremeUltraHyperMetaIdeaGeneration = 0.0f;
    ConceptualFinalUltimateAbsoluteSupremeUltraHyperEvolution = 0.0f;
    AbstractFinalUltimateAbsoluteSupremeUltraHyperRealityCreation = 0.0f;
    UltimateConceptualFinalUltimateAbsoluteSupremeUltimacy = 0.0f;
}

void UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateYottaConceptualStats();
}

void UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::ActivateYottaConceptual()
{
    if (!bIsYottaConceptualActive && CanActivateYottaConceptual())
    {
        bIsYottaConceptualActive = true;
        OnYottaConceptualActivated.Broadcast(YottaConceptualLevel);
        OnYottaConceptualStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Yotta-Conceptual System Activated at Level: %d"), YottaConceptualLevel);
    }
}

void UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::DeactivateYottaConceptual()
{
    if (bIsYottaConceptualActive)
    {
        bIsYottaConceptualActive = false;
        OnYottaConceptualDeactivated.Broadcast(YottaConceptualLevel);
        OnYottaConceptualStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Yotta-Conceptual System Deactivated."));
    }
}

void UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::SetYottaConceptualLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxYottaConceptualLevel)
    {
        int32 OldLevel = YottaConceptualLevel;
        YottaConceptualLevel = NewLevel;
        UpdateYottaConceptualStats();
        OnYottaConceptualLevelChanged.Broadcast(OldLevel, YottaConceptualLevel);
        UE_LOG(LogTemp, Warning, TEXT("Yotta-Conceptual Level set to: %d"), YottaConceptualLevel);
        
        if (YottaConceptualLevel >= MaxYottaConceptualLevel)
        {
            OnYottaConceptualMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Yotta-Conceptual Max Level Reached!"));
        }
    }
}

void UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::UseYottaConceptualPower()
{
    if (bIsYottaConceptualActive && YottaConceptualLevel > 0)
    {
        OnYottaConceptualPowerUsed.Broadcast(YottaConceptualPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Yotta-Conceptual Power Used: %.2f"), YottaConceptualPowerCost);
    }
    else
    {
        OnYottaConceptualPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Yotta-Conceptual Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::PerformYottaConceptualAbility()
{
    if (bIsYottaConceptualActive && YottaConceptualLevel >= YottaConceptualThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Yotta-Conceptual Ability at Level %d!"), YottaConceptualLevel);
        OnYottaConceptualAbilityPerformed.Broadcast(YottaConceptualLevel);
        UseYottaConceptualPower();
        
        // Perform yotta-conceptual ability based on level
        switch (YottaConceptualLevel / 20)
        {
            case 0:
                MasterYottascaleConcepts();
                break;
            case 1:
                GenerateFinalUltimateAbsoluteSupremeUltraHyperMetaIdeas();
                break;
            case 2:
                EvolveConceptuallyFinalUltimateAbsoluteSupremeUltraHyper();
                break;
            case 3:
                CreateAbstractFinalUltimateAbsoluteSupremeUltraHyperReality();
                break;
            case 4:
            case 5:
                ExerciseUltimateConceptualFinalUltimateAbsoluteSupremeUltimacy();
                break;
            default:
                ExerciseUltimateConceptualFinalUltimateAbsoluteSupremeUltimacy();
                break;
        }
    }
    else if (YottaConceptualLevel < YottaConceptualThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Yotta-Conceptual Level too low to perform ability. Required: %.0f, Current: %d"), YottaConceptualThreshold, YottaConceptualLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Yotta-Conceptual is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::IsYottaConceptualActive() const
{
    return bIsYottaConceptualActive;
}

int32 UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::GetYottaConceptualLevel() const
{
    return YottaConceptualLevel;
}

float UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::GetYottaConceptualPowerCost() const
{
    return YottaConceptualPowerCost;
}

void UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::MasterYottascaleConcepts()
{
    if (bIsYottaConceptualActive)
    {
        float ConceptMastery = YottascaleConceptMastery * (YottaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Yottascale Concepts with power: %.2f"), ConceptMastery);
        // Apply yottascale concept mastery effects
    }
}

void UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::GenerateFinalUltimateAbsoluteSupremeUltraHyperMetaIdeas()
{
    if (bIsYottaConceptualActive)
    {
        float IdeaGeneration = FinalUltimateAbsoluteSupremeUltraHyperMetaIdeaGeneration * (YottaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Generating Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta Ideas with power: %.2f"), IdeaGeneration);
        // Apply final-ultimate-absolute-supreme-ultra-hyper-meta idea generation effects
    }
}

void UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::EvolveConceptuallyFinalUltimateAbsoluteSupremeUltraHyper()
{
    if (bIsYottaConceptualActive)
    {
        float EvolutionPower = ConceptualFinalUltimateAbsoluteSupremeUltraHyperEvolution * (YottaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually Final-Ultimate-Absolute-Supreme-Ultra-Hyper with power: %.2f"), EvolutionPower);
        // Apply conceptual final-ultimate-absolute-supreme-ultra-hyper evolution effects
    }
}

void UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::CreateAbstractFinalUltimateAbsoluteSupremeUltraHyperReality()
{
    if (bIsYottaConceptualActive)
    {
        float RealityCreation = AbstractFinalUltimateAbsoluteSupremeUltraHyperRealityCreation * (YottaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Creating Abstract Final-Ultimate-Absolute-Supreme-Ultra-Hyper Reality with power: %.2f"), RealityCreation);
        // Apply abstract final-ultimate-absolute-supreme-ultra-hyper reality creation effects
    }
}

void UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::ExerciseUltimateConceptualFinalUltimateAbsoluteSupremeUltimacy()
{
    if (bIsYottaConceptualActive)
    {
        float ConceptualUltimacy = UltimateConceptualFinalUltimateAbsoluteSupremeUltimacy * (YottaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Ultimate Conceptual Final-Ultimate-Absolute-Supreme Ultimacy with power: %.2f"), ConceptualUltimacy);
        // Apply ultimate conceptual final-ultimate-absolute-supreme ultimacy effects
    }
}

bool UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::CanActivateYottaConceptual() const
{
    return YottaConceptualLevel > 0;
}

void UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::UpdateYottaConceptualStats()
{
    // Update yotta-conceptual properties based on level
    YottascaleConceptMastery = YottaConceptualLevel * 21.5f;
    FinalUltimateAbsoluteSupremeUltraHyperMetaIdeaGeneration = YottaConceptualLevel * 21.3f;
    ConceptualFinalUltimateAbsoluteSupremeUltraHyperEvolution = YottaConceptualLevel * 21.2f;
    AbstractFinalUltimateAbsoluteSupremeUltraHyperRealityCreation = YottaConceptualLevel * 21.1f;
    UltimateConceptualFinalUltimateAbsoluteSupremeUltimacy = YottaConceptualLevel * 22.0f;
}

void UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM::OnYottaConceptualStateChanged()
{
    // Handle state change effects
    if (bIsYottaConceptualActive)
    {
        // Apply yotta-conceptual activation effects
        UE_LOG(LogTemp, Warning, TEXT("Yotta-Conceptual state changed to ACTIVE"));
    }
    else
    {
        // Remove yotta-conceptual effects
        UE_LOG(LogTemp, Warning, TEXT("Yotta-Conceptual state changed to INACTIVE"));
    }
}
