#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "SoloLevelingCharacter.generated.h"

UENUM(BlueprintType)
enum class ECombatStance : uint8
{
    CS_Balanced,
    CS_Aggressive,
    CS_Defensive,
    CS_Tactical,
    CS_Shadow,
    CS_Ultimate
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    WT_Dagger,
    WT_Sword,
    WT_Greatsword,
    WT_Spear,
    WT_Fist,
    WT_Bow,
    WT_Staff,
    WT_Shadow
};

UENUM(BlueprintType)
enum class EMovementType : uint8
{
    MT_Normal,
    MT_Dash,
    MT_ShadowStep,
    MT_Teleport,
    MT_Flight,
    MT_Phase
};

USTRUCT(BlueprintType)
struct FWeaponMasteryData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWeaponType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MasteryLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 KillCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> UnlockedCombos;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ExperiencePoints;
};

USTRUCT(BlueprintType)
struct FComboData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> ComboSequence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimingWindow;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bRequiresSpecificWeapon;
};

UCLASS()
class SIMPLEAPP_API ASoloLevelingCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASoloLevelingCharacter();

    // Core Character Properties
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
    ECombatStance CurrentStance;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
    bool bIsInCombat;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
    float Health;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
    float MaxHealth;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
    float Power;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
    float MaxPower;

    // Weapon Mastery System
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    TMap<EWeaponType, FWeaponMasteryData> WeaponMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    EWeaponType CurrentWeaponType;

    // Combo System
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    TArray<FName> CurrentCombo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    TArray<FComboData> AvailableCombos;

    // Power System Integration
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power Systems")
    TArray<class UPowerSystemComponent*> ActivePowerSystems;

    // Movement Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float DashSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float ShadowStepDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bCanDoubleJump;

    // Combat Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float BaseDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float CriticalChance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float CriticalMultiplier;

    // Shadow Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shadow")
    int32 ShadowArmySize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shadow")
    bool bCanSummonShadows;

    // Override ACharacter functions
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // Combat Functions
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Attack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void HeavyAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Block();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Dodge();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Parry();

    // Stance System
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void SwitchStance(ECombatStance NewStance);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool CanSwitchStance(ECombatStance NewStance);

    // Movement Functions
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void ExecuteAdvancedMovement(EMovementType MovementType);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Dash();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void ShadowStep();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Teleport(FVector TargetLocation);

    // Combo System
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void AddComboMove(FName MoveName);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ExecuteCombo();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool CheckComboTiming();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ResetCombo();

    // Weapon Mastery
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void UpdateWeaponMastery(EWeaponType WeaponType, float Experience);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void UnlockCombo(FName ComboName);

    // Power System Integration
    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void ActivatePowerSystem(class UPowerSystemComponent* PowerSystem);

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void DeactivatePowerSystem(class UPowerSystemComponent* PowerSystem);

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void UsePowerSystemAbility(FName AbilityName);

    // Shadow Army
    UFUNCTION(BlueprintCallable, Category = "Shadow")
    void SummonShadow(class AEnemy* TargetEnemy);

    UFUNCTION(BlueprintCallable, Category = "Shadow")
    void CommandShadowArmy();

    UFUNCTION(BlueprintCallable, Category = "Shadow")
    void DismissShadowArmy();

    // Perfect Timing System
    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool ExecutePerfectTimingAction(FName ActionName);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ShowTimingWindow();

    // Events
    UPROPERTY(BlueprintAssignable, Category = "Character Events")
    FOnCharacterDamaged OnCharacterDamaged;

    UPROPERTY(BlueprintAssignable, Category = "Character Events")
    FOnCharacterHealed OnCharacterHealed;

    UPROPERTY(BlueprintAssignable, Category = "Character Events")
    FOnStanceChanged OnStanceChanged;

    UPROPERTY(BlueprintAssignable, Category = "Character Events")
    FOnComboExecuted OnComboExecuted;

    UPROPERTY(BlueprintAssignable, Category = "Character Events")
    FOnShadowSummoned OnShadowSummoned;

protected:
    // Input Actions
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);

    void Jump();
    void StartAttack();
    void StopAttack();
    void StartBlock();
    void StopBlock();
    void DodgePressed();
    void SprintStart();
    void SprintStop();

    // Combat State Management
    void UpdateCombatState();
    void UpdateStanceEffects();
    void UpdateComboTiming(float DeltaTime);

    // Animation
    void PlayAttackAnimation();
    void PlayHeavyAttackAnimation();
    void PlayBlockAnimation();
    void PlayDodgeAnimation();

private:
    // Internal State
    bool bIsAttacking;
    bool bIsBlocking;
    bool bIsDodging;
    bool bIsSprinting;
    float ComboTimer;
    float LastAttackTime;
    int32 ComboCount;

    // Timing Windows
    float PerfectDodgeWindow;
    float PerfectParryWindow;
    float ComboTimingWindow;

    // Movement
    FVector LastMovementInput;
    float SprintSpeedMultiplier;

    // Helper Functions
    void InitializeWeaponMastery();
    void InitializeComboSystem();
    void CalculateDamage();
    void ApplyStanceEffects();
    void UpdateCharacterStats();
};
