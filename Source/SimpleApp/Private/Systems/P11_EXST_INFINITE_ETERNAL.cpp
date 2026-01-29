#include "P11_EXST_INFINITE_ETERNAL.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP11_EXST_INFINITE_ETERNAL::UP11_EXST_INFINITE_ETERNAL()
{
    PrimaryComponentTick.bCanEverTick = false;
    InfiniteEternalExistenceLevel = 0;
    MaxInfiniteEternalExistenceLevel = 100;
    bIsInfiniteEternalExistenceActive = false;
    InfiniteEternalExistencePowerCost = 60.0f;
    InfiniteEternalExistenceThreshold = 60.0f;
    
    // Initialize infinite eternal existence properties
    InfiniteEternalLifeForce = 0.0f;
    InfiniteEternalPerpetuation = 0.0f;
    InfiniteEternalInfiniteContinuum = 0.0f;
    InfiniteEternalTimelessPerpetuation = 0.0f;
    InfiniteEternalSelfSufficiency = 0.0f;
}

void UP11_EXST_INFINITE_ETERNAL::BeginPlay()
{
    Super::BeginPlay();
    UpdateInfiniteEternalExistenceStats();
}

void UP11_EXST_INFINITE_ETERNAL::ActivateInfiniteEternalExistence()
{
    if (!bIsInfiniteEternalExistenceActive && CanActivateInfiniteEternalExistence())
    {
        bIsInfiniteEternalExistenceActive = true;
        OnInfiniteEternalExistenceActivated.Broadcast(InfiniteEternalExistenceLevel);
        OnInfiniteEternalExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Existence System Activated at Level: %d"), InfiniteEternalExistenceLevel);
    }
}

void UP11_EXST_INFINITE_ETERNAL::DeactivateInfiniteEternalExistence()
{
    if (bIsInfiniteEternalExistenceActive)
    {
        bIsInfiniteEternalExistenceActive = false;
        OnInfiniteEternalExistenceDeactivated.Broadcast(InfiniteEternalExistenceLevel);
        OnInfiniteEternalExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Existence System Deactivated."));
    }
}

void UP11_EXST_INFINITE_ETERNAL::SetInfiniteEternalExistenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxInfiniteEternalExistenceLevel)
    {
        int32 OldLevel = InfiniteEternalExistenceLevel;
        InfiniteEternalExistenceLevel = NewLevel;
        UpdateInfiniteEternalExistenceStats();
        OnInfiniteEternalExistenceLevelChanged.Broadcast(OldLevel, InfiniteEternalExistenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Existence Level set to: %d"), InfiniteEternalExistenceLevel);
        
        if (InfiniteEternalExistenceLevel >= MaxInfiniteEternalExistenceLevel)
        {
            OnInfiniteEternalExistenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Existence Max Level Reached!"));
        }
    }
}

void UP11_EXST_INFINITE_ETERNAL::UseInfiniteEternalExistencePower()
{
    if (bIsInfiniteEternalExistenceActive && InfiniteEternalExistenceLevel > 0)
    {
        OnInfiniteEternalExistencePowerUsed.Broadcast(InfiniteEternalExistencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Existence Power Used: %.2f"), InfiniteEternalExistencePowerCost);
    }
    else
    {
        OnInfiniteEternalExistencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Existence Power Use Failed: System not active or insufficient level."));
    }
}

void UP11_EXST_INFINITE_ETERNAL::PerformInfiniteEternalExistenceAbility()
{
    if (bIsInfiniteEternalExistenceActive && InfiniteEternalExistenceLevel >= InfiniteEternalExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Infinite Eternal Existence Ability at Level %d!"), InfiniteEternalExistenceLevel);
        OnInfiniteEternalExistenceAbilityPerformed.Broadcast(InfiniteEternalExistenceLevel);
        UseInfiniteEternalExistencePower();
        
        // Perform infinite eternal existence ability based on level
        switch (InfiniteEternalExistenceLevel / 20)
        {
            case 0:
                ChannelInfiniteEternalLifeForce();
                break;
            case 1:
                AchieveInfiniteEternalPerpetuation();
                break;
            case 2:
                MaintainInfiniteEternalInfiniteContinuum();
                break;
            case 3:
                PerpetuateInfiniteEternalTimelessly();
                break;
            case 4:
            case 5:
                AchieveInfiniteEternalSelfSufficiency();
                break;
            default:
                AchieveInfiniteEternalSelfSufficiency();
                break;
        }
    }
    }
    else if (InfiniteEternalExistenceLevel < InfiniteEternalExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Existence Level too low to perform ability. Required: %.0f, Current: %d"), InfiniteEternalExistenceThreshold, InfiniteEternalExistenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Existence is not active, cannot perform ability."));
    }
}

bool UP11_EXST_INFINITE_ETERNAL::IsInfiniteEternalExistenceActive() const
{
    return bIsInfiniteEternalExistenceActive;
}

int32 UP11_EXST_INFINITE_ETERNAL::GetInfiniteEternalExistenceLevel() const
{
    return InfiniteEternalExistenceLevel;
}

float UP11_EXST_INFINITE_ETERNAL::GetInfiniteEternalExistencePowerCost() const
{
    return InfiniteEternalExistencePowerCost;
}

void UP11_EXST_INFINITE_ETERNAL::ChannelInfiniteEternalLifeForce()
{
    if (bIsInfiniteEternalExistenceActive)
    {
        float LifeForcePower = InfiniteEternalLifeForce * (InfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Infinite Eternal Life Force with power: %.2f"), LifeForcePower);
        // Apply infinite eternal life force effects
    }
}

void UP11_EXST_INFINITE_ETERNAL::AchieveInfiniteEternalPerpetuation()
{
    if (bIsInfiniteEternalExistenceActive)
    {
        float PerpetuationPower = InfiniteEternalPerpetuation * (InfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Infinite Eternal Perpetuation with power: %.2f"), PerpetuationPower);
        // Apply infinite eternal perpetuation effects
    }
}

void UP11_EXST_INFINITE_ETERNAL::MaintainInfiniteEternalInfiniteContinuum()
{
    if (bIsInfiniteEternalExistenceActive)
    {
        float ContinuumPower = InfiniteEternalInfiniteContinuum * (InfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Maintaining Infinite Eternal Infinite Continuum with power: %.2f"), ContinuumPower);
        // Apply infinite eternal infinite continuum effects
    }
}

void UP11_EXST_INFINITE_ETERNAL::PerpetuateInfiniteEternalTimelessly()
{
    if (bIsInfiniteEternalExistenceActive)
    {
        float PerpetuationPower = InfiniteEternalTimelessPerpetuation * (InfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Perpetuating Infinite Eternal Timelessly with power: %.2f"), PerpetuationPower);
        // Apply infinite eternal timeless perpetuation effects
    }
}

void UP11_EXST_INFINITE_ETERNAL::AchieveInfiniteEternalSelfSufficiency()
{
    if (bIsInfiniteEternalExistenceActive)
    {
        float SufficiencyPower = InfiniteEternalSelfSufficiency * (InfiniteEternalExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Infinite Eternal Self-Sufficiency with power: %.2f"), SufficiencyPower);
        // Apply infinite eternal self-sufficiency effects
    }
}

bool UP11_EXST_INFINITE_ETERNAL::CanActivateInfiniteEternalExistence() const
{
    return InfiniteEternalExistenceLevel > 0;
}

void UP11_EXST_INFINITE_ETERNAL::UpdateInfiniteEternalExistenceStats()
{
    // Update infinite eternal existence properties based on level
    InfiniteEternalLifeForce = InfiniteEternalExistenceLevel * 5.5f;
    InfiniteEternalPerpetuation = InfiniteEternalExistenceLevel * 5.3f;
    InfiniteEternalInfiniteContinuum = InfiniteEternalExistenceLevel * 5.4f;
    InfiniteEternalTimelessPerpetuation = InfiniteEternalExistenceLevel * 5.2f;
    InfiniteEternalSelfSufficiency = InfiniteEternalExistenceLevel * 5.6f;
}

void UP11_EXST_INFINITE_ETERNAL::OnInfiniteEternalExistenceStateChanged()
{
    // Handle state change effects
    if (bIsInfiniteEternalExistenceActive)
    {
        // Apply infinite eternal existence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Existence state changed to ACTIVE"));
    }
    else
    {
        // Remove infinite eternal existence effects
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Existence state changed to INACTIVE"));
    }
}
