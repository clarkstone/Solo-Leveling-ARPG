#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "TransmogrificationSystem.generated.h"

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
    ES_Head = 0,
    ES_Chest,
    ES_Shoulders,
    ES_Arms,
    ES_Legs,
    ES_Feet,
    ES_Hands,
    ES_Waist,
    ES_Neck,
    ES_Ring1,
    ES_Ring2,
    ES_Trinket1,
    ES_Trinket2,
    ES_MainHand,
    ES_OffHand,
    ES_TwoHand,
    ES_Ranged,
    ES_Ammo,
    ES_Back,
    ES_Cosmetic1,
    ES_Cosmetic2,
    ES_Cosmetic3,
    ES_MAX
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
    AT_Light = 0,
    AT_Medium,
    AT_Heavy,
    AT_Cloth,
    AT_Robe,
    AT_Custom
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    WT_Sword = 0,
    WT_Axe,
    WT_Mace,
    WT_Dagger,
    WT_Bow,
    WT_Crossbow,
    WT_Staff,
    WT_Wand,
    WT_Spear,
    WT_Halberd,
    WT_Greatsword,
    WT_Greataxe,
    WT_Greatmace,
    WT_Fists,
    WT_Custom
};

USTRUCT(BlueprintType)
struct FTransmogAppearance
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Appearance")
    FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Appearance")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Appearance")
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Appearance")
    USkeletalMesh* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Appearance")
    TArray<UMaterialInterface*> Materials;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Appearance")
    TArray<FLinearColor> DyeColors;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Appearance")
    bool bIsUnlocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Appearance")
    FString UnlockRequirement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Appearance")
    EEquipmentSlot EquipmentSlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Appearance")
    EArmorType ArmorType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Appearance")
    EWeaponType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Appearance")
    bool bHideHelmet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Appearance")
    bool bHideShoulders;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Appearance")
    bool bHideCloak;
};

USTRUCT(BlueprintType)
struct FTransmogSet
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Set")
    FString SetName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Set")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Set")
    UTexture2D* SetIcon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Set")
    TMap<EEquipmentSlot, FTransmogAppearance> SetPieces;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Set")
    TArray<FString> SetBonuses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Set")
    bool bIsUnlocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Set")
    FString UnlockRequirement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Set")
    int32 PiecesRequired;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmog Set")
    int32 PiecesUnlocked;
};

USTRUCT(BlueprintType)
struct FEquipmentTransmog
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Transmog")
    FString OriginalItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Transmog")
    FTransmogAppearance TransmogAppearance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Transmog")
    bool bHasTransmog;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Transmog")
    EEquipmentSlot Slot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Transmog")
    TArray<FLinearColor> AppliedDyes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Transmog")
    bool bHideSlot;
};

USTRUCT(BlueprintType)
struct FDyeColor
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dye Color")
    FString ColorName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dye Color")
    FLinearColor Color;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dye Color")
    UTexture2D* ColorSwatch;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dye Color")
    bool bIsUnlocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dye Color")
    FString UnlockRequirement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dye Color")
    int32 Cost;
};

UCLASS(BlueprintType, Blueprintable)
class SIMPLEAPP_API UTransmogrificationSystem : public UActorComponent
{
    GENERATED_BODY()

public:
    UTransmogrificationSystem();

    // Transmogrification Events
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTransmogApplied, const FEquipmentTransmog&, EquipmentTransmog);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTransmogRemoved, EEquipmentSlot, Slot);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAppearanceUnlocked, const FTransmogAppearance&, Appearance);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetUnlocked, const FTransmogSet&, TransmogSet);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDyeApplied, const FString&, ItemID);

    UPROPERTY(BlueprintAssignable, Category = "Transmogrification Events")
    FOnTransmogApplied OnTransmogApplied;

    UPROPERTY(BlueprintAssignable, Category = "Transmogrification Events")
    FOnTransmogRemoved OnTransmogRemoved;

    UPROPERTY(BlueprintAssignable, Category = "Transmogrification Events")
    FOnAppearanceUnlocked OnAppearanceUnlocked;

    UPROPERTY(BlueprintAssignable, Category = "Transmogrification Events")
    FOnSetUnlocked OnSetUnlocked;

    UPROPERTY(BlueprintAssignable, Category = "Transmogrification Events")
    FOnDyeApplied OnDyeApplied;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Transmogrification Management
    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    void InitializeTransmogrification();

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool ApplyTransmog(const FString& ItemID, const FString& AppearanceName);

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool RemoveTransmog(const FString& ItemID);

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool HasTransmog(const FString& ItemID) const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    FEquipmentTransmog GetEquipmentTransmog(const FString& ItemID) const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    TArray<FEquipmentTransmog> GetAllTransmogs() const;

    // Appearance Collection
    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    TArray<FTransmogAppearance> GetAvailableAppearances(EEquipmentSlot Slot) const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    TArray<FTransmogAppearance> GetUnlockedAppearances(EEquipmentSlot Slot) const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool UnlockAppearance(const FString& AppearanceName);

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool IsAppearanceUnlocked(const FString& AppearanceName) const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    FTransmogAppearance GetAppearance(const FString& AppearanceName) const;

    // Transmog Sets
    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    TArray<FTransmogSet> GetAvailableSets() const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    TArray<FTransmogSet> GetUnlockedSets() const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool UnlockTransmogSet(const FString& SetName);

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool IsSetUnlocked(const FString& SetName) const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    FTransmogSet GetTransmogSet(const FString& SetName) const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool ApplyTransmogSet(const FString& SetName);

    // Dye System
    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    TArray<FDyeColor> GetAvailableDyes() const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    TArray<FDyeColor> GetUnlockedDyes() const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool UnlockDye(const FString& DyeName);

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool IsDyeUnlocked(const FString& DyeName) const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool ApplyDye(const FString& ItemID, const FString& DyeName, int32 DyeChannel);

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool RemoveDye(const FString& ItemID, int32 DyeChannel);

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    TArray<FLinearColor> GetAppliedDyes(const FString& ItemID) const;

    // Slot Visibility
    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool SetSlotVisibility(EEquipmentSlot Slot, bool bVisible);

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool IsSlotVisible(EEquipmentSlot Slot) const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    void ToggleHelmetVisibility();

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    void ToggleShoulderVisibility();

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    void ToggleCloakVisibility();

    // Preview System
    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool PreviewTransmog(const FString& ItemID, const FString& AppearanceName);

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    void ClearPreview();

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool IsPreviewActive() const;

    // Save/Load
    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    void SaveTransmogrification();

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    void LoadTransmogrification();

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    void ResetTransmogrification();

    // Utility Functions
    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    bool CanTransmogItem(const FString& ItemID) const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    EEquipmentSlot GetItemSlot(const FString& ItemID) const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    TArray<FString> GetTransmoggableItems() const;

    UFUNCTION(BlueprintCallable, Category = "Transmogrification")
    void UpdateCharacterAppearance();

protected:
    // Internal Functions
    void InitializeAppearances();
    void InitializeDyes();
    void InitializeTransmogSets();
    void ApplyAppearanceToCharacter(const FString& ItemID);
    void UpdateSlotVisibility(EEquipmentSlot Slot);
    void CheckForSetBonuses();

private:
    // Internal State
    TMap<FString, FEquipmentTransmog> EquipmentTransmogs;
    TArray<FTransmogAppearance> AvailableAppearances;
    TArray<FDyeColor> AvailableDyes;
    TArray<FTransmogSet> AvailableSets;
    TMap<EEquipmentSlot, bool> SlotVisibility;
    bool bPreviewActive;
    FString PreviewItemID;
    FTransmogAppearance PreviewAppearance;

    // Helper Functions
    FTransmogAppearance CreateAppearance(const FString& Name, EEquipmentSlot Slot);
    FDyeColor CreateDye(const FString& Name, FLinearColor Color);
    FTransmogSet CreateTransmogSet(const FString& Name);
    void NotifyTransmogApplied(const FEquipmentTransmog& EquipmentTransmog);
    void NotifyTransmogRemoved(EEquipmentSlot Slot);
    void NotifyAppearanceUnlocked(const FTransmogAppearance& Appearance);
    void NotifySetUnlocked(const FTransmogSet& TransmogSet);
    void NotifyDyeApplied(const FString& ItemID);
    bool ValidateTransmog(const FString& ItemID, const FString& AppearanceName);
    void UpdateCharacterMesh();
    void UpdateCharacterMaterials();
};
