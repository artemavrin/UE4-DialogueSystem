//Copyright (c) 2016 Artem A. Mavrin and other contributors

#pragma once

#include "AssetTypeActions_Base.h"

class FQuestBookAssetTypeActions : public FAssetTypeActions_Base
{
public:
	FQuestBookAssetTypeActions(EAssetTypeCategories::Type InAssetCategory);

	// IAssetTypeActions interface
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override;
	// End of IAssetTypeActions interface

private:
	EAssetTypeCategories::Type MyAssetCategory;
};