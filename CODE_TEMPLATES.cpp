// 🎯 SOLO LEVELING: SHADOW MONARCH - CODE TEMPLATES
// Copy-paste ready C++ templates for immediate implementation

#pragma once

// ========================================
// TEMPLATE 1: CHARACTER CLASS
// ========================================

// ShadowMonarchCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShadowMonarchCharacter.generated.h"

UCLASS()
class SOLOLEVELINGSHADOWMONARCH_API AShadowMonarchCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AShadowMonarchCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Movement Functions
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);

    // Combat Functions
    void LightAttack();
    void HeavyAttack();
    void Dodge();
    void LockOnTarget();

    // Camera Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent* CameraBoom;

    // System Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Systems")
    class UHunterStatsComponent* HunterStats;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Systems")
    class UCombatComponent* CombatSystem;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Systems")
    class UShadowArmyComponent* ShadowArmy;

public:
    virtual void Tick(float DeltaTime) override;
};

// ShadowMonarchCharacter.cpp
#include "ShadowMonarchCharacter.h"
#include "HunterStatsComponent.h"
#include "CombatComponent.h"
#include "ShadowArmyComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AShadowMonarchCharacter::AShadowMonarchCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create camera boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // Create follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // Create system components
    HunterStats = CreateDefaultSubobject<UHunterStatsComponent>(TEXT("HunterStats"));
    CombatSystem = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatSystem"));
    ShadowArmy = CreateDefaultSubobject<UShadowArmyComponent>(TEXT("ShadowArmy"));
}

void AShadowMonarchCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AShadowMonarchCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    // Movement bindings
    PlayerInputComponent->BindAxis("MoveForward", this, &AShadowMonarchCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AShadowMonarchCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    
    // Combat bindings
    PlayerInputComponent->BindAction("LightAttack", IE_Pressed, this, &AShadowMonarchCharacter::LightAttack);
    PlayerInputComponent->BindAction("HeavyAttack", IE_Pressed, this, &AShadowMonarchCharacter::HeavyAttack);
    PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AShadowMonarchCharacter::Dodge);
    PlayerInputComponent->BindAction("LockOn", IE_Pressed, this, &AShadowMonarchCharacter::LockOnTarget);
}

void AShadowMonarchCharacter::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AShadowMonarchCharacter::MoveRight(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void AShadowMonarchCharacter::LightAttack()
{
    if (CombatSystem)
    {
        CombatSystem->PerformLightAttack();
    }
}

void AShadowMonarchCharacter::HeavyAttack()
{
    if (CombatSystem)
    {
        CombatSystem->PerformHeavyAttack();
    }
}

void AShadowMonarchCharacter::Dodge()
{
    if (CombatSystem)
    {
        CombatSystem->Dodge();
    }
}

void AShadowMonarchCharacter::LockOnTarget()
{
    if (CombatSystem)
    {
        CombatSystem->ToggleLockOn();
    }
}

void AShadowMonarchCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// ========================================
// TEMPLATE 2: HUNTER STATS COMPONENT
// ========================================

// HunterStatsComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HunterStatsComponent.generated.h"

UENUM(BlueprintType)
enum class EHuntRank : uint8
{
    E_Rank,
    D_Rank,
    C_Rank,
    B_Rank,
    A_Rank,
    S_Rank,
    National
};

USTRUCT(BlueprintType)
struct FHunterStats
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    int32 Level = 1;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    EHuntRank HunterRank = EHuntRank::E_Rank;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    int32 Experience = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    int32 ExperienceToNext = 100;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    float HealthPoints = 100.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    float MaxHealthPoints = 100.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    float ManaPoints = 50.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    float MaxManaPoints = 50.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    float AttackPower = 10.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    float Defense = 5.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    float MagicPower = 8.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    bool bIsShadowMonarch = false;

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    int32 ShadowExtractionCount = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOLOLEVELINGSHADOWMONARCH_API UHunterStatsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHunterStatsComponent();

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddExperience(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void LevelUp();

    UFUNCTION(BlueprintCallable, Category = "Stats")
    bool CanLevelUp() const;

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void TakeDamage(float Damage);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void Heal(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void RestoreMana(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void UpgradeHunterRank();

    UFUNCTION(BlueprintPure, Category = "Stats")
    FHunterStats GetCurrentStats() const { return CurrentStats; }

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
    FHunterStats CurrentStats;

    void CheckRankUp();
    void UpdateStats();
    void OnLevelUp();
};

// HunterStatsComponent.cpp
#include "HunterStatsComponent.h"
#include "GameFramework/Character.h"

UHunterStatsComponent::UHunterStatsComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHunterStatsComponent::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize stats
    CurrentStats.MaxHealthPoints = 100.0f;
    CurrentStats.HealthPoints = CurrentStats.MaxHealthPoints;
    CurrentStats.MaxManaPoints = 50.0f;
    CurrentStats.ManaPoints = CurrentStats.MaxManaPoints;
}

void UHunterStatsComponent::AddExperience(int32 Amount)
{
    CurrentStats.Experience += Amount;
    
    while (CanLevelUp())
    {
        LevelUp();
    }
}

void UHunterStatsComponent::LevelUp()
{
    CurrentStats.Level++;
    CurrentStats.Experience = 0;
    CurrentStats.ExperienceToNext = FMath::RoundToInt(CurrentStats.ExperienceToNext * 1.5f);
    
    // Increase base stats
    CurrentStats.MaxHealthPoints += 20.0f;
    CurrentStats.HealthPoints = CurrentStats.MaxHealthPoints;
    CurrentStats.MaxManaPoints += 10.0f;
    CurrentStats.ManaPoints = CurrentStats.MaxManaPoints;
    CurrentStats.AttackPower += 5.0f;
    CurrentStats.Defense += 3.0f;
    CurrentStats.MagicPower += 4.0f;
    
    CheckRankUp();
    OnLevelUp();
}

bool UHunterStatsComponent::CanLevelUp() const
{
    return CurrentStats.Experience >= CurrentStats.ExperienceToNext;
}

void UHunterStatsComponent::TakeDamage(float Damage)
{
    float ActualDamage = FMath::Max(1.0f, Damage - CurrentStats.Defense);
    CurrentStats.HealthPoints = FMath::Max(0.0f, CurrentStats.HealthPoints - ActualDamage);
}

void UHunterStatsComponent::Heal(float Amount)
{
    CurrentStats.HealthPoints = FMath::Min(CurrentStats.MaxHealthPoints, CurrentStats.HealthPoints + Amount);
}

void UHunterStatsComponent::RestoreMana(float Amount)
{
    CurrentStats.ManaPoints = FMath::Min(CurrentStats.MaxManaPoints, CurrentStats.ManaPoints + Amount);
}

void UHunterStatsComponent::CheckRankUp()
{
    EHuntRank NewRank = CurrentStats.HunterRank;
    
    if (CurrentStats.Level >= 500) NewRank = EHuntRank::National;
    else if (CurrentStats.Level >= 200) NewRank = EHuntRank::S_Rank;
    else if (CurrentStats.Level >= 100) NewRank = EHuntRank::A_Rank;
    else if (CurrentStats.Level >= 50) NewRank = EHuntRank::B_Rank;
    else if (CurrentStats.Level >= 25) NewRank = EHuntRank::C_Rank;
    else if (CurrentStats.Level >= 10) NewRank = EHuntRank::D_Rank;
    
    if (NewRank != CurrentStats.HunterRank)
    {
        CurrentStats.HunterRank = NewRank;
        UpgradeHunterRank();
    }
}

void UHunterStatsComponent::UpgradeHunterRank()
{
    // Apply rank bonuses
    switch (CurrentStats.HunterRank)
    {
        case EHuntRank::D_Rank:
            CurrentStats.AttackPower += 10.0f;
            break;
        case EHuntRank::C_Rank:
            CurrentStats.AttackPower += 15.0f;
            CurrentStats.Defense += 5.0f;
            break;
        case EHuntRank::B_Rank:
            CurrentStats.AttackPower += 25.0f;
            CurrentStats.Defense += 10.0f;
            break;
        case EHuntRank::A_Rank:
            CurrentStats.AttackPower += 40.0f;
            CurrentStats.Defense += 20.0f;
            CurrentStats.MagicPower += 20.0f;
            break;
        case EHuntRank::S_Rank:
            CurrentStats.AttackPower += 60.0f;
            CurrentStats.Defense += 30.0f;
            CurrentStats.MagicPower += 40.0f;
            break;
        case EHuntRank::National:
            CurrentStats.AttackPower += 100.0f;
            CurrentStats.Defense += 50.0f;
            CurrentStats.MagicPower += 80.0f;
            break;
    }
}

void UHunterStatsComponent::UpdateStats()
{
    // Update derived stats
}

void UHunterStatsComponent::OnLevelUp()
{
    // Trigger level up effects
    if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
    {
        // Play level up effect
        // Update UI
    }
}

// ========================================
// TEMPLATE 3: COMBAT COMPONENT
// ========================================

// CombatComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UENUM(BlueprintType)
enum class ECombatState : uint8
{
    Idle,
    Attacking,
    Dodging,
    Stunned,
    Dead
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOLOLEVELINGSHADOWMONARCH_API UCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCombatComponent();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void PerformLightAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void PerformHeavyAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Dodge();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ToggleLockOn();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ReleaseTarget();

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool IsAttacking() const { return CurrentCombatState == ECombatState::Attacking; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    AActor* GetCurrentTarget() const { return CurrentTarget; }

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    ECombatState CurrentCombatState;

    UPROPERTY(BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    AActor* CurrentTarget;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    float AttackRange = 200.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    float DodgeDistance = 500.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    float AttackCooldown = 1.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    float DodgeCooldown = 0.5f;

    bool bCanAttack = true;
    bool bCanDodge = true;
    
    FTimerHandle AttackTimer;
    FTimerHandle DodgeTimer;

    void ResetAttack();
    void ResetDodge();
    void FindNearestTarget();
};

// CombatComponent.cpp
#include "CombatComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

UCombatComponent::UCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    CurrentCombatState = ECombatState::Idle;
}

void UCombatComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UCombatComponent::PerformLightAttack()
{
    if (!bCanAttack || CurrentCombatState != ECombatState::Idle)
        return;

    bCanAttack = false;
    CurrentCombatState = ECombatState::Attacking;

    // Play attack animation
    if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
    {
        // Play montage or animation
        UE_LOG(LogTemp, Warning, TEXT("Light Attack!"));
    }

    // Deal damage to nearby enemies
    DealDamageInRadius(AttackRange, 1.0f); // 1.0x damage for light attack

    GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, 
        &UCombatComponent::ResetAttack, AttackCooldown);
}

void UCombatComponent::PerformHeavyAttack()
{
    if (!bCanAttack || CurrentCombatState != ECombatState::Idle)
        return;

    bCanAttack = false;
    CurrentCombatState = ECombatState::Attacking;

    // Play heavy attack animation
    if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Heavy Attack!"));
    }

    // Deal damage with higher multiplier
    DealDamageInRadius(AttackRange * 1.2f, 2.0f); // 2.0x damage for heavy attack

    GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, 
        &UCombatComponent::ResetAttack, AttackCooldown * 1.5f);
}

void UCombatComponent::Dodge()
{
    if (!bCanDodge || CurrentCombatState != ECombatState::Idle)
        return;

    bCanDodge = false;
    CurrentCombatState = ECombatState::Dodging;

    // Perform dodge movement
    if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
    {
        FVector DodgeDirection = Character->GetActorForwardVector();
        Character->LaunchCharacter(DodgeDirection * DodgeDistance, true, true);
        
        UE_LOG(LogTemp, Warning, TEXT("Dodge!"));
    }

    GetWorld()->GetTimerManager().SetTimer(DodgeTimer, this, 
        &UCombatComponent::ResetDodge, DodgeCooldown);
}

void UCombatComponent::ToggleLockOn()
{
    if (CurrentTarget)
    {
        ReleaseTarget();
    }
    else
    {
        FindNearestTarget();
    }
}

void UCombatComponent::ReleaseTarget()
{
    CurrentTarget = nullptr;
    UE_LOG(LogTemp, Warning, TEXT("Target Released"));
}

void UCombatComponent::FindNearestTarget()
{
    // Simple target finding - can be enhanced with line of sight checks
    FVector OwnerLocation = GetOwner()->GetActorLocation();
    
    // Find all actors in range
    TArray<FOverlapResult> OverlapResults;
    FCollisionShape Sphere = FCollisionShape::MakeSphere(1000.0f); // 10m detection range
    
    if (GetWorld()->OverlapMultiByChannel(OverlapResults, OwnerLocation, FQuat::Identity, 
        ECC_Pawn, Sphere))
    {
        AActor* NearestTarget = nullptr;
        float NearestDistance = 1000.0f;

        for (const FOverlapResult& Result : OverlapResults)
        {
            AActor* Actor = Result.GetActor();
            if (Actor && Actor != GetOwner())
            {
                float Distance = FVector::Dist(OwnerLocation, Actor->GetActorLocation());
                if (Distance < NearestDistance)
                {
                    NearestDistance = Distance;
                    NearestTarget = Actor;
                }
            }
        }

        CurrentTarget = NearestTarget;
        if (CurrentTarget)
        {
            UE_LOG(LogTemp, Warning, TEXT("Target Locked: %s"), *CurrentTarget->GetName());
        }
    }
}

void UCombatComponent::ResetAttack()
{
    bCanAttack = true;
    CurrentCombatState = ECombatState::Idle;
}

void UCombatComponent::ResetDodge()
{
    bCanDodge = true;
    CurrentCombatState = ECombatState::Idle;
}

void UCombatComponent::DealDamageInRadius(float Radius, float DamageMultiplier)
{
    // This would be implemented with actual damage system
    FVector OwnerLocation = GetOwner()->GetActorLocation();
    
    // Debug visualization
    DrawDebugSphere(GetWorld(), OwnerLocation, Radius, 12, FColor::Red, false, 2.0f);
    
    UE_LOG(LogTemp, Warning, TEXT("Dealing %.1fx damage in %.0f radius"), DamageMultiplier, Radius);
}

// ========================================
// TEMPLATE 4: SHADOW ARMY COMPONENT
// ========================================

// ShadowArmyComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShadowArmyComponent.generated.h"

UENUM(BlueprintType)
enum class EShadowRank : uint8
{
    Soldier,
    Mage,
    Knight,
    General,
    Monarch
};

USTRUCT(BlueprintType)
struct FShadowData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString ShadowName;

    UPROPERTY(BlueprintReadOnly)
    EShadowRank Rank;

    UPROPERTY(BlueprintReadOnly)
    int32 Level;

    UPROPERTY(BlueprintReadOnly)
    float Health;

    UPROPERTY(BlueprintReadOnly)
    float AttackPower;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOLOLEVELINGSHADOWMONARCH_API UShadowArmyComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UShadowArmyComponent();

    UFUNCTION(BlueprintCallable, Category = "Shadow Army")
    bool ExtractShadowFromEnemy(class AActor* Enemy);

    UFUNCTION(BlueprintCallable, Category = "Shadow Army")
    void SummonShadow(const FShadowData& Shadow);

    UFUNCTION(BlueprintCallable, Category = "Shadow Army")
    void CommandShadowArmy(const FString& Command);

    UFUNCTION(BlueprintPure, Category = "Shadow Army")
    TArray<FShadowData> GetShadowArmy() const { return ShadowArmy; }

    UFUNCTION(BlueprintPure, Category = "Shadow Army")
    int32 GetShadowCount() const { return ShadowArmy.Num(); }

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(BlueprintReadOnly, Category = "Shadow Army", meta = (AllowPrivateAccess = "true"))
    TArray<FShadowData> ShadowArmy;

    UPROPERTY(EditDefaultsOnly, Category = "Shadow Army")
    int32 MaxShadowArmySize = 10;

    UPROPERTY(EditDefaultsOnly, Category = "Shadow Army")
    float ExtractionChance = 0.5f;

    bool CanExtractShadow() const;
    FShadowData CreateShadowFromEnemy(class AActor* Enemy);
};

// ShadowArmyComponent.cpp
#include "ShadowArmyComponent.h"

UShadowArmyComponent::UShadowArmyComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UShadowArmyComponent::BeginPlay()
{
    Super::BeginPlay();
}

bool UShadowArmyComponent::ExtractShadowFromEnemy(AActor* Enemy)
{
    if (!CanExtractShadow() || !Enemy)
        return false;

    // Random chance to extract shadow
    if (FMath::FRand() > ExtractionChance)
        return false;

    FShadowData NewShadow = CreateShadowFromEnemy(Enemy);
    
    if (ShadowArmy.Num() < MaxShadowArmySize)
    {
        ShadowArmy.Add(NewShadow);
        UE_LOG(LogTemp, Warning, TEXT("Shadow Extracted: %s"), *NewShadow.ShadowName);
        return true;
    }

    return false;
}

void UShadowArmyComponent::SummonShadow(const FShadowData& Shadow)
{
    // Implementation would spawn actual shadow actor
    UE_LOG(LogTemp, Warning, TEXT("Summoning Shadow: %s"), *Shadow.ShadowName);
}

void UShadowArmyComponent::CommandShadowArmy(const FString& Command)
{
    UE_LOG(LogTemp, Warning, TEXT("Commanding Shadow Army: %s"), *Command);
    
    for (const FShadowData& Shadow : ShadowArmy)
    {
        // Issue command to each shadow
        UE_LOG(LogTemp, Warning, TEXT("  %s follows command"), *Shadow.ShadowName);
    }
}

bool UShadowArmyComponent::CanExtractShadow() const
{
    return ShadowArmy.Num() < MaxShadowArmySize;
}

FShadowData UShadowArmyComponent::CreateShadowFromEnemy(AActor* Enemy)
{
    FShadowData NewShadow;
    NewShadow.ShadowName = FString::Printf(TEXT("Shadow %s"), *Enemy->GetName());
    NewShadow.Rank = EShadowRank::Soldier; // Default rank
    NewShadow.Level = FMath::RandRange(1, 10);
    NewShadow.Health = 100.0f + (NewShadow.Level * 10);
    NewShadow.AttackPower = 10.0f + (NewShadow.Level * 2);
    
    return NewShadow;
}

/*
========================================
USAGE INSTRUCTIONS:
========================================

1. Copy these templates into your Visual Studio project
2. Add them to your SoloLevelingShadowMonarch.Build.cs
3. Compile and test each component
4. Customize based on your specific needs

Each template includes:
- Header file with UCLASS/USTRUCT definitions
- Implementation file with core functionality
- Blueprint integration for easy use
- Solo Leveling specific features

Start with Character class, then add components!
========================================
*/
