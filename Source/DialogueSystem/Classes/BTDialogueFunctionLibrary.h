//Copyright (c) 2016 Artem A. Mavrin and other contributors

#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/SlateWrapperTypes.h"

#include "Quest.h"
#include "DialogueSettings.h"
#include "BTDialogueFunctionLibrary.generated.h"

class UBlackboardComponent;
struct FBlackboardKeySelector;

//UCLASS(meta = (RestrictedToClasses = "BTNode"))
UCLASS()
class DIALOGUESYSTEM_API UBTDialogueFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "DialogueSystem|Dialogue", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
		static void SetQuestionVisibility(UBTNode* NodeOwner, FString QuestionNodeName, bool NewVisibility);

	UFUNCTION(BlueprintCallable, Category = "DialogueSystem|Dialogue", Meta = (DefaultToSelf = "EventListener"))
		static void SkipCurrentPhrase(UDialogueEventListener* EventListener);

	UFUNCTION(BlueprintCallable, Category = "DialogueSystem|Dialogue", Meta = (DefaultToSelf = "DialogueSettings"))
		static ADialogueSettings* GenerateSettings(TSubclassOf<ADialogueSettings> DialogueSettings, APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "DialogueSystem|Quest", Meta = (DefaultToSelf = "Quests"))
		static void AddQuest(UPARAM(ref) TArray<FQuest>& Quests, FQuest Quest);

	UFUNCTION(BlueprintCallable, Category = "DialogueSystem|Quest", Meta = (DefaultToSelf = "Quests"))
		static void DeleteQuest(UPARAM(ref) TArray<FQuest>& Quests, FQuest Quest);

	UFUNCTION(BlueprintCallable, Category = "DialogueSystem|Quest", Meta = (DefaultToSelf = "Quest"))
		static void UpdateTaskProgress(UPARAM(ref) FQuest& Quest, int32 TaskIndex);

	UFUNCTION(BlueprintCallable, Category = "DialogueSystem|Quest", Meta = (DefaultToSelf = "Quests"))
		static bool HasQuest(TArray<FQuest> Quests, FQuest Quest);
	
};