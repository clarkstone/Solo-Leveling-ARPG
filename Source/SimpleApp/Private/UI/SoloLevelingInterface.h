#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "PowerSystemCore.h"
#include "SoloLevelingInterface.generated.h"

UENUM(BlueprintType)
enum class EUIState : uint8
{
    UI_Hidden,
    UI_MainHUD,
    UI_ClassSelection,
    UI_PowerPathInterface,
    UI_AbilityBar,
    UI_CharacterStats,
    UI_Inventory,
    UI_QuestLog,
    UI_Dialogue,
    UI_Cutscene
};

USTRUCT(BlueprintType)
struct FPowerPathDisplayData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString PathName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECoreClass CoreClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPowerRank CurrentRank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentExperience;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsUnlocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor PathColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString RankTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FAbilityData> CurrentAbilities;
};

USTRUCT(BlueprintType)
struct FAbilityDisplayData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString AbilityName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ManaCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Cooldown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentCooldown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsAvailable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SlotIndex;
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

    // Class System Manager Reference
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
    class UClassSystemManager* ClassSystemManager;

    // UI Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
    class UWidgetComponent* MainHUD;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
    class UWidgetComponent* ClassSelectionWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
    class UWidgetComponent* PowerPathWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
    class UWidgetComponent* AbilityBarWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
    class UWidgetComponent* CharacterStatsWidget;

    // UI State Management
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
    EUIState CurrentUIState;

    // UI Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")
    class UWidgetComponent* MainHUD;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface")

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    class UWidget* PowerPathWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    class UWidget* AbilityBarWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    class UWidget* CharacterStatsWidget;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // UI Management
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowInterface();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void HideInterface();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void ToggleInterface();

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsInterfaceVisible() const;

    // Class Selection UI
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowClassSelection();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void HideClassSelection();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void OnClassSelected(ECoreClass SelectedClass);

    // Power Path UI
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowPowerPathInterface();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void HidePowerPathInterface();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void UpdatePowerPathDisplay();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void OnPathUnlocked(const FString& PathName, ECoreClass CoreClass);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void OnPathActivated(const FString& PathName, bool bActivated);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void OnRankUp(EPowerRank OldRank, EPowerRank NewRank);

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
