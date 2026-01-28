#include "COMPLETE_PERPETUAL_EXISTENCE_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    PerpetualExistenceLevel = 0;
    MaxPerpetualExistenceLevel = 100;
    bIsPerpetualExistenceActive = false;
    PerpetualExistencePowerCost = 20.0f;
    PerpetualExistenceThreshold = 70.0f;
    
    // Initialize perpetual-existence properties
    PerpetualLifeEssence = 0.0f;
    InfiniteSelfRenewal = 0.0f;
    EternalContinuum = 0.0f;
    TimelessPerpetuation = 0.0f;
    AbsoluteSelfSufficiency = 0.0f;
}

void UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdatePerpetualExistenceStats();
}

void UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::ActivatePerpetualExistence()
{
    if (!bIsPerpetualExistenceActive && CanActivatePerpetualExistence())
    {
        bIsPerpetualExistenceActive = true;
        OnPerpetualExistenceActivated.Broadcast(PerpetualExistenceLevel);
        OnPerpetualExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Perpetual-Existence System Activated at Level: %d"), PerpetualExistenceLevel);
    }
}

void UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::DeactivatePerpetualExistence()
{
    if (bIsPerpetualExistenceActive)
    {
        bIsPerpetualExistenceActive = false;
        OnPerpetualExistenceDeactivated.Broadcast(PerpetualExistenceLevel);
        OnPerpetualExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Perpetual-Existence System Deactivated."));
    }
}

void UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::SetPerpetualExistenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxPerpetualExistenceLevel)
    {
        int32 OldLevel = PerpetualExistenceLevel;
        PerpetualExistenceLevel = NewLevel;
        UpdatePerpetualExistenceStats();
        OnPerpetualExistenceLevelChanged.Broadcast(OldLevel, PerpetualExistenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Perpetual-Existence Level set to: %d"), PerpetualExistenceLevel);
        
        if (PerpetualExistenceLevel >= MaxPerpetualExistenceLevel)
        {
            OnPerpetualExistenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Perpetual-Existence Max Level Reached!"));
        }
    }
}

void UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::UsePerpetualExistencePower()
{
    if (bIsPerpetualExistenceActive && PerpetualExistenceLevel > 0)
    {
        OnPerpetualExistencePowerUsed.Broadcast(PerpetualExistencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Perpetual-Existence Power Used: %.2f"), PerpetualExistencePowerCost);
    }
    else
    {
        OnPerpetualExistencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Perpetual-Existence Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::PerformPerpetualExistenceAbility()
{
    if (bIsPerpetualExistenceActive && PerpetualExistenceLevel >= PerpetualExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Perpetual-Existence Ability at Level %d!"), PerpetualExistenceLevel);
        OnPerpetualExistenceAbilityPerformed.Broadcast(PerpetualExistenceLevel);
        UsePerpetualExistencePower();
        
        // Perform perpetual-existence ability based on level
        switch (PerpetualExistenceLevel / 20)
        {
            case 0:
                ChannelPerpetualLifeEssence();
                break;
            case 1:
                RenewInfinitely();
                break;
            case 2:
                MaintainEternalContinuum();
                break;
            case 3:
                PerpetuateTimelessly();
                break;
            case 4:
            case 5:
                AchieveAbsoluteSelfSufficiency();
                break;
            default:
                AchieveAbsoluteSelfSufficiency();
                break;
        }
    }
    else if (PerpetualExistenceLevel < PerpetualExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Perpetual-Existence Level too low to perform ability. Required: %.0f, Current: %d"), PerpetualExistenceThreshold, PerpetualExistenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Perpetual-Existence is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::IsPerpetualExistenceActive() const
{
    return bIsPerpetualExistenceActive;
}

int32 UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::GetPerpetualExistenceLevel() const
{
    return PerpetualExistenceLevel;
}

float UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::GetPerpetualExistencePowerCost() const
{
    return PerpetualExistencePowerCost;
}

void UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::ChannelPerpetualLifeEssence()
{
    if (bIsPerpetualExistenceActive)
    {
        float LifeEssencePower = PerpetualLifeEssence * (PerpetualExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Perpetual Life Essence with power: %.2f"), LifeEssencePower);
        // Apply perpetual life essence effects
    }
}

void UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::RenewInfinitely()
{
    if (bIsPerpetualExistenceActive)
    {
        float RenewalPower = InfiniteSelfRenewal * (PerpetualExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Renewing Infinitely with power: %.2f"), RenewalPower);
        // Apply infinite self-renewal effects
    }
}

void UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::MaintainEternalContinuum()
{
    if (bIsPerpetualExistenceActive)
    {
        float ContinuumPower = EternalContinuum * (PerpetualExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Maintaining Eternal Continuum with power: %.2f"), ContinuumPower);
        // Apply eternal continuum effects
    }
}

void UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::PerpetuateTimelessly()
{
    if (bIsPerpetualExistenceActive)
    {
        float PerpetuationPower = TimelessPerpetuation * (PerpetualExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Perpetuating Timelessly with power: %.2f"), PerpetuationPower);
        // Apply timeless perpetuation effects
    }
}

void UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::AchieveAbsoluteSelfSufficiency()
{
    if (bIsPerpetualExistenceActive)
    {
        float SelfSufficiencyPower = AbsoluteSelfSufficiency * (PerpetualExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Absolute Self-Sufficiency with power: %.2f"), SelfSufficiencyPower);
        // Apply absolute self-sufficiency effects
    }
}

bool UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::CanActivatePerpetualExistence() const
{
    return PerpetualExistenceLevel > 0;
}

void UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::UpdatePerpetualExistenceStats()
{
    // Update perpetual-existence properties based on level
    PerpetualLifeEssence = PerpetualExistenceLevel * 4.1f;
    InfiniteSelfRenewal = PerpetualExistenceLevel * 3.9f;
    EternalContinuum = PerpetualExistenceLevel * 4.0f;
    TimelessPerpetuation = PerpetualExistenceLevel * 3.8f;
    AbsoluteSelfSufficiency = PerpetualExistenceLevel * 4.3f;
}

void UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM::OnPerpetualExistenceStateChanged()
{
    // Handle state change effects
    if (bIsPerpetualExistenceActive)
    {
        // Apply perpetual-existence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Perpetual-Existence state changed to ACTIVE"));
    }
    else
    {
        // Remove perpetual-existence effects
        UE_LOG(LogTemp, Warning, TEXT("Perpetual-Existence state changed to INACTIVE"));
    }
}
