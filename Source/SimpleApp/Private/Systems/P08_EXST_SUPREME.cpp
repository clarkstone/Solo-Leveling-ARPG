#include "P08_EXST_SUPREME.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP08_EXST_SUPREME::UP08_EXST_SUPREME()
{
    PrimaryComponentTick.bCanEverTick = false;
    SupremeExistenceLevel = 0;
    MaxSupremeExistenceLevel = 100;
    bIsSupremeExistenceActive = false;
    SupremeExistencePowerCost = 45.0f;
    SupremeExistenceThreshold = 45.0f;
    
    // Initialize supreme existence properties
    SupremeLifeForce = 0.0f;
    SupremePerpetuation = 0.0f;
    SupremeInfiniteContinuum = 0.0f;
    SupremeTimelessPerpetuation = 0.0f;
    SupremeSelfSufficiency = 0.0f;
}

void UP08_EXST_SUPREME::BeginPlay()
{
    Super::BeginPlay();
    UpdateSupremeExistenceStats();
}

void UP08_EXST_SUPREME::ActivateSupremeExistence()
{
    if (!bIsSupremeExistenceActive && CanActivateSupremeExistence())
    {
        bIsSupremeExistenceActive = true;
        OnSupremeExistenceActivated.Broadcast(SupremeExistenceLevel);
        OnSupremeExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Supreme Existence System Activated at Level: %d"), SupremeExistenceLevel);
    }
}

void UP08_EXST_SUPREME::DeactivateSupremeExistence()
{
    if (bIsSupremeExistenceActive)
    {
        bIsSupremeExistenceActive = false;
        OnSupremeExistenceDeactivated.Broadcast(SupremeExistenceLevel);
        OnSupremeExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Supreme Existence System Deactivated."));
    }
}

void UP08_EXST_SUPREME::SetSupremeExistenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxSupremeExistenceLevel)
    {
        int32 OldLevel = SupremeExistenceLevel;
        SupremeExistenceLevel = NewLevel;
        UpdateSupremeExistenceStats();
        OnSupremeExistenceLevelChanged.Broadcast(OldLevel, SupremeExistenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Supreme Existence Level set to: %d"), SupremeExistenceLevel);
        
        if (SupremeExistenceLevel >= MaxSupremeExistenceLevel)
        {
            OnSupremeExistenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Supreme Existence Max Level Reached!"));
        }
    }
}

void UP08_EXST_SUPREME::UseSupremeExistencePower()
{
    if (bIsSupremeExistenceActive && SupremeExistenceLevel > 0)
    {
        OnSupremeExistencePowerUsed.Broadcast(SupremeExistencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Supreme Existence Power Used: %.2f"), SupremeExistencePowerCost);
    }
    else
    {
        OnSupremeExistencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Supreme Existence Power Use Failed: System not active or insufficient level."));
    }
}

void UP08_EXST_SUPREME::PerformSupremeExistenceAbility()
{
    if (bIsSupremeExistenceActive && SupremeExistenceLevel >= SupremeExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Supreme Existence Ability at Level %d!"), SupremeExistenceLevel);
        OnSupremeExistenceAbilityPerformed.Broadcast(SupremeExistenceLevel);
        UseSupremeExistencePower();
        
        // Perform supreme existence ability based on level
        switch (SupremeExistenceLevel / 20)
        {
            case 0:
                ChannelSupremeLifeForce();
                break;
            case 1:
                AchieveSupremePerpetuation();
                break;
            case 2:
                MaintainSupremeInfiniteContinuum();
                break;
            case 3:
                PerpetuateSupremeTimelessly();
                break;
            case 4:
            case 5:
                AchieveSupremeSelfSufficiency();
                break;
            default:
                AchieveSupremeSelfSufficiency();
                break;
        }
    }
    }
    else if (SupremeExistenceLevel < SupremeExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Supreme Existence Level too low to perform ability. Required: %.0f, Current: %d"), SupremeExistenceThreshold, SupremeExistenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Supreme Existence is not active, cannot perform ability."));
    }
}

bool UP08_EXST_SUPREME::IsSupremeExistenceActive() const
{
    return bIsSupremeExistenceActive;
}

int32 UP08_EXST_SUPREME::GetSupremeExistenceLevel() const
{
    return SupremeExistenceLevel;
}

float UP08_EXST_SUPREME::GetSupremeExistencePowerCost() const
{
    return SupremeExistencePowerCost;
}

void UP08_EXST_SUPREME::ChannelSupremeLifeForce()
{
    if (bIsSupremeExistenceActive)
    {
        float LifeForcePower = SupremeLifeForce * (SupremeExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Supreme Life Force with power: %.2f"), LifeForcePower);
        // Apply supreme life force effects
    }
}

void UP08_EXST_SUPREME::AchieveSupremePerpetuation()
{
    if (bIsSupremeExistenceActive)
    {
        float PerpetuationPower = SupremePerpetuation * (SupremeExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Supreme Perpetuation with power: %.2f"), PerpetuationPower);
        // Apply supreme perpetuation effects
    }
}

void UP08_EXST_SUPREME::MaintainSupremeInfiniteContinuum()
{
    if (bIsSupremeExistenceActive)
    {
        float ContinuumPower = SupremeInfiniteContinuum * (SupremeExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Maintaining Supreme Infinite Continuum with power: %.2f"), ContinuumPower);
        // Apply supreme infinite continuum effects
    }
}

void UP08_EXST_SUPREME::PerpetuateSupremeTimelessly()
{
    if (bIsSupremeExistenceActive)
    {
        float PerpetuationPower = SupremeTimelessPerpetuation * (SupremeExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Perpetuating Supreme Timelessly with power: %.2f"), PerpetuationPower);
        // Apply supreme timeless perpetuation effects
    }
}

void UP08_EXST_SUPREME::AchieveSupremeSelfSufficiency()
{
    if (bIsSupremeExistenceActive)
    {
        float SufficiencyPower = SupremeSelfSufficiency * (SupremeExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Supreme Self-Sufficiency with power: %.2f"), SufficiencyPower);
        // Apply supreme self-sufficiency effects
    }
}

bool UP08_EXST_SUPREME::CanActivateSupremeExistence() const
{
    return SupremeExistenceLevel > 0;
}

void UP08_EXST_SUPREME::UpdateSupremeExistenceStats()
{
    // Update supreme existence properties based on level
    SupremeLifeForce = SupremeExistenceLevel * 4.0f;
    SupremePerpetuation = SupremeExistenceLevel * 3.8f;
    SupremeInfiniteContinuum = SupremeExistenceLevel * 3.9f;
    SupremeTimelessPerpetuation = SupremeExistenceLevel * 3.7f;
    SupremeSelfSufficiency = SupremeExistenceLevel * 4.1f;
}

void UP08_EXST_SUPREME::OnSupremeExistenceStateChanged()
{
    // Handle state change effects
    if (bIsSupremeExistenceActive)
    {
        // Apply supreme existence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Supreme Existence state changed to ACTIVE"));
    }
    else
    {
        // Remove supreme existence effects
        UE_LOG(LogTemp, Warning, TEXT("Supreme Existence state changed to INACTIVE"));
    }
}
