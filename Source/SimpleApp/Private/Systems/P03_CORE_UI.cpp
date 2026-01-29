#include "P03_CORE_UI.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP03_CORE_UI::UP03_CORE_UI()
{
    PrimaryComponentTick.bCanEverTick = false;
    UILevel = 0;
    MaxUILevel = 100;
    bIsUIActive = false;
    UIPowerCost = 10.0f;
    UIThreshold = 10.0f;
    
    // Initialize UI properties
    InterfaceCreation = 0.0f;
    HUDSystem = 0.0f;
    MenuSystem = 0.0f;
    VisualFeedback = 0.0f;
}

void UP03_CORE_UI::BeginPlay()
{
    Super::BeginPlay();
    UpdateUIStats();
}

void UP03_CORE_UI::ActivateUI()
{
    if (!bIsUIActive && CanActivateUI())
    {
        bIsUIActive = true;
        OnUIActivated.Broadcast(UILevel);
        OnUIStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("UI System Activated at Level: %d"), UILevel);
    }
}

void UP03_CORE_UI::DeactivateUI()
{
    if (bIsUIActive)
    {
        bIsUIActive = false;
        OnUIDeactivated.Broadcast(UILevel);
        OnUIStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("UI System Deactivated."));
    }
}

void UP03_CORE_UI::SetUILevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxUILevel)
    {
        int32 OldLevel = UILevel;
        UILevel = NewLevel;
        UpdateUIStats();
        OnUILevelChanged.Broadcast(OldLevel, UILevel);
        UE_LOG(LogTemp, Warning, TEXT("UI Level set to: %d"), UILevel);
        
        if (UILevel >= MaxUILevel)
        {
            OnUIMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("UI Max Level Reached!"));
        }
    }
}

void UP03_CORE_UI::UseUIPower()
{
    if (bIsUIActive && UILevel > 0)
    {
        OnUIPowerUsed.Broadcast(UIPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("UI Power Used: %.2f"), UIPowerCost);
    }
    else
    {
        OnUIPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("UI Power Use Failed: System not active or insufficient level."));
    }
}

void UP03_CORE_UI::PerformUIAbility()
{
    if (bIsUIActive && UILevel >= UIThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing UI Ability at Level %d!"), UILevel);
        OnUIAbilityPerformed.Broadcast(UILevel);
        UseUIPower();
        
        // Perform UI ability based on level
        switch (UILevel / 20)
        {
            case 0:
                CreateInterfaces();
                break;
            case 1:
                AccessHUDSystem();
                break;
            case 2:
                ControlMenuSystem();
                break;
            case 3:
                ApplyVisualFeedback();
                break;
            default:
                ApplyVisualFeedback();
                break;
        }
    }
    }
    else if (UILevel < UIThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("UI Level too low to perform ability. Required: %.0f, Current: %d"), UIThreshold, UILevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("UI is not active, cannot perform ability."));
    }
}

bool UP03_CORE_UI::IsUIActive() const
{
    return bIsUIActive;
}

int32 UP03_CORE_UI::GetUILevel() const
{
    return UILevel;
}

float UP03_CORE_UI::GetUIPowerCost() const
{
    return UIPowerCost;
}

void UP03_CORE_UI::CreateInterfaces()
{
    if (bIsUIActive)
    {
        float InterfacePower = InterfaceCreation * (UILevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Creating Interfaces with power: %.2f"), InterfacePower);
        // Apply interface creation effects
    }
}

void UP03_CORE_UI::AccessHUDSystem()
{
    if (bIsUIActive)
    {
        float HUDPower = HUDSystem * (UILevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing HUD System with power: %.2f"), HUDPower);
        // Apply HUD system effects
    }
}

void UP03_CORE_UI::ControlMenuSystem()
{
    if (bIsUIActive)
    {
        float MenuPower = MenuSystem * (UILevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Menu System with power: %.2f"), MenuPower);
        // Apply menu system effects
    }
}

void UP03_CORE_UI::ApplyVisualFeedback()
{
    if (bIsUIActive)
    {
        float FeedbackPower = VisualFeedback * (UILevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Applying Visual Feedback with power: %.2f"), FeedbackPower);
        // Apply visual feedback effects
    }
}

bool UP03_CORE_UI::CanActivateUI() const
{
    return UILevel > 0;
}

void UP03_CORE_UI::UpdateUIStats()
{
    // Update UI properties based on level
    InterfaceCreation = UILevel * 1.3f;
    HUDSystem = UILevel * 1.5f;
    MenuSystem = UILevel * 1.2f;
    VisualFeedback = UILevel * 1.4f;
}

void UP03_CORE_UI::OnUIStateChanged()
{
    // Handle state change effects
    if (bIsUIActive)
    {
        // Apply UI activation effects
        UE_LOG(LogTemp, Warning, TEXT("UI state changed to ACTIVE"));
    }
    else
    {
        // Remove UI effects
        UE_LOG(LogTemp, Warning, TEXT("UI state changed to INACTIVE"));
    }
}
