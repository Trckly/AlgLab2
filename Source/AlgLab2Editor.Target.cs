// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AlgLab2EditorTarget : TargetRules
{
	public AlgLab2EditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "AlgLab2" } );
        
        bOverrideBuildEnvironment = true; 
        AdditionalCompilerArguments = "-Wno-unused-but-set-variable";
	}
}
