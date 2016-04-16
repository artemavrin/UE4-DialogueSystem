// Copyright 2015 Mavrin Artem. All Rights Reserved.

#include "DialogueSystemPrivatePCH.h"
#include "BTTask_WaitAnswer.h"
#include "BTComposite_QuestionGroup.h"

#include "UObjectToken.h"

#define LOCTEXT_NAMESPACE "DialogueSystem" 

UBTComposite_QuestionGroup::UBTComposite_QuestionGroup(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "QuestionGroup";

	OnNextChild.BindUObject(this, &UBTComposite_QuestionGroup::GetNextChildHandler);
}

int32 UBTComposite_QuestionGroup::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	int32 NextChildIdx = PrevChild + 1;
	UBTTask_WaitAnswer* AnswerNode = nullptr;

	if (PrevChild == -1)
	{
		NextChildIdx = BTSpecialChild::ReturnToParent;

		for (auto& Child : Children)
		{
			AnswerNode = Cast<UBTTask_WaitAnswer>(Child.ChildTask);
			if (AnswerNode)
			{
				UE_LOG(LogTemp, Warning, TEXT("#1.1"));
				NextChildIdx = PrevChild + 1;
				break;
			}
		}
		if (!AnswerNode) {
#if WITH_EDITOR
			FMessageLog("PIE").Error()
				->AddToken(FTextToken::Create(LOCTEXT("GetAnswerNode", "Node ")))
				->AddToken(FUObjectToken::Create(this))
				->AddToken(FTextToken::Create(LOCTEXT("ErrorTree", " in ")))
				->AddToken(FUObjectToken::Create((UObject*)SearchData.OwnerComp.GetCurrentTree()))
				->AddToken(FTextToken::Create(LOCTEXT("QuestionGroupHasNoAnswerNode", "has no Wait Answer node!")));
#endif
			return BTSpecialChild::ReturnToParent;
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

#undef LOCTEXT_NAMESPACE