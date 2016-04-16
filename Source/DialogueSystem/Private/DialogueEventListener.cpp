// Copyright 2015 Mavrin Artem. All Rights Reserved.

#include "DialogueSystemPrivatePCH.h"
#include "DialogueEventListener.h"

#define LOCTEXT_NAMESPACE "DialogueSystem"

UBTTask_WaitAnswer* UDialogueEventListener::GetCurrentBrunch()
{
	return WaitAnswerNode;
}

TSharedRef<SWidget> UDialogueEventListener::RebuildWidget()
{
	MyBox = SNew(SBox);
		
	return MyBox.ToSharedRef();
}

#if WITH_EDITOR

const FText UDialogueEventListener::GetPaletteCategory()
{
	return NSLOCTEXT("DialogueSystem", "Dialogue", "Dialogue");
}

#endif

/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE