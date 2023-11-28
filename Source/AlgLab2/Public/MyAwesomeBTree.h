// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyAwesomeBTree.generated.h"

USTRUCT()
struct FTreeNode
{
	GENERATED_BODY()
	
	float Value;
	int Offset;
	FTreeNode* Parent;
	FTreeNode* LeftChild;
	FTreeNode* RightChild;
};

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FSetOffset, FTreeNode&, Element, int, RowOffset, int, ColumnOffset);

/**
 * 
 */
UCLASS()
class ALGLAB2_API UMyAwesomeBTree : public UObject
{
	GENERATED_BODY()
protected:
	FTreeNode* Root;

	int NodeQuantity;

	float* WalkArray;

	int CurrentIndex;

	void Walk(FTreeNode* CurrentNode);

public:
	FSetOffset SetOffset;
	
	void Construct();

	void Add(float Element);

	bool Exists(float Element, FTreeNode* CurrentNode);

	FTreeNode* Find(float Element, FTreeNode* CurrentNode);

	float* WalkTheTree();

	int Num();

	FTreeNode* GetRoot() const;
};
