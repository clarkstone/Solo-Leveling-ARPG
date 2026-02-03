#include "CharacterCustomization.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Animation/SkeletalMeshActor.h"
#include "Net/UnrealNetwork.h"

UCharacterCustomization::UCharacterCustomization()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);
    
    bIsCustomizationActive = false;
    SelectedPresetIndex = -1;
}

void UCharacterCustomization::BeginPlay()
{
    Super::BeginPlay();
    InitializeCustomizationSystem();
    LoadCustomization();
}

void UCharacterCustomization::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCharacterCustomization::InitializeCustomizationSystem()
{
    UE_LOG(LogTemp, Warning, TEXT("Character Customization System initialized"));
    
    // Load default presets
    LoadPresets();
    
    // Initialize default customization data
    CurrentCustomization.Appearance.BodyType = EBodyType::BT_Standard;
    CurrentCustomization.Appearance.GenderIdentity = EGenderIdentity::GI_Male;
    CurrentCustomization.Appearance.CharacterRace = ERace::Race_Human;
    CurrentCustomization.Appearance.SkinTone = ESkinTone::ST_Fair;
    CurrentCustomization.Appearance.Age = 25;
    CurrentCustomization.Appearance.Height = 175.0f;
    CurrentCustomization.Appearance.Weight = 70.0f;
    CurrentCustomization.Appearance.HairColor = EHairColor::HC_Brown;
    CurrentCustomization.Appearance.HairHighlightColor = EHairColor::HC_Black;
    CurrentCustomization.Appearance.LeftEyeColor = EEyeColor::EC_Brown;
    CurrentCustomization.Appearance.RightEyeColor = EEyeColor::EC_Brown;
    CurrentCustomization.Appearance.bHasVitiligo = false;
    CurrentCustomization.Appearance.bHasHeterochromia = false;
    CurrentCustomization.CustomizationPoints = 100;
    CurrentCustomization.bIsCustomizationComplete = false;
}

void UCharacterCustomization::StartCustomization()
{
    if (bIsCustomizationActive)
    {
        UE_LOG(LogTemp, Warning, TEXT("Customization already active"));
        return;
    }

    bIsCustomizationActive = true;
    UE_LOG(LogTemp, Warning, TEXT("Character customization started"));
    
    // Notify listeners
    OnAppearanceChanged.Broadcast(CurrentCustomization.Appearance);
}

void UCharacterCustomization::FinishCustomization()
{
    if (!bIsCustomizationActive)
    {
        UE_LOG(LogTemp, Warning, TEXT("No customization in progress"));
        return;
    }

    if (!ValidateCustomization())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid customization data - cannot finish"));
        return;
    }

    bIsCustomizationActive = false;
    CurrentCustomization.bIsCustomizationComplete = true;
    
    ApplyCustomization(CurrentCustomization);
    SaveCustomization();
    
    // Notify listeners
    OnCharacterCustomized.Broadcast(CurrentCustomization);
    
    UE_LOG(LogTemp, Warning, TEXT("Character customization completed"));
}

void UCharacterCustomization::CancelCustomization()
{
    if (!bIsCustomizationActive)
    {
        return;
    }

    bIsCustomizationActive = false;
    UE_LOG(LogTemp, Warning, TEXT("Character customization cancelled"));
    
    // Revert to last saved customization
    LoadCustomization();
    ApplyCustomization(CurrentCustomization);
}

bool UCharacterCustomization::IsCustomizationActive() const
{
    return bIsCustomizationActive;
}

void UCharacterCustomization::ApplyCustomization(const FCharacterCustomizationData& CustomizationData)
{
    CurrentCustomization = CustomizationData;
    ApplyAppearanceToCharacter();
    NotifyAppearanceChanged();
}

FCharacterCustomizationData UCharacterCustomization::GetCurrentCustomization() const
{
    return CurrentCustomization;
}

TArray<FCharacterPreset> UCharacterCustomization::GetAvailablePresets() const
{
    return AvailablePresets;
}

void UCharacterCustomization::SelectPreset(int32 PresetIndex)
{
    if (PresetIndex < 0 || PresetIndex >= AvailablePresets.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid preset index: %d"), PresetIndex);
        return;
    }

    const FCharacterPreset& Preset = AvailablePresets[PresetIndex];
    if (!Preset.bIsLocked)
    {
        SelectedPresetIndex = PresetIndex;
        ApplyPreset(Preset);
        NotifyPresetSelected.Broadcast(Preset, PresetIndex);
        UE_LOG(LogTemp, Warning, TEXT("Preset selected: %s"), *Preset.PresetName);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Preset is locked: %s - %s"), *Preset.PresetName, *Preset.UnlockRequirement);
    }
}

void UCharacterCustomization::SaveAsPreset(const FString& PresetName)
{
    FCharacterPreset NewPreset;
    NewPreset.PresetName = PresetName;
    NewPreset.Appearance = CurrentCustomization.Appearance;
    NewPreset.PresetThumbnail = CurrentCustomization.Appearance.PortraitImage;
    NewPreset.bIsLocked = false;
    NewPreset.UnlockRequirement = TEXT("");
    
    AvailablePresets.Add(NewPreset);
    PresetDatabase.Add(PresetName, AvailablePresets.Num() - 1);
    
    SaveCustomization();
    UE_LOG(LogTemp, Warning, TEXT("Preset saved: %s"), *PresetName);
}

void UCharacterCustomization::DeletePreset(int32 PresetIndex)
{
    if (PresetIndex < 0 || PresetIndex >= AvailablePresets.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid preset index: %d"), PresetIndex);
        return;
    }

    const FCharacterPreset& Preset = AvailablePresets[PresetIndex];
    FString PresetName = Preset.PresetName;
    
    AvailablePresets.RemoveAt(PresetIndex);
    PresetDatabase.Remove(PresetName);
    
    SaveCustomization();
    UE_LOG(LogTemp, Warning, TEXT("Preset deleted: %s"), *PresetName);
}

bool UCharacterCustomization::IsPresetUnlocked(int32 PresetIndex) const
{
    if (PresetIndex < 0 || PresetIndex >= AvailablePresets.Num())
    {
        return false;
    }
    
    return !AvailablePresets[PresetIndex].bIsLocked;
}

// Appearance Modification Functions
void UCharacterCustomization::SetBodyType(EBodyType BodyType)
{
    CurrentCustomization.Appearance.BodyType = BodyType;
    NotifyAppearanceChanged();
}

void UCharacterCustomization::SetGenderIdentity(EGenderIdentity GenderIdentity)
{
    CurrentCustomization.Appearance.GenderIdentity = GenderIdentity;
    NotifyAppearanceChanged();
}

void UCharacterCustomization::SetRace(ERace Race)
{
    CurrentCustomization.Appearance.CharacterRace = Race;
    NotifyAppearanceChanged();
}

void UCharacterCustomization::SetSkinTone(ESkinTone SkinTone)
{
    CurrentCustomization.Appearance.SkinTone = SkinTone;
    NotifyAppearanceChanged();
}

void UCharacterCustomization::SetAge(int32 Age)
{
    CurrentCustomization.Appearance.Age = FMath::Clamp(Age, 18, 80);
    NotifyAppearanceChanged();
}

void UCharacterCustomization::SetHeight(float Height)
{
    CurrentCustomization.Appearance.Height = FMath::Clamp(Height, 150.0f, 220.0f);
    NotifyAppearanceChanged();
}

void UCharacterCustomization::SetWeight(float Weight)
{
    CurrentCustomization.Appearance.Weight = FMath::Clamp(Weight, 40.0f, 120.0f);
    NotifyAppearanceChanged();
}

void UCharacterCustomization::AddScar(const FString& Scar)
{
    if (!CurrentCustomization.Appearance.Scars.Contains(Scar))
    {
        CurrentCustomization.Appearance.Scars.Add(Scar);
        NotifyAppearanceChanged();
        UE_LOG(LogTemp, Warning, TEXT("Scar added: %s"), *Scar);
    }
}

void UCharacterCustomization::RemoveScar(const FString& Scar)
{
    if (CurrentCustomization.Appearance.Scars.Contains(Scar))
    {
        CurrentCustomization.Appearance.Scars.Remove(Scar);
        NotifyAppearanceChanged();
        UE_LOG(LogTemp, Warning, TEXT("Scar removed: %s"), *Scar);
    }
}

void UCharacterCustomization::AddTattoo(const FString& Tattoo)
{
    if (!CurrentCustomization.Appearance.Tattoos.Contains(Tattoo))
    {
        CurrentCustomization.Appearance.Tattoos.Add(Tattoo);
        NotifyAppearanceChanged();
        UE_LOG(LogTemp, Warning, TEXT("Tattoo added: %s"), *Tattoo);
    }
}

void UCharacterCustomization::RemoveTattoo(const FString& Tattoo)
{
    if (CurrentCustomization.Appearance.Tattoos.Contains(Tattoo))
    {
        CurrentCustomization.Appearance.Tattoos.Remove(Tattoo);
        NotifyAppearanceChanged();
        UE_LOG(LogTemp, Warning, TEXT("Tattoo removed: %s"), *Tattoo);
    }
}

void UCharacterCustomization::SetHairColor(EHairColor Color)
{
    CurrentCustomization.Appearance.HairColor = Color;
    NotifyAppearanceChanged();
}

void UCharacterCustomization::SetHairHighlightColor(EHairColor HighlightColor)
{
    CurrentCustomization.Appearance.HairHighlightColor = HighlightColor;
    NotifyAppearanceChanged();
}

void UCharacterCustomization::SetHairstyle(const FString& Hairstyle)
{
    CurrentCustomization.Appearance.Hairstyle = Hairstyle;
    NotifyAppearanceChanged();
}

void UCharacterCustomization::SetFacialHairStyle(const FString& FacialHairStyle)
{
    CurrentCustomization.Appearance.FacialHairStyle = FacialHairStyle;
    NotifyAppearanceChanged();
}

void UCharacterCustomization::SetEyeColors(EEyeColor LeftEye, EEyeColor RightEye)
{
    CurrentCustomization.Appearance.LeftEyeColor = LeftEye;
    CurrentCustomization.Appearance.RightEyeColor = RightEye;
    
    if (LeftEye != RightEye)
    {
        CurrentCustomization.Appearance.bHasHeterochromia = true;
    }
    else
    {
        CurrentCustomization.Appearance.bHasHeterochromia = false;
    }
    
    NotifyAppearanceChanged();
}

void UCharacterCustomization::SetMakeupStyle(const FString& MakeupStyle)
{
    CurrentCustomization.Appearance.MakeupStyle = MakeupStyle;
    NotifyAppearanceChanged();
}

void UCharacterCustomization::ToggleVitiligo()
{
    CurrentCustomization.Appearance.bHasVitiligo = !CurrentCustomization.Appearance.bHasVitiligo;
    NotifyAppearanceChanged();
}

void UCharacterCustomization::ToggleHeterochromia()
{
    CurrentCustomization.Appearance.bHasHeterochromia = !CurrentCustomization.Appearance.bHasHeterochromia;
    
    if (!CurrentCustomization.Appearance.bHasHeterochromia)
    {
        // If disabling heterochromia, make both eyes the same color
        CurrentCustomization.Appearance.RightEyeColor = CurrentCustomization.Appearance.LeftEyeColor;
    }
    
    NotifyAppearanceChanged();
}

void UCharacterCustomization::AddRaceSpecificFeature(const FString& Feature)
{
    if (!CurrentCustomization.Appearance.RaceSpecificFeatures.Contains(Feature))
    {
        CurrentCustomization.Appearance.RaceSpecificFeatures.Add(Feature);
        NotifyAppearanceChanged();
        UE_LOG(LogTemp, Warning, TEXT("Race-specific feature added: %s"), *Feature);
    }
}

void UCharacterCustomization::RemoveRaceSpecificFeature(const FString& Feature)
{
    if (CurrentCustomization.Appearance.RaceSpecificFeatures.Contains(Feature))
    {
        CurrentCustomization.Appearance.RaceSpecificFeatures.Remove(Feature);
        NotifyAppearanceChanged();
        UE_LOG(LogTemp, Warning, TEXT("Race-specific feature removed: %s"), *Feature);
    }
}

// Quality of Life Features
void UCharacterCustomization::OpenMagicMirror()
{
    // Check if player can customize (not in combat, etc.)
    if (!CanRecustomize())
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot customize at this time"));
        return;
    }
    
    StartCustomization();
}

bool UCharacterCustomization::CanRecustomize() const
{
    // Check if player is in a safe location for customization
    // This would typically check for combat state, dialogue state, etc.
    return true; // For now, always allow customization
}

void UCharacterCustomization::RandomizeAppearance()
{
    GenerateRandomAppearance();
    NotifyAppearanceChanged();
}

// Data Management
void UCharacterCustomization::SaveCustomization()
{
    // Save current customization to save game data
    // This would integrate with the save system
    UE_LOG(LogTemp, Warning, TEXT("Character customization saved"));
}

void UCharacterCustomization::LoadCustomization()
{
    // Load customization from save game data
    // This would integrate with the save system
    UE_LOG(LogTemp, Warning, TEXT("Character customization loaded"));
}

void UCharacterCustomization::ResetToDefault()
{
    // Reset to default appearance
    InitializeCustomizationSystem();
    NotifyAppearanceChanged();
    UE_LOG(LogTemp, Warning, TEXT("Character customization reset to default"));
}

bool UCharacterCustomization::ValidateCustomization()
{
    // Validate customization data
    return true; // For now, always valid
}

void UCharacterCustomization::LoadPresets()
{
    // Load presets from data table or create defaults
    AvailablePresets.Empty();
    PresetDatabase.Empty();
    
    // Create default presets
    FCharacterPreset DefaultPreset = CreateDefaultPreset(TEXT("Default"));
    AvailablePresets.Add(DefaultPreset);
    PresetDatabase.Add(TEXT("Default"), 0);
    
    // Create race-specific presets
    FCharacterPreset HumanPreset = CreateDefaultPreset(TEXT("Human Warrior"));
    HumanPreset.Appearance.BodyType = EBodyType::BT_Athletic;
    HumanPreset.Appearance.GenderIdentity = EGenderIdentity::GI_Male;
    AvailablePresets.Add(HumanPreset);
    PresetDatabase.Add(TEXT("Human Warrior"), 1);
    
    FCharacterPreset ElfPreset = CreateDefaultPreset(TEXT("Elf Mage"));
    ElfPreset.Appearance.CharacterRace = ERace::Race_Elf;
    ElfPreset.Appearance.BodyType = EBodyType::BT_Slender;
    ElfPreset.Appearance.GenderIdentity = EGenderIdentity::GI_Female;
    AvailablePresets.Add(ElfPreset);
    PresetDatabase.Add(TEXT("Elf Mage"), 2);
    
    FCharacterPreset DwarfPreset = CreateDefaultPreset(TEXT("Dwarf Fighter"));
    DwarfPreset.Appearance.CharacterRace = ERace::Race_Dwarf;
    DwarfPreset.Appearance.BodyType = EBodyType::BT_Heavy;
    AvailablePresets.Add(DwarfPreset);
    PresetDatabase.Add(TEXT("Dwarf Fighter"), 3);
    
    // Lock some presets for now (would unlock through achievements)
    AvailablePresets[1].bIsLocked = false; // Human Warrior unlocked
    AvailablePresets[2].bIsLocked = true; // Elf Mage locked (requires achievement)
    AvailablePresets[3].bIsLocked = true; // Dwarf Fighter locked (requires achievement)
    
    UpdatePresetUnlockStatus();
}

FCharacterPreset UCharacterCustomization::CreateDefaultPreset(const FString& Name)
{
    FCharacterPreset Preset;
    Preset.PresetName = Name;
    Preset.Appearance = CurrentCustomization.Appearance;
    Preset.bIsLocked = false;
    Preset.UnlockRequirement = TEXT("");
    Preset.PresetThumbnail = nullptr;
    
    return Preset;
}

void UCharacterCustomization::ApplyPreset(const FCharacterPreset& Preset)
{
    CurrentCustomization.Appearance = Preset.Appearance;
    SelectedPresetIndex = AvailablePresets.IndexOf(Preset);
    ApplyAppearanceToCharacter();
    NotifyAppearanceChanged();
    NotifyPresetSelected.Broadcast(Preset, SelectedPresetIndex);
}

void UCharacterCustomization::UpdatePresetUnlockStatus()
{
    // Update unlock status based on achievements, level, etc.
    for (int32 i = 0; i < AvailablePresets.Num(); i++)
    {
        FCharacterPreset& Preset = AvailablePresets[i];
        
        // Check unlock conditions
        if (Preset.PresetName == TEXT("Elf Mage"))
        {
            Preset.bIsLocked = false; // Unlock Elf Mage (achievement-based)
        }
        else if (Preset.PresetName == TEXT("Dwarf Fighter"))
        {
            Preset.bIsLocked = false; // Unlock Dwarf Fighter (achievement-based)
        }
    }
}

void UCharacterCustomization::NotifyAppearanceChanged()
{
    OnAppearanceChanged.Broadcast(CurrentCustomization.Appearance);
}

void UCharacterCustomization::NotifyPresetSelected()
{
    if (SelectedPresetIndex >= 0 && SelectedPresetIndex < AvailablePresets.Num())
    {
        OnPresetSelected.Broadcast(AvailablePresets[SelectedPresetIndex], SelectedPresetIndex);
    }
}

void UCharacterCustomization::NotifyCharacterCustomized()
{
    OnCharacterCustomized.Broadcast(CurrentCustomization);
}

FCharacterCustomizationData UCharacterCustomization::GenerateRandomAppearance()
{
    // Generate random appearance
    CurrentCustomization.Appearance.BodyType = static_cast<EBodyType>(FMath::RandRange(0, 3));
    CurrentCustomization.Appearance.GenderIdentity = static_cast<EGenderIdentity>(FMath::RandRange(0, 3));
    CurrentCustomization.Appearance.CharacterRace = static_cast<ERace>(FMath::RandRange(0, 7));
    CurrentCustomization.Appearance.SkinTone = static_cast<ESkinTone>(FMath::RandRange(0, 6));
    CurrentCustomization.Appearance.Age = FMath::RandRange(18, 60);
    CurrentCustomization.Appearance.Height = FMath::RandRange(150.0f, 220.0f);
    CurrentCustomization.Appearance.Weight = FMath::RandRange(40.0f, 120.0f);
    CurrentCustomization.Appearance.HairColor = static_cast<EHairColor>(FMath::RandRange(0, 10));
    CurrentCustomization.Appearance.HairHighlightColor = static_cast<EHairColor>(FMath::RandRange(0, 10));
    CurrentCustomization.Appearance.LeftEyeColor = static_cast<EEyeColor>(FMath::RandRange(0, 8));
    CurrentCustomization.Appearance.RightEyeColor = static_cast<EEyeColor>(FMath::RandRange(0, 8));
    
    // Random chance for special features
    CurrentCustomization.Appearance.bHasViligo = FMath::RandRange(0, 10) > 7;
    CurrentCustomization.Appearance.bHasHeterochromia = FMath::RandRange(0, 10) > 8;
    
    // Add random scars and tattoos
    if (FMath::RandRange(0, 10) > 7)
    {
        CurrentCustomization.Appearance.Scars.Add(FString::Printf(TEXT("Scar_%d"), FMath::RandRange(1, 5)));
    }
    
    if (FMath::RandRange(0, 10) > 8)
    {
        CurrentCustomization.Appearance.Tattoos.Add(FString::Printf(TEXT("Tattoo_%d"), FMath::RandRange(1, 5)));
    }
    
    // Random hairstyle and facial hair
    TArray<FString> Hairstyles = {TEXT("Short"), TEXT("Medium"), TEXT("Long"), TEXT("Bald"), TEXT("Ponytail"), TEXT("Mohawk"), TEXT("Braided")};
    CurrentCustomization.Appearance.Hairstyle = Hairstyles[FMath::RandRange(0, Hairstyles.Num() - 1)];
    
    TArray<FString> FacialHairStyles = {TEXT("Clean Shaven"), TEXT("Beard"), TEXT("Mustache"), TEXT("Sideburns"), TEXT("Goatee"), TEXT("None")};
    CurrentCustomization.Appearance.FacialHairStyle = FacialHairStyles[FMath::RandRange(0, FacialHairStyles.Num() - 1)];
    
    // Random makeup
    TArray<FString> MakeupStyles = {TEXT("None"), TEXT("Natural"), TEXT("Dramatic"), TEXT("Gothic"), TEXT("Elegant")};
    CurrentCustomization.Appearance.MakeupStyle = MakeupStyles[FMath::RandRange(0, MakeupStyles.Num() - 1)];
    
    UE_LOG(LogTemp, Warning, TEXT("Random appearance generated"));
}

void UCharacterCustomization::ApplyAppearanceToCharacter()
{
    // Apply appearance to character mesh and materials
    AActor* OwnerActor = GetOwner();
    if (!OwnerActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("No owner actor found for customization application"));
        return;
    }
    
    // Get skeletal mesh component
    USkeletalMeshComponent* SkeletalMesh = OwnerActor->FindComponentByClass<USkeletalMeshComponent>();
    if (!SkeletalMesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("No skeletal mesh component found"));
        return;
    }
    
    // Update skeletal mesh based on race and body type
    UpdateCharacterMesh();
    
    // Update materials based on appearance
    UpdateCharacterMaterials();
}

void UCharacterCustomization::UpdateCharacterMesh()
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
    
    // Load appropriate mesh based on race and body type
    FString MeshPath = TEXT("/Game/Characters/");
    
    switch (CurrentCustomization.Appearance.CharacterRace)
    {
        case ERace::Race_Human:
            MeshPath += TEXT("Human/");
            break;
        case ERace::Race_Elf:
            MeshPath += TEXT("Elf/");
            break;
        case ERace::Race_Dwarf:
            MeshPath += TEXT("Dwarf/");
            break;
        case ERace::Race_Orc:
            MeshPath += TEXT("Orc/");
            break;
        case ERace::Race_Beastkin:
            MeshPath += TEXT("Beastkin/");
            break;
        case ERace::Race_Dragonborn:
            MeshPath += TEXT("Dragonborn/");
            break;
        case ERace::Race_Celestial:
            MeshPath += TEXT("Celestial/");
            break;
        case ERace::Race_Shadow:
            MeshPath += TEXT("Shadow/");
            break;
        default:
            MeshPath += TEXT("Human/");
            break;
    }
    
    switch (CurrentCustomization.Appearance.BodyType)
    {
        case EBodyType::BT_Standard:
            MeshPath += TEXT("Standard/");
            break;
        case EBodyType::BT_Athletic:
            MeshPath += TEXT("Athletic/");
            break;
        case EBodyType::BT_Slender:
            MeshPath += TEXT("Slender/");
            break;
        case EBodyType::BT_Heavy:
            MeshPath += TEXT("Heavy/");
            break;
        default:
            MeshPath += TEXT("Standard/");
            break;
    }
    
    switch (CurrentCustomization.Appearance.GenderIdentity)
    {
        case EGenderIdentity::GI_Male:
            MeshPath += TEXT("Male/");
            break;
        case EGenderIdentity::GI_Female:
            MeshPath += TEXT("Female/");
            break;
        case EGenderIdentity::GI_NonBinary:
            MeshPath += TEXT("NonBinary/");
            break;
        default:
            MeshPath += TEXT("Male/");
            break;
    }
    
    MeshPath += TEXT("SKM_Character.uasset");
    
    // Load the appropriate mesh
    USkeletalMesh* NewMesh = LoadObject<USkeletalMesh>(nullptr, *MeshPath);
    if (NewMesh)
    {
        SkeletalMesh->SetSkeletalMesh(NewMesh);
        UE_LOG(LogTemp, Warning, TEXT("Loaded character mesh: %s"), *MeshPath);
    }
}

void UCharacterCustomization::UpdateCharacterMaterials()
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
    
    // Update materials based on skin tone and race
    UMaterialInterface* MaterialInterface = GEngine->MaterialManager;
    if (!MaterialInterface)
    {
        return;
    }
    
    // Create dynamic material instance based on appearance
    UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialInterface->LoadMaterial(TEXT("M_Character_Master"));
    if (DynamicMaterial)
    {
        SkeletalMesh->SetMaterial(0, DynamicMaterial);
        
        // Set skin tone parameters
        FLinearColor SkinColor;
        switch (CurrentCustomization.Appearance.SkinTone)
        {
            case ESkinTone::ST_Pale:
                SkinColor = FLinearColor(FColor(0.95f, 0.85f, 0.80f, 1.0f));
                break;
            case ESkinTone::ST_Fair:
                SkinColor = FLinearColor(FColor(0.95f, 0.85f, 0.75f, 1.0f));
                break;
            case ESkinTone::ST_Olive:
                SkinColor = FLinearColor(FColor(0.85f, 0.75f, 0.65f, 1.0f));
                break;
            case ESkinTone::ST_Tan:
                SkinColor = FLinearColor(0.75f, 0.65f, 0.55f, 1.0f));
                break;
            case ESkinTone::ST_Brown:
                SkinColor = FLinearColor(0.65f, 0.55f, 0.45f, 1.0f));
                break;
            case ESkinTone::ST_DarkBrown:
                SkinColor = FLinearColor(0.55f, 0.45f, 0.35f, 1.0f));
                break;
            default:
                SkinColor = FLinearColor(0.95f, 0.85f, 0.75f, 1.0f));
                break;
        }
        
        DynamicMaterial->SetVectorParameterValue(FName(TEXT("SkinColor"), SkinColor);
        
        // Set hair color parameters
        FLinearColor HairColor;
        switch (CurrentCustomization.Appearance.HairColor)
        {
            case EHairColor::HC_Black:
                HairColor = FLinearColor(FColor(0.05f, 0.05f, 0.05f, 1.0f));
                break;
            case EHairColor::HC_Brown:
                HairColor = FLinearColor(0.1f, 0.05f, 0.02f, 1.0f));
                break;
            case EHairColor::HC_Blonde:
                HairColor = FLinearColor(0.7f, 0.65f, 0.6f, 1.0f));
                break;
            case EHairColor::HC_Red:
                HairColor = FLinearColor(0.8f, 0.2f, 0.2f, 1.0f));
                break;
            case EHairColor::HC_White:
                HairColor = FLinearColor(0.95f, 0.95f, 0.9f, 1.0f));
                break;
            case EHairColor::HC_Gray:
                HairColor = FLinearColor(0.5f, 0.5f, 0.5f, 1.0f));
                break;
            case EHairColor::HC_Blue:
                HairColor = FLinearColor(0.2f, 0.4f, 0.8f, 1.0f));
                break;
            case EHairColor::HC_Green:
                HairColor = FLinearColor(0.2f, 0.6f, 0.2f, 1.0f));
                break;
            case EHairColor::HC_Purple:
                HairColor = FLinearColor(0.6f, 0.2f, 0.8f, 1.0f));
                break;
            case EHairColor::HC_Pink:
                HairColor = FLinearColor(0.9f, 0.7f, 0.8f, 1.0f));
                break;
            default:
                HairColor = FLinearColor(0.1f, 0.05f, 0.02f, 1.0f));
                break;
        }
        
        DynamicMaterial->SetVectorParameterValue(FName(TEXT("HairColor"), HairColor);
        
        // Set eye color parameters
        FLinearColor LeftEyeColor;
        switch (CurrentCustomization.Appearance.LeftEyeColor)
        {
            case EEyeColor::EC_Brown:
                LeftEyeColor = FLinearColor(0.1f, 0.05f, 0.02f, 1.0f));
                break;
            case EEyeColor::EC_Blue:
                LeftEyeColor = FLinearColor(0.2f, 0.4f, 0.8f, 1.0f));
                break;
            case EEyeColor::EC_Green:
                LeftEyeColor = FLinearColor(0.2f, 0.6f, 0.2f, 1.0f));
                break;
            case EEyeColor::EC_Hazel:
                LeftEyeColor = FLinearColor(0.5f, 0.4f, 0.1f, 1.0f));
                break;
            case EEyeColor::EC_Gray:
                LeftEyeColor = FLinearColor(0.5f, 0.5f, 0.5f, 1.0f));
                break;
            case EEyeColor::EC_Amber:
                LeftEyeColor = FLinearColor(0.8f, 0.4f, 0.1f, 1.0f));
                break;
            case EEyeColor::EC_Violet:
                LeftEyeColor = FLinearColor(0.6f, 0.2f, 0.8f, 1.0f));
                break;
            case EEyeColor::EC_Red:
                LeftEyeColor = FLinearColor(0.8f, 0.2f, 0.2f, 1.0f));
                break;
            default:
                LeftEyeColor = FLinearColor(0.1f, 0.05f, 0.02f, 1.0f));
                break;
        }
        
        DynamicMaterial->SetVectorParameterValue(FName(TEXT("LeftEyeColor"), LeftEyeColor));
        
        // Set right eye color (for heterochromia)
        DynamicMaterial->SetVectorParameterValue(FName(TEXT("RightEyeColor"), CurrentCustomization.Appearance.RightEyeColor));
        
        UE_LOG(LogTemp, Warning, TEXT("Character materials updated based on appearance"));
    }
}

void UCharacterCustomization::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UCharacterCustomization, CurrentCustomization);
    DOREPLIFETIME(UCharacterCustomization, bIsCustomizationActive);
    DOREPLIFETIME(UCharacterCustomization, SelectedPresetIndex);
    DOREPLIFETIME(UCharacterCustomization, AvailablePresets);
}
