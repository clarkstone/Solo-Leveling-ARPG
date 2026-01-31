#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "NPC.generated.h"

UENUM(BlueprintType)
enum class ENPCType : uint8
{
    NT_QuestGiver,
    NT_Merchant,
    NT_Trainer,
    NT_Blacksmith,
    NT_Alchemist,
    NT_Enchanter,
    NT_StoryCharacter,
    NT_GuildMaster,
    NT_Guard,
    NT_Villager
};

UENUM(BlueprintType)
enum class ENPCState : uint8
{
    NS_Idle,
    NS_Patrol,
    NS_Dialogue,
    NS_Training,
    NS_Working,
    NS_Sleeping,
    NS_Emergency
};

UCLASS()
class SIMPLEAPP_API ANPC : public ACharacter
{
    GENERATED_BODY()

public:
    ANPC();

    // NPC Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    ENPCType NPCType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    ENPCState CurrentState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    FString NPCName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    FString NPCDescription;

    // AI Controller
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC")
    class AAIController* NPCController;

    // Behavior Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    bool bIsFriendly;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    bool bCanTrade;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    bool bCanTrain;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    bool bCanCraft;

    // Dialogue Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    TArray<FString> AvailableDialogues;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    bool bHasVoiceOver;

    // Schedule Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    float WakeUpTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    float SleepTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    float WorkStartTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    float WorkEndTime;

    // Override ACharacter functions
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // NPC Functions
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void SetNPCState(ENPCState NewState);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    ENPCState GetNPCState();

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void SetBehaviorFriendly();

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void SetBehaviorHostile();

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void SetBehaviorNeutral();

    // Interaction Functions
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void InteractWithPlayer(class ASoloLevelingCharacter* Player);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void StartDialogue(FString DialogueID);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void EndDialogue();

    // Service Functions
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void OpenShop();

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void OpenTrainingMenu();

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void OpenCraftingMenu();

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void OpenEnchantmentMenu();

    // Movement Functions
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void Patrol();

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void GoToLocation(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void ReturnHome();

    // AI Functions
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void UpdateAI();

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void ProcessPlayerAction(FString ActionName);

    // Events
    UPROPERTY(BlueprintAssignable, Category = "NPC Events")
    FOnNPCInteracted OnNPCInteracted;

    UPROPERTY(BlueprintAssignable, Category = "NPC Events")
    FOnNPCStateChanged OnNPCStateChanged;

protected:
    // Internal AI Functions
    void InitializeAI();
    void UpdateBehavior();
    void ProcessSchedule();

    // Movement Functions
    void MoveToTarget(FVector TargetLocation);
    void UpdatePatrolPath();

    // State Functions
    void HandleIdleState();
    void HandlePatrolState();
    void HandleDialogueState();
    void HandleWorkingState();
    void HandleSleepingState();
    void HandleEmergencyState();

private:
    // Internal State
    float LastUpdateTime;
    bool bIsInteracting;
    bool bIsWorking;
    bool bIsSleeping;

    // Movement
    FVector HomeLocation;
    TArray<FVector> PatrolPoints;
    int32 CurrentPatrolIndex;
    FVector TargetLocation;

    // Helper Functions
    void InitializeNPC();
    void SetupAIController();
    void ConfigureBehaviorTree();
};
