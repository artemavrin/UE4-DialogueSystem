// Copyright 2015 Mavrin Artem. All Rights Reserved.
#pragma once

#include "BehaviorTree/BTCompositeNode.h"
#include "DialogueSettings.h"
#include "BTDialogueTypes.h"
#include "BTComposite_Question.generated.h"

/**
* Question composite node.
*/
UCLASS()
class DIALOGUESYSTEM_API UBTComposite_Question : public UBTCompositeNode
{
	GENERATED_UCLASS_BODY()

	int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const;
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

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif
};
