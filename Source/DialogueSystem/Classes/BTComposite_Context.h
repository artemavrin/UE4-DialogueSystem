//Copyright (c) 2016 Artem A. Mavrin and other contributors
#pragma once

#include "BehaviorTree/BTCompositeNode.h"
#include "BTDialogueTypes.h"

#include "BTComposite_Context.generated.h"

UENUM()
enum class EContextExecutionMode : uint8
{
	/** Work like a sequence */
	CE_Sequence		UMETA(DisplayName = "Sequence mode"),
	/** Work like a selector */
	CE_Selector		UMETA(DisplayName = "Selector mode")
};

/**
* Context composite node.
*/
UCLASS()
class DIALOGUESYSTEM_API UBTComposite_Context : public UBTCompositeNode
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditInstanceOnly, Category = "Execution") EContextExecutionMode ExecutionMode;
	UPROPERTY(EditInstanceOnly, Category = "Text") TArray<FBTDialogueParameter> DialogueParameters;

public:

	bool VerifyExecution(EBTNodeResult::Type LastResult) const;
	int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const;
	void PushArguments(FFormatNamedArguments& DialogueArguments, UBlackboardComponent * Blackboard) const;

public:

	virtual FString GetStaticDescription() const override;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif

};