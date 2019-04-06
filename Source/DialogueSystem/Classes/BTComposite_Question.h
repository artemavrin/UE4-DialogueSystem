//Copyright (c) 2016 Artem A. Mavrin and other contributors
#pragma once

#include "BehaviorTree/BTCompositeNode.h"
#include "DialogueSettings.h"
#include "BTContextNode_Interface.h"
#include "BTComposite_Question.generated.h"

/**
* Question composite node.
*/
UCLASS()
class DIALOGUESYSTEM_API UBTComposite_Question : public UBTCompositeNode, public IBTContextNode_Interface
{
	GENERATED_UCLASS_BODY()

	int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;
	virtual FString GetStaticDescription() const override;

	/** Question Thumbnail */
	UPROPERTY(EditInstanceOnly, Category = Question, meta = (MultiLine = "true"))
	FText QuestionThumbnail;
	
	/** Question visibility */
	UPROPERTY(EditInstanceOnly, Category = QuestionVisibility)
	bool bVisible;

	/** Hide question after select*/
	UPROPERTY(EditInstanceOnly, Category = QuestionVisibility)
	bool bHideAfterSelect;

	/** Dialogue settings */
	UPROPERTY(EditInstanceOnly, Category = QuestionVisibility)
	TSubclassOf<ADialogueSettings> DialogueSettings;

	/** Variable controls question's visibility */
	UPROPERTY(EditInstanceOnly, Category = QuestionVisibility, meta = (DisplayName = "Variable"))
	FText SettingName;

	bool GetVisibility(APlayerController* PlayerController);

	void SetVisibility(APlayerController* PlayerController, bool NewVisibility) const;

	FText GetQuestionThumbnail(UBlackboardComponent * Blackboard) const;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif

	/** Set by WaitAnswer, and checked by QuestionGroup; true if visible & decorators agree. */
	bool bCanExecute;
	/** Set by WaitAnswer, tested by QuestionGroup. */
	bool bSelected;
};
