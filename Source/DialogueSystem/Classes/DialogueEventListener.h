//Copyright (c) 2016 Artem A. Mavrin and other contributors

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

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DialogueSystem|Dialogue")
	UBTTask_WaitAnswer* GetCurrentBrunch();

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~ End UWidget Interface

protected:
	TSharedPtr<SBox> MyBox;

};