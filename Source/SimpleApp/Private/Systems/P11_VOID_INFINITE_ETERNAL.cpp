#include "P11_VOID_INFINITE_ETERNAL.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP11_VOID_INFINITE_ETERNAL::UP11_VOID_INFINITE_ETERNAL()
{
    PrimaryComponentTick.bCanEverTick = false;
    InfiniteEternalVoidLevel = 0;
    MaxInfiniteEternalVoidLevel = 100;
    bIsInfiniteEternalVoidActive = false;
    InfiniteEternalVoidPowerCost = 60.0f;
    InfiniteEternalVoidThreshold = 60.0f;
    
    // Initialize infinite eternal void properties
    InfiniteEternalVoidMastery = 0.0f;
    InfiniteEternalUltimateAnnihilation = 0.0f;
    InfiniteEternalPerfectVoidEmptiness = 0.0f;
    InfiniteEternalConceptualUltimateOblivion = 0.0f;
    InfiniteEternalExistenceUltimateNegation = 0.0f;
}

void UP11_VOID_INFINITE_ETERNAL::BeginPlay()
{
    Super::BeginPlay();
    UpdateInfiniteEternalVoidStats();
}

void UP11_VOID_INFINITE_ETERNAL::ActivateInfiniteEternalVoid()
{
    if (!bIsInfiniteEternalVoidActive && CanActivateInfiniteEternalVoid())
    {
        bIsInfiniteEternalVoidActive = true;
        OnInfiniteEternalVoidActivated.Broadcast(InfiniteEternalVoidLevel);
        OnInfiniteEternalVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Void System Activated at Level: %d"), InfiniteEternalVoidLevel);
    }
}

void UP11_VOID_INFINITE_ETERNAL::DeactivateInfiniteEternalVoid()
{
    if (bIsInfiniteEternalVoidActive)
    {
        bIsInfiniteEternalVoidActive = false;
        OnInfiniteEternalVoidDeactivated.Broadcast(InfiniteEternalVoidLevel);
        OnInfiniteEternalVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Void System Deactivated."));
    }
}

void UP11_VOID_INFINITE_ETERNAL::SetInfiniteEternalVoidLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxInfiniteEternalVoidLevel)
    {
        int32 OldLevel = InfiniteEternalVoidLevel;
        InfiniteEternalVoidLevel = NewLevel;
        UpdateInfiniteEternalVoidStats();
        OnInfiniteEternalVoidLevelChanged.Broadcast(OldLevel, InfiniteEternalVoidLevel);
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Void Level set to: %d"), InfiniteEternalVoidLevel);
        
        if (InfiniteEternalVoidLevel >= MaxInfiniteEternalVoidLevel)
        {
            OnInfiniteEternalVoidMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Void Max Level Reached!"));
        }
    }
}

void UP11_VOID_INFINITE_ETERNAL::UseInfiniteEternalVoidPower()
{
    if (bIsInfiniteEternalVoidActive && InfiniteEternalVoidLevel > 0)
    {
        OnInfiniteEternalVoidPowerUsed.Broadcast(InfiniteEternalVoidPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Void Power Used: %.2f"), InfiniteEternalVoidPowerCost);
    }
    else
    {
        OnInfiniteEternalVoidPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Void Power Use Failed: System not active or insufficient level."));
    }
}

void UP11_VOID_INFINITE_ETERNAL::PerformInfiniteEternalVoidAbility()
{
    if (bIsInfiniteEternalVoidActive && InfiniteEternalVoidLevel >= InfiniteEternalVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Infinite Eternal Void Ability at Level %d!"), InfiniteEternalVoidLevel);
        OnInfiniteEternalVoidAbilityPerformed.Broadcast(InfiniteEternalVoidLevel);
        UseInfiniteEternalVoidPower();
        
        // Perform infinite eternal void ability based on level
        switch (InfiniteEternalVoidLevel / 20)
        {
            case 0:
                MasterInfiniteEternalVoid();
                break;
            case 1:
                AnnihilateInfiniteEternally();
                break;
            case 2:
                AchieveInfiniteEternalPerfectVoidEmptiness();
                break;
            case 3:
                InduceInfiniteEternalConceptualUltimateOblivion();
                break;
            case 4:
            case 5:
                NegateInfiniteEternalUltimateExistence();
                break;
            default:
                NegateInfiniteEternalUltimateExistence();
                break;
        }
    }
    }
    else if (InfiniteEternalVoidLevel < InfiniteEternalVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Void Level too low to perform ability. Required: %.0f, Current: %d"), InfiniteEternalVoidThreshold, InfiniteEternalVoidLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Void is not active, cannot perform ability."));
    }
}

bool UP11_VOID_INFINITE_ETERNAL::IsInfiniteEternalVoidActive() const
{
    return bIsInfiniteEternalVoidActive;
}

int32 UP11_VOID_INFINITE_ETERNAL::GetInfiniteEternalVoidLevel() const
{
    return InfiniteEternalVoidLevel;
}

float UP11_VOID_INFINITE_ETERNAL::GetInfiniteEternalVoidPowerCost() const
{
    return InfiniteEternalVoidPowerCost;
}

void UP11_VOID_INFINITE_ETERNAL::MasterInfiniteEternalVoid()
{
    if (bIsInfiniteEternalVoidActive)
    {
        float MasteryPower = InfiniteEternalVoidMastery * (InfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Infinite Eternal Void with power: %.2f"), MasteryPower);
        // Apply infinite eternal void mastery effects
    }
}

void UP11_VOID_INFINITE_ETERNAL::AnnihilateInfiniteEternally()
{
    if (bIsInfiniteEternalVoidActive)
    {
        float AnnihilationPower = InfiniteEternalUltimateAnnihilation * (InfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Infinite Eternally with power: %.2f"), AnnihilationPower);
        // Apply infinite eternal annihilation effects
    }
}

void UP11_VOID_INFINITE_ETERNAL::AchieveInfiniteEternalPerfectVoidEmptiness()
{
    if (bIsInfiniteEternalVoidActive)
    {
        float EmptinessPower = InfiniteEternalPerfectVoidEmptiness * (InfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Infinite Eternal Perfect Void Emptiness with power: %.2f"), EmptinessPower);
        // Apply infinite eternal perfect void emptiness effects
    }
}

void UP11_VOID_INFINITE_ETERNAL::InduceInfiniteEternalConceptualUltimateOblivion()
{
    if (bIsInfiniteEternalVoidActive)
    {
        float OblivionPower = InfiniteEternalConceptualUltimateOblivion * (InfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Infinite Eternal Conceptual Ultimate Oblivion with power: %.2f"), OblivionPower);
        // Apply infinite eternal conceptual ultimate oblivion effects
    }
}

void UP11_VOID_INFINITE_ETERNAL::NegateInfiniteEternalUltimateExistence()
{
    if (bIsInfiniteEternalVoidActive)
    {
        float NegationPower = InfiniteEternalExistenceUltimateNegation * (InfiniteEternalVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Infinite Eternal Ultimate Existence with power: %.2f"), NegationPower);
        // Apply infinite eternal ultimate existence negation effects
    }
}

bool UP11_VOID_INFINITE_ETERNAL::CanActivateInfiniteEternalVoid() const
{
    return InfiniteEternalVoidLevel > 0;
}

void UP11_VOID_INFINITE_ETERNAL::UpdateInfiniteEternalVoidStats()
{
    // Update infinite eternal void properties based on level
    InfiniteEternalVoidMastery = InfiniteEternalVoidLevel * 6.0f;
    InfiniteEternalUltimateAnnihilation = InfiniteEternalVoidLevel * 6.2f;
    InfiniteEternalPerfectVoidEmptiness = InfiniteEternalVoidLevel * 6.1f;
    InfiniteEternalConceptualUltimateOblivion = InfiniteEternalVoidLevel * 5.9f;
    InfiniteEternalExistenceUltimateNegation = InfiniteEternalVoidLevel * 6.3f;
}

void UP11_VOID_INFINITE_ETERNAL::OnInfiniteEternalVoidStateChanged()
{
    // Handle state change effects
    if (bIsInfiniteEternalVoidActive)
    {
        // Apply infinite eternal void activation effects
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Void state changed to ACTIVE"));
    }
    else
    {
        // Remove infinite eternal void effects
        UE_LOG(LogTemp, Warning, TEXT("Infinite Eternal Void state changed to INACTIVE"));
    }
}
