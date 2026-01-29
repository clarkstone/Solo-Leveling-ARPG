#include "P01_VOID_ULTIMATE.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP01_VOID_ULTIMATE::UP01_VOID_ULTIMATE()
{
    PrimaryComponentTick.bCanEverTick = false;
    UltimateVoidLevel = 0;
    MaxUltimateVoidLevel = 100;
    bIsUltimateVoidActive = false;
    UltimateVoidPowerCost = 10.0f;
    UltimateVoidThreshold = 10.0f;
    
    // Initialize ultimate void properties
    VoidMastery = 0.0f;
    UltimateAnnihilation = 0.0f;
    PerfectVoidEmptiness = 0.0f;
    ConceptualUltimateOblivion = 0.0f;
    ExistenceUltimateNegation = 0.0f;
}

void UP01_VOID_ULTIMATE::BeginPlay()
{
    Super::BeginPlay();
    UpdateUltimateVoidStats();
}

void UP01_VOID_ULTIMATE::ActivateUltimateVoid()
{
    if (!bIsUltimateVoidActive && CanActivateUltimateVoid())
    {
        bIsUltimateVoidActive = true;
        OnUltimateVoidActivated.Broadcast(UltimateVoidLevel);
        OnUltimateVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Void System Activated at Level: %d"), UltimateVoidLevel);
    }
}

void UP01_VOID_ULTIMATE::DeactivateUltimateVoid()
{
    if (bIsUltimateVoidActive)
    {
        bIsUltimateVoidActive = false;
        OnUltimateVoidDeactivated.Broadcast(UltimateVoidLevel);
        OnUltimateVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Void System Deactivated."));
    }
}

void UP01_VOID_ULTIMATE::SetUltimateVoidLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxUltimateVoidLevel)
    {
        int32 OldLevel = UltimateVoidLevel;
        UltimateVoidLevel = NewLevel;
        UpdateUltimateVoidStats();
        OnUltimateVoidLevelChanged.Broadcast(OldLevel, UltimateVoidLevel);
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Void Level set to: %d"), UltimateVoidLevel);
        
        if (UltimateVoidLevel >= MaxUltimateVoidLevel)
        {
            OnUltimateVoidMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Ultimate Void Max Level Reached!"));
        }
    }
}

void UP01_VOID_ULTIMATE::UseUltimateVoidPower()
{
    if (bIsUltimateVoidActive && UltimateVoidLevel > 0)
    {
        OnUltimateVoidPowerUsed.Broadcast(UltimateVoidPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Void Power Used: %.2f"), UltimateVoidPowerCost);
    }
    else
    {
        OnUltimateVoidPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Void Power Use Failed: System not active or insufficient level."));
    }
}

void UP01_VOID_ULTIMATE::PerformUltimateVoidAbility()
{
    if (bIsUltimateVoidActive && UltimateVoidLevel >= UltimateVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Ultimate Void Ability at Level %d!"), UltimateVoidLevel);
        OnUltimateVoidAbilityPerformed.Broadcast(UltimateVoidLevel);
        UseUltimateVoidPower();
        
        // Perform ultimate void ability based on level
        switch (UltimateVoidLevel / 20)
        {
            case 0:
                MasterUltimateVoid();
                break;
            case 1:
                AnnihilateUltimately();
                break;
            case 2:
                AchievePerfectVoidEmptiness();
                break;
            case 3:
                InduceConceptualUltimateOblivion();
                break;
            case 4:
            case 5:
                NegateUltimateExistence();
                break;
            default:
                NegateUltimateExistence();
                break;
        }
    }
    }
    else if (UltimateVoidLevel < UltimateVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Void Level too low to perform ability. Required: %.0f, Current: %d"), UltimateVoidThreshold, UltimateVoidLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Void is not active, cannot perform ability."));
    }
}

bool UP01_VOID_ULTIMATE::IsUltimateVoidActive() const
{
    return bIsUltimateVoidActive;
}

int32 UP01_VOID_ULTIMATE::GetUltimateVoidLevel() const
{
    return UltimateVoidLevel;
}

float UP01_VOID_ULTIMATE::GetUltimateVoidPowerCost() const
{
    return UltimateVoidPowerCost;
}

void UP01_VOID_ULTIMATE::MasterUltimateVoid()
{
    if (bIsUltimateVoidActive)
    {
        float VoidMasteryPower = VoidMastery * (UltimateVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Ultimate Void with power: %.2f"), VoidMasteryPower);
        // Apply ultimate void mastery effects
    }
}

void UP01_VOID_ULTIMATE::AnnihilateUltimately()
{
    if (bIsUltimateVoidActive)
    {
        float AnnihilationPower = UltimateAnnihilation * (UltimateVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Ultimately with power: %.2f"), AnnihilationPower);
        // Apply ultimate annihilation effects
    }
}

void UP01_VOID_ULTIMATE::AchievePerfectVoidEmptiness()
{
    if (bIsUltimateVoidActive)
    {
        float EmptinessPower = PerfectVoidEmptiness * (UltimateVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Perfect Void Emptiness with power: %.2f"), EmptinessPower);
        // Apply perfect void emptiness effects
    }
}

void UP01_VOID_ULTIMATE::InduceConceptualUltimateOblivion()
{
    if (bIsUltimateVoidActive)
    {
        float OblivionPower = ConceptualUltimateOblivion * (UltimateVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Conceptual Ultimate Oblivion with power: %.2f"), OblivionPower);
        // Apply conceptual ultimate oblivion effects
    }
}

void UP01_VOID_ULTIMATE::NegateUltimateExistence()
{
    if (bIsUltimateVoidActive)
    {
        float NegationPower = ExistenceUltimateNegation * (UltimateVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Ultimate Existence with power: %.2f"), NegationPower);
        // Apply ultimate existence negation effects
    }
}

bool UP01_VOID_ULTIMATE::CanActivateUltimateVoid() const
{
    return UltimateVoidLevel > 0;
}

void UP01_VOID_ULTIMATE::UpdateUltimateVoidStats()
{
    // Update ultimate void properties based on level
    VoidMastery = UltimateVoidLevel * 1.8f;
    UltimateAnnihilation = UltimateVoidLevel * 2.0f;
    PerfectVoidEmptiness = UltimateVoidLevel * 1.9f;
    ConceptualUltimateOblivion = UltimateVoidLevel * 1.7f;
    ExistenceUltimateNegation = UltimateVoidLevel * 2.1f;
}

void UP01_VOID_ULTIMATE::OnUltimateVoidStateChanged()
{
    // Handle state change effects
    if (bIsUltimateVoidActive)
    {
        // Apply ultimate void activation effects
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Void state changed to ACTIVE"));
    }
    else
    {
        // Remove ultimate void effects
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Void state changed to INACTIVE"));
    }
}
