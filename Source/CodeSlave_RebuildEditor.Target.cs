// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class CodeSlave_RebuildEditorTarget : TargetRules
{
	public CodeSlave_RebuildEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "CodeSlave_Rebuild" } );
	}
}
