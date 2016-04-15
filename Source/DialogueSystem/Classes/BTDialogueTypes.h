// Copyright 2015 Mavrin Artem. All Rights Reserved.

#pragma once
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeTypes.h"
#include "Engine/Texture2D.h"
#include "BTDialogueTypes.generated.h"

UENUM()
enum class ETextEffect : uint8
{
	/** Text has no effect */
	NoEffect,

	/** Text has typewriter effect */
	Typewriter,
};

USTRUCT()
struct DIALOGUESYSTEM_API FBTDialogueTextPhrase
{
	GENERATED_USTRUCT_BODY()

	/** Phrase */
	UPROPERTY(EditInstanceOnly, meta = (MultiLine = true), Category = Text)
	FText Phrase;

	/** How long to show the phrase */
	UPROPERTY(EditInstanceOnly, meta = (UIMin = 0, ClampMin = 0), Category = Text)
	float ShowingTime;

};

USTRUCT()
struct DIALOGUESYSTEM_API FBTDialogueTextOptions
{
	GENERATED_USTRUCT_BODY()

	/** Enable to show text phrase */
	UPROPERTY(EditInstanceOnly, Category = General)
	bool bShowTextPhrases;

	/** Enable to hide last phrase */
	UPROPERTY(EditInstanceOnly, Category = General)
	bool bHideLastPhrase;

	/** How long to show each phrase */
	UPROPERTY(EditInstanceOnly, meta = (UIMin = 0, ClampMin = 0), Category = General)
	float GeneralShowingTime;

	/** Enable to use general time for all phrases */
	UPROPERTY(EditInstanceOnly, Category = General)
	bool UseGeneralTime;

	/** Name of TextBlock where will be show phrases */
	UPROPERTY(EditInstanceOnly, Category = Widget)
	FName DialoguePhraseSlotName;

	/** Name of Widget where will be show questions */
	UPROPERTY(EditInstanceOnly, Category = Widget)
	FName DialogueQuestionsSlotName;

	/** Phrases */
	UPROPERTY(EditInstanceOnly, Category = Text)
	TArray<FBTDialogueTextPhrase> Phrases;

	/** Effect */
	UPROPERTY(EditInstanceOnly, Category = TextEffect)
	ETextEffect TextEffect;

	/** Delay of typewriter */
	UPROPERTY(EditInstanceOnly, Category = TextEffect)
	float Delay;
};

USTRUCT()
struct DIALOGUESYSTEM_API FBTDialogueSoundOptions
{
	GENERATED_USTRUCT_BODY()

	/** Enable to play sound */
	UPROPERTY(EditInstanceOnly, Category = Sound)
	bool bPlaySound;

	/** CUE to play */
	UPROPERTY(EditInstanceOnly, Category = Sound)
	USoundCue* SoundToPlay;
};

USTRUCT()
struct DIALOGUESYSTEM_API FBTDialogueImageOptions
{
	GENERATED_USTRUCT_BODY()

	/** Enable to show speaker's image */
	UPROPERTY(EditInstanceOnly, Category = Image)
	bool bShowImage;

	/** Speaker's image */
	UPROPERTY(EditInstanceOnly, Category = Image)
	UTexture2D* Image;

	/** Name of Image where will be show Speaker's Image */
	UPROPERTY(EditInstanceOnly, Category = Widget)
	FName DialogueSpeakerImageSlotName;
};

USTRUCT()
struct DIALOGUESYSTEM_API FBTDialogueNameOptions
{
	GENERATED_USTRUCT_BODY()

	/** Enable to show speaker's name */
	UPROPERTY(EditInstanceOnly, Category = Name)
	bool bShowName;

	/** Speaker's name */
	UPROPERTY(EditInstanceOnly, Category = Name)
	FText Name;

	/** Name of TextBlock where will be show Speaker's Name */
	UPROPERTY(EditInstanceOnly, Category = Widget)
	FName DialogueSpeakerNameSlotName;
};

USTRUCT()
struct DIALOGUESYSTEM_API FBTDialogueCameraOptions
{
	GENERATED_USTRUCT_BODY()

	/** Enable to switch camera */
	UPROPERTY(EditInstanceOnly, Category = Camera)
	bool bUseCamera;

	/** Camera to view*/
	UPROPERTY(EditInstanceOnly, Category = Camera)
	FBlackboardKeySelector CameraToView;

	/** Player camera*/
	UPROPERTY(EditInstanceOnly, Category = Camera)
	FBlackboardKeySelector PlayerCamera;
};

USTRUCT()
struct DIALOGUESYSTEM_API FBTAnimationBlendOptions
{
	GENERATED_USTRUCT_BODY()

	/** Slot node name in Animation Blueprint*/
	UPROPERTY(EditInstanceOnly, Category = Animation)
	FName SlotNodeName;

	/** Blend In time */
	UPROPERTY(EditInstanceOnly, Category = Animation)
		float BlendInTime;

	/** Blend Out time */
	UPROPERTY(EditInstanceOnly, Category = Animation)
		float BlendOutTime;

	/** Play rate */
	UPROPERTY(EditInstanceOnly, Category = Animation)
		float InPlayRate;

};

USTRUCT()
struct DIALOGUESYSTEM_API FBTDialogueCharacterAnimationOptions
{
	GENERATED_USTRUCT_BODY()

	/** Enable to play character animation */
	UPROPERTY(EditInstanceOnly, Category = Animation)
	bool bPlayAnimation;

	/** Enable to loop character animation */
	UPROPERTY(EditInstanceOnly, Category = Animation)
	bool bLoop;

	/** Enable to play the whole animation character animation */
	UPROPERTY(EditInstanceOnly, Category = Animation)
	bool bWaitEndOfAnimation;

	/** Skeletal mesh component*/
	UPROPERTY(EditInstanceOnly, Category = Animation)
	FBlackboardKeySelector Mesh;

	/** Animation*/
	UPROPERTY(EditInstanceOnly, Category = Animation)
	UAnimSequenceBase* Animation;

	/** Blend Options*/
	UPROPERTY(EditInstanceOnly, Category = Animation)
	FBTAnimationBlendOptions AnimationBlendOptions;
};

UENUM()
enum class EWidggetInputMode : uint8
{
	/** Input mode that allows only the UI to respond to user input */
	UIOnly,
	/** Input mode that allows the UI to respond to user input, and if the UI doesn't handle it player input / player controller gets a chance. */
	GameAndUI,
};

