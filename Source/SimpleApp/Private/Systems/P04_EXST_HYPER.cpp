#include "P04_EXST_HYPER.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP04_EXST_HYPER::UP04_EXST_HYPER()
{
    PrimaryComponentTick.bCanEverTick = false;
    HyperExistenceLevel = 0;
    MaxHyperExistenceLevel = 100;
    bIsHyperExistenceActive = false;
    HyperExistencePowerCost = 25.0f;
    HyperExistenceThreshold = 25.0f;
    
    // Initialize hyper existence properties
    HyperLifeForce = 0.0f;
    HyperPerpetuation = 0.0f;
    HyperInfiniteContinuum = 0.0f;
    HyperTimelessPerpetuation = 0.0f;
    HyperSelfSufficiency = 0.0f;
}

void UP04_EXST_HYPER::BeginPlay()
{
    Super::BeginPlay();
    UpdateHyperExistenceStats();
}

void UP04_EXST_HYPER::ActivateHyperExistence()
{
    if (!bIsHyperExistenceActive && CanActivateHyperExistence())
    {
        bIsHyperExistenceActive = true;
        OnHyperExistenceActivated.Broadcast(HyperExistenceLevel);
        OnHyperExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Hyper Existence System Activated at Level: %d"), HyperExistenceLevel);
    }
}

void UP04_EXST_HYPER::DeactivateHyperExistence()
{
    if (bIsHyperExistenceActive)
    {
        bIsHyperExistenceActive = false;
        OnHyperExistenceDeactivated.Broadcast(HyperExistenceLevel);
        OnHyperExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Hyper Existence System Deactivated."));
    }
}

void UP04_EXST_HYPER::SetHyperExistenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxHyperExistenceLevel)
    {
        int32 OldLevel = HyperExistenceLevel;
        HyperExistenceLevel = NewLevel;
        UpdateHyperExistenceStats();
        OnHyperExistenceLevelChanged.Broadcast(OldLevel, HyperExistenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Hyper Existence Level set to: %d"), HyperExistenceLevel);
        
        if (HyperExistenceLevel >= MaxHyperExistenceLevel)
        {
            OnHyperExistenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Hyper Existence Max Level Reached!"));
        }
    }
}

void UP04_EXST_HYPER::UseHyperExistencePower()
{
    if (bIsHyperExistenceActive && HyperExistenceLevel > 0)
    {
        OnHyperExistencePowerUsed.Broadcast(HyperExistencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Hyper Existence Power Used: %.2f"), HyperExistencePowerCost);
    }
    else
    {
        OnHyperExistencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Hyper Existence Power Use Failed: System not active or insufficient level."));
    }
}

void UP04_EXST_HYPER::PerformHyperExistenceAbility()
{
    if (bIsHyperExistenceActive && HyperExistenceLevel >= HyperExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Hyper Existence Ability at Level %d!"), HyperExistenceLevel);
        OnHyperExistenceAbilityPerformed.Broadcast(HyperExistenceLevel);
        UseHyperExistencePower();
        
        // Perform hyper existence ability based on level
        switch (HyperExistenceLevel / 20)
        {
            case 0:
                ChannelHyperLifeForce();
                break;
            case 1:
                AchieveHyperPerpetuation();
                break;
            case 2:
                MaintainHyperInfiniteContinuum();
                break;
            case 3:
                PerpetuateHyperTimelessly();
                break;
            case 4:
            case 5:
                AchieveHyperSelfSufficiency();
                break;
            default:
                AchieveHyperSelfSufficiency();
                break;
        }
    }
    }
    else if (HyperExistenceLevel < HyperExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hyper Existence Level too low to perform ability. Required: %.0f, Current: %d"), HyperExistenceThreshold, HyperExistenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Hyper Existence is not active, cannot perform ability."));
    }
}

bool UP04_EXST_HYPER::IsHyperExistenceActive() const
{
    return bIsHyperExistenceActive;
}

int32 UP04_EXST_HYPER::GetHyperExistenceLevel() const
{
    return HyperExistenceLevel;
}

float UP04_EXST_HYPER::GetHyperExistencePowerCost() const
{
    return HyperExistencePowerCost;
}

void UP04_EXST_HYPER::ChannelHyperLifeForce()
{
    if (bIsHyperExistenceActive)
    {
        float LifeForcePower = HyperLifeForce * (HyperExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Hyper Life Force with power: %.2f"), LifeForcePower);
        // Apply hyper life force effects
    }
}

void UP04_EXST_HYPER::AchieveHyperPerpetuation()
{
    if (bIsHyperExistenceActive)
    {
        float PerpetuationPower = HyperPerpetuation * (HyperExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Hyper Perpetuation with power: %.2f"), PerpetuationPower);
        // Apply hyper perpetuation effects
    }
}

void UP04_EXST_HYPER::MaintainHyperInfiniteContinuum()
{
    if (bIsHyperExistenceActive)
    {
        float ContinuumPower = HyperInfiniteContinuum * (HyperExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Maintaining Hyper Infinite Continuum with power: %.2f"), ContinuumPower);
        // Apply hyper infinite continuum effects
    }
}

void UP04_EXST_HYPER::PerpetuateHyperTimelessly()
{
    if (bIsHyperExistenceActive)
    {
        float PerpetuationPower = HyperTimelessPerpetuation * (HyperExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Perpetuating Hyper Timelessly with power: %.2f"), PerpetuationPower);
        // Apply hyper timeless perpetuation effects
    }
}

void UP04_EXST_HYPER::AchieveHyperSelfSufficiency()
{
    if (bIsHyperExistenceActive)
    {
        float SufficiencyPower = HyperSelfSufficiency * (HyperExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Hyper Self-Sufficiency with power: %.2f"), SufficiencyPower);
        // Apply hyper self-sufficiency effects
    }
}

bool UP04_EXST_HYPER::CanActivateHyperExistence() const
{
    return HyperExistenceLevel > 0;
}

void UP04_EXST_HYPER::UpdateHyperExistenceStats()
{
    // Update hyper existence properties based on level
    HyperLifeForce = HyperExistenceLevel * 2.5f;
    HyperPerpetuation = HyperExistenceLevel * 2.3f;
    HyperInfiniteContinuum = HyperExistenceLevel * 2.4f;
    HyperTimelessPerpetuation = HyperExistenceLevel * 2.2f;
    HyperSelfSufficiency = HyperExistenceLevel * 2.6f;
}

void UP04_EXST_HYPER::OnHyperExistenceStateChanged()
{
    // Handle state change effects
    if (bIsHyperExistenceActive)
    {
        // Apply hyper existence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Hyper Existence state changed to ACTIVE"));
    }
    else
    {
        // Remove hyper existence effects
        UE_LOG(LogTemp, Warning, TEXT("Hyper Existence state changed to INACTIVE"));
    }
}
