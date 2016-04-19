//Copyright (c) 2016 Artem A. Mavrin and other contributors

#include "DialogueSystemPrivatePCH.h"
#include "BTComposite_Question.h"
#include "UserWidget.h"
#include "WidgetTree.h"
#include "PanelWidget.h"
#include "TextBlock.h"
#include "ContentWidget.h"
#include "DialogueButton.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTTask_WaitAnswer.h"
#include "GameFramework/PlayerController.h"
#include "BTTask_ShowPhrases.h"
#include "BTTask_CloseDialogue.h"
#include "Runtime/Engine/Classes/Matinee/MatineeActor.h"
#include "UObjectToken.h"

#define LOCTEXT_NAMESPACE "DialogueSystem"

UBTTask_WaitAnswer::UBTTask_WaitAnswer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Wait for an answer";
	SelectedAnswer = FText::GetEmpty();
	DialogueQuestionsSlotName = FName("QuestionsSlot");
	bAnswerDone = false;
	bUseGamepad = false;
	bNotifyTick = true;
	InputMode = EWidggetInputMode::UIOnly;
	Timer = -1;
}

EBTNodeResult::Type UBTTask_WaitAnswer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ClearAnswer();
	EBTNodeResult::Type NodeResult = !bAnswerDone ? EBTNodeResult::InProgress : NodeResult = EBTNodeResult::Succeeded;
	TimerCount = Timer;
	AActor* OwnerActor = OwnerComp.GetOwner();

	if (!DialogueWidget.IsNone())
	{
		FName WidgetKeyName = DialogueWidget.SelectedKeyName;
		BlackboardComp = OwnerComp.GetBlackboardComponent();
		Widget = Cast<UUserWidget>(BlackboardComp->GetValueAsObject(WidgetKeyName));
		WidgetComp = Cast<UWidgetComponent>(BlackboardComp->GetValueAsObject(WidgetKeyName));
		UDialogueButton* FirstButton = nullptr;

		if (!Widget && !WidgetComp)
		{
#if WITH_EDITOR
			FMessageLog("PIE").Error()
				->AddToken(FTextToken::Create(LOCTEXT("InvalidWidgetKey", "Invalid key for Dialogue Widget in ")))
				->AddToken(FUObjectToken::Create((UObject*)OwnerComp.GetCurrentTree()));
#endif
			return EBTNodeResult::Failed;
		}

		if (WidgetComp)
		{
			Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetComp->GetWidgetClass());
			PlayerController = WidgetComp->GetUserWidgetObject()->GetOwningPlayer();
			bIsUserWidget = false;
		}
		else
		{
			bIsUserWidget = true;
			PlayerController = Widget->GetOwningPlayer();
		}

		if (Widget && Widget->IsInViewport())
		{
			Widget->RemoveFromParent();
		}
		if (!Widget)
		{
			NodeResult = EBTNodeResult::Failed;
		}
		else
		{
			WidgetTree = Widget->WidgetTree;
			UWidget* DialogueQuestionsSlot = WidgetTree->FindWidget(DialogueQuestionsSlotName);
			UPanelWidget* Panel = Cast<UPanelWidget>(DialogueQuestionsSlot);
			if (Panel)
			{
				TArray<UWidget*> Buttons;
				UDialogueButton* SampleButton = nullptr;
				UTextBlock* SampleTextBlock = nullptr;
				WidgetTree->GetChildWidgets(DialogueQuestionsSlot, Buttons);
				for (auto& elem : Buttons)
				{
					UDialogueButton* Button = Cast<UDialogueButton>(elem);
					if (Button)
					{
						SampleButton = Button;
						WidgetTree->RemoveWidget(elem);
					}
					UTextBlock* TextBlock = Cast<UTextBlock>(elem);
					if (TextBlock)
					{
						SampleTextBlock = TextBlock;
						WidgetTree->RemoveWidget(elem);
					}
				}
				if (SampleButton != nullptr && SampleTextBlock != nullptr)
				{
					const UBTNode* BTNode = GetParentNode();
					const UBTCompositeNode* CBTNode = Cast<UBTCompositeNode>(BTNode);
					Panel->SetVisibility(ESlateVisibility::Visible);
					if (CBTNode)
					{
						int32 ButtonNumber = 0;
						for (int32 Index = 0; Index != CBTNode->Children.Num(); ++Index)
						{
							auto& Child = CBTNode->Children[Index];
							UBTComposite_Question* Question = Cast<UBTComposite_Question>(Child.ChildComposite);
							bool bDecoratorOk = CBTNode->DoDecoratorsAllowExecution(OwnerComp, OwnerComp.GetActiveInstanceIdx(), Index);

							if(Question)
							{
								Question->bCanExecute = false;
								Question->bSelected = false;
							}
							if (
									Question
									&& Question->Children.Num() > 0
									&& Question->GetVisibility(PlayerController)
									&& Question->bVisible
									&& bDecoratorOk
								)
							{
								Question->bCanExecute = true;
								UDialogueButton *NewSampleButton = NewObject<UDialogueButton>(this, NAME_None, SampleButton->GetFlags(), SampleButton);
								UTextBlock *NewSampleTextBlock = NewObject<UTextBlock>(this, NAME_None, SampleTextBlock->GetFlags(), SampleTextBlock);

								ButtonNumber++;
								if (bUseGamepad)
								{
									NewSampleButton->IsFocusable = true;
									if (ButtonNumber == 1)
									{
										FirstButton = NewSampleButton;
									}
								}
								else
								{
									NewSampleButton->IsFocusable = false;
								}

								NewSampleTextBlock->SetText(FText::Format(NSLOCTEXT("DialogueSystem", "ButtonText", "{0}"), Question->GetQuestionThumbnail(BlackboardComp)));
								UWidget* Oldtext = NewSampleButton->GetChildAt(0);
								NewSampleButton->WaitTask = this;
								NewSampleButton->RemoveChild(Oldtext);
								NewSampleButton->AddChild(NewSampleTextBlock);
								Panel->AddChild(NewSampleButton);
							}
						}
					}
				}
				// Event Listener
				UWidget* DialogueEventListener = WidgetTree->FindWidget(FName("DialogueEventListener"));
				if (DialogueEventListener != nullptr)
				{
					UDialogueEventListener* EventListener = Cast<UDialogueEventListener>(DialogueEventListener);
					if (EventListener)
					{
						EventListener->WaitAnswerNode = this;
					}
				}
			}
			if (bIsUserWidget)
			{
				Widget->AddToViewport();
			}
			else
			{
				WidgetComp->SetWidget(Widget);
				WidgetComp->SetVisibility(true);
			}
			PlayerController->bShowMouseCursor = !bUseGamepad;
			FInputModeUIOnly InputModeUIOnly;
			FInputModeGameAndUI InputModeGameAndUI;

			if (InputMode == EWidggetInputMode::UIOnly)
			{
				PlayerController->SetInputMode(InputModeUIOnly);
			}
			else
			{
				PlayerController->SetInputMode(InputModeGameAndUI);
			}
			if (bUseGamepad && Panel)
			{
				FirstButton->SetKeyboardFocus();
			}
			else
			{
				if (InputMode == EWidggetInputMode::UIOnly)
				{
					InputModeUIOnly.SetWidgetToFocus(Widget->TakeWidget());
				}
				else
				{
					InputModeGameAndUI.SetWidgetToFocus(Widget->TakeWidget());
				}
			}

		}

		// cinematic
		if (DialogueCinematicOptions.bPlayMatinee && !DialogueCinematicOptions.Matinee.Equals("None"))
		{
			for (TActorIterator<AMatineeActor> It(OwnerActor->GetWorld()); It; ++It)
			{
				MatineeActor = *It;
				if (MatineeActor && MatineeActor->GetName().Equals(DialogueCinematicOptions.Matinee))
				{
					MatineeActor->bLooping = DialogueCinematicOptions.bLoop;
					MatineeActor->Play();
					break;
				}
			}
		}

		// camera
		if (DialogueCameraOptions.bUseCamera)
		{
			if (!DialogueCameraOptions.CameraToView.IsNone() && !DialogueCameraOptions.PlayerCamera.IsNone())
			{
				FName CameraToViewKeyName = DialogueCameraOptions.CameraToView.SelectedKeyName;
				BlackboardComp = OwnerComp.GetBlackboardComponent();
				UCameraComponent* CameraToView = Cast<UCameraComponent>(BlackboardComp->GetValueAsObject(CameraToViewKeyName));

				FName PlayerCameraKeyName = DialogueCameraOptions.PlayerCamera.SelectedKeyName;
				PlayerCamera = Cast<UCameraComponent>(BlackboardComp->GetValueAsObject(PlayerCameraKeyName));

				if (PlayerCamera && CameraToView)
				{
					SaveDefaultCameraData(PlayerCamera);
					if (PlayerCamera == CameraToView)
					{
						PlayerCamera->SetWorldLocationAndRotation(DefaultCameraLocation, DefaultCameraRotation);
					}
					else
					{
						PlayerCamera->SetWorldLocationAndRotation(CameraToView->GetComponentLocation(), CameraToView->GetComponentRotation());
					}
				}
			}
		}
	}

	return NodeResult;
}

void UBTTask_WaitAnswer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (bAnswerDone)
	{
		// cinematic
		if (DialogueCinematicOptions.bPlayMatinee && MatineeActor)
		{
			MatineeActor->Stop();
		}
		// Event Listener
		UWidget* DialogueEventListener = WidgetTree->FindWidget(FName("DialogueEventListener"));
		if (DialogueEventListener != nullptr)
		{
			UDialogueEventListener* EventListener = Cast<UDialogueEventListener>(DialogueEventListener);
			if (EventListener)
			{
				EventListener->WaitAnswerNode = nullptr;
			}
		}
		if (WidgetComp)
		{
			Widget->SetVisibility(ESlateVisibility::Hidden);
		}
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	TimerCount = TimerCount > 0 ? TimerCount - DeltaSeconds : 0;
}

void UBTTask_WaitAnswer::SaveDefaultCameraDataForAll(UBTNode* Node)
{
	UBTTask_ShowPhrases* ShowPhrases = Cast<UBTTask_ShowPhrases>(Node);
	UBTTask_WaitAnswer* WaitAnswer = Cast<UBTTask_WaitAnswer>(Node);
	UBTTask_CloseDialogue* CloseDialogue = Cast<UBTTask_CloseDialogue>(Node);
	UBTCompositeNode* ComposteNode = Cast<UBTCompositeNode>(Node);
	if (ShowPhrases)
	{
		ShowPhrases->DefaultCameraLocation = DefaultCameraLocation;
		ShowPhrases->DefaultCameraRotation = DefaultCameraRotation;
	}
	if (WaitAnswer)
	{
		WaitAnswer->DefaultCameraLocation = DefaultCameraLocation;
		WaitAnswer->DefaultCameraRotation = DefaultCameraRotation;
	}
	if (CloseDialogue)
	{
		CloseDialogue->DefaultCameraLocation = DefaultCameraLocation;
		CloseDialogue->DefaultCameraRotation = DefaultCameraRotation;
		CloseDialogue->FirstTaskNode = this;
	}
	if (ComposteNode && ComposteNode->Children.Num() > 0)
	{
		for (auto& Child : ComposteNode->Children)
		{
			SaveDefaultCameraDataForAll(Child.ChildTask);
			SaveDefaultCameraDataForAll(Child.ChildComposite);
		}
	}
}

void UBTTask_WaitAnswer::SaveDefaultCameraData(UCameraComponent* Camera)
{
	if (DefaultCameraLocation.IsZero() || DefaultCameraRotation.IsZero())
	{
		DefaultCameraLocation = Camera->GetComponentLocation();
		DefaultCameraRotation = Camera->GetComponentRotation();
		UBTCompositeNode* Parent = GetParentNode();
		SaveDefaultCameraDataForAll(Parent);
	}
}

FString UBTTask_WaitAnswer::GetStaticDescription() const
{
	return FString("Wait for an answer");
}

void UBTTask_WaitAnswer::SetAnswer(FText Text)
{
	SelectedAnswer = FText::Format(NSLOCTEXT("DialogueSystem", "ButtonText", "{0}"), Text);
	
	for(auto& Child : GetParentNode()->Children)
	{
		UBTComposite_Question* Question = Cast<UBTComposite_Question>(Child.ChildComposite);
		if(Question) {

			FText FormatedQuestion = Question->GetQuestionThumbnail(BlackboardComp);
			if(FormatedQuestion.EqualTo(SelectedAnswer))
			{
				Question->bSelected = true;
				break;
			}
		}
	}
	
	bAnswerDone = true;
}

void UBTTask_WaitAnswer::SetAnswer(UDialogueButton* DialogueButton)
{
	if (DialogueButton != nullptr && DialogueButton->GetChildrenCount() > 0)
	{
		UTextBlock* TextBlock = Cast<UTextBlock>(DialogueButton->GetChildAt(0));
		if (TextBlock)
		{
			SetAnswer(TextBlock->GetText());
		}
	}
}

float UBTTask_WaitAnswer::GetTimer()
{
	return TimerCount;
}

bool UBTTask_WaitAnswer::HasTimer()
{
	return Timer == -1 ? false : true;
}

void UBTTask_WaitAnswer::ClearAnswer()
{
	SelectedAnswer = FText::GetEmpty();
	bAnswerDone = false;
}

FText UBTTask_WaitAnswer::GetAnswer()
{
	return SelectedAnswer;
}
#if WITH_EDITOR

FName UBTTask_WaitAnswer::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Task.Wait.Icon");
}

#endif	// WITH_EDITOR

#undef LOCTEXT_NAMESPACE
