#include "P26_VOID_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP26_VOID_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::UP26_VOID_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL()
{
    PrimaryComponentTick.bCanEverTick = false;
    OmegaOmegaInfiniteEternalVoidLevel = 0;
    MaxOmegaOmegaInfiniteEternalVoidLevel = 100;
    bIsOmegaOmegaInfiniteEternalVoidActive = false;
    OmegaOmegaInfiniteEternalVoidPowerCost = 135.0f;
    OmegaOmegaInfiniteEternalVoidThreshold = 135.0f;
    
    // Initialize omega omega omega omega omega omega omega omega omega omega omega infinite eternal void properties
    OmegaOmegaInfiniteEternalVoidMastery = 0.0f;
    OmegaOmegaInfiniteEternalUltimateAnnihilation = 0.0f;
    OmegaOmegaInfiniteEternalPerfectVoidEmptiness = 0.0f;
    OmegaOmegaInfiniteEternalConceptualUltimateOblivion = 0.0f;
    OmegaOmegaInfiniteEternalExistenceUltimateNegation = 0.0f;
}

void UP26_VOID_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::BeginPlay()
{
    Super::BeginPlay();
    UpdateOmegaOmegaInfiniteEternalVoidStats();
}

void UP26_VOID_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::ActivateOmegaOmegaInfiniteEternalVoid()
{
    if (!bIsOmegaOmegaInfiniteEternalVoidActive && CanActivateOmegaOmegaInfiniteEternalVoid())
    {
        bIsOmegaOmegaInfiniteEternalVoidActive = true;
        OnOmegaOmegaInfiniteEternalVoidActivated.Broadcast(OmegaOmegaInfiniteEternalVoidLevel);
        OnOmegaOmegaInfiniteEternalVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Void System Activated at Level: %d"), OmegaOmegaInfiniteEternalVoidLevel);
    }
}

void UP26_VOID_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::DeactivateOmegaOmegaInfiniteEternalVoid()
{
    if (bIsOmegaInfiniteEternalVoidActive)
    {
        bIsOmegaInfiniteEternalVoidActive = false;
        OnOmegaOmegaInfiniteEternalVoidDeactivated.Broadcast(OmegaOmegaInfiniteEternalVoidLevel);
        OnOmegaOmegaInfiniteEternalVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Void System Deactivated."));
    }
}

void UP26_VOID_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::SetOmegaOmegaInfiniteEternalVoidLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxOmegaOmegaInfiniteEternalVoidLevel)
    {
        int32 OldLevel = OmegaOmegaInfiniteEternalVoidLevel;
        OmegaOmegaInfiniteEternalVoidLevel = NewLevel;
        UpdateOmegaOmegaInfiniteEternalVoidStats();
        OnOmegaOmegaInfiniteEternalVoidLevelChanged.Broadcast(OldLevel, OmegaOmegaInfiniteEternalVoidLevel);
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Void Level set to: %d"), OmegaOmegaInfiniteEternalVoidLevel);
        
        if (OmegaOmegaInfiniteEternalVoidLevel >= MaxOmegaOmegaInfiniteEternalVoidLevel)
        {
            OnOmegaOmegaInfiniteEternalVoidMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Void Max Level Reached!"));
        }
    }
}

void UP26_VOID_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::UseOmegaOmegaInfiniteEternalVoidPower()
{
    if (bIsOmegaInfiniteEternalVoidActive && OmegaOmegaInfiniteEternalVoidLevel > 0)
    {
        OnOmegaOmegaInfiniteEternalVoidPowerUsed.Broadcast(OmegaOmegaInfiniteEternalVoidPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Void Power Used: %.2f"), OmegaOmegaInfiniteEternalVoidPowerCost);
    }
    else
    {
        OnOmegaOmegaInfiniteEternalVoidPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Void Power Use Failed: System not active or insufficient level."));
    }
}

void UP26_VOID_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::PerformOmegaOmegaInfiniteEternalVoidAbility()
{
    if (bIsOmegaInfiniteEternalVoidActive && OmegaOmegaInfiniteEternalVoidLevel >= OmegaOmegaInfiniteEternalVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Omega Omega Infinite Eternal Void Ability at Level %d!"), OmegaOmegaInfiniteEternalVoidLevel);
        OnOmegaOmegaInfiniteEternalVoidAbilityPerformed.Broadcast(OmegaOmegaInfiniteEternalVoidLevel);
        UseOmegaOmegaInfiniteEternalVoidPower();
        
        // Perform omega omega omega omega omega omega omega omega infinite eternal void ability based on level
        switch (OmegaOmegaInfiniteEternalVoidLevel / 20)
        {
            case 0:
                MasterOmegaOmegaInfiniteEternalVoid();
                break;
            case 1:
                AnnihilateOmegaOmegaInfiniteEternally();
                break;
            case 2:
                AchieveOmegaOmegaInfiniteEternalPerfectVoidEmptiness();
                break;
            case 3:
                InduceOmegaOmegaInfiniteEternalConceptualUltimateOblivion();
                break;
            case 4:
            case 5:
                NegateOmegaOmegaInfiniteEternalUltimateExistence();
                break;
            default:
                NegateOmegaOmegaInfiniteEternalUltimateExistence();
                break;
        }
    }
    }
    else if (OmegaOmegaInfiniteEternalVoidLevel < OmegaOmegaInfiniteEternalVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Void Level too low to perform ability. Required: %.0f, Current: %d"), OmegaOmegaInfiniteEternalVoidThreshold, OmegaOmegaInfiniteEternalVoidLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Void is not active, cannot perform ability."));
    }
}

bool UP26_VOID_OMEGA_OMEGA_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::IsOmegaInfiniteEternalVoidActive() const
{
    return bIsOmegaInfiniteEternalVoidActive;
}

int32 UP26_VOID_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::GetOmegaOmegaInfiniteEternalVoidLevel() const
{
    return OmegaOmegaInfiniteEternalVoidLevel;
}

float UP26_VOID_OMEGA_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::GetOmegaOmegaInfiniteEternalVoidPowerCost() const
{
    return OmegaOmegaInfiniteEternalVoidPowerCost;
}

void UP26_VOID_OMEGA_OMEGA_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::MasterOmegaOmegaInfiniteEternalVoid()
{
    if (bIsOmegaInfiniteEternalVoidActive)
    {
        float MasteryPower = OmegaOmegaInfiniteEternalVoidMastery * (OmegaOmegaInfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Omega Omega Infinite Eternal Void with power: %.2f"), MasteryPower);
        // Apply omega omega omega omega omega omega omega omega infinite void mastery effects
    }
}

void UP26_VOID_OMEGA_OMEGA_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::AnnihilateOmegaOmegaInfiniteEternally()
{
    if (bIsOmegaInfiniteEternalVoidActive)
    {
        float AnnihilationPower = OmegaOmegaInfiniteEternalUltimateAnnihilation * (OmegaOmegaInfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Omega Omega Infinite Eternally with power: %.2f"), AnnihilationPower);
        // Apply omega omega omega omega omega omega omega omega infinite eternal annihilation effects
    }
}

void UP26_VOID_OMEGA_OMEGA_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::AchieveOmegaOmegaInfiniteEternalPerfectVoidEmptiness()
{
    if (bIsOmegaInfiniteEternalVoidActive)
    {
        float EmptinessPower = OmegaOmegaInfiniteEternalPerfectVoidEmptiness * (OmegaOmegaInfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Omega Infinite Eternal Perfect Void Emptiness with power: %.2f"), EmptinessPower);
        // Apply omega omega omega omega omega omega omega omega infinite eternal perfect void emptiness effects
    }
}

void UP26_VOID_OMEGA_OMEGA_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::InduceOmegaOmegaInfiniteEternalConceptualUltimateOblivion()
{
    if (bIsOmegaInfiniteEternalVoidActive)
    {
        float OblivionPower = OmegaOmegaInfiniteEternalConceptualUltimateOblivion * (OmegaOmegaInfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Omega Omega Infinite Eternal Conceptual Ultimate Oblivion with power: %.2f"), OblivionPower);
        // Apply omega omega omega omega omega omega omega omega infinite eternal conceptual ultimate oblivion effects
    }
}

void UP26_VOID_OMEGA_OMEGA_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::NegateOmegaOmegaInfiniteEternalUltimateExistence()
{
    if (bIsOmegaInfiniteEternalVoidActive)
    {
        float NegationPower = OmegaOmegaInfiniteEternalExistenceUltimateNegation * (OmegaOmegaInfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Omega Omega Omega Omega Omega Infinite Eternal Ultimate Existence with power: %.2f"), NegationPower);
        // Apply omega omega omega omega omega omega omega omega infinite eternal ultimate existence negation effects
    }
}

bool UP26_VOID_OMEGA_OMEGA_OMEGA_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::CanActivateOmegaOmegaInfiniteEternalVoid() const
{
    return OmegaOmegaInfiniteEternalVoidLevel > 0;
}

void UP26_VOID_OMEGA_OMEGA_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::UpdateOmegaOmegaInfiniteEternalVoidStats()
{
    // Update omega omega omega omega omega omega omega omega infinite eternal void properties based on level
    OmegaOmegaInfiniteEternalVoidMastery = OmegaOmegaInfiniteEternalVoidLevel * 13.5f;
    OmegaOmegaInfiniteEternalUltimateAnnihilation = OmegaOmegaInfiniteEternalVoidLevel * 13.7f;
    OmegaOmegaInfiniteEternalPerfectVoidEmptiness = OmegaOmegaInfiniteEternalVoidLevel * 13.6f;
    OmegaOmegaInfiniteEternalConceptualUltimateOblivion = OmegaOmegaInfiniteEternalVoidLevel * 13.4f;
    OmegaOmegaInfiniteEternalExistenceUltimateNegation = OmegaOmegaInfiniteEternalVoidLevel * 13.8f;
}

void UP26_VOID_OMEGA_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::OnOmegaOmegaInfiniteEternalVoidStateChanged()
{
    // Handle state change effects
    if (bIsOmegaInfiniteEternalVoidActive)
    {
        // Apply omega omega omega omega omega omega omega omega infinite void activation effects
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Void state changed to ACTIVE"));
    }
    else
    {
        // Remove omega omega omega omega omega omega omega omega infinite void effects
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Void state changed to INACTIVE"));
    }
}
