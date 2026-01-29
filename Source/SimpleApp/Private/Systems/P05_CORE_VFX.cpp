#include "P05_CORE_VFX.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP05_CORE_VFX::UP05_CORE_VFX()
{
    PrimaryComponentTick.bCanEverTick = false;
    VisualEffectsLevel = 0;
    MaxVisualEffectsLevel = 100;
    bIsVisualEffectsActive = false;
    VisualEffectsPowerCost = 20.0f;
    VisualEffectsThreshold = 20.0f;
    
    // Initialize visual effects properties
    VFXPower = 0.0f;
}

void UP05_CORE_VFX::BeginPlay()
{
    Super::BeginPlay();
    UpdateVisualEffectsStats();
}

void UP05_CORE_VFX::ActivateVisualEffects()
{
    if (!bIsVisualEffectsActive && CanActivateVisualEffects())
    {
        bIsVisualEffectsActive = true;
        OnVisualEffectsActivated.Broadcast(VisualEffectsLevel);
        OnVisualEffectsStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Visual Effects System Activated at Level: %d"), VisualEffectsLevel);
    }
}

void UP05_CORE_VFX::DeactivateVisualEffects()
{
    if (bIsVisualEffectsActive)
    {
        bIsVisualEffectsActive = false;
        OnVisualEffectsDeactivated.Broadcast(VisualEffectsLevel);
        OnVisualEffectsStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Visual Effects System Deactivated."));
    }
}

void UP05_CORE_VFX::SetVisualEffectsLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxVisualEffectsLevel)
    {
        int32 OldLevel = VisualEffectsLevel;
        VisualEffectsLevel = NewLevel;
        UpdateVisualEffectsStats();
        OnVisualEffectsLevelChanged.Broadcast(OldLevel, VisualEffectsLevel);
        UE_LOG(LogTemp, Warning, TEXT("Visual Effects Level set to: %d"), VisualEffectsLevel);
        
        if (VisualEffectsLevel >= MaxVisualEffectsLevel)
        {
            OnVisualEffectsMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Visual Effects Max Level Reached!"));
        }
    }
}

void UP05_CORE_VFX::UseVisualEffectsPower()
{
    if (bIsVisualEffectsActive && VisualEffectsLevel > 0)
    {
        OnVisualEffectsPowerUsed.Broadcast(VisualEffectsPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Visual Effects Power Used: %.2f"), VisualEffectsPowerCost);
    }
    else
    {
        OnVisualEffectsPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Visual Effects Power Use Failed: System not active or insufficient level."));
    }
}

void UP05_CORE_VFX::PerformVisualEffectsAbility()
{
    if (bIsVisualEffectsActive && VisualEffectsLevel >= VisualEffectsThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Visual Effects Ability at Level %d!"), VisualEffectsLevel);
        OnVisualEffectsAbilityPerformed.Broadcast(VisualEffectsLevel);
        UseVisualEffectsPower();
        
        // Perform visual effects ability based on level
        switch (VisualEffectsLevel / 20)
        {
            case 0:
                ManipulateVisualReality();
                break;
            case 1:
                ControlVisualTime();
                break;
            case 2:
                AlterVisualPerception();
                break;
            default:
                AlterVisualPerception();
                break;
        }
    }
    }
    }
    else if (VisualEffectsLevel < VisualEffectsThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Visual Effects Level too low to perform ability. Required: %.0f, Current: %d"), VisualEffectsThreshold, VisualEffectsLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Visual Effects is not active, cannot perform ability."));
    }
}

bool UP05_CORE_VFX::IsVisualEffectsActive() const
{
    return bIsVisualEffectsActive;
}

int32 UP05_CORE_VFX::GetVisualEffectsLevel() const
{
    return VisualEffectsLevel;
}

float UP05_CORE_VFX::GetVisualEffectsPowerCost() const
{
    return VisualEffectsPowerCost;
}

void UP05_CORE_VFX::ManipulateVisualReality()
{
    if (bIsVisualEffectsActive)
    {
        float RealityPower = VFXPower * (VisualEffectsLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Manipulating Visual Reality with power: %.2f"), RealityPower);
        // Apply visual reality manipulation effects
    }
}

void UP05_CORE_VFX::ControlVisualTime()
{
    if (bIsVisualEffectsActive)
    {
        float TimePower = VFXPower * (VisualEffectsLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Visual Time with power: %.2f"), TimePower);
        // Apply visual time control effects
    }
}

void UP05_CORE_VFX::AlterVisualPerception()
{
    if (bIsVisualEffectsActive)
    {
        float PerceptionPower = VFXPower * (VisualEffectsLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Altering Visual Perception with power: %.2f"), PerceptionPower);
        // Apply visual perception effects
    }
}

bool UP05_CORE_VFX::CanActivateVisualEffects() const
{
    return VisualEffectsLevel > 0;
}

void UP05_CORE_VFX::UpdateVisualEffectsStats()
{
    // Update visual effects properties based on level
    VFXPower = VisualEffectsLevel * 2.5f;
}

void UP05_CORE_VFX::OnVisualEffectsStateChanged()
{
    // Handle state change effects
    if (bIsVisualEffectsActive)
    {
        // Apply visual effects activation effects
        UE_LOG(LogTemp, Warning, TEXT("Visual Effects state changed to ACTIVE"));
    }
    else
    {
        // Remove visual effects effects
        UE_LOG(LogTemp, Warning, TEXT("Visual Effects state changed to INACTIVE"));
    }
}
