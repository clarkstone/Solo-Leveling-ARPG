#include "SoloLevelingCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Systems/PowerSystemComponent.h"

ASoloLevelingCharacter::ASoloLevelingCharacter()
{
    // Set this character to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Initialize character properties
    CurrentStance = ECombatStance::CS_Balanced;
    bIsInCombat = false;
    Health = 100.0f;
    MaxHealth = 100.0f;
    Power = 100.0f;
    MaxPower = 100.0f;

    // Initialize movement properties
    DashSpeed = 1200.0f;
    ShadowStepDistance = 800.0f;
    bCanDoubleJump = true;

    // Initialize combat properties
    BaseDamage = 10.0f;
    CriticalChance = 0.1f;
    CriticalMultiplier = 2.0f;

    // Initialize shadow properties
    ShadowArmySize = 0;
    bCanSummonShadows = false;

    // Initialize internal state
    bIsAttacking = false;
    bIsBlocking = false;
    bIsDodging = false;
    bIsSprinting = false;
    ComboTimer = 0.0f;
    LastAttackTime = 0.0f;
    ComboCount = 0;

    // Initialize timing windows
    PerfectDodgeWindow = 0.2f;
    PerfectParryWindow = 0.15f;
    ComboTimingWindow = 1.0f;

    // Initialize movement
    LastMovementInput = FVector::ZeroVector;
    SprintSpeedMultiplier = 1.7f;

    // Initialize weapon mastery
    InitializeWeaponMastery();
    InitializeComboSystem();
}

void ASoloLevelingCharacter::BeginPlay()
{
    Super::BeginPlay();

    UpdateCharacterStats();
    UE_LOG(LogTemp, Warning, TEXT("Solo Leveling Character initialized"));
}

void ASoloLevelingCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateCombatState();
    UpdateStanceEffects();
    UpdateComboTiming(DeltaTime);
}

void ASoloLevelingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Movement bindings
    PlayerInputComponent->BindAxis("MoveForward", this, &ASoloLevelingCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASoloLevelingCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &ASoloLevelingCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &ASoloLevelingCharacter::LookUp);

    // Action bindings
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASoloLevelingCharacter::Jump);
    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ASoloLevelingCharacter::StartAttack);
    PlayerInputComponent->BindAction("Attack", IE_Released, this, &ASoloLevelingCharacter::StopAttack);
    PlayerInputComponent->BindAction("Block", IE_Pressed, this, &ASoloLevelingCharacter::StartBlock);
    PlayerInputComponent->BindAction("Block", IE_Released, this, &ASoloLevelingCharacter::StopBlock);
    PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &ASoloLevelingCharacter::DodgePressed);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASoloLevelingCharacter::SprintStart);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASoloLevelingCharacter::SprintStop);

    // Stance switching
    PlayerInputComponent->BindAction("SwitchStanceBalanced", IE_Pressed, this, [this]() { SwitchStance(ECombatStance::CS_Balanced); });
    PlayerInputComponent->BindAction("SwitchStanceAggressive", IE_Pressed, this, [this]() { SwitchStance(ECombatStance::CS_Aggressive); });
    PlayerInputComponent->BindAction("SwitchStanceDefensive", IE_Pressed, this, [this]() { SwitchStance(ECombatStance::CS_Defensive); });
    PlayerInputComponent->BindAction("SwitchStanceTactical", IE_Pressed, this, [this]() { SwitchStance(ECombatStance::CS_Tactical); });
    PlayerInputComponent->BindAction("SwitchStanceShadow", IE_Pressed, this, [this]() { SwitchStance(ECombatStance::CS_Shadow); });

    // Advanced movement
    PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ASoloLevelingCharacter::Dash);
    PlayerInputComponent->BindAction("ShadowStep", IE_Pressed, this, &ASoloLevelingCharacter::ShadowStep);
}

void ASoloLevelingCharacter::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ASoloLevelingCharacter::MoveRight(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void ASoloLevelingCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void ASoloLevelingCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void ASoloLevelingCharacter::Jump()
{
    if (bCanDoubleJump && CanJump())
    {
        Super::Jump();
    }
}

void ASoloLevelingCharacter::StartAttack()
{
    if (!bIsAttacking && !bIsBlocking)
    {
        bIsAttacking = true;
        bIsInCombat = true;
        
        PlayAttackAnimation();
        AddComboMove(TEXT("Attack"));
        
        UE_LOG(LogTemp, Warning, TEXT("Attack started"));
    }
}

void ASoloLevelingCharacter::StopAttack()
{
    bIsAttacking = false;
}

void ASoloLevelingCharacter::StartBlock()
{
    if (!bIsAttacking)
    {
        bIsBlocking = true;
        PlayBlockAnimation();
        UE_LOG(LogTemp, Warning, TEXT("Block started"));
    }
}

void ASoloLevelingCharacter::StopBlock()
{
    bIsBlocking = false;
}

void ASoloLevelingCharacter::DodgePressed()
{
    if (!bIsDodging && !bIsAttacking)
    {
        Dodge();
    }
}

void ASoloLevelingCharacter::SprintStart()
{
    bIsSprinting = true;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
    }
}

void ASoloLevelingCharacter::SprintStop()
{
    bIsSprinting = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
    }
}

void ASoloLevelingCharacter::Attack()
{
    if (!bIsAttacking)
    {
        StartAttack();
    }
}

void ASoloLevelingCharacter::HeavyAttack()
{
    if (!bIsAttacking && !bIsBlocking)
    {
        bIsAttacking = true;
        bIsInCombat = true;
        
        PlayHeavyAttackAnimation();
        AddComboMove(TEXT("HeavyAttack"));
        
        UE_LOG(LogTemp, Warning, TEXT("Heavy attack started"));
    }
}

void ASoloLevelingCharacter::Block()
{
    if (!bIsBlocking)
    {
        StartBlock();
    }
}

void ASoloLevelingCharacter::Dodge()
{
    if (!bIsDodging)
    {
        bIsDodging = true;
        PlayDodgeAnimation();
        
        // Execute dodge movement
        FVector DodgeDirection = GetLastMovementInputVector();
        if (DodgeDirection.IsNearlyZero())
        {
            DodgeDirection = GetActorForwardVector();
        }
        
        LaunchCharacter(DodgeDirection * DashSpeed, true, true);
        
        // Set timer to end dodge
        FTimerHandle DodgeTimer;
        GetWorldTimerManager().SetTimer(DodgeTimer, this, &ASoloLevelingCharacter::EndDodge, 0.3f, false);
        
        UE_LOG(LogTemp, Warning, TEXT("Dodge executed"));
    }
}

void ASoloLevelingCharacter::EndDodge()
{
    bIsDodging = false;
}

void ASoloLevelingCharacter::Parry()
{
    if (bIsBlocking)
    {
        // Check for perfect parry timing
        if (ExecutePerfectTimingAction(TEXT("Parry")))
        {
            UE_LOG(LogTemp, Warning, TEXT("Perfect parry executed!"));
            // Apply parry effects (counter attack, stun, etc.)
        }
    }
}

void ASoloLevelingCharacter::SwitchStance(ECombatStance NewStance)
{
    if (CanSwitchStance(NewStance))
    {
        ECombatStance OldStance = CurrentStance;
        CurrentStance = NewStance;
        
        ApplyStanceEffects();
        OnStanceChanged.Broadcast(OldStance, NewStance);
        
        UE_LOG(LogTemp, Warning, TEXT("Switched to stance: %d"), (int32)NewStance);
    }
}

bool ASoloLevelingCharacter::CanSwitchStance(ECombatStance NewStance)
{
    // Can switch stances if not in the middle of an attack
    return !bIsAttacking && !bIsDodging;
}

void ASoloLevelingCharacter::ExecuteAdvancedMovement(EMovementType MovementType)
{
    switch (MovementType)
    {
        case EMovementType::MT_Dash:
            Dash();
            break;
        case EMovementType::MT_ShadowStep:
            ShadowStep();
            break;
        case EMovementType::MT_Teleport:
            // Teleport to aimed location
            break;
        case EMovementType::MT_Flight:
            // Enable flight mode
            break;
        case EMovementType::MT_Phase:
            // Phase through objects
            break;
        default:
            break;
    }
}

void ASoloLevelingCharacter::Dash()
{
    if (!bIsDodging)
    {
        FVector DashDirection = GetActorForwardVector();
        LaunchCharacter(DashDirection * DashSpeed, true, true);
        
        UE_LOG(LogTemp, Warning, TEXT("Dash executed"));
    }
}

void ASoloLevelingCharacter::ShadowStep()
{
    if (bCanSummonShadows && !bIsDodging)
    {
        FVector ShadowStepLocation = GetActorLocation() + GetActorForwardVector() * ShadowStepDistance;
        
        // Create shadow effect at current location
        // Teleport to new location
        SetActorLocation(ShadowStepLocation, false, nullptr, ETeleportType::TeleportPhysics);
        
        UE_LOG(LogTemp, Warning, TEXT("Shadow step executed"));
    }
}

void ASoloLevelingCharacter::Teleport(FVector TargetLocation)
{
    SetActorLocation(TargetLocation, false, nullptr, ETeleportType::TeleportPhysics);
    UE_LOG(LogTemp, Warning, TEXT("Teleported to location"));
}

void ASoloLevelingCharacter::AddComboMove(FName MoveName)
{
    CurrentCombo.Add(MoveName);
    ComboTimer = ComboTimingWindow;
    ComboCount++;
    
    // Check if combo matches any available combos
    CheckComboTiming();
}

void ASoloLevelingCharacter::ExecuteCombo()
{
    if (CurrentCombo.Num() > 0)
    {
        // Find matching combo
        for (const FComboData& Combo : AvailableCombos)
        {
            if (Combo.ComboSequence == CurrentCombo)
            {
                // Execute combo effects
                float TotalDamage = BaseDamage * Combo.DamageMultiplier;
                CalculateDamage();
                
                OnComboExecuted.Broadcast(CurrentCombo, TotalDamage);
                
                UE_LOG(LogTemp, Warning, TEXT("Combo executed: %s"), *CurrentCombo[0].ToString());
                break;
            }
        }
        
        ResetCombo();
    }
}

bool ASoloLevelingCharacter::CheckComboTiming()
{
    if (ComboTimer > 0.0f)
    {
        // Check if current combo matches any available combos
        for (const FComboData& Combo : AvailableCombos)
        {
            if (Combo.ComboSequence.Num() <= CurrentCombo.Num())
            {
                bool bMatches = true;
                for (int32 i = 0; i < Combo.ComboSequence.Num(); i++)
                {
                    if (Combo.ComboSequence[i] != CurrentCombo[i])
                    {
                        bMatches = false;
                        break;
                    }
                }
                
                if (bMatches)
                {
                    ExecuteCombo();
                    return true;
                }
            }
        }
    }
    
    return false;
}

void ASoloLevelingCharacter::ResetCombo()
{
    CurrentCombo.Empty();
    ComboCount = 0;
    ComboTimer = 0.0f;
}

void ASoloLevelingCharacter::UpdateWeaponMastery(EWeaponType WeaponType, float Experience)
{
    if (WeaponMastery.Contains(WeaponType))
    {
        FWeaponMasteryData& MasteryData = WeaponMastery[WeaponType];
        MasteryData.ExperiencePoints += Experience;
        
        // Check for level up
        float RequiredExperience = MasteryData.MasteryLevel * 100.0f;
        if (MasteryData.ExperiencePoints >= RequiredExperience)
        {
            MasteryData.MasteryLevel++;
            MasteryData.ExperiencePoints -= RequiredExperience;
            
            UE_LOG(LogTemp, Warning, TEXT("Weapon mastery leveled up: %d"), MasteryData.MasteryLevel);
        }
    }
}

void ASoloLevelingCharacter::UnlockCombo(FName ComboName)
{
    // Add combo to available combos based on weapon mastery
    for (TPair<EWeaponType, FWeaponMasteryData>& MasteryPair : WeaponMastery)
    {
        if (!MasteryPair.Value.UnlockedCombos.Contains(ComboName))
        {
            MasteryPair.Value.UnlockedCombos.Add(ComboName);
            UE_LOG(LogTemp, Warning, TEXT("Combo unlocked: %s"), *ComboName.ToString());
            break;
        }
    }
}

void ASoloLevelingCharacter::ActivatePowerSystem(UPowerSystemComponent* PowerSystem)
{
    if (PowerSystem && !ActivePowerSystems.Contains(PowerSystem))
    {
        ActivePowerSystems.Add(PowerSystem);
        PowerSystem->ActivateSystem();
        
        UE_LOG(LogTemp, Warning, TEXT("Power system activated"));
    }
}

void ASoloLevelingCharacter::DeactivatePowerSystem(UPowerSystemComponent* PowerSystem)
{
    if (PowerSystem && ActivePowerSystems.Contains(PowerSystem))
    {
        ActivePowerSystems.Remove(PowerSystem);
        PowerSystem->DeactivateSystem();
        
        UE_LOG(LogTemp, Warning, TEXT("Power system deactivated"));
    }
}

void ASoloLevelingCharacter::UsePowerSystemAbility(FName AbilityName)
{
    for (UPowerSystemComponent* PowerSystem : ActivePowerSystems)
    {
        if (PowerSystem->HasAbility(AbilityName))
        {
            PowerSystem->UseAbility(AbilityName);
            break;
        }
    }
}

void ASoloLevelingCharacter::SummonShadow(AEnemy* TargetEnemy)
{
    if (bCanSummonShadows && TargetEnemy)
    {
        // Extract shadow from defeated enemy
        ShadowArmySize++;
        
        OnShadowSummoned.Broadcast(TargetEnemy, ShadowArmySize);
        
        UE_LOG(LogTemp, Warning, TEXT("Shadow summoned. Army size: %d"), ShadowArmySize);
    }
}

void ASoloLevelingCharacter::CommandShadowArmy()
{
    if (ShadowArmySize > 0)
    {
        // Command all shadows to attack
        UE_LOG(LogTemp, Warning, TEXT("Commanding shadow army of %d shadows"), ShadowArmySize);
    }
}

void ASoloLevelingCharacter::DismissShadowArmy()
{
    ShadowArmySize = 0;
    UE_LOG(LogTemp, Warning, TEXT("Shadow army dismissed"));
}

bool ASoloLevelingCharacter::ExecutePerfectTimingAction(FName ActionName)
{
    // Check if action is within perfect timing window
    // This would be implemented with proper timing detection
    return FMath::FRand() < 0.3f; // 30% chance for now
}

void ASoloLevelingCharacter::ShowTimingWindow()
{
    // Visual feedback for perfect timing window
    UE_LOG(LogTemp, Warning, TEXT("Perfect timing window available"));
}

void ASoloLevelingCharacter::UpdateCombatState()
{
    // Update combat state based on recent actions
    if (LastAttackTime > 0.0f && (GetWorld()->GetTimeSeconds() - LastAttackTime) > 5.0f)
    {
        bIsInCombat = false;
    }
}

void ASoloLevelingCharacter::UpdateStanceEffects()
{
    // Apply stance-specific effects
    switch (CurrentStance)
    {
        case ECombatStance::CS_Aggressive:
            BaseDamage = 15.0f;
            CriticalChance = 0.15f;
            break;
        case ECombatStance::CS_Defensive:
            BaseDamage = 8.0f;
            // Increase defense
            break;
        case ECombatStance::CS_Tactical:
            // Increase perception and strategy
            break;
        case ECombatStance::CS_Shadow:
            // Enable shadow abilities
            bCanSummonShadows = true;
            break;
        default:
            BaseDamage = 10.0f;
            CriticalChance = 0.1f;
            break;
    }
}

void ASoloLevelingCharacter::UpdateComboTiming(float DeltaTime)
{
    if (ComboTimer > 0.0f)
    {
        ComboTimer -= DeltaTime;
        if (ComboTimer <= 0.0f)
        {
            ResetCombo();
        }
    }
}

void ASoloLevelingCharacter::InitializeWeaponMastery()
{
    // Initialize weapon mastery for all weapon types
    for (int32 i = 0; i < (int32)EWeaponType::WT_Shadow + 1; i++)
    {
        FWeaponMasteryData MasteryData;
        MasteryData.WeaponType = (EWeaponType)i;
        MasteryData.MasteryLevel = 1;
        MasteryData.KillCount = 0;
        MasteryData.ExperiencePoints = 0.0f;
        
        WeaponMastery.Add((EWeaponType)i, MasteryData);
    }
}

void ASoloLevelingCharacter::InitializeComboSystem()
{
    // Initialize basic combos
    FComboData BasicCombo;
    BasicCombo.ComboSequence.Add(TEXT("Attack"));
    BasicCombo.ComboSequence.Add(TEXT("Attack"));
    BasicCombo.DamageMultiplier = 1.5f;
    BasicCombo.TimingWindow = 1.0f;
    AvailableCombos.Add(BasicCombo);
    
    FComboData HeavyCombo;
    HeavyCombo.ComboSequence.Add(TEXT("Attack"));
    HeavyCombo.ComboSequence.Add(TEXT("HeavyAttack"));
    HeavyCombo.DamageMultiplier = 2.0f;
    HeavyCombo.TimingWindow = 1.5f;
    AvailableCombos.Add(HeavyCombo);
}

void ASoloLevelingCharacter::CalculateDamage()
{
    // Calculate damage based on weapon mastery, stance, and power systems
    float TotalDamage = BaseDamage;
    
    // Apply weapon mastery bonus
    if (WeaponMastery.Contains(CurrentWeaponType))
    {
        const FWeaponMasteryData& MasteryData = WeaponMastery[CurrentWeaponType];
        TotalDamage *= (1.0f + MasteryData.MasteryLevel * 0.1f);
    }
    
    // Apply critical hit chance
    if (FMath::FRand() < CriticalChance)
    {
        TotalDamage *= CriticalMultiplier;
        UE_LOG(LogTemp, Warning, TEXT("Critical hit! Damage: %.2f"), TotalDamage);
    }
}

void ASoloLevelingCharacter::ApplyStanceEffects()
{
    UpdateStanceEffects();
}

void ASoloLevelingCharacter::UpdateCharacterStats()
{
    // Update character stats based on level, equipment, and power systems
    MaxHealth = 100.0f + (ActivePowerSystems.Num() * 10.0f);
    MaxPower = 100.0f + (ActivePowerSystems.Num() * 15.0f);
    
    Health = FMath::Min(Health, MaxHealth);
    Power = FMath::Min(Power, MaxPower);
}

void ASoloLevelingCharacter::PlayAttackAnimation()
{
    if (USkeletalMeshComponent* Mesh = GetMesh())
    {
        // Play attack animation montage
        UE_LOG(LogTemp, Warning, TEXT("Playing attack animation"));
    }
}

void ASoloLevelingCharacter::PlayHeavyAttackAnimation()
{
    if (USkeletalMeshComponent* Mesh = GetMesh())
    {
        // Play heavy attack animation montage
        UE_LOG(LogTemp, Warning, TEXT("Playing heavy attack animation"));
    }
}

void ASoloLevelingCharacter::PlayBlockAnimation()
{
    if (USkeletalMeshComponent* Mesh = GetMesh())
    {
        // Play block animation montage
        UE_LOG(LogTemp, Warning, TEXT("Playing block animation"));
    }
}

void ASoloLevelingCharacter::PlayDodgeAnimation()
{
    if (USkeletalMeshComponent* Mesh = GetMesh())
    {
        // Play dodge animation montage
        UE_LOG(LogTemp, Warning, TEXT("Playing dodge animation"));
    }
}
