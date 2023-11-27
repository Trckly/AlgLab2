// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyAwesomeQueue.generated.h"

/**
 * 
 */

typedef struct FQElement
{
	char QValue;
	FQElement* PNext;
	FQElement* PPrev;
} FQElement;

UCLASS()
class ALGLAB2_API UMyAwesomeQueue : public UObject
{
	GENERATED_BODY()

public:

	void Construct(char* Elements);
	
	void CopyConstruct(const UMyAwesomeQueue& OtherQueue);
	
	void MoveConstruct(UMyAwesomeQueue&& OtherQueue) noexcept;

	void Push(char Element);
	
	void Push(FQElement const * const & Element);

	char Pop();

	char Peek();

	char GetElementByIndex(int Index);

	int GetIndexOfElement(char Element);

	int GetNumOfElements();

	char GetFirst();

	char* GetAllElements();

	FQElement* GetStart();

	FQElement* GetEnd();

private:

	FQElement* Start;
	FQElement* End;
	
	int NumOfElements;
};
