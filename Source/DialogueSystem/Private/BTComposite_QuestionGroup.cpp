// Copyright 2015 Mavrin Artem. All Rights Reserved.

#include "DialogueSystemPrivatePCH.h"
#include "BTTask_WaitAnswer.h"
#include "BTComposite_QuestionGroup.h"

UBTComposite_QuestionGroup::UBTComposite_QuestionGroup(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "QuestionGroup";

	OnNextChild.BindUObject(this, &UBTComposite_QuestionGroup::GetNextChildHandler);
}

int32 UBTComposite_QuestionGroup::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	int32 NextChildIdx = PrevChild + 1;

	if (PrevChild == -1)
	{
		NextChildIdx = BTSpecialChild::ReturnToParent;

		for (auto& Child : Children)
		{
			UBTTask_WaitAnswer* AnswerNode = Cast<UBTTask_WaitAnswer>(Child.ChildTask);
			if (AnswerNode)
			{
				NextChildIdx = PrevChild + 1;
				break;
			}
		}
	}

	if (NextChildIdx == GetChildrenNum())
	{
		NextChildIdx = 0;
	}

	if (LastResult == EBTNodeResult::Failed)
	{
		NextChildIdx = BTSpecialChild::ReturnToParent;
	}

	return NextChildIdx;
}

void UBTComposite_QuestionGroup::SetCloseDialogue(bool Close)
{
	bCloseDialogue = Close;
}

#if WITH_EDITOR

FName UBTComposite_QuestionGroup::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Root.Icon");
}

#endif