#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_ZETTA_CONCEPTUAL_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZettaConceptualActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZettaConceptualDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnZettaConceptualLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnZettaConceptualMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZettaConceptualPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnZettaConceptualPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZettaConceptualAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_ZETTA_CONCEPTUAL_SYSTEM();

    // Zetta-Conceptual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zetta-Conceptual")
    int32 ZettaConceptualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zetta-Conceptual")
    int32 MaxZettaConceptualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zetta-Conceptual")
    bool bIsZettaConceptualActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zetta-Conceptual")
    float ZettaConceptualPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zetta-Conceptual")
    float ZettaConceptualThreshold;

    // Zetta-Conceptual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zetta-Conceptual")
    float ZettascaleConceptMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zetta-Conceptual")
    float MetaIdeaGeneration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zetta-Conceptual")
    float ConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zetta-Conceptual")
    float AbstractRealityCreation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zetta-Conceptual")
    float UltimateConceptualDominion;

    // Zetta-Conceptual Events
    UPROPERTY(BlueprintAssignable, Category = "Zetta-Conceptual")
    FOnZettaConceptualActivated OnZettaConceptualActivated;

    UPROPERTY(BlueprintAssignable, Category = "Zetta-Conceptual")
    FOnZettaConceptualDeactivated OnZettaConceptualDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Zetta-Conceptual")
    FOnZettaConceptualLevelChanged OnZettaConceptualLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Zetta-Conceptual")
    FOnZettaConceptualMaxLevelReached OnZettaConceptualMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Zetta-Conceptual")
    FOnZettaConceptualPowerUsed OnZettaConceptualPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Zetta-Conceptual")
    FOnZettaConceptualPowerFailed OnZettaConceptualPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Zetta-Conceptual")
    FOnZettaConceptualAbilityPerformed OnZettaConceptualAbilityPerformed;

    // Zetta-Conceptual Functions
    UFUNCTION(BlueprintCallable, Category = "Zetta-Conceptual")
    void ActivateZettaConceptual();

    UFUNCTION(BlueprintCallable, Category = "Zetta-Conceptual")
    void DeactivateZettaConceptual();

    UFUNCTION(BlueprintCallable, Category = "Zetta-Conceptual")
    void SetZettaConceptualLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Zetta-Conceptual")
    void UseZettaConceptualPower();

    UFUNCTION(BlueprintCallable, Category = "Zetta-Conceptual")
    void PerformZettaConceptualAbility();

    UFUNCTION(BlueprintCallable, Category = "Zetta-Conceptual")
    bool IsZettaConceptualActive() const;

    UFUNCTION(BlueprintCallable, Category = "Zetta-Conceptual")
    int32 GetZettaConceptualLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Zetta-Conceptual")
    float GetZettaConceptualPowerCost() const;

    // Zetta-Conceptual Abilities
    UFUNCTION(BlueprintCallable, Category = "Zetta-Conceptual")
    void MasterZettascaleConcepts();

    UFUNCTION(BlueprintCallable, Category = "Zetta-Conceptual")
    void GenerateMetaIdeas();

    UFUNCTION(BlueprintCallable, Category = "Zetta-Conceptual")
    void EvolveConceptually();

    UFUNCTION(BlueprintCallable, Category = "Zetta-Conceptual")
    void CreateAbstractReality();

    UFUNCTION(BlueprintCallable, Category = "Zetta-Conceptual")
    void ExerciseUltimateConceptualDominion();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateZettaConceptual() const;
    void UpdateZettaConceptualStats();
    void OnZettaConceptualStateChanged();
};
