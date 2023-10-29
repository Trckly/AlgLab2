// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <fstream>
#include <chrono>
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
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

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ProcessingTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ErrorTextBlock;

	UPROPERTY(meta=(BindWidget))
	UUniformGridPanel* Table6D;

	TArray<int> Array6D_1;

	TArray<int> Array6D_2;

	TArray<int> Array6D_3;

	TArray<int> Array6D_4;

	TArray<int> Array6D_5;

	TArray<int> Array6D_6;

	TArray<int> Array6D_7;

public:
	///
	/// Sorting Functions
	///
	TArray<int> SelectionSort(TArray<int> Array);

	TArray<int> ShellSort(TArray<int> Array);

	void QuickSort(TArray<int>& Array, int Low, int High);

	void MergeSort(TArray<int>& Array, int Begin, int End);

	TArray<int> CountingSort(const TArray<int>& Array);

	bool IsSorted(const TArray<int>& Array, const FString& SortMethod, const int& Size);

	///
	/// Helping Functions
	///
	int Partition(TArray<int>& Array, int Low, int High);

	void Merge(TArray<int>& Array, int const Left, int const Mid, int const Right);

	void InitArrays();
	
	///
	/// Danylo Panel Functions
	///
	UFUNCTION(BlueprintCallable)
	void ProcessLab6D();
};
