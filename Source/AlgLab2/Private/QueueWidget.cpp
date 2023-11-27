// Fill out your copyright notice in the Description page of Project Settings.


#include "QueueWidget.h"


void UQueueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BSetActive->OnClicked.AddDynamic(this, &UQueueWidget::SetWidgetActive);
	StandardColor = BSetActive->BackgroundColor;
}

void UQueueWidget::Setup(FString Name, int WidgetIndex, FString Elements)
{

	TQueueName->SetText(FText::FromString(Name));
	WIndex = WidgetIndex;
	
	char* Elem = TCHAR_TO_ANSI(*Elements);
	PriorityQueue = NewObject<UMyAwesomeQueue>();
	PriorityQueue->Construct(Elem);
}

void UQueueWidget::Setup(FString Name, int WidgetIndex, const UMyAwesomeQueue* First, const UMyAwesomeQueue* Second)
{
	TQueueName->SetText(FText::FromString(Name));
	WIndex = WidgetIndex;

	PriorityQueue = NewObject<UMyAwesomeQueue>();
	PriorityQueue->CopyConstruct(*First);
	
	for(const FQElement* Runner = const_cast<UMyAwesomeQueue*>(Second)->GetStart(); Runner != nullptr; Runner = Runner->PNext)
	{
		PriorityQueue->Push(Runner);
	}
	
}

int UQueueWidget::GetWidgetIndex()
{
	return WIndex;
}

bool UQueueWidget::IsCheckedState()
{
	return IsChecked->IsChecked();
}

void UQueueWidget::SetWidgetActive()
{
	Activated.Execute(WIndex);
}

void UQueueWidget::Activate()
{
	BSetActive->SetBackgroundColor(FLinearColor::Blue);
}

void UQueueWidget::Deactivate()
{
	BSetActive->SetBackgroundColor(StandardColor);
}

int UQueueWidget::GetNumOfElements()
{
	return PriorityQueue->GetNumOfElements();
}

FString UQueueWidget::GetMin()
{
	char El = PriorityQueue->GetFirst();
	return FString(&El);
}

FString UQueueWidget::GetMax()
{
	char El = PriorityQueue->Peek();
	return FString(&El);
}

FString UQueueWidget::GetAllElements()
{
	char* all = PriorityQueue->GetAllElements();
	FString ret(all);
	delete [] all;
	return ret;
	
}

int UQueueWidget::FindIndexByElement(FString Element)
{
	char* Elem = TCHAR_TO_ANSI(*Element);
	return PriorityQueue->GetIndexOfElement(*Elem);
}

FString UQueueWidget::GetThirdFS()
{
	if(PriorityQueue->GetNumOfElements() >= 3)
	{
		FQElement* Runner = PriorityQueue->GetStart();
		for(int i = 0; i < 2; i++)
		{
			Runner = Runner->PNext;
		}
		char Value = Runner->QValue;
		return FString(&Value);
	}
	return FString("NaN");
}

FString UQueueWidget::GetSecondFE()
{
	if(PriorityQueue->GetNumOfElements() >= 2)
	{
		FQElement* Runner = PriorityQueue->GetEnd();
		Runner = Runner->PPrev;
		char Value = Runner->QValue;
		return FString(&Value);
	}
	return FString("NaN");
}

void UQueueWidget::AddElement(FString Element)
{
	char* Elem = TCHAR_TO_ANSI(*Element);
	PriorityQueue->Push(*Elem);
}

UMyAwesomeQueue* UQueueWidget::GetPriorityQueue()
{
	return PriorityQueue;
}
