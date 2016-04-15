// Copyright 2015 Mavrin Artem. All Rights Reserved.
#pragma once

#include "Quest_Task.generated.h"

/**
* Quest task.
*/
USTRUCT()
struct DIALOGUESYSTEM_API FQuest_Task
{
	GENERATED_BODY()

	//Task title
	UPROPERTY(Category = Task, EditAnywhere)
	FText Title;

	//How many times needs to do
	UPROPERTY(Category = Task, EditAnywhere)
	int32 TotalProgressNeeded;

	//How many times did
	UPROPERTY(Category = Task, BlueprintReadOnly)
	int32 Progress;

};