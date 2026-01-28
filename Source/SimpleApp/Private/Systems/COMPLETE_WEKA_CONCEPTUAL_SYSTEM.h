#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_WEKA_CONCEPTUAL_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWekaConceptualActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWekaConceptualDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnWekaConceptualLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWekaConceptualMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWekaConceptualPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWekaConceptualPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWekaConceptualAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_WEKA_CONCEPTUAL_SYSTEM();

    // Weka-Conceptual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weka-Conceptual")
    int32 WekaConceptualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weka-Conceptual")
    int32 MaxWekaConceptualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weka-Conceptual")
    bool bIsWekaConceptualActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weka-Conceptual")
    float WekaConceptualPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weka-Conceptual")
    float WekaConceptualThreshold;

    // Weka-Conceptual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weka-Conceptual")
    float WekascaleConceptMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weka-Conceptual")
    float SupremeUltraHyperMetaIdeaGeneration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weka-Conceptual")
    float ConceptualSupremeUltraHyperEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weka-Conceptual")
    float AbstractSupremeUltraHyperRealityCreation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weka-Conceptual")
    float UltimateConceptualSupremeUltimacy;

    // Weka-Conceptual Events
    UPROPERTY(BlueprintAssignable, Category = "Weka-Conceptual")
    FOnWekaConceptualActivated OnWekaConceptualActivated;

    UPROPERTY(BlueprintAssignable, Category = "Weka-Conceptual")
    FOnWekaConceptualDeactivated OnWekaConceptualDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Weka-Conceptual")
    FOnWekaConceptualLevelChanged OnWekaConceptualLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Weka-Conceptual")
    FOnWekaConceptualMaxLevelReached OnWekaConceptualMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Weka-Conceptual")
    FOnWekaConceptualPowerUsed OnWekaConceptualPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Weka-Conceptual")
    FOnWekaConceptualPowerFailed OnWekaConceptualPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Weka-Conceptual")
    FOnWekaConceptualAbilityPerformed OnWekaConceptualAbilityPerformed;

    // Weka-Conceptual Functions
    UFUNCTION(BlueprintCallable, Category = "Weka-Conceptual")
    void ActivateWekaConceptual();

    UFUNCTION(BlueprintCallable, Category = "Weka-Conceptual")
    void DeactivateWekaConceptual();

    UFUNCTION(BlueprintCallable, Category = "Weka-Conceptual")
    void SetWekaConceptualLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Weka-Conceptual")
    void UseWekaConceptualPower();

    UFUNCTION(BlueprintCallable, Category = "Weka-Conceptual")
    void PerformWekaConceptualAbility();

    UFUNCTION(BlueprintCallable, Category = "Weka-Conceptual")
    bool IsWekaConceptualActive() const;

    UFUNCTION(BlueprintCallable, Category = "Weka-Conceptual")
    int32 GetWekaConceptualLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Weka-Conceptual")
    float GetWekaConceptualPowerCost() const;

    // Weka-Conceptual Abilities
    UFUNCTION(BlueprintCallable, Category = "Weka-Conceptual")
    void MasterWekascaleConcepts();

    UFUNCTION(BlueprintCallable, Category = "Weka-Conceptual")
    void GenerateSupremeUltraHyperMetaIdeas();

    UFUNCTION(BlueprintCallable, Category = "Weka-Conceptual")
    void EvolveConceptuallySupremeUltraHyper();

    UFUNCTION(BlueprintCallable, Category = "Weka-Conceptual")
    void CreateAbstractSupremeUltraHyperReality();

    UFUNCTION(BlueprintCallable, Category = "Weka-Conceptual")
    void ExerciseUltimateConceptualSupremeUltimacy;

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateWekaConceptual() const;
    void UpdateWekaConceptualStats();
    void OnWekaConceptualStateChanged();
};
