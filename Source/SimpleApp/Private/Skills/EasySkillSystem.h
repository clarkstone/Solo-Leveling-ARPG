#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "SkillCustomization.h"
#include "EasySkillSystem.generated.h"

UENUM(BlueprintType)
enum class ESkillSlotType : uint8
{
    SST_Primary = 0,     // Main combat skills
    SST_Secondary,       // Support/utility skills
    SST_Utility,         // Movement and defensive skills
    SST_Ultimate,        // Powerful cooldown abilities
    SST_Passive,         // Always-active passive skills
    SST_Reaction,        // Triggered response skills
    SST_Contextual,      // Situation-dependent skills
    SST_Custom
};

UENUM(BlueprintType)
enum class ESkillUsagePattern : uint8
{
    SUP_Spammable = 0,   // Low cooldown, basic damage/utility
    SUP_Situational,     // Used in specific situations
    SUP_Burst,           // High damage, long cooldown
    SUP_Sustained,        // DoT or continuous effects
    SUP_Control,          // CC and debuffs
    SUP_Mobility,         // Movement and positioning
    SUP_Defensive,        // Protection and healing
    SUP_Hybrid           // Multiple uses
};

USTRUCT(BlueprintType)
struct FEasySkillSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Easy Skill Slot")
    ESkillSlotType SlotType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Easy Skill Slot")
    FString SlotName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Easy Skill Slot")
    int32 SlotIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Easy Skill Slot")
    FString CurrentSkillID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Easy Skill Slot")
    bool bIsLocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Easy Skill Slot")
    int32 UnlockLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Easy Skill Slot")
    UTexture2D* SlotIcon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Easy Skill Slot")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Easy Skill Slot")
    TArray<FString> RecommendedSkills;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Easy Skill Slot")
    bool bAutoSwap;
};

USTRUCT(BlueprintType)
struct FSkillRecommendation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Recommendation")
    FString SkillID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Recommendation")
    FString SkillName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Recommendation")
    ESkillUsagePattern UsagePattern;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Recommendation")
    float RecommendationScore;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Recommendation")
    FString Reason;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Recommendation")
    TArray<FString> SynergySkills;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Recommendation")
    bool bIsNew;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Recommendation")
    UTexture2D* SkillIcon;
};

USTRUCT(BlueprintType)
struct FSkillCombo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Combo")
    FString ComboName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Combo")
    TArray<FString> SkillSequence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Combo")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Combo")
    float DamageMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Combo")
    TArray<FString> AdditionalEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Combo")
    bool bIsDiscovered;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Combo")
    int32 TimesUsed;

    UPROPERTY(EditAwareAnywhere, BlueprintReadWrite, Category = "Skill Combo")
    UTexture2D* ComboIcon;
};

USTRUCT(BlueprintType)
struct FSkillLoadout
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Loadout")
    FString LoadoutName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Loadout")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Loadout")
    TMap<ESkillSlotType, FString> AssignedSkills;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Loadout")
    TArray<FString> TaggedSkills;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Loadout")
    bool bIsActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Loadout")
    bool bIsFavorite;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Loadout")
    int32 UsageCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Loadout")
    float WinRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Loadout")
    UTexture2D* LoadoutIcon;
};

UCLASS(BlueprintType, Blueprintable)
class SIMPLEAPP_API UEasySkillSystem : public UActorComponent
{
    GENERATED_BODY()

public:
    UEasySkillSystem();

    // Easy Skill System Events
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillSlotChanged, const FEasySkillSlot&, SkillSlot);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillRecommended, const FSkillRecommendation&, Recommendation);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComboDiscovered, const FSkillCombo&, Combo);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadoutSwitched, const FSkillLoadout&, Loadout);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillUsed, const FString&, SkillID, ESkillUsagePattern, UsagePattern);

    UPROPERTY(BlueprintAssignable, Category = "Easy Skill System Events")
    FOnSkillSlotChanged OnSkillSlotChanged;

    UPROPERTY(BlueprintAssignable, Category = "Easy Skill System Events")
    FOnSkillRecommended OnSkillRecommended;

    UPROPERTY(BlueprintAssignable, Category = "Easy Skill System Events")
    FOnComboDiscovered OnComboDiscovered;

    UPROPERTY(BlueprintAssignable, Category = "Easy Skill System Events")
    FOnLoadoutSwitched OnLoadoutSwitched;

    UPROPERTY(BlueprintAssignable, Category = "Easy Skill System Events")
    FOnSkillUsed OnSkillUsed;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Easy Skill Management
    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    void InitializeEasySkillSystem();

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TArray<FEasySkillSlot> GetSkillSlots() const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    FEasySkillSlot GetSkillSlot(ESkillSlotType SlotType) const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    bool AssignSkillToSlot(const FString& SkillID, ESkillSlotType SlotType);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    bool RemoveSkillFromSlot(ESkillSlotType SlotType);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    FString GetSkillInSlot(ESkillSlotType SlotType) const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    bool IsSlotLocked(ESkillSlotType SlotType) const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    bool UnlockSlot(ESkillSlotType SlotType);

    // Smart Recommendations
    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TArray<FSkillRecommendation> GetSkillRecommendations() const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TArray<FSkillRecommendation> GetRecommendationsForSlot(ESkillSlotType SlotType) const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TArray<FSkillRecommendation> GetSynergyRecommendations(const FString& SkillID) const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TArray<FSkillRecommendation> GetSituationRecommendations(const FString& Situation) const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    bool ApplyRecommendation(const FString& SkillID, ESkillSlotType SlotType);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    void UpdateRecommendations();

    // Skill Combos
    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TArray<FSkillCombo> GetDiscoveredCombos() const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TArray<FSkillCombo> GetAvailableCombos() const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    bool DiscoverCombo(const TArray<FString>& SkillSequence);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    FSkillCombo GetCombo(const FString& ComboName) const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    void UseCombo(const FString& ComboName);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TArray<FString> GetComboSuggestions() const;

    // Loadout Management
    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TArray<FSkillLoadout> GetSkillLoadouts() const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    bool CreateLoadout(const FString& LoadoutName, const FString& Description);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    bool SaveCurrentLoadout(const FString& LoadoutName);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    bool SwitchToLoadout(const FString& LoadoutName);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    bool DeleteLoadout(const FString& LoadoutName);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    FSkillLoadout GetCurrentLoadout() const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    void SetFavoriteLoadout(const FString& LoadoutName, bool bIsFavorite);

    // Quick Access Features
    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TArray<FString> GetQuickAccessSkills() const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    bool AddToQuickAccess(const FString& SkillID);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    bool RemoveFromQuickAccess(const FString& SkillID);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    void RotateQuickAccess();

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    void AutoArrangeSkills();

    // Context-Aware Features
    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TArray<FString> GetContextualSkills(const FString& Context) const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    FString GetBestSkillForSituation(const FString& Situation) const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    void UpdateContext(const FString& NewContext);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    FString GetCurrentContext() const;

    // Skill Usage Analysis
    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TMap<FString, int32> GetSkillUsageStats() const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TArray<FString> GetMostUsedSkills() const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TArray<FString> GetLeastUsedSkills() const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    void RecordSkillUsage(const FString& SkillID, ESkillUsagePattern UsagePattern);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    float GetSkillEfficiency(const FString& SkillID) const;

    // Auto-Swapping Features
    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    void EnableAutoSwap(ESkillSlotType SlotType, bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    bool IsAutoSwapEnabled(ESkillSlotType SlotType) const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    void ProcessAutoSwap();

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    FString GetAutoSwapSuggestion(ESkillSlotType SlotType) const;

    // Tutorial and Help
    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    TArray<FString> GetSkillTips() const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    FString GetSkillHelp(const FString& SkillID) const;

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    void ShowSkillTutorial(const FString& SkillID);

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    bool HasCompletedTutorial() const;

    // Save/Load
    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    void SaveEasySkillSystem();

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    void LoadEasySkillSystem();

    UFUNCTION(BlueprintCallable, Category = "Easy Skill System")
    void ResetEasySkillSystem();

protected:
    // Internal Functions
    void InitializeSkillSlots();
    void InitializeSkillCombos();
    void InitializeDefaultLoadouts();
    void UpdateSkillRecommendations();
    void AnalyzeSkillUsage();
    void ProcessContextChanges();
    void UpdateAutoSwapLogic();

private:
    // Internal State
    TArray<FEasySkillSlot> SkillSlots;
    TArray<FSkillRecommendation> CurrentRecommendations;
    TArray<FSkillCombo> DiscoveredCombos;
    TArray<FSkillCombo> AvailableCombos;
    TArray<FSkillLoadout> SkillLoadouts;
    TArray<FString> QuickAccessSkills;
    TMap<ESkillSlotType, bool> AutoSwapEnabled;
    
    // Usage Tracking
    TMap<FString, int32> SkillUsageCount;
    TMap<FString, ESkillUsagePattern> SkillUsagePattern;
    TMap<FString, float> SkillEfficiency;
    TMap<FString, TArray<FString>> SkillSynergies;
    
    // Context System
    FString CurrentContext;
    TArray<FString> RecentSkillUsage;
    float LastContextUpdate;
    
    // Loadout Management
    FString CurrentLoadoutName;
    int32 MaxQuickAccessSlots;
    bool bTutorialCompleted;

    // Helper Functions
    FEasySkillSlot CreateSkillSlot(ESkillSlotType Type, const FString& Name, int32 Index);
    FSkillRecommendation CreateRecommendation(const FString& SkillID, float Score, const FString& Reason);
    FSkillCombo CreateCombo(const FString& Name, const TArray<FString>& Sequence);
    FSkillLoadout CreateLoadout(const FString& Name, const FString& Description);
    void NotifySkillSlotChanged(const FEasySkillSlot& SkillSlot);
    void NotifySkillRecommended(const FSkillRecommendation& Recommendation);
    void NotifyComboDiscovered(const FSkillCombo& Combo);
    void NotifyLoadoutSwitched(const FSkillLoadout& Loadout);
    void NotifySkillUsed(const FString& SkillID, ESkillUsagePattern UsagePattern);
    float CalculateRecommendationScore(const FString& SkillID, ESkillSlotType SlotType) const;
    TArray<FString> GetAvailableSkills() const;
    bool ValidateSkillAssignment(const FString& SkillID, ESkillSlotType SlotType) const;
    void UpdateSkillSynergies();
    void GenerateComboSuggestions();
    void OptimizeLoadout();
    FString GetBestSkillForSlot(ESkillSlotType SlotType) const;
    void UpdateSkillEfficiency(const FString& SkillID);
    void ProcessSkillCombo(const TArray<FString>& RecentSkills);
    void UpdateQuickAccessRotation();
};
