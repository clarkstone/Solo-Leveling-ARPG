#include "P07_VOID_ULTRA.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP07_VOID_ULTRA::UP07_VOID_ULTRA()
{
    PrimaryComponentTick.bCanEverTick = false;
    UltraVoidLevel = 0;
    MaxUltraVoidLevel = 100;
    bIsUltraVoidActive = false;
    UltraVoidPowerCost = 40.0f;
    UltraVoidThreshold = 40.0f;
    
    // Initialize ultra void properties
    VoidMastery = 0.0f;
    UltimateAnnihilation = 0.0f;
    PerfectVoidEmptiness = 0.0f;
    ConceptualUltimateOblivion = 0.0f;
    ExistenceUltimateNegation = 0.0f;
}

void UP07_VOID_ULTRA::BeginPlay()
{
    Super::BeginPlay();
    UpdateUltraVoidStats();
}

void UP07_VOID_ULTRA::ActivateUltraVoid()
{
    if (!bIsUltraVoidActive && CanActivateUltraVoid())
    {
        bIsUltraVoidActive = true;
        OnUltraVoidActivated.Broadcast(UltraVoidLevel);
        OnUltraVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Ultra Void System Activated at Level: %d"), UltraVoidLevel);
    }
}

void UP07_VOID_ULTRA::DeactivateUltraVoid()
{
    if (bIsUltraVoidActive)
    {
        bIsUltraVoidActive = false;
        OnUltraVoidDeactivated.Broadcast(UltraVoidLevel);
        OnUltraVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Ultra Void System Deactivated."));
    }
}

void UP07_VOID_ULTRA::SetUltraVoidLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxUltraVoidLevel)
    {
        int32 OldLevel = UltraVoidLevel;
        UltraVoidLevel = NewLevel;
        UpdateUltraVoidStats();
        OnUltraVoidLevelChanged.Broadcast(OldLevel, UltraVoidLevel);
        UE_LOG(LogTemp, Warning, TEXT("Ultra Void Level set to: %d"), UltraVoidLevel);
        
        if (UltraVoidLevel >= MaxUltraVoidLevel)
        {
            OnUltraVoidMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Ultra Void Max Level Reached!"));
        }
    }
}

void UP07_VOID_ULTRA::UseUltraVoidPower()
{
    if (bIsUltraVoidActive && UltraVoidLevel > 0)
    {
        OnUltraVoidPowerUsed.Broadcast(UltraVoidPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Ultra Void Power Used: %.2f"), UltraVoidPowerCost);
    }
    else
    {
        OnUltraVoidPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Ultra Void Power Use Failed: System not active or insufficient level."));
    }
}

void UP07_VOID_ULTRA::PerformUltraVoidAbility()
{
    if (bIsUltraVoidActive && UltraVoidLevel >= UltraVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Ultra Void Ability at Level %d!"), UltraVoidLevel);
        OnUltraVoidAbilityPerformed.Broadcast(UltraVoidLevel);
        UseUltraVoidPower();
        
        // Perform ultra void ability based on level
        switch (UltraVoidLevel / 20)
        {
            case 0:
                MasterUltraVoid();
                break;
            case 1:
                AnnihilateUltimately();
                break;
            case 2:
                AchievePerfectVoidEmptiness();
                break;
            case 3:
                InduceConceptualUltimateOblivion();
                break;
            case 4:
            case 5:
                NegateUltimateExistence();
                break;
            default:
                NegateUltimateExistence();
                break;
        }
    }
    }
    else if (UltraVoidLevel < UltraVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ultra Void Level too low to perform ability. Required: %.0f, Current: %d"), UltraVoidThreshold, UltraVoidLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Ultra Void is not active, cannot perform ability."));
    }
}

bool UP07_VOID_ULTRA::IsUltraVoidActive() const
{
    return bIsUltraVoidActive;
}

int32 UP07_VOID_ULTRA::GetUltraVoidLevel() const
{
    return UltraVoidLevel;
}

float UP07_VOID_ULTRA::GetUltraVoidPowerCost() const
{
    return UltraVoidPowerCost;
}

void UP07_VOID_ULTRA::MasterUltraVoid()
{
    if (bIsUltraVoidActive)
    {
        float MasteryPower = VoidMastery * (UltraVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Ultra Void with power: %.2f"), MasteryPower);
        // Apply ultra void mastery effects
    }
}

void UP07_VOID_ULTRA::AnnihilateUltimately()
{
    if (bIsUltraVoidActive)
    {
        float AnnihilationPower = UltimateAnnihilation * (UltraVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Ultimately with power: %.2f"), AnnihilationPower);
        // Apply ultimate annihilation effects
    }
}

void UP07_VOID_ULTRA::AchievePerfectVoidEmptiness()
{
    if (bIsUltraVoidActive)
    {
        float EmptinessPower = PerfectVoidEmptiness * (UltraVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Perfect Void Emptiness with power: %.2f"), EmptinessPower);
        // Apply perfect void emptiness effects
    }
}

void UP07_VOID_ULTRA::InduceConceptualUltimateOblivion()
{
    if (bIsUltraVoidActive)
    {
        float OblivionPower = ConceptualUltimateOblivion * (UltraVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Conceptual Ultimate Oblivion with power: %.2f"), OblivionPower);
        // Apply conceptual ultimate oblivion effects
    }
}

void UP07_VOID_ULTRA::NegateUltimateExistence()
{
    if (bIsUltraVoidActive)
    {
        float NegationPower = ExistenceUltimateNegation * (UltraVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Ultimate Existence with power: %.2f"), NegationPower);
        // Apply ultimate existence negation effects
    }
}

bool UP07_VOID_ULTRA::CanActivateUltraVoid() const
{
    return UltraVoidLevel > 0;
}

void UP07_VOID_ULTRA::UpdateUltraVoidStats()
{
    // Update ultra void properties based on level
    VoidMastery = UltraVoidLevel * 4.0f;
    UltimateAnnihilation = UltraVoidLevel * 4.2f;
    PerfectVoidEmptiness = UltraVoidLevel * 4.1f;
    ConceptualUltimateOblivion = UltraVoidLevel * 3.9f;
    ExistenceUltimateNegation = UltraVoidLevel * 4.3f;
}

void UP07_VOID_ULTRA::OnUltraVoidStateChanged()
{
    // Handle state change effects
    if (bIsUltraVoidActive)
    {
        // Apply ultra void activation effects
        UE_LOG(LogTemp, Warning, TEXT("Ultra Void state changed to ACTIVE"));
    }
    else
    {
        // Remove ultra void effects
        UE_LOG(LogTemp, Warning, TEXT("Ultra Void state changed to INACTIVE"));
    }
}
