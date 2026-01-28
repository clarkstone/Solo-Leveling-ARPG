#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_VELLA_CONCEPTUAL_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVellaConceptualActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVellaConceptualDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnVellaConceptualLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVellaConceptualMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVellaConceptualPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVellaConceptualPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVellaConceptualAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_VELLA_CONCEPTUAL_SYSTEM();

    // Vella-Conceptual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vella-Conceptual")
    int32 VellaConceptualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vella-Conceptual")
    int32 MaxVellaConceptualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vella-Conceptual")
    bool bIsVellaConceptualActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vella-Conceptual")
    float VellaConceptualPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vella-Conceptual")
    float VellaConceptualThreshold;

    // Vella-Conceptual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vella-Conceptual")
    float VellascaleConceptMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vella-Conceptual")
    float AbsoluteSupremeUltraHyperMetaIdeaGeneration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vella-Conceptual")
    float ConceptualAbsoluteSupremeUltraHyperEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vella-Conceptual")
    float AbstractAbsoluteSupremeUltraHyperRealityCreation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vella-Conceptual")
    float UltimateConceptualAbsoluteSupremeUltimacy;

    // Vella-Conceptual Events
    UPROPERTY(BlueprintAssignable, Category = "Vella-Conceptual")
    FOnVellaConceptualActivated OnVellaConceptualActivated;

    UPROPERTY(BlueprintAssignable, Category = "Vella-Conceptual")
    FOnVellaConceptualDeactivated OnVellaConceptualDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Vella-Conceptual")
    FOnVellaConceptualLevelChanged OnVellaConceptualLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Vella-Conceptual")
    FOnVellaConceptualMaxLevelReached OnVellaConceptualMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Vella-Conceptual")
    FOnVellaConceptualPowerUsed OnVellaConceptualPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Vella-Conceptual")
    FOnVellaConceptualPowerFailed OnVellaConceptualPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Vella-Conceptual")
    FOnVellaConceptualAbilityPerformed OnVellaConceptualAbilityPerformed;

    // Vella-Conceptual Functions
    UFUNCTION(BlueprintCallable, Category = "Vella-Conceptual")
    void ActivateVellaConceptual();

    UFUNCTION(BlueprintCallable, Category = "Vella-Conceptual")
    void DeactivateVellaConceptual();

    UFUNCTION(BlueprintCallable, Category = "Vella-Conceptual")
    void SetVellaConceptualLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Vella-Conceptual")
    void UseVellaConceptualPower();

    UFUNCTION(BlueprintCallable, Category = "Vella-Conceptual")
    void PerformVellaConceptualAbility();

    UFUNCTION(BlueprintCallable, Category = "Vella-Conceptual")
    bool IsVellaConceptualActive() const;

    UFUNCTION(BlueprintCallable, Category = "Vella-Conceptual")
    int32 GetVellaConceptualLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Vella-Conceptual")
    float GetVellaConceptualPowerCost() const;

    // Vella-Conceptual Abilities
    UFUNCTION(BlueprintCallable, Category = "Vella-Conceptual")
    void MasterVellascaleConcepts();

    UFUNCTION(BlueprintCallable, Category = "Vella-Conceptual")
    void GenerateAbsoluteSupremeUltraHyperMetaIdeas();

    UFUNCTION(BlueprintCallable, Category = "Vella-Conceptual")
    void EvolveConceptuallyAbsoluteSupremeUltraHyper();

    UFUNCTION(BlueprintCallable, Category = "Vella-Conceptual")
    void CreateAbstractAbsoluteSupremeUltraHyperReality();

    UFUNCTION(BlueprintCallable, Category = "Vella-Conceptual")
    void ExerciseUltimateConceptualAbsoluteSupremeUltimacy;

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateVellaConceptual() const;
    void UpdateVellaConceptualStats();
    void OnVellaConceptualStateChanged();
};
