#include "COMPLETE_COSMIC_NULL_VOID_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::UCOMPLETE_COSMIC_NULL_VOID_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    CosmicNullVoidLevel = 0;
    MaxCosmicNullVoidLevel = 100;
    bIsCosmicNullVoidActive = false;
    CosmicNullVoidPowerCost = 50.0f;
    CosmicNullVoidThreshold = 100.0f;
    
    // Initialize cosmic-null-void properties
    CosmicNullVoidMastery = 0.0f;
    UltimateAbsoluteVoidAnnihilation = 0.0f;
    PerfectCosmicNullEmptiness = 0.0f;
    ConceptualCosmicNullOblivion = 0.0f;
    ExistenceCosmicNullNegation = 0.0f;
}

void UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateCosmicNullVoidStats();
}

void UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::ActivateCosmicNullVoid()
{
    if (!bIsCosmicNullVoidActive && CanActivateCosmicNullVoid())
    {
        bIsCosmicNullVoidActive = true;
        OnCosmicNullVoidActivated.Broadcast(CosmicNullVoidLevel);
        OnCosmicNullVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Cosmic-Null-Void System Activated at Level: %d"), CosmicNullVoidLevel);
    }
}

void UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::DeactivateCosmicNullVoid()
{
    if (bIsCosmicNullVoidActive)
    {
        bIsCosmicNullVoidActive = false;
        OnCosmicNullVoidDeactivated.Broadcast(CosmicNullVoidLevel);
        OnCosmicNullVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Cosmic-Null-Void System Deactivated."));
    }
}

void UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::SetCosmicNullVoidLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxCosmicNullVoidLevel)
    {
        int32 OldLevel = CosmicNullVoidLevel;
        CosmicNullVoidLevel = NewLevel;
        UpdateCosmicNullVoidStats();
        OnCosmicNullVoidLevelChanged.Broadcast(OldLevel, CosmicNullVoidLevel);
        UE_LOG(LogTemp, Warning, TEXT("Cosmic-Null-Void Level set to: %d"), CosmicNullVoidLevel);
        
        if (CosmicNullVoidLevel >= MaxCosmicNullVoidLevel)
        {
            OnCosmicNullVoidMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Cosmic-Null-Void Max Level Reached!"));
        }
    }
}

void UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::UseCosmicNullVoidPower()
{
    if (bIsCosmicNullVoidActive && CosmicNullVoidLevel > 0)
    {
        OnCosmicNullVoidPowerUsed.Broadcast(CosmicNullVoidPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Cosmic-Null-Void Power Used: %.2f"), CosmicNullVoidPowerCost);
    }
    else
    {
        OnCosmicNullVoidPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Cosmic-Null-Void Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::PerformCosmicNullVoidAbility()
{
    if (bIsCosmicNullVoidActive && CosmicNullVoidLevel >= CosmicNullVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Cosmic-Null-Void Ability at Level %d!"), CosmicNullVoidLevel);
        OnCosmicNullVoidAbilityPerformed.Broadcast(CosmicNullVoidLevel);
        UseCosmicNullVoidPower();
        
        // Perform cosmic-null-void ability based on level
        switch (CosmicNullVoidLevel / 20)
        {
            case 0:
                MasterCosmicNullVoid();
                break;
            case 1:
                AnnihilateCosmicNullUltimately();
                break;
            case 2:
                AchievePerfectCosmicNullEmptiness();
                break;
            case 3:
                InduceConceptualCosmicNullOblivion();
                break;
            case 4:
            case 5:
                NegateExistenceCosmicNull();
                break;
            default:
                NegateExistenceCosmicNull();
                break;
        }
    }
    else if (CosmicNullVoidLevel < CosmicNullVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cosmic-Null-Void Level too low to perform ability. Required: %.0f, Current: %d"), CosmicNullVoidThreshold, CosmicNullVoidLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Cosmic-Null-Void is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::IsCosmicNullVoidActive() const
{
    return bIsCosmicNullVoidActive;
}

int32 UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::GetCosmicNullVoidLevel() const
{
    return CosmicNullVoidLevel;
}

float UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::GetCosmicNullVoidPowerCost() const
{
    return CosmicNullVoidPowerCost;
}

void UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::MasterCosmicNullVoid()
{
    if (bIsCosmicNullVoidActive)
    {
        float VoidMastery = CosmicNullVoidMastery * (CosmicNullVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Cosmic-Null-Void with power: %.2f"), VoidMastery);
        // Apply cosmic-null-void mastery effects
    }
}

void UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::AnnihilateCosmicNullUltimately()
{
    if (bIsCosmicNullVoidActive)
    {
        float AnnihilationPower = UltimateAbsoluteVoidAnnihilation * (CosmicNullVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Cosmic-Null Ultimately with power: %.2f"), AnnihilationPower);
        // Apply cosmic-null ultimate annihilation effects
    }
}

void UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::AchievePerfectCosmicNullEmptiness()
{
    if (bIsCosmicNullVoidActive)
    {
        float EmptinessPower = PerfectCosmicNullEmptiness * (CosmicNullVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Perfect Cosmic Null Emptiness with power: %.2f"), EmptinessPower);
        // Apply perfect cosmic null emptiness effects
    }
}

void UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::InduceConceptualCosmicNullOblivion()
{
    if (bIsCosmicNullVoidActive)
    {
        float OblivionPower = ConceptualCosmicNullOblivion * (CosmicNullVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Conceptual Cosmic Null Oblivion with power: %.2f"), OblivionPower);
        // Apply conceptual cosmic null oblivion effects
    }
}

void UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::NegateExistenceCosmicNull()
{
    if (bIsCosmicNullVoidActive)
    {
        float NegationPower = ExistenceCosmicNullNegation * (CosmicNullVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Existence Cosmic Null with power: %.2f"), NegationPower);
        // Apply existence cosmic null negation effects
    }
}

bool UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::CanActivateCosmicNullVoid() const
{
    return CosmicNullVoidLevel > 0;
}

void UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::UpdateCosmicNullVoidStats()
{
    // Update cosmic-null-void properties based on level
    CosmicNullVoidMastery = CosmicNullVoidLevel * 17.8f;
    UltimateAbsoluteVoidAnnihilation = CosmicNullVoidLevel * 17.6f;
    PerfectCosmicNullEmptiness = CosmicNullVoidLevel * 17.5f;
    ConceptualCosmicNullOblivion = CosmicNullVoidLevel * 17.4f;
    ExistenceCosmicNullNegation = CosmicNullVoidLevel * 18.2f;
}

void UCOMPLETE_COSMIC_NULL_VOID_SYSTEM::OnCosmicNullVoidStateChanged()
{
    // Handle state change effects
    if (bIsCosmicNullVoidActive)
    {
        // Apply cosmic-null-void activation effects
        UE_LOG(LogTemp, Warning, TEXT("Cosmic-Null-Void state changed to ACTIVE"));
    }
    else
    {
        // Remove cosmic-null-void effects
        UE_LOG(LogTemp, Warning, TEXT("Cosmic-Null-Void state changed to INACTIVE"));
    }
}
