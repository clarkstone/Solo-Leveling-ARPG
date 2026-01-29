#include "P10_EXST_ETERNAL.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP10_EXST_ETERNAL::UP10_EXST_ETERNAL()
{
    PrimaryComponentTick.bCanEverTick = false;
    EternalExistenceLevel = 0;
    MaxEternalExistenceLevel = 100;
    bIsEternalExistenceActive = false;
    EternalExistencePowerCost = 55.0f;
    EternalExistenceThreshold = 55.0f;
    
    // Initialize eternal existence properties
    EternalLifeForce = 0.0f;
    EternalPerpetuation = 0.0f;
    EternalInfiniteContinuum = 0.0f;
    EternalTimelessPerpetuation = 0.0f;
    EternalSelfSufficiency = 0.0f;
}

void UP10_EXST_ETERNAL::BeginPlay()
{
    Super::BeginPlay();
    UpdateEternalExistenceStats();
}

void UP10_EXST_ETERNAL::ActivateEternalExistence()
{
    if (!bIsEternalExistenceActive && CanActivateEternalExistence())
    {
        bIsEternalExistenceActive = true;
        OnEternalExistenceActivated.Broadcast(EternalExistenceLevel);
        OnEternalExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Eternal Existence System Activated at Level: %d"), EternalExistenceLevel);
    }
}

void UP10_EXST_ETERNAL::DeactivateEternalExistence()
{
    if (bIsEternalExistenceActive)
    {
        bIsEternalExistenceActive = false;
        OnEternalExistenceDeactivated.Broadcast(EternalExistenceLevel);
        OnEternalExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Eternal Existence System Deactivated."));
    }
}

void UP10_EXST_ETERNAL::SetEternalExistenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxEternalExistenceLevel)
    {
        int32 OldLevel = EternalExistenceLevel;
        EternalExistenceLevel = NewLevel;
        UpdateEternalExistenceStats();
        OnEternalExistenceLevelChanged.Broadcast(OldLevel, EternalExistenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Eternal Existence Level set to: %d"), EternalExistenceLevel);
        
        if (EternalExistenceLevel >= MaxEternalExistenceLevel)
        {
            OnEternalExistenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Eternal Existence Max Level Reached!"));
        }
    }
}

void UP10_EXST_ETERNAL::UseEternalExistencePower()
{
    if (bIsEternalExistenceActive && EternalExistenceLevel > 0)
    {
        OnEternalExistencePowerUsed.Broadcast(EternalExistencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Eternal Existence Power Used: %.2f"), EternalExistencePowerCost);
    }
    else
    {
        OnEternalExistencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Eternal Existence Power Use Failed: System not active or insufficient level."));
    }
}

void UP10_EXST_ETERNAL::PerformEternalExistenceAbility()
{
    if (bIsEternalExistenceActive && EternalExistenceLevel >= EternalExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Eternal Existence Ability at Level %d!"), EternalExistenceLevel);
        OnEternalExistenceAbilityPerformed.Broadcast(EternalExistenceLevel);
        UseEternalExistencePower();
        
        // Perform eternal existence ability based on level
        switch (EternalExistenceLevel / 20)
        {
            case 0:
                ChannelEternalLifeForce();
                break;
            case 1:
                AchieveEternalPerpetuation();
                break;
            case 2:
                MaintainEternalInfiniteContinuum();
                break;
            case 3:
                PerpetuateEternalTimelessly();
                break;
            case 4:
            case 5:
                AchieveEternalSelfSufficiency();
                break;
            default:
                AchieveEternalSelfSufficiency();
                break;
        }
    }
    }
    else if (EternalExistenceLevel < EternalExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Eternal Existence Level too low to perform ability. Required: %.0f, Current: %d"), EternalExistenceThreshold, EternalExistenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Eternal Existence is not active, cannot perform ability."));
    }
}

bool UP10_EXST_ETERNAL::IsEternalExistenceActive() const
{
    return bIsEternalExistenceActive;
}

int32 UP10_EXST_ETERNAL::GetEternalExistenceLevel() const
{
    return EternalExistenceLevel;
}

float UP10_EXST_ETERNAL::GetEternalExistencePowerCost() const
{
    return EternalExistencePowerCost;
}

void UP10_EXST_ETERNAL::ChannelEternalLifeForce()
{
    if (bIsEternalExistenceActive)
    {
        float LifeForcePower = EternalLifeForce * (EternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Eternal Life Force with power: %.2f"), LifeForcePower);
        // Apply eternal life force effects
    }
}

void UP10_EXST_ETERNAL::AchieveEternalPerpetuation()
{
    if (bIsEternalExistenceActive)
    {
        float PerpetuationPower = EternalPerpetuation * (EternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Eternal Perpetuation with power: %.2f"), PerpetuationPower);
        // Apply eternal perpetuation effects
    }
}

void UP10_EXST_ETERNAL::MaintainEternalInfiniteContinuum()
{
    if (bIsEternalExistenceActive)
    {
        float ContinuumPower = EternalInfiniteContinuum * (EternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Maintaining Eternal Infinite Continuum with power: %.2f"), ContinuumPower);
        // Apply eternal infinite continuum effects
    }
}

void UP10_EXST_ETERNAL::PerpetuateEternalTimelessly()
{
    if (bIsEternalExistenceActive)
    {
        float PerpetuationPower = EternalTimelessPerpetuation * (EternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Perpetuating Eternal Timelessly with power: %.2f"), PerpetuationPower);
        // Apply eternal timeless perpetuation effects
    }
}

void UP10_EXST_ETERNAL::AchieveEternalSelfSufficiency()
{
    if (bIsEternalExistenceActive)
    {
        float SufficiencyPower = EternalSelfSufficiency * (EternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Eternal Self-Sufficiency with power: %.2f"), SufficiencyPower);
        // Apply eternal self-sufficiency effects
    }
}

bool UP10_EXST_ETERNAL::CanActivateEternalExistence() const
{
    return EternalExistenceLevel > 0;
}

void UP10_EXST_ETERNAL::UpdateEternalExistenceStats()
{
    // Update eternal existence properties based on level
    EternalLifeForce = EternalExistenceLevel * 5.0f;
    EternalPerpetuation = EternalExistenceLevel * 4.8f;
    EternalInfiniteContinuum = EternalExistenceLevel * 4.9f;
    EternalTimelessPerpetuation = EternalExistenceLevel * 4.7f;
    EternalSelfSufficiency = EternalExistenceLevel * 5.1f;
}

void UP10_EXST_ETERNAL::OnEternalExistenceStateChanged()
{
    // Handle state change effects
    if (bIsEternalExistenceActive)
    {
        // Apply eternal existence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Eternal Existence state changed to ACTIVE"));
    }
    else
    {
        // Remove eternal existence effects
        UE_LOG(LogTemp, Warning, TEXT("Eternal Existence state changed to INACTIVE"));
    }
}
