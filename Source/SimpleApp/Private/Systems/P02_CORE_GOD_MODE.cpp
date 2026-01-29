#include "P02_CORE_GOD_MODE.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP02_CORE_GOD_MODE::UP02_CORE_GOD_MODE()
{
    PrimaryComponentTick.bCanEverTick = false;
    GodModeLevel = 0;
    MaxGodModeLevel = 100;
    bIsGodModeActive = false;
    GodModePowerCost = 10.0f;
    GodModeThreshold = 10.0f;
    
    // Initialize god mode properties
    GodModePower = 0.0f;
    Invincibility = 0.0f;
    DivineAuthority = 0.0f;
    Omniscience = 0.0f;
}

void UP02_CORE_GOD_MODE::BeginPlay()
{
    Super::BeginPlay();
    UpdateGodModeStats();
}

void UP02_CORE_GOD_MODE::ActivateGodMode()
{
    if (!bIsGodModeActive && CanActivateGodMode())
    {
        bIsGodModeActive = true;
        OnGodModeActivated.Broadcast(GodModeLevel);
        OnGodModeStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("God Mode System Activated at Level: %d"), GodModeLevel);
    }
}

void UP02_CORE_GOD_MODE::DeactivateGodMode()
{
    if (bIsGodModeActive)
    {
        bIsGodModeActive = false;
        OnGodModeDeactivated.Broadcast(GodModeLevel);
        OnGodModeStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("God Mode System Deactivated."));
    }
}

void UP02_CORE_GOD_MODE::SetGodModeLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxGodModeLevel)
    {
        int32 OldLevel = GodModeLevel;
        GodModeLevel = NewLevel;
        UpdateGodModeStats();
        OnGodModeLevelChanged.Broadcast(OldLevel, GodModeLevel);
        UE_LOG(LogTemp, Warning, TEXT("God Mode Level set to: %d"), GodModeLevel);
        
        if (GodModeLevel >= MaxGodModeLevel)
        {
            OnGodModeMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, TEXT("God Mode Max Level Reached!"));
        }
    }
}

void UP02_CORE_GOD_MODE::UseGodModePower()
{
    if (bIsGodModeActive && GodModeLevel > 0)
    {
        OnGodModePowerUsed.Broadcast(GodModePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("God Mode Power Used: %.2f"), GodModePowerCost);
    }
    else
    {
        OnGodModePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("God Mode Power Use Failed: System not active or insufficient level."));
    }
}

void UP02_CORE_GOD_MODE::PerformGodModeAbility()
{
    if (bIsGodModeActive && GodModeLevel >= GodModeThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing God Mode Ability at Level %d!"), GodModeLevel);
        OnGodModeAbilityPerformed.Broadcast(GodModeLevel);
        UseGodModePower();
        
        // Perform god mode ability based on level
        switch (GodModeLevel / 20)
        {
            case 0:
                BecomeInvincible();
                break;
            case 1:
                WieldDivineAuthority();
                break;
            case 2:
                AccessOmniscience();
                break;
            case 3:
                AchieveOmniscience();
                break;
            default:
                AchieveOmniscience();
                break;
        }
    }
    }
    }
    else if (GodModeLevel < GodModeThreshold)
    {
        UE_LOG(LogTemp, TEXT("God Mode Level too low to perform ability. Required: %.0f, Current: %d"), GodModeThreshold, GodModeLevel);
    }
    else
    {
        UE_LOG(LogTemp, TEXT("God Mode is not active, cannot perform ability."));
    }
}

bool UP02_CORE_GOD_MODE::IsGodModeActive() const
{
    return bIsGodModeActive;
}

int32 UP02_CORE_GOD_MODE::GetGodModeLevel() const
{
    return GodModeLevel;
}

float UP02_CORE_GOD_MODE::GetGodModePowerCost() const
{
    return GodModePowerCost;
}

void UP02_CORE_GOD_MODE::BecomeInvincible()
{
    if (bIsGodModeActive)
    {
        float Invincibility = Invincibility * (GodModeLevel / 100.0f);
        UE_LOG(LogTemp, TEXT("Becoming Invincible with power: %.2f"), Invincibility);
        // Apply invincibility effects
    }
}

void UP02_CORE_GOD_MODE::WieldDivineAuthority()
{
    if (bIsGodModeActive)
    {
        float AuthorityPower = DivineAuthority * (GodModeLevel / 100.0f);
        UE_LOG(LogTemp, TEXT("Wielding Divine Authority with power: %.2f"), AuthorityPower);
        // Apply divine authority effects
    }
}

void UP02_CORE_GOD_MODE::AccessOmniscience()
{
    if (bIsGodModeActive)
    {
        float OmnisciencePower = Omniscience * (GodModeLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Omniscience with power: %.2f"), OmnisciencePower);
        // Apply omniscience effects
    }
}

void UP02_CORE_GOD_MODE::AchieveOmniscience()
{
    if (bIsGodModeActive)
    {
        float OmnisciencePower = Omniscience * (GodModeLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omniscience with power: %.2f"), OmnisciencePower);
        // Apply omniscience effects
    }
}

bool UP02_CORE_GOD_MODE::CanActivateGodMode() const
{
    return GodModeLevel > 0;
}

void UP02_CORE_GOD_MODE::UpdateGodModeStats()
{
    // Update god mode properties based on level
    GodModePower = GodModeLevel * 2.0f;
    Invincibility = GodModeLevel * 1.8f;
    DivineAuthority = GodModeLevel * 2.5f;
    Omniscience = GodModeLevel * 2.2f;
}

void UP02_CORE_GOD_MODE::OnGodModeStateChanged()
{
    // Handle state change effects
    if (bIsGodModeActive)
    {
        // Apply god mode activation effects
        UE_LOG(LogTemp, Warning, TEXT("God Mode state changed to ACTIVE"));
    }
    else
    {
        // Remove god mode effects
        UE_LOG(LogTemp, Warning, TEXT("God Mode state changed to INACTIVE"));
    }
}
