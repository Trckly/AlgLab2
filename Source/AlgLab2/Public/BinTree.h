// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ALGLAB2_API BinTree
{
protected:
	struct Node
	{
		char Value;
		Node* LeftChild;
		Node* RightChild;
	};

	Node* Root;

	void MixedTraversal(Node* RootNode, TArray<char>& Store);
	
public:
	BinTree();
	~BinTree();

	void Push(char Value) noexcept;

	TArray<char> Traverse();

	bool Find(char Character);

	void Empty();

	TArray<char> GetParentAndChildren(char Character);
};
