//Copyright (c) 2016 Artem A. Mavrin and other contributors
#pragma once

#include "Quest_Task.h"
#include "Quest.generated.h"

class UQuestBook;
/**
* Quest.
*/
USTRUCT(BlueprintType)
struct DIALOGUESYSTEM_API FQuest 
{
	GENERATED_USTRUCT_BODY()

	bool operator == (const FQuest &Quest) const
	{
		return this->ID == Quest.ID && this->QuestBook == Quest.QuestBook;
	}

public:

	//Quest ID. Should be unique in current quest book
	UPROPERTY(Category = Quest, EditInstanceOnly, BlueprintReadOnly)
	int32 ID;

	//Quest title
	UPROPERTY(Category = Quest, EditInstanceOnly, BlueprintReadOnly)
	FText Title;

	//Task description
	UPROPERTY(Category = Quest, EditInstanceOnly, BlueprintReadOnly, meta = (MultiLine = true))
	FText Description;

	//Intro text
	UPROPERTY(Category = Quest, EditInstanceOnly, BlueprintReadOnly, meta = (MultiLine = true))
	FText IntroText;

	//Text in progress
	UPROPERTY(Category = Quest, EditInstanceOnly, BlueprintReadOnly, meta = (MultiLine = true))
	FText ProgressText;

	//Finish text
	UPROPERTY(Category = Quest, EditInstanceOnly, BlueprintReadOnly, meta = (MultiLine = true))
	FText FinishText;

	//Experience
	UPROPERTY(Category = Quest, EditInstanceOnly, BlueprintReadOnly)
	float Experience;

	//Completed
	UPROPERTY(Category = Quest, EditInstanceOnly, BlueprintReadOnly)
	bool bCompleted;

	//Tasks
	UPROPERTY(Category = Tasks, EditInstanceOnly, BlueprintReadOnly)
	TArray<FQuest_Task> Tasks;

	UPROPERTY()
	UQuestBook* QuestBook;

};
