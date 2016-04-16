// Copyright 2015 Mavrin Artem. All Rights Reserved.

#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CloseDialogue.generated.h"

/**
* Close dialogue task node.
*/
UCLASS()
class DIALOGUESYSTEM_API UBTTask_CloseDialogue : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	/** Dialogue widget */
	UPROPERTY(EditInstanceOnly, Category = Widget)
	FBlackboardKeySelector DialogueWidget;

	/** Do we show the mouse cursor when the dialogue is closed ? */
	UPROPERTY(EditInstanceOnly, Category = Mouse)
	ECloseDialogueCursorOptions MouseOptions;

	/** Player camera*/
	UPROPERTY(EditInstanceOnly, Category = Camera)
	FBlackboardKeySelector PlayerCamera;
	
	FVector DefaultCameraLocation;
	FRotator DefaultCameraRotation;
	UBTTaskNode* FirstTaskNode;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif // WITH_EDITOR
};
