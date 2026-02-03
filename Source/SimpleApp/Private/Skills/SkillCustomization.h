#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "SkillCustomization.generated.h"

UENUM(BlueprintType)
enum class ESkillElement : uint8
{
    SE_None = 0,
    SE_Fire,
    SE_Ice,
    SE_Lightning,
    SE_Poison,
    SE_Holy,
    SE_Shadow,
    SE_Earth,
    SE_Wind,
    SE_Arcane
};

UENUM(BlueprintType)
enum class ESkillRarity : uint8
{
    SR_Common = 0,
    SR_Uncommon,
    SR_Rare,
    SR_Epic,
    SR_Legendary,
    SR_Mythic
};

UENUM(BlueprintType)
enum class ESkillModificationType : uint8
{
    SMT_Damage = 0,
    SMT_Range,
    SMT_Cooldown,
    SMT_ManaCost,
    SMT_AoE,
    SMT_Duration,
    SMT_StatusEffect,
    SMT_VisualEffect,
    SMT_SoundEffect
};

USTRUCT(BlueprintType)
struct FSkillModification
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Modification")
    ESkillModificationType ModificationType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Modification")
    float ModificationValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Modification")
    bool bIsPercentage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Modification")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Modification")
    UTexture2D* Icon;
};

USTRUCT(BlueprintType)
struct FSkillVisualVariant
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Visual Variant")
    FString VariantName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Visual Variant")
    ESkillElement Element;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Visual Variant")
    UParticleSystem* ParticleEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Visual Variant")
    USoundBase* SoundEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Visual Variant")
    FLinearColor ColorTint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Visual Variant")
    float Scale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Visual Variant")
    bool bIsUnlocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Visual Variant")
    FString UnlockRequirement;
};

USTRUCT(BlueprintType)
struct FSkillUpgradeNode
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Upgrade Node")
    FString NodeName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Upgrade Node")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Upgrade Node")
    int32 RequiredLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Upgrade Node")
    int32 SkillPointsRequired;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Upgrade Node")
    TArray<FSkillModification> Modifications;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Upgrade Node")
    TArray<FString> PrerequisiteNodes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Upgrade Node")
    bool bIsUnlocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Upgrade Node")
    UTexture2D* NodeIcon;
};

USTRUCT(BlueprintType)
struct FSkillTree
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree")
    FString TreeName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree")
    TArray<FSkillUpgradeNode> Nodes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree")
    TMap<FString, int32> NodeConnections;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree")
    int32 TotalSkillPoints;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree")
    int32 UsedSkillPoints;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree")
    bool bIsTreeUnlocked;
};

USTRUCT(BlueprintType)
struct FCustomizedSkill
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customized Skill")
    FString BaseSkillName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customized Skill")
    ESkillElement CurrentElement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customized Skill")
    TArray<FSkillModification> AppliedModifications;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customized Skill")
    FSkillVisualVariant CurrentVisualVariant;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customized Skill")
    int32 SkillLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customized Skill")
    int32 Experience;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customized Skill")
    bool bIsFavorite;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customized Skill")
    int32 SlotIndex;
};

UCLASS(BlueprintType, Blueprintable)
class SIMPLEAPP_API USkillCustomization : public UActorComponent
{
    GENERATED_BODY()

public:
    USkillCustomization();

    // Skill Customization Events
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillCustomized, const FCustomizedSkill&, CustomizedSkill);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillUpgraded, const FString&, SkillName, int32, NewLevel);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVisualVariantUnlocked, const FSkillVisualVariant&, Variant);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillTreeUnlocked, const FString&, TreeName);

    UPROPERTY(BlueprintAssignable, Category = "Skill Customization Events")
    FOnSkillCustomized OnSkillCustomized;

    UPROPERTY(BlueprintAssignable, Category = "Skill Customization Events")
    FOnSkillUpgraded OnSkillUpgraded;

    UPROPERTY(BlueprintAssignable, Category = "Skill Customization Events")
    FOnVisualVariantUnlocked OnVisualVariantUnlocked;

    UPROPERTY(BlueprintAssignable, Category = "Skill Customization Events")
    FOnSkillTreeUnlocked OnSkillTreeUnlocked;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Skill Management
    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    void InitializeSkillCustomization();

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    FCustomizedSkill GetCustomizedSkill(const FString& SkillName) const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    TArray<FCustomizedSkill> GetAllCustomizedSkills() const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    void AddSkillToCustomization(const FString& SkillName);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    void RemoveSkillFromCustomization(const FString& SkillName);

    // Skill Tree Management
    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    TArray<FSkillTree> GetAvailableSkillTrees() const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    bool UnlockSkillTree(const FString& TreeName);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    bool IsSkillTreeUnlocked(const FString& TreeName) const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    int32 GetAvailableSkillPoints(const FString& TreeName) const;

    // Skill Upgrade System
    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    bool UpgradeSkillNode(const FString& TreeName, const FString& NodeName);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    bool CanUpgradeSkillNode(const FString& TreeName, const FString& NodeName) const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    TArray<FSkillUpgradeNode> GetAvailableNodes(const FString& TreeName) const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    TArray<FSkillUpgradeNode> GetUnlockedNodes(const FString& TreeName) const;

    // Element Customization
    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    bool ChangeSkillElement(const FString& SkillName, ESkillElement NewElement);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    ESkillElement GetSkillElement(const FString& SkillName) const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    TArray<ESkillElement> GetAvailableElements(const FString& SkillName) const;

    // Visual Variants
    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    TArray<FSkillVisualVariant> GetAvailableVisualVariants(const FString& SkillName) const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    bool ApplyVisualVariant(const FString& SkillName, const FString& VariantName);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    bool UnlockVisualVariant(const FString& SkillName, const FString& VariantName);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    FSkillVisualVariant GetCurrentVisualVariant(const FString& SkillName) const;

    // Skill Modifications
    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    bool ApplySkillModification(const FString& SkillName, const FSkillModification& Modification);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    bool RemoveSkillModification(const FString& SkillName, ESkillModificationType ModificationType);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    TArray<FSkillModification> GetAppliedModifications(const FString& SkillName) const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    float GetModifiedSkillValue(const FString& SkillName, ESkillModificationType ModificationType, float BaseValue) const;

    // Ashes of War System (Elden Ring inspired)
    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    TArray<FString> GetAvailableAshesOfWar() const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    bool ApplyAshOfWar(const FString& SkillName, const FString& AshOfWarName);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    void RemoveAshOfWar(const FString& SkillName);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    FString GetAppliedAshOfWar(const FString& SkillName) const;

    // Rune System (Diablo III inspired)
    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    TArray<FString> GetAvailableRunes() const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    bool SocketRune(const FString& SkillName, const FString& RuneName);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    void RemoveRune(const FString& SkillName, int32 SocketIndex);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    TArray<FString> GetSocketedRunes(const FString& SkillName) const;

    // Skill Progression
    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    void AddSkillExperience(const FString& SkillName, int32 ExperienceAmount);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    int32 GetSkillLevel(const FString& SkillName) const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    int32 GetSkillExperience(const FString& SkillName) const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    int32 GetExperienceToNextLevel(const FString& SkillName) const;

    // Favorite Skills
    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    void SetFavoriteSkill(const FString& SkillName, bool bIsFavorite);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    bool IsFavoriteSkill(const FString& SkillName) const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    TArray<FCustomizedSkill> GetFavoriteSkills() const;

    // Skill Slot Management
    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    bool AssignSkillToSlot(const FString& SkillName, int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    void RemoveSkillFromSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    FString GetSkillInSlot(int32 SlotIndex) const;

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    TArray<FString> GetAssignedSkills() const;

    // Save/Load
    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    void SaveSkillCustomization();

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    void LoadSkillCustomization();

    UFUNCTION(BlueprintCallable, Category = "Skill Customization")
    void ResetSkillCustomization();

protected:
    // Internal Functions
    void InitializeSkillTrees();
    void InitializeVisualVariants();
    void InitializeAshesOfWar();
    void InitializeRunes();
    void UpdateSkillEffects(const FString& SkillName);
    void CheckForUnlocks();

private:
    // Internal State
    TMap<FString, FCustomizedSkill> CustomizedSkills;
    TArray<FSkillTree> SkillTrees;
    TMap<FString, TArray<FSkillVisualVariant>> VisualVariants;
    TMap<FString, TArray<FString>> AshesOfWar;
    TMap<FString, TArray<FString>> Runes;
    TMap<FString, FString> AppliedAshesOfWar;
    TMap<FString, TArray<FString>> SocketedRunes;
    TArray<FString> AssignedSkillSlots;
    int32 TotalSkillPoints;

    // Helper Functions
    FSkillTree CreateDefaultSkillTree(const FString& Name);
    FSkillVisualVariant CreateVisualVariant(const FString& Name, ESkillElement Element);
    FSkillUpgradeNode CreateUpgradeNode(const FString& Name, int32 RequiredLevel, int32 SkillPoints);
    void ApplyModificationsToSkill(FCustomizedSkill& Skill);
    void NotifySkillCustomized(const FCustomizedSkill& Skill);
    void NotifySkillUpgraded(const FString& SkillName, int32 NewLevel);
    void NotifyVisualVariantUnlocked(const FSkillVisualVariant& Variant);
    void NotifySkillTreeUnlocked(const FString& TreeName);
    bool ValidateSkillModification(const FSkillModification& Modification);
    int32 CalculateExperienceRequirement(int32 Level) const;
};
