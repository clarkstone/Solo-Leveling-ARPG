#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "SoloLevelingInterface.generated.h"

UENUM(BlueprintType)
enum class EUIState : uint8
{
    UI_Hidden,
    UI_MainHUD,
    UI_SystemInterface,
    UI_Inventory,
    UI_QuestLog,
    UI_CharacterStats,
    UI_Dialogue,
    UI_Cutscene
};

USTRUCT(BlueprintType)
struct FPowerSystemDisplayData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SystemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PowerLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor SystemColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString StatusText;
};

UCLASS()
class SIMPLEAPP_API USoloLevelingInterface : public UActorComponent
{
    GENERATED_BODY()

public:
    USoloLevelingInterface();

    // UI State Management
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
    EUIState CurrentUIState;

    // UI Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
    class UWidgetComponent* MainHUD;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
    class UWidgetComponent* SystemInterface;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
    class UWidgetComponent* DialogueUI;

    // Interface Configuration
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interface")
    bool bShowSystemInterface;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interface")
    bool bShowMinimalHUD;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interface")
    float InterfaceFadeSpeed;

    // Power System Display
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
    TArray<FPowerSystemDisplayData> ActivePowerSystems;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Initialization
    UFUNCTION(BlueprintCallable, Category = "Interface")
    void Initialize();

    // UI State Management
    UFUNCTION(BlueprintCallable, Category = "Interface")
    void ShowInterface(EUIState UIState);

    UFUNCTION(BlueprintCallable, Category = "Interface")
    void HideInterface();

    UFUNCTION(BlueprintCallable, Category = "Interface")
    void ToggleSystemInterface();

    // Power System Interface
    UFUNCTION(BlueprintCallable, Category = "Interface")
    void UpdatePowerSystemDisplay(TArray<FPowerSystemDisplayData> Systems);

    UFUNCTION(BlueprintCallable, Category = "Interface")
    void ShowPowerSystemNotification(FString Message, FLinearColor Color);

    UFUNCTION(BlueprintCallable, Category = "Interface")
    void DisplaySystemStats();

    // HUD Functions
    UFUNCTION(BlueprintCallable, Category = "Interface")
    void UpdateHealthBar(float Health, float MaxHealth);

    UFUNCTION(BlueprintCallable, Category = "Interface")
    void UpdatePowerBar(float Power, float MaxPower);

    UFUNCTION(BlueprintCallable, Category = "Interface")
    void ShowDamageNumber(FVector Location, float Damage, bool bIsCritical);

    UFUNCTION(BlueprintCallable, Category = "Interface")
    void ShowComboDisplay(TArray<FName> Combo);

    // Dialogue System
    UFUNCTION(BlueprintCallable, Category = "Interface")
    void ShowDialogue(FString SpeakerName, FString DialogueText, TArray<FString> Choices);

    UFUNCTION(BlueprintCallable, Category = "Interface")
    void HideDialogue();

    UFUNCTION(BlueprintCallable, Category = "Interface")
    void ProcessDialogueChoice(int32 ChoiceIndex);

    // System Notifications
    UFUNCTION(BlueprintCallable, Category = "Interface")
    void ShowNotification(FString Message, float Duration);

    UFUNCTION(BlueprintCallable, Category = "Interface")
    void ShowQuestNotification(FString QuestName, FString Objective);

    UFUNCTION(BlueprintCallable, Category = "Interface")
    void ShowAchievementNotification(FString AchievementName);

    // Visual Effects
    UFUNCTION(BlueprintCallable, Category = "Interface")
    void PlayScreenShake(float Intensity, float Duration);

    UFUNCTION(BlueprintCallable, Category = "Interface")
    void ShowTimingWindow(FName ActionName, float Duration);

    UFUNCTION(BlueprintCallable, Category = "Interface")
    void FlashScreen(FLinearColor Color, float Duration);

    // Events
    UPROPERTY(BlueprintAssignable, Category = "Interface Events")
    FOnInterfaceStateChanged OnInterfaceStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Interface Events")
    FOnPowerSystemActivated OnPowerSystemActivated;

    UPROPERTY(BlueprintAssignable, Category = "Interface Events")
    FOnDialogueChoiceSelected OnDialogueChoiceSelected;

protected:
    // Internal UI Systems
    void InitializeHUD();
    void InitializeSystemInterface();
    void InitializeDialogueSystem();
    void InitializeVisualEffects();

    // UI Updates
    void UpdateHUD();
    void UpdateSystemInterface();
    void UpdateVisualEffects();

private:
    // Internal State
    bool bIsTransitioning;
    float TransitionTimer;
    EUIState PreviousUIState;

    // UI Data
    TArray<FString> NotificationQueue;
    float LastNotificationTime;
    int32 CurrentNotificationIndex;

    // Helper Functions
    void CreateHUDElements();
    void CreateSystemInterfaceElements();
    void CreateDialogueElements();
    void ProcessNotificationQueue();
};
