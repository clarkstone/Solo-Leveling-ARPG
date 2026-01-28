#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_ETERNAL_COSMIC_VOID_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalCosmicVoidActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalCosmicVoidDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnEternalCosmicVoidLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEternalCosmicVoidMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalCosmicVoidPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEternalCosmicVoidPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalCosmicVoidAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM();

    // Eternal-Cosmic-Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Cosmic-Void")
    int32 EternalCosmicVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Cosmic-Void")
    int32 MaxEternalCosmicVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Cosmic-Void")
    bool bIsEternalCosmicVoidActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Cosmic-Void")
    float EternalCosmicVoidPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Cosmic-Void")
    float EternalCosmicVoidThreshold;

    // Eternal-Cosmic-Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Cosmic-Void")
    float EternalCosmicVoidMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Cosmic-Void")
    float FinalAbsoluteVoidAnnihilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Cosmic-Void")
    float PerfectEternalCosmicNullEmptiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Cosmic-Void")
    float ConceptualEternalCosmicOblivion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Cosmic-Void")
    float ExistenceEternalCosmicNegation;

    // Eternal-Cosmic-Void Events
    UPROPERTY(BlueprintAssignable, Category = "Eternal-Cosmic-Void")
    FOnEternalCosmicVoidActivated OnEternalCosmicVoidActivated;

    UPROPERTY(BlueprintAssignable, Category = "Eternal-Cosmic-Void")
    FOnEternalCosmicVoidDeactivated OnEternalCosmicVoidDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Eternal-Cosmic-Void")
    FOnEternalCosmicVoidLevelChanged OnEternalCosmicVoidLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Eternal-Cosmic-Void")
    FOnEternalCosmicVoidMaxLevelReached OnEternalCosmicVoidMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Eternal-Cosmic-Void")
    FOnEternalCosmicVoidPowerUsed OnEternalCosmicVoidPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Eternal-Cosmic-Void")
    FOnEternalCosmicVoidPowerFailed OnEternalCosmicVoidPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Eternal-Cosmic-Void")
    FOnEternalCosmicVoidAbilityPerformed OnEternalCosmicVoidAbilityPerformed;

    // Eternal-Cosmic-Void Functions
    UFUNCTION(BlueprintCallable, Category = "Eternal-Cosmic-Void")
    void ActivateEternalCosmicVoid();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Cosmic-Void")
    void DeactivateEternalCosmicVoid();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Cosmic-Void")
    void SetEternalCosmicVoidLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Eternal-Cosmic-Void")
    void UseEternalCosmicVoidPower();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Cosmic-Void")
    void PerformEternalCosmicVoidAbility();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Cosmic-Void")
    bool IsEternalCosmicVoidActive() const;

    UFUNCTION(BlueprintCallable, Category = "Eternal-Cosmic-Void")
    int32 GetEternalCosmicVoidLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Eternal-Cosmic-Void")
    float GetEternalCosmicVoidPowerCost() const;

    // Eternal-Cosmic-Void Abilities
    UFUNCTION(BlueprintCallable, Category = "Eternal-Cosmic-Void")
    void MasterEternalCosmicVoid();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Cosmic-Void")
    void AnnihilateEternalCosmicUltimately();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Cosmic-Void")
    void AchievePerfectEternalCosmicNullEmptiness();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Cosmic-Void")
    void InduceConceptualEternalCosmicOblivion();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Cosmic-Void")
    void NegateExistenceEternalCosmic();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateEternalCosmicVoid() const;
    void UpdateEternalCosmicVoidStats();
    void OnEternalCosmicVoidStateChanged();
};
