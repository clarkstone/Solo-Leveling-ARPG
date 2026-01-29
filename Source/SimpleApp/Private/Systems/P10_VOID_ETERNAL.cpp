#include "P10_VOID_ETERNAL.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP10_VOID_ETERNAL::UP10_VOID_ETERNAL()
{
    PrimaryComponentTick.bCanEverTick = false;
    EternalVoidLevel = 0;
    MaxEternalVoidLevel = 100;
    bIsEternalVoidActive = false;
    EternalVoidPowerCost = 55.0f;
    EternalVoidThreshold = 55.0f;
    
    // Initialize eternal void properties
    EternalVoidMastery = 0.0f;
    EternalUltimateAnnihilation = 0.0f;
    EternalPerfectVoidEmptiness = 0.0f;
    EternalConceptualUltimateOblivion = 0.0f;
    EternalExistenceUltimateNegation = 0.0f;
}

void UP10_VOID_ETERNAL::BeginPlay()
{
    Super::BeginPlay();
    UpdateEternalVoidStats();
}

void UP10_VOID_ETERNAL::ActivateEternalVoid()
{
    if (!bIsEternalVoidActive && CanActivateEternalVoid())
    {
        bIsEternalVoidActive = true;
        OnEternalVoidActivated.Broadcast(EternalVoidLevel);
        OnEternalVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Eternal Void System Activated at Level: %d"), EternalVoidLevel);
    }
}

void UP10_VOID_ETERNAL::DeactivateEternalVoid()
{
    if (bIsEternalVoidActive)
    {
        bIsEternalVoidActive = false;
        OnEternalVoidDeactivated.Broadcast(EternalVoidLevel);
        OnEternalVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Eternal Void System Deactivated."));
    }
}

void UP10_VOID_ETERNAL::SetEternalVoidLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxEternalVoidLevel)
    {
        int32 OldLevel = EternalVoidLevel;
        EternalVoidLevel = NewLevel;
        UpdateEternalVoidStats();
        OnEternalVoidLevelChanged.Broadcast(OldLevel, EternalVoidLevel);
        UE_LOG(LogTemp, Warning, TEXT("Eternal Void Level set to: %d"), EternalVoidLevel);
        
        if (EternalVoidLevel >= MaxEternalVoidLevel)
        {
            OnEternalVoidMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Eternal Void Max Level Reached!"));
        }
    }
}

void UP10_VOID_ETERNAL::UseEternalVoidPower()
{
    if (bIsEternalVoidActive && EternalVoidLevel > 0)
    {
        OnEternalVoidPowerUsed.Broadcast(EternalVoidPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Eternal Void Power Used: %.2f"), EternalVoidPowerCost);
    }
    else
    {
        OnEternalVoidPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Eternal Void Power Use Failed: System not active or insufficient level."));
    }
}

void UP10_VOID_ETERNAL::PerformEternalVoidAbility()
{
    if (bIsEternalVoidActive && EternalVoidLevel >= EternalVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Eternal Void Ability at Level %d!"), EternalVoidLevel);
        OnEternalVoidAbilityPerformed.Broadcast(EternalVoidLevel);
        UseEternalVoidPower();
        
        // Perform eternal void ability based on level
        switch (EternalVoidLevel / 20)
        {
            case 0:
                MasterEternalVoid();
                break;
            case 1:
                AnnihilateEternally();
                break;
            case 2:
                AchieveEternalPerfectVoidEmptiness();
                break;
            case 3:
                InduceEternalConceptualUltimateOblivion();
                break;
            case 4:
            case 5:
                NegateEternalUltimateExistence();
                break;
            default:
                NegateEternalUltimateExistence();
                break;
        }
    }
    }
    else if (EternalVoidLevel < EternalVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Eternal Void Level too low to perform ability. Required: %.0f, Current: %d"), EternalVoidThreshold, EternalVoidLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Eternal Void is not active, cannot perform ability."));
    }
}

bool UP10_VOID_ETERNAL::IsEternalVoidActive() const
{
    return bIsEternalVoidActive;
}

int32 UP10_VOID_ETERNAL::GetEternalVoidLevel() const
{
    return EternalVoidLevel;
}

float UP10_VOID_ETERNAL::GetEternalVoidPowerCost() const
{
    return EternalVoidPowerCost;
}

void UP10_VOID_ETERNAL::MasterEternalVoid()
{
    if (bIsEternalVoidActive)
    {
        float MasteryPower = EternalVoidMastery * (EternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Eternal Void with power: %.2f"), MasteryPower);
        // Apply eternal void mastery effects
    }
}

void UP10_VOID_ETERNAL::AnnihilateEternally()
{
    if (bIsEternalVoidActive)
    {
        float AnnihilationPower = EternalUltimateAnnihilation * (EternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Eternally with power: %.2f"), AnnihilationPower);
        // Apply eternal annihilation effects
    }
}

void UP10_VOID_ETERNAL::AchieveEternalPerfectVoidEmptiness()
{
    if (bIsEternalVoidActive)
    {
        float EmptinessPower = EternalPerfectVoidEmptiness * (EternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Eternal Perfect Void Emptiness with power: %.2f"), EmptinessPower);
        // Apply eternal perfect void emptiness effects
    }
}

void UP10_VOID_ETERNAL::InduceEternalConceptualUltimateOblivion()
{
    if (bIsEternalVoidActive)
    {
        float OblivionPower = EternalConceptualUltimateOblivion * (EternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Eternal Conceptual Ultimate Oblivion with power: %.2f"), OblivionPower);
        // Apply eternal conceptual ultimate oblivion effects
    }
}

void UP10_VOID_ETERNAL::NegateEternalUltimateExistence()
{
    if (bIsEternalVoidActive)
    {
        float NegationPower = EternalExistenceUltimateNegation * (EternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Eternal Ultimate Existence with power: %.2f"), NegationPower);
        // Apply eternal ultimate existence negation effects
    }
}

bool UP10_VOID_ETERNAL::CanActivateEternalVoid() const
{
    return EternalVoidLevel > 0;
}

void UP10_VOID_ETERNAL::UpdateEternalVoidStats()
{
    // Update eternal void properties based on level
    EternalVoidMastery = EternalVoidLevel * 5.5f;
    EternalUltimateAnnihilation = EternalVoidLevel * 5.7f;
    EternalPerfectVoidEmptiness = EternalVoidLevel * 5.6f;
    EternalConceptualUltimateOblivion = EternalVoidLevel * 5.4f;
    EternalExistenceUltimateNegation = EternalVoidLevel * 5.8f;
}

void UP10_VOID_ETERNAL::OnEternalVoidStateChanged()
{
    // Handle state change effects
    if (bIsEternalVoidActive)
    {
        // Apply eternal void activation effects
        UE_LOG(LogTemp, Warning, TEXT("Eternal Void state changed to ACTIVE"));
    }
    else
    {
        // Remove eternal void effects
        UE_LOG(LogTemp, Warning, TEXT("Eternal Void state changed to INACTIVE"));
    }
}
