#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P06_TRNS_META_PHASE6.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaPhase6Activated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaPhase6Deactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnMetaPhase6LevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMetaPhase6MaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaPhase6PowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMetaPhase6PowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaPhase6AbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP06_TRNS_PHASE6 : public UActorComponent
{
    GENERATED_BODY()

public:
    UP06_TRNS_PHASE6();

    // Meta Phase6 Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Phase6")
    int32 MetaPhase6Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Phase6")
    int32 MaxMetaPhase6Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Phase6")
    bool bIsMetaPhase6Active;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Phase6")
    float MetaPhase6PowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Phase6")
    float MetaPhase6Threshold;

    // Meta Phase6 Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Phase6")
    float MetaPhase6Dominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Phase6")
    float Phase6UltimateRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Phase6")
    float MetaPhase6InfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Phase6")
    float ConceptualPhase6Evolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Phase6")
    float Phase6UltimateAuthority;

    // Meta Phase6 Events
    UPROPERTY(BlueprintAssignable, Category = "Meta Phase6")
    FOnMetaPhase6Activated OnMetaPhase6Activated;

    UPROPERTY(BlueprintAssignable, Category = "Meta Phase6")
    FOnMetaPhase6Deactivated OnMetaPhase6Deactivated;

    UPROPERTY(BlueprintAssignable, Category = "Meta Phase6")
    FOnMetaPhase6LevelChanged OnMetaPhase6LevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Meta Phase6")
    FOnMetaPhase6MaxLevelReached OnMetaPhase6MaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Meta Phase6")
    FOnMetaPhase6PowerUsed OnMetaPhase6PowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Meta Phase6")
    FOnMetaPhase6PowerFailed OnMetaPhase6PowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Meta Phase6")
    FOnMetaPhase6AbilityPerformed OnMetaPhase6AbilityPerformed;

    // Meta Phase6 Functions
    UFUNCTION(BlueprintCallable, Category = "Meta Phase6")
    void ActivateMetaPhase6();

    UFUNCTION(BlueprintCallable, Category = "Meta Phase6")
    void DeactivateMetaPhase6();

    UFUNCTION(BlueprintCallable, Category = "Meta Phase6")
    void SetMetaPhase6Level(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Meta Phase6")
    void UseMetaPhase6Power();

    UFUNCTION(BlueprintCallable, Category = "Meta Phase6")
    void PerformMetaPhase6Ability();

    UFUNCTION(BlueprintCallable, Category = "Meta Phase6")
    bool IsMetaPhase6Active() const;

    UFUNCTION(BlueprintCallable, Category = "Meta Phase6")
    int32 GetMetaPhase6Level() const;

    UFUNCTION(BlueprintCallable, Category = "Meta Phase6")
    float GetMetaPhase6PowerCost() const;

    // Meta Phase6 Abilities
    UFUNCTION(BlueprintCallable, Category = "Meta Phase6")
    void ExerciseMetaPhase6Dominion();

    UFUNCTION(BlueprintCallable, Category = "Meta Phase6")
    void TranscendPhase6UltimateRecursion();

    UFUNCTION(BlueprintCallable, Category = "Meta Phase6")
    void AccessMetaPhase6InfiniteConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Meta Phase6")
    void EvolveConceptuallyPhase6();

    UFUNCTION(BlueprintCallable, Category = "Meta Phase6")
    void WieldPhase6UltimateAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateMetaPhase6() const;
    void UpdateMetaPhase6Stats();
    void OnMetaPhase6StateChanged();
};
