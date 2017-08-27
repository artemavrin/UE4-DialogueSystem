//Copyright (c) 2016 Artem A. Mavrin and other contributors

#pragma once

#include "PanelWidget.h"
#include "ContentWidget.h"
#include "Components/Button.h"
#include "BTTask_WaitAnswer.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "DialogueButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickDelegate);

UCLASS()
class DIALOGUESYSTEM_API UDialogueButton : public UButton
{
	GENERATED_BODY()

public:
	UDialogueButton();

	UBTTask_WaitAnswer* WaitTask;

	UPROPERTY()
	FClickDelegate click;

	UFUNCTION()
	void OnClick();

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
};