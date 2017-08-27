//Copyright (c) 2016 Artem A. Mavrin and other contributors

#include "DialogueSystemEditorPrivatePCH.h"
#include "QuestBookEditorCommands.h"

//////////////////////////////////////////////////////////////////////////
// FFlipbookEditorCommands

#define LOCTEXT_NAMESPACE "DialogueSystem"

void FQuestBookEditorCommands::RegisterCommands()
{
	UI_COMMAND(AddQuest, "Add Quest", "Adds a new quest", EUserInterfaceActionType::Button, FInputChord());
	//UI_COMMAND(DeleteQuest, "Delete Quest", "Deletes a quest", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE