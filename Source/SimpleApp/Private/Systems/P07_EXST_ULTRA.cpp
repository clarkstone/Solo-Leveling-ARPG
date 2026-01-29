#include "P07_EXST_ULTRA.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP07_EXST_ULTRA::UP07_EXST_ULTRA()
{
    PrimaryComponentTick.bCanEverTick = false;
    UltraExistenceLevel = 0;
    MaxUltraExistenceLevel = 100;
    bIsUltraExistenceActive = false;
    UltraExistencePowerCost = 40.0f;
    UltraExistenceThreshold = 40.0f;
    
    // Initialize ultra existence properties
    UltraLifeForce = 0.0f;
    UltraPerpetuation = 0.0f;
    UltraInfiniteContinuum = 0.0f;
    UltraTimelessPerpetuation = 0.0f;
    UltraSelfSufficiency = 0.0f;
}

void UP07_EXST_ULTRA::BeginPlay()
{
    Super::BeginPlay();
    UpdateUltraExistenceStats();
}

void UP07_EXST_ULTRA::ActivateUltraExistence()
{
    if (!bIsUltraExistenceActive && CanActivateUltraExistence())
    {
        bIsUltraExistenceActive = true;
        OnUltraExistenceActivated.Broadcast(UltraExistenceLevel);
        OnUltraExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Ultra Existence System Activated at Level: %d"), UltraExistenceLevel);
    }
}

void UP07_EXST_ULTRA::DeactivateUltraExistence()
{
    if (bIsUltraExistenceActive)
    {
        bIsUltraExistenceActive = false;
        OnUltraExistenceDeactivated.Broadcast(UltraExistenceLevel);
        OnUltraExistenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Ultra Existence System Deactivated."));
    }
}

void UP07_EXST_ULTRA::SetUltraExistenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxUltraExistenceLevel)
    {
        int32 OldLevel = UltraExistenceLevel;
        UltraExistenceLevel = NewLevel;
        UpdateUltraExistenceStats();
        OnUltraExistenceLevelChanged.Broadcast(OldLevel, UltraExistenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Ultra Existence Level set to: %d"), UltraExistenceLevel);
        
        if (UltraExistenceLevel >= MaxUltraExistenceLevel)
        {
            OnUltraExistenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Ultra Existence Max Level Reached!"));
        }
    }
}

void UP07_EXST_ULTRA::UseUltraExistencePower()
{
    if (bIsUltraExistenceActive && UltraExistenceLevel > 0)
    {
        OnUltraExistencePowerUsed.Broadcast(UltraExistencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Ultra Existence Power Used: %.2f"), UltraExistencePowerCost);
    }
    else
    {
        OnUltraExistencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Ultra Existence Power Use Failed: System not active or insufficient level."));
    }
}

void UP07_EXST_ULTRA::PerformUltraExistenceAbility()
{
    if (bIsUltraExistenceActive && UltraExistenceLevel >= UltraExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Ultra Existence Ability at Level %d!"), UltraExistenceLevel);
        OnUltraExistenceAbilityPerformed.Broadcast(UltraExistenceLevel);
        UseUltraExistencePower();
        
        // Perform ultra existence ability based on level
        switch (UltraExistenceLevel / 20)
        {
            case 0:
                ChannelUltraLifeForce();
                break;
            case 1:
                AchieveUltraPerpetuation();
                break;
            case 2:
                MaintainUltraInfiniteContinuum();
                break;
            case 3:
                PerpetuateUltraTimelessly();
                break;
            case 4:
            case 5:
                AchieveUltraSelfSufficiency();
                break;
            default:
                AchieveUltraSelfSufficiency();
                break;
        }
    }
    }
    else if (UltraExistenceLevel < UltraExistenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ultra Existence Level too low to perform ability. Required: %.0f, Current: %d"), UltraExistenceThreshold, UltraExistenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Ultra Existence is not active, cannot perform ability."));
    }
}

bool UP07_EXST_ULTRA::IsUltraExistenceActive() const
{
    return bIsUltraExistenceActive;
}

int32 UP07_EXST_ULTRA::GetUltraExistenceLevel() const
{
    return UltraExistenceLevel;
}

float UP07_EXST_ULTRA::GetUltraExistencePowerCost() const
{
    return UltraExistencePowerCost;
}

void UP07_EXST_ULTRA::ChannelUltraLifeForce()
{
    if (bIsUltraExistenceActive)
    {
        float LifeForcePower = UltraLifeForce * (UltraExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Ultra Life Force with power: %.2f"), LifeForcePower);
        // Apply ultra life force effects
    }
}

void UP07_EXST_ULTRA::AchieveUltraPerpetuation()
{
    if (bIsUltraExistenceActive)
    {
        float PerpetuationPower = UltraPerpetuation * (UltraExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Ultra Perpetuation with power: %.2f"), PerpetuationPower);
        // Apply ultra perpetuation effects
    }
}

void UP07_EXST_ULTRA::MaintainUltraInfiniteContinuum()
{
    if (bIsUltraExistenceActive)
    {
        float ContinuumPower = UltraInfiniteContinuum * (UltraExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Maintaining Ultra Infinite Continuum with power: %.2f"), ContinuumPower);
        // Apply ultra infinite continuum effects
    }
}

void UP07_EXST_ULTRA::PerpetuateUltraTimelessly()
{
    if (bIsUltraExistenceActive)
    {
        float PerpetuationPower = UltraTimelessPerpetuation * (UltraExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Perpetuating Ultra Timelessly with power: %.2f"), PerpetuationPower);
        // Apply ultra timeless perpetuation effects
    }
}

void UP07_EXST_ULTRA::AchieveUltraSelfSufficiency()
{
    if (bIsUltraExistenceActive)
    {
        float SufficiencyPower = UltraSelfSufficiency * (UltraExistenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Ultra Self-Sufficiency with power: %.2f"), SufficiencyPower);
        // Apply ultra self-sufficiency effects
    }
}

bool UP07_EXST_ULTRA::CanActivateUltraExistence() const
{
    return UltraExistenceLevel > 0;
}

void UP07_EXST_ULTRA::UpdateUltraExistenceStats()
{
    // Update ultra existence properties based on level
    UltraLifeForce = UltraExistenceLevel * 3.5f;
    UltraPerpetuation = UltraExistenceLevel * 3.3f;
    UltraInfiniteContinuum = UltraExistenceLevel * 3.4f;
    UltraTimelessPerpetuation = UltraExistenceLevel * 3.2f;
    UltraSelfSufficiency = UltraExistenceLevel * 3.6f;
}

void UP07_EXST_ULTRA::OnUltraExistenceStateChanged()
{
    // Handle state change effects
    if (bIsUltraExistenceActive)
    {
        // Apply ultra existence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Ultra Existence state changed to ACTIVE"));
    }
    else
    {
        // Remove ultra existence effects
        UE_LOG(LogTemp, Warning, TEXT("Ultra Existence state changed to INACTIVE"));
    }
}
