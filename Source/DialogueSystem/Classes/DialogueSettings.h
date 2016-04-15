// Copyright 2015 Mavrin Artem. All Rights Reserved.

#pragma once

#include "DialogueSettings.generated.h"

/**
* Contains dialogue settings
*/
UCLASS(BlueprintType, Blueprintable)
class DIALOGUESYSTEM_API ADialogueSettings : public AActor
{
	GENERATED_BODY()

public:

	APlayerController* PlayerController;

	bool GetPropertyBoolValue(FString ValueName);
	void SetPropertyBoolValue(FString ValueName, bool NewValue);
	TArray<FString> GetBoolVariables();
};