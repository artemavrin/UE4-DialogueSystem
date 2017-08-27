//Copyright (c) 2016 Artem A. Mavrin and other contributors

#include "DialogueSystemPrivatePCH.h"
#include "BTComposite_Context.h"

UBTComposite_Context::UBTComposite_Context(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Context";
	ExecutionMode = EContextExecutionMode::CE_Sequence;

	OnNextChild.BindUObject(this, &UBTComposite_Context::GetNextChildHandler);
}

bool UBTComposite_Context::VerifyExecution(EBTNodeResult::Type LastResult) const
{
	if (ExecutionMode == EContextExecutionMode::CE_Sequence)
		return LastResult == EBTNodeResult::Succeeded;

	else return LastResult == EBTNodeResult::Failed;
}

int32 UBTComposite_Context::GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{

	int32 NextChildIdx = BTSpecialChild::ReturnToParent;

	if (PrevChild == BTSpecialChild::NotInitialized)
	{
		NextChildIdx = 0;
	}
	else if (VerifyExecution(LastResult) && (PrevChild + 1) < GetChildrenNum())
	{
		NextChildIdx = PrevChild + 1;
	}

	return NextChildIdx;
}

#if WITH_EDITOR

FName UBTComposite_Context::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Decorator.DoesPathExist.Icon");
}

#endif

FString UBTComposite_Context::GetStaticDescription() const
{

	FString Description = "";
	Description += (ExecutionMode == EContextExecutionMode::CE_Sequence) ? TEXT("Sequence \n\n") : TEXT("Selector \n\n");

	for (const FBTDialogueParameter& DialogueParameter : DialogueParameters)
		Description += DialogueParameter.StringKey + " : " + DialogueParameter.BlackboardKey.SelectedKeyName.ToString() + TEXT("  \n");

	return Description;

}

void UBTComposite_Context::PushArguments(FFormatNamedArguments& DialogueArguments, UBlackboardComponent * Blackboard) const
{
	for (const FBTDialogueParameter& DialogueParameter : DialogueParameters)
		DialogueParameter.PushArgument(DialogueArguments, Blackboard);
}
