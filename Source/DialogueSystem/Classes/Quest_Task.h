//Copyright (c) 2016 Artem A. Mavrin and other contributors
#pragma once

#include "Quest_Task.generated.h"

/**
* Quest task.
*/
USTRUCT(BlueprintType)
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
