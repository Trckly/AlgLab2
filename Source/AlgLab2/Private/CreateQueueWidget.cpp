// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateQueueWidget.h"

void UCreateQueueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!BExit->OnClicked.IsBound())
	{
		BExit->OnClicked.AddDynamic(this, &UCreateQueueWidget::Exit);
	}

	if(!BCreate->OnClicked.IsBound())
	{
		BCreate->OnClicked.AddDynamic(this, &UCreateQueueWidget::Create);
	}
}

void UCreateQueueWidget::Exit()
{
	DeleteWidget.Execute();
}

void UCreateQueueWidget::Create()
{
	CreateQueue.Execute(InputName->GetText().ToString(), UserInput->GetText().ToString());
}
