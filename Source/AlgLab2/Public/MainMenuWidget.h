// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <fstream>
#include <chrono>
#include "PriorityQueue.h"
#include "CoreMinimal.h"
#include "BinTree.h"
#include "CreateQueueWidget.h"
#include "QueueWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableText.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/ScrollBox.h"
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

	PriorityQueue AwesomeQueue;

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

	UPROPERTY(meta=(BindWidget))
	UTextBlock* IncestTextBlock;

	int RowCount;
	int ColumnCount;
	
	TArray<TArray<UUniformGridSlot*>> GridChildren;
	
	TArray<TArray<UTextBlock*>> SlotsText;

	// Lab 9 D Variables
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ArrayOutputText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ErrorOutput;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* MiddleArithmeticText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* FoundIndex;

	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* ArrayLengthBox;
	
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* SearchBox;

	int ComparisonCount;

	UPROPERTY()
	TArray<int> ArrayToSearchIn;

	// Lab 10 D Variables
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ErrorOutput_1;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UMultiLineEditableTextBox* LineInputText;

	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* WordSearchBox;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* WordSearchOutput;

	// Lab 11 D Variables
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UMultiLineEditableTextBox* LineInputText_1;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UMultiLineEditableTextBox* LineInputText_2;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* WordSearchOutput_1;

	
	///
	/// Andrii Panel Variables ////////////////////////////////////////////////////////////////////////////////////////
	///
 
	///
	/// Lab 6
	///

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ErrorTextBlockA;

	UPROPERTY(meta=(BindWidget))
	UUniformGridPanel* Table6A;

	TArray<TArray<int>> Array6A;
	
	///
	/// Lab 7
	///

	UPROPERTY(meta=(BindWidget))
	UButton* BCreateQueue;

	UPROPERTY(meta=(BindWidget))
	UButton* BFindElement;

	UPROPERTY(meta=(BindWidget))
	UButton* BAddElement;

	UPROPERTY(meta=(BindWidget))
	UButton* BMergeQueue;

	UPROPERTY(meta=(BindWidget))
	UScrollBox* SQueues;

	UPROPERTY(meta=(BindWidget))
	UEditableText* ElementToFind;

	UPROPERTY(meta=(BindWidget))
	UEditableText* ElementToAdd;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TPosition;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TElements;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TQuantity;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TMin;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TMax;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TThirdFS;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TSecondFE;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UQueueWidget> QueueWidgetClass;

	UPROPERTY()
	TMap<int, UQueueWidget*> QueueWidgets;

	int ActiveWidget;

	int NewIndex;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UCreateQueueWidget> CreateQueueWidgetClass;

	UPROPERTY()
	UCreateQueueWidget* CreateQueueWidget;
	
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

	UFUNCTION(BlueprintCallable)
	void ParentAndChildren();

	///
	/// Lab 9 D
	///
	UFUNCTION(BlueprintCallable)
	void Search();

	UFUNCTION(BlueprintCallable)
	void Create();

	int Requirement9D();

	void GenerateArrayValues(int Length);

	int BinarySearch(int InSearch);

	///
	/// Lab 10 D
	///
	UFUNCTION(BlueprintCallable)
	void SearchWord();

	int PatternSearchKMP(const FString& Pat, const FString& Txt);

	void DeleteNumbersInString(FString& String);

	void BuildLPSArray(const FString& Pat, int M, TArray<int>& Lps);

	///
	/// Lab 11 D
	///
	UFUNCTION(BlueprintCallable)
	void Search11D();
	
	void BoyerMooreSearch(FString Txt, FString Pat);
	
	void BadCharHeuristic(const FString& Str, TArray<int>& BadChar);	
	
	FString FindRequiredWord();

	bool IsVowel(char Ch);
	
	///
	/// Andrii Panel Functions ////////////////////////////////////////////////////////////////////////////////////////
	///

	///
	/// Lab 6
	/// 
	UFUNCTION(BlueprintCallable)
	void ProcessLab6A();

	void SelectionSortA(TArray<int>& Array);

	void ShellSortA(TArray<int>& Array);

	void QuickSortA(TArray<int>& Array, int Begin, int End);

	void MergeSortA(TArray<int>& Array, int Begin, int End);

	TArray<int> CountingSortA(const TArray<int>& Array);

	bool IsSortedA(const TArray<int>& Array);
	
	int PartitionA(TArray<int>& Array, int Begin, int End);

	void SwapElementsA(TArray<int>& Array, int First, int Second);

	void MergeA(TArray<int>& Array, int const Left, int const Mid, int const Right);

	void InitArraysA();
	

	///
	/// Lab 7
	///

	UFUNCTION(BlueprintCallable)
	void StartASeven();

	UFUNCTION()
	void CreateQueueCreator();

	UFUNCTION()
	void CreateQueue(FString Name, FString Elements);

	UFUNCTION()
	void MergeQueues();

	UFUNCTION()
	void FindElementIndex();

	UFUNCTION()
	void AddElement();

	UFUNCTION()
	void RemoveWidgetCreator();

	UFUNCTION()
	void SetActiveWidget(int WidgetIndex);

	UFUNCTION()
	void ShowStats(UQueueWidget* Queue);
};
