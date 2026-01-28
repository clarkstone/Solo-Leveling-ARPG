# 🚀 WEEK 2 IMPLEMENTATION PLAN - UI & ENEMY SYSTEMS

## DAY 1: UI SYSTEM IMPLEMENTATION

### Main HUD Widget Blueprint
```cpp
// MainHUD.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

UCLASS()
class SOLOLEVELINGSHADOWMONARCH_API UMainHUD : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void UpdateHealthBar(float CurrentHealth, float MaxHealth);

    UFUNCTION(BlueprintCallable)
    void UpdateManaBar(float CurrentMana, float MaxMana);

    UFUNCTION(BlueprintCallable)
    void UpdateExperienceBar(float CurrentExp, float MaxExp);

    UFUNCTION(BlueprintCallable)
    void UpdateLevelText(int32 Level);

    UFUNCTION(BlueprintCallable)
    void UpdateRankText(EHuntRank Rank);

    UFUNCTION(BlueprintCallable)
    void UpdateGoldText(int32 Gold);

    UFUNCTION(BlueprintCallable)
    void ShowSystemMessage(const FString& Message);

    UFUNCTION(BlueprintCallable)
    void ShowDamageNumber(float Damage, FVector Location);

protected:
    virtual void NativeConstruct() override;

private:
    // UI Elements (Bind in Blueprint)
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthBar;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* ManaBar;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* ExperienceBar;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* LevelText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* RankText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* GoldText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* SystemMessageText;

    UPROPERTY(meta = (BindWidget))
    class UVerticalBox* ShadowArmyList;

    // Animation
    UPROPERTY(Transient)
    class UWidgetAnimation* LevelUpAnimation;

    UPROPERTY(Transient)
    class UWidgetAnimation* DamageNumberAnimation;

    // System
    FTimerHandle SystemMessageTimer;
    void HideSystemMessage();
};
```

### Character Sheet Widget
```cpp
// CharacterSheetWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HunterStatsComponent.h"
#include "CharacterSheetWidget.generated.h"

UCLASS()
class SOLOLEVELINGSHADOWMONARCH_API UCharacterSheetWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void InitializeCharacterSheet(class UHunterStatsComponent* StatsComponent);

    UFUNCTION(BlueprintCallable)
    void UpdateCharacterStats();

    UFUNCTION(BlueprintCallable)
    void OnStatPointAllocated(EHuntStat StatType);

protected:
    virtual void NativeConstruct() override;

private:
    UPROPERTY()
    class UHunterStatsComponent* HunterStats;

    // UI Elements
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* CharacterNameText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* LevelText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* RankText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* HealthText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ManaText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* AttackPowerText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* DefenseText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* MagicPowerText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* AgilityText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* StatPointsText;

    // Stat Allocation Buttons
    UPROPERTY(meta = (BindWidget))
    class UButton* StrengthButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* DexterityButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* IntelligenceButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* VitalityButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* AgilityButton;

    // Functions
    UFUNCTION()
    void OnStrengthButtonClicked();

    UFUNCTION()
    void OnDexterityButtonClicked();

    UFUNCTION()
    void OnIntelligenceButtonClicked();

    UFUNCTION()
    void OnVitalityButtonClicked();

    UFUNCTION()
    void OnAgilityButtonClicked();
};
```

### Shadow Army Widget
```cpp
// ShadowArmyWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShadowArmyComponent.h"
#include "ShadowArmyWidget.generated.h"

UCLASS()
class SOLOLEVELINGSHADOWMONARCH_API UShadowArmyWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void InitializeShadowArmy(class UShadowArmyComponent* ShadowComponent);

    UFUNCTION(BlueprintCallable)
    void UpdateShadowList();

    UFUNCTION(BlueprintCallable)
    void OnShadowSummoned(int32 ShadowIndex);

    UFUNCTION(BlueprintCallable)
    void OnShadowEvolved(int32 ShadowIndex);

protected:
    virtual void NativeConstruct() override;

private:
    UPROPERTY()
    class UShadowArmyComponent* ShadowArmyComponent;

    UPROPERTY(meta = (BindWidget))
    class UVerticalBox* ShadowList;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ShadowCountText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ActiveShadowsText;

    UPROPERTY()
    TSubclassOf<class UUserWidget> ShadowEntryWidgetClass;

    void CreateShadowEntry(const FShadowData& ShadowData, int32 Index);
};
```

## DAY 2: ENEMY AI SYSTEM

### Enemy Character Base
```cpp
// EnemyCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
    Idle,
    Patrol,
    Chase,
    Attack,
    Stunned,
    Dead
};

USTRUCT(BlueprintType)
struct FEnemyStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackPower = 15.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Defense = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DetectionRange = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackRange = 150.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MovementSpeed = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperienceValue = 25;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 GoldValue = 10;
};

UCLASS()
class SOLOLEVELINGSHADOWMONARCH_API AEnemyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AEnemyCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

    // AI Functions
    UFUNCTION(BlueprintCallable)
    void SetEnemyState(EEnemyState NewState);

    UFUNCTION(BlueprintCallable)
    void StartPatrol();

    UFUNCTION(BlueprintCallable)
    void ChasePlayer();

    UFUNCTION(BlueprintCallable)
    void AttackPlayer();

    UFUNCTION(BlueprintCallable)
    void OnDeath();

    // Combat
    UFUNCTION(BlueprintCallable)
    void PerformBasicAttack();

    UFUNCTION(BlueprintCallable)
    void PerformSpecialAttack();

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
    class UEnemyAIController* AIController;

    UPROPERTY(EditAnywhere, Category = "AI")
    FEnemyStats EnemyStats;

    UPROPERTY(EditAnywhere, Category = "AI")
    EEnemyState CurrentState;

    UPROPERTY(EditAnywhere, Category = "AI")
    TArray<class AActor*> PatrolPoints;

    UPROPERTY(EditAnywhere, Category = "AI")
    int32 CurrentPatrolIndex;

    UPROPERTY(EditAnywhere, Category = "Combat")
    float AttackCooldown = 2.0f;

    UPROPERTY(EditAnywhere, Category = "Combat")
    bool bCanAttack = true;

    FTimerHandle AttackTimer;
    FTimerHandle DeathTimer;

    // AI Behavior
    void UpdateAIState();
    bool CanSeePlayer();
    bool IsPlayerInRange();
    void MoveToNextPatrolPoint();
    void DropLoot();
};
```

### Enemy AI Controller
```cpp
// EnemyAIController.h
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class SOLOLEVELINGSHADOWMONARCH_API UEnemyAIController : public AIController
{
    GENERATED_BODY()

public:
    UEnemyAIController();

protected:
    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;

    // AI Behavior
    UFUNCTION(BlueprintCallable)
    void SetTarget(class AActor* NewTarget);

    UFUNCTION(BlueprintCallable)
    void ClearTarget();

    UFUNCTION(BlueprintCallable)
    void MoveToTarget();

    UFUNCTION(BlueprintCallable)
    void MoveToPatrolPoint(class AActor* PatrolPoint);

    UFUNCTION(BlueprintCallable)
    void AttackTarget();

    UFUNCTION(BlueprintCallable)
    void StopMovement();

    // Perception
    UFUNCTION()
    void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
    UPROPERTY()
    class AActor* CurrentTarget;

    UPROPERTY()
    class UAIPerceptionComponent* PerceptionComponent;

    UPROPERTY()
    class UAISenseConfig_Sight* SightConfig;

    UPROPERTY()
    class UAISenseConfig_Hearing* HearingConfig;

    void SetupPerceptionSystem();
    bool IsTargetValid(AActor* Target) const;
};
```

## DAY 3: DUNGEON SYSTEM

### Dungeon Gate Actor
```cpp
// DungeonGate.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGate.generated.h"

UENUM(BlueprintType)
enum class EDungeonRank : uint8
{
    D_Rank,
    C_Rank,
    B_Rank,
    A_Rank,
    S_Rank
};

USTRUCT(BlueprintType)
struct FDungeonData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EDungeonRank Rank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DungeonName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString MapName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RecommendedPlayers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> EnemyTypes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString BossType;
};

UCLASS()
class SOLOLEVELINGSHADOWMONARCH_API ADungeonGate : public AActor
{
    GENERATED_BODY()

public:
    ADungeonGate();

protected:
    virtual void BeginPlay() override;

    // Interaction
    UFUNCTION(BlueprintCallable)
    bool CanPlayerEnter(class AShadowMonarchCharacter* Player);

    UFUNCTION(BlueprintCallable)
    void EnterDungeon(class AShadowMonarchCharacter* Player);

    UFUNCTION(BlueprintCallable)
    void OnPlayerOverlap(class APrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* GateMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class USphereComponent* TriggerVolume;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UNiagaraComponent* PortalEffect;

    UPROPERTY(EditAnywhere, Category = "Dungeon")
    FDungeonData DungeonInfo;

    UPROPERTY(EditAnywhere, Category = "Dungeon")
    bool bIsActive = true;

    UPROPERTY(EditAnywhere, Category = "Dungeon")
    float RespawnTime = 300.0f;

    FTimerHandle RespawnTimer;
    void RespawnGate();
};
```

## DAY 4: ANIMATION SYSTEM

### Animation Blueprint Setup
```cpp
// ShadowMonarchAnimInstance.h
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShadowMonarchAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
    Idle,
    Walking,
    Running,
    Jumping,
    Falling,
    Dodging,
    Attacking
};

UCLASS()
class SOLOLEVELINGSHADOWMONARCH_API UShadowMonarchAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeUpdateAnimation(float DeltaTime) override;

protected:
    // Movement
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    EMovementState MovementState;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float Speed;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsInAir;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsMoving;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FVector2D MovementInput;

    // Combat
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsAttacking;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsDodging;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsUsingSkill;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsLockedOn;

private:
    UPROPERTY()
    class AShadowMonarchCharacter* Character;

    void UpdateMovementState();
    void UpdateCombatState();
};
```

## DAY 5: SOUND SYSTEM

### Audio Manager
```cpp
// AudioManager.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AudioManager.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOLOLEVELINGSHADOWMONARCH_API UAudioManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UAudioManager();

    // Sound Effects
    UFUNCTION(BlueprintCallable)
    void PlayAttackSound();

    UFUNCTION(BlueprintCallable)
    void PlayHeavyAttackSound();

    UFUNCTION(BlueprintCallable)
    void PlayDodgeSound();

    UFUNCTION(BlueprintCallable)
    void PlaySkillSound();

    UFUNCTION(BlueprintCallable)
    void PlayHitSound();

    UFUNCTION(BlueprintCallable)
    void PlayDeathSound();

    UFUNCTION(BlueprintCallable)
    void PlayLevelUpSound();

    UFUNCTION(BlueprintCallable)
    void PlayShadowExtractSound();

    UFUNCTION(BlueprintCallable)
    void PlayShadowSummonSound();

    // Music
    UFUNCTION(BlueprintCallable)
    void PlayCombatMusic();

    UFUNCTION(BlueprintCallable)
    void PlayExplorationMusic();

    UFUNCTION(BlueprintCallable)
    void PlayDungeonMusic();

    UFUNCTION(BlueprintCallable)
    void StopMusic();

protected:
    virtual void BeginPlay() override;

private:
    // Sound Cues
    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* AttackSound;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* HeavyAttackSound;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* DodgeSound;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* SkillSound;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* HitSound;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* DeathSound;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* LevelUpSound;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* ShadowExtractSound;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* ShadowSummonSound;

    // Music
    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* CombatMusic;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* ExplorationMusic;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* DungeonMusic;

    UPROPERTY()
    class UAudioComponent* MusicAudioComponent;
};
```

## DAY 6-7: SAVE/LOAD SYSTEM

### Save Game Manager
```cpp
// SaveGameManager.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveGameManager.generated.h"

USTRUCT(BlueprintType)
struct FPlayerSaveData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString PlayerName;

    UPROPERTY(BlueprintReadWrite)
    int32 Level;

    UPROPERTY(BlueprintReadWrite)
    int32 Experience;

    UPROPERTY(BlueprintReadWrite)
    EHuntRank HunterRank;

    UPROPERTY(BlueprintReadWrite)
    FHunterStats Stats;

    UPROPERTY(BlueprintReadWrite)
    TArray<FShadowData> ShadowArmy;

    UPROPERTY(BlueprintReadWrite)
    FVector PlayerLocation;

    UPROPERTY(BlueprintReadWrite)
    FRotator PlayerRotation;

    UPROPERTY(BlueprintReadWrite)
    FString CurrentMap;

    UPROPERTY(BlueprintReadWrite)
    int32 Gold;

    UPROPERTY(BlueprintReadWrite)
    TArray<FString> CompletedQuests;

    UPROPERTY(BlueprintReadWrite)
    float PlayTime;
};

UCLASS()
class SOLOLEVELINGSHADOWMONARCH_API USaveGameManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    bool SaveGame(class AShadowMonarchCharacter* Player);

    UFUNCTION(BlueprintCallable)
    bool LoadGame(class AShadowMonarchCharacter* Player);

    UFUNCTION(BlueprintCallable)
    bool AutoSave();

    UFUNCTION(BlueprintCallable)
    void DeleteSave();

    UFUNCTION(BlueprintPure)
    bool DoesSaveExist();

    UFUNCTION(BlueprintPure)
    FPlayerSaveData GetSaveData();

protected:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
    UPROPERTY()
    FString SaveSlotName = "SoloLevelingSave";

    UPROPERTY()
    FPlayerSaveData CurrentSaveData;

    FTimerHandle AutoSaveTimer;
    void StartAutoSave();
    void OnAutoSave();
};
```

## WEEK 2 SUCCESS METRICS

### Daily Goals:
- **Day 1:** Complete UI framework with HUD, Character Sheet, Shadow Army UI
- **Day 2:** Implement Enemy AI with patrol, chase, attack behaviors
- **Day 3:** Create Dungeon Gate system with level requirements
- **Day 4:** Set up Animation Blueprints for character and enemies
- **Day 5:** Implement comprehensive audio system
- **Day 6-7:** Complete save/load system with auto-save

### Week 2 Completion Target:
- Fully functional UI system
- Smart enemy AI with multiple behaviors
- Dungeon entry system
- Smooth animations
- Immersive sound effects and music
- Persistent save system

### Testing Checklist:
- [ ] All UI widgets display correctly
- [ ] Enemy AI responds to player presence
- [ ] Dungeons can be entered and exited
- [ ] Animations play smoothly
- [ ] Sound effects trigger appropriately
- [ ] Game saves and loads correctly

**WEEK 2 WILL TRANSFORM YOUR FOUNDATION INTO A PLAYABLE GAME! 🚀**
