//Copyright (c) 2016 Artem A. Mavrin and other contributors

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
	int32 NextChildIdx = PrevChild+1;
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
