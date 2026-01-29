#include "P02_CORE_ITEMS.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP02_CORE_ITEMS::UP02_CORE_ITEMS()
{
    PrimaryComponentTick.bCanEverTick = false;
    ItemsLevel = 0;
    MaxItemsLevel = 100;
    bIsItemsActive = false;
    ItemsPowerCost = 10.0f;
    ItemsThreshold = 10.0f;
    
    // Initialize items properties
    ItemCreation = 0.0f;
    InventoryManagement = 0.0f;
    CraftingSystem = 0.0f;
    ItemRarity = 0.0f;
}

void UP02_CORE_ITEMS::BeginPlay()
{
    Super::BeginPlay();
    UpdateItemsStats();
}

void UP02_CORE_ITEMS::ActivateItems()
{
    if (!bIsItemsActive && CanActivateItems())
    {
        bIsItemsActive = true;
        OnItemsActivated.Broadcast(ItemsLevel);
        OnItemsStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Items System Activated at Level: %d"), ItemsLevel);
    }
}

void UP02_CORE_ITEMS::DeactivateItems()
{
    if (bIsItemsActive)
    {
        bIsItemsActive = false;
        OnItemsDeactivated.Broadcast(ItemsLevel);
        OnItemsStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Items System Deactivated."));
    }
}

void UP02_CORE_ITEMS::SetItemsLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxItemsLevel)
    {
        int32 OldLevel = ItemsLevel;
        ItemsLevel = NewLevel;
        UpdateItemsStats();
        OnItemsLevelChanged.Broadcast(OldLevel, ItemsLevel);
        UE_LOG(LogTemp, Warning, TEXT("Items Level set to: %d"), ItemsLevel);
        
        if (ItemsLevel >= MaxItemsLevel)
        {
            OnItemsMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Items Max Level Reached!"));
        }
    }
}

void UP02_CORE_ITEMS::UseItemsPower()
{
    if (bIsItemsActive && ItemsLevel > 0)
    {
        OnItemsPowerUsed.Broadcast(ItemsPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Items Power Used: %.2f"), ItemsPowerCost);
    }
    else
    {
        OnItemsPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Items Power Use Failed: System not active or insufficient level."));
    }
}

void UP02_CORE_ITEMS::PerformItemsAbility()
{
    if (bIsItemsActive && ItemsLevel >= ItemsThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Items Ability at Level %d!"), ItemsLevel);
        OnItemsAbilityPerformed.Broadcast(ItemsLevel);
        UseItemsPower();
        
        // Perform items ability based on level
        switch (ItemsLevel / 20)
        {
            case 0:
                CreateItems();
                break;
            case 1:
                AccessCraftingSystem();
                break;
            case 2:
                ApplyItemRarity();
                break;
            default:
                ApplyItemRarity();
                break;
        }
    }
    }
    else if (ItemsLevel < ItemsThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Items Level too low to perform ability. Required: %.0f, Current: %d"), ItemsThreshold, ItemsLevel);
    }
    else
    {
        UE_LOG(LogTemp, TEXT("Items is not active, cannot perform ability."));
    }
}

bool UP02_CORE_ITEMS::IsItemsActive() const
{
    return bIsItemsActive;
}

int32 UP02_CORE_ITEMS::GetItemsLevel() const
{
    return ItemsLevel;
}

float UP02_CORE_ITEMS::GetItemsPowerCost() const
{
    return ItemsPowerCost;
}

void UP02_CORE_ITEMS::CreateItems()
{
    if (bIsItemsActive)
    {
        float CreationPower = ItemCreation * (ItemsLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Creating Items with power: %.2f"), CreationPower);
        // Apply item creation effects
    }
}

void UP02_CORE_ITEMS::AccessCraftingSystem()
{
    if (bIsItemsActive)
    {
        float CraftingPower = CraftingSystem * (ItemsLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Crafting System with power: %.2f"), CraftingPower);
        // Apply crafting system effects
    }
}

void UP02_CORE_ITEMS::ApplyItemRarity()
{
    if (bIsItemsActive)
    {
        float RarityPower = ItemRarity * (ItemsLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Applying Item Rarity with power: %.2f"), RarityPower);
        // Apply item rarity effects
    }
}

bool UP02_CORE_ITEMS::CanActivateItems() const
{
    return ItemsLevel > 0;
}

void UP02_CORE_ITEMS::UpdateItemsStats()
{
    // Update items properties based on level
    ItemCreation = ItemsLevel * 1.8f;
    InventoryManagement = ItemsLevel * 1.5f;
    CraftingSystem = ItemsLevel * 1.2f;
    ItemRarity = ItemsLevel * 1.7f;
}

void UP02_CORE_ITEMS::OnItemsStateChanged()
{
    // Handle state change effects
    if (bIsItemsActive)
    {
        // Apply items activation effects
        UE_LOG(LogTemp, Warning, TEXT("Items state changed to ACTIVE"));
    }
    else
    {
        // Remove items effects
        UE_LOG(LogTemp, Warning, TEXT("Items state changed to INACTIVE"));
    }
}
