#include "COMPLETE_ETERNAL_EXISTENCE_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    EternalExistenceLevel = 0;
    MaxEternalExistenceLevel = 100;
    bIsEternalExistenceActive = false;
    EternalExistencePowerCost = 15.0f;
    EternalExistenceThreshold = 60.0f;
    
    // Initialize eternal-existence properties
    EternalLifeForce = 0.0f;
    InfiniteSustenance = 0.0f;
    PerpetualRenewal = 0.0f;
    TimelessExistence = 0.0f;
    AbsoluteImmortality = 0.0f;
}

void UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateEternalExistenceStats();
}

void UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::ActivateEternalExistence()
{
    if (!bIsEternalExistenceActive && CanActivateEternalExistence())
    {
        bIsEternalExistenceActive = true;
        OnEternalExistenceActivated.Broadcast(EternalExistenceLevel);
        OnEternalExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Existence System Activated at Level: %d"), EternalExistenceLevel);
    }
}

void UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::DeactivateEternalExistence()
{
    if (bIsEternalExistenceActive)
    {
        bIsEternalExistenceActive = false;
        OnEternalExistenceDeactivated.Broadcast(EternalExistenceLevel);
        OnEternalExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Existence System Deactivated."));
    }
}

void UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::SetEternalExistenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxEternalExistenceLevel)
    {
        int32 OldLevel = EternalExistenceLevel;
        EternalExistenceLevel = NewLevel;
        UpdateEternalExistenceStats();
        OnEternalExistenceLevelChanged.Broadcast(OldLevel, EternalExistenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Existence Level set to: %d"), EternalExistenceLevel);
        
        if (EternalExistenceLevel >= MaxEternalExistenceLevel)
        {
            OnEternalExistenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Eternal-Existence Max Level Reached!"));
        }
    }
}

void UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::UseEternalExistencePower()
{
    if (bIsEternalExistenceActive && EternalExistenceLevel > 0)
    {
        OnEternalExistencePowerUsed.Broadcast(EternalExistencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Existence Power Used: %.2f"), EternalExistencePowerCost);
    }
    else
    {
        OnEternalExistencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Existence Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::PerformEternalExistenceAbility()
{
    if (bIsEternalExistenceActive && EternalExistenceLevel >= EternalExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Eternal-Existence Ability at Level %d!"), EternalExistenceLevel);
        OnEternalExistenceAbilityPerformed.Broadcast(EternalExistenceLevel);
        UseEternalExistencePower();
        
        // Perform eternal-existence ability based on level
        switch (EternalExistenceLevel / 20)
        {
            case 0:
                ChannelEternalLifeForce();
                break;
            case 1:
                SustainInfiniteExistence();
                break;
            case 2:
                RenewPerpetually();
                break;
            case 3:
                ExistTimelessly();
                break;
            case 4:
            case 5:
                AchieveAbsoluteImmortality();
                break;
            default:
                AchieveAbsoluteImmortality();
                break;
        }
    }
    else if (EternalExistenceLevel < EternalExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Existence Level too low to perform ability. Required: %.0f, Current: %d"), EternalExistenceThreshold, EternalExistenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Existence is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::IsEternalExistenceActive() const
{
    return bIsEternalExistenceActive;
}

int32 UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::GetEternalExistenceLevel() const
{
    return EternalExistenceLevel;
}

float UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::GetEternalExistencePowerCost() const
{
    return EternalExistencePowerCost;
}

void UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::ChannelEternalLifeForce()
{
    if (bIsEternalExistenceActive)
    {
        float LifeForcePower = EternalLifeForce * (EternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Eternal Life Force with power: %.2f"), LifeForcePower);
        // Apply eternal life force effects
    }
}

void UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::SustainInfiniteExistence()
{
    if (bIsEternalExistenceActive)
    {
        float SustenancePower = InfiniteSustenance * (EternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Sustaining Infinite Existence with power: %.2f"), SustenancePower);
        // Apply infinite sustenance effects
    }
}

void UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::RenewPerpetually()
{
    if (bIsEternalExistenceActive)
    {
        float RenewalPower = PerpetualRenewal * (EternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Renewing Perpetually with power: %.2f"), RenewalPower);
        // Apply perpetual renewal effects
    }
}

void UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::ExistTimelessly()
{
    if (bIsEternalExistenceActive)
    {
        float TimelessPower = TimelessExistence * (EternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Existing Timelessly with power: %.2f"), TimelessPower);
        // Apply timeless existence effects
    }
}

void UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::AchieveAbsoluteImmortality()
{
    if (bIsEternalExistenceActive)
    {
        float ImmortalityPower = AbsoluteImmortality * (EternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Absolute Immortality with power: %.2f"), ImmortalityPower);
        // Apply absolute immortality effects
    }
}

bool UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::CanActivateEternalExistence() const
{
    return EternalExistenceLevel > 0;
}

void UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::UpdateEternalExistenceStats()
{
    // Update eternal-existence properties based on level
    EternalLifeForce = EternalExistenceLevel * 2.8f;
    InfiniteSustenance = EternalExistenceLevel * 2.6f;
    PerpetualRenewal = EternalExistenceLevel * 2.9f;
    TimelessExistence = EternalExistenceLevel * 2.7f;
    AbsoluteImmortality = EternalExistenceLevel * 3.0f;
}

void UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM::OnEternalExistenceStateChanged()
{
    // Handle state change effects
    if (bIsEternalExistenceActive)
    {
        // Apply eternal-existence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Existence state changed to ACTIVE"));
    }
    else
    {
        // Remove eternal-existence effects
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Existence state changed to INACTIVE"));
    }
}
