// VRM4U Copyright (c) 2021-2024 Haruyoshi Yamamoto. This software is released under the MIT License.


#include "VrmAssetListObject.h"
#include "EditorFramework/AssetImportData.h"
//#include "LoaderBPFunctionLibrary.h"



UVrmAssetListObject::UVrmAssetListObject(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	RootPackagePath = GetTransientPackage()->GetName();

	//Result = new FReturnedData();
}


void UVrmAssetListObject::CopyMember(UVrmAssetListObject *dst) const {
	dst->bAssetSave = bAssetSave;
	dst->bSkipMorphTarget = bSkipMorphTarget;

	dst->MtoonLitSet = MtoonLitSet;
	dst->MtoonUnlitSet = MtoonUnlitSet;
	dst->SSSSet = SSSSet;
	dst->SSSProfileSet = SSSProfileSet;
	dst->UnlitSet = UnlitSet;
	dst->GLTFSet = GLTFSet;
	dst->UEFNUnlitSet = UEFNUnlitSet;
	dst->UEFNLitSet = UEFNLitSet;
	dst->UEFNSSSProfileSet = UEFNSSSProfileSet;
	dst->CustomSet = CustomSet;


	dst->BaseMToonLitOpaqueMaterial = BaseMToonLitOpaqueMaterial;
	dst->BaseMToonLitTranslucentMaterial = BaseMToonLitTranslucentMaterial;
	dst->OptMToonLitOpaqueMaterial = OptMToonLitOpaqueMaterial;
	dst->OptMToonLitOpaqueTwoSidedMaterial = OptMToonLitOpaqueTwoSidedMaterial;
	dst->OptMToonLitTranslucentMaterial = OptMToonLitTranslucentMaterial;
	dst->OptMToonLitTranslucentTwoSidedMaterial = OptMToonLitTranslucentTwoSidedMaterial;

	dst->BaseMToonUnlitOpaqueMaterial = BaseMToonUnlitOpaqueMaterial;
	dst->BaseMToonUnlitTranslucentMaterial = BaseMToonUnlitTranslucentMaterial;
	dst->OptMToonUnlitOpaqueMaterial = OptMToonUnlitOpaqueMaterial;
	dst->OptMToonUnlitOpaqueTwoSidedMaterial = OptMToonUnlitOpaqueTwoSidedMaterial;
	dst->OptMToonUnlitTranslucentMaterial = OptMToonUnlitTranslucentMaterial;
	dst->OptMToonUnlitTranslucentTwoSidedMaterial = OptMToonUnlitTranslucentTwoSidedMaterial;

	dst->OptMToonOutlineMaterial = OptMToonOutlineMaterial;

	dst->BaseUnlitOpaqueMaterial			= BaseUnlitOpaqueMaterial;
	dst->BaseUnlitTranslucentMaterial = BaseUnlitTranslucentMaterial;
	dst->BasePBROpaqueMaterial = BasePBROpaqueMaterial;


	dst->BaseSkeletalMesh = BaseSkeletalMesh;
	dst->VrmMetaObject = VrmMetaObject;
	dst->VrmLicenseObject = VrmLicenseObject;
	dst->Vrm1LicenseObject = Vrm1LicenseObject;
	dst->SkeletalMesh = SkeletalMesh;
	dst->Textures = Textures;
	dst->Materials = Materials;
	dst->HumanoidRig = HumanoidRig;
	dst->RootPackagePath = RootPackagePath;
	dst->FileFullPathName = FileFullPathName;
	dst->OrigFileName = OrigFileName;
	dst->BaseFileName = BaseFileName;
	dst->HumanoidSkeletalMesh = HumanoidSkeletalMesh;
}

UPackage* UVrmAssetListObject::GetPackage() const
{
	if (RootPackagePath.IsEmpty())
	{
		return nullptr;
	}

	if (UPackage* existingPackage = FindPackage(nullptr, *RootPackagePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Existing"));
		return existingPackage;
	}

	UPackage* newPackage = CreatePackage(*RootPackagePath);
	newPackage->FullyLoad();

	return newPackage;
}

void UVrmAssetListObject::SetPackage(UPackage* package)
{
	if (!package)
	{
		RootPackagePath.Reset();
		return;
	}

	RootPackagePath = package->GetName();
}

#if WITH_EDITOR
void UVrmAssetListObject::GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const
{
	if (AssetImportData)
	{
		OutTags.Add(FAssetRegistryTag(SourceFileTagName(), AssetImportData->GetSourceData().ToJson(), FAssetRegistryTag::TT_Hidden));

		OutTags.Add(FAssetRegistryTag("VRM4U", SourceFileTagName().ToString(), FAssetRegistryTag::TT_Hidden));
	}
	Super::GetAssetRegistryTags(OutTags);
}

void UVrmAssetListObject::WaitUntilAsyncPropertyReleased() const {
	if (IsValid(SkeletalMesh) == false) {
		return;
	}
	//SkeletalMesh->WaitUntilAsyncPropertyReleased(AsyncProperties);
}


#endif
