#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerSystemCore.h"
#include "ClassSystemManager.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SIMPLEAPP_API UClassSystemManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UClassSystemManager();

    // Player Class Data
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Class System")
    FPlayerPowerProgression PlayerProgression;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Class System")
    TArray<UPowerPathComponent*> AllPowerPaths;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Class System")
    TArray<UPowerPathComponent*> UnlockedPaths;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Class System")
    TArray<UPowerPathComponent*> ActivePaths;

    // Events
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClassSelected, ECoreClass, SelectedClass);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPathUnlocked, const FString&, PathName, ECoreClass, CoreClass);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPathActivated, const FString&, PathName, bool, bActivated);

    UPROPERTY(BlueprintAssignable, Category = "Class System Events")
    FOnClassSelected OnClassSelected;

    UPROPERTY(BlueprintAssignable, Category = "Class System Events")
    FOnPathUnlocked OnPathUnlocked;

    UPROPERTY(BlueprintAssignable, Category = "Class System Events")
    FOnPathActivated OnPathActivated;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Class Management
    UFUNCTION(BlueprintCallable, Category = "Class System")
    void SelectClass(ECoreClass CoreClass);

    UFUNCTION(BlueprintCallable, Category = "Class System")
    ECoreClass GetSelectedClass() const;

    UFUNCTION(BlueprintCallable, Category = "Class System")
    bool HasSelectedClass() const;

    // Path Management
    UFUNCTION(BlueprintCallable, Category = "Class System")
    bool UnlockPath(const FString& PathName);

    UFUNCTION(BlueprintCallable, Category = "Class System")
    bool ActivatePath(const FString& PathName);

    UFUNCTION(BlueprintCallable, Category = "Class System")
    bool DeactivatePath(const FString& PathName);

    UFUNCTION(BlueprintCallable, Category = "Class System")
    bool IsPathUnlocked(const FString& PathName) const;

    UFUNCTION(BlueprintCallable, Category = "Class System")
    bool IsPathActive(const FString& PathName) const;

    UFUNCTION(BlueprintCallable, Category = "Class System")
    UPowerPathComponent* GetPath(const FString& PathName) const;

    UFUNCTION(BlueprintCallable, Category = "Class System")
    TArray<UPowerPathComponent*> GetPathsForClass(ECoreClass CoreClass) const;

    UFUNCTION(BlueprintCallable, Category = "Class System")
    TArray<UPowerPathComponent*> GetAvailablePaths() const;

    // Progression
    UFUNCTION(BlueprintCallable, Category = "Class System")
    void AddPathExperience(const FString& PathName, int32 ExperienceAmount);

    UFUNCTION(BlueprintCallable, Category = "Class System")
    EPowerRank GetPathRank(const FString& PathName) const;

    UFUNCTION(BlueprintCallable, Category = "Class System")
    int32 GetTotalPowerLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Class System")
    float GetTotalPowerMultiplier() const;

    // Multi-path System
    UFUNCTION(BlueprintCallable, Category = "Class System")
    bool CanUnlockMultiPath() const;

    UFUNCTION(BlueprintCallable, Category = "Class System")
    void UnlockMultiPathAccess();

    UFUNCTION(BlueprintCallable, Category = "Class System")
    bool HasMultiPathAccess() const;

    UFUNCTION(BlueprintCallable, Category = "Class System")
    TArray<FString> GetHybridAbilities() const;

    // Acquisition System
    UFUNCTION(BlueprintCallable, Category = "Class System")
    bool CheckAcquisitionRequirements(const FPowerPathData& PathData) const;

    UFUNCTION(BlueprintCallable, Category = "Class System")
    void OnStoryEvent(const FString& EventName);

    UFUNCTION(BlueprintCallable, Category = "Class System")
    void OnGuildJoined(const FString& GuildName);

    UFUNCTION(BlueprintCallable, Category = "Class System")
    void OnQuestCompleted(const FString& QuestName);

    UFUNCTION(BlueprintCallable, Category = "Class System")
    void OnAchievementUnlocked(const FString& AchievementName);

    // Utility
    UFUNCTION(BlueprintCallable, Category = "Class System")
    TArray<FString> GetAllPathNames() const;

    UFUNCTION(BlueprintCallable, Category = "Class System")
    TArray<FString> GetActivePathNames() const;

    UFUNCTION(BlueprintCallable, Category = "Class System")
    TArray<FAbilityData> GetAllActiveAbilities() const;

    UFUNCTION(BlueprintCallable, Category = "Class System")
    bool HasAbility(const FString& AbilityName) const;

protected:
    // Internal Functions
    void InitializePowerPaths();
    void LoadPathDefinitions();
    void UpdateActivePaths();
    void CheckForAutoUnlocks();

private:
    // Internal State
    TMap<FString, FPowerPathDefinition> PathDefinitions;
    TMap<FString, UPowerPathComponent*> PathComponents;
    TArray<FString> CompletedQuests;
    TArray<FString> JoinedGuilds;
    TArray<FString> UnlockedAchievements;
    TArray<FString> TriggeredStoryEvents;

    // Helper Functions
    UPowerPathComponent* CreatePathComponent(const FString& PathName);
    void RegisterPathComponent(UPowerPathComponent* PathComponent);
    void UnregisterPathComponent(UPowerPathComponent* PathComponent);
    bool ValidatePathForClass(const FString& PathName, ECoreClass CoreClass) const;
    void UpdatePlayerProgression();
};
