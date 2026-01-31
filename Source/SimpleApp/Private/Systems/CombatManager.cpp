#include "CombatManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UCombatManager::UCombatManager()
{
    CurrentState = ECombatState::CS_Idle;
    bIsInCombat = false;
    ActiveEnemyCount = 0;
    CombatEngagementRange = 1000.0f;
    CombatCooldownTime = 2.0f;
    PerfectTimingWindow = 0.2f;
    
    LastAttackTime = 0.0f;
    ComboTimer = 0.0f;
    CombatTimer = 0.0f;
    bCanAttack = true;
    bIsInCombo = false;
    
    TotalAttacks = 0;
    PerfectTimings = 0;
    CombosExecuted = 0;
    TotalDamageDealt = 0.0f;
}

void UCombatManager::BeginPlay()
{
    Super::BeginPlay();
    Initialize();
}

void UCombatManager::Initialize()
{
    InitializeComboSystem();
    UE_LOG(LogTemp, Warning, TEXT("Combat Manager initialized"));
}

void UCombatManager::StartCombat()
{
    bIsInCombat = true;
    CurrentState = ECombatState::CS_Engaged;
    CombatTimer = 0.0f;
    
    OnCombatStarted.Broadcast();
    UE_LOG(LogTemp, Warning, TEXT("Combat started"));
}

void UCombatManager::EndCombat()
{
    bIsInCombat = false;
    CurrentState = ECombatState::CS_Victory;
    
    OnCombatEnded.Broadcast();
    UE_LOG(LogTemp, Warning, TEXT("Combat ended"));
}

void UCombatManager::ProcessAttack(FCombatData CombatData)
{
    if (!bCanAttack) return;
    
    TotalAttacks++;
    TotalDamageDealt += CombatData.Damage;
    
    if (CombatData.bIsPerfectTiming)
    {
        PerfectTimings++;
        OnPerfectTimingExecuted.Broadcast(CombatData.AttackType);
    }
    
    OnAttackExecuted.Broadcast(CombatData);
    
    // Start attack cooldown
    bCanAttack = false;
    LastAttackTime = GetWorld()->GetTimeSeconds();
    
    UE_LOG(LogTemp, Warning, TEXT("Attack processed: %.2f damage"), CombatData.Damage);
}

bool UCombatManager::CheckPerfectTiming(FName ActionName)
{
    // Check if action is within perfect timing window
    float TimeSinceLastAttack = GetWorld()->GetTimeSeconds() - LastAttackTime;
    return TimeSinceLastAttack <= PerfectTimingWindow;
}

void UCombatManager::AddComboMove(FName MoveName)
{
    CurrentCombo.Add(MoveName);
    ComboTimer = 1.0f;
    bIsInCombo = true;
    
    ValidateCombo();
}

void UCombatManager::ExecuteCombo()
{
    if (CurrentCombo.Num() > 0)
    {
        CombosExecuted++;
        OnComboExecuted.Broadcast(CurrentCombo, TotalDamageDealt * 1.5f);
        
        UE_LOG(LogTemp, Warning, TEXT("Combo executed"));
        ResetCombo();
    }
}

void UCombatManager::ResetCombo()
{
    CurrentCombo.Empty();
    bIsInCombo = false;
    ComboTimer = 0.0f;
}

void UCombatManager::InitializeComboSystem()
{
    // Initialize basic combos
    FComboData BasicCombo;
    BasicCombo.ComboSequence.Add(TEXT("Attack"));
    BasicCombo.ComboSequence.Add(TEXT("Attack"));
    BasicCombo.DamageMultiplier = 1.5f;
    AvailableCombos.Add(BasicCombo);
    
    UE_LOG(LogTemp, Warning, TEXT("Combo system initialized"));
}

void UCombatManager::UpdateCombatState(float DeltaTime)
{
    if (!bIsInCombat) return;
    
    CombatTimer += DeltaTime;
    
    // Check for attack cooldown
    if (!bCanAttack)
    {
        float TimeSinceAttack = GetWorld()->GetTimeSeconds() - LastAttackTime;
        if (TimeSinceAttack >= CombatCooldownTime)
        {
            bCanAttack = true;
        }
    }
    
    // Update combo timer
    if (bIsInCombo && ComboTimer > 0.0f)
    {
        ComboTimer -= DeltaTime;
        if (ComboTimer <= 0.0f)
        {
            ExecuteCombo();
        }
    }
    
    // Check for combat end conditions
    if (ActiveEnemyCount == 0)
    {
        EndCombat();
    }
}

void UCombatManager::ValidateCombo()
{
    // Check if current combo matches any available combos
    for (const FComboData& Combo : AvailableCombos)
    {
        if (Combo.ComboSequence == CurrentCombo)
        {
            ExecuteCombo();
            break;
        }
    }
}
