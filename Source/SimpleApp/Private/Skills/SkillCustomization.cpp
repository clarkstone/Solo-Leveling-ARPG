#include "SkillCustomization.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Net/UnrealNetwork.h"

USkillCustomization::USkillCustomization()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);
    
    TotalSkillPoints = 0;
}

void USkillCustomization::BeginPlay()
{
    Super::BeginPlay();
    InitializeSkillCustomization();
}

void USkillCustomization::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USkillCustomization::InitializeSkillCustomization()
{
    UE_LOG(LogTemp, Warning, TEXT("Skill Customization System initialized"));
    
    // Initialize all skill systems
    InitializeSkillTrees();
    InitializeVisualVariants();
    InitializeAshesOfWar();
    InitializeRunes();
    
    // Load saved customization
    LoadSkillCustomization();
    
    UE_LOG(LogTemp, Warning, TEXT("Skill Customization System ready"));
}

FCustomizedSkill USkillCustomization::GetCustomizedSkill(const FString& SkillName) const
{
    if (CustomizedSkills.Contains(SkillName))
    {
        return CustomizedSkills[SkillName];
    }
    
    // Return empty skill if not found
    FCustomizedSkill EmptySkill;
    return EmptySkill;
}

TArray<FCustomizedSkill> USkillCustomization::GetAllCustomizedSkills() const
{
    TArray<FCustomizedSkill> AllSkills;
    
    for (const auto& SkillPair : CustomizedSkills)
    {
        AllSkills.Add(SkillPair.Value);
    }
    
    return AllSkills;
}

void USkillCustomization::AddSkillToCustomization(const FString& SkillName)
{
    if (CustomizedSkills.Contains(SkillName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Skill already in customization: %s"), *SkillName);
        return;
    }
    
    FCustomizedSkill NewSkill;
    NewSkill.BaseSkillName = SkillName;
    NewSkill.CurrentElement = ESkillElement::SE_None;
    NewSkill.SkillLevel = 1;
    NewSkill.Experience = 0;
    NewSkill.bIsFavorite = false;
    NewSkill.SlotIndex = -1;
    
    // Set default visual variant
    if (VisualVariants.Contains(SkillName) && VisualVariants[SkillName].Num() > 0)
    {
        NewSkill.CurrentVisualVariant = VisualVariants[SkillName][0];
    }
    
    CustomizedSkills.Add(SkillName, NewSkill);
    
    UE_LOG(LogTemp, Warning, TEXT("Skill added to customization: %s"), *SkillName);
    NotifySkillCustomized(NewSkill);
}

void USkillCustomization::RemoveSkillFromCustomization(const FString& SkillName)
{
    if (!CustomizedSkills.Contains(SkillName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Skill not found in customization: %s"), *SkillName);
        return;
    }
    
    CustomizedSkills.Remove(SkillName);
    
    // Remove from assigned slots
    for (int32 i = 0; i < AssignedSkillSlots.Num(); i++)
    {
        if (AssignedSkillSlots[i] == SkillName)
        {
            AssignedSkillSlots[i] = TEXT("");
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Skill removed from customization: %s"), *SkillName);
}

TArray<FSkillTree> USkillCustomization::GetAvailableSkillTrees() const
{
    return SkillTrees;
}

bool USkillCustomization::UnlockSkillTree(const FString& TreeName)
{
    for (FSkillTree& Tree : SkillTrees)
    {
        if (Tree.TreeName == TreeName && !Tree.bIsTreeUnlocked)
        {
            Tree.bIsTreeUnlocked = true;
            NotifySkillTreeUnlocked(TreeName);
            UE_LOG(LogTemp, Warning, TEXT("Skill tree unlocked: %s"), *TreeName);
            return true;
        }
    }
    
    return false;
}

bool USkillCustomization::IsSkillTreeUnlocked(const FString& TreeName) const
{
    for (const FSkillTree& Tree : SkillTrees)
    {
        if (Tree.TreeName == TreeName)
        {
            return Tree.bIsTreeUnlocked;
        }
    }
    
    return false;
}

int32 USkillCustomization::GetAvailableSkillPoints(const FString& TreeName) const
{
    for (const FSkillTree& Tree : SkillTrees)
    {
        if (Tree.TreeName == TreeName)
        {
            return Tree.TotalSkillPoints - Tree.UsedSkillPoints;
        }
    }
    
    return 0;
}

bool USkillCustomization::UpgradeSkillNode(const FString& TreeName, const FString& NodeName)
{
    if (!CanUpgradeSkillNode(TreeName, NodeName))
    {
        return false;
    }
    
    for (FSkillTree& Tree : SkillTrees)
    {
        if (Tree.TreeName == TreeName)
        {
            for (FSkillUpgradeNode& Node : Tree.Nodes)
            {
                if (Node.NodeName == NodeName && !Node.bIsUnlocked)
                {
                    Node.bIsUnlocked = true;
                    Tree.UsedSkillPoints += Node.SkillPointsRequired;
                    
                    // Apply modifications to relevant skills
                    ApplyModificationsToSkill(CustomizedSkills[NodeName]);
                    
                    NotifySkillUpgraded(NodeName, Node.bIsUnlocked ? 1 : 0);
                    UE_LOG(LogTemp, Warning, TEXT("Skill node upgraded: %s in tree %s"), *NodeName, *TreeName);
                    return true;
                }
            }
        }
    }
    
    return false;
}

bool USkillCustomization::CanUpgradeSkillNode(const FString& TreeName, const FString& NodeName) const
{
    for (const FSkillTree& Tree : SkillTrees)
    {
        if (Tree.TreeName == TreeName)
        {
            if (!Tree.bIsTreeUnlocked)
            {
                return false;
            }
            
            for (const FSkillUpgradeNode& Node : Tree.Nodes)
            {
                if (Node.NodeName == NodeName)
                {
                    if (Node.bIsUnlocked)
                    {
                        return false;
                    }
                    
                    if (Tree.TotalSkillPoints - Tree.UsedSkillPoints < Node.SkillPointsRequired)
                    {
                        return false;
                    }
                    
                    // Check prerequisites
                    for (const FString& Prerequisite : Node.PrerequisiteNodes)
                    {
                        bool bPrerequisiteMet = false;
                        for (const FSkillUpgradeNode& CheckNode : Tree.Nodes)
                        {
                            if (CheckNode.NodeName == Prerequisite && CheckNode.bIsUnlocked)
                            {
                                bPrerequisiteMet = true;
                                break;
                            }
                        }
                        
                        if (!bPrerequisiteMet)
                        {
                            return false;
                        }
                    }
                    
                    return true;
                }
            }
        }
    }
    
    return false;
}

TArray<FSkillUpgradeNode> USkillCustomization::GetAvailableNodes(const FString& TreeName) const
{
    TArray<FSkillUpgradeNode> AvailableNodes;
    
    for (const FSkillTree& Tree : SkillTrees)
    {
        if (Tree.TreeName == TreeName)
        {
            for (const FSkillUpgradeNode& Node : Tree.Nodes)
            {
                if (!Node.bIsUnlocked && CanUpgradeSkillNode(TreeName, Node.NodeName))
                {
                    AvailableNodes.Add(Node);
                }
            }
        }
    }
    
    return AvailableNodes;
}

TArray<FSkillUpgradeNode> USkillCustomization::GetUnlockedNodes(const FString& TreeName) const
{
    TArray<FSkillUpgradeNode> UnlockedNodes;
    
    for (const FSkillTree& Tree : SkillTrees)
    {
        if (Tree.TreeName == TreeName)
        {
            for (const FSkillUpgradeNode& Node : Tree.Nodes)
            {
                if (Node.bIsUnlocked)
                {
                    UnlockedNodes.Add(Node);
                }
            }
        }
    }
    
    return UnlockedNodes;
}

bool USkillCustomization::ChangeSkillElement(const FString& SkillName, ESkillElement NewElement)
{
    if (!CustomizedSkills.Contains(SkillName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Skill not found for element change: %s"), *SkillName);
        return false;
    }
    
    TArray<ESkillElement> AvailableElements = GetAvailableElements(SkillName);
    if (!AvailableElements.Contains(NewElement))
    {
        UE_LOG(LogTemp, Warning, TEXT("Element not available for skill %s"), *SkillName);
        return false;
    }
    
    FCustomizedSkill& Skill = CustomizedSkills[SkillName];
    Skill.CurrentElement = NewElement;
    
    // Update visual variant to match element
    if (VisualVariants.Contains(SkillName))
    {
        for (const FSkillVisualVariant& Variant : VisualVariants[SkillName])
        {
            if (Variant.Element == NewElement)
            {
                Skill.CurrentVisualVariant = Variant;
                break;
            }
        }
    }
    
    UpdateSkillEffects(SkillName);
    NotifySkillCustomized(Skill);
    
    UE_LOG(LogTemp, Warning, TEXT("Skill element changed: %s to %d"), *SkillName, (int32)NewElement);
    return true;
}

ESkillElement USkillCustomization::GetSkillElement(const FString& SkillName) const
{
    if (CustomizedSkills.Contains(SkillName))
    {
        return CustomizedSkills[SkillName].CurrentElement;
    }
    
    return ESkillElement::SE_None;
}

TArray<ESkillElement> USkillCustomization::GetAvailableElements(const FString& SkillName) const
{
    TArray<ESkillElement> AvailableElements;
    
    if (VisualVariants.Contains(SkillName))
    {
        for (const FSkillVisualVariant& Variant : VisualVariants[SkillName])
        {
            if (Variant.bIsUnlocked && !AvailableElements.Contains(Variant.Element))
            {
                AvailableElements.Add(Variant.Element);
            }
        }
    }
    
    return AvailableElements;
}

TArray<FSkillVisualVariant> USkillCustomization::GetAvailableVisualVariants(const FString& SkillName) const
{
    if (VisualVariants.Contains(SkillName))
    {
        return VisualVariants[SkillName];
    }
    
    return TArray<FSkillVisualVariant>();
}

bool USkillCustomization::ApplyVisualVariant(const FString& SkillName, const FString& VariantName)
{
    if (!CustomizedSkills.Contains(SkillName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Skill not found for visual variant: %s"), *SkillName);
        return false;
    }
    
    if (!VisualVariants.Contains(SkillName))
    {
        UE_LOG(LogTemp, Warning, TEXT("No visual variants found for skill: %s"), *SkillName);
        return false;
    }
    
    for (const FSkillVisualVariant& Variant : VisualVariants[SkillName])
    {
        if (Variant.VariantName == VariantName && Variant.bIsUnlocked)
        {
            FCustomizedSkill& Skill = CustomizedSkills[SkillName];
            Skill.CurrentVisualVariant = Variant;
            Skill.CurrentElement = Variant.Element;
            
            UpdateSkillEffects(SkillName);
            NotifySkillCustomized(Skill);
            
            UE_LOG(LogTemp, Warning, TEXT("Visual variant applied: %s to skill %s"), *VariantName, *SkillName);
            return true;
        }
    }
    
    return false;
}

bool USkillCustomization::UnlockVisualVariant(const FString& SkillName, const FString& VariantName)
{
    if (!VisualVariants.Contains(SkillName))
    {
        return false;
    }
    
    for (FSkillVisualVariant& Variant : VisualVariants[SkillName])
    {
        if (Variant.VariantName == VariantName && !Variant.bIsUnlocked)
        {
            Variant.bIsUnlocked = true;
            NotifyVisualVariantUnlocked(Variant);
            UE_LOG(LogTemp, Warning, TEXT("Visual variant unlocked: %s for skill %s"), *VariantName, *SkillName);
            return true;
        }
    }
    
    return false;
}

FSkillVisualVariant USkillCustomization::GetCurrentVisualVariant(const FString& SkillName) const
{
    if (CustomizedSkills.Contains(SkillName))
    {
        return CustomizedSkills[SkillName].CurrentVisualVariant;
    }
    
    FSkillVisualVariant EmptyVariant;
    return EmptyVariant;
}

bool USkillCustomization::ApplySkillModification(const FString& SkillName, const FSkillModification& Modification)
{
    if (!CustomizedSkills.Contains(SkillName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Skill not found for modification: %s"), *SkillName);
        return false;
    }
    
    if (!ValidateSkillModification(Modification))
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid skill modification"));
        return false;
    }
    
    FCustomizedSkill& Skill = CustomizedSkills[SkillName];
    
    // Remove existing modification of the same type
    for (int32 i = 0; i < Skill.AppliedModifications.Num(); i++)
    {
        if (Skill.AppliedModifications[i].ModificationType == Modification.ModificationType)
        {
            Skill.AppliedModifications.RemoveAt(i);
            break;
        }
    }
    
    // Add new modification
    Skill.AppliedModifications.Add(Modification);
    
    UpdateSkillEffects(SkillName);
    NotifySkillCustomized(Skill);
    
    UE_LOG(LogTemp, Warning, TEXT("Skill modification applied: %d to skill %s"), (int32)Modification.ModificationType, *SkillName);
    return true;
}

bool USkillCustomization::RemoveSkillModification(const FString& SkillName, ESkillModificationType ModificationType)
{
    if (!CustomizedSkills.Contains(SkillName))
    {
        return false;
    }
    
    FCustomizedSkill& Skill = CustomizedSkills[SkillName];
    
    for (int32 i = 0; i < Skill.AppliedModifications.Num(); i++)
    {
        if (Skill.AppliedModifications[i].ModificationType == ModificationType)
        {
            Skill.AppliedModifications.RemoveAt(i);
            UpdateSkillEffects(SkillName);
            NotifySkillCustomized(Skill);
            UE_LOG(LogTemp, Warning, TEXT("Skill modification removed: %d from skill %s"), (int32)ModificationType, *SkillName);
            return true;
        }
    }
    
    return false;
}

TArray<FSkillModification> USkillCustomization::GetAppliedModifications(const FString& SkillName) const
{
    if (CustomizedSkills.Contains(SkillName))
    {
        return CustomizedSkills[SkillName].AppliedModifications;
    }
    
    return TArray<FSkillModification>();
}

float USkillCustomization::GetModifiedSkillValue(const FString& SkillName, ESkillModificationType ModificationType, float BaseValue) const
{
    if (!CustomizedSkills.Contains(SkillName))
    {
        return BaseValue;
    }
    
    const FCustomizedSkill& Skill = CustomizedSkills[SkillName];
    float ModifiedValue = BaseValue;
    
    for (const FSkillModification& Modification : Skill.AppliedModifications)
    {
        if (Modification.ModificationType == ModificationType)
        {
            if (Modification.bIsPercentage)
            {
                ModifiedValue *= (1.0f + Modification.ModificationValue / 100.0f);
            }
            else
            {
                ModifiedValue += Modification.ModificationValue;
            }
        }
    }
    
    return ModifiedValue;
}

TArray<FString> USkillCustomization::GetAvailableAshesOfWar() const
{
    TArray<FString> AvailableAshes;
    
    for (const auto& AshPair : AshesOfWar)
    {
        AvailableAshes.Add(AshPair.Key);
    }
    
    return AvailableAshes;
}

bool USkillCustomization::ApplyAshOfWar(const FString& SkillName, const FString& AshOfWarName)
{
    if (!CustomizedSkills.Contains(SkillName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Skill not found for Ash of War: %s"), *SkillName);
        return false;
    }
    
    if (!AshesOfWar.Contains(AshOfWarName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Ash of War not found: %s"), *AshOfWarName);
        return false;
    }
    
    AppliedAshesOfWar.Add(SkillName, AshOfWarName);
    
    // Apply Ash of War effects
    const TArray<FString>& Effects = AshesOfWar[AshOfWarName];
    for (const FString& Effect : Effects)
    {
        // Parse and apply effects
        if (Effect.StartsWith(TEXT("Element:")))
        {
            FString ElementStr = Effect.RightChop(8);
            ESkillElement Element = static_cast<ESkillElement>(FCString::Atoi(*ElementStr));
            ChangeSkillElement(SkillName, Element);
        }
        else if (Effect.StartsWith(TEXT("Damage:")))
        {
            FString DamageStr = Effect.RightChop(7);
            float DamageBonus = FCString::Atof(*DamageStr);
            
            FSkillModification DamageMod;
            DamageMod.ModificationType = ESkillModificationType::SMT_Damage;
            DamageMod.ModificationValue = DamageBonus;
            DamageMod.bIsPercentage = true;
            DamageMod.Description = FString::Printf(TEXT("Ash of War: +%d%% Damage"), (int32)DamageBonus);
            
            ApplySkillModification(SkillName, DamageMod);
        }
    }
    
    UpdateSkillEffects(SkillName);
    NotifySkillCustomized(CustomizedSkills[SkillName]);
    
    UE_LOG(LogTemp, Warning, TEXT("Ash of War applied: %s to skill %s"), *AshOfWarName, *SkillName);
    return true;
}

void USkillCustomization::RemoveAshOfWar(const FString& SkillName)
{
    if (AppliedAshesOfWar.Contains(SkillName))
    {
        AppliedAshesOfWar.Remove(SkillName);
        UpdateSkillEffects(SkillName);
        NotifySkillCustomized(CustomizedSkills[SkillName]);
        UE_LOG(LogTemp, Warning, TEXT("Ash of War removed from skill: %s"), *SkillName);
    }
}

FString USkillCustomization::GetAppliedAshOfWar(const FString& SkillName) const
{
    if (AppliedAshesOfWar.Contains(SkillName))
    {
        return AppliedAshesOfWar[SkillName];
    }
    
    return TEXT("");
}

TArray<FString> USkillCustomization::GetAvailableRunes() const
{
    TArray<FString> AvailableRunes;
    
    for (const auto& RunePair : Runes)
    {
        AvailableRunes.Add(RunePair.Key);
    }
    
    return AvailableRunes;
}

bool USkillCustomization::SocketRune(const FString& SkillName, const FString& RuneName)
{
    if (!CustomizedSkills.Contains(SkillName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Skill not found for rune: %s"), *SkillName);
        return false;
    }
    
    if (!Runes.Contains(RuneName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Rune not found: %s"), *RuneName);
        return false;
    }
    
    if (!SocketedRunes.Contains(SkillName))
    {
        SocketedRunes.Add(SkillName, TArray<FString>());
    }
    
    TArray<FString>& SkillRunes = SocketedRunes[SkillName];
    if (SkillRunes.Num() >= 5) // Max 5 runes per skill
    {
        UE_LOG(LogTemp, Warning, TEXT("Maximum runes reached for skill: %s"), *SkillName);
        return false;
    }
    
    SkillRunes.Add(RuneName);
    
    // Apply rune effects
    const TArray<FString>& Effects = Runes[RuneName];
    for (const FString& Effect : Effects)
    {
        // Parse and apply effects
        if (Effect.StartsWith(TEXT("Element:")))
        {
            FString ElementStr = Effect.RightChop(8);
            ESkillElement Element = static_cast<ESkillElement>(FCString::Atoi(*ElementStr));
            ChangeSkillElement(SkillName, Element);
        }
        else if (Effect.StartsWith(TEXT("Cooldown:")))
        {
            FString CooldownStr = Effect.RightChop(10);
            float CooldownReduction = FCString::Atof(*CooldownStr);
            
            FSkillModification CooldownMod;
            CooldownMod.ModificationType = ESkillModificationType::SMT_Cooldown;
            CooldownMod.ModificationValue = -CooldownReduction;
            CooldownMod.bIsPercentage = true;
            CooldownMod.Description = FString::Printf(TEXT("Rune: -%d%% Cooldown"), (int32)CooldownReduction);
            
            ApplySkillModification(SkillName, CooldownMod);
        }
    }
    
    UpdateSkillEffects(SkillName);
    NotifySkillCustomized(CustomizedSkills[SkillName]);
    
    UE_LOG(LogTemp, Warning, TEXT("Rune socketed: %s to skill %s"), *RuneName, *SkillName);
    return true;
}

void USkillCustomization::RemoveRune(const FString& SkillName, int32 SocketIndex)
{
    if (!SocketedRunes.Contains(SkillName))
    {
        return;
    }
    
    TArray<FString>& SkillRunes = SocketedRunes[SkillName];
    if (SocketIndex >= 0 && SocketIndex < SkillRunes.Num())
    {
        FString RemovedRune = SkillRunes[SocketIndex];
        SkillRunes.RemoveAt(SocketIndex);
        
        UpdateSkillEffects(SkillName);
        NotifySkillCustomized(CustomizedSkills[SkillName]);
        
        UE_LOG(LogTemp, Warning, TEXT("Rune removed: %s from skill %s"), *RemovedRune, *SkillName);
    }
}

TArray<FString> USkillCustomization::GetSocketedRunes(const FString& SkillName) const
{
    if (SocketedRunes.Contains(SkillName))
    {
        return SocketedRunes[SkillName];
    }
    
    return TArray<FString>();
}

void USkillCustomization::AddSkillExperience(const FString& SkillName, int32 ExperienceAmount)
{
    if (!CustomizedSkills.Contains(SkillName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Skill not found for experience: %s"), *SkillName);
        return;
    }
    
    FCustomizedSkill& Skill = CustomizedSkills[SkillName];
    Skill.Experience += ExperienceAmount;
    
    // Check for level up
    int32 RequiredExperience = CalculateExperienceRequirement(Skill.SkillLevel);
    while (Skill.Experience >= RequiredExperience && Skill.SkillLevel < 100)
    {
        Skill.Experience -= RequiredExperience;
        Skill.SkillLevel++;
        RequiredExperience = CalculateExperienceRequirement(Skill.SkillLevel);
        
        NotifySkillUpgraded(SkillName, Skill.SkillLevel);
        UE_LOG(LogTemp, Warning, TEXT("Skill leveled up: %s to level %d"), *SkillName, Skill.SkillLevel);
    }
}

int32 USkillCustomization::GetSkillLevel(const FString& SkillName) const
{
    if (CustomizedSkills.Contains(SkillName))
    {
        return CustomizedSkills[SkillName].SkillLevel;
    }
    
    return 1;
}

int32 USkillCustomization::GetSkillExperience(const FString& SkillName) const
{
    if (CustomizedSkills.Contains(SkillName))
    {
        return CustomizedSkills[SkillName].Experience;
    }
    
    return 0;
}

int32 USkillCustomization::GetExperienceToNextLevel(const FString& SkillName) const
{
    if (CustomizedSkills.Contains(SkillName))
    {
        const FCustomizedSkill& Skill = CustomizedSkills[SkillName];
        return CalculateExperienceRequirement(Skill.SkillLevel) - Skill.Experience;
    }
    
    return 0;
}

void USkillCustomization::SetFavoriteSkill(const FString& SkillName, bool bIsFavorite)
{
    if (CustomizedSkills.Contains(SkillName))
    {
        CustomizedSkills[SkillName].bIsFavorite = bIsFavorite;
        UE_LOG(LogTemp, Warning, TEXT("Skill favorite status changed: %s to %s"), *SkillName, bIsFavorite ? TEXT("true") : TEXT("false"));
    }
}

bool USkillCustomization::IsFavoriteSkill(const FString& SkillName) const
{
    if (CustomizedSkills.Contains(SkillName))
    {
        return CustomizedSkills[SkillName].bIsFavorite;
    }
    
    return false;
}

TArray<FCustomizedSkill> USkillCustomization::GetFavoriteSkills() const
{
    TArray<FCustomizedSkill> FavoriteSkills;
    
    for (const auto& SkillPair : CustomizedSkills)
    {
        if (SkillPair.Value.bIsFavorite)
        {
            FavoriteSkills.Add(SkillPair.Value);
        }
    }
    
    return FavoriteSkills;
}

bool USkillCustomization::AssignSkillToSlot(const FString& SkillName, int32 SlotIndex)
{
    if (!CustomizedSkills.Contains(SkillName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Skill not found for slot assignment: %s"), *SkillName);
        return false;
    }
    
    if (SlotIndex < 0 || SlotIndex >= 10) // 10 skill slots (0-9)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid slot index: %d"), SlotIndex);
        return false;
    }
    
    // Ensure array is large enough
    while (AssignedSkillSlots.Num() <= SlotIndex)
    {
        AssignedSkillSlots.Add(TEXT(""));
    }
    
    // Remove skill from previous slot
    for (int32 i = 0; i < AssignedSkillSlots.Num(); i++)
    {
        if (AssignedSkillSlots[i] == SkillName)
        {
            AssignedSkillSlots[i] = TEXT("");
        }
    }
    
    // Assign to new slot
    AssignedSkillSlots[SlotIndex] = SkillName;
    CustomizedSkills[SkillName].SlotIndex = SlotIndex;
    
    UE_LOG(LogTemp, Warning, TEXT("Skill assigned to slot: %s to slot %d"), *SkillName, SlotIndex);
    return true;
}

void USkillCustomization::RemoveSkillFromSlot(int32 SlotIndex)
{
    if (SlotIndex >= 0 && SlotIndex < AssignedSkillSlots.Num())
    {
        FString SkillName = AssignedSkillSlots[SlotIndex];
        AssignedSkillSlots[SlotIndex] = TEXT("");
        
        if (CustomizedSkills.Contains(SkillName))
        {
            CustomizedSkills[SkillName].SlotIndex = -1;
        }
        
        UE_LOG(LogTemp, Warning, TEXT("Skill removed from slot: %d"), SlotIndex);
    }
}

FString USkillCustomization::GetSkillInSlot(int32 SlotIndex) const
{
    if (SlotIndex >= 0 && SlotIndex < AssignedSkillSlots.Num())
    {
        return AssignedSkillSlots[SlotIndex];
    }
    
    return TEXT("");
}

TArray<FString> USkillCustomization::GetAssignedSkills() const
{
    TArray<FString> AssignedSkills;
    
    for (const FString& SkillName : AssignedSkillSlots)
    {
        if (!SkillName.IsEmpty())
        {
            AssignedSkills.Add(SkillName);
        }
    }
    
    return AssignedSkills;
}

void USkillCustomization::SaveSkillCustomization()
{
    // Save skill customization data
    UE_LOG(LogTemp, Warning, TEXT("Skill customization saved"));
}

void USkillCustomization::LoadSkillCustomization()
{
    // Load skill customization data
    UE_LOG(LogTemp, Warning, TEXT("Skill customization loaded"));
}

void USkillCustomization::ResetSkillCustomization()
{
    CustomizedSkills.Empty();
    AppliedAshesOfWar.Empty();
    SocketedRunes.Empty();
    AssignedSkillSlots.Empty();
    
    for (FSkillTree& Tree : SkillTrees)
    {
        Tree.UsedSkillPoints = 0;
        for (FSkillUpgradeNode& Node : Tree.Nodes)
        {
            Node.bIsUnlocked = false;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Skill customization reset"));
}

void USkillCustomization::InitializeSkillTrees()
{
    SkillTrees.Empty();
    
    // Create default skill trees
    FSkillTree CombatTree = CreateDefaultSkillTree(TEXT("Combat"));
    FSkillTree MagicTree = CreateDefaultSkillTree(TEXT("Magic"));
    FSkillTree StealthTree = CreateDefaultSkillTree(TEXT("Stealth"));
    
    // Add nodes to combat tree
    FSkillUpgradeNode PowerAttack = CreateUpgradeNode(TEXT("Power Attack"), 5, 2);
    PowerAttack.Modifications.Add(FSkillModification{ESkillModificationType::SMT_Damage, 25.0f, true, TEXT("+25% Damage"), nullptr});
    CombatTree.Nodes.Add(PowerAttack);
    
    FSkillUpgradeNode QuickStrike = CreateUpgradeNode(TEXT("Quick Strike"), 3, 1);
    QuickStrike.Modifications.Add(FSkillModification{ESkillModificationType::SMT_Cooldown, -20.0f, true, TEXT("-20% Cooldown"), nullptr});
    CombatTree.Nodes.Add(QuickStrike);
    
    SkillTrees.Add(CombatTree);
    SkillTrees.Add(MagicTree);
    SkillTrees.Add(StealthTree);
}

void USkillCustomization::InitializeVisualVariants()
{
    VisualVariants.Empty();
    
    // Create visual variants for common skills
    TArray<FString> CommonSkills = {TEXT("Fireball"), TEXT("Ice Bolt"), TEXT("Lightning Strike"), TEXT("Poison Dart")};
    
    for (const FString& SkillName : CommonSkills)
    {
        TArray<FSkillVisualVariant> Variants;
        
        // Add element variants
        Variants.Add(CreateVisualVariant(TEXT("Fire"), ESkillElement::SE_Fire));
        Variants.Add(CreateVisualVariant(TEXT("Ice"), ESkillElement::SE_Ice));
        Variants.Add(CreateVisualVariant(TEXT("Lightning"), ESkillElement::SE_Lightning));
        Variants.Add(CreateVisualVariant(TEXT("Poison"), ESkillElement::SE_Poison));
        Variants.Add(CreateVisualVariant(TEXT("Holy"), ESkillElement::SE_Holy));
        Variants.Add(CreateVisualVariant(TEXT("Shadow"), ESkillElement::SE_Shadow));
        
        VisualVariants.Add(SkillName, Variants);
    }
}

void USkillCustomization::InitializeAshesOfWar()
{
    AshesOfWar.Empty();
    
    // Create Ashes of War
    TArray<FString> LightningAsh = {TEXT("Element:4"), TEXT("Damage:15")};
    AshesOfWar.Add(TEXT("Lightning Ash"), LightningAsh);
    
    TArray<FString> FireAsh = {TEXT("Element:1"), TEXT("Damage:20")};
    AshesOfWar.Add(TEXT("Fire Ash"), FireAsh);
    
    TArray<FString> IceAsh = {TEXT("Element:2"), TEXT("Cooldown:10")};
    AshesOfWar.Add(TEXT("Ice Ash"), IceAsh);
}

void USkillCustomization::InitializeRunes()
{
    Runes.Empty();
    
    // Create runes
    TArray<FString> FireRune = {TEXT("Element:1"), TEXT("Damage:10")};
    Runes.Add(TEXT("Fire Rune"), FireRune);
    
    TArray<FString> IceRune = {TEXT("Element:2"), TEXT("Cooldown:15")};
    Runes.Add(TEXT("Ice Rune"), IceRune);
    
    TArray<FString> LightningRune = {TEXT("Element:4"), TEXT("Damage:5"), TEXT("Cooldown:5")};
    Runes.Add(TEXT("Lightning Rune"), LightningRune);
}

void USkillCustomization::UpdateSkillEffects(const FString& SkillName)
{
    if (!CustomizedSkills.Contains(SkillName))
    {
        return;
    }
    
    const FCustomizedSkill& Skill = CustomizedSkills[SkillName];
    
    // Update particle effects, sounds, and materials based on current visual variant
    // This would interface with the visual effects system
    
    UE_LOG(LogTemp, Warning, TEXT("Skill effects updated for: %s"), *SkillName);
}

void USkillCustomization::CheckForUnlocks()
{
    // Check for new unlocks based on player level, achievements, etc.
    // This would be called periodically or after certain events
}

FSkillTree USkillCustomization::CreateDefaultSkillTree(const FString& Name)
{
    FSkillTree Tree;
    Tree.TreeName = Name;
    Tree.Description = FString::Printf(TEXT("Skill tree for %s"), *Name);
    Tree.TotalSkillPoints = 20;
    Tree.UsedSkillPoints = 0;
    Tree.bIsTreeUnlocked = false;
    
    return Tree;
}

FSkillVisualVariant USkillCustomization::CreateVisualVariant(const FString& Name, ESkillElement Element)
{
    FSkillVisualVariant Variant;
    Variant.VariantName = Name;
    Variant.Element = Element;
    Variant.ParticleEffect = nullptr;
    Variant.SoundEffect = nullptr;
    Variant.ColorTint = FLinearColor::White;
    Variant.Scale = 1.0f;
    Variant.bIsUnlocked = true;
    Variant.UnlockRequirement = TEXT("");
    
    return Variant;
}

FSkillUpgradeNode USkillCustomization::CreateUpgradeNode(const FString& Name, int32 RequiredLevel, int32 SkillPoints)
{
    FSkillUpgradeNode Node;
    Node.NodeName = Name;
    Node.Description = FString::Printf(TEXT("Upgrade node for %s"), *Name);
    Node.RequiredLevel = RequiredLevel;
    Node.SkillPointsRequired = SkillPoints;
    Node.bIsUnlocked = false;
    Node.NodeIcon = nullptr;
    
    return Node;
}

void USkillCustomization::ApplyModificationsToSkill(FCustomizedSkill& Skill)
{
    // Apply modifications from unlocked nodes
    // This would be called when nodes are upgraded
}

void USkillCustomization::NotifySkillCustomized(const FCustomizedSkill& Skill)
{
    OnSkillCustomized.Broadcast(Skill);
}

void USkillCustomization::NotifySkillUpgraded(const FString& SkillName, int32 NewLevel)
{
    OnSkillUpgraded.Broadcast(SkillName, NewLevel);
}

void USkillCustomization::NotifyVisualVariantUnlocked(const FSkillVisualVariant& Variant)
{
    OnVisualVariantUnlocked.Broadcast(Variant);
}

void USkillCustomization::NotifySkillTreeUnlocked(const FString& TreeName)
{
    OnSkillTreeUnlocked.Broadcast(TreeName);
}

bool USkillCustomization::ValidateSkillModification(const FSkillModification& Modification)
{
    // Validate modification values
    if (Modification.bIsPercentage && FMath::Abs(Modification.ModificationValue) > 100.0f)
    {
        return false;
    }
    
    return true;
}

int32 USkillCustomization::CalculateExperienceRequirement(int32 Level) const
{
    // Exponential experience requirement
    return 100 * Level * Level;
}

void USkillCustomization::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(USkillCustomization, CustomizedSkills);
    DOREPLIFETIME(USkillCustomization, SkillTrees);
    DOREPLIFETIME(USkillCustomization, VisualVariants);
    DOREPLIFETIME(USkillCustomization, AshesOfWar);
    DOREPLIFETIME(USkillCustomization, Runes);
    DOREPLIFETIME(USkillCustomization, AppliedAshesOfWar);
    DOREPLIFETIME(USkillCustomization, SocketedRunes);
    DOREPLIFETIME(USkillCustomization, AssignedSkillSlots);
    DOREPLIFETIME(USkillCustomization, TotalSkillPoints);
}
