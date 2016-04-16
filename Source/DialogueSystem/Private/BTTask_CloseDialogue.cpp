// Copyright 2015 Mavrin Artem. All Rights Reserved.

#include "DialogueSystemPrivatePCH.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "WidgetComponent.h"
#include "UserWidget.h"
#include "BTTask_CloseDialogue.h"
#include "BTComposite_QuestionGroup.h"
#include "Camera/CameraComponent.h"
#include "BTTask_ShowPhrases.h"
#include "BTTask_WaitAnswer.h"
#include "UObjectToken.h"

#define LOCTEXT_NAMESPACE "DialogueSystem" 

UBTTask_CloseDialogue::UBTTask_CloseDialogue(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Close Dialogue";
}

EBTNodeResult::Type UBTTask_CloseDialogue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::Failed;

	if (!DialogueWidget.IsNone())
	{
		FName KeyName = DialogueWidget.SelectedKeyName;
		UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
		UUserWidget* Widget = Cast<UUserWidget>(BlackboardComp->GetValueAsObject(KeyName));
		UWidgetComponent* WidgetComp = Cast<UWidgetComponent>(BlackboardComp->GetValueAsObject(KeyName));

		if (!Widget && !WidgetComp)
		{
#if WITH_EDITOR
			FMessageLog("PIE").Error()
				->AddToken(FTextToken::Create(LOCTEXT("InvalidWidgetKey", "Invalid key for Dialogue Widget in ")))
				->AddToken(FUObjectToken::Create((UObject*)OwnerComp.GetCurrentTree()));
#endif
			return EBTNodeResult::Failed;
		}

		if (!Widget && WidgetComp)
		{
			Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetComp->GetWidgetClass());
		}

		APlayerController* PlayerController = Widget->GetOwningPlayer();
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);

		if (Widget && Widget->IsInViewport())
		{
			Widget->RemoveFromParent();
		}

		switch (MouseOptions)
		{
		case ECloseDialogueCursorOptions::Show:
			PlayerController->bShowMouseCursor = true;
			break;
		default:
			PlayerController->bShowMouseCursor = false;
			break;
		}
	}
	// set camera default values
	if (!PlayerCamera.IsNone())
	{
		FName PlayerCameraKeyName = PlayerCamera.SelectedKeyName;
		UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
		UCameraComponent* PlayerCameraComp = Cast<UCameraComponent>(BlackboardComp->GetValueAsObject(PlayerCameraKeyName));

		if (PlayerCameraComp)
		{
			PlayerCameraComp->SetWorldLocationAndRotation(DefaultCameraLocation, DefaultCameraRotation);
			UBTTask_ShowPhrases* ShowPhrases = Cast<UBTTask_ShowPhrases>(FirstTaskNode);
			UBTTask_WaitAnswer* WaitAnswer = Cast<UBTTask_WaitAnswer>(FirstTaskNode);
			if (ShowPhrases)
			{
				ShowPhrases->DefaultCameraLocation = FVector(0.f, 0.f, 0.f);
			}
			if (WaitAnswer)
			{
				WaitAnswer->DefaultCameraLocation = FVector(0.f, 0.f, 0.f);
			}
		}
	}

	return NodeResult;
}

FString UBTTask_CloseDialogue::GetStaticDescription() const
{
	return FString("Close Dialogue");
}


#if WITH_EDITOR

FName UBTTask_CloseDialogue::GetNodeIconName() const
{
	return FName("GraphBreadcrumb.BrowseBack");
}

#endif	// WITH_EDITOR

#undef LOCTEXT_NAMESPACE