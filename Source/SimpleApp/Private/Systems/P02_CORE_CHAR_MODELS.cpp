#include "P02_CORE_CHAR_MODELS.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP02_CORE_CHAR_MODELS::UP02_CORE_CHAR_MODELS()
{
    PrimaryComponentTick.bCanEverTick = false;
    CharacterModelsLevel = 0;
    MaxCharacterModelsLevel = 100;
    bIsCharacterModelsActive = false;
    CharacterModelsPowerCost = 10.0f;
    CharacterModelsThreshold = 10.0f;
    
    // Initialize character models properties
    ModelCreation = 0.0f;
    AnimationSystem = 0.0f;
    VisualEffects = 0.0f;
}

void UP02_CORE_CHAR_MODELS::BeginPlay()
{
    Super::BeginPlay();
    UpdateCharacterModelsStats();
}

void UP02_CORE_CHAR_MODELS::ActivateCharacterModels()
{
    if (!bIsCharacterModelsActive && CanActivateCharacterModels())
    {
        bIsCharacterModelsActive = true;
        OnCharacterModelsActivated.Broadcast(CharacterModelsLevel);
        OnCharacterModelsStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Character Models System Activated at Level: %d"), CharacterModelsLevel);
    }
}

void UP02_CORE_CHAR_MODELS::DeactivateCharacterModels()
{
    if (bIsCharacterModelsActive)
    {
        bIsCharacterModelsActive = false;
        OnCharacterModelsDeactivated.Broadcast(CharacterModelsLevel);
        OnCharacterModelsStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Character Models System Deactivated."));
    }
}

void UP02_CORE_CHAR_MODELS::SetCharacterModelsLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxCharacterModelsLevel)
    {
        int32 OldLevel = CharacterModelsLevel;
        CharacterModelsLevel = NewLevel;
        UpdateCharacterModelsStats();
        OnCharacterModelsLevelChanged.Broadcast(OldLevel, CharacterModelsLevel);
        UE_LOG(LogTemp, Warning, TEXT("Character Models Level set to: %d"), CharacterModelsLevel);
        
        if (CharacterModelsLevel >= MaxCharacterModelsLevel)
        {
            OnCharacterModelsMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Character Models Max Level Reached!"));
        }
    }
}

void UP02_CORE_CHAR_MODELS::UseCharacterModelsPower()
{
    if (bIsCharacterModelsActive && CharacterModelsLevel > 0)
    {
        OnCharacterModelsPowerUsed.Broadcast(CharacterModelsPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Character Models Power Used: %.2f"), CharacterModelsPowerCost);
    }
    else
    {
        OnCharacterModelsPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Character Models Power Use Failed: System not active or insufficient level."));
    }
}

void UP02_CORE_CHAR_MODELS::PerformCharacterModelsAbility()
{
    if (bIsCharacterModelsActive && CharacterModelsLevel >= CharacterModelsThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Character Models Ability at Level %d!"), CharacterModelsLevel);
        OnCharacterModelsAbilityPerformed.Broadcast(CharacterModelsLevel);
        UseCharacterModelsPower();
        
        // Perform character models ability based on level
        switch (CharacterModelsLevel / 20)
        {
            case 0:
                CreateModels();
                break;
            case 1:
                AccessAnimationSystem();
                break;
            case 2:
                ApplyVisualEffects();
                break;
            case 3:
                AchieveModelCreation();
                break;
            default:
                AchieveModelCreation();
                break;
        }
    }
    }
    }
    else if (CharacterModelsLevel < CharacterModelsThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Character Models Level too low to perform ability. Required: %.0f, Current: %d"), CharacterModelsThreshold, CharacterModelsLevel);
    }
    else
    {
        UE_LOG(LogTemp, TEXT("Character Models is not active, cannot perform ability."));
    }
}

bool UP02_CORE_CHAR_MODELS::IsCharacterModelsActive() const
{
    return bIsCharacterModelsActive;
}

int32 UP02_CORE_CHAR_MODELS::GetCharacterModelsLevel() const
{
    return CharacterModelsLevel;
}

float UP02_CORE_CHAR_MODELS::GetCharacterModelsPowerCost() const
{
    return CharacterModelsPowerCost;
}

void UP02_CORE_CHAR_MODELS::CreateModels()
{
    if (bIsCharacterModelsActive)
    {
        float CreationPower = ModelCreation * (CharacterModelsLevel / 100.0f);
        UE_LOG(LogTemp, TEXT("Creating Models with power: %.2f"), CreationPower);
        // Apply model creation effects
    }
}

void UP02_CORE_CHAR_MODELS::AccessAnimationSystem()
{
    if (bIsCharacterModelsActive)
    {
        float AnimationPower = AnimationSystem * (CharacterModelsLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Animation System with power: %.2f"), AnimationPower);
        // Apply animation system effects
    }
}

void UP02_CORE_CHAR_MODELS::ApplyVisualEffects()
{
    if (bIsCharacterModelsActive)
    {
        float VFXPower = VisualEffects * (CharacterModelsLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Applying Visual Effects with power: %.2f"), VFXPower);
        // Apply visual effects
    }
}

void UP02_CORE_CHAR_MODELS::AchieveModelCreation()
{
    if (bIsCharacterModelsActive)
    {
        float CreationPower = ModelCreation * (CharacterModelsLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Model Creation with power: %.2f"), CreationPower);
        // Apply model creation effects
    }
}

bool UP02_CORE_CHAR_MODELS::CanActivateCharacterModels() const
{
    return CharacterModelsLevel > 0;
}

void UP02_CORE_CHAR_MODELS::UpdateCharacterModelsStats()
{
    // Update character models properties based on level
    ModelCreation = CharacterModelsLevel * 1.5f;
    AnimationSystem = CharacterModelsLevel * 1.2f;
    VisualEffects = CharacterModelsLevel * 1.3f;
}

void UP02_CORE_CHAR_MODELS::OnCharacterModelsStateChanged()
{
    // Handle state change effects
    if (bIsCharacterModelsActive)
    {
        // Apply character models activation effects
        UE_LOG(LogTemp, Warning, TEXT("Character Models state changed to ACTIVE"));
    }
    else
    {
        // Remove character models effects
        UE_LOG(LogTemp, Warning, TEXT("Character Models state changed to INACTIVE"));
    }
}
