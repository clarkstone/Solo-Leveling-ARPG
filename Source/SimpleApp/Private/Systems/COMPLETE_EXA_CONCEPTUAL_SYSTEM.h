#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_EXA_CONCEPTUAL_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExaConceptualActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExaConceptualDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnExaConceptualLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExaConceptualMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExaConceptualPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExaConceptualPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExaConceptualAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_EXA_CONCEPTUAL_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_EXA_CONCEPTUAL_SYSTEM();

    // Exa-Conceptual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exa-Conceptual")
    int32 ExaConceptualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exa-Conceptual")
    int32 MaxExaConceptualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exa-Conceptual")
    bool bIsExaConceptualActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exa-Conceptual")
    float ExaConceptualPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exa-Conceptual")
    float ExaConceptualThreshold;

    // Exa-Conceptual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exa-Conceptual")
    float ExascaleConceptMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exa-Conceptual")
    float InfiniteIdeaGeneration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exa-Conceptual")
    float ConceptualRealityShaping;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exa-Conceptual")
    float AbstractThoughtManifestation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exa-Conceptual")
    float MetaConceptualAuthority;

    // Exa-Conceptual Events
    UPROPERTY(BlueprintAssignable, Category = "Exa-Conceptual")
    FOnExaConceptualActivated OnExaConceptualActivated;

    UPROPERTY(BlueprintAssignable, Category = "Exa-Conceptual")
    FOnExaConceptualDeactivated OnExaConceptualDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Exa-Conceptual")
    FOnExaConceptualLevelChanged OnExaConceptualLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Exa-Conceptual")
    FOnExaConceptualMaxLevelReached OnExaConceptualMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Exa-Conceptual")
    FOnExaConceptualPowerUsed OnExaConceptualPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Exa-Conceptual")
    FOnExaConceptualPowerFailed OnExaConceptualPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Exa-Conceptual")
    FOnExaConceptualAbilityPerformed OnExaConceptualAbilityPerformed;

    // Exa-Conceptual Functions
    UFUNCTION(BlueprintCallable, Category = "Exa-Conceptual")
    void ActivateExaConceptual();

    UFUNCTION(BlueprintCallable, Category = "Exa-Conceptual")
    void DeactivateExaConceptual();

    UFUNCTION(BlueprintCallable, Category = "Exa-Conceptual")
    void SetExaConceptualLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Exa-Conceptual")
    void UseExaConceptualPower();

    UFUNCTION(BlueprintCallable, Category = "Exa-Conceptual")
    void PerformExaConceptualAbility();

    UFUNCTION(BlueprintCallable, Category = "Exa-Conceptual")
    bool IsExaConceptualActive() const;

    UFUNCTION(BlueprintCallable, Category = "Exa-Conceptual")
    int32 GetExaConceptualLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Exa-Conceptual")
    float GetExaConceptualPowerCost() const;

    // Exa-Conceptual Abilities
    UFUNCTION(BlueprintCallable, Category = "Exa-Conceptual")
    void MasterExascaleConcepts();

    UFUNCTION(BlueprintCallable, Category = "Exa-Conceptual")
    void GenerateInfiniteIdeas();

    UFUNCTION(BlueprintCallable, Category = "Exa-Conceptual")
    void ShapeConceptualReality();

    UFUNCTION(BlueprintCallable, Category = "Exa-Conceptual")
    void ManifestAbstractThoughts();

    UFUNCTION(BlueprintCallable, Category = "Exa-Conceptual")
    void ExerciseMetaConceptualAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateExaConceptual() const;
    void UpdateExaConceptualStats();
    void OnExaConceptualStateChanged();
};
