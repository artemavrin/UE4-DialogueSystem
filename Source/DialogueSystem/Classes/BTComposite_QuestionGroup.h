// Copyright 2015 Mavrin Artem. All Rights Reserved.
#pragma once

#include "BehaviorTree/BTCompositeNode.h"
#include "BTComposite_QuestionGroup.generated.h"

/**
* Question Group composite node.
*/
UCLASS()
class DIALOGUESYSTEM_API UBTComposite_QuestionGroup : public UBTCompositeNode
{
	GENERATED_UCLASS_BODY()

	int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const;

	void SetCloseDialogue(bool	Close);

private:
	bool bCloseDialogue;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif
};
