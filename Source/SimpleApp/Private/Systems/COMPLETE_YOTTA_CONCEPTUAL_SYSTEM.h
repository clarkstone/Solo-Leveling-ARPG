#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_YOTTA_CONCEPTUAL_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnYottaConceptualActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnYottaConceptualDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnYottaConceptualLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnYottaConceptualMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnYottaConceptualPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnYottaConceptualPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnYottaConceptualAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_YOTTA_CONCEPTUAL_SYSTEM();

    // Yotta-Conceptual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yotta-Conceptual")
    int32 YottaConceptualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yotta-Conceptual")
    int32 MaxYottaConceptualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yotta-Conceptual")
    bool bIsYottaConceptualActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yotta-Conceptual")
    float YottaConceptualPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yotta-Conceptual")
    float YottaConceptualThreshold;

    // Yotta-Conceptual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yotta-Conceptual")
    float YottascaleConceptMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yotta-Conceptual")
    float HyperMetaIdeaGeneration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yotta-Conceptual")
    float ConceptualHyperEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yotta-Conceptual")
    float AbstractHyperRealityCreation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Yotta-Conceptual")
    float UltimateConceptualSupremacy;

    // Yotta-Conceptual Events
    UPROPERTY(BlueprintAssignable, Category = "Yotta-Conceptual")
    FOnYottaConceptualActivated OnYottaConceptualActivated;

    UPROPERTY(BlueprintAssignable, Category = "Yotta-Conceptual")
    FOnYottaConceptualDeactivated OnYottaConceptualDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Yotta-Conceptual")
    FOnYottaConceptualLevelChanged OnYottaConceptualLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Yotta-Conceptual")
    FOnYottaConceptualMaxLevelReached OnYottaConceptualMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Yotta-Conceptual")
    FOnYottaConceptualPowerUsed OnYottaConceptualPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Yotta-Conceptual")
    FOnYottaConceptualPowerFailed OnYottaConceptualPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Yotta-Conceptual")
    FOnYottaConceptualAbilityPerformed OnYottaConceptualAbilityPerformed;

    // Yotta-Conceptual Functions
    UFUNCTION(BlueprintCallable, Category = "Yotta-Conceptual")
    void ActivateYottaConceptual();

    UFUNCTION(BlueprintCallable, Category = "Yotta-Conceptual")
    void DeactivateYottaConceptual();

    UFUNCTION(BlueprintCallable, Category = "Yotta-Conceptual")
    void SetYottaConceptualLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Yotta-Conceptual")
    void UseYottaConceptualPower();

    UFUNCTION(BlueprintCallable, Category = "Yotta-Conceptual")
    void PerformYottaConceptualAbility();

    UFUNCTION(BlueprintCallable, Category = "Yotta-Conceptual")
    bool IsYottaConceptualActive() const;

    UFUNCTION(BlueprintCallable, Category = "Yotta-Conceptual")
    int32 GetYottaConceptualLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Yotta-Conceptual")
    float GetYottaConceptualPowerCost() const;

    // Yotta-Conceptual Abilities
    UFUNCTION(BlueprintCallable, Category = "Yotta-Conceptual")
    void MasterYottascaleConcepts();

    UFUNCTION(BlueprintCallable, Category = "Yotta-Conceptual")
    void GenerateHyperMetaIdeas();

    UFUNCTION(BlueprintCallable, Category = "Yotta-Conceptual")
    void EvolveConceptuallyHyper();

    UFUNCTION(BlueprintCallable, Category = "Yotta-Conceptual")
    void CreateAbstractHyperReality();

    UFUNCTION(BlueprintCallable, Category = "Yotta-Conceptual")
    void ExerciseUltimateConceptualSupremacy;

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateYottaConceptual() const;
    void UpdateYottaConceptualStats();
    void OnYottaConceptualStateChanged();
};
