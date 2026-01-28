# 🎮 Unreal Engine 5 Project Setup Guide

## Step 1: Project Creation

### Create New Project
```bash
1. Launch Unreal Engine 5.3+
2. Click "Games" → "Next"
3. Select "Third Person" template
4. Project Name: "SoloLevelingShadowMonarch"
5. Location: Your development folder
6. Engine: Unreal Engine 5.3
7. Include starter content: YES
8. Create Project
```

### Project Configuration
```cpp
// Config/DefaultEngine.ini
[/Script/EngineSettings.GameMapsSettings]
GameDefaultMap=/Game/Maps/MainMenu.MainMenu
GlobalDefaultGameMode=/Game/Blueprints/BP_ShadowMonarchGameMode.BP_ShadowMonarchGameMode_C

[/Script/Engine.RendererSettings]
r.MobileHDR=1
r.MobileTonemapperUpscale=1
```

## Step 2: Folder Structure

### Create Project Structure
```
SoloLevelingShadowMonarch/
├── Content/
│   ├── Blueprints/
│   │   ├── Characters/
│   │   ├── Combat/
│   │   ├── UI/
│   │   ├── Systems/
│   │   └── World/
│   ├── Materials/
│   ├── Meshes/
│   │   ├── Characters/
│   │   ├── Weapons/
│   │   └── Environment/
│   ├── Textures/
│   ├── Animations/
│   ├── Audio/
│   └── Maps/
│       ├── Hub/
│       ├── Dungeons/
│       └── Menus/
├── Config/
├── Source/
│   └── SoloLevelingShadowMonarch/
│       ├── Private/
│       ├── Public/
│       └── Classes/
└── Saved/
```

## Step 3: C++ Classes Setup

### Create Core C++ Classes

#### 1. Game Mode
```cpp
// ShadowMonarchGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShadowMonarchGameMode.generated.h"

UCLASS()
class SOLOLEVELINGSHADOWMONARCH_API AShadowMonarchGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AShadowMonarchGameMode();

    virtual void BeginPlay() override;
    virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Player")
    TSubclassOf<class AShadowMonarchCharacter> DefaultCharacterClass;

    UPROPERTY(EditDefaultsOnly, Category = "Player")
    TSubclassOf<class AShadowMonarchPlayerController> DefaultPlayerControllerClass;
};
```

```cpp
// ShadowMonarchGameMode.cpp
#include "ShadowMonarchGameMode.h"
#include "ShadowMonarchCharacter.h"
#include "ShadowMonarchPlayerController.h"

AShadowMonarchGameMode::AShadowMonarchGameMode()
{
    DefaultPawnClass = AShadowMonarchCharacter::StaticClass();
    PlayerControllerClass = AShadowMonarchPlayerController::StaticClass();
}

void AShadowMonarchGameMode::BeginPlay()
{
    Super::BeginPlay();
}

void AShadowMonarchGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
}
```

#### 2. Character Class
```cpp
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

    // Movement
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);

    // Combat
    void LightAttack();
    void HeavyAttack();
    void Dodge();
    void LockOn();

    // Camera
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent* CameraBoom;

    // Combat System
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    class UCombatComponent* CombatComponent;

    // Stats System
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
    class UHunterStatsComponent* HunterStats;

    // Shadow Army
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shadows")
    class UShadowArmyComponent* ShadowArmyComponent;

public:
    virtual void Tick(float DeltaTime) override;
};
```

#### 3. Player Controller
```cpp
// ShadowMonarchPlayerController.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShadowMonarchPlayerController.generated.h"

UCLASS()
class SOLOLEVELINGSHADOWMONARCH_API AShadowMonarchPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AShadowMonarchPlayerController();

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    // UI
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> MainHUDClass;

    UPROPERTY()
    class UUserWidget* MainHUD;

    // Targeting System
    UPROPERTY()
    class AActor* LockedTarget;

    void ToggleLockOn();
    void ReleaseLockOn();

    // Input Actions
    void OnPauseMenu();
    void OnInventory();
    void OnCharacterSheet();
    void OnShadowArmy();
};
```

## Step 4: Component Systems

### 1. Hunter Stats Component
```cpp
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

    UPROPERTY(BlueprintReadOnly)
    int32 Level = 1;

    UPROPERTY(BlueprintReadOnly)
    EHuntRank HunterRank = EHuntRank::E_Rank;

    UPROPERTY(BlueprintReadOnly)
    int32 Experience = 0;

    UPROPERTY(BlueprintReadOnly)
    int32 ExperienceToNext = 100;

    UPROPERTY(BlueprintReadOnly)
    float HealthPoints = 100.0f;

    UPROPERTY(BlueprintReadOnly)
    float MaxHealthPoints = 100.0f;

    UPROPERTY(BlueprintReadOnly)
    float ManaPoints = 50.0f;

    UPROPERTY(BlueprintReadOnly)
    float MaxManaPoints = 50.0f;

    UPROPERTY(BlueprintReadOnly)
    float AttackPower = 10.0f;

    UPROPERTY(BlueprintReadOnly)
    float Defense = 5.0f;

    UPROPERTY(BlueprintReadOnly)
    float MagicPower = 8.0f;

    UPROPERTY(BlueprintReadOnly)
    bool bIsShadowMonarch = false;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOLOLEVELINGSHADOWMONARCH_API UHunterStatsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHunterStatsComponent();

    UFUNCTION(BlueprintCallable)
    void AddExperience(int32 Amount);

    UFUNCTION(BlueprintCallable)
    void LevelUp();

    UFUNCTION(BlueprintCallable)
    bool CanLevelUp() const;

    UFUNCTION(BlueprintCallable)
    void TakeDamage(float Damage);

    UFUNCTION(BlueprintCallable)
    void Heal(float Amount);

    UPROPERTY(BlueprintReadOnly)
    FHunterStats CurrentStats;

protected:
    virtual void BeginPlay() override;

private:
    void CheckRankUp();
};
```

### 2. Combat Component
```cpp
// CombatComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UENUM(BlueprintType)
enum class ECombatState : uint8
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

    UFUNCTION(BlueprintCallable)
    void PerformLightAttack();

    UFUNCTION(BlueprintCallable)
    void PerformHeavyAttack();

    UFUNCTION(BlueprintCallable)
    void Dodge();

    UFUNCTION(BlueprintCallable)
    void LockOnTarget(AActor* Target);

    UFUNCTION(BlueprintCallable)
    void ReleaseTarget();

    UPROPERTY(BlueprintReadOnly)
    ECombatState CurrentCombatState;

    UPROPERTY(BlueprintReadOnly)
    AActor* CurrentTarget;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    float AttackRange = 200.0f;

    UPROPERTY()
    float DodgeDistance = 500.0f;

    UPROPERTY()
    float AttackCooldown = 1.0f;

    bool bCanAttack = true;
    FTimerHandle AttackTimer;
};
```

## Step 5: Input Setup

### Project Settings → Input
```
Action Mappings:
- LightAttack: Left Mouse Button
- HeavyAttack: Right Mouse Button
- Dodge: Left Shift
- LockOn: Middle Mouse Button
- Pause: Escape
- Inventory: I
- CharacterSheet: C
- ShadowArmy: S

Axis Mappings:
- MoveForward: W, S
- MoveRight: A, D
- Turn: Mouse X
- LookUp: Mouse Y
```

## Step 6: Basic UI Setup

### Main HUD Widget
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
    void ShowSystemMessage(const FString& Message);

protected:
    virtual void NativeConstruct() override;

private:
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthBar;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* ManaBar;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* ExperienceBar;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* LevelText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* HunterRankText;
};
```

## Step 7: Build Configuration

### .Build.cs File
```csharp
// SoloLevelingShadowMonarch.Build.cs
using UnrealBuildTool;

public class SoloLevelingShadowMonarch : ModuleRules
{
    public SoloLevelingShadowMonarch(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] 
        { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore",
            "EnhancedInput",
            "GameplayTags",
            "GameplayTasks",
            "UMG"
        });

        PrivateDependencyModuleNames.AddRange(new string[] 
        { 
            "Slate", 
            "SlateCore" 
        });
    }
}
```

## Step 8: Initial Testing

### Create Test Map
1. Create new level: `/Game/Maps/TestLevel`
2. Add Player Start
3. Add basic geometry for testing
4. Add some test enemies
5. Set as default map for testing

### Compile and Test
```bash
1. Compile project in Visual Studio
2. Launch in editor
3. Test basic movement
4. Test UI display
5. Verify save/load functionality
```

---

## 🎯 NEXT STEPS

After completing this setup:

1. **Implement character animations**
2. **Create combat mechanics**
3. **Build enemy AI system**
4. **Design dungeon layouts**
5. **Implement Shadow Army system**

**You're now ready to start building your Solo Leveling RPG! 🚀**
