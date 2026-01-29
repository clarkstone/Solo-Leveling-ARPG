#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P04_CNCP_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConceptualActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConceptualDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnConceptualLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConceptualMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConceptualPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConceptualPowerFailed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConceptualAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP04_CNCP_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UP04_CNCP_SYSTEM();

    // Conceptual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conceptual")
    int32 ConceptualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conceptual")
    int32 MaxConceptualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conceptual")
    bool bIsConceptualActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conceptual")
    float ConceptualPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conceptual")
    float ConceptualThreshold;

    // Conceptual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conceptual")
    float ConceptualMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conceptual")
    float UltimateIdeaGeneration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conceptual")
    float ConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conceptual")
    float AbstractRealityCreation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conceptual")
    float UltimateConceptualUltimacy;

    // Conceptual Events
    UPROPERTY(BlueprintAssignable, Category = "Conceptual")
    FOnConceptualActivated OnConceptualActivated);

    UPROPERTY(BlueprintAssignable, Category = "Conceptual")
    FOnConceptualDeactivated OnConceptualDeactivated);

    UPROPERTY(BlueprintAssignable, Category = "Conceptual")
    FOnConceptualLevelChanged OnConceptualLevelChanged);

    UPROPERTY(BlueprintAssignable, Category = "Conceptual")
    FOnConceptualMaxLevelReached OnConceptualMaxLevelReached);

    UPROPERTY(BlueprintAssignable, Category = "Conceptual")
    FOnConceptualPowerUsed OnConceptualPowerUsed);

    UPROPERTY(BlueprintAssignable, Category = "Conceptual")
    FOnConceptualPowerFailed OnConceptualPowerFailed);

    UPROPERTY(BlueprintAssignable, Category = "Conceptual")
    FOnConceptualAbilityPerformed OnConceptualAbilityPerformed);

    // Conceptual Functions
    UFUNCTION(BlueprintCallable, Category = "Conceptual")
    void MasterConcepts();

    UFUNCTION(BlueprintCallable, Category = "Conceptual")
    void GenerateUltimateIdeas();

    UFUNCTION(BlueprintCallable, Category = "Conceptual")
    void EvolveConceptually();

    UFUNCTION(BlueprintCallable, Category = "Conceptual")
    void CreateAbstractReality();

    UFUNCTION(BlueprintCallable, Category = "Conceptual")
    void ExerciseUltimateConceptualUltimacy();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateConceptual() const;
    void UpdateConceptualStats();
    void OnConceptualStateChanged();
};
