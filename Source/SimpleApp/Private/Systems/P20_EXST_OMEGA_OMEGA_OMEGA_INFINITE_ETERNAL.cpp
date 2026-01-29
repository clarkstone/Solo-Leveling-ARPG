#include "P20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL()
{
    PrimaryComponentTick.bCanEverTick = false;
    OmegaOmegaInfiniteEternalExistenceLevel = 0;
    MaxOmegaOmegaInfiniteEternalExistenceLevel = 100;
    bIsOmegaOmegaInfiniteEternalExistenceActive = false;
    OmegaOmegaInfiniteEternalExistencePowerCost = 105.0f;
    OmegaOmegaInfiniteEternalExistenceThreshold = 105.0f;
    
    // Initialize omega omega infinite eternal existence properties
    OmegaOmegaInfiniteEternalLifeForce = 0.0f;
    OmegaOmegaInfiniteEternalPerpetuation = 0.0f;
    OmegaOmegaInfiniteEternalInfiniteContinuum = 0.0f;
    OmegaOmegaInfiniteEternalTimelessPerpetuation = 0.0f;
    OmegaOmegaInfiniteEternalSelfSufficiency = 0.0f;
}

void UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::BeginPlay()
{
    Super::BeginPlay();
    UpdateOmegaOmegaInfiniteEternalExistenceStats();
}

void UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::ActivateOmegaOmegaInfiniteEternalExistence()
{
    if (!bIsOmegaInfiniteEternalExistenceActive && CanActivateOmegaOmegaInfiniteEternalExistence())
    {
        bIsOmegaInfiniteEternalExistenceActive = true;
        OnOmegaOmegaInfiniteEternalExistenceActivated.Broadcast(OmegaOmegaInfiniteEternalExistenceLevel);
        OnOmegaOmegaInfiniteEternalExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Existence System Activated at Level: %d"), OmegaOmegaInfiniteEternalExistenceLevel);
    }
}

void UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::DeactivateOmegaOmegaInfiniteEternalExistence()
{
    if (bIsOmegaInfiniteEternalExistenceActive)
    {
        bIsOmegaInfiniteEternalExistenceActive = false;
        OnOmegaOmegaInfiniteEternalExistenceDeactivated.Broadcast(OmegaOmegaInfiniteEternalExistenceLevel);
        OnOmegaOmegaInfiniteEternalExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Existence System Deactivated."));
    }
}

void UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::SetOmegaOmegaInfiniteEternalExistenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxOmegaOmegaInfiniteEternalExistenceLevel)
    {
        int32 OldLevel = OmegaOmegaInfiniteEternalExistenceLevel;
        OmegaOmegaInfiniteEternalExistenceLevel = NewLevel;
        UpdateOmegaOmegaInfiniteEternalExistenceStats();
        OnOmegaOmegaInfiniteEternalExistenceLevelChanged.Broadcast(OldLevel, OmegaOmegaInfiniteEternalExistenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Existence Level set to: %d"), OmegaOmegaInfiniteEternalExistenceLevel);
        
        if (OmegaOmegaInfiniteEternalExistenceLevel >= MaxOmegaOmegaInfiniteEternalExistenceLevel)
        {
            OnOmegaOmegaInfiniteEternalExistenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Existence Max Level Reached!"));
        }
    }
}

void UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::UseOmegaOmegaInfiniteEternalExistencePower()
{
    if (bIsOmegaInfiniteEternalExistenceActive && OmegaOmegaInfiniteEternalExistenceLevel > 0)
    {
        OnOmegaOmegaInfiniteEternalExistencePowerUsed.Broadcast(OmegaOmegaInfiniteEternalExistencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Existence Power Used: %.2f"), OmegaOmegaInfiniteEternalExistencePowerCost);
    }
    else
    {
        OnOmegaOmegaInfiniteEternalExistencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Existence Power Use Failed: System not active or insufficient level."));
    }
}

void UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::PerformOmegaOmegaInfiniteEternalExistenceAbility()
{
    if (bIsOmegaInfiniteEternalExistenceActive && OmegaOmegaInfiniteEternalExistenceLevel >= OmegaOmegaInfiniteEternalExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Omega Omega Omega Infinite Eternal Existence Ability at Level %d!"), OmegaOmegaInfiniteEternalExistenceLevel);
        OnOmegaOmegaInfiniteEternalExistenceAbilityPerformed.Broadcast(OmegaOmegaInfiniteEternalExistenceLevel);
        UseOmegaOmegaInfiniteEternalExistencePower();
        
        // Perform omega omega infinite eternal existence ability based on level
        switch (OmegaOmegaInfiniteEternalExistenceLevel / 20)
        {
            case 0:
                ChannelOmegaOmegaInfiniteEternalLifeForce();
                break;
            case 1:
                AchieveOmegaOmegaInfiniteEternalPerpetuation();
                break;
            case 2:
                MaintainOmegaOmegaInfiniteEternalInfiniteContinuum();
                break;
            case 3:
                PerpetuateOmegaOmegaInfiniteEternalTimelessly();
                break;
            case 4:
            case 5:
                AchieveOmegaOmegaInfiniteEternalSelfSufficiency();
                break;
            default:
                AchieveOmegaOmegaInfiniteEternalSelfSufficiency();
                break;
        }
    }
    }
    else if (OmegaOmegaInfiniteEternalExistenceLevel < OmegaOmegaInfiniteEternalExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Existence Level too low to perform ability. Required: %.0f, Current: %d"), OmegaOmegaInfiniteEternalExistenceThreshold, OmegaOmegaInfiniteEternalExistenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Existence is not active, cannot perform ability."));
    }
}

bool UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::IsOmegaInfiniteEternalExistenceActive() const
{
    return bIsOmegaInfiniteEternalExistenceActive;
}

int32 UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::GetOmegaOmegaInfiniteEternalExistenceLevel() const
{
    return OmegaOmegaInfiniteEternalExistenceLevel;
}

float UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::GetOmegaOmegaInfiniteEternalExistencePowerCost() const
{
    return OmegaOmegaInfiniteEternalExistencePowerCost;
}

void UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::ChannelOmegaOmegaInfiniteEternalLifeForce()
{
    if (bIsOmegaInfiniteEternalExistenceActive)
    {
        float LifeForcePower = OmegaOmegaInfiniteEternalLifeForce * (OmegaOmegaInfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Omega Omega Infinite Eternal Life Force with power: %.2f"), LifeForcePower);
        // Apply omega omega infinite eternal life force effects
    }
}

void UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::AchieveOmegaInfiniteEternalPerpetuation()
{
    if (bIsOmegaInfiniteEternalExistenceActive)
    {
        float PerpetuationPower = OmegaOmegaInfiniteEternalPerpetuation * (OmegaOmegaInfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Omega Infinite Eternal Perpetuation with power: %.2f"), PerpetuationPower);
        // Apply omega omega infinite eternal perpetuation effects
    }
}

void UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::MaintainOmegaOmegaInfiniteEternalInfiniteContinuum()
{
    if (bIsOmegaInfiniteEternalExistenceActive)
    {
        float ContinuumPower = OmegaOmegaInfiniteEternalInfiniteContinuum * (OmegaOmegaInfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Maintaining Omega Omega Infinite Eternal Infinite Continuum with power: %.2f"), ContinuumPower);
        // Apply omega omega infinite eternal infinite continuum effects
    }
}

void UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::PerpetuateOmegaOmegaInfiniteEternalTimelessly()
{
    if (bIsOmegaInfiniteEternalExistenceActive)
    {
        float PerpetuationPower = OmegaOmegaInfiniteEternalTimelessPerpetuation * (OmegaOmegaInfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Perpetuating Omega Omega Infinite Eternal Timelessly with power: %.2f"), PerpetuationPower);
        // Apply omega omega infinite eternal timeless perpetuation effects
    }
}

void UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::AchieveOmegaInfiniteEternalSelfSufficiency()
{
    if (bIsOmegaInfiniteEternalExistenceActive)
    {
        float SufficiencyPower = OmegaOmegaInfiniteEternalSelfSufficiency * (OmegaOmegaInfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Omega Infinite Eternal Self-Sufficiency with power: %.2f"), SufficiencyPower);
        // Apply omega omega infinite eternal self-sufficiency effects
    }
}

bool UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::CanActivateOmegaOmegaInfiniteEternalExistence() const
{
    return OmegaOmegaInfiniteEternalExistenceLevel > 0;
}

void UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::UpdateOmegaOmegaInfiniteEternalExistenceStats()
{
    // Update omega omega infinite eternal existence properties based on level
    OmegaOmegaInfiniteEternalLifeForce = OmegaOmegaInfiniteEternalExistenceLevel * 10.0f;
    OmegaOmegaInfiniteEternalPerpetuation = OmegaOmegaInfiniteEternalExistenceLevel * 9.8f;
    OmegaOmegaInfiniteEternalInfiniteContinuum = OmegaOmegaInfiniteEternalExistenceLevel * 9.9f;
    OmegaOmegaInfiniteEternalTimelessPerpetuation = OmegaOmegaInfiniteEternalExistenceLevel * 9.7f;
    OmegaOmegaInfiniteEternalSelfSufficiency = OmegaOmegaInfiniteEternalExistenceLevel * 10.1f;
}

void UP20_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL::OnOmegaOmegaInfiniteEternalExistenceStateChanged()
{
    // Handle state change effects
    if (bIsOmegaInfiniteEternalExistenceActive)
    {
        // Apply omega omega infinite eternal existence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Existence state changed to ACTIVE"));
    }
    else
    {
        // Remove omega omega infinite eternal existence effects
        UE_LOG(LogTemp, Warning, TEXT("Omega Omega Infinite Eternal Existence state changed to INACTIVE"));
    }
}
