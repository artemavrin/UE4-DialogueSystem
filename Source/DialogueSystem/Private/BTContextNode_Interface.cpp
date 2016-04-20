#include "DialogueSystemPrivatePCH.h"
#include "BTContextNode_Interface.h"

UBTContextNode_Interface::UBTContextNode_Interface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void IBTContextNode_Interface::GetPhrasesContext(const UBTNode * CurrentNode, FFormatNamedArguments& FormatNamedArguments, UBlackboardComponent * Blackboard) const
{
	if (const UBTCompositeNode * Parent = CurrentNode->GetParentNode())
		GetPhrasesContext(Parent, FormatNamedArguments, Blackboard);

	const UBTComposite_Context * ContextNode = Cast<UBTComposite_Context>(CurrentNode);
	if (ContextNode) ContextNode->PushArguments(FormatNamedArguments, Blackboard);
}
