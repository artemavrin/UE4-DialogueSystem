// Copyright 2015 Mavrin Artem. All Rights Reserved.

#include "DialogueSystemPrivatePCH.h"
#include "SoundDefinitions.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "UserWidget.h"
#include "WidgetComponent.h"
#include "BTDialogueTypes.h"
#include "WidgetTree.h"
#include "Runtime/UMG/Public/Components/TextWidgetTypes.h"
#include "TextBlock.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "BTTask_ShowPhrases.h"
#include "BTComposite_QuestionGroup.h"
#include "Image.h"
#include "BTTask_WaitAnswer.h"
#include "BTTask_CloseDialogue.h"
#include "Runtime/CoreUObject/Public/Misc/UObjectToken.h"

#define LOCTEXT_NAMESPACE "DialogueSystem" 

UBTTask_ShowPhrases::UBTTask_ShowPhrases(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Show Phrases";
	InputMode = EWidggetInputMode::UIOnly;
	DialogueTextOptions.bShowTextPhrases = true;
	DialogueSoundOptions.bPlaySound = false;
	DialogueCameraOptions.bUseCamera = false;
	DialogueCharacterAnimationOptions.bPlayAnimation = false;
	DialogueCharacterAnimationOptions.bLoop = false;
	DialogueCharacterAnimationOptions.bWaitEndOfAnimation = false;
	DialogueCharacterAnimationOptions.AnimationBlendOptions.BlendInTime = 0.25f;
	DialogueCharacterAnimationOptions.AnimationBlendOptions.BlendOutTime = 0.25f;
	DialogueCharacterAnimationOptions.AnimationBlendOptions.SlotNodeName = TEXT("Dialogue");
	DialogueCharacterAnimationOptions.AnimationBlendOptions.InPlayRate = 1.0f;
	DialogueImageOptions.bShowImage = false;
	DialogueNameOptions.bShowName = false;
	DialogueTextOptions.bHideLastPhrase = false;
	DialogueNameOptions.DialogueSpeakerNameSlotName = FName("NameSlot");
	DialogueImageOptions.DialogueSpeakerImageSlotName = FName("ImageSlot");
	DialogueTextOptions.DialoguePhraseSlotName = FName("PhraseSlot");
	DialogueTextOptions.DialogueQuestionsSlotName = FName("QuestionsSlot");
	DialogueTextOptions.GeneralShowingTime = 2.0f;
	DialogueTextOptions.UseGeneralTime = true;
	DialogueTextOptions.TextEffect = ETextEffect::NoEffect;
	DialogueTextOptions.Delay = 0.07f;
	ShowingNumPhrase = 0;
	bTextFinished = false;
	bCharacterAnimationStarted = false;
	bNotifyTick = true;
	bShowPropertyDetails = true;
}

EBTNodeResult::Type UBTTask_ShowPhrases::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{	
	EBTNodeResult::Type NodeResult = ShowingNumPhrase <= PhrasesCount ? EBTNodeResult::InProgress : NodeResult = EBTNodeResult::Succeeded;
	// reset timer handle
	TimerHandle.Invalidate();
	//AudioComponent = NULL;
	
	if (!DialogueWidget.IsNone())
	{
		FName WidgetKeyName = DialogueWidget.SelectedKeyName;
		BlackboardComp = OwnerComp.GetBlackboardComponent();
		Widget = Cast<UUserWidget>(BlackboardComp->GetValueAsObject(WidgetKeyName));
		WidgetComp = Cast<UWidgetComponent>(BlackboardComp->GetValueAsObject(WidgetKeyName));
		OwnerActor = OwnerComp.GetOwner();

		if (WidgetComp)
		{
			Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetComp->GetWidgetClass());
			bIsUserWidget = false;
		}
		else
		{
			bIsUserWidget = true;
		}

		if (Widget && Widget->IsInViewport())
		{
			Widget->RemoveFromParent();
		}

		if (Widget && !Widget->IsInViewport())
		{
			UWidgetTree* WidgetTree = Widget->WidgetTree;
			UWidget* DialogueQuestionsSlot = WidgetTree->FindWidget(DialogueTextOptions.DialogueQuestionsSlotName);
			if (DialogueQuestionsSlot != nullptr)
			{
				DialogueQuestionsSlot->SetVisibility(ESlateVisibility::Hidden);
			}

			// text
			DialoguePhraseSlot = WidgetTree->FindWidget(DialogueTextOptions.DialoguePhraseSlotName);
			if (DialoguePhraseSlot != nullptr)
			{
				DialoguePhraseSlot->SetVisibility(ESlateVisibility::Visible);
				UTextBlock* StartPhraseTextBlock = Cast<UTextBlock>(DialoguePhraseSlot);
				if (StartPhraseTextBlock)
				{
					if (DialogueTextOptions.bShowTextPhrases)
					{
						PhrasesCount = DialogueTextOptions.Phrases.Num() - 1; // starts from 0
						if (ShowingNumPhrase > PhrasesCount)
						{
							ShowingNumPhrase = 0;
						}
						FText StartPhrase = DialogueTextOptions.Phrases.Num() > 0 ? DialogueTextOptions.Phrases[ShowingNumPhrase].Phrase : FText::GetEmpty();
						if (DialogueTextOptions.TextEffect == ETextEffect::NoEffect || DialogueTextOptions.Delay == 0.0f)
						{
							StartPhraseTextBlock->SetText(FText::Format(NSLOCTEXT("DialogueSystem", "ShowPhraseText", "{0}"), StartPhrase));
							float ShowingTime = DialogueTextOptions.UseGeneralTime ? DialogueTextOptions.GeneralShowingTime : DialogueTextOptions.Phrases[ShowingNumPhrase].ShowingTime;
							TimerDelegate = FTimerDelegate::CreateUObject(this, &UBTTask_ShowPhrases::ShowNewDialoguePhrase, false);
							OwnerActor->GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, ShowingTime, false);
						}
						else
						{
							if (DialogueTextOptions.TextEffect == ETextEffect::Typewriter)
							{
								CurrentCharNum = 1; StringToDisplay = "";
								FullString = StartPhrase.ToString().GetCharArray();
								StringToDisplay.AppendChar(FullString[0]);
								if (StartPhraseTextBlock)
								{
									StartPhraseTextBlock->SetText(FText::Format(NSLOCTEXT("DialogueSystem", "ShowPhraseText", "{0}"), FText::FromString(StringToDisplay)));
								}
								TimerDelegate = FTimerDelegate::CreateUObject(this, &UBTTask_ShowPhrases::ShowNewChar);
								OwnerActor->GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, DialogueTextOptions.Delay, false);
							}
						}
						// play phrase sound 
						if (DialogueTextOptions.Phrases[ShowingNumPhrase].SoundToPlay)
						{
							PhraseAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), DialogueTextOptions.Phrases[ShowingNumPhrase].SoundToPlay);
						}
					}
					else
					{
						DialoguePhraseSlot->SetVisibility(ESlateVisibility::Hidden);
						bTextFinished = true;
					}
				}
			}
			// name
			DialogueNameSlot = WidgetTree->FindWidget(DialogueNameOptions.DialogueSpeakerNameSlotName);
			if (DialogueNameSlot != nullptr)
			{
				if (DialogueNameOptions.bShowName)
				{
					DialogueNameSlot->SetVisibility(ESlateVisibility::Visible);
					UTextBlock* NameTextBlock = Cast<UTextBlock>(DialogueNameSlot);
					if (NameTextBlock)
					{
						NameTextBlock->SetText(DialogueNameOptions.Name);
					}
				}
				else
				{
					DialogueNameSlot->SetVisibility(ESlateVisibility::Hidden);
				}
			}
			// image
			DialogueImageSlot = WidgetTree->FindWidget(DialogueImageOptions.DialogueSpeakerImageSlotName);
			if (DialogueImageSlot != nullptr)
			{
				if (DialogueImageOptions.bShowImage)
				{
					DialogueImageSlot->SetVisibility(ESlateVisibility::Visible);
					UImage* DialogueImage = Cast<UImage>(DialogueImageSlot);
					if (DialogueImage)
					{
						DialogueImage->SetBrushFromTexture(DialogueImageOptions.Image);
					}
				}
				else
				{
					DialogueImageSlot->SetVisibility(ESlateVisibility::Hidden);
				}
			}
			// general sound
			if (DialogueSoundOptions.bPlaySound)
			{
				if (DialogueSoundOptions.SoundToPlay)
				{
					GeneralAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), DialogueSoundOptions.SoundToPlay);
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
			// character animation
			if (DialogueCharacterAnimationOptions.bPlayAnimation && !DialogueCharacterAnimationOptions.Mesh.IsNone() && DialogueCharacterAnimationOptions.Animation != nullptr)
			{
				FName MeshKeyName = DialogueCharacterAnimationOptions.Mesh.SelectedKeyName;
				BlackboardComp = OwnerComp.GetBlackboardComponent();
				Mesh = Cast<USkeletalMeshComponent>(BlackboardComp->GetValueAsObject(MeshKeyName));
				if (Mesh)
				{
					UAnimInstance *AnimInst = Mesh->GetAnimInstance();
					if (AnimInst)
					{
						AnimInst->PlaySlotAnimationAsDynamicMontage(DialogueCharacterAnimationOptions.Animation, 
							DialogueCharacterAnimationOptions.AnimationBlendOptions.SlotNodeName,
							DialogueCharacterAnimationOptions.AnimationBlendOptions.BlendInTime,
							DialogueCharacterAnimationOptions.AnimationBlendOptions.BlendOutTime,
							DialogueCharacterAnimationOptions.AnimationBlendOptions.InPlayRate);
					}
					if (DialogueCharacterAnimationOptions.bWaitEndOfAnimation)
					{
						UAnimSequenceBase* SequenceBase = DialogueCharacterAnimationOptions.Animation;
						CharacterAnimationDuration = SequenceBase->SequenceLength / SequenceBase->RateScale;
					}
				}
				bCharacterAnimationStarted = true;
			}
			// Event Listener

			UWidget* DialogueEventListener = WidgetTree->FindWidget(FName("DialogueEventListener"));
			if (DialogueEventListener != nullptr)
			{
				UDialogueEventListener* EventListener = Cast<UDialogueEventListener>(DialogueEventListener);
				if (EventListener)
				{
					EventListener->ShowPhrasesNode = this;
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
			PlayerController = Widget->GetOwningPlayer();
			if (InputMode == EWidggetInputMode::UIOnly)
			{
				FInputModeUIOnly InputModeUIOnly;
				InputModeUIOnly.SetWidgetToFocus(Widget->TakeWidget());
				PlayerController->SetInputMode(InputModeUIOnly);
			}
			else
			{
				FInputModeGameAndUI InputModeGameAndUI;
				InputModeGameAndUI.SetWidgetToFocus(Widget->TakeWidget());
				PlayerController->SetInputMode(InputModeGameAndUI);
			}
		}
		else
		{
			bTextFinished = true;
			NodeResult = EBTNodeResult::Failed;
		}
	}
	
	return NodeResult;
}

void UBTTask_ShowPhrases::ShowNewDialoguePhrase(bool bSkip)
{
	if (bSkip && DialogueTextOptions.TextEffect == ETextEffect::Typewriter && !bShowingFullPhrase)
	{
		FText StartPhrase = DialogueTextOptions.Phrases[ShowingNumPhrase].Phrase;
		UTextBlock* StartPhraseTextBlock = Cast<UTextBlock>(DialoguePhraseSlot);
		if (StartPhraseTextBlock)
		{
			// first show hole phrase 
			UE_LOG(LogTemp, Warning, TEXT("#1"));
			StartPhraseTextBlock->SetText(FText::Format(NSLOCTEXT("DialogueSystem", "ShowPhraseText", "{0}"), StartPhrase));
			UE_LOG(LogTemp, Warning, TEXT("#1.1"));
			OwnerActor->GetWorldTimerManager().ClearTimer(TimerHandle);
			TimerDelegate = FTimerDelegate::CreateUObject(this, &UBTTask_ShowPhrases::ShowNewDialoguePhrase, false);
			float ShowingTime = DialogueTextOptions.UseGeneralTime ? DialogueTextOptions.GeneralShowingTime : DialogueTextOptions.Phrases[ShowingNumPhrase].ShowingTime;
			OwnerActor->GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, ShowingTime, false);
		}
		bShowingFullPhrase = true;
		return;
	}
	ShowingNumPhrase++;
	if (ShowingNumPhrase <= PhrasesCount)
	{
		bTextFinished = false;
		FText StartPhrase = DialogueTextOptions.Phrases[ShowingNumPhrase].Phrase;
		UTextBlock* StartPhraseTextBlock = Cast<UTextBlock>(DialoguePhraseSlot);

		if (DialogueTextOptions.TextEffect == ETextEffect::Typewriter && DialogueTextOptions.Delay > 0)
		{
			OwnerActor->GetWorldTimerManager().ClearTimer(TimerHandle);
			CurrentCharNum = 1; StringToDisplay = "";
			FullString = StartPhrase.ToString().GetCharArray();
			StringToDisplay.AppendChar(FullString[0]);
			if (StartPhraseTextBlock)
			{
			UE_LOG(LogTemp, Warning, TEXT("#2"));
				StartPhraseTextBlock->SetText(FText::Format(NSLOCTEXT("DialogueSystem", "ShowPhraseText", "{0}"), FText::FromString(StringToDisplay)));
			UE_LOG(LogTemp, Warning, TEXT("#2.2"));
			}
			TimerDelegate = FTimerDelegate::CreateUObject(this, &UBTTask_ShowPhrases::ShowNewChar);
			OwnerActor->GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, DialogueTextOptions.Delay, false);
		}
		else
		{
			if (StartPhraseTextBlock)
			{
			UE_LOG(LogTemp, Warning, TEXT("#3"));
				StartPhraseTextBlock->SetText(FText::Format(NSLOCTEXT("DialogueSystem", "ShowPhraseText", "{0}"), StartPhrase));
			UE_LOG(LogTemp, Warning, TEXT("#3.3"));
			}
			float ShowingTime = DialogueTextOptions.UseGeneralTime ? DialogueTextOptions.GeneralShowingTime : DialogueTextOptions.Phrases[ShowingNumPhrase].ShowingTime;
			OwnerActor->GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, ShowingTime, false);
		}
		//phrase sound
		if (DialogueTextOptions.Phrases[ShowingNumPhrase].SoundToPlay)
		{
			PhraseAudioComponent->Deactivate();
			PhraseAudioComponent->DestroyComponent();
			PhraseAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), DialogueTextOptions.Phrases[ShowingNumPhrase].SoundToPlay);
		}
		bShowingFullPhrase = false;
	}
	else
	{
		if (DialogueTextOptions.bHideLastPhrase)
		{
			if (DialoguePhraseSlot != nullptr)
			{
				DialoguePhraseSlot->SetVisibility(ESlateVisibility::Hidden);
			}
			if (DialogueNameSlot != nullptr)
			{
				DialogueNameSlot->SetVisibility(ESlateVisibility::Hidden);
			}
			if (DialogueImageSlot != nullptr)
			{
				DialogueImageSlot->SetVisibility(ESlateVisibility::Hidden);
			}
			if (!bIsUserWidget)
			{
				WidgetComp->SetVisibility(false);
				WidgetComp->SetActive(false);
			}
		}
		bTextFinished = true;
		if (DialogueTextOptions.Phrases[ShowingNumPhrase-1].SoundToPlay)
		{
			PhraseAudioComponent->Deactivate();
			PhraseAudioComponent->DestroyComponent();
		}
		if (GeneralAudioComponent != NULL && DialogueSoundOptions.bPlaySound && DialogueSoundOptions.bStopInEnd)
		{
			GeneralAudioComponent->Deactivate();
			GeneralAudioComponent->DestroyComponent();
		}
	}
}

void UBTTask_ShowPhrases::ShowNewChar()
{
	StringToDisplay.AppendChar(FullString[CurrentCharNum]);
	UTextBlock* StartPhraseTextBlock = Cast<UTextBlock>(DialoguePhraseSlot);
	if (StartPhraseTextBlock)
	{
		StartPhraseTextBlock->SetText(FText::Format(NSLOCTEXT("DialogueSystem", "ShowPhraseText", "{0}"), FText::FromString(StringToDisplay)));
	}
	CurrentCharNum++;
	if (CurrentCharNum >= FullString.Num() - 1)
	{
		float ShowingTime = DialogueTextOptions.UseGeneralTime ? DialogueTextOptions.GeneralShowingTime : DialogueTextOptions.Phrases[ShowingNumPhrase].ShowingTime;
		TimerDelegate = FTimerDelegate::CreateUObject(this, &UBTTask_ShowPhrases::ShowNewDialoguePhrase, false);
		OwnerActor->GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, ShowingTime, false);
	}
	else
	{
		OwnerActor->GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, DialogueTextOptions.Delay, false);
	}
};

void UBTTask_ShowPhrases::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	bool bCharacterAnimationFinished = true;

	if (DialogueCharacterAnimationOptions.bPlayAnimation)
	{
		CharacterAnimationDuration -= DeltaSeconds;
		if (CharacterAnimationDuration <=0.0f && DialogueCharacterAnimationOptions.bLoop && !bTextFinished)
		{
			UAnimInstance *AnimInst = Mesh->GetAnimInstance();
			if (AnimInst)
			{
				AnimInst->PlaySlotAnimationAsDynamicMontage(DialogueCharacterAnimationOptions.Animation,
					DialogueCharacterAnimationOptions.AnimationBlendOptions.SlotNodeName,
					DialogueCharacterAnimationOptions.AnimationBlendOptions.BlendInTime,
					DialogueCharacterAnimationOptions.AnimationBlendOptions.BlendOutTime,
					DialogueCharacterAnimationOptions.AnimationBlendOptions.InPlayRate);
			}
			UAnimSequenceBase* SequenceBase = DialogueCharacterAnimationOptions.Animation;
			CharacterAnimationDuration = SequenceBase->SequenceLength / SequenceBase->RateScale;
		}
		bCharacterAnimationFinished = (CharacterAnimationDuration <= 0.0f && bCharacterAnimationStarted) || (!DialogueCharacterAnimationOptions.bWaitEndOfAnimation && bTextFinished) ? true : false;
	}
	if (bTextFinished && bCharacterAnimationFinished)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		bCharacterAnimationFinished = false;
		bTextFinished = false;
		ShowingNumPhrase = 0;
		UWidgetTree* WidgetTree = Widget->WidgetTree;
		UWidget* DialogueEventListener = WidgetTree->FindWidget(FName("DialogueEventListener"));
		if (DialogueEventListener != nullptr)
		{
			UDialogueEventListener* EventListener = Cast<UDialogueEventListener>(DialogueEventListener);
			if (EventListener)
			{
				EventListener->ShowPhrasesNode = nullptr;
			}
		}
	}
}

void UBTTask_ShowPhrases::SaveDefaultCameraDataForAll(UBTNode* Node)
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

void UBTTask_ShowPhrases::SaveDefaultCameraData(UCameraComponent* Camera)
{
	if (DefaultCameraLocation.IsZero() || DefaultCameraRotation.IsZero())
	{
		DefaultCameraLocation = Camera->GetComponentLocation();
		DefaultCameraRotation = Camera->GetComponentRotation();
		UBTCompositeNode* Parent = GetParentNode();
		SaveDefaultCameraDataForAll(Parent);
	}
}

FString UBTTask_ShowPhrases::GetStaticDescription() const
{
	FString StringPhrases;
	StringPhrases = FString::Printf(TEXT("Sound: %s"),
		DialogueSoundOptions.bPlaySound && DialogueSoundOptions.SoundToPlay ? *DialogueSoundOptions.SoundToPlay->GetName() : TEXT("none"));
	if (DialogueTextOptions.Phrases.Num() > 0)
	{
		for (int32 i = 0; i < DialogueTextOptions.Phrases.Num(); i++)
		{
			if (StringPhrases == TEXT(""))
			{
				StringPhrases += DialogueTextOptions.Phrases[i].Phrase.ToString();
			}
			else
			{
				StringPhrases += TEXT('\n');
				StringPhrases += DialogueTextOptions.Phrases[i].Phrase.ToString();
			}
		}
	}
	else
	{
		StringPhrases += TEXT("\nPhrases: none");
	}

	if (!bShowPropertyDetails)
	{
		StringPhrases = FString::Printf(TEXT("Sound: %s \nPhrases: %i"),
			DialogueSoundOptions.bPlaySound && DialogueSoundOptions.SoundToPlay ? *DialogueSoundOptions.SoundToPlay->GetName() : TEXT("none"),
			DialogueTextOptions.Phrases.Num());
	}

	return StringPhrases;
}


#if WITH_EDITOR

FName UBTTask_ShowPhrases::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Decorator.Cooldown.Icon");
}

#endif	// WITH_EDITOR

#undef LOCTEXT_NAMESPACE
