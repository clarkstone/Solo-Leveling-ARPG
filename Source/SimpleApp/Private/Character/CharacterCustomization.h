#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CharacterCustomization.generated.h"

UENUM(BlueprintType)
enum class EBodyType : uint8
{
    BT_Standard = 0,
    BT_Athletic,
    BT_Slender,
    BT_Heavy,
    BT_Custom
};

UENUM(BlueprintType)
enum class EGenderIdentity : uint8
{
    GI_Male = 0,
    GI_Female,
    GI_NonBinary,
    GI_Custom
};

UENUM(BlueprintType)
enum class ERace : uint8
{
    Race_Human = 0,
    Race_Elf,
    Race_Dwarf,
    Race_Orc,
    Race_Beastkin,
    Race_Dragonborn,
    Race_Celestial,
    Race_Shadow,
    Race_Custom
};

UENUM(BlueprintType)
enum class ESkinTone : uint8
{
    ST_Pale = 0,
    ST_Fair,
    ST_Olive,
    ST_Tan,
    ST_Brown,
    ST_DarkBrown,
    ST_Custom
};

UENUM(BlueprintType)
enum class EHairColor : uint8
{
    HC_Black = 0,
    HC_Brown,
    HC_Blonde,
    HC_Red,
    HC_White,
    HC_Gray,
    HC_Blue,
    HC_Green,
    HC_Purple,
    HC_Pink,
    HC_Custom
};

UENUM(BlueprintType)
enum class EEyeColor : uint8
{
    EC_Brown = 0,
    EC_Blue,
    EC_Green,
    EC_Hazel,
    EC_Gray,
    EC_Amber,
    EC_Violet,
    EC_Red,
    EC_Custom
};

USTRUCT(BlueprintType)
struct FCharacterAppearance
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    EBodyType BodyType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    EGenderIdentity GenderIdentity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    ERace CharacterRace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    ESkinTone SkinTone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    int32 Age;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    float Height;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    float Weight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    TArray<FString> Scars;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    TArray<FString> Tattoos;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    TArray<FString> Freckles;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    bool bHasVitiligo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    bool bHasHeterochromia;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    EHairColor HairColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    EHairColor HairHighlightColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FString Hairstyle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FString FacialHairStyle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    EEyeColor LeftEyeColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Race = "Appearance")
    EEyeColor RightEyeColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FString MakeupStyle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    TArray<FString> RaceSpecificFeatures;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    UTexture2D* PortraitImage;
};

USTRUCT(BlueprintType)
struct FCharacterCustomizationData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
    FCharacterAppearance Appearance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
    TMap<FString, int32> SelectedPresets;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
    bool bIsCustomizationComplete;

    UPROPERTY(EditAnywhere, Blueprint, BlueprintReadWrite, Category = "Customization")
    FString CharacterName;

    UPROPERTY(EditAnywhere, Blueprint, BlueprintReadWrite, Category = "Customization")
    int32 CustomizationPoints;
};

USTRUCT(BlueprintType)
struct FCharacterPreset
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preset")
    FString PresetName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preset")
    FCharacterAppearance Appearance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preset")
    UTexture2D* PresetThumbnail;

    UPROPERTY(EditAnywhere, Blueprint, BlueprintReadWrite, Category = "Preset")
    bool bIsLocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preset")
    FString UnlockRequirement;
};

UCLASS(BlueprintType, Blueprintable)
class SIMPLEAPP_API UCharacterCustomization : public UActorComponent
{
    GENERATED_BODY()

public:
    UCharacterCustomization();

    // Customization Events
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterCustomized, const FCharacterCustomizationData&, CustomizationData);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPresetSelected, const FCharacterPreset&, Preset, int32, PresetIndex);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAppearanceChanged, const FCharacterAppearance&, Appearance);

    UPROPERTY(BlueprintAssignable, Category = "Character Customization Events")
    FOnCharacterCustomized OnCharacterCustomized;

    UPROPERTY(BlueprintAssignable, Category = "Character Customization Events")
    FOnPresetSelected OnPresetSelected;

    UPROPERTY(BlueprintAssignable, Category = "Character Customization Points")
    FOnAppearanceChanged OnAppearanceChanged;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Customization Management
    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void StartCustomization();

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void FinishCustomization();

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void CancelCustomization();

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    bool IsCustomizationActive() const;

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void ApplyCustomization(const FCharacterCustomizationData& CustomizationData);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    FCharacterCustomizationData GetCurrentCustomization() const;

    // Preset Management
    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    TArray<FCharacterPreset> GetAvailablePresets() const;

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SelectPreset(int32 PresetIndex);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SaveAsPreset(const FString& PresetName);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void DeletePreset(int32 PresetIndex);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    bool IsPresetUnlocked(int32 PresetIndex) const;

    // Appearance Modification
    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SetBodyType(EBodyType BodyType);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SetGenderIdentity(EGenderIdentity GenderIdentity);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SetRace(ERace Race);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SetSkinTone(ESkinTone SkinTone);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SetAge(int32 Age);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SetHeight(float Height);

    UFUNCTION(BlueprintCallable, Category = "Character Preset")
    void SetWeight(float Weight);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void AddScar(const FString& Scar);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void RemoveScar(const FString& Scar);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void AddTattoo(const FString& Tattoo);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void RemoveTattoo(const FString& Tattoo);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SetHairColor(EHairColor Color);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SetHairHighlightColor(EHairColor HighlightColor);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SetHairstyle(const FString& Hairstyle);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SetFacialHairStyle(const FString& FacialHairStyle);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SetEyeColors(EEyeColor LeftEye, EEyeColor RightEye);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SetMakeupStyle(const FString& MakeupStyle);

    UFUNCTION(BlueprintCallable, Customization = "Character Customization")
    void ToggleVitiligo();

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void ToggleHeterochromia();

    // Race-Specific Features
    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void AddRaceSpecificFeature(const FString& Feature);

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void RemoveRaceSpecificFeature(const FString& Feature);

    // Quality of Life Features
    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void OpenMagicMirror();

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    bool CanReCustomize() const;

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void RandomizeAppearance();

    // Data Management
    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void SaveCustomization();

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void LoadCustomization();

    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    void ResetToDefault();

    // Validation
    UFUNCTION(BlueprintCallable, Category = "Character Customization")
    bool ValidateCustomization();

protected:
    // Internal Functions
    void InitializeCustomizationSystem();
    void LoadPresets();
    void ApplyAppearanceToCharacter();
    void UpdateCharacterMesh();
    void UpdateCharacterMaterials();

private:
    // Internal State
    bool bIsCustomizationActive;
    FCharacterCustomizationData CurrentCustomization;
    TArray<FCharacterPreset> AvailablePresets;
    TMap<FString, int32> PresetDatabase;
    int32 SelectedPresetIndex;

    // Helper Functions
    FCharacterPreset CreateDefaultPreset(const FString& Name);
    void ApplyPreset(const FCharacterPreset& Preset);
    void UpdatePresetUnlockStatus();
    void NotifyAppearanceChanged();
    void NotifyPresetSelected();
    void NotifyCharacterCustomized();
    bool ValidateAppearance(const FCharacterAppearance& Appearance);
    void GenerateRandomAppearance();
};
