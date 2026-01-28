#include "COMPLETE_EXA_CONCEPTUAL_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::UCOMPLETE_EXA_CONCEPTUAL_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    ExaConceptualLevel = 0;
    MaxExaConceptualLevel = 100;
    bIsExaConceptualActive = false;
    ExaConceptualPowerCost = 15.0f;
    ExaConceptualThreshold = 60.0f;
    
    // Initialize exa-conceptual properties
    ExascaleConceptMastery = 0.0f;
    InfiniteIdeaGeneration = 0.0f;
    ConceptualRealityShaping = 0.0f;
    AbstractThoughtManifestation = 0.0f;
    MetaConceptualAuthority = 0.0f;
}

void UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateExaConceptualStats();
}

void UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::ActivateExaConceptual()
{
    if (!bIsExaConceptualActive && CanActivateExaConceptual())
    {
        bIsExaConceptualActive = true;
        OnExaConceptualActivated.Broadcast(ExaConceptualLevel);
        OnExaConceptualStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Exa-Conceptual System Activated at Level: %d"), ExaConceptualLevel);
    }
}

void UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::DeactivateExaConceptual()
{
    if (bIsExaConceptualActive)
    {
        bIsExaConceptualActive = false;
        OnExaConceptualDeactivated.Broadcast(ExaConceptualLevel);
        OnExaConceptualStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Exa-Conceptual System Deactivated."));
    }
}

void UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::SetExaConceptualLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxExaConceptualLevel)
    {
        int32 OldLevel = ExaConceptualLevel;
        ExaConceptualLevel = NewLevel;
        UpdateExaConceptualStats();
        OnExaConceptualLevelChanged.Broadcast(OldLevel, ExaConceptualLevel);
        UE_LOG(LogTemp, Warning, TEXT("Exa-Conceptual Level set to: %d"), ExaConceptualLevel);
        
        if (ExaConceptualLevel >= MaxExaConceptualLevel)
        {
            OnExaConceptualMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Exa-Conceptual Max Level Reached!"));
        }
    }
}

void UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::UseExaConceptualPower()
{
    if (bIsExaConceptualActive && ExaConceptualLevel > 0)
    {
        OnExaConceptualPowerUsed.Broadcast(ExaConceptualPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Exa-Conceptual Power Used: %.2f"), ExaConceptualPowerCost);
    }
    else
    {
        OnExaConceptualPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Exa-Conceptual Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::PerformExaConceptualAbility()
{
    if (bIsExaConceptualActive && ExaConceptualLevel >= ExaConceptualThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Exa-Conceptual Ability at Level %d!"), ExaConceptualLevel);
        OnExaConceptualAbilityPerformed.Broadcast(ExaConceptualLevel);
        UseExaConceptualPower();
        
        // Perform exa-conceptual ability based on level
        switch (ExaConceptualLevel / 20)
        {
            case 0:
                MasterExascaleConcepts();
                break;
            case 1:
                GenerateInfiniteIdeas();
                break;
            case 2:
                ShapeConceptualReality();
                break;
            case 3:
                ManifestAbstractThoughts();
                break;
            case 4:
            case 5:
                ExerciseMetaConceptualAuthority();
                break;
            default:
                ExerciseMetaConceptualAuthority();
                break;
        }
    }
    else if (ExaConceptualLevel < ExaConceptualThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Exa-Conceptual Level too low to perform ability. Required: %.0f, Current: %d"), ExaConceptualThreshold, ExaConceptualLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Exa-Conceptual is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::IsExaConceptualActive() const
{
    return bIsExaConceptualActive;
}

int32 UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::GetExaConceptualLevel() const
{
    return ExaConceptualLevel;
}

float UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::GetExaConceptualPowerCost() const
{
    return ExaConceptualPowerCost;
}

void UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::MasterExascaleConcepts()
{
    if (bIsExaConceptualActive)
    {
        float ConceptMastery = ExascaleConceptMastery * (ExaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Exascale Concepts with power: %.2f"), ConceptMastery);
        // Apply exascale concept mastery effects
    }
}

void UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::GenerateInfiniteIdeas()
{
    if (bIsExaConceptualActive)
    {
        float IdeaGeneration = InfiniteIdeaGeneration * (ExaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Generating Infinite Ideas with power: %.2f"), IdeaGeneration);
        // Apply infinite idea generation effects
    }
}

void UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::ShapeConceptualReality()
{
    if (bIsExaConceptualActive)
    {
        float RealityShaping = ConceptualRealityShaping * (ExaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Shaping Conceptual Reality with power: %.2f"), RealityShaping);
        // Apply conceptual reality shaping effects
    }
}

void UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::ManifestAbstractThoughts()
{
    if (bIsExaConceptualActive)
    {
        float ThoughtManifestation = AbstractThoughtManifestation * (ExaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Manifesting Abstract Thoughts with power: %.2f"), ThoughtManifestation);
        // Apply abstract thought manifestation effects
    }
}

void UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::ExerciseMetaConceptualAuthority()
{
    if (bIsExaConceptualActive)
    {
        float ConceptualAuthority = MetaConceptualAuthority * (ExaConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Meta-Conceptual Authority with power: %.2f"), ConceptualAuthority);
        // Apply meta-conceptual authority effects
    }
}

bool UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::CanActivateExaConceptual() const
{
    return ExaConceptualLevel > 0;
}

void UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::UpdateExaConceptualStats()
{
    // Update exa-conceptual properties based on level
    ExascaleConceptMastery = ExaConceptualLevel * 3.1f;
    InfiniteIdeaGeneration = ExaConceptualLevel * 2.9f;
    ConceptualRealityShaping = ExaConceptualLevel * 3.0f;
    AbstractThoughtManifestation = ExaConceptualLevel * 2.8f;
    MetaConceptualAuthority = ExaConceptualLevel * 3.2f;
}

void UCOMPLETE_EXA_CONCEPTUAL_SYSTEM::OnExaConceptualStateChanged()
{
    // Handle state change effects
    if (bIsExaConceptualActive)
    {
        // Apply exa-conceptual activation effects
        UE_LOG(LogTemp, Warning, TEXT("Exa-Conceptual state changed to ACTIVE"));
    }
    else
    {
        // Remove exa-conceptual effects
        UE_LOG(LogTemp, Warning, TEXT("Exa-Conceptual state changed to INACTIVE"));
    }
}
