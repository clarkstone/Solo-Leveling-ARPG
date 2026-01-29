#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P07_EXST_ULTRA.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraExistenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraExistenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnUltraExistenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltraExistenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraExistencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltraExistencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraExistenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP07_EXST_ULTRA : public UActorComponent
{
    GENERATED_BODY()

public:
    UP07_EXST_ULTRA();

    // Ultra Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Existence")
    int32 UltraExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Existence")
    int32 MaxUltraExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Existence")
    bool bIsUltraExistenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Existence")
    float UltraExistencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Existence")
    float UltraExistenceThreshold;

    // Ultra Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Existence")
    float UltraLifeForce;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Existence")
    float UltraPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Existence")
    float UltraInfiniteContinuum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Existence")
    float UltraTimelessPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Existence")
    float UltraSelfSufficiency;

    // Ultra Existence Events
    UPROPERTY(BlueprintAssignable, Category = "Ultra Existence")
    FOnUltraExistenceActivated OnUltraExistenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Existence")
    FOnUltraExistenceDeactivated OnUltraExistenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Existence")
    FOnUltraExistenceLevelChanged OnUltraExistenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Existence")
    FOnUltraExistenceMaxLevelReached OnUltraExistenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Existence")
    FOnUltraExistencePowerUsed OnUltraExistencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Existence")
    FOnUltraExistencePowerFailed OnUltraExistencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Existence")
    FOnUltraExistenceAbilityPerformed OnUltraExistenceAbilityPerformed;

    // Ultra Existence Functions
    UFUNCTION(BlueprintCallable, Category = "Ultra Existence")
    void ActivateUltraExistence();

    UFUNCTION(BlueprintCallable, Category = "Ultra Existence")
    void DeactivateUltraExistence();

    UFUNCTION(BlueprintCallable, Category = "Ultra Existence")
    void SetUltraExistenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Ultra Existence")
    void UseUltraExistencePower();

    UFUNCTION(BlueprintCallable, Category = "Ultra Existence")
    void PerformUltraExistenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Ultra Existence")
    bool IsUltraExistenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Ultra Existence")
    int32 GetUltraExistenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Ultra Existence")
    float GetUltraExistencePowerCost() const;

    // Ultra Existence Abilities
    UFUNCTION(BlueprintCallable, Category = "Ultra Existence")
    void ChannelUltraLifeForce();

    UFUNCTION(BlueprintCallable, Category = "Ultra Existence")
    void AchieveUltraPerpetuation();

    UFUNCTION(BlueprintCallable, Category = "Ultra Existence")
    void MaintainUltraInfiniteContinuum();

    UFUNCTION(BlueprintCallable, Category = "Ultra Existence")
    void PerpetuateUltraTimelessly();

    UFUNCTION(BlueprintCallable, Category = "Ultra Existence")
    void AchieveUltraSelfSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateUltraExistence() const;
    void UpdateUltraExistenceStats();
    void OnUltraExistenceStateChanged();
};
