#include "P08_VOID_SUPREME.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP08_VOID_SUPREME::UP08_VOID_SUPREME()
{
    PrimaryComponentTick.bCanEverTick = false;
    SupremeVoidLevel = 0;
    MaxSupremeVoidLevel = 100;
    bIsSupremeVoidActive = false;
    SupremeVoidPowerCost = 45.0f;
    SupremeVoidThreshold = 45.0f;
    
    // Initialize supreme void properties
    SupremeVoidMastery = 0.0f;
    SupremeUltimateAnnihilation = 0.0f;
    SupremePerfectVoidEmptiness = 0.0f;
    SupremeConceptualUltimateOblivion = 0.0f;
    SupremeExistenceUltimateNegation = 0.0f;
}

void UP08_VOID_SUPREME::BeginPlay()
{
    Super::BeginPlay();
    UpdateSupremeVoidStats();
}

void UP08_VOID_SUPREME::ActivateSupremeVoid()
{
    if (!bIsSupremeVoidActive && CanActivateSupremeVoid())
    {
        bIsSupremeVoidActive = true;
        OnSupremeVoidActivated.Broadcast(SupremeVoidLevel);
        OnSupremeVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Supreme Void System Activated at Level: %d"), SupremeVoidLevel);
    }
}

void UP08_VOID_SUPREME::DeactivateSupremeVoid()
{
    if (bIsSupremeVoidActive)
    {
        bIsSupremeVoidActive = false;
        OnSupremeVoidDeactivated.Broadcast(SupremeVoidLevel);
        OnSupremeVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Supreme Void System Deactivated."));
    }
}

void UP08_VOID_SUPREME::SetSupremeVoidLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxSupremeVoidLevel)
    {
        int32 OldLevel = SupremeVoidLevel;
        SupremeVoidLevel = NewLevel;
        UpdateSupremeVoidStats();
        OnSupremeVoidLevelChanged.Broadcast(OldLevel, SupremeVoidLevel);
        UE_LOG(LogTemp, Warning, TEXT("Supreme Void Level set to: %d"), SupremeVoidLevel);
        
        if (SupremeVoidLevel >= MaxSupremeVoidLevel)
        {
            OnSupremeVoidMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Supreme Void Max Level Reached!"));
        }
    }
}

void UP08_VOID_SUPREME::UseSupremeVoidPower()
{
    if (bIsSupremeVoidActive && SupremeVoidLevel > 0)
    {
        OnSupremeVoidPowerUsed.Broadcast(SupremeVoidPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Supreme Void Power Used: %.2f"), SupremeVoidPowerCost);
    }
    else
    {
        OnSupremeVoidPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Supreme Void Power Use Failed: System not active or insufficient level."));
    }
}

void UP08_VOID_SUPREME::PerformSupremeVoidAbility()
{
    if (bIsSupremeVoidActive && SupremeVoidLevel >= SupremeVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Supreme Void Ability at Level %d!"), SupremeVoidLevel);
        OnSupremeVoidAbilityPerformed.Broadcast(SupremeVoidLevel);
        UseSupremeVoidPower();
        
        // Perform supreme void ability based on level
        switch (SupremeVoidLevel / 20)
        {
            case 0:
                MasterSupremeVoid();
                break;
            case 1:
                AnnihilateSupremely();
                break;
            case 2:
                AchieveSupremePerfectVoidEmptiness();
                break;
            case 3:
                InduceSupremeConceptualUltimateOblivion();
                break;
            case 4:
            case 5:
                NegateSupremeUltimateExistence();
                break;
            default:
                NegateSupremeUltimateExistence();
                break;
        }
    }
    }
    else if (SupremeVoidLevel < SupremeVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Supreme Void Level too low to perform ability. Required: %.0f, Current: %d"), SupremeVoidThreshold, SupremeVoidLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Supreme Void is not active, cannot perform ability."));
    }
}

bool UP08_VOID_SUPREME::IsSupremeVoidActive() const
{
    return bIsSupremeVoidActive;
}

int32 UP08_VOID_SUPREME::GetSupremeVoidLevel() const
{
    return SupremeVoidLevel;
}

float UP08_VOID_SUPREME::GetSupremeVoidPowerCost() const
{
    return SupremeVoidPowerCost;
}

void UP08_VOID_SUPREME::MasterSupremeVoid()
{
    if (bIsSupremeVoidActive)
    {
        float MasteryPower = SupremeVoidMastery * (SupremeVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Supreme Void with power: %.2f"), MasteryPower);
        // Apply supreme void mastery effects
    }
}

void UP08_VOID_SUPREME::AnnihilateSupremely()
{
    if (bIsSupremeVoidActive)
    {
        float AnnihilationPower = SupremeUltimateAnnihilation * (SupremeVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Supremely with power: %.2f"), AnnihilationPower);
        // Apply supreme annihilation effects
    }
}

void UP08_VOID_SUPREME::AchieveSupremePerfectVoidEmptiness()
{
    if (bIsSupremeVoidActive)
    {
        float EmptinessPower = SupremePerfectVoidEmptiness * (SupremeVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Supreme Perfect Void Emptiness with power: %.2f"), EmptinessPower);
        // Apply supreme perfect void emptiness effects
    }
}

void UP08_VOID_SUPREME::InduceSupremeConceptualUltimateOblivion()
{
    if (bIsSupremeVoidActive)
    {
        float OblivionPower = SupremeConceptualUltimateOblivion * (SupremeVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Supreme Conceptual Ultimate Oblivion with power: %.2f"), OblivionPower);
        // Apply supreme conceptual ultimate oblivion effects
    }
}

void UP08_VOID_SUPREME::NegateSupremeUltimateExistence()
{
    if (bIsSupremeVoidActive)
    {
        float NegationPower = SupremeExistenceUltimateNegation * (SupremeVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Supreme Ultimate Existence with power: %.2f"), NegationPower);
        // Apply supreme ultimate existence negation effects
    }
}

bool UP08_VOID_SUPREME::CanActivateSupremeVoid() const
{
    return SupremeVoidLevel > 0;
}

void UP08_VOID_SUPREME::UpdateSupremeVoidStats()
{
    // Update supreme void properties based on level
    SupremeVoidMastery = SupremeVoidLevel * 4.5f;
    SupremeUltimateAnnihilation = SupremeVoidLevel * 4.7f;
    SupremePerfectVoidEmptiness = SupremeVoidLevel * 4.6f;
    SupremeConceptualUltimateOblivion = SupremeVoidLevel * 4.4f;
    SupremeExistenceUltimateNegation = SupremeVoidLevel * 4.8f;
}

void UP08_VOID_SUPREME::OnSupremeVoidStateChanged()
{
    // Handle state change effects
    if (bIsSupremeVoidActive)
    {
        // Apply supreme void activation effects
        UE_LOG(LogTemp, Warning, TEXT("Supreme Void state changed to ACTIVE"));
    }
    else
    {
        // Remove supreme void effects
        UE_LOG(LogTemp, Warning, TEXT("Supreme Void state changed to INACTIVE"));
    }
}
