#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P05_CORE_ITEMS.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemsActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemsDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnItemsLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemsMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemsPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemsPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemsAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP05_CORE_ITEMS : public UActorComponent
{
    GENERATED_BODY()

public:
    UP05_CORE_ITEMS();

    // Items Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
    int32 ItemsLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
    int32 MaxItemsLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
    bool bIsItemsActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
    float ItemsPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
    float ItemsThreshold;

    // Items Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
    float ItemCreation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
    float InventoryManagement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
    float CraftingSystem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
    float ItemRarity;

    // Items Events
    UPROPERTY(BlueprintAssignable, Category = "Items")
    FOnItemsActivated OnItemsActivated;

    UPROPERTY(BlueprintAssignable, Category = "Items")
    FOnItemsDeactivated OnItemsDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Items")
    FOnItemsLevelChanged OnItemsLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Items")
    FOnItemsMaxLevelReached OnItemsMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Items")
    FOnItemsPowerUsed OnItemsPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Items")
    FOnItemsPowerFailed OnItemsPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Items")
    FOnItemsAbilityPerformed OnItemsAbilityPerformed;

    // Items Functions
    UFUNCTION(BlueprintCallable, Category = "Items")
    void ActivateItems();

    UFUNCTION(BlueprintCallable, Category = "Items")
    void DeactivateItems();

    UFUNCTION(BlueprintCallable, Category = "Items")
    void SetItemsLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Items")
    void UseItemsPower();

    UFUNCTION(BlueprintCallable, Category = "Items")
    void PerformItemsAbility();

    UFUNCTION(BlueprintCallable, Category = "Items")
    bool IsItemsActive() const;

    UFUNCTION(BlueprintCallable, Category = "Items")
    int32 GetItemsLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Items")
    float GetItemsPowerCost() const;

    // Items Abilities
    UFUNCTION(BlueprintCallable, Category = "Items")
    void CreateItems();

    UFUNCTION(BlueprintCallable, Category = "Items")
    void AccessCraftingSystem();

    UFUNCTION(BlueprintCallable, Category = "Items")
    void ApplyItemRarity();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateItems() const;
    void UpdateItemsStats();
    void OnItemsStateChanged();
};
