#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P03_CORE_UI.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnUILevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUIMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUIPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP03_CORE_UI : public UActorComponent
{
    GENERATED_BODY()

public:
    UP03_CORE_UI();

    // UI Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    int32 UILevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    int32 MaxUILevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    bool bIsUIActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    float UIPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    float UIThreshold;

    // UI Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    float InterfaceCreation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    float HUDSystem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    float MenuSystem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    float VisualFeedback;

    // UI Events
    UPROPERTY(BlueprintAssignable, Category = "UI")
    FOnUIActivated OnUIActivated;

    UPROPERTY(BlueprintAssignable, Category = "UI")
    FOnUIDeactivated OnUIDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "UI")
    FOnUILevelChanged OnUILevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "UI")
    FOnUIMaxLevelReached OnUIMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "UI")
    FOnUIPowerUsed OnUIPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "UI")
    FOnUIPowerFailed OnUIPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "UI")
    FOnUIAbilityPerformed OnUIAbilityPerformed;

    // UI Functions
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ActivateUI();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void DeactivateUI();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetUILevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void UseUIPower();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void PerformUIAbility();

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsUIActive() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetUILevel() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetUIPowerCost() const;

    // UI Abilities
    UFUNCTION(BlueprintCallable, Category = "UI")
    void CreateInterfaces();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void AccessHUDSystem();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void ControlMenuSystem();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void ApplyVisualFeedback();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateUI() const;
    void UpdateUIStats();
    void OnUIStateChanged();
};
