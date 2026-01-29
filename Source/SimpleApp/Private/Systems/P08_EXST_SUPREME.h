#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P08_EXST_SUPREME.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeExistenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeExistenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnSupremeExistenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSupremeExistenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeExistencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSupremeExistencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeExistenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP08_EXST_SUPREME : public UActorComponent
{
    GENERATED_BODY()

public:
    UP08_EXST_SUPREME();

    // Supreme Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Existence")
    int32 SupremeExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Existence")
    int32 MaxSupremeExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Existence")
    bool bIsSupremeExistenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Existence")
    float SupremeExistencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Existence")
    float SupremeExistenceThreshold;

    // Supreme Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Existence")
    float SupremeLifeForce;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Existence")
    float SupremePerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Existence")
    float SupremeInfiniteContinuum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Existence")
    float SupremeTimelessPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Existence")
    float SupremeSelfSufficiency;

    // Supreme Existence Events
    UPROPERTY(BlueprintAssignable, Category = "Supreme Existence")
    FOnSupremeExistenceActivated OnSupremeExistenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Existence")
    FOnSupremeExistenceDeactivated OnSupremeExistenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Existence")
    FOnSupremeExistenceLevelChanged OnSupremeExistenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Existence")
    FOnSupremeExistenceMaxLevelReached OnSupremeExistenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Existence")
    FOnSupremeExistencePowerUsed OnSupremeExistencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Existence")
    FOnSupremeExistencePowerFailed OnSupremeExistencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Existence")
    FOnSupremeExistenceAbilityPerformed OnSupremeExistenceAbilityPerformed;

    // Supreme Existence Functions
    UFUNCTION(BlueprintCallable, Category = "Supreme Existence")
    void ActivateSupremeExistence();

    UFUNCTION(BlueprintCallable, Category = "Supreme Existence")
    void DeactivateSupremeExistence();

    UFUNCTION(BlueprintCallable, Category = "Supreme Existence")
    void SetSupremeExistenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Supreme Existence")
    void UseSupremeExistencePower();

    UFUNCTION(BlueprintCallable, Category = "Supreme Existence")
    void PerformSupremeExistenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Supreme Existence")
    bool IsSupremeExistenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Supreme Existence")
    int32 GetSupremeExistenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Supreme Existence")
    float GetSupremeExistencePowerCost() const;

    // Supreme Existence Abilities
    UFUNCTION(BlueprintCallable, Category = "Supreme Existence")
    void ChannelSupremeLifeForce();

    UFUNCTION(BlueprintCallable, Category = "Supreme Existence")
    void AchieveSupremePerpetuation();

    UFUNCTION(BlueprintCallable, Category = "Supreme Existence")
    void MaintainSupremeInfiniteContinuum();

    UFUNCTION(BlueprintCallable, Category = "Supreme Existence")
    void PerpetuateSupremeTimelessly();

    UFUNCTION(BlueprintCallable, Category = "Supreme Existence")
    void AchieveSupremeSelfSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateSupremeExistence() const;
    void UpdateSupremeExistenceStats();
    void OnSupremeExistenceStateChanged();
};
