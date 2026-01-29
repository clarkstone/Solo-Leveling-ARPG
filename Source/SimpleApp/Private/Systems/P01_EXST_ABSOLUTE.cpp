#include "P01_EXST_ABSOLUTE.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP01_EXST_ABSOLUTE::UP01_EXST_ABSOLUTE()
{
    PrimaryComponentTick.bCanEverTick = false;
    AbsoluteExistenceLevel = 0;
    MaxAbsoluteExistenceLevel = 100;
    bIsAbsoluteExistenceActive = false;
    AbsoluteExistencePowerCost = 10.0f;
    AbsoluteExistenceThreshold = 10.0f;
    
    // Initialize absolute existence properties
    AbsoluteLifeForce = 0.0f;
    EternalPerpetuation = 0.0f;
    InfiniteContinuum = 0.0f;
    TimelessPerpetuation = 0.0f;
    AbsoluteSelfSufficiency = 0.0f;
}

void UP01_EXST_ABSOLUTE::BeginPlay()
{
    Super::BeginPlay();
    UpdateAbsoluteExistenceStats();
}

void UP01_EXST_ABSOLUTE::ActivateAbsoluteExistence()
{
    if (!bIsAbsoluteExistenceActive && CanActivateAbsoluteExistence())
    {
        bIsAbsoluteExistenceActive = true;
        OnAbsoluteExistenceActivated.Broadcast(AbsoluteExistenceLevel);
        OnAbsoluteExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Absolute Existence System Activated at Level: %d"), AbsoluteExistenceLevel);
    }
}

void UP01_EXST_ABSOLUTE::DeactivateAbsoluteExistence()
{
    if (bIsAbsoluteExistenceActive)
    {
        bIsAbsoluteExistenceActive = false;
        OnAbsoluteExistenceDeactivated.Broadcast(AbsoluteExistenceLevel);
        OnAbsoluteExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Absolute Existence System Deactivated."));
    }
}

void UP01_EXST_ABSOLUTE::SetAbsoluteExistenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxAbsoluteExistenceLevel)
    {
        int32 OldLevel = AbsoluteExistenceLevel;
        AbsoluteExistenceLevel = NewLevel;
        UpdateAbsoluteExistenceStats();
        OnAbsoluteExistenceLevelChanged.Broadcast(OldLevel, AbsoluteExistenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Absolute Existence Level set to: %d"), AbsoluteExistenceLevel);
        
        if (AbsoluteExistenceLevel >= MaxAbsoluteExistenceLevel)
        {
            OnAbsoluteExistenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Absolute Existence Max Level Reached!"));
        }
    }
}

void UP01_EXST_ABSOLUTE::UseAbsoluteExistencePower()
{
    if (bIsAbsoluteExistenceActive && AbsoluteExistenceLevel > 0)
    {
        OnAbsoluteExistencePowerUsed.Broadcast(AbsoluteExistencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Absolute Existence Power Used: %.2f"), AbsoluteExistencePowerCost);
    }
    else
    {
        OnAbsoluteExistencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Absolute Existence Power Use Failed: System not active or insufficient level."));
    }
}

void UP01_EXST_ABSOLUTE::PerformAbsoluteExistenceAbility()
{
    if (bIsAbsoluteExistenceActive && AbsoluteExistenceLevel >= AbsoluteExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Absolute Existence Ability at Level %d!"), AbsoluteExistenceLevel);
        OnAbsoluteExistenceAbilityPerformed.Broadcast(AbsoluteExistenceLevel);
        UseAbsoluteExistencePower();
        
        // Perform absolute existence ability based on level
        switch (AbsoluteExistenceLevel / 20)
        {
            case 0:
                ChannelAbsoluteLifeForce();
                break;
            case 1:
                AchieveEternalPerpetuation();
                break;
            case 2:
                MaintainInfiniteContinuum();
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
    }
    else if (AbsoluteExistenceLevel < AbsoluteExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Absolute Existence Level too low to perform ability. Required: %.0f, Current: %d"), AbsoluteExistenceThreshold, AbsoluteExistenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Absolute Existence is not active, cannot perform ability."));
    }
}

bool UP01_EXST_ABSOLUTE::IsAbsoluteExistenceActive() const
{
    return bIsAbsoluteExistenceActive;
}

int32 UP01_EXST_ABSOLUTE::GetAbsoluteExistenceLevel() const
{
    return AbsoluteExistenceLevel;
}

float UP01_EXST_ABSOLUTE::GetAbsoluteExistencePowerCost() const
{
    return AbsoluteExistencePowerCost;
}

void UP01_EXST_ABSOLUTE::ChannelAbsoluteLifeForce()
{
    if (bIsAbsoluteExistenceActive)
    {
        float LifeForcePower = AbsoluteLifeForce * (AbsoluteExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Absolute Life Force with power: %.2f"), LifeForcePower);
        // Apply absolute life force effects
    }
}

void UP01_EXST_ABSOLUTE::AchieveEternalPerpetuation()
{
    if (bIsAbsoluteExistenceActive)
    {
        float PerpetuationPower = EternalPerpetuation * (AbsoluteExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Eternal Perpetuation with power: %.2f"), PerpetuationPower);
        // Apply eternal perpetuation effects
    }
}

void UP01_EXST_ABSOLUTE::MaintainInfiniteContinuum()
{
    if (bIsAbsoluteExistenceActive)
    {
        float ContinuumPower = InfiniteContinuum * (AbsoluteExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Maintaining Infinite Continuum with power: %.2f"), ContinuumPower);
        // Apply infinite continuum effects
    }
}

void UP01_EXST_ABSOLUTE::PerpetuateTimelessly()
{
    if (bIsAbsoluteExistenceActive)
    {
        float PerpetuationPower = TimelessPerpetuation * (AbsoluteExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Perpetuating Timelessly with power: %.2f"), PerpetuationPower);
        // Apply timeless perpetuation effects
    }
}

void UP01_EXST_ABSOLUTE::AchieveAbsoluteSelfSufficiency()
{
    if (bIsAbsoluteExistenceActive)
    {
        float SufficiencyPower = AbsoluteSelfSufficiency * (AbsoluteExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Absolute Self-Sufficiency with power: %.2f"), SufficiencyPower);
        // Apply absolute self-sufficiency effects
    }
}

bool UP01_EXST_ABSOLUTE::CanActivateAbsoluteExistence() const
{
    return AbsoluteExistenceLevel > 0;
}

void UP01_EXST_ABSOLUTE::UpdateAbsoluteExistenceStats()
{
    // Update absolute existence properties based on level
    AbsoluteLifeForce = AbsoluteExistenceLevel * 1.5f;
    EternalPerpetuation = AbsoluteExistenceLevel * 1.3f;
    InfiniteContinuum = AbsoluteExistenceLevel * 1.4f;
    TimelessPerpetuation = AbsoluteExistenceLevel * 1.2f;
    AbsoluteSelfSufficiency = AbsoluteExistenceLevel * 1.6f;
}

void UP01_EXST_ABSOLUTE::OnAbsoluteExistenceStateChanged()
{
    // Handle state change effects
    if (bIsAbsoluteExistenceActive)
    {
        // Apply absolute existence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Absolute Existence state changed to ACTIVE"));
    }
    else
    {
        // Remove absolute existence effects
        UE_LOG(LogTemp, Warning, TEXT("Absolute Existence state changed to INACTIVE"));
    }
}
