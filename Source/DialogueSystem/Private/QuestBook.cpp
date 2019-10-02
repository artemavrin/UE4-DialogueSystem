//Copyright (c) 2016 Artem A. Mavrin and other contributors

#pragma once
//#include "DialogueSystemPrivatePCH.h"
#include "QuestBook.h"

FQuest UQuestBook::GetQuest(int32 ID)
{
	FQuest Result;

	for (auto& elem : Quests)
	{
		if (elem.ID == ID)
		{
			Result = elem;
			break;
		}
	}

	return Result;
}

void UQuestBook::IncreaseLastID()
{
	LastID++;
}

void UQuestBook::SetUniqueID()
{
	IncreaseLastID();
	for (auto& elem : Quests)
	{
		if (elem.ID == 0)
		{
			elem.ID = LastID;
			elem.QuestBook = this;
			break;
		}
	}
}
