// Copyright 2015 Mavrin Artem. All Rights Reserved.

#include "DialogueSystemPrivatePCH.h"

#define LOCTEXT_NAMESPACE "DialogueSystem"

//////////////////////////////////////////////////////////////////////////
// FDialogueSystemModule

class FDialogueSystemModule : public IDialogueSystemModule
{
public:
	virtual void StartupModule() override
	{};
	virtual void ShutdownModule() override
	{};
};

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogueSystemModule, DialogueSystem)