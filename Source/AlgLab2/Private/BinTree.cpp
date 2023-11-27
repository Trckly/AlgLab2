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
	if (RootNode)
	{
		MixedTraversal(RootNode->LeftChild, Store);
		Store.Push(RootNode->Value);
		MixedTraversal(RootNode->RightChild, Store);
	}
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

TArray<char> BinTree::GetParentAndChildren(char Character)
{
	if(Find(Character))
	{
		TArray<char> Result;
		Result.SetNum(3);
		Node* Head = Root;
		if(Head->Value == Character)
		{
			Result[0] = ' ';
			Result[1] = Head->LeftChild->Value;
			Result[2] = Head->RightChild->Value;
		}
		else
		{
			bool bFoundPlace = false;
			while(!bFoundPlace)
			{
				Result[0] = Head->Value;
				if(Head->LeftChild && Head->RightChild)
				{
					if (Head->LeftChild->Value != Character && Head->RightChild->Value != Character)
					{
						if(Character < Head->Value)
							Head = Head->LeftChild;
						else
							Head = Head->RightChild;
					}
					else if (Head->LeftChild->Value == Character)
					{
						Head = Head->LeftChild;
						if(Head->LeftChild)
							Result[1] = Head->LeftChild->Value;
						else
							Result[1] = ' ';

						if(Head->RightChild)
							Result[2] = Head->RightChild->Value;
						else
							Result[2] = ' ';
						bFoundPlace = true;
					}
					else if (Head->RightChild->Value == Character)
					{
						Head = Head->RightChild;
						if(Head->LeftChild)
							Result[1] = Head->LeftChild->Value;
						else
							Result[1] = ' ';

						if(Head->RightChild)
							Result[2] = Head->RightChild->Value;
						else
							Result[2] = ' ';
						bFoundPlace = true;
					}
				}
				else if (!Head->LeftChild && Head->RightChild)
				{
					if (Head->RightChild->Value != Character)
					{
						if(Character < Head->Value)
							Head = Head->LeftChild;
						else
							Head = Head->RightChild;
					}
					else if(Head->RightChild->Value == Character)
					{
						Head = Head->RightChild;
						if(Head->LeftChild)
							Result[1] = Head->LeftChild->Value;
						else
							Result[1] = ' ';

						if(Head->RightChild)
							Result[2] = Head->RightChild->Value;
						else
							Result[2] = ' ';
						bFoundPlace = true;
					}
				}
				else if (Head->LeftChild && !Head->RightChild)
				{
					if (Head->LeftChild->Value != Character)
					{
						if(Character < Head->Value)
							Head = Head->LeftChild;
						else
							Head = Head->RightChild;
					}
					else if(Head->LeftChild->Value == Character)
					{
						Head = Head->LeftChild;
						if(Head->LeftChild)
							Result[1] = Head->LeftChild->Value;
						else
							Result[1] = ' ';

						if(Head->RightChild)
							Result[2] = Head->RightChild->Value;
						else
							Result[2] = ' ';
						bFoundPlace = true;
					}
				}
				else
				{
					bFoundPlace = true;
				}
			}
		}
		return Result;
	}
	return TArray<char>{' ', ' ', ' '};
}
