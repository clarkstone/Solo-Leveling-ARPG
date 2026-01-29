#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P05_CORE_GOD_MODE.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGodModeActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGodModeDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnGodModeLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGodModeMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGodModePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGodModePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGodModeAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP05_CORE_GOD_MODE : public UActorComponent
{
    GENERATED_BODY()

public:
    UP05_CORE_GOD_MODE();

    // God Mode Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "God Mode")
    int32 GodModeLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "God Mode")
    int32 MaxGodModeLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "God Mode")
    bool bIsGodModeActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "God Mode")
    float GodModePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "God Mode")
    float GodModeThreshold;

    // God Mode Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "God Mode")
    float GodModePower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "God Mode")
    float Invincibility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "God Mode")
    float DivineAuthority;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "God Mode")
    float Omniscience;

    // God Mode Events
    UPROPERTY(BlueprintAssignable, Category = "God Mode")
    FOnGodModeActivated OnGodModeActivated;

    UPROPERTY(BlueprintAssignable, Category = "God Mode")
    FOnGodModeDeactivated OnGodModeDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "God Mode")
    FOnGodModeLevelChanged OnGodModeLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "God Mode")
    FOnGodModeMaxLevelReached OnGodModeMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "God Mode")
    FOnGodModePowerUsed OnGodModePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "God Mode")
    FOnGodModePowerFailed OnGodModePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "God Mode")
    FOnGodModeAbilityPerformed OnGodModeAbilityPerformed;

    // God Mode Functions
    UFUNCTION(BlueprintCallable, Category = "God Mode")
    void ActivateGodMode();

    UFUNCTION(BlueprintCallable, Category = "God Mode")
    void DeactivateGodMode();

    UFUNCTION(BlueprintCallable, Category = "God Mode")
    void SetGodModeLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "God Mode")
    void UseGodModePower();

    UFUNCTION(BlueprintCallable, Category = "God Mode")
    void PerformGodModeAbility();

    UFUNCTION(BlueprintCallable, Category = "God Mode")
    bool IsGodModeActive() const;

    UFUNCTION(BlueprintCallable, Category = "God Mode")
    int32 GetGodModeLevel() const;

    UFUNCTION(BlueprintCallable, Category = "God Mode")
    float GetGodModePowerCost() const;

    // God Mode Abilities
    UFUNCTION(BlueprintCallable, Category = "God Mode")
    void BecomeInvincible();

    UFUNCTION(BlueprintCallable, Category = "God Mode")
    void WieldDivineAuthority();

    UFUNCTION(BlueprintCallable, Category = "God Mode")
    void AccessOmniscience();

    UFUNCTION(BlueprintCallable, Category = "God Mode")
    void AchieveOmniscience();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateGodMode() const;
    void UpdateGodModeStats();
    void OnGodModeStateChanged();
};
