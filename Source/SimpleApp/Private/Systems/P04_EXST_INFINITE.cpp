#include "P04_EXST_INFINITE.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP04_EXST_INFINITE::UP04_EXST_INFINITE()
{
    PrimaryComponentTick.bCanEverTick = false;
    InfiniteExistenceLevel = 0;
    MaxInfiniteExistenceLevel = 100;
    bIsInfiniteExistenceActive = false;
    InfiniteExistencePowerCost = 25.0f;
    InfiniteExistenceThreshold = 25.0f;
    
    // Initialize infinite existence properties
    InfiniteLifeForce = 0.0f;
    InfinitePerpetuation = 0.0f;
    InfiniteContinuum = 0.0f;
    InfiniteTimelessPerpetuation = 0.0f;
    InfiniteSelfSufficiency = 0.0f;
}

void UP04_EXST_INFINITE::BeginPlay()
{
    Super::BeginPlay();
    UpdateInfiniteExistenceStats();
}

void UP04_EXST_INFINITE::ActivateInfiniteExistence()
{
    if (!bIsInfiniteExistenceActive && CanActivateInfiniteExistence())
    {
        bIsInfiniteExistenceActive = true;
        OnInfiniteExistenceActivated.Broadcast(InfiniteExistenceLevel);
        OnInfiniteExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Existence System Activated at Level: %d"), InfiniteExistenceLevel);
    }
}

void UP04_EXST_INFINITE::DeactivateInfiniteExistence()
{
    if (bIsInfiniteExistenceActive)
    {
        bIsInfiniteExistenceActive = false;
        OnInfiniteExistenceDeactivated.Broadcast(InfiniteExistenceLevel);
        OnInfiniteExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Existence System Deactivated."));
    }
}

void UP04_EXST_INFINITE::SetInfiniteExistenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxInfiniteExistenceLevel)
    {
        int32 OldLevel = InfiniteExistenceLevel;
        InfiniteExistenceLevel = NewLevel;
        UpdateInfiniteExistenceStats();
        OnInfiniteExistenceLevelChanged.Broadcast(OldLevel, InfiniteExistenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Infinite Existence Level set to: %d"), InfiniteExistenceLevel);
        
        if (InfiniteExistenceLevel >= MaxInfiniteExistenceLevel)
        {
            OnInfiniteExistenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Infinite Existence Max Level Reached!"));
        }
    }
}

void UP04_EXST_INFINITE::UseInfiniteExistencePower()
{
    if (bIsInfiniteExistenceActive && InfiniteExistenceLevel > 0)
    {
        OnInfiniteExistencePowerUsed.Broadcast(InfiniteExistencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Infinite Existence Power Used: %.2f"), InfiniteExistencePowerCost);
    }
    else
    {
        OnInfiniteExistencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Existence Power Use Failed: System not active or insufficient level."));
    }
}

void UP04_EXST_INFINITE::PerformInfiniteExistenceAbility()
{
    if (bIsInfiniteExistenceActive && InfiniteExistenceLevel >= InfiniteExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Infinite Existence Ability at Level %d!"), InfiniteExistenceLevel);
        OnInfiniteExistenceAbilityPerformed.Broadcast(InfiniteExistenceLevel);
        UseInfiniteExistencePower();
        
        // Perform infinite existence ability based on level
        switch (InfiniteExistenceLevel / 20)
        {
            case 0:
                ChannelInfiniteLifeForce();
                break;
            case 1:
                AchieveInfinitePerpetuation();
                break;
            case 2:
                MaintainInfiniteContinuum();
                break;
            case 3:
                PerpetuateInfiniteTimelessly();
                break;
            case 4:
            case 5:
                AchieveInfiniteSelfSufficiency();
                break;
            default:
                AchieveInfiniteSelfSufficiency();
                break;
        }
    }
    }
    else if (InfiniteExistenceLevel < InfiniteExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Infinite Existence Level too low to perform ability. Required: %.0f, Current: %d"), InfiniteExistenceThreshold, InfiniteExistenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Infinite Existence is not active, cannot perform ability."));
    }
}

bool UP04_EXST_INFINITE::IsInfiniteExistenceActive() const
{
    return bIsInfiniteExistenceActive;
}

int32 UP04_EXST_INFINITE::GetInfiniteExistenceLevel() const
{
    return InfiniteExistenceLevel;
}

float UP04_EXST_INFINITE::GetInfiniteExistencePowerCost() const
{
    return InfiniteExistencePowerCost;
}

void UP04_EXST_INFINITE::ChannelInfiniteLifeForce()
{
    if (bIsInfiniteExistenceActive)
    {
        float LifeForcePower = InfiniteLifeForce * (InfiniteExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Infinite Life Force with power: %.2f"), LifeForcePower);
        // Apply infinite life force effects
    }
}

void UP04_EXST_INFINITE::AchieveInfinitePerpetuation()
{
    if (bIsInfiniteExistenceActive)
    {
        float PerpetuationPower = InfinitePerpetuation * (InfiniteExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Infinite Perpetuation with power: %.2f"), PerpetuationPower);
        // Apply infinite perpetuation effects
    }
}

void UP04_EXST_INFINITE::MaintainInfiniteContinuum()
{
    if (bIsInfiniteExistenceActive)
    {
        float ContinuumPower = InfiniteContinuum * (InfiniteExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Maintaining Infinite Continuum with power: %.2f"), ContinuumPower);
        // Apply infinite continuum effects
    }
}

void UP04_EXST_INFINITE::PerpetuateInfiniteTimelessly()
{
    if (bIsInfiniteExistenceActive)
    {
        float PerpetuationPower = InfiniteTimelessPerpetuation * (InfiniteExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Perpetuating Infinite Timelessly with power: %.2f"), PerpetuationPower);
        // Apply infinite timeless perpetuation effects
    }
}

void UP04_EXST_INFINITE::AchieveInfiniteSelfSufficiency()
{
    if (bIsInfiniteExistenceActive)
    {
        float SufficiencyPower = InfiniteSelfSufficiency * (InfiniteExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Infinite Self-Sufficiency with power: %.2f"), SufficiencyPower);
        // Apply infinite self-sufficiency effects
    }
}

bool UP04_EXST_INFINITE::CanActivateInfiniteExistence() const
{
    return InfiniteExistenceLevel > 0;
}

void UP04_EXST_INFINITE::UpdateInfiniteExistenceStats()
{
    // Update infinite existence properties based on level
    InfiniteLifeForce = InfiniteExistenceLevel * 3.5f;
    InfinitePerpetuation = InfiniteExistenceLevel * 3.3f;
    InfiniteContinuum = InfiniteExistenceLevel * 3.4f;
    InfiniteTimelessPerpetuation = InfiniteExistenceLevel * 3.2f;
    InfiniteSelfSufficiency = InfiniteExistenceLevel * 3.6f;
}

void UP04_EXST_INFINITE::OnInfiniteExistenceStateChanged()
{
    // Handle state change effects
    if (bIsInfiniteExistenceActive)
    {
        // Apply infinite existence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Infinite Existence state changed to ACTIVE"));
    }
    else
    {
        // Remove infinite existence effects
        UE_LOG(LogTemp, Warning, TEXT("Infinite Existence state changed to INACTIVE"));
    }
}
