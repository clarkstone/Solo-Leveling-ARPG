#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmniversalNothingnessActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmniversalNothingnessDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnOmniversalNothingnessLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmniversalNothingnessMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmniversalNothingnessPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmniversalNothingnessPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmniversalNothingnessAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_OMNIVERSAL_NOTHINGNESS_SYSTEM();

    // Omniversal-Nothingness Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omniversal-Nothingness")
    int32 OmniversalNothingnessLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omniversal-Nothingness")
    int32 MaxOmniversalNothingnessLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omniversal-Nothingness")
    bool bIsOmniversalNothingnessActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omniversal-Nothingness")
    float OmniversalNothingnessPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omniversal-Nothingness")
    float OmniversalNothingnessThreshold;

    // Omniversal-Nothingness Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omniversal-Nothingness")
    float OmniversalVoidControl;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omniversal-Nothingness")
    float AbsoluteAnnihilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omniversal-Nothingness")
    float InfiniteEmptiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omniversal-Nothingness")
    float ConceptualNullification;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omniversal-Nothingness")
    float ExistenceErasion;

    // Omniversal-Nothingness Events
    UPROPERTY(BlueprintAssignable, Category = "Omniversal-Nothingness")
    FOnOmniversalNothingnessActivated OnOmniversalNothingnessActivated;

    UPROPERTY(BlueprintAssignable, Category = "Omniversal-Nothingness")
    FOnOmniversalNothingnessDeactivated OnOmniversalNothingnessDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Omniversal-Nothingness")
    FOnOmniversalNothingnessLevelChanged OnOmniversalNothingnessLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Omniversal-Nothingness")
    FOnOmniversalNothingnessMaxLevelReached OnOmniversalNothingnessMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Omniversal-Nothingness")
    FOnOmniversalNothingnessPowerUsed OnOmniversalNothingnessPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Omniversal-Nothingness")
    FOnOmniversalNothingnessPowerFailed OnOmniversalNothingnessPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Omniversal-Nothingness")
    FOnOmniversalNothingnessAbilityPerformed OnOmniversalNothingnessAbilityPerformed;

    // Omniversal-Nothingness Functions
    UFUNCTION(BlueprintCallable, Category = "Omniversal-Nothingness")
    void ActivateOmniversalNothingness();

    UFUNCTION(BlueprintCallable, Category = "Omniversal-Nothingness")
    void DeactivateOmniversalNothingness();

    UFUNCTION(BlueprintCallable, Category = "Omniversal-Nothingness")
    void SetOmniversalNothingnessLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Omniversal-Nothingness")
    void UseOmniversalNothingnessPower();

    UFUNCTION(BlueprintCallable, Category = "Omniversal-Nothingness")
    void PerformOmniversalNothingnessAbility();

    UFUNCTION(BlueprintCallable, Category = "Omniversal-Nothingness")
    bool IsOmniversalNothingnessActive() const;

    UFUNCTION(BlueprintCallable, Category = "Omniversal-Nothingness")
    int32 GetOmniversalNothingnessLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Omniversal-Nothingness")
    float GetOmniversalNothingnessPowerCost() const;

    // Omniversal-Nothingness Abilities
    UFUNCTION(BlueprintCallable, Category = "Omniversal-Nothingness")
    void ControlOmniversalVoid();

    UFUNCTION(BlueprintCallable, Category = "Omniversal-Nothingness")
    void AnnihilateAbsolutely();

    UFUNCTION(BlueprintCallable, Category = "Omniversal-Nothingness")
    void EmptifyInfinitely();

    UFUNCTION(BlueprintCallable, Category = "Omniversal-Nothingness")
    void NullifyConceptually();

    UFUNCTION(BlueprintCallable, Category = "Omniversal-Nothingness")
    void EraseExistence();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateOmniversalNothingness() const;
    void UpdateOmniversalNothingnessStats();
    void OnOmniversalNothingnessStateChanged();
};
