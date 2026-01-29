#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P05_CORE_CHAR_MODELS.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterModelsActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterModelsDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnCharacterModelsLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterModelsMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterModelsPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterModelsPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterModelsAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP05_CORE_CHAR_MODELS : public UActorComponent
{
    GENERATED_BODY()

public:
    UP05_CORE_CHAR_MODELS();

    // Character Models Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Models")
    int32 CharacterModelsLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Models")
    int32 MaxCharacterModelsLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Models")
    bool bIsCharacterModelsActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Models")
    float CharacterModelsPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Models")
    float CharacterModelsThreshold;

    // Character Models Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Models")
    float ModelCreation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Models")
    float AnimationSystem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Models")
    float VisualEffects;

    // Character Models Events
    UPROPERTY(BlueprintAssignable, Category = "Character Models")
    FOnCharacterModelsActivated OnCharacterModelsActivated;

    UPROPERTY(BlueprintAssignable, Category = "Character Models")
    FOnCharacterModelsDeactivated OnCharacterModelsDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Character Models")
    FOnCharacterModelsLevelChanged OnCharacterModelsLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Character Models")
    FOnCharacterModelsMaxLevelReached OnCharacterModelsMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Character Models")
    FOnCharacterModelsPowerUsed OnCharacterModelsPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Character Models")
    FOnCharacterModelsPowerFailed OnCharacterModelsPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Character Models")
    FOnCharacterModelsAbilityPerformed OnCharacterModelsAbilityPerformed;

    // Character Models Functions
    UFUNCTION(BlueprintCallable, Category = "Character Models")
    void ActivateCharacterModels();

    UFUNCTION(BlueprintCallable, Category = "Character Models")
    void DeactivateCharacterModels();

    UFUNCTION(BlueprintCallable, Category = "Character Models")
    void SetCharacterModelsLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Character Models")
    void UseCharacterModelsPower();

    UFUNCTION(BlueprintCallable, Category = "Character Models")
    void PerformCharacterModelsAbility();

    UFUNCTION(BlueprintCallable, Category = "Character Models")
    bool IsCharacterModelsActive() const;

    UFUNCTION(BlueprintCallable, Category = "Character Models")
    int32 GetCharacterModelsLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Character Models")
    float GetCharacterModelsPowerCost() const;

    // Character Models Abilities
    UFUNCTION(BlueprintCallable, Category = "Character Models")
    void CreateModels();

    UFUNCTION(BlueprintCallable, Category = "Character Models")
    void AccessAnimationSystem();

    UFUNCTION(BlueprintCallable, Category = "Character Models")
    void ApplyVisualEffects();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateCharacterModels() const;
    void UpdateCharacterModelsStats();
    void OnCharacterModelsStateChanged();
};
