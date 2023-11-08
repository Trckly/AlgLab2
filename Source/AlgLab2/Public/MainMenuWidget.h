// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <fstream>
#include <chrono>
#include "PriorityQueue.h"
#include "CoreMinimal.h"
#include "BinTree.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
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

public:
	enum ESortTypes
	{
		Selection = 1,
		Shell = 2,
		Quick = 3,
		Merg = 4,
		Counting = 5
	};

protected:
	virtual void NativeConstruct() override;
	
	///
	/// Danylo Panel Variables ////////////////////////////////////////////////////////////////////////////////////////
	///

	///
	/// Lab 6
	///
	UPROPERTY(meta=(BindWidget))
	UButton* Lab6DButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ProcessingTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ErrorTextBlock;

	UPROPERTY(meta=(BindWidget))
	UUniformGridPanel* Table6D;

	TArray<TArray<int>> Array6D;

	///
	/// Lab 7
	///

	PriorityQueue Queue;

	PriorityQueue RememberedQueue;

	PriorityQueue AppendedQueue;
	
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* ValueLineEdit;

	UPROPERTY(meta=(BindWidget))
	UComboBoxString* PriorityComboBox;

	UPROPERTY(meta=(BindWidget))
	UButton* PushButton;

	UPROPERTY(meta=(BindWidget))
	UButton* AppendToButton;

	UPROPERTY(meta=(BindWidget))
	UButton* ShowQueueButton;

	UPROPERTY(meta=(BindWidget))
	UButton* RememberButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ErrorText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* SizeTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* MinMaxTextBlock;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ThirdOptionTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* BMinBMaxTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* FindTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* MainOutputTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* RememberedTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* AppendedTextBlock;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* OutputPanel;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* StatsPanel;
	
	bool bValid;

	///
	/// Lab 8
	///
	BinTree Tree;

	UPROPERTY(meta=(BindWidget))
	UUniformGridPanel* BinTreeGrid;

	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* PopulateTreeTextBox;

	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* FindTextBox;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* FoundTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TraversedTextBlock;

	int RowCount;
	int ColumnCount;
	
	TArray<TArray<UUniformGridSlot*>> GridChildren;
	
	TArray<TArray<UTextBlock*>> SlotsText;
	
public:
	///
	/// Sorting Functions /////////////////////////////////////////////////////////////////////////////////////////////
	///
	TArray<int> SelectionSort(TArray<int> Array);

	TArray<int> ShellSort(TArray<int> Array);

	void QuickSort(TArray<int>& Array, int Low, int High);

	void MergeSort(TArray<int>& Array, int Begin, int End);

	TArray<int> CountingSort(const TArray<int>& Array);

	bool IsSorted(const TArray<int>& Array, const FString& SortMethod, const int& Size);

	///
	/// Helping Functions /////////////////////////////////////////////////////////////////////////////////////////////
	///
	int Partition(TArray<int>& Array, int Low, int High);

	void Merge(TArray<int>& Array, int const Left, int const Mid, int const Right);

	void InitArrays();

	TArray<char> GetEnteredChars(bool& Successful);

	int GetEnteredPriority();

	int Find(char Character);

	char BeforeMin();

	char AfterMax();

	char GetThird();

	char GetBeforeLast();

	void OutputQueue();

	FString GetPriorityName(int Prio);

	void EmptySlotsText();

	void InitSlotsText();

	void InitGrid();

	void EmptyChildren();
	
	///
	/// Danylo Panel Functions ////////////////////////////////////////////////////////////////////////////////////////
	///

	///
	/// Lab 6
	/// 
	UFUNCTION(BlueprintCallable)
	void ProcessLab6D();

	/// 
	/// Lab 7
	///
	void DisableOutPanels();

	void EnableOutPanels();
	
	UFUNCTION()
	void PushToPriorityQueue();

	UFUNCTION()
	void AppendToPriorityQueue();

	UFUNCTION()
	void ShowQueue();

	UFUNCTION()
	void Remember();
	
	UFUNCTION(BlueprintCallable)
	void ProcessLab7D();

	/// 
	/// Lab 8
	///
	UFUNCTION(BlueprintCallable)
	void Populate();

	UFUNCTION(BlueprintCallable)
	void CastToInt();

	UFUNCTION(BlueprintCallable)
	void CastToChar();

	void PrintTreeSymbol(char Character);

	UFUNCTION(BlueprintCallable)
	void Find();

	UFUNCTION(BlueprintCallable)
	void Traverse();
};
