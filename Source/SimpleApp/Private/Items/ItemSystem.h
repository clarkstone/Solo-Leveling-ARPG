#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "ItemSystem.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    IT_Weapon,
    IT_Armor,
    IT_Consumable,
    IT_Material,
    IT_Artifact,
    IT_Quest,
    IT_System
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
    IR_Common,
    IR_Uncommon,
    IR_Rare,
    IR_Epic,
    IR_Legendary,
    IR_Mythic
};

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ItemDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemRarity ItemRarity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ItemLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ItemValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> ItemStats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString IconPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsStackable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStackSize;
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FItemData ItemData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsEmpty;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SlotIndex;
};

UCLASS()
class SIMPLEAPP_API UItemSystem : public UActorComponent
{
    GENERATED_BODY()

public:
    UItemSystem();

    // Inventory Configuration
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 MaxInventorySlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 MaxEquipmentSlots;

    // Inventory Data
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<FInventorySlot> InventorySlots;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<FInventorySlot> EquipmentSlots;

    // Item Database
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
    TMap<FString, FItemData> ItemDatabase;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Initialization
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void Initialize();

    // Inventory Management
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(FItemData ItemData, int32 Quantity);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool RemoveItem(FString ItemName, int32 Quantity);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool MoveItem(int32 FromSlot, int32 ToSlot);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    FItemData GetItemInSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetItemCount(FString ItemName);

    // Equipment Management
    UFUNCTION(BlueprintCallable, Category = "Equipment")
    bool EquipItem(int32 InventorySlot, int32 EquipmentSlot);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    bool UnequipItem(int32 EquipmentSlot);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    FItemData GetEquippedItem(int32 EquipmentSlot);

    // Item Usage
    UFUNCTION(BlueprintCallable, Category = "Items")
    bool UseItem(FString ItemName);

    UFUNCTION(BlueprintCallable, Category = "Items")
    bool UseItemInSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Items")
    void DropItem(int32 SlotIndex, int32 Quantity);

    // Crafting System
    UFUNCTION(BlueprintCallable, Category = "Crafting")
    bool CanCraftItem(FString ItemName);

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    bool CraftItem(FString ItemName, int32 Quantity);

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    TArray<FString> GetAvailableRecipes();

    // Item Enhancement
    UFUNCTION(BlueprintCallable, Category = "Enhancement")
    bool CanEnhanceItem(FItemData ItemData);

    UFUNCTION(BlueprintCallable, Category = "Enhancement")
    bool EnhanceItem(FItemData& ItemData);

    UFUNCTION(BlueprintCallable, Category = "Enhancement")
    bool CanUpgradeItem(FItemData ItemData);

    UFUNCTION(BlueprintCallable, Category = "Enhancement")
    bool UpgradeItem(FItemData& ItemData);

    // Power System Items
    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    bool AddPowerSystemItem(FString PowerSystemName, FItemData ItemData);

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void UsePowerSystemItem(FString PowerSystemName, FString ItemName);

    // Quest Items
    UFUNCTION(BlueprintCallable, Category = "Quests")
    bool AddQuestItem(FString QuestID, FItemData ItemData);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    bool HasQuestItem(FString QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    void CompleteQuestItem(FString QuestID);

    // Item Information
    UFUNCTION(BlueprintCallable, Category = "Items")
    FItemData GetItemData(FString ItemName);

    UFUNCTION(BlueprintCallable, Category = "Items")
    TArray<FString> GetItemStats(FString ItemName);

    UFUNCTION(BlueprintCallable, Category = "Items")
    FLinearColor GetRarityColor(EItemRarity Rarity);

    // Inventory Events
    UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
    FOnItemAdded OnItemAdded;

    UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
    FOnItemRemoved OnItemRemoved;

    UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
    FOnItemEquipped OnItemEquipped;

    UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
    FOnItemUsed OnItemUsed;

protected:
    // Internal Inventory Systems
    void InitializeInventory();
    void InitializeEquipment();
    void LoadItemDatabase();

    // Item Management
    void UpdateInventory();
    void UpdateEquipment();
    void ProcessItemEffects();

private:
    // Internal State
    int32 CurrentInventorySize;
    int32 CurrentEquipmentSize;
    bool bInventoryFull;

    // Item Management
    TMap<FString, int32> ItemQuantities;
    TMap<EItemType, TArray<FItemData>> ItemsByType;

    // Helper Functions
    void InitializeItemDatabase();
    void UpdateItemStats();
    void ProcessItemUse(FItemData ItemData);
};
