// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAwesomeQueue.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "QueueWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FActivated, int, WidgetIndex);
/**
 * 
 */
UCLASS()
class ALGLAB2_API UQueueWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	UMyAwesomeQueue* PriorityQueue;

	int WIndex;

	FLinearColor StandardColor;

public:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void Setup(FString Name, int WidgetIndex, FString Elements);
	
	void Setup(FString Name, int WidgetIndex, const UMyAwesomeQueue* First, const UMyAwesomeQueue* Second);
	
	int GetWidgetIndex();

	bool IsCheckedState();
	
	FActivated Activated;

	UFUNCTION()
	void SetWidgetActive();

	UFUNCTION()
	void Activate();

	UFUNCTION()
	void Deactivate();

	int GetNumOfElements();

	FString GetMin();

	FString GetMax();

	FString GetAllElements();

	int FindIndexByElement(FString Element);

	FString GetThirdFS();

	FString GetSecondFE();

	void AddElement(FString Element);
	
	UMyAwesomeQueue* GetPriorityQueue();
	
private:
	UPROPERTY(meta=(BindWidget))
	UButton* BSetActive;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TQueueName;

	UPROPERTY(meta=(BindWidget))
	UCheckBox* IsChecked;

};
