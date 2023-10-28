// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ALGLAB2_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	///
	/// Danylo Panel Variables
	///
	UPROPERTY(meta=(BindWidget))
	UButton* Lab6DButton;

public:
	///
	/// Sorting Functions
	///
	void SelectionSort(TArray<int>& Array);

	void ShellSort(TArray<int>& Array);

	void QuickSort(TArray<int>& Array, int Low, int High);

	void MergeSort(TArray<int>& Array, int Begin, int End);

	void CountingSort(TArray<int>& Array);

	///
	/// Helping Functions
	///
	int Partition(TArray<int>& Array, int Low, int High);

	void Merge(TArray<int>& Array, int const Left, int const Mid, int const Right);
	
	///
	/// Danylo Panel Functions
	///
	UFUNCTION(BlueprintCallable)
	void ProcessLab6D();
};
