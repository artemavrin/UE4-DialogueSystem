//Copyright (c) 2016 Artem A. Mavrin and other contributors

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
