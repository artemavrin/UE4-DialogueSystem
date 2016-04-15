// Copyright 2015 Mavrin Artem. All Rights Reserved.

#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BTDialogueTypes.h"
#include "Widget.h"
#include "WidgetComponent.h"
#include "UserWidget.h"
#include "Camera/CameraComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTTask_ShowPhrases.generated.h"


/**
* Show dialogue task node.
*/
UCLASS()
class DIALOGUESYSTEM_API UBTTask_ShowPhrases : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
	
	void ShowNewDialoguePhrase(bool bSkip);
	void ShowNewChar(bool bSkip);
	void SaveDefaultCameraDataForAll(UBTNode* Node);
	void SaveDefaultCameraData(UCameraComponent* PlayerCamera);

	/** Dialogue widget */
	UPROPERTY(EditInstanceOnly, Category = Widget)
	FBlackboardKeySelector DialogueWidget;

	/** Input Mode */
	UPROPERTY(EditInstanceOnly, Category = Widget)
	EWidggetInputMode InputMode;

	/** Dialogue name options */
	UPROPERTY(EditInstanceOnly, Category = Dialogue)
	FBTDialogueNameOptions DialogueNameOptions;

	/** Dialogue image options */
	UPROPERTY(EditInstanceOnly, Category = Dialogue)
	FBTDialogueImageOptions DialogueImageOptions;

	/** Dialogue text options */
	UPROPERTY(EditInstanceOnly, Category = Dialogue)
	FBTDialogueTextOptions DialogueTextOptions;

	/** Dialogue sound options */
	UPROPERTY(EditInstanceOnly, Category = Dialogue)
	FBTDialogueSoundOptions DialogueSoundOptions;

	/** Dialogue camera options */
	UPROPERTY(EditInstanceOnly, Category = Dialogue)
	FBTDialogueCameraOptions DialogueCameraOptions;

	/** Dialogue character animation options */
	UPROPERTY(EditInstanceOnly, Category = Dialogue)
	FBTDialogueCharacterAnimationOptions DialogueCharacterAnimationOptions;

	/** show detailed information about properties */
	UPROPERTY(EditInstanceOnly, Category = Description)
	uint32 bShowPropertyDetails : 1;

	int32 ShowingNumPhrase;
	int32 PhrasesCount;
	bool bTextFinished;
	bool bSoundStarted;
	bool bIsUserWidget;
	float SoundDuration;
	bool bCharacterAnimationStarted;
	float CharacterAnimationDuration;

	AActor* OwnerActor;
	UBlackboardComponent* BlackboardComp;
	UUserWidget* Widget;
	UWidget* DialoguePhraseSlot;
	UWidget* DialogueImageSlot;
	UWidget* DialogueNameSlot;
	UAudioComponent* AudioComponent;
	AAIController* AIController;

	int32 CurrentCharNum;
	TArray<TCHAR> FullString;
	FString StringToDisplay;
	
	APlayerController* PlayerController;
	UCameraComponent* PlayerCamera;
	USkeletalMeshComponent* Mesh;
	UWidgetComponent* WidgetComp;

	FVector DefaultCameraLocation;
	FRotator DefaultCameraRotation;

	FTimerDelegate TimerDelegate;
	FTimerHandle TimerHandle;
	FTimerHandle CharacterAnimTimerHandle;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif // WITH_EDITOR

protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};