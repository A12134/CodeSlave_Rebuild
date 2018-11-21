// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class CodeSlave_RebuildTarget : TargetRules
{
	public CodeSlave_RebuildTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "CodeSlave_Rebuild" } );
	}
}
