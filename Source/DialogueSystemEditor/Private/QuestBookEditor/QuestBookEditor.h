//Copyright (c) 2016 Artem A. Mavrin and other contributors

#pragma once

#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/AssetEditorManager.h"

#include "Editor/PropertyEditor/Public/IDetailsView.h"

//////////////////////////////////////////////////////////////////////////
// FQuestBookEditor

class FQuestBookEditor : public FAssetEditorToolkit, public FGCObject
{
	// IToolkit interface
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	// End of IToolkit interface

	// FAssetEditorToolkit
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FString GetDocumentationLink() const override;
	virtual void OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit) override;
	virtual void OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit) override;
	// End of FAssetEditorToolkit

	// FSerializableObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	// End of FSerializableObject interface

public:
	void InitQuestBookEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UQuestBook* InitQuestBook);
	
	UQuestBook* GetQuestBookBeingEdited() const { return QuestBookBeingEdited; }

protected:
	UQuestBook* QuestBookBeingEdited;

	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);
	void ExtendList();
	
private:
	TSharedPtr<IDetailsView> PropertyEditor;
	void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);
	int32 QuestNum;
};