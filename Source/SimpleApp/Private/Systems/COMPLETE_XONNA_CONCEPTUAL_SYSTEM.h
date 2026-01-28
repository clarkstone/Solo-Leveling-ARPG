#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_XONNA_CONCEPTUAL_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnXonnaConceptualActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnXonnaConceptualDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnXonnaConceptualLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnXonnaConceptualMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnXonnaConceptualPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnXonnaConceptualPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnXonnaConceptualAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_XONNA_CONCEPTUAL_SYSTEM();

    // Xonna-Conceptual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xonna-Conceptual")
    int32 XonnaConceptualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xonna-Conceptual")
    int32 MaxXonnaConceptualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xonna-Conceptual")
    bool bIsXonnaConceptualActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xonna-Conceptual")
    float XonnaConceptualPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xonna-Conceptual")
    float XonnaConceptualThreshold;

    // Xonna-Conceptual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xonna-Conceptual")
    float XonnascaleConceptMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xonna-Conceptual")
    float UltraHyperMetaIdeaGeneration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xonna-Conceptual")
    float ConceptualUltraHyperEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xonna-Conceptual")
    float AbstractUltraHyperRealityCreation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Xonna-Conceptual")
    float UltimateConceptualUltimacy;

    // Xonna-Conceptual Events
    UPROPERTY(BlueprintAssignable, Category = "Xonna-Conceptual")
    FOnXonnaConceptualActivated OnXonnaConceptualActivated;

    UPROPERTY(BlueprintAssignable, Category = "Xonna-Conceptual")
    FOnXonnaConceptualDeactivated OnXonnaConceptualDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Xonna-Conceptual")
    FOnXonnaConceptualLevelChanged OnXonnaConceptualLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Xonna-Conceptual")
    FOnXonnaConceptualMaxLevelReached OnXonnaConceptualMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Xonna-Conceptual")
    FOnXonnaConceptualPowerUsed OnXonnaConceptualPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Xonna-Conceptual")
    FOnXonnaConceptualPowerFailed OnXonnaConceptualPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Xonna-Conceptual")
    FOnXonnaConceptualAbilityPerformed OnXonnaConceptualAbilityPerformed;

    // Xonna-Conceptual Functions
    UFUNCTION(BlueprintCallable, Category = "Xonna-Conceptual")
    void ActivateXonnaConceptual();

    UFUNCTION(BlueprintCallable, Category = "Xonna-Conceptual")
    void DeactivateXonnaConceptual();

    UFUNCTION(BlueprintCallable, Category = "Xonna-Conceptual")
    void SetXonnaConceptualLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Xonna-Conceptual")
    void UseXonnaConceptualPower();

    UFUNCTION(BlueprintCallable, Category = "Xonna-Conceptual")
    void PerformXonnaConceptualAbility();

    UFUNCTION(BlueprintCallable, Category = "Xonna-Conceptual")
    bool IsXonnaConceptualActive() const;

    UFUNCTION(BlueprintCallable, Category = "Xonna-Conceptual")
    int32 GetXonnaConceptualLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Xonna-Conceptual")
    float GetXonnaConceptualPowerCost() const;

    // Xonna-Conceptual Abilities
    UFUNCTION(BlueprintCallable, Category = "Xonna-Conceptual")
    void MasterXonnascaleConcepts();

    UFUNCTION(BlueprintCallable, Category = "Xonna-Conceptual")
    void GenerateUltraHyperMetaIdeas();

    UFUNCTION(BlueprintCallable, Category = "Xonna-Conceptual")
    void EvolveConceptuallyUltraHyper();

    UFUNCTION(BlueprintCallable, Category = "Xonna-Conceptual")
    void CreateAbstractUltraHyperReality();

    UFUNCTION(BlueprintCallable, Category = "Xonna-Conceptual")
    void ExerciseUltimateConceptualUltimacy;

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateXonnaConceptual() const;
    void UpdateXonnaConceptualStats();
    void OnXonnaConceptualStateChanged();
};
