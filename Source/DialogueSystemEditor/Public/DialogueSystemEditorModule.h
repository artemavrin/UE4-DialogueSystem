// Copyright 2015 Mavrin Artem. All Rights Reserved.

#pragma once

#define DIALOGUESYSTEMEDITOR_MODULE_NAME "DialogueSystemEditor"

#include "ModuleManager.h"

//////////////////////////////////////////////////////////////////////////
// IDialogueSystemModule

class IDialogueSystemEditorModule : public IModuleInterface
{
public:
	virtual TSharedPtr<class FExtensibilityManager> GetQuestBookEditorToolBarExtensibilityManager() { return nullptr; }
	virtual uint32 GetDialogueSystemAssetCategory() const = 0;
	
};
