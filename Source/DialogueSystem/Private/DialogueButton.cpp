// Copyright 2015 Mavrin Artem. All Rights Reserved.

#include "DialogueSystemPrivatePCH.h"
#include "Widget.h"
#include "TextBlock.h"
#include "DialogueButton.h"

#define LOCTEXT_NAMESPACE "DialogueSystem"

UDialogueButton::UDialogueButton()
{
	OnClicked.AddDynamic(this, &UDialogueButton::OnClick);
}

void UDialogueButton::OnClick()
{
	UWidget* WText = GetChildAt(0);
	UTextBlock* TextBlock = Cast<UTextBlock>(WText);
	if (TextBlock && WaitTask != nullptr)
	{
		FText SelectedQuestion = TextBlock->GetText();
		WaitTask->SetAnswer(SelectedQuestion);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *TextBlock->GetText().ToString());
	}
}

#if WITH_EDITOR
const FText UDialogueButton::GetPaletteCategory()
{
	return NSLOCTEXT("DialogueSystem", "Dialogue", "Dialogue");
}
#endif

/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE