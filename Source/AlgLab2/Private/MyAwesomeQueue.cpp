// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAwesomeQueue.h"

void UMyAwesomeQueue::Construct(char* Elements)
{
	Start = nullptr;
	End = nullptr;
	NumOfElements = 0;

	for(char* c = Elements; *c != '\0'; c++)
	{
		Push(*c);
	}
}

void UMyAwesomeQueue::CopyConstruct(const UMyAwesomeQueue& OtherQueue)
{
	this->NumOfElements = 0;
	this->Start = nullptr;
	this->End = nullptr;
	
	for(FQElement* Runner = OtherQueue.End; Runner != nullptr; Runner = Runner->PPrev)
	{
		this->Push(Runner);
	}
}

void UMyAwesomeQueue::MoveConstruct(UMyAwesomeQueue&& OtherQueue) noexcept
{
	this->NumOfElements = OtherQueue.NumOfElements;
	this->Start = OtherQueue.Start;
	this->End = OtherQueue.End;

	OtherQueue.NumOfElements = 0;
	OtherQueue.Start = nullptr;
	OtherQueue.End = nullptr;
	
}

void UMyAwesomeQueue::Push(char Element)
{
	NumOfElements++;
	FQElement* NewElement = new FQElement;
	NewElement->QValue = Element;
	NewElement->PNext = nullptr;
	NewElement->PPrev = nullptr;

	if(Start == nullptr)
	{
		Start = NewElement;
		End = NewElement;
		return;
	}
	
	FQElement* PrevRunner = nullptr;
	for(FQElement* Runner = Start; Runner != nullptr; Runner = Runner->PNext)
	{
		if(NewElement->QValue <= Runner->QValue)
		{
			if(Runner->PPrev == nullptr)
			{
				Runner->PPrev = NewElement;
				NewElement->PNext = Runner;
				Start = NewElement;
				return;
			}

			NewElement->PPrev = Runner->PPrev;
			Runner->PPrev->PNext = NewElement;
			Runner->PPrev = NewElement;
			NewElement->PNext = Runner;
			return;
		}
		PrevRunner = Runner;
	}

	PrevRunner->PNext = NewElement;
	NewElement->PPrev = PrevRunner;
	End = NewElement;
}

void UMyAwesomeQueue::Push(FQElement const* const& Element)
{
	NumOfElements++;
	FQElement* NewElement = new FQElement;
	NewElement->QValue = Element->QValue;
	NewElement->PNext = nullptr;
	NewElement->PPrev = nullptr;

	if(Start == nullptr)
	{
		Start = NewElement;
		End = NewElement;
		return;
	}
	
	FQElement* PrevRunner = nullptr;
	for(FQElement* Runner = Start; Runner != nullptr; Runner = Runner->PNext)
	{
		if(NewElement->QValue <= Runner->QValue)
		{
			if(Runner->PPrev == nullptr)
			{
				Runner->PPrev = NewElement;
				NewElement->PNext = Runner;
				Start = NewElement;
				return;
			}

			NewElement->PPrev = Runner->PPrev;
			Runner->PPrev->PNext = NewElement;
			Runner->PPrev = NewElement;
			NewElement->PNext = Runner;
			return;
		}
		PrevRunner = Runner;
	}

	PrevRunner->PNext = NewElement;
	NewElement->PPrev = PrevRunner;
	End = NewElement;
	
}

char UMyAwesomeQueue::Pop()
{
	char Ret = ' ';
	
	if(End != nullptr)
	{
		Ret = End->QValue;
		End = End->PPrev;
		delete End->PNext;
		End->PNext = nullptr;
		NumOfElements--;
	}
	
	return Ret;
}

char UMyAwesomeQueue::Peek()
{
	char Ret = ' ';
	
	if(End != nullptr)
	{
		Ret = End->QValue;
	}
	
	return Ret;
	
}

char UMyAwesomeQueue::GetElementByIndex(int Index)
{
	FQElement* Wanted = Start;
	if(Index >= NumOfElements)
	{
		return ' ';
	}
	
	for(int i = 0; i < Index; i++)
	{
		Wanted = Wanted->PNext;
	}

	return Wanted->QValue;
}

int UMyAwesomeQueue::GetIndexOfElement(char Element)
{
	int Position = 1;
	for(FQElement* Runner = Start; Runner != nullptr; Runner = Runner->PNext, Position++)
	{
		if(Runner->QValue == Element)
		{
			return Position;
		}
	}
	
	return -1;
}

int UMyAwesomeQueue::GetNumOfElements()
{
	return NumOfElements;
}

char UMyAwesomeQueue::GetFirst()
{
	return Start->QValue;
}

char* UMyAwesomeQueue::GetAllElements()
{
	char* arr = new char[NumOfElements+1];

	FQElement* Runner = Start;
	for(int i = 0; i < NumOfElements; i++)
	{
		arr[i] = Runner->QValue;
		Runner = Runner->PNext;
	}

	arr[NumOfElements] = '\0';
	return arr;
}

FQElement* UMyAwesomeQueue::GetStart()
{
	return Start;
}

FQElement* UMyAwesomeQueue::GetEnd()
{
	return End;
}

