#include "P12_VOID_OMEGA_INFINITE_ETERNAL.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP12_VOID_OMEGA_INFINITE_ETERNAL::UP12_VOID_OMEGA_INFINITE_ETERNAL()
{
    PrimaryComponentTick.bCanEverTick = false;
    OmegaInfiniteEternalVoidLevel = 0;
    MaxOmegaInfiniteEternalVoidLevel = 100;
    bIsOmegaInfiniteEternalVoidActive = false;
    OmegaInfiniteEternalVoidPowerCost = 65.0f;
    OmegaInfiniteEternalVoidThreshold = 65.0f;
    
    // Initialize omega infinite eternal void properties
    OmegaInfiniteEternalVoidMastery = 0.0f;
    OmegaInfiniteEternalUltimateAnnihilation = 0.0f;
    OmegaInfiniteEternalPerfectVoidEmptiness = 0.0f;
    OmegaInfiniteEternalConceptualUltimateOblivion = 0.0f;
    OmegaInfiniteEternalExistenceUltimateNegation = 0.0f;
}

void UP12_VOID_OMEGA_INFINITE_ETERNAL::BeginPlay()
{
    Super::BeginPlay();
    UpdateOmegaInfiniteEternalVoidStats();
}

void UP12_VOID_OMEGA_INFINITE_ETERNAL::ActivateOmegaInfiniteEternalVoid()
{
    if (!bIsOmegaInfiniteEternalVoidActive && CanActivateOmegaInfiniteEternalVoid())
    {
        bIsOmegaInfiniteEternalVoidActive = true;
        OnOmegaInfiniteEternalVoidActivated.Broadcast(OmegaInfiniteEternalVoidLevel);
        OnOmegaInfiniteEternalVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Void System Activated at Level: %d"), OmegaInfiniteEternalVoidLevel);
    }
}

void UP12_VOID_OMEGA_INFINITE_ETERNAL::DeactivateOmegaInfiniteEternalVoid()
{
    if (bIsOmegaInfiniteEternalVoidActive)
    {
        bIsOmegaInfiniteEternalVoidActive = false;
        OnOmegaInfiniteEternalVoidDeactivated.Broadcast(OmegaInfiniteEternalVoidLevel);
        OnOmegaInfiniteEternalVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Void System Deactivated."));
    }
}

void UP12_VOID_OMEGA_INFINITE_ETERNAL::SetOmegaInfiniteEternalVoidLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxOmegaInfiniteEternalVoidLevel)
    {
        int32 OldLevel = OmegaInfiniteEternalVoidLevel;
        OmegaInfiniteEternalVoidLevel = NewLevel;
        UpdateOmegaInfiniteEternalVoidStats();
        OnOmegaInfiniteEternalVoidLevelChanged.Broadcast(OldLevel, OmegaInfiniteEternalVoidLevel);
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Void Level set to: %d"), OmegaInfiniteEternalVoidLevel);
        
        if (OmegaInfiniteEternalVoidLevel >= MaxOmegaInfiniteEternalVoidLevel)
        {
            OnOmegaInfiniteEternalVoidMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Void Max Level Reached!"));
        }
    }
}

void UP12_VOID_OMEGA_INFINITE_ETERNAL::UseOmegaInfiniteEternalVoidPower()
{
    if (bIsOmegaInfiniteEternalVoidActive && OmegaInfiniteEternalVoidLevel > 0)
    {
        OnOmegaInfiniteEternalVoidPowerUsed.Broadcast(OmegaInfiniteEternalVoidPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Void Power Used: %.2f"), OmegaInfiniteEternalVoidPowerCost);
    }
    else
    {
        OnOmegaInfiniteEternalVoidPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Void Power Use Failed: System not active or insufficient level."));
    }
}

void UP12_VOID_OMEGA_INFINITE_ETERNAL::PerformOmegaInfiniteEternalVoidAbility()
{
    if (bIsOmegaInfiniteEternalVoidActive && OmegaInfiniteEternalVoidLevel >= OmegaInfiniteEternalVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Omega Infinite Eternal Void Ability at Level %d!"), OmegaInfiniteEternalVoidLevel);
        OnOmegaInfiniteEternalVoidAbilityPerformed.Broadcast(OmegaInfiniteEternalVoidLevel);
        UseOmegaInfiniteEternalVoidPower();
        
        // Perform omega infinite eternal void ability based on level
        switch (OmegaInfiniteEternalVoidLevel / 20)
        {
            case 0:
                MasterOmegaInfiniteEternalVoid();
                break;
            case 1:
                AnnihilateOmegaInfiniteEternally();
                break;
            case 2:
                AchieveOmegaInfiniteEternalPerfectVoidEmptiness();
                break;
            case 3:
                InduceOmegaInfiniteEternalConceptualUltimateOblivion();
                break;
            case 4:
            case 5:
                NegateOmegaInfiniteEternalUltimateExistence();
                break;
            default:
                NegateOmegaInfiniteEternalUltimateExistence();
                break;
        }
    }
    }
    else if (OmegaInfiniteEternalVoidLevel < OmegaInfiniteEternalVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Void Level too low to perform ability. Required: %.0f, Current: %d"), OmegaInfiniteEternalVoidThreshold, OmegaInfiniteEternalVoidLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Void is not active, cannot perform ability."));
    }
}

bool UP12_VOID_OMEGA_INFINITE_ETERNAL::IsOmegaInfiniteEternalVoidActive() const
{
    return bIsOmegaInfiniteEternalVoidActive;
}

int32 UP12_VOID_OMEGA_INFINITE_ETERNAL::GetOmegaInfiniteEternalVoidLevel() const
{
    return OmegaInfiniteEternalVoidLevel;
}

float UP12_VOID_OMEGA_INFINITE_ETERNAL::GetOmegaInfiniteEternalVoidPowerCost() const
{
    return OmegaInfiniteEternalVoidPowerCost;
}

void UP12_VOID_OMEGA_INFINITE_ETERNAL::MasterOmegaInfiniteEternalVoid()
{
    if (bIsOmegaInfiniteEternalVoidActive)
    {
        float MasteryPower = OmegaInfiniteEternalVoidMastery * (OmegaInfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Omega Infinite Eternal Void with power: %.2f"), MasteryPower);
        // Apply omega infinite eternal void mastery effects
    }
}

void UP12_VOID_OMEGA_INFINITE_ETERNAL::AnnihilateOmegaInfiniteEternally()
{
    if (bIsOmegaInfiniteEternalVoidActive)
    {
        float AnnihilationPower = OmegaInfiniteEternalUltimateAnnihilation * (OmegaInfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Omega Infinite Eternally with power: %.2f"), AnnihilationPower);
        // Apply omega infinite eternal annihilation effects
    }
}

void UP12_VOID_OMEGA_INFINITE_ETERNAL::AchieveOmegaInfiniteEternalPerfectVoidEmptiness()
{
    if (bIsOmegaInfiniteEternalVoidActive)
    {
        float EmptinessPower = OmegaInfiniteEternalPerfectVoidEmptiness * (OmegaInfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Infinite Eternal Perfect Void Emptiness with power: %.2f"), EmptinessPower);
        // Apply omega infinite eternal perfect void emptiness effects
    }
}

void UP12_VOID_OMEGA_INFINITE_ETERNAL::InduceOmegaInfiniteEternalConceptualUltimateOblivion()
{
    if (bIsOmegaInfiniteEternalVoidActive)
    {
        float OblivionPower = OmegaInfiniteEternalConceptualUltimateOblivion * (OmegaInfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Omega Infinite Eternal Conceptual Ultimate Oblivion with power: %.2f"), OblivionPower);
        // Apply omega infinite eternal conceptual ultimate oblivion effects
    }
}

void UP12_VOID_OMEGA_INFINITE_ETERNAL::NegateOmegaInfiniteEternalUltimateExistence()
{
    if (bIsOmegaInfiniteEternalVoidActive)
    {
        float NegationPower = OmegaInfiniteEternalExistenceUltimateNegation * (OmegaInfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Omega Infinite Eternal Ultimate Existence with power: %.2f"), NegationPower);
        // Apply omega infinite eternal ultimate existence negation effects
    }
}

bool UP12_VOID_OMEGA_INFINITE_ETERNAL::CanActivateOmegaInfiniteEternalVoid() const
{
    return OmegaInfiniteEternalVoidLevel > 0;
}

void UP12_VOID_OMEGA_INFINITE_ETERNAL::UpdateOmegaInfiniteEternalVoidStats()
{
    // Update omega infinite eternal void properties based on level
    OmegaInfiniteEternalVoidMastery = OmegaInfiniteEternalVoidLevel * 6.5f;
    OmegaInfiniteEternalUltimateAnnihilation = OmegaInfiniteEternalVoidLevel * 6.7f;
    OmegaInfiniteEternalPerfectVoidEmptiness = OmegaInfiniteEternalVoidLevel * 6.6f;
    OmegaInfiniteEternalConceptualUltimateOblivion = OmegaInfiniteEternalVoidLevel * 6.4f;
    OmegaInfiniteEternalExistenceUltimateNegation = OmegaInfiniteEternalVoidLevel * 6.8f;
}

void UP12_VOID_OMEGA_INFINITE_ETERNAL::OnOmegaInfiniteEternalVoidStateChanged()
{
    // Handle state change effects
    if (bIsOmegaInfiniteEternalVoidActive)
    {
        // Apply omega infinite eternal void activation effects
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Void state changed to ACTIVE"));
    }
    else
    {
        // Remove omega infinite eternal void effects
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Void state changed to INACTIVE"));
    }
}
