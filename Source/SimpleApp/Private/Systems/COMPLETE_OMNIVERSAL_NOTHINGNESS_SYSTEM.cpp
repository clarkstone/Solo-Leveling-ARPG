#include "COMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    OmniversalNothingnessLevel = 0;
    MaxOmniversalNothingnessLevel = 100;
    bIsOmniversalNothingnessActive = false;
    OmniversalNothingnessPowerCost = 15.0f;
    OmniversalNothingnessThreshold = 60.0f;
    
    // Initialize omniversal-nothingness properties
    OmniversalVoidControl = 0.0f;
    AbsoluteAnnihilation = 0.0f;
    InfiniteEmptiness = 0.0f;
    ConceptualNullification = 0.0f;
    ExistenceErasion = 0.0f;
}

void UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateOmniversalNothingnessStats();
}

void UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::ActivateOmniversalNothingness()
{
    if (!bIsOmniversalNothingnessActive && CanActivateOmniversalNothingness())
    {
        bIsOmniversalNothingnessActive = true;
        OnOmniversalNothingnessActivated.Broadcast(OmniversalNothingnessLevel);
        OnOmniversalNothingnessStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omniversal-Nothingness System Activated at Level: %d"), OmniversalNothingnessLevel);
    }
}

void UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::DeactivateOmniversalNothingness()
{
    if (bIsOmniversalNothingnessActive)
    {
        bIsOmniversalNothingnessActive = false;
        OnOmniversalNothingnessDeactivated.Broadcast(OmniversalNothingnessLevel);
        OnOmniversalNothingnessStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omniversal-Nothingness System Deactivated."));
    }
}

void UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::SetOmniversalNothingnessLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxOmniversalNothingnessLevel)
    {
        int32 OldLevel = OmniversalNothingnessLevel;
        OmniversalNothingnessLevel = NewLevel;
        UpdateOmniversalNothingnessStats();
        OnOmniversalNothingnessLevelChanged.Broadcast(OldLevel, OmniversalNothingnessLevel);
        UE_LOG(LogTemp, Warning, TEXT("Omniversal-Nothingness Level set to: %d"), OmniversalNothingnessLevel);
        
        if (OmniversalNothingnessLevel >= MaxOmniversalNothingnessLevel)
        {
            OnOmniversalNothingnessMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Omniversal-Nothingness Max Level Reached!"));
        }
    }
}

void UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::UseOmniversalNothingnessPower()
{
    if (bIsOmniversalNothingnessActive && OmniversalNothingnessLevel > 0)
    {
        OnOmniversalNothingnessPowerUsed.Broadcast(OmniversalNothingnessPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Omniversal-Nothingness Power Used: %.2f"), OmniversalNothingnessPowerCost);
    }
    else
    {
        OnOmniversalNothingnessPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Omniversal-Nothingness Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::PerformOmniversalNothingnessAbility()
{
    if (bIsOmniversalNothingnessActive && OmniversalNothingnessLevel >= OmniversalNothingnessThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Omniversal-Nothingness Ability at Level %d!"), OmniversalNothingnessLevel);
        OnOmniversalNothingnessAbilityPerformed.Broadcast(OmniversalNothingnessLevel);
        UseOmniversalNothingnessPower();
        
        // Perform omniversal-nothingness ability based on level
        switch (OmniversalNothingnessLevel / 20)
        {
            case 0:
                ControlOmniversalVoid();
                break;
            case 1:
                AnnihilateAbsolutely();
                break;
            case 2:
                EmptifyInfinitely();
                break;
            case 3:
                NullifyConceptually();
                break;
            case 4:
            case 5:
                EraseExistence();
                break;
            default:
                EraseExistence();
                break;
        }
    }
    else if (OmniversalNothingnessLevel < OmniversalNothingnessThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Omniversal-Nothingness Level too low to perform ability. Required: %.0f, Current: %d"), OmniversalNothingnessThreshold, OmniversalNothingnessLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Omniversal-Nothingness is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::IsOmniversalNothingnessActive() const
{
    return bIsOmniversalNothingnessActive;
}

int32 UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::GetOmniversalNothingnessLevel() const
{
    return OmniversalNothingnessLevel;
}

float UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::GetOmniversalNothingnessPowerCost() const
{
    return OmniversalNothingnessPowerCost;
}

void UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::ControlOmniversalVoid()
{
    if (bIsOmniversalNothingnessActive)
    {
        float VoidControl = OmniversalVoidControl * (OmniversalNothingnessLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Omniversal Void with power: %.2f"), VoidControl);
        // Apply omniversal void control effects
    }
}

void UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::AnnihilateAbsolutely()
{
    if (bIsOmniversalNothingnessActive)
    {
        float AnnihilationPower = AbsoluteAnnihilation * (OmniversalNothingnessLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Absolutely with power: %.2f"), AnnihilationPower);
        // Apply absolute annihilation effects
    }
}

void UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::EmptifyInfinitely()
{
    if (bIsOmniversalNothingnessActive)
    {
        float EmptificationPower = InfiniteEmptiness * (OmniversalNothingnessLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Emptifying Infinitely with power: %.2f"), EmptificationPower);
        // Apply infinite emptiness effects
    }
}

void UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::NullifyConceptually()
{
    if (bIsOmniversalNothingnessActive)
    {
        float NullificationPower = ConceptualNullification * (OmniversalNothingnessLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Nullifying Conceptually with power: %.2f"), NullificationPower);
        // Apply conceptual nullification effects
    }
}

void UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::EraseExistence()
{
    if (bIsOmniversalNothingnessActive)
    {
        float ErasurePower = ExistenceErasion * (OmniversalNothingnessLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Erasing Existence with power: %.2f"), ErasurePower);
        // Apply existence erasure effects
    }
}

bool UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::CanActivateOmniversalNothingness() const
{
    return OmniversalNothingnessLevel > 0;
}

void UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::UpdateOmniversalNothingnessStats()
{
    // Update omniversal-nothingness properties based on level
    OmniversalVoidControl = OmniversalNothingnessLevel * 3.3f;
    AbsoluteAnnihilation = OmniversalNothingnessLevel * 3.1f;
    InfiniteEmptiness = OmniversalNothingnessLevel * 3.0f;
    ConceptualNullification = OmniversalNothingnessLevel * 2.9f;
    ExistenceErasion = OmniversalNothingnessLevel * 3.2f;
}

void UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM::OnOmniversalNothingnessStateChanged()
{
    // Handle state change effects
    if (bIsOmniversalNothingnessActive)
    {
        // Apply omniversal-nothingness activation effects
        UE_LOG(LogTemp, Warning, TEXT("Omniversal-Nothingness state changed to ACTIVE"));
    }
    else
    {
        // Remove omniversal-nothingness effects
        UE_LOG(LogTemp, Warning, TEXT("Omniversal-Nothingness state changed to INACTIVE"));
    }
}
