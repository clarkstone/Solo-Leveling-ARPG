#include "AdvancedEnemy.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/SoloLevelingCharacter.h"
#include "TimerManager.h"

AAdvancedEnemy::AAdvancedEnemy()
{
    // Initialize enemy properties
    EnemyTier = EEnemyTier::ET_Basic;
    CurrentState = EEnemyState::ES_Patrol;
    
    // Initialize health and combat
    Health = 100.0f;
    MaxHealth = 100.0f;
    Damage = 10.0f;
    AttackRange = 200.0f;
    DetectionRange = 500.0f;
    ChaseRange = 800.0f;
    
    // Initialize AI components
    AIController = nullptr;
    BehaviorTree = nullptr;
    Blackboard = nullptr;
    
    // Initialize learning system
    LearningCooldown = 5.0f;
    
    // Initialize environmental awareness
    VisionRadius = 600.0f;
    HearingRadius = 400.0f;
    bHasNightVision = false;
    
    // Initialize social behaviors
    bIsPackLeader = false;
    PackCoordinationRange = 1000.0f;
    
    // Initialize special abilities
    UltimateAbilityCooldown = 30.0f;
    bCanUseUltimateAbility = true;
    
    // Initialize internal state
    LastAttackTime = 0.0f;
    LastPlayerSightingTime = 0.0f;
    LastKnownPlayerLocation = FVector::ZeroVector;
    bHasSeenPlayer = false;
    bIsAlerted = false;
    
    // Initialize learning variables
    LastLearningTime = 0.0f;
    DefeatCount = 0;
}

void AAdvancedEnemy::BeginPlay()
{
    Super::BeginPlay();
    
    InitializeAI();
    UpdateAIState();
    
    UE_LOG(LogTemp, Warning, TEXT("Advanced Enemy initialized with tier: %d"), (int32)EnemyTier);
}

void AAdvancedEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    UpdateAIState();
    UpdateBehaviorTree();
    UpdateSensoryInput();
    UpdateDecisionMaking();
    UpdateMovement();
}

void AAdvancedEnemy::InitializeAI()
{
    // Get AI Controller
    AIController = GetController<AAIController>();
    
    // Initialize behavior tree based on enemy tier
    InitializeBehaviorTree();
    
    // Initialize blackboard
    InitializeBlackboard();
    
    // Set initial behavior data based on tier
    switch (EnemyTier)
    {
        case EEnemyTier::ET_Basic:
            BehaviorData.AggressionLevel = 0.3f;
            BehaviorData.Intelligence = 0.2f;
            BehaviorData.Teamwork = 0.1f;
            BehaviorData.Adaptability = 0.1f;
            BehaviorData.LearningRate = 0.05f;
            break;
        case EEnemyTier::ET_Elite:
            BehaviorData.AggressionLevel = 0.5f;
            BehaviorData.Intelligence = 0.4f;
            BehaviorData.Teamwork = 0.3f;
            BehaviorData.Adaptability = 0.3f;
            BehaviorData.LearningRate = 0.1f;
            break;
        case EEnemyTier::ET_Boss:
            BehaviorData.AggressionLevel = 0.7f;
            BehaviorData.Intelligence = 0.6f;
            BehaviorData.Teamwork = 0.5f;
            BehaviorData.Adaptability = 0.5f;
            BehaviorData.LearningRate = 0.2f;
            break;
        case EEnemyTier::ET_Monarch:
            BehaviorData.AggressionLevel = 0.9f;
            BehaviorData.Intelligence = 0.8f;
            BehaviorData.Teamwork = 0.7f;
            BehaviorData.Adaptability = 0.7f;
            BehaviorData.LearningRate = 0.3f;
            break;
    }
}

float AAdvancedEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    
    Health -= ActualDamage;
    
    // Alert nearby enemies
    if (!bIsAlerted)
    {
        bIsAlerted = true;
        CallForReinforcements();
    }
    
    // Broadcast damage event
    OnEnemyDamaged.Broadcast(this, ActualDamage, DamageCauser);
    
    // Check if defeated
    if (Health <= 0.0f)
    {
        LearnFromDefeat();
        OnEnemyDefeated.Broadcast(this);
        SetState(EEnemyState::ES_Dead);
    }
    
    return ActualDamage;
}

void AAdvancedEnemy::Attack()
{
    if (GetWorld()->GetTimeSeconds() - LastAttackTime > 1.0f)
    {
        // Perform basic attack
        LastAttackTime = GetWorld()->GetTimeSeconds();
        OnEnemyAttacked.Broadcast(this, Damage);
        
        UE_LOG(LogTemp, Warning, TEXT("Enemy attacking with damage: %.2f"), Damage);
    }
}

void AAdvancedEnemy::HeavyAttack()
{
    if (GetWorld()->GetTimeSeconds() - LastAttackTime > 2.0f)
    {
        // Perform heavy attack
        LastAttackTime = GetWorld()->GetTimeSeconds();
        float HeavyDamage = Damage * 1.5f;
        OnEnemyAttacked.Broadcast(this, HeavyDamage);
        
        UE_LOG(LogTemp, Warning, TEXT("Enemy heavy attacking with damage: %.2f"), HeavyDamage);
    }
}

void AAdvancedEnemy::SpecialAttack(FName AbilityName)
{
    if (SpecialAbilities.Contains(AbilityName))
    {
        // Execute special ability
        UE_LOG(LogTemp, Warning, TEXT("Enemy using special ability: %s"), *AbilityName.ToString());
    }
}

void AAdvancedEnemy::UseUltimateAbility()
{
    if (bCanUseUltimateAbility)
    {
        bCanUseUltimateAbility = false;
        
        // Start cooldown timer
        FTimerHandle UltimateTimer;
        GetWorldTimerManager().SetTimer(UltimateTimer, this, &AAdvancedEnemy::ResetUltimateAbility, UltimateAbilityCooldown, false);
        
        UE_LOG(LogTemp, Warning, TEXT("Enemy using ultimate ability!"));
    }
}

void AAdvancedEnemy::ResetUltimateAbility()
{
    bCanUseUltimateAbility = true;
}

void AAdvancedEnemy::SetState(EEnemyState NewState)
{
    if (CanTransitionToState(NewState))
    {
        EEnemyState OldState = CurrentState;
        CurrentState = NewState;
        
        OnEnemyStateChanged.Broadcast(this, OldState, NewState);
        
        UE_LOG(LogTemp, Warning, TEXT("Enemy state changed from %d to %d"), (int32)OldState, (int32)NewState);
    }
}

bool AAdvancedEnemy::CanTransitionToState(EEnemyState NewState)
{
    // Check if state transition is valid
    switch (CurrentState)
    {
        case EEnemyState::ES_Dead:
            return false; // Can't transition from dead
        case EEnemyState::ES_Patrol:
            return true; // Can transition to any state
        case EEnemyState::ES_Chase:
            return NewState != EEnemyState::ES_Patrol;
        case EEnemyState::ES_Combat:
            return NewState != EEnemyState::ES_Patrol;
        case EEnemyState::ES_Flee:
            return NewState == EEnemyState::ES_Patrol || NewState == EEnemyState::ES_Dead;
        default:
            return true;
    }
}

void AAdvancedEnemy::LearnFromDefeat()
{
    DefeatCount++;
    
    // Increase learning rate based on defeats
    BehaviorData.LearningRate = FMath::Clamp(BehaviorData.LearningRate + 0.05f, 0.0f, 1.0f);
    
    UE_LOG(LogTemp, Warning, TEXT("Enemy learning from defeat #%d. New learning rate: %.2f"), DefeatCount, BehaviorData.LearningRate);
}

// Boss Enemy Implementation
ABossEnemy::ABossEnemy()
{
    // Initialize boss-specific properties
    EnemyTier = EEnemyTier::ET_Boss;
    bCanManipulateEnvironment = true;
    
    // Initialize boss abilities
    Phase1Abilities.Add(TEXT("BasicAttack"));
    Phase1Abilities.Add(TEXT("HeavyAttack"));
    
    Phase2Abilities.Add(TEXT("AreaAttack"));
    Phase2Abilities.Add(TEXT("SummonMinions"));
    
    Phase3Abilities.Add(TEXT("UltimateAttack"));
    Phase3Abilities.Add(TEXT("EnvironmentManipulation"));
    
    UltimateAbilities.Add(TEXT("WorldEndingAttack"));
}

void ABossEnemy::BeginPlay()
{
    Super::BeginPlay();
    
    CurrentPhase = 1;
    UE_LOG(LogTemp, Warning, TEXT("Boss Enemy initialized"));
}

void ABossEnemy::TransitionToPhase(int32 NewPhase)
{
    if (NewPhase != CurrentPhase && NewPhase <= CombatPhases.Num())
    {
        CurrentPhase = NewPhase;
        LastPhaseTransitionTime = GetWorld()->GetTimeSeconds();
        
        // Apply phase-specific effects
        switch (NewPhase)
        {
            case 2:
                UE_LOG(LogTemp, Warning, TEXT("Boss entering Phase 2"));
                break;
            case 3:
                UE_LOG(LogTemp, Warning, TEXT("Boss entering Phase 3"));
                Enrage();
                break;
        }
        
        UpdatePhaseBehavior();
    }
}

void ABossEnemy::ManipulateEnvironment(EEnvironmentAction Action)
{
    if (bCanManipulateEnvironment)
    {
        // Execute environmental manipulation
        UE_LOG(LogTemp, Warning, TEXT("Boss manipulating environment with action: %d"), (int32)Action);
    }
}

void ABossEnemy::ExecuteUltimateAbility()
{
    if (CurrentPhase >= 2)
    {
        Super::UseUltimateAbility();
        UE_LOG(LogTemp, Warning, TEXT("Boss executing ultimate ability in Phase %d"), CurrentPhase);
    }
}

void ABossEnemy::SpawnMinions()
{
    if (CurrentPhase >= 2)
    {
        // Spawn boss minions
        UE_LOG(LogTemp, Warning, TEXT("Boss spawning minions"));
    }
}

void ABossEnemy::Enrage()
{
    bIsEnraged = true;
    Damage *= 1.5f;
    UE_LOG(LogTemp, Warning, TEXT("Boss enraged! Damage increased to %.2f"), Damage);
}
