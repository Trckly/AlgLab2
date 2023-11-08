// Fill out your copyright notice in the Description page of Project Settings.


#include "BinTree.h"

BinTree::BinTree()
{
	Root = nullptr;
}

BinTree::~BinTree()
{
	if(Root)
	{
		delete Root->LeftChild;
		delete Root->RightChild;
		delete Root;
		Root->LeftChild = nullptr;
		Root->RightChild = nullptr;
		Root = nullptr;
	}
}

void BinTree::Push(char Value) noexcept
{
	if(!Root)
	{
		Root = new Node{Value, nullptr,nullptr};
	}
	else
	{
		Node* Head = Root;
		bool bFoundPlace = false;
		while(!bFoundPlace)
		{
			if(FChar::ToUnsigned(Value) < FChar::ToUnsigned(Head->Value))
			{
				if(!Head->LeftChild)
				{
					Head->LeftChild = new Node{Value,nullptr, nullptr};
					bFoundPlace = true;
				}
				else
					Head = Head->LeftChild;
			}
			else
			{
				if(!Head->RightChild)
				{
					Head->RightChild = new Node{Value,nullptr, nullptr};
					bFoundPlace = true;
				}
				else
					Head = Head->RightChild;
			}
		}
	}
}

TArray<char> BinTree::Traverse()
{
	TArray<char> Result;
	MixedTraversal(Root, Result);
	return Result;
}

bool BinTree::Find(char Character)
{
	TArray<char> Result;
	MixedTraversal(Root, Result);
	for (char Value : Result)
	{
		if (Value == Character)
		{
			return true;
		}
	}
	return false;
}

void BinTree::MixedTraversal(Node* RootNode, TArray<char>& Store)
{
	Node* Left = RootNode->LeftChild,* Right = RootNode->RightChild;
	if (!Left && !Right)
	{
		return;
	}
	if(Left)
	{
		MixedTraversal(RootNode->LeftChild, Store);
	}
	if(Right)
	{
		MixedTraversal(RootNode->RightChild, Store);
	}
	Store.Push(RootNode->Value);
}

void BinTree::Empty()
{
	if(Root)
	{
		delete Root->LeftChild;
		delete Root->RightChild;
		delete Root;
		Root->LeftChild = nullptr;
		Root->RightChild = nullptr;
		Root = nullptr;
	}
}
