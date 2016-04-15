// Copyright 2015 Mavrin Artem. All Rights Reserved.
#pragma once

#include "QuestBook.h"
#include "QuestBookFactory.generated.h"


UCLASS()
class UQuestBookFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// End of UFactory interface
};