//Copyright (c) 2016 Artem A. Mavrin and other contributors

#pragma once

#include "Quest.h"
#include "QuestBook.generated.h"

/**
* Contains all available quests
*/
UCLASS(BlueprintType, meta = (DisplayThumbnail = "true"))
class DIALOGUESYSTEM_API UQuestBook : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 LastID;

	void IncreaseLastID();
	void SetUniqueID();

public:
	//Quests
	UPROPERTY(Category = Quests, EditInstanceOnly, BlueprintReadOnly)
	TArray<FQuest> Quests;

	//Gets Quest by ID
	UFUNCTION(Category = "DialogueSystem", BlueprintCallable)
	FQuest GetQuest(int32 ID);
};