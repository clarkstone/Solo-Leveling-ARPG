#include "P04_CNCP_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_CNCP_SYSTEM::UCOMPLETE_CNCP_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    ConceptualLevel = 0;
    MaxConceptualLevel = 100;
    bIsConceptualActive = false;
    ConceptualPowerCost = 20.0f;
    ConceptualThreshold = 20.0f;
    
    // Initialize conceptual properties
    ConceptualMastery = 0.0f;
    UltimateIdeaGeneration = 0.0f;
    ConceptualEvolution = 0.0f;
    AbstractRealityCreation = 0.0f;
    UltimateConceptualUltimacy = 0.0f;
}

void UCOMPLETE_CNCP_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateConceptualStats();
}

void UCOMPLETE_CNCP_SYSTEM::ActivateConceptual()
{
    if (!bIsConceptualActive && CanActivateConceptual())
    {
        bIsConceptualActive = true;
        OnConceptualActivated.Broadcast(ConceptualLevel);
        OnConceptualStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Conceptual System Activated at Level: %d"), ConceptualLevel);
    }
}

void UCOMPLETE_CNCP_SYSTEM::DeactivateConceptual()
{
    if (bIsConceptualActive)
    {
        bIsConceptualActive = false;
        OnConceptualDeactivated.Broadcast(ConceptualLevel);
        OnConceptualStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Conceptual System Deactivated."));
    }
}

void UCOMPLETE_CNCP_SYSTEM::SetConceptualLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxConceptualLevel)
    {
        int32 OldLevel = ConceptualLevel;
        ConceptualLevel = NewLevel;
        UpdateConceptualStats();
        OnConceptualLevelChanged.Broadcast(OldLevel, ConceptualLevel);
        UE_LOG(LogTemp, Warning, TEXT("Conceptual Level set to: %d"), ConceptualLevel);
        
        if (ConceptualLevel >= MaxConceptualLevel)
        {
            OnConceptualMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Conceptual Max Level Reached!"));
        }
    }
}

void UCOMPLETE_CNCP_SYSTEM::UseConceptualPower()
{
    if (bIsConceptualActive && ConceptualLevel > 0)
    {
        OnConceptualPowerUsed.Broadcast(ConceptualPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Conceptual Power Used: %.2f"), ConceptualPowerCost);
    }
    else
    {
        OnConceptualPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Conceptual Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_CNCP_SYSTEM::PerformConceptualAbility()
{
    if (bIsConceptualActive && ConceptualLevel >= ConceptualThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Conceptual Ability at Level %d!"), ConceptualLevel);
        OnConceptualAbilityPerformed.Broadcast(ConceptualLevel);
        UseConceptualPower();
        
        // Perform conceptual ability based on level
        switch (ConceptualLevel / 20)
        {
            case 0:
                MasterConcepts();
                    break;
            case 1:
                GenerateUltimateIdeas();
                    break;
            case 2:
                EvolveConceptually();
                    break;
            case 3:
                CreateAbstractReality();
                    break;
            default:
                ExerciseUltimateConceptualUltimacy();
                    break;
        }
    }
    }
    }
    }
    else if (ConceptualLevel < ConceptualThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Conceptual Level too low to perform ability. Required: %.0f, Current: %d"), ConceptualThreshold, ConceptualLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Conceptual is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_CNCP_SYSTEM::IsConceptualActive() const
{
    return bIsConceptualActive;
}

int32 UCOMPLETE_CNCP_SYSTEM::GetConceptualLevel() const
{
    return ConceptualLevel;
}

float UCOMPLETE_CNCP_SYSTEM::GetConceptualPowerCost() const
{
    return ConceptualPowerCost;
}

void UCOMPLETE_CNCP_SYSTEM::MasterConcepts()
{
    if (bIsConceptualActive)
    {
        float ConceptMastery = ConceptualMastery * (ConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Concepts with power: %.2f"), ConceptMastery);
        // Apply conceptual mastery effects
    }
}

void UCOMPLETE_CNCP_SYSTEM::GenerateUltimateIdeas()
{
    if (bIsConceptualActive)
    {
        float IdeaGeneration = UltimateIdeaGeneration * (ConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Generating Ultimate Ideas with power: %.2f"), IdeaGeneration);
        // Apply ultimate idea generation effects
    }
}

void UCOMPLETE_CNCP_SYSTEM::EvolveConceptually()
{
    if (bIsConceptualActive)
    {
        float EvolutionPower = ConceptualEvolution * (ConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually with power: %.2f"), EvolutionPower);
        // Apply conceptual evolution effects
    }
}

void UCOMPLETE_CPNCPS_SYSTEM::CreateAbstractReality()
{
    if (bIsConceptualActive)
    {
        float RealityCreation = AbstractRealityCreation * (ConceptualLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Creating Abstract Reality with power: %.2f"), RealityCreation);
        // Apply abstract reality creation effects
    }
}

bool UCOMPLETE_CNCP_SYSTEM::CanActivateConceptual() const
{
    return ConceptualLevel > 0;
}

void UCOMPLETE_CNCP_SYSTEM::UpdateConceptualStats()
{
    // Update conceptual properties based on level
    ConceptualMastery = ConceptualLevel * 2.5f;
    UltimateIdeaGeneration = ConceptualLevel * 2.3f;
    ConceptualEvolution = ConceptualLevel * 2.4f;
    AbstractRealityCreation = ConceptualLevel * 2.6f;
    UltimateConceptualUltimacy = ConceptualLevel * 2.7f;
}

void UCOMPLETE_CPNCPSYSTEM::OnConceptualStateChanged()
{
    // Handle state change effects
    if (bIsConceptualActive)
    {
        // Apply conceptual activation effects
        UE_LOG(LogTemp, Warning, TEXT("Conceptual state changed to ACTIVE"));
    }
    else
    {
        // Remove conceptual effects
        UE_LOG(LogTemp, Warning, TEXT("Conceptual state changed to INACTIVE"));
    }
}
