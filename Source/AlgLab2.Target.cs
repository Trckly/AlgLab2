// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AlgLab2Target : TargetRules
{
	public AlgLab2Target( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "AlgLab2" } );
        
        // bOverrideBuildEnvironment = true; 
        // AdditionalCompilerArguments = "-Wno-unused-but-set-variable";
	}
}
