// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DialogueSystemEditorPrivatePCH.h"
#include "QuestBookFactory.h"

#define LOCTEXT_NAMESPACE "DialogueSystem"

/////////////////////////////////////////////////////
// UQuestBookFactory

UQuestBookFactory::UQuestBookFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UQuestBook::StaticClass();
}

UObject* UQuestBookFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UQuestBook* NewQuestBook = NewObject<UQuestBook>(InParent, Class, Name, Flags | RF_Transactional);
	return NewQuestBook;
}

#undef LOCTEXT_NAMESPACE