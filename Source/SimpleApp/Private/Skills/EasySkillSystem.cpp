#include "EasySkillSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Net/UnrealNetwork.h"

UEasySkillSystem::UEasySkillSystem()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);
    
    MaxQuickAccessSlots = 8;
    bTutorialCompleted = false;
    LastContextUpdate = 0.0f;
}

void UEasySkillSystem::BeginPlay()
{
    Super::BeginPlay();
    InitializeEasySkillSystem();
}

void UEasySkillSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    UpdateSkillRecommendations();
    ProcessAutoSwap();
    ProcessContextChanges();
    UpdateQuickAccessRotation();
}

void UEasySkillSystem::InitializeEasySkillSystem()
{
    UE_LOG(LogTemp, Warning, TEXT("Easy Skill System initialized"));
    
    InitializeSkillSlots();
    InitializeSkillCombos();
    InitializeDefaultLoadouts();
    LoadEasySkillSystem();
    
    UE_LOG(LogTemp, Warning, TEXT("Easy Skill System ready"));
}

TArray<FEasySkillSlot> UEasySkillSystem::GetSkillSlots() const
{
    return SkillSlots;
}

bool UEasySkillSystem::AssignSkillToSlot(const FString& SkillID, ESkillSlotType SlotType)
{
    if (!ValidateSkillAssignment(SkillID, SlotType))
    {
        return false;
    }
    
    for (FEasySkillSlot& Slot : SkillSlots)
    {
        if (Slot.SlotType == SlotType)
        {
            Slot.CurrentSkillID = SkillID;
            NotifySkillSlotChanged(Slot);
            return true;
        }
    }
    
    return false;
}

TArray<FSkillRecommendation> UEasySkillSystem::GetSkillRecommendations() const
{
    return CurrentRecommendations;
}

void UEasySkillSystem::UpdateRecommendations()
{
    CurrentRecommendations.Empty();
    
    TArray<FString> AvailableSkills = GetAvailableSkills();
    
    for (const FString& SkillID : AvailableSkills)
    {
        for (const FEasySkillSlot& Slot : SkillSlots)
        {
            if (!Slot.bIsLocked)
            {
                float Score = CalculateRecommendationScore(SkillID, Slot.SlotType);
                
                if (Score > 0.6f)
                {
                    FSkillRecommendation Recommendation = CreateRecommendation(
                        SkillID, Score, FString::Printf(TEXT("Good fit for %s"), *Slot.SlotName)
                    );
                    
                    CurrentRecommendations.Add(Recommendation);
                }
            }
        }
    }
    
    CurrentRecommendations.Sort([](const FSkillRecommendation& A, const FSkillRecommendation& B)
    {
        return A.RecommendationScore > B.RecommendationScore;
    });
}

void UEasySkillSystem::RecordSkillUsage(const FString& SkillID, ESkillUsagePattern UsagePattern)
{
    if (!SkillUsageCount.Contains(SkillID))
    {
        SkillUsageCount.Add(SkillID, 0);
    }
    SkillUsageCount[SkillID]++;
    
    SkillUsagePattern.Add(SkillID, UsagePattern);
    
    RecentSkillUsage.Add(SkillID);
    if (RecentSkillUsage.Num() > 10)
    {
        RecentSkillUsage.RemoveAt(0);
    }
    
    UpdateSkillEfficiency(SkillID);
    ProcessSkillCombo(RecentSkillUsage);
    
    NotifySkillUsed(SkillID, UsagePattern);
}

TArray<FString> UEasySkillSystem::GetQuickAccessSkills() const
{
    return QuickAccessSkills;
}

bool UEasySkillSystem::AddToQuickAccess(const FString& SkillID)
{
    if (QuickAccessSkills.Num() >= MaxQuickAccessSlots)
    {
        return false;
    }
    
    if (!QuickAccessSkills.Contains(SkillID))
    {
        QuickAccessSkills.Add(SkillID);
        return true;
    }
    
    return false;
}

void UEasySkillSystem::AutoArrangeSkills()
{
    TArray<FSkillRecommendation> AllRecommendations = GetSkillRecommendations();
    
    for (FEasySkillSlot& Slot : SkillSlots)
    {
        if (!Slot.bIsLocked && Slot.CurrentSkillID.IsEmpty())
        {
            for (const FSkillRecommendation& Recommendation : AllRecommendations)
            {
                if (CalculateRecommendationScore(Recommendation.SkillID, Slot.SlotType) > 0.7f)
                {
                    AssignSkillToSlot(Recommendation.SkillID, Slot.SlotType);
                    break;
                }
            }
        }
    }
}

TArray<FString> UEasySkillSystem::GetContextualSkills(const FString& Context) const
{
    TArray<FString> ContextualSkills;
    TArray<FString> AvailableSkills = GetAvailableSkills();
    
    for (const FString& SkillID : AvailableSkills)
    {
        bool bIsRelevant = false;
        
        if (Context == TEXT("Combat"))
        {
            bIsRelevant = SkillID.Contains(TEXT("Attack")) || SkillID.Contains(TEXT("Fire"));
        }
        else if (Context == TEXT("Exploration"))
        {
            bIsRelevant = SkillID.Contains(TEXT("Dash")) || SkillID.Contains(TEXT("Detect"));
        }
        
        if (bIsRelevant)
        {
            ContextualSkills.Add(SkillID);
        }
    }
    
    return ContextualSkills;
}

void UEasySkillSystem::UpdateContext(const FString& NewContext)
{
    CurrentContext = NewContext;
    LastContextUpdate = GetWorld()->GetTimeSeconds();
    UpdateRecommendations();
}

void UEasySkillSystem::ProcessAutoSwap()
{
    for (const FEasySkillSlot& Slot : SkillSlots)
    {
        if (IsAutoSwapEnabled(Slot.SlotType) && !Slot.bIsLocked)
        {
            FString SuggestedSkill = GetAutoSwapSuggestion(Slot.SlotType);
            
            if (!SuggestedSkill.IsEmpty() && SuggestedSkill != Slot.CurrentSkillID)
            {
                AssignSkillToSlot(SuggestedSkill, Slot.SlotType);
            }
        }
    }
}

FString UEasySkillSystem::GetAutoSwapSuggestion(ESkillSlotType SlotType) const
{
    return GetBestSkillForSlot(SlotType);
}

void UEasySkillSystem::InitializeSkillSlots()
{
    SkillSlots.Empty();
    
    SkillSlots.Add(CreateSkillSlot(ESkillSlotType::SST_Primary, TEXT("Primary Attack"), 0));
    SkillSlots.Add(CreateSkillSlot(ESkillSlotType::SST_Secondary, TEXT("Secondary Attack"), 1));
    SkillSlots.Add(CreateSkillSlot(ESkillSlotType::SST_Utility, TEXT("Utility"), 2));
    SkillSlots.Add(CreateSkillSlot(ESkillSlotType::SST_Ultimate, TEXT("Ultimate"), 3));
    
    SkillSlots[0].bIsLocked = false;
    SkillSlots[1].bIsLocked = false;
    
    AutoSwapEnabled.Add(ESkillSlotType::SST_Utility, true);
}

FEasySkillSlot UEasySkillSystem::CreateSkillSlot(ESkillSlotType Type, const FString& Name, int32 Index)
{
    FEasySkillSlot Slot;
    Slot.SlotType = Type;
    Slot.SlotName = Name;
    Slot.SlotIndex = Index;
    Slot.CurrentSkillID = TEXT("");
    Slot.bIsLocked = true;
    Slot.UnlockLevel = 1;
    Slot.bAutoSwap = false;
    
    return Slot;
}

FSkillRecommendation UEasySkillSystem::CreateRecommendation(const FString& SkillID, float Score, const FString& Reason)
{
    FSkillRecommendation Recommendation;
    Recommendation.SkillID = SkillID;
    Recommendation.SkillName = SkillID;
    Recommendation.RecommendationScore = Score;
    Recommendation.Reason = Reason;
    
    return Recommendation;
}

float UEasySkillSystem::CalculateRecommendationScore(const FString& SkillID, ESkillSlotType SlotType) const
{
    float Score = 0.0f;
    
    if (SlotType == ESkillSlotType::SST_Primary)
    {
        if (SkillID.Contains(TEXT("Attack")) || SkillID.Contains(TEXT("Strike")))
        {
            Score = 0.9f;
        }
    }
    else if (SlotType == ESkillSlotType::SST_Utility)
    {
        if (SkillID.Contains(TEXT("Dash")) || SkillID.Contains(TEXT("Teleport")))
        {
            Score = 0.9f;
        }
    }
    
    if (SkillEfficiency.Contains(SkillID))
    {
        Score *= SkillEfficiency[SkillID];
    }
    
    return FMath::Clamp(Score, 0.0f, 1.0f);
}

TArray<FString> UEasySkillSystem::GetAvailableSkills() const
{
    TArray<FString> AvailableSkills;
    AvailableSkills.Add(TEXT("Basic Attack"));
    AvailableSkills.Add(TEXT("Heavy Strike"));
    AvailableSkills.Add(TEXT("Fireball"));
    AvailableSkills.Add(TEXT("Ice Bolt"));
    AvailableSkills.Add(TEXT("Lightning Strike"));
    AvailableSkills.Add(TEXT("Dash"));
    AvailableSkills.Add(TEXT("Teleport"));
    AvailableSkills.Add(TEXT("Shield"));
    AvailableSkills.Add(TEXT("Heal"));
    
    return AvailableSkills;
}

bool UEasySkillSystem::ValidateSkillAssignment(const FString& SkillID, ESkillSlotType SlotType) const
{
    TArray<FString> AvailableSkills = GetAvailableSkills();
    return AvailableSkills.Contains(SkillID);
}

void UEasySkillSystem::UpdateSkillEfficiency(const FString& SkillID)
{
    if (!SkillUsageCount.Contains(SkillID))
    {
        SkillEfficiency.Add(SkillID, 0.0f);
        return;
    }
    
    int32 UsageCount = SkillUsageCount[SkillID];
    float Efficiency = FMath::Clamp(UsageCount / 100.0f, 0.0f, 1.0f);
    
    SkillEfficiency[SkillID] = Efficiency;
}

void UEasySkillSystem::ProcessSkillCombo(const TArray<FString>& RecentSkills)
{
    if (RecentSkills.Num() >= 2)
    {
        TArray<FString> LastTwoSkills;
        LastTwoSkills.Add(RecentSkills[RecentSkills.Num() - 2]);
        LastTwoSkills.Add(RecentSkills[RecentSkills.Num() - 1]);
        
        DiscoverCombo(LastTwoSkills);
    }
}

void UEasySkillSystem::InitializeSkillCombos()
{
    AvailableCombos.Empty();
    
    TArray<FString> FireIceCombo;
    FireIceCombo.Add(TEXT("Fireball"));
    FireIceCombo.Add(TEXT("Ice Bolt"));
    AvailableCombos.Add(CreateCombo(TEXT("Fire + Ice"), FireIceCombo));
}

FSkillCombo UEasySkillSystem::CreateCombo(const FString& Name, const TArray<FString>& Sequence)
{
    FSkillCombo Combo;
    Combo.ComboName = Name;
    Combo.SkillSequence = Sequence;
    Combo.DamageMultiplier = 1.5f;
    Combo.bIsDiscovered = false;
    Combo.TimesUsed = 0;
    
    return Combo;
}

void UEasySkillSystem::NotifySkillSlotChanged(const FEasySkillSlot& SkillSlot)
{
    OnSkillSlotChanged.Broadcast(SkillSlot);
}

void UEasySkillSystem::NotifySkillUsed(const FString& SkillID, ESkillUsagePattern UsagePattern)
{
    OnSkillUsed.Broadcast(SkillID, UsagePattern);
}

void UEasySkillSystem::UpdateQuickAccessRotation()
{
    // Rotate quick access skills periodically
}

void UEasySkillSystem::ProcessContextChanges()
{
    float CurrentTime = GetWorld()->GetTimeSeconds();
    
    if (CurrentTime - LastContextUpdate > 5.0f)
    {
        UpdateRecommendations();
        LastContextUpdate = CurrentTime;
    }
}

void UEasySkillSystem::InitializeDefaultLoadouts()
{
    // Initialize default loadouts
}

FString UEasySkillSystem::GetBestSkillForSlot(ESkillSlotType SlotType) const
{
    TArray<FSkillRecommendation> SlotRecommendations = GetRecommendationsForSlot(SlotType);
    
    if (SlotRecommendations.Num() > 0)
    {
        return SlotRecommendations[0].SkillID;
    }
    
    return TEXT("");
}

TArray<FSkillRecommendation> UEasySkillSystem::GetRecommendationsForSlot(ESkillSlotType SlotType) const
{
    TArray<FSkillRecommendation> SlotRecommendations;
    
    for (const FSkillRecommendation& Recommendation : CurrentRecommendations)
    {
        if (CalculateRecommendationScore(Recommendation.SkillID, SlotType) > 0.5f)
        {
            SlotRecommendations.Add(Recommendation);
        }
    }
    
    return SlotRecommendations;
}

bool UEasySkillSystem::IsAutoSwapEnabled(ESkillSlotType SlotType) const
{
    if (AutoSwapEnabled.Contains(SlotType))
    {
        return AutoSwapEnabled[SlotType];
    }
    
    return false;
}

void UEasySkillSystem::SaveEasySkillSystem()
{
    UE_LOG(LogTemp, Warning, TEXT("Easy skill system saved"));
}

void UEasySkillSystem::LoadEasySkillSystem()
{
    UE_LOG(LogTemp, Warning, TEXT("Easy skill system loaded"));
}

void UEasySkillSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UEasySkillSystem, SkillSlots);
    DOREPLIFETIME(UEasySkillSystem, CurrentRecommendations);
    DOREPLIFETIME(UEasySkillSystem, DiscoveredCombos);
    DOREPLIFETIME(UEasySkillSystem, SkillLoadouts);
    DOREPLIFETIME(UEasySkillSystem, QuickAccessSkills);
    DOREPLIFETIME(UEasySkillSystem, SkillUsageCount);
    DOREPLIFETIME(UEasySkillSystem, AutoSwapEnabled);
}
