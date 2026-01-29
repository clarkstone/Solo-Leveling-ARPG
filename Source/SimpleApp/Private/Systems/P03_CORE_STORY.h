#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P03_CORE_STORY.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoryActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoryDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnStoryLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStoryMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoryPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStoryPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoryAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP03_CORE_STORY : public UActorComponent
{
    GENERATED_BODY()

public:
    UP03_CORE_STORY();

    // Story Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
    int32 StoryLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
    int32 MaxStoryLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
    bool bIsStoryActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
    float StoryPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
    float StoryThreshold;

    // Story Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
    float StoryProgression;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
    float NarrativeControl;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
    float QuestGeneration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
    float DialogueSystem;

    // Story Events
    UPROPERTY(BlueprintAssignable, Category = "Story")
    FOnStoryActivated OnStoryActivated;

    UPROPERTY(BlueprintAssignable, Category = "Story")
    FOnStoryDeactivated OnStoryDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Story")
    FOnStoryLevelChanged OnStoryLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Story")
    FOnStoryMaxLevelReached OnStoryMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Story")
    FOnStoryPowerUsed OnStoryPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Story")
    FOnStoryPowerFailed OnStoryPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Story")
    FOnStoryAbilityPerformed OnStoryAbilityPerformed;

    // Story Functions
    UFUNCTION(BlueprintCallable, Category = "Story")
    void ActivateStory();

    UFUNCTION(BlueprintCallable, Category = "Story")
    void DeactivateStory();

    UFUNCTION(BlueprintCallable, Category = "Story")
    void SetStoryLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Story")
    void UseStoryPower();

    UFUNCTION(BlueprintCallable, Category = "Story")
    void PerformStoryAbility();

    UFUNCTION(BlueprintCallable, Category = "Story")
    bool IsStoryActive() const;

    UFUNCTION(BlueprintCallable, Category = "Story")
    int32 GetStoryLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Story")
    float GetStoryPowerCost() const;

    // Story Abilities
    UFUNCTION(BlueprintCallable, Category = "Story")
    void ProgressStory();

    UFUNCTION(BlueprintCallable, Category = "Story")
    void ControlNarrative();

    UFUNCTION(BlueprintCallable, Category = "Story")
    void GenerateQuests();

    UFUNCTION(BlueprintCallable, Category = "Story")
    void AccessDialogueSystem();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateStory() const;
    void UpdateStoryStats();
    void OnStoryStateChanged();
};
