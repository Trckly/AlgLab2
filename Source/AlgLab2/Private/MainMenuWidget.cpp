// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/UniformGridSlot.h"
#include "Kismet/KismetMathLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Array6D.SetNum(7);

	PushButton->OnClicked.AddDynamic(this, &UMainMenuWidget::PushToPriorityQueue);

	AppendToButton->OnClicked.AddDynamic(this, &UMainMenuWidget::AppendToPriorityQueue);

	ShowQueueButton->OnClicked.AddDynamic(this, &UMainMenuWidget::ShowQueue);

	RememberButton->OnClicked.AddDynamic(this, &UMainMenuWidget::Remember);

	DisableOutPanels();
}

TArray<int> UMainMenuWidget::SelectionSort(TArray<int> Array)
{
	int MinIdx, N = Array.Num();
 
	// One by one move boundary of
	// unsorted subarray
	for (int i = 0; i < N - 1; i++)
	{
		// Find the minimum element in
		// unsorted array
		MinIdx = i;
		for (int j = i + 1; j < N; j++) {
			if (Array[j] < Array[MinIdx])
				MinIdx = j;
		}
 
		// Swap the found minimum element
		// with the first element
		if (MinIdx != i)
			Swap(Array[MinIdx], Array[i]);
	}
	return Array;
}

TArray<int> UMainMenuWidget::ShellSort(TArray<int> Array)
{
	int N = Array.Num();
	
	for (int Gap = N / 2; Gap > 0; Gap /= 2)
	{
		for (int i = Gap; i < N; ++i)
		{
			int Temp = Array[i];

			int j;
			for(j = i; j >= Gap && Array[j-Gap] < Temp; j -= Gap)
				Array[j] = Array[j-Gap];

			Array[j] = Temp;
		}
	}
	return Array;
}

void UMainMenuWidget::QuickSort(TArray<int>& Array, int Low, int High)
{
	if(Low < High)
	{
		int Pi = Partition(Array, Low, High);
		
		QuickSort(Array, Low, Pi - 1);
		QuickSort(Array, Pi + 1, High);
	}
}

void UMainMenuWidget::MergeSort(TArray<int>& Array, int Begin, int End)
{
	if (Begin >= End)
		return;
 
	int Mid = Begin + (End - Begin) / 2;
	MergeSort(Array, Begin, Mid);
	MergeSort(Array, Mid + 1, End);
	Merge(Array, Begin, Mid, End);
}


TArray<int> UMainMenuWidget::CountingSort(const TArray<int>& Array)
{
	const int N = Array.Num();

	int Max = 0, Min = 0;
 
	for (int i = 0; i < N; i++)
	{
		Max = FMath::Max(Max, Array[i]);
		Min = FMath::Min(Min, Array[i]);
	}
	
	// Initializing countArray[] with 0
	TArray<int> CountArray;
	CountArray.SetNumZeroed(Max - Min + 1, false);
 
	// Mapping each element of inputArray[] as an index
	// of countArray[] array
	for (int i = 0; i < N; i++)
		CountArray[Array[i] - Min]++;
	
	TArray<int> OutputArray;
	OutputArray.SetNum(N, false);
	
	int k = 0;

	for (int j = Min; j <= Max; ++j)
	{
		for (int i = 0; i < CountArray[j - Min]; i++)
		{
			OutputArray[k++] = j;
		}
	}
	return OutputArray;
}

bool UMainMenuWidget::IsSorted(const TArray<int>& Array, const FString& SortMethod, const int& Size)
{
	for (int i = 1; i < Array.Num(); ++i)
	{
		if(Array[i] < Array[i-1])
		{
			ErrorTextBlock->SetText(FText::FromString(SortMethod + ", " + FString::FormatAsNumber(Size)));
			return false;
		}
	}
	return true;
}

int UMainMenuWidget::Partition(TArray<int>& Array, int Low, int High)
{
	int Pivot = Array[High];

	int i = (Low - 1);

	for (int j = Low; j <= High - 1; ++j)
	{
		if(Array[j] > Pivot)
		{
			++i;
			Swap(Array[i], Array[j]);
		}
	}
	Swap(Array[i + 1], Array[High]);

	return (i + 1);
}

void UMainMenuWidget::Merge(TArray<int>& Array, int const Left, int const Mid, int const Right)
{
	int const SubArrayOne = Mid - Left + 1;
	int const SubArrayTwo = Right - Mid;
 
	// Create temp arrays
	auto *LeftArray = new int[SubArrayOne],
			*RightArray = new int[SubArrayTwo];
 
	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < SubArrayOne; i++)
		LeftArray[i] = Array[Left + i];
	for (auto j = 0; j < SubArrayTwo; j++)
		RightArray[j] = Array[Mid + 1 + j];
	
	auto IndexOfSubArrayOne = 0, IndexOfSubArrayTwo = 0;
	int IndexOfMergedArray = Left;
 
	// Merge the temp arrays back into array[left..right]
	while (IndexOfSubArrayOne < SubArrayOne && IndexOfSubArrayTwo < SubArrayTwo)
	{
		if (LeftArray[IndexOfSubArrayOne] >= RightArray[IndexOfSubArrayTwo])
		{
			Array[IndexOfMergedArray] = LeftArray[IndexOfSubArrayOne];
			IndexOfSubArrayOne++;
		}
		else
		{
			Array[IndexOfMergedArray] = RightArray[IndexOfSubArrayTwo];
			IndexOfSubArrayTwo++;
		}
		IndexOfMergedArray++;
	}
 
	// Copy the remaining elements of
	// left[], if there are any
	while (IndexOfSubArrayOne < SubArrayOne)
	{
		Array[IndexOfMergedArray] = LeftArray[IndexOfSubArrayOne];
		IndexOfSubArrayOne++;
		IndexOfMergedArray++;
	}
 
	// Copy the remaining elements of
	// right[], if there are any
	while (IndexOfSubArrayTwo < SubArrayTwo)
	{
		Array[IndexOfMergedArray] = RightArray[IndexOfSubArrayTwo];
		IndexOfSubArrayTwo++;
		IndexOfMergedArray++;
	}
	delete[] LeftArray;
	delete[] RightArray;
}

void UMainMenuWidget::InitArrays()
{
	std::ofstream Fout;
	Fout.open("/Users/bossofthisgym/Documents/Unreal Projects/AlgLab2/Logs/InitialArraysLog.txt", std::ios::trunc);
	Fout << "1024 elements array:\n";
	for(int i = 0; i < 1024; ++i)
	{
		Array6D[0].Push(UKismetMathLibrary::RandomIntegerInRange(-50, 50));
		Fout << Array6D[0][i] << " ";
	}
	Fout << '\n';

	Fout << "\n4096 elements array:\n";
	for(int i = 0; i < 4096; ++i)
	{
		Array6D[1].Push(UKismetMathLibrary::RandomIntegerInRange(-50, 50));
		Fout << Array6D[1][i] << " ";
	}
	Fout << '\n';

	Fout << "\n16384 elements array:\n";
	for(int i = 0; i < 16384; ++i)
	{
		Array6D[2].Push(UKismetMathLibrary::RandomIntegerInRange(-50, 50));
		Fout << Array6D[2][i] << " ";
	}
	Fout << '\n';

	Fout << "\n65536 elements array:\n";
	for(int i = 0; i < 65536; ++i)
	{
		Array6D[3].Push(UKismetMathLibrary::RandomIntegerInRange(-50, 50));
		Fout << Array6D[3][i] << " ";
	}
	Fout << '\n';

	Fout << "\n262144 elements array:\n";
	for(int i = 0; i < 262144; ++i)
	{
		Array6D[4].Push(UKismetMathLibrary::RandomIntegerInRange(-50, 50));
		Fout << Array6D[4][i] << " ";
	}
	Fout << '\n';

	Fout << "\n1048576 elements array:\n";
	for(int i = 0; i < 1048576; ++i)
	{
		Array6D[5].Push(UKismetMathLibrary::RandomIntegerInRange(-50, 50));
		Fout << Array6D[5][i] << " ";
	}
	Fout << '\n';

	Fout << "\n4194304 elements array:\n";
	for(int i = 0; i < 4194304; ++i)
	{
		Array6D[6].Push(UKismetMathLibrary::RandomIntegerInRange(-50, 50));
		Fout << Array6D[6][i] << " ";
	}
	Fout << '\n';
	Fout.close();
}

TArray<char> UMainMenuWidget::GetEnteredChars(bool& Successful)
{
	FString InitialText = ValueLineEdit->GetText().ToString();
	TArray<char> Result;
	for (const TCHAR& Char : InitialText)
	{
		if (FChar::IsAlnum(Char) && !FChar::IsDigit(Char))
		{
			Result.Push(Char);
		}
	}
	if(Result.Num() == 0)
	{
		ErrorText->SetText(FText::FromString(TEXT("Invalid values in value member!")));
		Successful = false;
	}
	else
	{
		Successful = true;
	}
	return Result;
}

int UMainMenuWidget::GetEnteredPriority()
{
	return PriorityComboBox->GetSelectedIndex();
}

int UMainMenuWidget::Find(char Character)
{
	PriorityQueue TempQueue(Queue);
	for(int i = 0; i < Queue.GetSize(); ++i)
	{
		if(TempQueue.Top() == Character)
			return i;
		TempQueue.Dequeue();
	}
	return -1;
}

char UMainMenuWidget::BeforeMin()
{
	int MinIndex = Find(Queue.GetMin());
	PriorityQueue TempQueue(Queue);
	for(int i = 0; i < MinIndex; ++i)
	{
		if(i == MinIndex-1)
			return TempQueue.Top();
		TempQueue.Dequeue();
	}
	return 0;
}

char UMainMenuWidget::AfterMax()
{
	int MaxIndex = Find(Queue.GetMax());
	PriorityQueue TempQueue(Queue);
	for(int i = 0; i < TempQueue.GetSize(); ++i)
	{
		if(i == MaxIndex+1)
			return TempQueue.Top();
		TempQueue.Dequeue();
	}
	return 0;
}

char UMainMenuWidget::GetThird()
{
	PriorityQueue TempQueue(Queue);
	for (int i = 0; i < 3; ++i)
	{
		if(i == 2)
			return TempQueue.Top();
		TempQueue.Dequeue();
	}
	return 0;
}

char UMainMenuWidget::GetBeforeLast()
{
	PriorityQueue TempQueue(Queue);
	for (int i = 0; i < TempQueue.GetSize(); ++i)
	{
		if(i == TempQueue.GetSize() - 2)
			return TempQueue.Top();
		TempQueue.Dequeue();
	}
	return 0;
}

void UMainMenuWidget::OutputQueue()
{
	if(Queue.GetSize() > 0)
	{
		FString QueueString;
		int Size = Queue.GetSize();
		PriorityQueue Temp = Queue;
		for(int i = 0; i < Size; ++i)
		{
			int TopIndex = Temp.Top();
			if(i != Size-1)
				QueueString += FString::Printf(TEXT("%c(%s) -> "), Temp.ValueAt(TopIndex), *GetPriorityName(Temp.PriorityAt(TopIndex)));
			else
				QueueString += FString::Printf(TEXT("%c(%s)"), Temp.ValueAt(TopIndex), *GetPriorityName(Temp.PriorityAt(TopIndex)));
			Temp.Dequeue();
		}
		MainOutputTextBlock->SetText(FText::FromString(QueueString));
	}

	if(RememberedQueue.GetSize() > 0)
	{
		FString RememberedQueueString;
		PriorityQueue Temp = RememberedQueue;
		int Size = Temp.GetSize();
		for(int i = 0; i < Size; ++i)
		{
			int TopIndex = Temp.Top();
			if(i != Size-1)
				RememberedQueueString += FString::Printf(TEXT("%c(%s) -> "), Temp.ValueAt(TopIndex), *GetPriorityName(Temp.PriorityAt(TopIndex)));
			else
				RememberedQueueString += FString::Printf(TEXT("%c(%s)"), Temp.ValueAt(TopIndex), *GetPriorityName(Temp.PriorityAt(TopIndex)));
			Temp.Dequeue();
		}
		RememberedTextBlock->SetText(FText::FromString(RememberedQueueString));
	}

	if(AppendedQueue.GetSize() > 0)
	{
		FString AppendedQueueString;
		PriorityQueue Temp = AppendedQueue;
		int Size = Temp.GetSize();
		for(int i = 0; i < Size; ++i)
		{
			int TopIndex = Temp.Top();
			if(i != Size-1)
				AppendedQueueString += FString::Printf(TEXT("%c(%s) -> "), Temp.ValueAt(TopIndex), *GetPriorityName(Temp.PriorityAt(TopIndex)));
			else
				AppendedQueueString += FString::Printf(TEXT("%c(%s)"), Temp.ValueAt(TopIndex), *GetPriorityName(Temp.PriorityAt(TopIndex)));
			Temp.Dequeue();
		}
		AppendedTextBlock->SetText(FText::FromString(AppendedQueueString));
	}
}

FString UMainMenuWidget::GetPriorityName(int Prio)
{
	switch (Prio)
	{
	case PriorityQueue::EPriorityTypes::High:
		return TEXT("High");
	case PriorityQueue::EPriorityTypes::Highest:
		return TEXT("Highest");
	case PriorityQueue::EPriorityTypes::AboveNormal:
		return TEXT("AboveNormal");
	case PriorityQueue::EPriorityTypes::Normal:
		return TEXT("Normal");
	case PriorityQueue::EPriorityTypes::BelowNormal:
		return TEXT("BelowNormal");
	case PriorityQueue::EPriorityTypes::Low:
		return TEXT("Low");
	case PriorityQueue::EPriorityTypes::Lowest:
		return TEXT("Lowest");
	default:
		return TEXT("Undefined");
	}
}

void UMainMenuWidget::ProcessLab6D()
{
	TArray<int> Result;
	InitArrays();

	FString SortType = TEXT("Selection");
	for (int i = 0; i < 5; ++i)
	{
		auto StartTime = std::chrono::high_resolution_clock::now();
		Result = SelectionSort(Array6D[i]);
		auto StopTime = std::chrono::high_resolution_clock::now(); 
		std::chrono::microseconds ExcecutionTime = std::chrono::duration_cast<std::chrono::microseconds>(StopTime - StartTime);
		
		UTextBlock* NewCell = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		NewCell->SetText(FText::FromString(FString::FormatAsNumber(ExcecutionTime.count())));
		Table6D->AddChildToUniformGrid(NewCell, ESortTypes::Selection, i + 1);
	}

	SortType = TEXT("Shell");
	for (int i = 0; i < 7; ++i)
	{
		auto StartTime = std::chrono::high_resolution_clock::now();
		Result = ShellSort(Array6D[i]);
		auto StopTime = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds ExcecutionTime = std::chrono::duration_cast<std::chrono::microseconds>(StopTime - StartTime);
		
		UTextBlock* NewCell = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		NewCell->SetText(FText::FromString(FString::FormatAsNumber(ExcecutionTime.count())));
		Table6D->AddChildToUniformGrid(NewCell, ESortTypes::Shell, i + 1);
	}

	SortType = TEXT("Quick");
	for (int i = 0; i < 7; ++i)
	{
		Result = Array6D[i];
		auto StartTime = std::chrono::high_resolution_clock::now();
		QuickSort(Result, 0, Result.Num()-1);
		auto StopTime = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds ExcecutionTime = std::chrono::duration_cast<std::chrono::microseconds>(StopTime - StartTime);
		
		UTextBlock* NewCell = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		NewCell->SetText(FText::FromString(FString::FormatAsNumber(ExcecutionTime.count())));
		Table6D->AddChildToUniformGrid(NewCell, ESortTypes::Quick, i + 1);
	}

	SortType = TEXT("Merge");
	for (int i = 0; i < 7; ++i)
	{
		Result = Array6D[i];
		auto StartTime = std::chrono::high_resolution_clock::now();
		MergeSort(Result, 0, Result.Num()-1);
		auto StopTime = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds ExcecutionTime = std::chrono::duration_cast<std::chrono::microseconds>(StopTime - StartTime);
		
		UTextBlock* NewCell = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		NewCell->SetText(FText::FromString(FString::FormatAsNumber(ExcecutionTime.count())));
		Table6D->AddChildToUniformGrid(NewCell, ESortTypes::Merg, i + 1);
	}

	SortType = TEXT("Counting");
	for (int i = 0; i < 7; ++i)
	{
		auto StartTime = std::chrono::high_resolution_clock::now();
		Result = CountingSort(Array6D[i]);
		auto StopTime = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds ExcecutionTime = std::chrono::duration_cast<std::chrono::microseconds>(StopTime - StartTime);
		
		UTextBlock* NewCell = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		NewCell->SetText(FText::FromString(FString::FormatAsNumber(ExcecutionTime.count())));
		Table6D->AddChildToUniformGrid(NewCell, ESortTypes::Counting, i + 1);
	}
}

void UMainMenuWidget::DisableOutPanels()
{
	OutputPanel->SetVisibility(ESlateVisibility::Hidden);
	StatsPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenuWidget::EnableOutPanels()
{
	OutputPanel->SetVisibility(ESlateVisibility::Visible);
	StatsPanel->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuWidget::PushToPriorityQueue()
{
	//Cosmetic function /////////////////////////////////////////
	if(OutputPanel->GetVisibility() == ESlateVisibility::Visible)
	{
		DisableOutPanels();
	}
	/////////////////////////////////////////////////////////////

	bool bSuccessfulConversion;
	TArray<char> Values = GetEnteredChars(bSuccessfulConversion);
	if(bSuccessfulConversion)
	{
		int Priority = GetEnteredPriority();
		for (const char& Value : Values)
		{
			Queue.Enqueue(Value, Priority);
		}
	}
}

void UMainMenuWidget::AppendToPriorityQueue()
{
	AppendedQueue = RememberedQueue + Queue;
	OutputQueue();
}

void UMainMenuWidget::ShowQueue()
{
	if(Queue.GetSize() > 0)
	{
		EnableOutPanels();
	
		SizeTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Size: %i"), Queue.GetSize())));

		OutputQueue();

	

		// MinMaxTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Min: %c; Max: %c"), Queue.GetMin(),
		// 	Queue.GetMax())));
	}
}

void UMainMenuWidget::Remember()
{
	RememberedQueue = std::move(Queue);
	OutputQueue();
}

void UMainMenuWidget::ProcessLab7D()
{
	// PriorityQueue PQueue;
}

void UMainMenuWidget::Populate()
{
	FString InsertedText = PopulateTreeTextBox->GetText().ToString();
	InsertedText.RemoveSpacesInline();
	BinTreeGrid->ClearChildren();
	EmptySlotsText();
	EmptyChildren();
	Tree.Empty();
	RowCount = InsertedText.Len() * 2;
	ColumnCount = InsertedText.Len() * 2;
	InitSlotsText();
	InitGrid();
	for(auto Character : InsertedText)
	{
		PrintTreeSymbol(Character);
		Tree.Push(Character);
	}
}

void UMainMenuWidget::PrintTreeSymbol(char Character)
{
	int RowIndex = 0;
	int ColumnIndex = ColumnCount/2;
	FString CurrentChar;
	if(SlotsText[RowIndex][ColumnIndex]->GetText().ToString().Len() == 0)
	{
		SlotsText[RowIndex][ColumnIndex]->SetText(FText::FromString(FString::Printf(TEXT("%c"),Character)));
	}
	else
	{
		bool bFoundPlace = false;
		while(!bFoundPlace)
		{
			char PrevChar = SlotsText[RowIndex][ColumnIndex]->GetText().ToString()[0];
			if(Character < PrevChar)
			{
				RowIndex++;
				ColumnIndex--;
				CurrentChar = SlotsText[RowIndex][ColumnIndex]->GetText().ToString();
				if(CurrentChar.Len() == 0)
				{
					SlotsText[RowIndex][ColumnIndex]->SetText(FText::FromString(FString::Printf(TEXT("%c"),Character)));
					bFoundPlace = true;
				}
				else
					continue;
			}
			else
			{
				RowIndex++;
				ColumnIndex++;
				CurrentChar = SlotsText[RowIndex][ColumnIndex]->GetText().ToString();
				if(CurrentChar.Len() == 0)
				{
					SlotsText[RowIndex][ColumnIndex]->SetText(FText::FromString(FString::Printf(TEXT("%c"),Character)));
					bFoundPlace = true;
				}
				else
					continue;
			}
		}
	}
}

void UMainMenuWidget::Find()
{
	FString CharToFind = FindTextBox->GetText().ToString();
	bool bFound = Tree.Find(static_cast<char>(CharToFind[0]));
	if(bFound)
		FoundTextBlock->SetText(FText::FromString(TEXT("Exists")));
	else
		FoundTextBlock->SetText(FText::FromString(TEXT("Absent")));
}

void UMainMenuWidget::Traverse()
{
	TArray<char> Result = Tree.Traverse();
	FString ResultStr;
	for (auto Char : Result)
	{
		ResultStr += FString::Printf(TEXT("%c "), Char);
	}
	TraversedTextBlock->SetText(FText::FromString(ResultStr));
}

void UMainMenuWidget::ParentAndChildren()
{
	FString Input = FindTextBox->GetText().ToString();
	TArray<char> Result = Tree.GetParentAndChildren(Input[0]);
	FString Output;
	Output += FString::Printf(TEXT("Parent: %c\n"), Result[0]);
	Output += FString::Printf(TEXT("Left Child: %c\n"), Result[1]);
	Output += FString::Printf(TEXT("Right Child: %c"), Result[2]);
	
	IncestTextBlock->SetText(FText::FromString(Output));
}


void UMainMenuWidget::CastToInt()
{
	for (int i = 0; i < SlotsText.Num(); ++i)
	{
		for (int j = 0; j < SlotsText[i].Num(); ++j)
		{
			FString Char = SlotsText[i][j]->GetText().ToString();
			if(Char.Len() > 0)
			{
				int CastedChar = static_cast<int>(Char[0]);
				SlotsText[i][j]->SetText(FText::FromString(FString::FromInt(CastedChar)));
			}
		}
	}
}

void UMainMenuWidget::CastToChar()
{
	for (int i = 0; i < SlotsText.Num(); ++i)
	{
		for (int j = 0; j < SlotsText[i].Num(); ++j)
		{
			FString Char = SlotsText[i][j]->GetText().ToString();
			if(Char.Len() > 0)
			{
				int CastedChar = FCString::Atoi(*Char);
				char ValidChar = static_cast<char>(CastedChar);
				SlotsText[i][j]->SetText(FText::FromString(FString::Printf(TEXT("%c"), ValidChar)));
			}
		}
	}
}

void UMainMenuWidget::EmptySlotsText()
{
	for (int i = 0; i < SlotsText.Num(); ++i)
	{
		SlotsText[i].Empty();
	}
	SlotsText.Empty();
}

void UMainMenuWidget::InitSlotsText()
{
	SlotsText.SetNum(RowCount);
	for (int i = 0; i < RowCount; ++i)
	{
		SlotsText[i].SetNum(ColumnCount);
		for (int j = 0; j < ColumnCount; ++j)
		{
			SlotsText[i][j] = NewObject<UTextBlock>(this);
			SlotsText[i][j]->SetText(FText::FromString(TEXT("")));
		}
	}
}

void UMainMenuWidget::InitGrid()
{
	for(int i = 0; i < RowCount; ++i)
	{
		for (int j = 0; j < ColumnCount; ++j)
		{
			BinTreeGrid->AddChildToUniformGrid(SlotsText[i][j], i, j);
		}
	}
}

void UMainMenuWidget::EmptyChildren()
{
	for (int i = 0; i < GridChildren.Num(); ++i)
	{
		GridChildren[i].Empty();
	}
	GridChildren.Empty();
}
