// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "CreateQueueWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE(FDeleteWidget);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FCreateQueue, FString, QueueName, FString, QueueElements);

/**
 * 
 */
UCLASS()
class ALGLAB2_API UCreateQueueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UEditableText* UserInput;
	
	UPROPERTY(meta=(BindWidget))
	UEditableText* InputName;
	
	UPROPERTY(meta=(BindWidget))
	UButton* BExit;
	
	UPROPERTY(meta=(BindWidget))
	UButton* BCreate;

	FDeleteWidget DeleteWidget;
	FCreateQueue CreateQueue;
	
	UFUNCTION()
	void Exit();

	UFUNCTION()
	void Create();
};
