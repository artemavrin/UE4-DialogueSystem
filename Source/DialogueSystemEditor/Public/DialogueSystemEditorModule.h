//Copyright (c) 2016 Artem A. Mavrin and other contributors

#pragma once

#define DIALOGUESYSTEMEDITOR_MODULE_NAME "DialogueSystemEditor"

#include "ModuleManager.h"
#include "AssetToolsModule.h"

#include "QuestBookAssetTypeActions.h"
#include "DialogueSystemStyle.h"
#include "QuestBookEditor/QuestBookEditorCustomization.h"
#include "BehaviorTreeEditor/QuestionCustomization.h"
#include "BehaviorTreeEditor/ShowPhrasesCustomization.h"

//////////////////////////////////////////////////////////////////////////
// IDialogueSystemModule

class IDialogueSystemEditorModule : public IModuleInterface
{
public:
	virtual TSharedPtr<class FExtensibilityManager> GetQuestBookEditorToolBarExtensibilityManager() { return nullptr; }
	virtual uint32 GetDialogueSystemAssetCategory() const = 0;
	
};
