//Copyright (c) 2016 Artem A. Mavrin and other contributors

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