#include "TransmogrificationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Animation/SkeletalMeshActor.h"
#include "Net/UnrealNetwork.h"

UTransmogrificationSystem::UTransmogrificationSystem()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);
    
    bPreviewActive = false;
    
    // Initialize slot visibility (all visible by default)
    for (int32 i = 0; i < (int32)EEquipmentSlot::ES_MAX; i++)
    {
        SlotVisibility.Add(static_cast<EEquipmentSlot>(i), true);
    }
}

void UTransmogrificationSystem::BeginPlay()
{
    Super::BeginPlay();
    InitializeTransmogrification();
}

void UTransmogrificationSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTransmogrificationSystem::InitializeTransmogrification()
{
    UE_LOG(LogTemp, Warning, TEXT("Transmogrification System initialized"));
    
    // Initialize all transmog systems
    InitializeAppearances();
    InitializeDyes();
    InitializeTransmogSets();
    
    // Load saved transmogrification
    LoadTransmogrification();
    
    UE_LOG(LogTemp, Warning, TEXT("Transmogrification System ready"));
}

bool UTransmogrificationSystem::ApplyTransmog(const FString& ItemID, const FString& AppearanceName)
{
    if (!ValidateTransmog(ItemID, AppearanceName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid transmog: %s -> %s"), *ItemID, *AppearanceName);
        return false;
    }
    
    FTransmogAppearance Appearance = GetAppearance(AppearanceName);
    if (Appearance.ItemName.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("Appearance not found: %s"), *AppearanceName);
        return false;
    }
    
    FEquipmentTransmog EquipmentTransmog;
    EquipmentTransmog.OriginalItemID = ItemID;
    EquipmentTransmog.TransmogAppearance = Appearance;
    EquipmentTransmog.bHasTransmog = true;
    EquipmentTransmog.Slot = GetItemSlot(ItemID);
    EquipmentTransmog.bHideSlot = false;
    
    EquipmentTransmogs.Add(ItemID, EquipmentTransmog);
    
    ApplyAppearanceToCharacter(ItemID);
    NotifyTransmogApplied(EquipmentTransmog);
    
    UE_LOG(LogTemp, Warning, TEXT("Transmog applied: %s -> %s"), *ItemID, *AppearanceName);
    return true;
}

bool UTransmogrificationSystem::RemoveTransmog(const FString& ItemID)
{
    if (!EquipmentTransmogs.Contains(ItemID))
    {
        UE_LOG(LogTemp, Warning, TEXT("No transmog found for item: %s"), *ItemID);
        return false;
    }
    
    EEquipmentSlot Slot = EquipmentTransmogs[ItemID].Slot;
    EquipmentTransmogs.Remove(ItemID);
    
    ApplyAppearanceToCharacter(ItemID);
    NotifyTransmogRemoved(Slot);
    
    UE_LOG(LogTemp, Warning, TEXT("Transmog removed from item: %s"), *ItemID);
    return true;
}

bool UTransmogrificationSystem::HasTransmog(const FString& ItemID) const
{
    return EquipmentTransmogs.Contains(ItemID);
}

FEquipmentTransmog UTransmogrificationSystem::GetEquipmentTransmog(const FString& ItemID) const
{
    if (EquipmentTransmogs.Contains(ItemID))
    {
        return EquipmentTransmogs[ItemID];
    }
    
    FEquipmentTransmog EmptyTransmog;
    return EmptyTransmog;
}

TArray<FEquipmentTransmog> UTransmogrificationSystem::GetAllTransmogs() const
{
    TArray<FEquipmentTransmog> AllTransmogs;
    
    for (const auto& TransmogPair : EquipmentTransmogs)
    {
        AllTransmogs.Add(TransmogPair.Value);
    }
    
    return AllTransmogs;
}

TArray<FTransmogAppearance> UTransmogrificationSystem::GetAvailableAppearances(EEquipmentSlot Slot) const
{
    TArray<FTransmogAppearance> SlotAppearances;
    
    for (const FTransmogAppearance& Appearance : AvailableAppearances)
    {
        if (Appearance.EquipmentSlot == Slot)
        {
            SlotAppearances.Add(Appearance);
        }
    }
    
    return SlotAppearances;
}

TArray<FTransmogAppearance> UTransmogrificationSystem::GetUnlockedAppearances(EEquipmentSlot Slot) const
{
    TArray<FTransmogAppearance> UnlockedAppearances;
    
    for (const FTransmogAppearance& Appearance : AvailableAppearances)
    {
        if (Appearance.EquipmentSlot == Slot && Appearance.bIsUnlocked)
        {
            UnlockedAppearances.Add(Appearance);
        }
    }
    
    return UnlockedAppearances;
}

bool UTransmogrificationSystem::UnlockAppearance(const FString& AppearanceName)
{
    for (FTransmogAppearance& Appearance : AvailableAppearances)
    {
        if (Appearance.ItemName == AppearanceName && !Appearance.bIsUnlocked)
        {
            Appearance.bIsUnlocked = true;
            NotifyAppearanceUnlocked(Appearance);
            UE_LOG(LogTemp, Warning, TEXT("Appearance unlocked: %s"), *AppearanceName);
            return true;
        }
    }
    
    return false;
}

bool UTransmogrificationSystem::IsAppearanceUnlocked(const FString& AppearanceName) const
{
    for (const FTransmogAppearance& Appearance : AvailableAppearances)
    {
        if (Appearance.ItemName == AppearanceName)
        {
            return Appearance.bIsUnlocked;
        }
    }
    
    return false;
}

FTransmogAppearance UTransmogrificationSystem::GetAppearance(const FString& AppearanceName) const
{
    for (const FTransmogAppearance& Appearance : AvailableAppearances)
    {
        if (Appearance.ItemName == AppearanceName)
        {
            return Appearance;
        }
    }
    
    FTransmogAppearance EmptyAppearance;
    return EmptyAppearance;
}

TArray<FTransmogSet> UTransmogrificationSystem::GetAvailableSets() const
{
    return AvailableSets;
}

TArray<FTransmogSet> UTransmogrificationSystem::GetUnlockedSets() const
{
    TArray<FTransmogSet> UnlockedSets;
    
    for (const FTransmogSet& Set : AvailableSets)
    {
        if (Set.bIsUnlocked)
        {
            UnlockedSets.Add(Set);
        }
    }
    
    return UnlockedSets;
}

bool UTransmogrificationSystem::UnlockTransmogSet(const FString& SetName)
{
    for (FTransmogSet& Set : AvailableSets)
    {
        if (Set.SetName == SetName && !Set.bIsUnlocked)
        {
            Set.bIsUnlocked = true;
            NotifySetUnlocked(Set);
            UE_LOG(LogTemp, Warning, TEXT("Transmog set unlocked: %s"), *SetName);
            return true;
        }
    }
    
    return false;
}

bool UTransmogrificationSystem::IsSetUnlocked(const FString& SetName) const
{
    for (const FTransmogSet& Set : AvailableSets)
    {
        if (Set.SetName == SetName)
        {
            return Set.bIsUnlocked;
        }
    }
    
    return false;
}

FTransmogSet UTransmogrificationSystem::GetTransmogSet(const FString& SetName) const
{
    for (const FTransmogSet& Set : AvailableSets)
    {
        if (Set.SetName == SetName)
        {
            return Set;
        }
    }
    
    FTransmogSet EmptySet;
    return EmptySet;
}

bool UTransmogrificationSystem::ApplyTransmogSet(const FString& SetName)
{
    FTransmogSet Set = GetTransmogSet(SetName);
    if (Set.SetName.IsEmpty() || !Set.bIsUnlocked)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot apply transmog set: %s"), *SetName);
        return false;
    }
    
    // Apply all pieces in the set
    for (const auto& PiecePair : Set.SetPieces)
    {
        EEquipmentSlot Slot = PiecePair.Key;
        const FTransmogAppearance& Appearance = PiecePair.Value;
        
        // Find an item in this slot to apply the transmog to
        TArray<FString> SlotItems = GetTransmoggableItems();
        for (const FString& ItemID : SlotItems)
        {
            if (GetItemSlot(ItemID) == Slot)
            {
                ApplyTransmog(ItemID, Appearance.ItemName);
                break;
            }
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Transmog set applied: %s"), *SetName);
    return true;
}

TArray<FDyeColor> UTransmogrificationSystem::GetAvailableDyes() const
{
    return AvailableDyes;
}

TArray<FDyeColor> UTransmogrificationSystem::GetUnlockedDyes() const
{
    TArray<FDyeColor> UnlockedDyes;
    
    for (const FDyeColor& Dye : AvailableDyes)
    {
        if (Dye.bIsUnlocked)
        {
            UnlockedDyes.Add(Dye);
        }
    }
    
    return UnlockedDyes;
}

bool UTransmogrificationSystem::UnlockDye(const FString& DyeName)
{
    for (FDyeColor& Dye : AvailableDyes)
    {
        if (Dye.ColorName == DyeName && !Dye.bIsUnlocked)
        {
            Dye.bIsUnlocked = true;
            UE_LOG(LogTemp, Warning, TEXT("Dye unlocked: %s"), *DyeName);
            return true;
        }
    }
    
    return false;
}

bool UTransmogrificationSystem::IsDyeUnlocked(const FString& DyeName) const
{
    for (const FDyeColor& Dye : AvailableDyes)
    {
        if (Dye.ColorName == DyeName)
        {
            return Dye.bIsUnlocked;
        }
    }
    
    return false;
}

bool UTransmogrificationSystem::ApplyDye(const FString& ItemID, const FString& DyeName, int32 DyeChannel)
{
    if (!EquipmentTransmogs.Contains(ItemID))
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot dye item without transmog: %s"), *ItemID);
        return false;
    }
    
    FDyeColor Dye;
    bool bDyeFound = false;
    for (const FDyeColor& AvailableDye : AvailableDyes)
    {
        if (AvailableDye.ColorName == DyeName && AvailableDye.bIsUnlocked)
        {
            Dye = AvailableDye;
            bDyeFound = true;
            break;
        }
    }
    
    if (!bDyeFound)
    {
        UE_LOG(LogTemp, Warning, TEXT("Dye not found or locked: %s"), *DyeName);
        return false;
    }
    
    FEquipmentTransmog& EquipmentTransmog = EquipmentTransmogs[ItemID];
    
    // Ensure dye array is large enough
    while (EquipmentTransmog.AppliedDyes.Num() <= DyeChannel)
    {
        EquipmentTransmog.AppliedDyes.Add(FLinearColor::White);
    }
    
    EquipmentTransmog.AppliedDyes[DyeChannel] = Dye.Color;
    
    ApplyAppearanceToCharacter(ItemID);
    NotifyDyeApplied(ItemID);
    
    UE_LOG(LogTemp, Warning, TEXT("Dye applied: %s to item %s channel %d"), *DyeName, *ItemID, DyeChannel);
    return true;
}

bool UTransmogrificationSystem::RemoveDye(const FString& ItemID, int32 DyeChannel)
{
    if (!EquipmentTransmogs.Contains(ItemID))
    {
        return false;
    }
    
    FEquipmentTransmog& EquipmentTransmog = EquipmentTransmogs[ItemID];
    
    if (DyeChannel >= 0 && DyeChannel < EquipmentTransmog.AppliedDyes.Num())
    {
        EquipmentTransmog.AppliedDyes[DyeChannel] = FLinearColor::White;
        
        ApplyAppearanceToCharacter(ItemID);
        NotifyDyeApplied(ItemID);
        
        UE_LOG(LogTemp, Warning, TEXT("Dye removed from item %s channel %d"), *ItemID, DyeChannel);
        return true;
    }
    
    return false;
}

TArray<FLinearColor> UTransmogrificationSystem::GetAppliedDyes(const FString& ItemID) const
{
    if (EquipmentTransmogs.Contains(ItemID))
    {
        return EquipmentTransmogs[ItemID].AppliedDyes;
    }
    
    return TArray<FLinearColor>();
}

bool UTransmogrificationSystem::SetSlotVisibility(EEquipmentSlot Slot, bool bVisible)
{
    if (SlotVisibility.Contains(Slot))
    {
        SlotVisibility[Slot] = bVisible;
        UpdateSlotVisibility(Slot);
        UE_LOG(LogTemp, Warning, TEXT("Slot visibility changed: %d to %s"), (int32)Slot, bVisible ? TEXT("visible") : TEXT("hidden"));
        return true;
    }
    
    return false;
}

bool UTransmogrificationSystem::IsSlotVisible(EEquipmentSlot Slot) const
{
    if (SlotVisibility.Contains(Slot))
    {
        return SlotVisibility[Slot];
    }
    
    return true;
}

void UTransmogrificationSystem::ToggleHelmetVisibility()
{
    bool bCurrentVisibility = IsSlotVisible(EEquipmentSlot::ES_Head);
    SetSlotVisibility(EEquipmentSlot::ES_Head, !bCurrentVisibility);
}

void UTransmogrificationSystem::ToggleShoulderVisibility()
{
    bool bCurrentVisibility = IsSlotVisible(EEquipmentSlot::ES_Shoulders);
    SetSlotVisibility(EEquipmentSlot::ES_Shoulders, !bCurrentVisibility);
}

void UTransmogrificationSystem::ToggleCloakVisibility()
{
    bool bCurrentVisibility = IsSlotVisible(EEquipmentSlot::ES_Back);
    SetSlotVisibility(EEquipmentSlot::ES_Back, !bCurrentVisibility);
}

bool UTransmogrificationSystem::PreviewTransmog(const FString& ItemID, const FString& AppearanceName)
{
    if (!ValidateTransmog(ItemID, AppearanceName))
    {
        return false;
    }
    
    bPreviewActive = true;
    PreviewItemID = ItemID;
    PreviewAppearance = GetAppearance(AppearanceName);
    
    // Apply preview appearance
    ApplyAppearanceToCharacter(ItemID);
    
    UE_LOG(LogTemp, Warning, TEXT("Transmog preview: %s -> %s"), *ItemID, *AppearanceName);
    return true;
}

void UTransmogrificationSystem::ClearPreview()
{
    if (bPreviewActive)
    {
        bPreviewActive = false;
        PreviewItemID = TEXT("");
        
        // Restore original appearance
        UpdateCharacterAppearance();
        
        UE_LOG(LogTemp, Warning, TEXT("Transmog preview cleared"));
    }
}

bool UTransmogrificationSystem::IsPreviewActive() const
{
    return bPreviewActive;
}

void UTransmogrificationSystem::SaveTransmogrification()
{
    // Save transmogrification data
    UE_LOG(LogTemp, Warning, TEXT("Transmogrification saved"));
}

void UTransmogrificationSystem::LoadTransmogrification()
{
    // Load transmogrification data
    UE_LOG(LogTemp, Warning, TEXT("Transmogrification loaded"));
}

void UTransmogrificationSystem::ResetTransmogrification()
{
    EquipmentTransmogs.Empty();
    bPreviewActive = false;
    PreviewItemID = TEXT("");
    
    // Reset slot visibility
    for (int32 i = 0; i < (int32)EEquipmentSlot::ES_MAX; i++)
    {
        SlotVisibility[static_cast<EEquipmentSlot>(i)] = true;
    }
    
    UpdateCharacterAppearance();
    
    UE_LOG(LogTemp, Warning, TEXT("Transmogrification reset"));
}

bool UTransmogrificationSystem::CanTransmogItem(const FString& ItemID) const
{
    // Check if item can be transmogrified
    // This would typically check item type, rarity, etc.
    return true; // For now, all items can be transmogrified
}

EEquipmentSlot UTransmogrificationSystem::GetItemSlot(const FString& ItemID) const
{
    // Determine equipment slot based on item ID
    // This would typically query the item system
    if (ItemID.Contains(TEXT("Helmet")))
    {
        return EEquipmentSlot::ES_Head;
    }
    else if (ItemID.Contains(TEXT("Chest")))
    {
        return EEquipmentSlot::ES_Chest;
    }
    else if (ItemID.Contains(TEXT("Sword")))
    {
        return EEquipmentSlot::ES_MainHand;
    }
    else if (ItemID.Contains(TEXT("Shield")))
    {
        return EEquipmentSlot::ES_OffHand;
    }
    
    return EEquipmentSlot::ES_MAX;
}

TArray<FString> UTransmogrificationSystem::GetTransmoggableItems() const
{
    // Get all items that can be transmogrified
    // This would typically query the inventory system
    TArray<FString> TransmoggableItems;
    
    // Sample items for demonstration
    TransmoggableItems.Add(TEXT("IronHelmet"));
    TransmoggableItems.Add(TEXT("LeatherChest"));
    TransmoggableItems.Add(TEXT("SteelSword"));
    TransmoggableItems.Add(TEXT("WoodenShield"));
    
    return TransmoggableItems;
}

void UTransmogrificationSystem::UpdateCharacterAppearance()
{
    // Update all equipped items with their transmog appearances
    TArray<FString> EquippedItems = GetTransmoggableItems();
    
    for (const FString& ItemID : EquippedItems)
    {
        ApplyAppearanceToCharacter(ItemID);
    }
}

void UTransmogrificationSystem::InitializeAppearances()
{
    AvailableAppearances.Empty();
    
    // Create default appearances for each slot
    AvailableAppearances.Add(CreateAppearance(TEXT("Iron Helmet"), EEquipmentSlot::ES_Head));
    AvailableAppearances.Add(CreateAppearance(TEXT("Steel Helmet"), EEquipmentSlot::ES_Head));
    AvailableAppearances.Add(CreateAppearance(TEXT("Golden Helmet"), EEquipmentSlot::ES_Head));
    
    AvailableAppearances.Add(CreateAppearance(TEXT("Leather Chest"), EEquipmentSlot::ES_Chest));
    AvailableAppearances.Add(CreateAppearance(TEXT("Chain Mail"), EEquipmentSlot::ES_Chest));
    AvailableAppearances.Add(CreateAppearance(TEXT("Plate Armor"), EEquipmentSlot::ES_Chest));
    
    AvailableAppearances.Add(CreateAppearance(TEXT("Steel Sword"), EEquipmentSlot::ES_MainHand));
    AvailableAppearances.Add(CreateAppearance(TEXT("Fire Sword"), EEquipmentSlot::ES_MainHand));
    AvailableAppearances.Add(CreateAppearance(TEXT("Ice Sword"), EEquipmentSlot::ES_MainHand));
    
    AvailableAppearances.Add(CreateAppearance(TEXT("Wooden Shield"), EEquipmentSlot::ES_OffHand));
    AvailableAppearances.Add(CreateAppearance(TEXT("Steel Shield"), EEquipmentSlot::ES_OffHand));
    AvailableAppearances.Add(CreateAppearance(TEXT("Tower Shield"), EEquipmentSlot::ES_OffHand));
    
    // Unlock some appearances by default
    for (int32 i = 0; i < AvailableAppearances.Num() && i < 6; i++)
    {
        AvailableAppearances[i].bIsUnlocked = true;
    }
}

void UTransmogrificationSystem::InitializeDyes()
{
    AvailableDyes.Empty();
    
    // Create basic dye colors
    AvailableDyes.Add(CreateDye(TEXT("Red"), FLinearColor::Red));
    AvailableDyes.Add(CreateDye(TEXT("Blue"), FLinearColor::Blue));
    AvailableDyes.Add(CreateDye(TEXT("Green"), FLinearColor::Green));
    AvailableDyes.Add(CreateDye(TEXT("Yellow"), FLinearColor::Yellow));
    AvailableDyes.Add(CreateDye(TEXT("Purple"), FLinearColor::Purple));
    AvailableDyes.Add(CreateDye(TEXT("Orange"), FLinearColor(1.0f, 0.5f, 0.0f, 1.0f)));
    AvailableDyes.Add(CreateDye(TEXT("Black"), FLinearColor::Black));
    AvailableDyes.Add(CreateDye(TEXT("White"), FLinearColor::White));
    AvailableDyes.Add(CreateDye(TEXT("Gold"), FLinearColor(1.0f, 0.843f, 0.0f, 1.0f)));
    AvailableDyes.Add(CreateDye(TEXT("Silver"), FLinearColor(0.753f, 0.753f, 0.753f, 1.0f)));
    
    // Unlock some dyes by default
    for (int32 i = 0; i < AvailableDyes.Num() && i < 5; i++)
    {
        AvailableDyes[i].bIsUnlocked = true;
    }
}

void UTransmogrificationSystem::InitializeTransmogSets()
{
    AvailableSets.Empty();
    
    // Create transmog sets
    FTransmogSet IronSet = CreateTransmogSet(TEXT("Iron Set"));
    IronSet.SetPieces.Add(EEquipmentSlot::ES_Head, CreateAppearance(TEXT("Iron Helmet"), EEquipmentSlot::ES_Head));
    IronSet.SetPieces.Add(EEquipmentSlot::ES_Chest, CreateAppearance(TEXT("Iron Chest"), EEquipmentSlot::ES_Chest));
    IronSet.SetPieces.Add(EEquipmentSlot::ES_Legs, CreateAppearance(TEXT("Iron Legs"), EEquipmentSlot::ES_Legs));
    IronSet.PiecesRequired = 3;
    IronSet.bIsUnlocked = true;
    
    FTransmogSet SteelSet = CreateTransmogSet(TEXT("Steel Set"));
    SteelSet.SetPieces.Add(EEquipmentSlot::ES_Head, CreateAppearance(TEXT("Steel Helmet"), EEquipmentSlot::ES_Head));
    SteelSet.SetPieces.Add(EEquipmentSlot::ES_Chest, CreateAppearance(TEXT("Steel Chest"), EEquipmentSlot::ES_Chest));
    SteelSet.SetPieces.Add(EEquipmentSlot::ES_Legs, CreateAppearance(TEXT("Steel Legs"), EEquipmentSlot::ES_Legs));
    SteelSet.PiecesRequired = 3;
    SteelSet.bIsUnlocked = false;
    
    AvailableSets.Add(IronSet);
    AvailableSets.Add(SteelSet);
}

void UTransmogrificationSystem::ApplyAppearanceToCharacter(const FString& ItemID)
{
    AActor* OwnerActor = GetOwner();
    if (!OwnerActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("No owner actor found for transmog application"));
        return;
    }
    
    USkeletalMeshComponent* SkeletalMesh = OwnerActor->FindComponentByClass<USkeletalMeshComponent>();
    if (!SkeletalMesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("No skeletal mesh component found"));
        return;
    }
    
    // Get the transmog appearance for this item
    FTransmogAppearance Appearance;
    bool bHasTransmog = false;
    
    if (EquipmentTransmogs.Contains(ItemID))
    {
        Appearance = EquipmentTransmogs[ItemID].TransmogAppearance;
        bHasTransmog = true;
    }
    
    // Apply the appearance to the character
    // This would typically involve changing the mesh and materials
    if (bHasTransmog && Appearance.Mesh)
    {
        // Apply transmog mesh
        SkeletalMesh->SetSkeletalMesh(Appearance.Mesh);
        
        // Apply materials with dyes
        for (int32 i = 0; i < Appearance.Materials.Num() && i < SkeletalMesh->GetNumMaterials(); i++)
        {
            UMaterialInterface* Material = Appearance.Materials[i];
            if (Material)
            {
                UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material);
                if (DynamicMaterial)
                {
                    // Apply dye colors
                    if (EquipmentTransmogs.Contains(ItemID))
                    {
                        const TArray<FLinearColor>& AppliedDyes = EquipmentTransmogs[ItemID].AppliedDyes;
                        for (int32 DyeIndex = 0; DyeIndex < AppliedDyes.Num() && DyeIndex < 4; DyeIndex++)
                        {
                            FString ParameterName = FString::Printf(TEXT("DyeColor_%d"), DyeIndex);
                            DynamicMaterial->SetVectorParameterValue(FName(*ParameterName), AppliedDyes[DyeIndex]);
                        }
                    }
                    
                    SkeletalMesh->SetMaterial(i, DynamicMaterial);
                }
            }
        }
    }
    
    UpdateSlotVisibility(GetItemSlot(ItemID));
}

void UTransmogrificationSystem::UpdateSlotVisibility(EEquipmentSlot Slot)
{
    AActor* OwnerActor = GetOwner();
    if (!OwnerActor)
    {
        return;
    }
    
    USkeletalMeshComponent* SkeletalMesh = OwnerActor->FindComponentByClass<USkeletalMeshComponent>();
    if (!SkeletalMesh)
    {
        return;
    }
    
    // Hide/show mesh parts based on slot visibility
    bool bVisible = IsSlotVisible(Slot);
    
    // This would typically involve hiding/showing specific mesh parts
    // For now, we'll just log the visibility change
    UE_LOG(LogTemp, Warning, TEXT("Slot visibility updated: %d is %s"), (int32)Slot, bVisible ? TEXT("visible") : TEXT("hidden"));
}

void UTransmogrificationSystem::CheckForSetBonuses()
{
    // Check for completed transmog sets and apply bonuses
    for (const FTransmogSet& Set : AvailableSets)
    {
        if (!Set.bIsUnlocked)
        {
            continue;
        }
        
        int32 PiecesEquipped = 0;
        
        for (const auto& PiecePair : Set.SetPieces)
        {
            EEquipmentSlot Slot = PiecePair.Key;
            const FTransmogAppearance& RequiredAppearance = PiecePair.Value;
            
            // Check if any item in this slot has the required appearance
            for (const auto& TransmogPair : EquipmentTransmogs)
            {
                const FEquipmentTransmog& EquipmentTransmog = TransmogPair.Value;
                if (EquipmentTransmog.Slot == Slot && 
                    EquipmentTransmog.TransmogAppearance.ItemName == RequiredAppearance.ItemName)
                {
                    PiecesEquipped++;
                    break;
                }
            }
        }
        
        if (PiecesEquipped >= Set.PiecesRequired)
        {
            // Apply set bonus
            UE_LOG(LogTemp, Warning, TEXT("Set bonus activated: %s (%d pieces)"), *Set.SetName, PiecesEquipped);
        }
    }
}

FTransmogAppearance UTransmogrificationSystem::CreateAppearance(const FString& Name, EEquipmentSlot Slot)
{
    FTransmogAppearance Appearance;
    Appearance.ItemName = Name;
    Appearance.Description = FString::Printf(TEXT("Transmog appearance for %s"), *Name);
    Appearance.Icon = nullptr;
    Appearance.Mesh = nullptr;
    Appearance.Materials.Empty();
    Appearance.DyeColors.Empty();
    Appearance.bIsUnlocked = false;
    Appearance.UnlockRequirement = TEXT("");
    Appearance.EquipmentSlot = Slot;
    Appearance.ArmorType = EArmorType::AT_Custom;
    Appearance.WeaponType = EWeaponType::WT_Custom;
    Appearance.bHideHelmet = false;
    Appearance.bHideShoulders = false;
    Appearance.bHideCloak = false;
    
    return Appearance;
}

FDyeColor UTransmogrificationSystem::CreateDye(const FString& Name, FLinearColor Color)
{
    FDyeColor Dye;
    Dye.ColorName = Name;
    Dye.Color = Color;
    Dye.ColorSwatch = nullptr;
    Dye.bIsUnlocked = false;
    Dye.UnlockRequirement = TEXT("");
    Dye.Cost = 100;
    
    return Dye;
}

FTransmogSet UTransmogrificationSystem::CreateTransmogSet(const FString& Name)
{
    FTransmogSet Set;
    Set.SetName = Name;
    Set.Description = FString::Printf(TEXT("Transmog set for %s"), *Name);
    Set.SetIcon = nullptr;
    Set.SetPieces.Empty();
    Set.SetBonuses.Empty();
    Set.bIsUnlocked = false;
    Set.UnlockRequirement = TEXT("");
    Set.PiecesRequired = 0;
    Set.PiecesUnlocked = 0;
    
    return Set;
}

void UTransmogrificationSystem::NotifyTransmogApplied(const FEquipmentTransmog& EquipmentTransmog)
{
    OnTransmogApplied.Broadcast(EquipmentTransmog);
}

void UTransmogrificationSystem::NotifyTransmogRemoved(EEquipmentSlot Slot)
{
    OnTransmogRemoved.Broadcast(Slot);
}

void UTransmogrificationSystem::NotifyAppearanceUnlocked(const FTransmogAppearance& Appearance)
{
    OnAppearanceUnlocked.Broadcast(Appearance);
}

void UTransmogrificationSystem::NotifySetUnlocked(const FTransmogSet& TransmogSet)
{
    OnSetUnlocked.Broadcast(TransmogSet);
}

void UTransmogrificationSystem::NotifyDyeApplied(const FString& ItemID)
{
    OnDyeApplied.Broadcast(ItemID);
}

bool UTransmogrificationSystem::ValidateTransmog(const FString& ItemID, const FString& AppearanceName)
{
    if (!CanTransmogItem(ItemID))
    {
        UE_LOG(LogTemp, Warning, TEXT("Item cannot be transmogrified: %s"), *ItemID);
        return false;
    }
    
    FTransmogAppearance Appearance = GetAppearance(AppearanceName);
    if (Appearance.ItemName.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("Appearance not found: %s"), *AppearanceName);
        return false;
    }
    
    if (!Appearance.bIsUnlocked)
    {
        UE_LOG(LogTemp, Warning, TEXT("Appearance not unlocked: %s"), *AppearanceName);
        return false;
    }
    
    EEquipmentSlot ItemSlot = GetItemSlot(ItemID);
    if (Appearance.EquipmentSlot != ItemSlot)
    {
        UE_LOG(LogTemp, Warning, TEXT("Appearance slot mismatch: item %d, appearance %d"), (int32)ItemSlot, (int32)Appearance.EquipmentSlot);
        return false;
    }
    
    return true;
}

void UTransmogrificationSystem::UpdateCharacterMesh()
{
    // Update character mesh based on all transmogs
    UpdateCharacterAppearance();
}

void UTransmogrificationSystem::UpdateCharacterMaterials()
{
    // Update character materials based on all transmogs and dyes
    UpdateCharacterAppearance();
}

void UTransmogrificationSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UTransmogrificationSystem, EquipmentTransmogs);
    DOREPLIFETIME(UTransmogrificationSystem, AvailableAppearances);
    DOREPLIFETIME(UTransmogrificationSystem, AvailableDyes);
    DOREPLIFETIME(UTransmogrificationSystem, AvailableSets);
    DOREPLIFETIME(UTransmogrificationSystem, SlotVisibility);
    DOREPLIFETIME(UTransmogrificationSystem, bPreviewActive);
    DOREPLIFETIME(UTransmogrificationSystem, PreviewItemID);
}
