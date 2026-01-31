#include "ItemSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UItemSystem::UItemSystem()
{
    MaxInventorySlots = 30;
    MaxEquipmentSlots = 10;
    CurrentInventorySize = 0;
    CurrentEquipmentSize = 0;
    bInventoryFull = false;
}

void UItemSystem::BeginPlay()
{
    Super::BeginPlay();
    Initialize();
}

void UItemSystem::Initialize()
{
    InitializeInventory();
    InitializeEquipment();
    LoadItemDatabase();
    
    UE_LOG(LogTemp, Warning, TEXT("Item System initialized"));
}

void UItemSystem::InitializeInventory()
{
    // Initialize inventory slots
    InventorySlots.SetNum(MaxInventorySlots);
    
    for (int32 i = 0; i < MaxInventorySlots; i++)
    {
        FInventorySlot Slot;
        Slot.SlotIndex = i;
        Slot.Quantity = 0;
        Slot.bIsEmpty = true;
        InventorySlots[i] = Slot;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Inventory initialized with %d slots"), MaxInventorySlots);
}

void UItemSystem::InitializeEquipment()
{
    // Initialize equipment slots
    EquipmentSlots.SetNum(MaxEquipmentSlots);
    
    for (int32 i = 0; i < MaxEquipmentSlots; i++)
    {
        FInventorySlot Slot;
        Slot.SlotIndex = i;
        Slot.Quantity = 1;
        Slot.bIsEmpty = true;
        EquipmentSlots[i] = Slot;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Equipment initialized with %d slots"), MaxEquipmentSlots);
}

void UItemSystem::LoadItemDatabase()
{
    // Load basic items
    FItemData HealthPotion;
    HealthPotion.ItemName = TEXT("Health Potion");
    HealthPotion.ItemDescription = TEXT("Restores 50 health points");
    HealthPotion.ItemType = EItemType::IT_Consumable;
    HealthPotion.ItemRarity = EItemRarity::IR_Common;
    HealthPotion.ItemLevel = 1;
    HealthPotion.ItemValue = 50.0f;
    HealthPotion.bIsStackable = true;
    HealthPotion.MaxStackSize = 99;
    ItemDatabase.Add(TEXT("Health Potion"), HealthPotion);
    
    FItemData ManaPotion;
    ManaPotion.ItemName = TEXT("Mana Potion");
    ManaPotion.ItemDescription = TEXT("Restores 50 power points");
    ManaPotion.ItemType = EItemType::IT_Consumable;
    ManaPotion.ItemRarity = EItemRarity::IR_Common;
    ManaPotion.ItemLevel = 1;
    ManaPotion.ItemValue = 50.0f;
    ManaPotion.bIsStackable = true;
    ManaPotion.MaxStackSize = 99;
    ItemDatabase.Add(TEXT("Mana Potion"), ManaPotion);
    
    // Add basic weapon
    FItemData BasicSword;
    BasicSword.ItemName = TEXT("Basic Sword");
    BasicSword.ItemDescription = TEXT("A simple but effective sword");
    BasicSword.ItemType = EItemType::IT_Weapon;
    BasicSword.ItemRarity = EItemRarity::IR_Common;
    BasicSword.ItemLevel = 1;
    BasicSword.ItemValue = 100.0f;
    BasicSword.bIsStackable = false;
    BasicSword.MaxStackSize = 1;
    ItemDatabase.Add(TEXT("Basic Sword"), BasicSword);
    
    UE_LOG(LogTemp, Warning, TEXT("Item database loaded"));
}

bool UItemSystem::AddItem(FItemData ItemData, int32 Quantity)
{
    // Check if item exists in database
    if (!ItemDatabase.Contains(ItemData.ItemName))
    {
        ItemDatabase.Add(ItemData.ItemName, ItemData);
    }
    
    // Find empty slot or stackable slot
    for (int32 i = 0; i < InventorySlots.Num(); i++)
    {
        FInventorySlot& Slot = InventorySlots[i];
        
        if (Slot.bIsEmpty)
        {
            // Add to empty slot
            Slot.ItemData = ItemData;
            Slot.Quantity = Quantity;
            Slot.bIsEmpty = false;
            
            OnItemAdded.Broadcast(ItemData, Quantity);
            UE_LOG(LogTemp, Warning, TEXT("Item added: %s x%d"), *ItemData.ItemName, Quantity);
            return true;
        }
        else if (Slot.ItemData.ItemName == ItemData.ItemName && ItemData.bIsStackable)
        {
            // Add to existing stack
            int32 MaxStack = ItemData.MaxStackSize;
            if (Slot.Quantity + Quantity <= MaxStack)
            {
                Slot.Quantity += Quantity;
                OnItemAdded.Broadcast(ItemData, Quantity);
                UE_LOG(LogTemp, Warning, TEXT("Item stacked: %s x%d"), *ItemData.ItemName, Slot.Quantity);
                return true;
            }
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Inventory full, cannot add item: %s"), *ItemData.ItemName);
    return false;
}

bool UItemSystem::RemoveItem(FString ItemName, int32 Quantity)
{
    for (int32 i = 0; i < InventorySlots.Num(); i++)
    {
        FInventorySlot& Slot = InventorySlots[i];
        
        if (!Slot.bIsEmpty && Slot.ItemData.ItemName == ItemName)
        {
            if (Slot.Quantity >= Quantity)
            {
                Slot.Quantity -= Quantity;
                
                if (Slot.Quantity <= 0)
                {
                    Slot.bIsEmpty = true;
                    Slot.ItemData = FItemData();
                }
                
                OnItemRemoved.Broadcast(ItemName, Quantity);
                UE_LOG(LogTemp, Warning, TEXT("Item removed: %s x%d"), *ItemName, Quantity);
                return true;
            }
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Cannot remove item: %s x%d"), *ItemName, Quantity);
    return false;
}

bool UItemSystem::UseItem(FString ItemName)
{
    if (ItemDatabase.Contains(ItemName))
    {
        FItemData ItemData = ItemDatabase[ItemName];
        
        if (ItemData.ItemType == EItemType::IT_Consumable)
        {
            // Apply consumable effects
            if (ItemName == TEXT("Health Potion"))
            {
                // Restore health
                UE_LOG(LogTemp, Warning, TEXT("Health potion used"));
            }
            else if (ItemName == TEXT("Mana Potion"))
            {
                // Restore power
                UE_LOG(LogTemp, Warning, TEXT("Mana potion used"));
            }
            
            // Remove one from inventory
            RemoveItem(ItemName, 1);
            
            OnItemUsed.Broadcast(ItemData);
            return true;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Cannot use item: %s"), *ItemName);
    return false;
}

bool UItemSystem::EquipItem(int32 InventorySlot, int32 EquipmentSlot)
{
    if (InventorySlot >= 0 && InventorySlot < InventorySlots.Num() &&
        EquipmentSlot >= 0 && EquipmentSlot < EquipmentSlots.Num())
    {
        FInventorySlot& InvSlot = InventorySlots[InventorySlot];
        FInventorySlot& EquipSlot = EquipmentSlots[EquipmentSlot];
        
        if (!InvSlot.bIsEmpty && EquipSlot.bIsEmpty)
        {
            // Move item to equipment slot
            EquipSlot.ItemData = InvSlot.ItemData;
            EquipSlot.Quantity = 1;
            EquipSlot.bIsEmpty = false;
            
            // Clear inventory slot
            InvSlot.bIsEmpty = true;
            InvSlot.ItemData = FItemData();
            InvSlot.Quantity = 0;
            
            OnItemEquipped.Broadcast(EquipSlot.ItemData, EquipmentSlot);
            UE_LOG(LogTemp, Warning, TEXT("Item equipped: %s"), *EquipSlot.ItemData.ItemName);
            return true;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Cannot equip item"));
    return false;
}

bool UItemSystem::UnequipItem(int32 EquipmentSlot)
{
    if (EquipmentSlot >= 0 && EquipmentSlot < EquipmentSlots.Num())
    {
        FInventorySlot& EquipSlot = EquipmentSlots[EquipmentSlot];
        
        if (!EquipSlot.bIsEmpty)
        {
            // Find empty inventory slot
            for (int32 i = 0; i < InventorySlots.Num(); i++)
            {
                FInventorySlot& InvSlot = InventorySlots[i];
                
                if (InvSlot.bIsEmpty)
                {
                    // Move item back to inventory
                    InvSlot.ItemData = EquipSlot.ItemData;
                    InvSlot.Quantity = 1;
                    InvSlot.bIsEmpty = false;
                    
                    // Clear equipment slot
                    EquipSlot.bIsEmpty = true;
                    EquipSlot.ItemData = FItemData();
                    EquipSlot.Quantity = 0;
                    
                    UE_LOG(LogTemp, Warning, TEXT("Item unequipped: %s"), *InvSlot.ItemData.ItemName);
                    return true;
                }
            }
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Cannot unequip item"));
    return false;
}

FItemData UItemSystem::GetItemInSlot(int32 SlotIndex)
{
    if (SlotIndex >= 0 && SlotIndex < InventorySlots.Num())
    {
        return InventorySlots[SlotIndex].ItemData;
    }
    
    return FItemData();
}

int32 UItemSystem::GetItemCount(FString ItemName)
{
    int32 Count = 0;
    
    for (const FInventorySlot& Slot : InventorySlots)
    {
        if (!Slot.bIsEmpty && Slot.ItemData.ItemName == ItemName)
        {
            Count += Slot.Quantity;
        }
    }
    
    return Count;
}

FItemData UItemSystem::GetItemData(FString ItemName)
{
    if (ItemDatabase.Contains(ItemName))
    {
        return ItemDatabase[ItemName];
    }
    
    return FItemData();
}

FLinearColor UItemSystem::GetRarityColor(EItemRarity Rarity)
{
    switch (Rarity)
    {
        case EItemRarity::IR_Common:
            return FLinearColor::White;
        case EItemRarity::IR_Uncommon:
            return FLinearColor::Green;
        case EItemRarity::IR_Rare:
            return FLinearColor::Blue;
        case EItemRarity::IR_Epic:
            return FLinearColor::Purple;
        case EItemRarity::IR_Legendary:
            return FLinearColor::Orange;
        case EItemRarity::IR_Mythic:
            return FLinearColor::Red;
        default:
            return FLinearColor::White;
    }
}
