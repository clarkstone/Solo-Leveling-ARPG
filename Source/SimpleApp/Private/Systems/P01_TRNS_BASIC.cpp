#include "P01_TRNS_BASIC.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP01_TRNS_BASIC::UP01_TRNS_BASIC()
{
    PrimaryComponentTick.bCanEverTick = false;
    BasicTranscendenceLevel = 0;
    MaxBasicTranscendenceLevel = 100;
    bIsBasicTranscendenceActive = false;
    BasicTranscendencePowerCost = 10.0f;
    BasicTranscendenceThreshold = 10.0f;
    
    // Initialize basic transcendence properties
    TranscendencePower = 0.0f;
    RealityManipulation = 0.0f;
    EssenceControl = 0.0f;
    DimensionalShift = 0.0f;
    TimeControl = 0.0f;
    ExistenceOverride = 0.0f;
}

void UP01_TRNS_BASIC::BeginPlay()
{
    Super::BeginPlay();
    UpdateBasicTranscendenceStats();
}

void UP01_TRNS_BASIC::ActivateBasicTranscendence()
{
    if (!bIsBasicTranscendenceActive && CanActivateBasicTranscendence())
    {
        bIsBasicTranscendenceActive = true;
        OnBasicTranscendenceActivated.Broadcast(BasicTranscendenceLevel);
        OnBasicTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Basic Transcendence System Activated at Level: %d"), BasicTranscendenceLevel);
    }
}

void UP01_TRNS_BASIC::DeactivateBasicTranscendence()
{
    if (bIsBasicTranscendenceActive)
    {
        bIsBasicTranscendenceActive = false;
        OnBasicTranscendenceDeactivated.Broadcast(BasicTranscendenceLevel);
        OnBasicTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Basic Transcendence System Deactivated."));
    }
}

void UP01_TRNS_BASIC::SetBasicTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxBasicTranscendenceLevel)
    {
        int32 OldLevel = BasicTranscendenceLevel;
        BasicTranscendenceLevel = NewLevel;
        UpdateBasicTranscendenceStats();
        OnBasicTranscendenceLevelChanged.Broadcast(OldLevel, BasicTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Basic Transcendence Level set to: %d"), BasicTranscendenceLevel);
        
        if (BasicTranscendenceLevel >= MaxBasicTranscendenceLevel)
        {
            OnBasicTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Basic Transcendence Max Level Reached!"));
        }
    }
}

void UP01_TRNS_BASIC::UseBasicTranscendencePower()
{
    if (bIsBasicTranscendenceActive && BasicTranscendenceLevel > 0)
    {
        OnBasicTranscendencePowerUsed.Broadcast(BasicTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Basic Transcendence Power Used: %.2f"), BasicTranscendencePowerCost);
    }
    else
    {
        OnBasicTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Basic Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UP01_TRNS_BASIC::PerformBasicTranscendenceAbility()
{
    if (bIsBasicTranscendenceActive && BasicTranscendenceLevel >= BasicTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Basic Transcendence Ability at Level %d!"), BasicTranscendenceLevel);
        OnBasicTranscendenceAbilityPerformed.Broadcast(BasicTranscendenceLevel);
        UseBasicTranscendencePower();
        
        // Perform basic transcendence ability based on level
        switch (BasicTranscendenceLevel / 20)
        {
            case 0:
                ManipulateReality();
                break;
            case 1:
                ControlEssence();
                break;
            case 2:
                ShiftDimensions();
                break;
            case 3:
                ControlTime();
                break;
            case 4:
            case 5:
                OverrideExistence();
                break;
            default:
                OverrideExistence();
                break;
        }
    }
    }
    else if (BasicTranscendenceLevel < BasicTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Basic Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), BasicTranscendenceThreshold, BasicTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Basic Transcendence is not active, cannot perform ability."));
    }
}

bool UP01_TRNS_BASIC::IsBasicTranscendenceActive() const
{
    return bIsBasicTranscendenceActive;
}

int32 UP01_TRNS_BASIC::GetBasicTranscendenceLevel() const
{
    return BasicTranscendenceLevel;
}

float UP01_TRNS_BASIC::GetBasicTranscendencePowerCost() const
{
    return BasicTranscendencePowerCost;
}

void UP01_TRNS_BASIC::ManipulateReality()
{
    if (bIsBasicTranscendenceActive)
    {
        float RealityPower = RealityManipulation * (BasicTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Manipulating Reality with power: %.2f"), RealityPower);
        // Apply reality manipulation effects
    }
}

void UP01_TRNS_BASIC::ControlEssence()
{
    if (bIsBasicTranscendenceActive)
    {
        float EssencePower = EssenceControl * (BasicTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Essence with power: %.2f"), EssencePower);
        // Apply essence control effects
    }
}

void UP01_TRNS_BASIC::ShiftDimensions()
{
    if (bIsBasicTranscendenceActive)
    {
        float DimensionalPower = DimensionalShift * (BasicTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Shifting Dimensions with power: %.2f"), DimensionalPower);
        // Apply dimensional shift effects
    }
}

void UP01_TRNS_BASIC::ControlTime()
{
    if (bIsBasicTranscendenceActive)
    {
        float TimePower = TimeControl * (BasicTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Time with power: %.2f"), TimePower);
        // Apply time control effects
    }
}

void UP01_TRNS_BASIC::OverrideExistence()
{
    if (bIsBasicTranscendenceActive)
    {
        float ExistencePower = ExistenceOverride * (BasicTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Overriding Existence with power: %.2f"), ExistencePower);
        // Apply existence override effects
    }
}

bool UP01_TRNS_BASIC::CanActivateBasicTranscendence() const
{
    return BasicTranscendenceLevel > 0;
}

void UP01_TRNS_BASIC::UpdateBasicTranscendenceStats()
{
    // Update basic transcendence properties based on level
    TranscendencePower = BasicTranscendenceLevel * 1.0f;
    RealityManipulation = BasicTranscendenceLevel * 1.2f;
    EssenceControl = BasicTranscendenceLevel * 1.1f;
    DimensionalShift = BasicTranscendenceLevel * 1.3f;
    TimeControl = BasicTranscendenceLevel * 1.4f;
    ExistenceOverride = BasicTranscendenceLevel * 1.5f;
}

void UP01_TRNS_BASIC::OnBasicTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsBasicTranscendenceActive)
    {
        // Apply basic transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Basic Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove basic transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Basic Transcendence state changed to INACTIVE"));
    }
}
