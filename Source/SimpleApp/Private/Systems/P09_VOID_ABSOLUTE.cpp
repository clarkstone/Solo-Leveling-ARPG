#include "P09_VOID_ABSOLUTE.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP09_VOID_ABSOLUTE::UP09_VOID_ABSOLUTE()
{
    PrimaryComponentTick.bCanEverTick = false;
    AbsoluteVoidLevel = 0;
    MaxAbsoluteVoidLevel = 100;
    bIsAbsoluteVoidActive = false;
    AbsoluteVoidPowerCost = 50.0f;
    AbsoluteVoidThreshold = 50.0f;
    
    // Initialize absolute void properties
    AbsoluteVoidMastery = 0.0f;
    AbsoluteUltimateAnnihilation = 0.0f;
    AbsolutePerfectVoidEmptiness = 0.0f;
    AbsoluteConceptualUltimateOblivion = 0.0f;
    AbsoluteExistenceUltimateNegation = 0.0f;
}

void UP09_VOID_ABSOLUTE::BeginPlay()
{
    Super::BeginPlay();
    UpdateAbsoluteVoidStats();
}

void UP09_VOID_ABSOLUTE::ActivateAbsoluteVoid()
{
    if (!bIsAbsoluteVoidActive && CanActivateAbsoluteVoid())
    {
        bIsAbsoluteVoidActive = true;
        OnAbsoluteVoidActivated.Broadcast(AbsoluteVoidLevel);
        OnAbsoluteVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void System Activated at Level: %d"), AbsoluteVoidLevel);
    }
}

void UP09_VOID_ABSOLUTE::DeactivateAbsoluteVoid()
{
    if (bIsAbsoluteVoidActive)
    {
        bIsAbsoluteVoidActive = false;
        OnAbsoluteVoidDeactivated.Broadcast(AbsoluteVoidLevel);
        OnAbsoluteVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void System Deactivated."));
    }
}

void UP09_VOID_ABSOLUTE::SetAbsoluteVoidLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxAbsoluteVoidLevel)
    {
        int32 OldLevel = AbsoluteVoidLevel;
        AbsoluteVoidLevel = NewLevel;
        UpdateAbsoluteVoidStats();
        OnAbsoluteVoidLevelChanged.Broadcast(OldLevel, AbsoluteVoidLevel);
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void Level set to: %d"), AbsoluteVoidLevel);
        
        if (AbsoluteVoidLevel >= MaxAbsoluteVoidLevel)
        {
            OnAbsoluteVoidMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Absolute Void Max Level Reached!"));
        }
    }
}

void UP09_VOID_ABSOLUTE::UseAbsoluteVoidPower()
{
    if (bIsAbsoluteVoidActive && AbsoluteVoidLevel > 0)
    {
        OnAbsoluteVoidPowerUsed.Broadcast(AbsoluteVoidPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void Power Used: %.2f"), AbsoluteVoidPowerCost);
    }
    else
    {
        OnAbsoluteVoidPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void Power Use Failed: System not active or insufficient level."));
    }
}

void UP09_VOID_ABSOLUTE::PerformAbsoluteVoidAbility()
{
    if (bIsAbsoluteVoidActive && AbsoluteVoidLevel >= AbsoluteVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Absolute Void Ability at Level %d!"), AbsoluteVoidLevel);
        OnAbsoluteVoidAbilityPerformed.Broadcast(AbsoluteVoidLevel);
        UseAbsoluteVoidPower();
        
        // Perform absolute void ability based on level
        switch (AbsoluteVoidLevel / 20)
        {
            case 0:
                MasterAbsoluteVoid();
                break;
            case 1:
                AnnihilateAbsolutely();
                break;
            case 2:
                AchieveAbsolutePerfectVoidEmptiness();
                break;
            case 3:
                InduceAbsoluteConceptualUltimateOblivion();
                break;
            case 4:
            case 5:
                NegateAbsoluteUltimateExistence();
                break;
            default:
                NegateAbsoluteUltimateExistence();
                break;
        }
    }
    }
    else if (AbsoluteVoidLevel < AbsoluteVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void Level too low to perform ability. Required: %.0f, Current: %d"), AbsoluteVoidThreshold, AbsoluteVoidLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void is not active, cannot perform ability."));
    }
}

bool UP09_VOID_ABSOLUTE::IsAbsoluteVoidActive() const
{
    return bIsAbsoluteVoidActive;
}

int32 UP09_VOID_ABSOLUTE::GetAbsoluteVoidLevel() const
{
    return AbsoluteVoidLevel;
}

float UP09_VOID_ABSOLUTE::GetAbsoluteVoidPowerCost() const
{
    return AbsoluteVoidPowerCost;
}

void UP09_VOID_ABSOLUTE::MasterAbsoluteVoid()
{
    if (bIsAbsoluteVoidActive)
    {
        float MasteryPower = AbsoluteVoidMastery * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Absolute Void with power: %.2f"), MasteryPower);
        // Apply absolute void mastery effects
    }
}

void UP09_VOID_ABSOLUTE::AnnihilateAbsolutely()
{
    if (bIsAbsoluteVoidActive)
    {
        float AnnihilationPower = AbsoluteUltimateAnnihilation * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Absolutely with power: %.2f"), AnnihilationPower);
        // Apply absolute annihilation effects
    }
}

void UP09_VOID_ABSOLUTE::AchieveAbsolutePerfectVoidEmptiness()
{
    if (bIsAbsoluteVoidActive)
    {
        float EmptinessPower = AbsolutePerfectVoidEmptiness * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Absolute Perfect Void Emptiness with power: %.2f"), EmptinessPower);
        // Apply absolute perfect void emptiness effects
    }
}

void UP09_VOID_ABSOLUTE::InduceAbsoluteConceptualUltimateOblivion()
{
    if (bIsAbsoluteVoidActive)
    {
        float OblivionPower = AbsoluteConceptualUltimateOblivion * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Absolute Conceptual Ultimate Oblivion with power: %.2f"), OblivionPower);
        // Apply absolute conceptual ultimate oblivion effects
    }
}

void UP09_VOID_ABSOLUTE::NegateAbsoluteUltimateExistence()
{
    if (bIsAbsoluteVoidActive)
    {
        float NegationPower = AbsoluteExistenceUltimateNegation * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Absolute Ultimate Existence with power: %.2f"), NegationPower);
        // Apply absolute ultimate existence negation effects
    }
}

bool UP09_VOID_ABSOLUTE::CanActivateAbsoluteVoid() const
{
    return AbsoluteVoidLevel > 0;
}

void UP09_VOID_ABSOLUTE::UpdateAbsoluteVoidStats()
{
    // Update absolute void properties based on level
    AbsoluteVoidMastery = AbsoluteVoidLevel * 5.0f;
    AbsoluteUltimateAnnihilation = AbsoluteVoidLevel * 5.2f;
    AbsolutePerfectVoidEmptiness = AbsoluteVoidLevel * 5.1f;
    AbsoluteConceptualUltimateOblivion = AbsoluteVoidLevel * 4.9f;
    AbsoluteExistenceUltimateNegation = AbsoluteVoidLevel * 5.3f;
}

void UP09_VOID_ABSOLUTE::OnAbsoluteVoidStateChanged()
{
    // Handle state change effects
    if (bIsAbsoluteVoidActive)
    {
        // Apply absolute void activation effects
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void state changed to ACTIVE"));
    }
    else
    {
        // Remove absolute void effects
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void state changed to INACTIVE"));
    }
}
