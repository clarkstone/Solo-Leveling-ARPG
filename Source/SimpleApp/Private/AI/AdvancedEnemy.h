#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AdvancedEnemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyTier : uint8
{
    ET_Basic,        // Rank E-D monsters
    ET_Elite,        // Rank C-B monsters
    ET_Boss,         // Rank A-S monsters
    ET_Monarch       // Monarch-level beings
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
    ES_Patrol,
    ES_Chase,
    ES_Combat,
    ES_Flee,
    ES_Special,
    ES_Dead
};

USTRUCT(BlueprintType)
struct FPlayerPatternData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> FrequentlyUsedAbilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector> PreferredPositions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DodgeFrequency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackFrequency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlockSuccessRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPrefersRangedCombat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUsesEnvironmentalAdvantage;
};

USTRUCT(BlueprintType)
struct FEnemyBehaviorData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AggressionLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Intelligence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Teamwork;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Adaptability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LearningRate;
};

UCLASS()
class SIMPLEAPP_API AAdvancedEnemy : public ACharacter
{
    GENERATED_BODY()

public:
    AAdvancedEnemy();

    // Enemy Properties
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
    EEnemyTier EnemyTier;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
    EEnemyState CurrentState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    FEnemyBehaviorData BehaviorData;

    // Health and Combat
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    float AttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    float DetectionRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    float ChaseRange;

    // AI Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    class AAIController* AIController;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    UBehaviorTree* BehaviorTree;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    UBlackboardComponent* Blackboard;

    // Learning System
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    FPlayerPatternData PlayerPatternMemory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float LearningCooldown;

    // Environmental Awareness
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float VisionRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HearingRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    bool bHasNightVision;

    // Social Behaviors
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    bool bIsPackLeader;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TArray<AAdvancedEnemy*> PackMembers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float PackCoordinationRange;

    // Special Abilities
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    TArray<FName> SpecialAbilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    float UltimateAbilityCooldown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    bool bCanUseUltimateAbility;

    // Override ACharacter functions
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

    // AI Functions
    UFUNCTION(BlueprintCallable, Category = "AI")
    void InitializeAI();

    UFUNCTION(BlueprintCallable, Category = "AI")
    void UpdateAIState();

    UFUNCTION(BlueprintCallable, Category = "AI")
    void AnalyzeEnvironment();

    UFUNCTION(BlueprintCallable, Category = "AI")
    void AnalyzePlayerBehavior(class ASoloLevelingCharacter* Player);

    UFUNCTION(BlueprintCallable, Category = "AI")
    void AdaptStrategy(FPlayerPatternData PlayerData);

    UFUNCTION(BlueprintCallable, Category = "AI")
    void CoordinateWithPack();

    UFUNCTION(BlueprintCallable, Category = "AI")
    void CallForReinforcements();

    UFUNCTION(BlueprintCallable, Category = "AI")
    void RetreatAndHeal();

    // Combat Functions
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Attack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void HeavyAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void SpecialAttack(FName AbilityName);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void UseUltimateAbility();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Block();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Dodge();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Parry();

    // Movement Functions
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Patrol();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void ChasePlayer();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Flee();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void UseEnvironment();

    // Learning Functions
    UFUNCTION(BlueprintCallable, Category = "AI")
    void RecordPlayerAction(FName ActionName, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "AI")
    void UpdatePlayerPattern();

    UFUNCTION(BlueprintCallable, Category = "AI")
    void LearnFromDefeat();

    // State Management
    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetState(EEnemyState NewState);

    UFUNCTION(BlueprintCallable, Category = "AI")
    bool CanTransitionToState(EEnemyState NewState);

    // Events
    UPROPERTY(BlueprintAssignable, Category = "Enemy Events")
    FOnEnemyStateChanged OnEnemyStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Enemy Events")
    FOnEnemyAttacked OnEnemyAttacked;

    UPROPERTY(BlueprintAssignable, Category = "Enemy Events")
    FOnEnemyDamaged OnEnemyDamaged;

    UPROPERTY(BlueprintAssignable, Category = "Enemy Events")
    FOnEnemyDefeated OnEnemyDefeated;

protected:
    // Internal AI Functions
    void UpdateBehaviorTree();
    void UpdateSensoryInput();
    void UpdateDecisionMaking();
    void UpdateMovement();

    // Combat AI
    void ChooseAttackStrategy();
    void EvaluateCombatSituation();
    void ExecuteCombatTactics();

    // Environmental Interaction
    void FindCover();
    void SetAmbush();
    void UseTraps();

    // Social AI
    void CommunicateWithPack();
    void SharePlayerData();
    void CoordinateAttack();

private:
    // Internal State
    float LastAttackTime;
    float LastPlayerSightingTime;
    FVector LastKnownPlayerLocation;
    bool bHasSeenPlayer;
    bool bIsAlerted;

    // Learning Variables
    float LastLearningTime;
    int32 DefeatCount;
    TArray<FPlayerPatternData> PlayerHistory;

    // Environmental Variables
    TArray<AActor*> NearbyCover;
    TArray<AActor*> NearbyTraps;
    TArray<AAdvancedEnemy*> NearbyAllies;

    // Helper Functions
    void InitializeBehaviorTree();
    void InitializeBlackboard();
    void UpdateSensors();
    void ProcessSensoryData();
};

// Boss Enemy Class
UCLASS()
class SIMPLEAPP_API ABossEnemy : public AAdvancedEnemy
{
    GENERATED_BODY()

public:
    ABossEnemy();

    // Boss Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
    TArray<FBossPhase> CombatPhases;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
    int32 CurrentPhase;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
    float PhaseTransitionHealth;

    // Boss Abilities
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
    TArray<FName> Phase1Abilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
    TArray<FName> Phase2Abilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
    TArray<FName> Phase3Abilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
    TArray<FName> UltimateAbilities;

    // Environmental Control
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
    bool bCanManipulateEnvironment;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
    float EnvironmentManipulationRange;

    // Override functions
    virtual void BeginPlay() override;
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

    // Boss Functions
    UFUNCTION(BlueprintCallable, Category = "Boss")
    void TransitionToPhase(int32 NewPhase);

    UFUNCTION(BlueprintCallable, Category = "Boss")
    void ManipulateEnvironment(EEnvironmentAction Action);

    UFUNCTION(BlueprintCallable, Category = "Boss")
    void ExecuteUltimateAbility();

    UFUNCTION(BlueprintCallable, Category = "Boss")
    void SpawnMinions();

    UFUNCTION(BlueprintCallable, Category = "Boss")
    void Enrage();

protected:
    // Boss AI Functions
    void UpdatePhaseBehavior();
    void ExecutePhaseAbilities();
    void TriggerPhaseTransition();

private:
    // Boss State
    bool bIsEnraged;
    float LastPhaseTransitionTime;
    TArray<AActor*> SpawnedMinions;
};
