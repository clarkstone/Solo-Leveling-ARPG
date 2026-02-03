#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerSystemCore.h"
#include "PowerPathComponent.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SIMPLEAPP_API UPowerPathComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPowerPathComponent();

    // Path Information
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power Path")
    FPowerPathDefinition PathDefinition;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power Path")
    EPowerRank CurrentRank;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power Path")
    int32 CurrentExperience;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power Path")
    bool bIsActive;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power Path")
    bool bIsUnlocked;

    // Events
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRankUp, EPowerRank, OldRank, EPowerRank, NewRank);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityUnlocked, const FAbilityData&, Ability);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPathActivated, const FString&, PathName);

    UPROPERTY(BlueprintAssignable, Category = "Power Path Events")
    FOnRankUp OnRankUp;

    UPROPERTY(BlueprintAssignable, Category = "Power Path Events")
    FOnAbilityUnlocked OnAbilityUnlocked;

    UPROPERTY(BlueprintAssignable, Category = "Power Path Events")
    FOnPathActivated OnPathActivated;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Path Management
    UFUNCTION(BlueprintCallable, Category = "Power Path")
    void InitializePath(const FPowerPathDefinition& InPathDefinition);

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    void UnlockPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    void ActivatePath();

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    void DeactivatePath();

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    bool CanActivate() const;

    // Progression
    UFUNCTION(BlueprintCallable, Category = "Power Path")
    void AddExperience(int32 ExperienceAmount);

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    bool CanRankUp() const;

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    void RankUp();

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    EPowerRank GetNextRank() const;

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    int32 GetExperienceToNextRank() const;

    // Abilities
    UFUNCTION(BlueprintCallable, Category = "Power Path")
    TArray<FAbilityData> GetCurrentAbilities() const;

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    TArray<FAbilityData> GetAbilitiesForRank(EPowerRank Rank) const;

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    bool HasAbility(const FString& AbilityName) const;

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    FAbilityData GetAbility(const FString& AbilityName) const;

    // Power System Integration
    UFUNCTION(BlueprintCallable, Category = "Power Path")
    int32 GetPowerLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    float GetPowerMultiplier() const;

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    FString GetCurrentRankTitle() const;

    // Utility
    UFUNCTION(BlueprintCallable, Category = "Power Path")
    bool IsLegendaryPath() const;

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    ECoreClass GetCoreClass() const;

    UFUNCTION(BlueprintCallable, Category = "Power Path")
    FString GetPathName() const;

protected:
    // Internal Functions
    void UpdateAbilities();
    void OnRankUpInternal();
    void CalculatePowerLevel();
    void NotifyAbilityUnlocked(const FAbilityData& Ability);

private:
    // Internal State
    int32 CachedPowerLevel;
    float CachedPowerMultiplier;
    TMap<EPowerRank, TArray<FAbilityData>> CachedAbilities;

    // Helper Functions
    int32 GetRequiredExperienceForRank(EPowerRank Rank) const;
    void UpdateCachedData();
};
