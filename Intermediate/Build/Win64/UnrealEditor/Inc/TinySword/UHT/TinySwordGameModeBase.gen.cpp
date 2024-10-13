// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TinySword/TinySwordGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTinySwordGameModeBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	TINYSWORD_API UClass* Z_Construct_UClass_ATinySwordGameModeBase();
	TINYSWORD_API UClass* Z_Construct_UClass_ATinySwordGameModeBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_TinySword();
// End Cross Module References
	void ATinySwordGameModeBase::StaticRegisterNativesATinySwordGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATinySwordGameModeBase);
	UClass* Z_Construct_UClass_ATinySwordGameModeBase_NoRegister()
	{
		return ATinySwordGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ATinySwordGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATinySwordGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_TinySword,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATinySwordGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "TinySwordGameModeBase.h" },
		{ "ModuleRelativePath", "TinySwordGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATinySwordGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATinySwordGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATinySwordGameModeBase_Statics::ClassParams = {
		&ATinySwordGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ATinySwordGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATinySwordGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATinySwordGameModeBase()
	{
		if (!Z_Registration_Info_UClass_ATinySwordGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATinySwordGameModeBase.OuterSingleton, Z_Construct_UClass_ATinySwordGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATinySwordGameModeBase.OuterSingleton;
	}
	template<> TINYSWORD_API UClass* StaticClass<ATinySwordGameModeBase>()
	{
		return ATinySwordGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATinySwordGameModeBase);
	ATinySwordGameModeBase::~ATinySwordGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_Users_hayeo_OneDrive_Documents_Unreal_Projects_TinySword_Source_TinySword_TinySwordGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_hayeo_OneDrive_Documents_Unreal_Projects_TinySword_Source_TinySword_TinySwordGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATinySwordGameModeBase, ATinySwordGameModeBase::StaticClass, TEXT("ATinySwordGameModeBase"), &Z_Registration_Info_UClass_ATinySwordGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATinySwordGameModeBase), 1073016351U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_hayeo_OneDrive_Documents_Unreal_Projects_TinySword_Source_TinySword_TinySwordGameModeBase_h_3299932273(TEXT("/Script/TinySword"),
		Z_CompiledInDeferFile_FID_Users_hayeo_OneDrive_Documents_Unreal_Projects_TinySword_Source_TinySword_TinySwordGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_hayeo_OneDrive_Documents_Unreal_Projects_TinySword_Source_TinySword_TinySwordGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
