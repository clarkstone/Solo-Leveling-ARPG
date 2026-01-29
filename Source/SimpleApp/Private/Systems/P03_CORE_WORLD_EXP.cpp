#include "P03_CORE_WORLD_EXP.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP03_CORE_WORLD_EXP::UP03_CORE_WORLD_EXP()
{
    PrimaryComponentTick.bCanEverTick = false;
    WorldExpansionLevel = 0;
    MaxWorldExpansionLevel = 100;
    bIsWorldExpansionActive = false;
    WorldExpansionPowerCost = 10.0f;
    WorldExpansionThreshold = 10.0f;
    
    // Initialize world expansion properties
    WorldCreation = 0.0f;
    DimensionalExpansion = 0.0f;
    RealityManipulation = 0.0f;
    WorldControl = 0.0f;
}

void UP03_CORE_WORLD_EXP::BeginPlay()
{
    Super::BeginPlay();
    UpdateWorldExpansionStats();
}

void UP03_CORE_WORLD_EXP::ActivateWorldExpansion()
{
    if (!bIsWorldExpansionActive && CanActivateWorldExpansion())
    {
        bIsWorldExpansionActive = true;
        OnWorldExpansionActivated.Broadcast(WorldExpansionLevel);
        OnWorldExpansionStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("World Expansion System Activated at Level: %d"), WorldExpansionLevel);
    }
}

void UP03_CORE_WORLD_EXP::DeactivateWorldExpansion()
{
    if (bIsWorldExpansionActive)
    {
        bIsWorldExpansionActive = false;
        OnWorldExpansionDeactivated.Broadcast(WorldExpansionLevel);
        OnWorldExpansionStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("World Expansion System Deactivated."));
    }
}

void UP03_CORE_WORLD_EXP::SetWorldExpansionLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxWorldExpansionLevel)
    {
        int32 OldLevel = WorldExpansionLevel;
        WorldExpansionLevel = NewLevel;
        UpdateWorldExpansionStats();
        OnWorldExpansionLevelChanged.Broadcast(OldLevel, WorldExpansionLevel);
        UE_LOG(LogTemp, Warning, TEXT("World Expansion Level set to: %d"), WorldExpansionLevel);
        
        if (WorldExpansionLevel >= MaxWorldExpansionLevel)
        {
            OnWorldExpansionMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("World Expansion Max Level Reached!"));
        }
    }
}

void UP03_CORE_WORLD_EXP::UseWorldExpansionPower()
{
    if (bIsWorldExpansionActive && WorldExpansionLevel > 0)
    {
        OnWorldExpansionPowerUsed.Broadcast(WorldExpansionPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("World Expansion Power Used: %.2f"), WorldExpansionPowerCost);
    }
    else
    {
        OnWorldExpansionPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("World Expansion Power Use Failed: System not active or insufficient level."));
    }
}

void UP03_CORE_WORLD_EXP::PerformWorldExpansionAbility()
{
    if (bIsWorldExpansionActive && WorldExpansionLevel >= WorldExpansionThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing World Expansion Ability at Level %d!"), WorldExpansionLevel);
        OnWorldExpansionAbilityPerformed.Broadcast(WorldExpansionLevel);
        UseWorldExpansionPower();
        
        // Perform world expansion ability based on level
        switch (WorldExpansionLevel / 20)
        {
            case 0:
                CreateWorlds();
                break;
            case 1:
                ExpandDimensions();
                break;
            case 2:
                ManipulateReality();
                break;
            case 3:
                ControlWorld();
                break;
            default:
                ControlWorld();
                break;
        }
    }
    }
    else if (WorldExpansionLevel < WorldExpansionThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("World Expansion Level too low to perform ability. Required: %.0f, Current: %d"), WorldExpansionThreshold, WorldExpansionLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("World Expansion is not active, cannot perform ability."));
    }
}

bool UP03_CORE_WORLD_EXP::IsWorldExpansionActive() const
{
    return bIsWorldExpansionActive;
}

int32 UP03_CORE_WORLD_EXP::GetWorldExpansionLevel() const
{
    return WorldExpansionLevel;
}

float UP03_CORE_WORLD_EXP::GetWorldExpansionPowerCost() const
{
    return WorldExpansionPowerCost;
}

void UP03_CORE_WORLD_EXP::CreateWorlds()
{
    if (bIsWorldExpansionActive)
    {
        float CreationPower = WorldCreation * (WorldExpansionLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Creating Worlds with power: %.2f"), CreationPower);
        // Apply world creation effects
    }
}

void UP03_CORE_WORLD_EXP::ExpandDimensions()
{
    if (bIsWorldExpansionActive)
    {
        float ExpansionPower = DimensionalExpansion * (WorldExpansionLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Expanding Dimensions with power: %.2f"), ExpansionPower);
        // Apply dimensional expansion effects
    }
}

void UP03_CORE_WORLD_EXP::ManipulateReality()
{
    if (bIsWorldExpansionActive)
    {
        float RealityPower = RealityManipulation * (WorldExpansionLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Manipulating Reality with power: %.2f"), RealityPower);
        // Apply reality manipulation effects
    }
}

void UP03_CORE_WORLD_EXP::ControlWorld()
{
    if (bIsWorldExpansionActive)
    {
        float WorldPower = WorldControl * (WorldExpansionLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling World with power: %.2f"), WorldPower);
        // Apply world control effects
    }
}

bool UP03_CORE_WORLD_EXP::CanActivateWorldExpansion() const
{
    return WorldExpansionLevel > 0;
}

void UP03_CORE_WORLD_EXP::UpdateWorldExpansionStats()
{
    // Update world expansion properties based on level
    WorldCreation = WorldExpansionLevel * 1.4f;
    DimensionalExpansion = WorldExpansionLevel * 1.6f;
    RealityManipulation = WorldExpansionLevel * 1.5f;
    WorldControl = WorldExpansionLevel * 1.7f;
}

void UP03_CORE_WORLD_EXP::OnWorldExpansionStateChanged()
{
    // Handle state change effects
    if (bIsWorldExpansionActive)
    {
        // Apply world expansion activation effects
        UE_LOG(LogTemp, Warning, TEXT("World Expansion state changed to ACTIVE"));
    }
    else
    {
        // Remove world expansion effects
        UE_LOG(LogTemp, Warning, TEXT("World Expansion state changed to INACTIVE"));
    }
}
