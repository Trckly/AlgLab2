// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAwesomeBTree.h"

void UMyAwesomeBTree::Construct()
{
	Root = nullptr;
	NodeQuantity = 0;
	WalkArray = nullptr;
	CurrentIndex = 0;
}

void UMyAwesomeBTree::Add(float Element)
{
	int RowOffset = 0;
	int ColumnOffset = 0;
	
	FTreeNode* NewNode = new FTreeNode;
	NewNode->Value = Element;
	NewNode->Parent = nullptr;
	NewNode->LeftChild = nullptr;
	NewNode->RightChild = nullptr;

	if(Root == nullptr)
	{
		Root = NewNode;
		NodeQuantity++;
		SetOffset.ExecuteIfBound(*NewNode, RowOffset, ColumnOffset);
		return;
	}

	FTreeNode* Runner = Root;

	while(true)
	{
		if(Runner->Value > NewNode->Value)
		{
			RowOffset++;
			ColumnOffset = -1;
			
			if(Runner->LeftChild == nullptr)
			{
				NewNode->Parent = Runner;
				Runner->LeftChild = NewNode;
				NodeQuantity++;
				SetOffset.ExecuteIfBound(*NewNode, RowOffset, ColumnOffset);
				break;
			}

			Runner = Runner->LeftChild;
			continue;
		}
		
		if(Runner->Value < NewNode->Value)
		{
			RowOffset++;
			ColumnOffset = 1;
			
			if(Runner->RightChild == nullptr)
			{
				NewNode->Parent = Runner;
				Runner->RightChild = NewNode;
				NodeQuantity++;
				SetOffset.ExecuteIfBound(*NewNode, RowOffset, ColumnOffset);
				break;
			}
			
			Runner = Runner->RightChild;
			continue;
		}
		
		break;
	}
}

bool UMyAwesomeBTree::Exists(float Element, FTreeNode* CurrentNode)
{
	bool IsFound = false;
	if(CurrentNode->Value == Element) return true;

	if(CurrentNode->LeftChild != nullptr)
		IsFound = Exists(Element, CurrentNode->LeftChild);
	if(IsFound) return IsFound;

	if(CurrentNode->RightChild != nullptr)
		IsFound = Exists(Element, CurrentNode->RightChild);

	return IsFound;	
}

FTreeNode* UMyAwesomeBTree::Find(float Element, FTreeNode* CurrentNode)
{
	FTreeNode* Result = nullptr;
	if(CurrentNode->Value == Element) return CurrentNode;

	if(CurrentNode->LeftChild != nullptr)
		Result = Find(Element, CurrentNode->LeftChild);
	if(Result) return Result;

	if(CurrentNode->RightChild != nullptr)
		Result = Find(Element, CurrentNode->RightChild);

	return Result;	
}

float* UMyAwesomeBTree::WalkTheTree()
{
	if(WalkArray)
		delete[] WalkArray;

	if(CurrentIndex != 0)
		CurrentIndex = 0;
	
	WalkArray = new float[NodeQuantity];

	Walk(Root);

	return WalkArray;
}

int UMyAwesomeBTree::Num()
{
	return NodeQuantity;
}

void UMyAwesomeBTree::Walk(FTreeNode* CurrentNode)
{
	if(CurrentNode->LeftChild != nullptr)
	{
		Walk(CurrentNode->LeftChild);
	}
	if(CurrentNode->RightChild != nullptr)
	{
		Walk(CurrentNode->RightChild);
	}

	WalkArray[CurrentIndex++] = CurrentNode->Value;
}

FTreeNode* UMyAwesomeBTree::GetRoot() const
{
	return Root;
}
