#include "SoloLevelingInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Widget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"

USoloLevelingInterface::USoloLevelingInterface()
{
    CurrentUIState = EUIState::UI_Hidden;
    bShowSystemInterface = true;
    bShowMinimalHUD = false;
    InterfaceFadeSpeed = 0.3f;
    
    bIsTransitioning = false;
    TransitionTimer = 0.0f;
    PreviousUIState = EUIState::UI_Hidden;
    
    LastNotificationTime = 0.0f;
    CurrentNotificationIndex = 0;
}

void USoloLevelingInterface::BeginPlay()
{
    Super::BeginPlay();
    Initialize();
}

void USoloLevelingInterface::Initialize()
{
    InitializeHUD();
    InitializeSystemInterface();
    InitializeDialogueSystem();
    InitializeVisualEffects();
    
    UE_LOG(LogTemp, Warning, TEXT("Solo Leveling Interface initialized"));
}

void USoloLevelingInterface::InitializeHUD()
{
    // Create main HUD widget
    MainHUD = CreateWidgetComponent<UWidgetComponent>(this);
    MainHUD->SetWidgetSpace(EWidgetSpace::Screen);
    MainHUD->SetDrawSize(FVector2D(1920, 1080));
    MainHUD->RegisterComponent();
    
    UE_LOG(LogTemp, Warning, TEXT("HUD initialized"));
}

void USoloLevelingInterface::InitializeSystemInterface()
{
    // Create system interface widget (Jin-Woo style blue screens)
    SystemInterface = CreateWidgetComponent<UWidgetComponent>(this);
    SystemInterface->SetWidgetSpace(EWidgetSpace::Screen);
    SystemInterface->SetDrawSize(FVector2D(1920, 1080));
    SystemInterface->RegisterComponent();
    
    UE_LOG(LogTemp, Warning, TEXT("System interface initialized"));
}

void USoloLevelingInterface::ShowInterface(EUIState UIState)
{
    if (CurrentUIState != UIState && !bIsTransitioning)
    {
        PreviousUIState = CurrentUIState;
        CurrentUIState = UIState;
        bIsTransitioning = true;
        TransitionTimer = 0.0f;
        
        OnInterfaceStateChanged.Broadcast(PreviousUIState, UIState);
        
        UE_LOG(LogTemp, Warning, TEXT("Showing interface state: %d"), (int32)UIState);
    }
}

void USoloLevelingInterface::ToggleSystemInterface()
{
    if (CurrentUIState == EUIState::UI_SystemInterface)
    {
        ShowInterface(EUIState::UI_MainHUD);
    }
    else
    {
        ShowInterface(EUIState::UI_SystemInterface);
    }
}

void USoloLevelingInterface::UpdatePowerSystemDisplay(TArray<FPowerSystemDisplayData> Systems)
{
    ActivePowerSystems = Systems;
    UpdateSystemInterface();
    
    UE_LOG(LogTemp, Warning, TEXT("Updated power system display with %d systems"), Systems.Num());
}

void USoloLevelingInterface::ShowPowerSystemNotification(FString Message, FLinearColor Color)
{
    ShowNotification(Message, 3.0f);
    
    UE_LOG(LogTemp, Warning, TEXT("Power system notification: %s"), *Message);
}

void USoloLevelingInterface::UpdateHealthBar(float Health, float MaxHealth)
{
    // Update health bar display
    float HealthPercentage = Health / MaxHealth;
    
    UE_LOG(LogTemp, Warning, TEXT("Health bar updated: %.1f/%.1f (%.1f%%)"), Health, MaxHealth, HealthPercentage * 100.0f);
}

void USoloLevelingInterface::UpdatePowerBar(float Power, float MaxPower)
{
    // Update power bar display
    float PowerPercentage = Power / MaxPower;
    
    UE_LOG(LogTemp, Warning, TEXT("Power bar updated: %.1f/%.1f (%.1f%%)"), Power, MaxPower, PowerPercentage * 100.0f);
}

void USoloLevelingInterface::ShowDamageNumber(FVector Location, float Damage, bool bIsCritical)
{
    // Create damage number widget at location
    FString DamageText = FString::Printf(TEXT("%.1f"), Damage);
    
    if (bIsCritical)
    {
        DamageText = TEXT("CRITICAL! ") + DamageText;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Damage number: %s at location: %s"), *DamageText, *Location.ToString());
}

void USoloLevelingInterface::ShowDialogue(FString SpeakerName, FString DialogueText, TArray<FString> Choices)
{
    ShowInterface(EUIState::UI_Dialogue);
    
    UE_LOG(LogTemp, Warning, TEXT("Dialogue: %s - %s"), *SpeakerName, *DialogueText);
}

void USoloLevelingInterface::ShowNotification(FString Message, float Duration)
{
    NotificationQueue.Add(Message);
    
    UE_LOG(LogTemp, Warning, TEXT("Notification: %s"), *Message);
}

void USoloLevelingInterface::PlayScreenShake(float Intensity, float Duration)
{
    // Apply screen shake effect
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        PC->ClientPlayCameraShake();
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Screen shake: Intensity=%.2f, Duration=%.2f"), Intensity, Duration);
}

void USoloLevelingInterface::ShowTimingWindow(FName ActionName, float Duration)
{
    // Show perfect timing window visual
    UE_LOG(LogTemp, Warning, TEXT("Timing window for %s: %.2f seconds"), *ActionName.ToString(), Duration);
}

void USoloLevelingInterface::InitializeDialogueSystem()
{
    // Initialize dialogue UI components
    DialogueUI = CreateWidgetComponent<UWidgetComponent>(this);
    DialogueUI->SetWidgetSpace(EWidgetSpace::Screen);
    DialogueUI->SetDrawSize(FVector2D(1920, 1080));
    DialogueUI->RegisterComponent();
    
    UE_LOG(LogTemp, Warning, TEXT("Dialogue system initialized"));
}

void USoloLevelingInterface::InitializeVisualEffects()
{
    // Initialize visual effect systems
    UE_LOG(LogTemp, Warning, TEXT("Visual effects initialized"));
}
