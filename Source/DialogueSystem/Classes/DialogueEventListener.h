// Copyright 2015 Mavrin Artem. All Rights Reserved.

#pragma once

#include "BTTask_ShowPhrases.h"
#include "BTTask_WaitAnswer.h"
#include "Widget.h"
#include "DialogueEventListener.generated.h"

/**
* The EventListener allows skip dialogue phrases.
*
*/
UCLASS(meta = (DisplayName = "DialogueEventListener"))
class DIALOGUESYSTEM_API UDialogueEventListener : public UWidget
{
	GENERATED_BODY()

public:

	UBTTask_ShowPhrases* ShowPhrasesNode;
	UBTTask_WaitAnswer* WaitAnswerNode;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DialogueSystem")
	UBTTask_WaitAnswer* GetCurrentBrunch();

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

};