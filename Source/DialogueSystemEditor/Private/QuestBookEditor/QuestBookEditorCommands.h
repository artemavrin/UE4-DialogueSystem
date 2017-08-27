//Copyright (c) 2016 Artem A. Mavrin and other contributors

#pragma once


class FQuestBookEditorCommands : public TCommands<FQuestBookEditorCommands>
{
public:
	FQuestBookEditorCommands()
		: TCommands<FQuestBookEditorCommands>(
			TEXT("QuestBookEditor"), // Context name for fast lookup
			NSLOCTEXT("Contexts", "QuestBookEditor", "QuestBook Editor"), // Localized context name for displaying
			NAME_None, // Parent
			FName(TEXT("SlateEditorStyle")) // Icon Style Set
			)
	{
	}

	// TCommand<> interface
	virtual void RegisterCommands() override;
	// End of TCommand<> interface

public:
	TSharedPtr<FUICommandInfo> AddQuest;
	//TSharedPtr<FUICommandInfo> DeleteQuest;

};