// Copyright 2015 Mavrin Artem. All Rights Reserved.

#include "DialogueSystemPrivatePCH.h"
#include "BTTask_WaitAnswer.h"
#include "BTComposite_Question.h"

UBTComposite_Question::UBTComposite_Question(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Question";
	bVisible = true;

	OnNextChild.BindUObject(this, &UBTComposite_Question::GetNextChildHandler);
}

int32 UBTComposite_Question::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	int32 NextChildIdx = BTSpecialChild::ReturnToParent;
	
	if (PrevChild == -1)
	{
		const UBTCompositeNode* ParentNode = GetParentNode();
		FText AnswerText = FText::GetEmpty();

		UBTTask_WaitAnswer* AnswerNode = nullptr;

		for (auto& Child : ParentNode->Children)
		{
			AnswerNode = Cast<UBTTask_WaitAnswer>(Child.ChildTask);
			if (AnswerNode)
			{
				AnswerText = AnswerNode->GetAnswer();
				break;
			}
		}
		if (QuestionThumbnail.ToString() == AnswerText.ToString())
		{
			NextChildIdx = 0;
			AnswerNode->ClearAnswer();
			if (bHideAfterSelect)
			{
				SetVisibility(AnswerNode->PlayerController, false);
			}
		}
	}
	else
	{
		NextChildIdx = PrevChild + 1;
	}

	if (NextChildIdx == GetChildrenNum() || LastResult == EBTNodeResult::Failed)
	{
		NextChildIdx = BTSpecialChild::ReturnToParent;
	}

	return NextChildIdx;
}

FString UBTComposite_Question::GetStaticDescription() const
{
	return QuestionThumbnail.ToString();
}

bool UBTComposite_Question::GetVisibility(APlayerController* PlayerController)
{
	if (DialogueSettings != NULL && !SettingName.EqualTo(FText::FromString("None")))
	{
		for (TActorIterator<ADialogueSettings> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ADialogueSettings *Settings = *ActorItr;
			if (Settings->PlayerController == PlayerController)
			{
				return Settings->GetPropertyBoolValue(SettingName.ToString());
			}
			
		}
	}
	return bVisible;
}

void UBTComposite_Question::SetVisibility(APlayerController* PlayerController, bool NewVisibility) const
{
	if (DialogueSettings != NULL && !SettingName.EqualTo(FText::FromString("None")))
	{
		for (TActorIterator<ADialogueSettings> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ADialogueSettings *Settings = *ActorItr;
			if (Settings->PlayerController == PlayerController)
			{
				return Settings->SetPropertyBoolValue(SettingName.ToString(), NewVisibility);
			}

		}
	}
}

#if WITH_EDITOR

FName UBTComposite_Question::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Decorator.DoesPathExist.Icon");
}

#endif
