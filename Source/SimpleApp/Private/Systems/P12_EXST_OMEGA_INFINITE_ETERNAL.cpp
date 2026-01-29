#include "P12_EXST_OMEGA_INFINITE_ETERNAL.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP12_EXST_OMEGA_INFINITE_ETERNAL::UP12_EXST_OMEGA_INFINITE_ETERNAL()
{
    PrimaryComponentTick.bCanEverTick = false;
    OmegaInfiniteEternalExistenceLevel = 0;
    MaxOmegaInfiniteEternalExistenceLevel = 100;
    bIsOmegaInfiniteEternalExistenceActive = false;
    OmegaInfiniteEternalExistencePowerCost = 65.0f;
    OmegaInfiniteEternalExistenceThreshold = 65.0f;
    
    // Initialize omega infinite eternal existence properties
    OmegaInfiniteEternalLifeForce = 0.0f;
    OmegaInfiniteEternalPerpetuation = 0.0f;
    OmegaInfiniteEternalInfiniteContinuum = 0.0f;
    OmegaInfiniteEternalTimelessPerpetuation = 0.0f;
    OmegaInfiniteEternalSelfSufficiency = 0.0f;
}

void UP12_EXST_OMEGA_INFINITE_ETERNAL::BeginPlay()
{
    Super::BeginPlay();
    UpdateOmegaInfiniteEternalExistenceStats();
}

void UP12_EXST_OMEGA_INFINITE_ETERNAL::ActivateOmegaInfiniteEternalExistence()
{
    if (!bIsOmegaInfiniteEternalExistenceActive && CanActivateOmegaInfiniteEternalExistence())
    {
        bIsOmegaInfiniteEternalExistenceActive = true;
        OnOmegaInfiniteEternalExistenceActivated.Broadcast(OmegaInfiniteEternalExistenceLevel);
        OnOmegaInfiniteEternalExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Existence System Activated at Level: %d"), OmegaInfiniteEternalExistenceLevel);
    }
}

void UP12_EXST_OMEGA_INFINITE_ETERNAL::DeactivateOmegaInfiniteEternalExistence()
{
    if (bIsOmegaInfiniteEternalExistenceActive)
    {
        bIsOmegaInfiniteEternalExistenceActive = false;
        OnOmegaInfiniteEternalExistenceDeactivated.Broadcast(OmegaInfiniteEternalExistenceLevel);
        OnOmegaInfiniteEternalExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Existence System Deactivated."));
    }
}

void UP12_EXST_OMEGA_INFINITE_ETERNAL::SetOmegaInfiniteEternalExistenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxOmegaInfiniteEternalExistenceLevel)
    {
        int32 OldLevel = OmegaInfiniteEternalExistenceLevel;
        OmegaInfiniteEternalExistenceLevel = NewLevel;
        UpdateOmegaInfiniteEternalExistenceStats();
        OnOmegaInfiniteEternalExistenceLevelChanged.Broadcast(OldLevel, OmegaInfiniteEternalExistenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Existence Level set to: %d"), OmegaInfiniteEternalExistenceLevel);
        
        if (OmegaInfiniteEternalExistenceLevel >= MaxOmegaInfiniteEternalExistenceLevel)
        {
            OnOmegaInfiniteEternalExistenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Existence Max Level Reached!"));
        }
    }
}

void UP12_EXST_OMEGA_INFINITE_ETERNAL::UseOmegaInfiniteEternalExistencePower()
{
    if (bIsOmegaInfiniteEternalExistenceActive && OmegaInfiniteEternalExistenceLevel > 0)
    {
        OnOmegaInfiniteEternalExistencePowerUsed.Broadcast(OmegaInfiniteEternalExistencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Existence Power Used: %.2f"), OmegaInfiniteEternalExistencePowerCost);
    }
    else
    {
        OnOmegaInfiniteEternalExistencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Existence Power Use Failed: System not active or insufficient level."));
    }
}

void UP12_EXST_OMEGA_INFINITE_ETERNAL::PerformOmegaInfiniteEternalExistenceAbility()
{
    if (bIsOmegaInfiniteEternalExistenceActive && OmegaInfiniteEternalExistenceLevel >= OmegaInfiniteEternalExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Omega Infinite Eternal Existence Ability at Level %d!"), OmegaInfiniteEternalExistenceLevel);
        OnOmegaInfiniteEternalExistenceAbilityPerformed.Broadcast(OmegaInfiniteEternalExistenceLevel);
        UseOmegaInfiniteEternalExistencePower();
        
        // Perform omega infinite eternal existence ability based on level
        switch (OmegaInfiniteEternalExistenceLevel / 20)
        {
            case 0:
                ChannelOmegaInfiniteEternalLifeForce();
                break;
            case 1:
                AchieveOmegaInfiniteEternalPerpetuation();
                break;
            case 2:
                MaintainOmegaInfiniteEternalInfiniteContinuum();
                break;
            case 3:
                PerpetuateOmegaInfiniteEternalTimelessly();
                break;
            case 4:
            case 5:
                AchieveOmegaInfiniteEternalSelfSufficiency();
                break;
            default:
                AchieveOmegaInfiniteEternalSelfSufficiency();
                break;
        }
    }
    }
    else if (OmegaInfiniteEternalExistenceLevel < OmegaInfiniteEternalExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Existence Level too low to perform ability. Required: %.0f, Current: %d"), OmegaInfiniteEternalExistenceThreshold, OmegaInfiniteEternalExistenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Existence is not active, cannot perform ability."));
    }
}

bool UP12_EXST_OMEGA_INFINITE_ETERNAL::IsOmegaInfiniteEternalExistenceActive() const
{
    return bIsOmegaInfiniteEternalExistenceActive;
}

int32 UP12_EXST_OMEGA_INFINITE_ETERNAL::GetOmegaInfiniteEternalExistenceLevel() const
{
    return OmegaInfiniteEternalExistenceLevel;
}

float UP12_EXST_OMEGA_INFINITE_ETERNAL::GetOmegaInfiniteEternalExistencePowerCost() const
{
    return OmegaInfiniteEternalExistencePowerCost;
}

void UP12_EXST_OMEGA_INFINITE_ETERNAL::ChannelOmegaInfiniteEternalLifeForce()
{
    if (bIsOmegaInfiniteEternalExistenceActive)
    {
        float LifeForcePower = OmegaInfiniteEternalLifeForce * (OmegaInfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Omega Infinite Eternal Life Force with power: %.2f"), LifeForcePower);
        // Apply omega infinite eternal life force effects
    }
}

void UP12_EXST_OMEGA_INFINITE_ETERNAL::AchieveOmegaInfiniteEternalPerpetuation()
{
    if (bIsOmegaInfiniteEternalExistenceActive)
    {
        float PerpetuationPower = OmegaInfiniteEternalPerpetuation * (OmegaInfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Infinite Eternal Perpetuation with power: %.2f"), PerpetuationPower);
        // Apply omega infinite eternal perpetuation effects
    }
}

void UP12_EXST_OMEGA_INFINITE_ETERNAL::MaintainOmegaInfiniteEternalInfiniteContinuum()
{
    if (bIsOmegaInfiniteEternalExistenceActive)
    {
        float ContinuumPower = OmegaInfiniteEternalInfiniteContinuum * (OmegaInfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Maintaining Omega Infinite Eternal Infinite Continuum with power: %.2f"), ContinuumPower);
        // Apply omega infinite eternal infinite continuum effects
    }
}

void UP12_EXST_OMEGA_INFINITE_ETERNAL::PerpetuateOmegaInfiniteEternalTimelessly()
{
    if (bIsOmegaInfiniteEternalExistenceActive)
    {
        float PerpetuationPower = OmegaInfiniteEternalTimelessPerpetuation * (OmegaInfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Perpetuating Omega Infinite Eternal Timelessly with power: %.2f"), PerpetuationPower);
        // Apply omega infinite eternal timeless perpetuation effects
    }
}

void UP12_EXST_OMEGA_INFINITE_ETERNAL::AchieveOmegaInfiniteEternalSelfSufficiency()
{
    if (bIsOmegaInfiniteEternalExistenceActive)
    {
        float SufficiencyPower = OmegaInfiniteEternalSelfSufficiency * (OmegaInfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Infinite Eternal Self-Sufficiency with power: %.2f"), SufficiencyPower);
        // Apply omega infinite eternal self-sufficiency effects
    }
}

bool UP12_EXST_OMEGA_INFINITE_ETERNAL::CanActivateOmegaInfiniteEternalExistence() const
{
    return OmegaInfiniteEternalExistenceLevel > 0;
}

void UP12_EXST_OMEGA_INFINITE_ETERNAL::UpdateOmegaInfiniteEternalExistenceStats()
{
    // Update omega infinite eternal existence properties based on level
    OmegaInfiniteEternalLifeForce = OmegaInfiniteEternalExistenceLevel * 6.0f;
    OmegaInfiniteEternalPerpetuation = OmegaInfiniteEternalExistenceLevel * 5.8f;
    OmegaInfiniteEternalInfiniteContinuum = OmegaInfiniteEternalExistenceLevel * 5.9f;
    OmegaInfiniteEternalTimelessPerpetuation = OmegaInfiniteEternalExistenceLevel * 5.7f;
    OmegaInfiniteEternalSelfSufficiency = OmegaInfiniteEternalExistenceLevel * 6.1f;
}

void UP12_EXST_OMEGA_INFINITE_ETERNAL::OnOmegaInfiniteEternalExistenceStateChanged()
{
    // Handle state change effects
    if (bIsOmegaInfiniteEternalExistenceActive)
    {
        // Apply omega infinite eternal existence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Existence state changed to ACTIVE"));
    }
    else
    {
        // Remove omega infinite eternal existence effects
        UE_LOG(LogTemp, Warning, TEXT("Omega Infinite Eternal Existence state changed to INACTIVE"));
    }
}
