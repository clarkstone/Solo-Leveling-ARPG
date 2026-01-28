#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_COSMIC_NULL_VOID_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCosmicNullVoidActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCosmicNullVoidDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnCosmicNullVoidLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCosmicNullVoidMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCosmicNullVoidPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCosmicNullVoidPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCosmicNullVoidAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_COSMIC_NULL_VOID_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_COSMIC_NULL_VOID_SYSTEM();

    // Cosmic-Null-Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmic-Null-Void")
    int32 CosmicNullVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmic-Null-Void")
    int32 MaxCosmicNullVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmic-Null-Void")
    bool bIsCosmicNullVoidActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmic-Null-Void")
    float CosmicNullVoidPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmic-Null-Void")
    float CosmicNullVoidThreshold;

    // Cosmic-Null-Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmic-Null-Void")
    float CosmicNullVoidMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmic-Null-Void")
    float UltimateAbsoluteVoidAnnihilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmic-Null-Void")
    float PerfectCosmicNullEmptiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmic-Null-Void")
    float ConceptualCosmicNullOblivion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmic-Null-Void")
    float ExistenceCosmicNullNegation;

    // Cosmic-Null-Void Events
    UPROPERTY(BlueprintAssignable, Category = "Cosmic-Null-Void")
    FOnCosmicNullVoidActivated OnCosmicNullVoidActivated;

    UPROPERTY(BlueprintAssignable, Category = "Cosmic-Null-Void")
    FOnCosmicNullVoidDeactivated OnCosmicNullVoidDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Cosmic-Null-Void")
    FOnCosmicNullVoidLevelChanged OnCosmicNullVoidLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Cosmic-Null-Void")
    FOnCosmicNullVoidMaxLevelReached OnCosmicNullVoidMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Cosmic-Null-Void")
    FOnCosmicNullVoidPowerUsed OnCosmicNullVoidPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Cosmic-Null-Void")
    FOnCosmicNullVoidPowerFailed OnCosmicNullVoidPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Cosmic-Null-Void")
    FOnCosmicNullVoidAbilityPerformed OnCosmicNullVoidAbilityPerformed;

    // Cosmic-Null-Void Functions
    UFUNCTION(BlueprintCallable, Category = "Cosmic-Null-Void")
    void ActivateCosmicNullVoid();

    UFUNCTION(BlueprintCallable, Category = "Cosmic-Null-Void")
    void DeactivateCosmicNullVoid();

    UFUNCTION(BlueprintCallable, Category = "Cosmic-Null-Void")
    void SetCosmicNullVoidLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Cosmic-Null-Void")
    void UseCosmicNullVoidPower();

    UFUNCTION(BlueprintCallable, Category = "Cosmic-Null-Void")
    void PerformCosmicNullVoidAbility();

    UFUNCTION(BlueprintCallable, Category = "Cosmic-Null-Void")
    bool IsCosmicNullVoidActive() const;

    UFUNCTION(BlueprintCallable, Category = "Cosmic-Null-Void")
    int32 GetCosmicNullVoidLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Cosmic-Null-Void")
    float GetCosmicNullVoidPowerCost() const;

    // Cosmic-Null-Void Abilities
    UFUNCTION(BlueprintCallable, Category = "Cosmic-Null-Void")
    void MasterCosmicNullVoid();

    UFUNCTION(BlueprintCallable, Category = "Cosmic-Null-Void")
    void AnnihilateCosmicNullUltimately();

    UFUNCTION(BlueprintCallable, Category = "Cosmic-Null-Void")
    void AchievePerfectCosmicNullEmptiness();

    UFUNCTION(BlueprintCallable, Category = "Cosmic-Null-Void")
    void InduceConceptualCosmicNullOblivion();

    UFUNCTION(BlueprintCallable, Category = "Cosmic-Null-Void")
    void NegateExistenceCosmicNull();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateCosmicNullVoid() const;
    void UpdateCosmicNullVoidStats();
    void OnCosmicNullVoidStateChanged();
};
