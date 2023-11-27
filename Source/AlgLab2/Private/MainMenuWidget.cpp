// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/UniformGridSlot.h"
#include "Kismet/KismetMathLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Array6D.SetNum(7);
	Array6A.SetNum(7);

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
	//Fout.open("/Users/bossofthisgym/Documents/Unreal Projects/AlgLab2/Logs/InitialArraysLog.txt", std::ios::trunc);
	Fout.open("D:\\Algorythms\\AlgLab2\\Content\\Stuff\\InitialArraysLog.txt", std::ios::trunc);
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
	PriorityQueue TempQueue(AwesomeQueue);
	for(int i = 0; i < AwesomeQueue.GetSize(); ++i)
	{
		if(TempQueue.Top() == Character)
			return i;
		TempQueue.Dequeue();
	}
	return -1;
}

char UMainMenuWidget::BeforeMin()
{
	int MinIndex = Find(AwesomeQueue.GetMin());
	PriorityQueue TempQueue(AwesomeQueue);
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
	int MaxIndex = Find(AwesomeQueue.GetMax());
	PriorityQueue TempQueue(AwesomeQueue);
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
	PriorityQueue TempQueue(AwesomeQueue);
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
	PriorityQueue TempQueue(AwesomeQueue);
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
	if(AwesomeQueue.GetSize() > 0)
	{
		FString QueueString;
		int Size = AwesomeQueue.GetSize();
		PriorityQueue Temp = AwesomeQueue;
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
		int PushPriority = GetEnteredPriority();
		for (const char& Value : Values)
		{
			AwesomeQueue.Enqueue(Value, PushPriority);
		}
	}
}

void UMainMenuWidget::AppendToPriorityQueue()
{
	AppendedQueue = RememberedQueue + AwesomeQueue;
	OutputQueue();
}

void UMainMenuWidget::ShowQueue()
{
	if(AwesomeQueue.GetSize() > 0)
	{
		EnableOutPanels();
	
		SizeTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Size: %i"), AwesomeQueue.GetSize())));

		OutputQueue();

	

		// MinMaxTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Min: %c; Max: %c"), Queue.GetMin(),
		// 	Queue.GetMax())));
	}
}

void UMainMenuWidget::Remember()
{
	RememberedQueue = std::move(AwesomeQueue);
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

void UMainMenuWidget::Search()
{
	int Index;
	if(SearchBox->GetText().ToString().IsEmpty())
	{
		Index = BinarySearch(FCString::Atoi(*MiddleArithmeticText->GetText().ToString()));
	}
	else
	{
		Index = BinarySearch(FCString::Atoi(*SearchBox->GetText().ToString()));
	}
	if(Index == -1)
	{
		FoundIndex->SetText(FText::FromString(TEXT("Given element is absent")));
	}
	else
	{
		FoundIndex->SetText(FText::FromString(FString::FromInt(Index)));
	}
	UE_LOG(LogTemp, Warning, TEXT("Comparison count = %i"), ComparisonCount);
}

void UMainMenuWidget::Create()
{
	FString EnteredLengthValue = ArrayLengthBox->GetText().ToString();
	if(!EnteredLengthValue.IsNumeric())
	{
		ErrorOutput->SetText(FText::FromString(TEXT("Make sure you've entered numeric value!")));
	}
	else
	{
		GenerateArrayValues(FCString::Atoi(*EnteredLengthValue));
		
		FString OutputString;
		for (auto Number : ArrayToSearchIn)
		{
			OutputString += FString::FromInt(Number) + " ";
		}
		OutputString.RemoveFromEnd(" ");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *OutputString);

		int MidArithmetic = Requirement9D();

		OutputString.Empty();
		for (auto Number : ArrayToSearchIn)
		{
			OutputString += FString::FromInt(Number) + " ";
		}
		OutputString.RemoveFromEnd(" ");
		if(ArrayToSearchIn.Num() <= 20)
		{
			ArrayOutputText->SetText(FText::FromString(OutputString));
		}
		else
		{
			ArrayOutputText->SetText(FText::FromString(TEXT("Array is too big to display on screen. Look for array in the logs")));
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *OutputString);

		MiddleArithmeticText->SetText(FText::FromString(FString::FromInt(MidArithmetic)));
	}
}

int UMainMenuWidget::Requirement9D()
{
	int MiddleArithmetic, Sum = 0;

	for(const auto & Number : ArrayToSearchIn)
	{
		Sum += Number;
	}
	MiddleArithmetic =  Sum / ArrayToSearchIn.Num();

	for(auto & Number : ArrayToSearchIn)
	{
		if(Number < MiddleArithmetic)
		{
			Number *= 2;
		}
	}
	return MiddleArithmetic;
}

void UMainMenuWidget::GenerateArrayValues(int Length)
{
	if(ArrayToSearchIn.Num() > 0)
	{
		ArrayToSearchIn.Empty();
	}

	ArrayToSearchIn.SetNum(Length);
	for (int i = 0; i < Length; ++i)
	{
		ArrayToSearchIn[i] = UKismetMathLibrary::RandomIntegerInRange(-500, 500);
	}
	
	ArrayToSearchIn.Sort();
}

int UMainMenuWidget::BinarySearch(int InSearch)
{
	ComparisonCount= 0;
	int L = 0, R = ArrayToSearchIn.Num();
	while (L <= R)
	{
		ComparisonCount++;
		int M = L + (R - L) / 2;
		UE_LOG(LogTemp, Warning, TEXT("Middle element: %i. Value: %i"), M, ArrayToSearchIn[M]);
 
		// Check if x is present at mid
		if (ArrayToSearchIn[M] == InSearch)
			return M;
 
		// If x greater, ignore left half
		if (ArrayToSearchIn[M] < InSearch)
		{
			L = M + 1;
			UE_LOG(LogTemp, Warning, TEXT("Search in right half"));
		}
 
		// If x is smaller, ignore right half
		else
		{
			R = M - 1;
			UE_LOG(LogTemp, Warning, TEXT("Search in left half"));
		}
	}
 
	// If we reach here, then element was not present
	return -1;
}

void UMainMenuWidget::SearchWord()
{
	FString EnteredText = LineInputText->GetText().ToString();
	DeleteNumbersInString(EnteredText);

	FString Pattern = WordSearchBox->GetText().ToString();
	if(Pattern.Len() != 0)
	{
		int Index = PatternSearchKMP(Pattern, EnteredText);
		if(Index != -1)
		{
			WordSearchOutput->SetText(FText::FromString(FString::Printf(TEXT("Found at: %i"), Index)));
		}
		else
		{
			WordSearchOutput->SetText(FText::FromString(FString::Printf(TEXT("Pattern does not exist!"))));
		}
	}
}

int UMainMenuWidget::PatternSearchKMP(const FString& Pat, const FString& Txt)
{
	int M = Pat.Len();
	int N = Txt.Len();
 
	// create lps[] that will hold the longest prefix suffix
	// values for pattern
	TArray<int> Lps;
	Lps.SetNum(M);
 
	// Preprocess the pattern (calculate lps[] array)
	BuildLPSArray(Pat, M, Lps);

	FString LpsDebugString = TEXT("Lps = [");
	for(const auto & Number : Lps)
	{
		LpsDebugString += FString::FromInt(Number) + ", ";
	}
	LpsDebugString.RemoveFromEnd(FString(TEXT(", ")));
	LpsDebugString += "]";
	UE_LOG(LogTemp, Warning, TEXT("%s"), *LpsDebugString);
 
	int i = 0; // index for txt[]
	int j = 0; // index for pat[]
	while ((N - i) >= (M - j)) {
		if (Pat[j] == Txt[i]) {
			j++;
			i++;
		}
 
		if (j == M) {
			return i - j;
			j = Lps[j - 1];
		}
 
		// mismatch after j matches
		if (i < N && Pat[j] != Txt[i]) {
			// Do not match lps[0..lps[j-1]] characters,
			// they will match anyway
			if (j != 0)
				j = Lps[j - 1];
			else
				i = i + 1;
		}
	}
	return -1;
}

void UMainMenuWidget::DeleteNumbersInString(FString& String)
{
	for (int i = 0; i < String.Len(); ++i)
	{
		// if(String[i] == '\n')
		// {
		// 	String.RemoveAt(i);
		// 	String.InsertAt(i, ' ');
		// }
		if(FChar::IsDigit(String[i]))
		{
			String.RemoveAt(i);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *String);
}

void UMainMenuWidget::BuildLPSArray(const FString& Pat, int M, TArray<int>& Lps)
{
	{
		// length of the previous longest prefix suffix
		int Len = 0;
 
		Lps[0] = 0; // Lps[0] is always 0
 
		// the loop calculates Lps[i] for i = 1 to M-1
		int i = 1;
		while (i < M) {
			if (Pat[i] == Pat[Len]) {
				Len++;
				Lps[i] = Len;
				i++;
			}
			else // (Pat[i] != Pat[Len])
			{
				// This is tricky. Consider the example.
				// AAACAAAA and i = 7. The idea is similar
				// to search step.
				if (Len != 0) {
					Len = Lps[Len - 1];
 
					// Also, note that we do not increment
					// i here
				}
				else // if (len == 0)
				{
					Lps[i] = 0;
					i++;
				}
			}
		}
	}
}

void UMainMenuWidget::Search11D()
{
	FString Text = LineInputText_2->GetText().ToString();
	FString Pattern = FindRequiredWord();

	UE_LOG(LogTemp, Warning, TEXT("%s"), *Text);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Pattern);

	BoyerMooreSearch(Text, Pattern);
}

void UMainMenuWidget::BoyerMooreSearch(FString Txt, FString Pat)
{
	{ 
		int M = Pat.Len(); 
		int N = Txt.Len(); 
 
		TArray<int> BadChar;
		BadChar.SetNum(256, false);
 
		/* Fill the bad character array by calling 
		the preprocessing function badCharHeuristic() 
		for given pattern */
		BadCharHeuristic(Pat, BadChar);

		FString DebugBadChar;
		for (const auto& Char : BadChar)
		{
			if(Char != -1){
				DebugBadChar += FString::FromInt(Char) + ", ";
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *DebugBadChar);
 
		int s = 0; // s is shift of the pattern with 
		// respect to text 
		while(s <= (N - M)) 
		{
			// DEBUG
			UE_LOG(LogTemp, Warning, TEXT("s = %i"), s);
			
			int j = M - 1;

			// DEBUG
			FString DebugTextClip;
			for (int i = s; i <= s+M; ++i)
			{
				DebugTextClip += Txt[i];
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *DebugTextClip);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Pat);
			
			/* Keep reducing index j of pattern while 
			characters of pattern and text are 
			matching at this shift s */
			while(j >= 0 && Pat[j] == Txt[s + j]) 
				j--; 

			// DEBUG
			UE_LOG(LogTemp, Warning, TEXT("j after reducing = %i"), j);
			
			/* If the pattern is present at current 
			shift, then index j will become -1 after 
			the above loop */
			if (j < 0) 
			{
				UE_LOG(LogTemp, Warning, TEXT("Pattern occurs at shift = %i"), s); 
 
				/* Shift the pattern so that the next 
				character in text aligns with the last 
				occurrence of it in pattern. 
				The condition s+m < n is necessary for 
				the case when pattern occurs at the end 
				of text */
				s += (s + M < N)? M-BadChar[Txt[s + M]] : 1; 
 
			} 
 
			else
			{
				/* Shift the pattern so that the bad character 
				in text aligns with the last occurrence of 
				it in pattern. The max function is used to 
				make sure that we get a positive shift. 
				We may get a negative shift if the last 
				occurrence of bad character in pattern 
				is on the right side of the current 
				character. */
				s += FMath::Max(1, j - BadChar[Txt[s + j]]);
			}
		} 
	} 
}

void UMainMenuWidget::BadCharHeuristic(const FString& Str, TArray<int>& BadChar)
{ 
	int i; 
 
	// Initialize all occurrences as -1 
	for (i = 0; i < BadChar.Num(); i++) 
		BadChar[i] = -1; 
 
	// Fill the actual value of last occurrence 
	// of a character 
	for (i = 0; i < Str.Len(); i++) 
		BadChar[static_cast<int>(Str[i])] = i; 
}

FString UMainMenuWidget::FindRequiredWord()
{
	FString FirstText = LineInputText_1->GetText().ToString();
	TArray<FString> Words;
	FirstText.ParseIntoArray(Words, TEXT(" "));

	FString Result;
	int Min = INT_MAX;
	for(const auto& Word : Words)
	{
		int VowelsCount = 0;
		for(const auto& Char : Word)
		{
			if(IsVowel(Char))
			{
				VowelsCount++;
			}
		}
		if(Min > VowelsCount)
		{
			Min = VowelsCount;
			Result = Word;
		}
	}
	for (int i = 0; i < Result.Len(); ++i)
	{
		if(TChar<TCHAR>::IsDigit(Result[i]))
		{
			Result.RemoveAt(i);
		}
	}
	return Result;
}

bool UMainMenuWidget::IsVowel(char Ch)
{
	// Convert the character to lowercase for case-insensitive comparison
	Ch = tolower(Ch);

	// Check if the character is one of the vowels
	return (Ch == 'a' || Ch == 'e' || Ch == 'i' || Ch == 'o' || Ch == 'u');
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

void UMainMenuWidget::ProcessLab6A()
{
	TArray<int> Result;
	InitArraysA();

	FString SortType = TEXT("Selection");
	for (int i = 0; i < 5; ++i)
	{
		Result = Array6A[i];
		auto StartTime = std::chrono::high_resolution_clock::now();
		SelectionSortA(Result);
		auto StopTime = std::chrono::high_resolution_clock::now(); 
		std::chrono::microseconds ExcecutionTime = std::chrono::duration_cast<std::chrono::microseconds>(StopTime - StartTime);
		
		UTextBlock* NewCell = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		NewCell->SetText(FText::FromString(FString::FormatAsNumber(ExcecutionTime.count())));
		Table6A->AddChildToUniformGrid(NewCell, ESortTypes::Selection, i + 1);
	}

	SortType = TEXT("Shell");
	for (int i = 0; i < 7; ++i)
	{
		Result = Array6A[i];
		auto StartTime = std::chrono::high_resolution_clock::now();
		ShellSortA(Result);
		auto StopTime = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds ExcecutionTime = std::chrono::duration_cast<std::chrono::microseconds>(StopTime - StartTime);
		
		UTextBlock* NewCell = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		NewCell->SetText(FText::FromString(FString::FormatAsNumber(ExcecutionTime.count())));
		Table6A->AddChildToUniformGrid(NewCell, ESortTypes::Shell, i + 1);
	}

	SortType = TEXT("Quick");
	for (int i = 0; i < 7; ++i)
	{
		Result = Array6A[i];
		auto StartTime = std::chrono::high_resolution_clock::now();
		QuickSortA(Result, 0, Result.Num()-1);
		auto StopTime = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds ExcecutionTime = std::chrono::duration_cast<std::chrono::microseconds>(StopTime - StartTime);
		
		UTextBlock* NewCell = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		NewCell->SetText(FText::FromString(FString::FormatAsNumber(ExcecutionTime.count())));
		Table6A->AddChildToUniformGrid(NewCell, ESortTypes::Quick, i + 1);
	}

	SortType = TEXT("Merge");
	for (int i = 0; i < 7; ++i)
	{
		Result = Array6A[i];
		auto StartTime = std::chrono::high_resolution_clock::now();
		MergeSortA(Result, 0, Result.Num()-1);
		auto StopTime = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds ExcecutionTime = std::chrono::duration_cast<std::chrono::microseconds>(StopTime - StartTime);
		
		UTextBlock* NewCell = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		NewCell->SetText(FText::FromString(FString::FormatAsNumber(ExcecutionTime.count())));
		Table6A->AddChildToUniformGrid(NewCell, ESortTypes::Merg, i + 1);
	}

	SortType = TEXT("Counting");
	for (int i = 0; i < 7; ++i)
	{
		auto StartTime = std::chrono::high_resolution_clock::now();
		Result = CountingSortA(Array6A[i]);
		auto StopTime = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds ExcecutionTime = std::chrono::duration_cast<std::chrono::microseconds>(StopTime - StartTime);
		
		UTextBlock* NewCell = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
		NewCell->SetText(FText::FromString(FString::FormatAsNumber(ExcecutionTime.count())));
		Table6A->AddChildToUniformGrid(NewCell, ESortTypes::Counting, i + 1);
	}
}

void UMainMenuWidget::SelectionSortA(TArray<int>& Array)
{
	for (int i = 0; i < Array.Num(); i++) {
		int IndexToSwap = i;
		
		for (int k = i; k < Array.Num() - 1; k++) {
			if (Array[k + 1] > Array[IndexToSwap]) {
				IndexToSwap = k + 1;
			}
		}
		if(&Array[i] != &Array[IndexToSwap])
		{
			Swap(Array[i], Array[IndexToSwap]);
		}
	}
}

void UMainMenuWidget::ShellSortA(TArray<int>& Array)
{
	for (int Gap = Array.Num()/2; Gap > 0; Gap /= 2)
	{

		for (int i = Gap; i < Array.Num(); i += 1)
		{

			float Temp = Array[i];

			int j;            
			for (j = i; j >= Gap && Array[j - Gap] < Temp; j -= Gap)
			{
				Array[j] = Array[j - Gap];
			}

			Array[j] = Temp;
		}
	}
}

void UMainMenuWidget::QuickSortA(TArray<int>& Array, int Begin, int End)
{	// base case
	if (Begin >= End)
		return;
 
	// partitioning the Array_16Aay
	int p = PartitionA(Array, Begin, End);
 
	// Sorting the left part
	QuickSortA(Array, Begin, p - 1);
 
	// Sorting the right part
	QuickSortA(Array, p + 1, End);
	
}

void UMainMenuWidget::MergeSortA(TArray<int>& Array, int Begin, int End)
{
	if (Begin >= End)
		return;
 
	int Mid = Begin + (End - Begin) / 2;
	MergeSortA(Array, Begin, Mid);
	MergeSortA(Array, Mid + 1, End);
	MergeA(Array, Begin, Mid, End);
}

TArray<int> UMainMenuWidget::CountingSortA(const TArray<int>& Array)
{
	const int Size = Array.Num();

	// Finding the minimum element of array inputArray[].
	int MinElement = Array[0];
	for (int i = 1; i < Size; i++)
	{
		if (Array[i] < MinElement)
		{
			MinElement = Array[i];
		}
	}

	// Finding the maximum element of array inputArray[].
	int MaxElement = Array[0];
	for (int i = 1; i < Size; i++)
	{
		if (Array[i] > MaxElement)
		{
			MaxElement = Array[i];
		}
	}

	// Calculating the offset.
	int Offset = abs(MinElement);

	// Mapping each element of inputArray[] as an index of countArray[] array.
	TArray<int> CountArray;
	CountArray.Init(0, MaxElement + Offset + 1);
	for (int i = 0; i < Size; i++)
	{
		CountArray[Array[i] + Offset] += 1;
	}
	
	// Creating outputArray[] from countArray[] array.
	TArray<int> OutputArray;
	OutputArray.Init(0, Size);
	for (int i = CountArray.Num() - 1, j = 0; i >= 0;)
	{
		if(CountArray[i] > 0)
		{
			OutputArray[j] = i - Offset;
			CountArray[i]--;
			j++;
		}
		if(CountArray[i] == 0)
		{
			i--;
		}
	}
	
	return OutputArray;
}

bool UMainMenuWidget::IsSortedA(const TArray<int>& Array)
{
	for(int i = 0; i < Array.Num() - 1; i++)
	{
		if(Array[i + 1] > Array[i])
		{
			return false;
		}
	}
	
	return true;
}

int UMainMenuWidget::PartitionA(TArray<int>& Array, int Begin, int End)
{
	const float Pivot = Array[End];
 
	int i = Begin - 1;
	for(int j = Begin; j <= End - 1; j++)
	{
		if(Array[j] > Pivot)
		{
			i++;
			SwapElementsA(Array, i,j);
		}
	}
	i++;
	SwapElementsA(Array, i, End);
 
	return i;
}
void UMainMenuWidget::SwapElementsA(TArray<int>& Array, int First, int Second)
{
	const float Temp = Array[First];
	Array[First] = Array[Second];
	Array[Second] = Temp;
}

void UMainMenuWidget::MergeA(TArray<int>& Array, int const Left, int const Mid, int const Right)
{
	
	int const SubArrayOne = Mid - Left + 1;
	int const SubArrayTwo = Right - Mid;
	
	// Create temp arrays
	auto *LeftArray = new float[SubArrayOne],
			*RightArray = new float[SubArrayTwo];
 
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

void UMainMenuWidget::InitArraysA()
{
	std::ofstream Fout;
	Fout.open("D:\\Algorythms\\AlgLab2\\Content\\Stuff\\InitialArraysLog.txt", std::ios::trunc);
	Fout << "1024 elements array:\n";
	for(int i = 0; i < 1024; ++i)
	{
		Array6A[0].Push(UKismetMathLibrary::RandomIntegerInRange(-50, 50));
		Fout << Array6A[0][i] << " ";
	}
	Fout << '\n';

	Fout << "\n4096 elements array:\n";
	for(int i = 0; i < 4096; ++i)
	{
		Array6A[1].Push(UKismetMathLibrary::RandomIntegerInRange(-50, 50));
		Fout << Array6A[1][i] << " ";
	}
	Fout << '\n';

	Fout << "\n16384 elements array:\n";
	for(int i = 0; i < 16384; ++i)
	{
		Array6A[2].Push(UKismetMathLibrary::RandomIntegerInRange(-50, 50));
		Fout << Array6A[2][i] << " ";
	}
	Fout << '\n';

	Fout << "\n65536 elements array:\n";
	for(int i = 0; i < 65536; ++i)
	{
		Array6A[3].Push(UKismetMathLibrary::RandomIntegerInRange(-50, 50));
		Fout << Array6A[3][i] << " ";
	}
	Fout << '\n';

	Fout << "\n262144 elements array:\n";
	for(int i = 0; i < 262144; ++i)
	{
		Array6A[4].Push(UKismetMathLibrary::RandomIntegerInRange(-50, 50));
		Fout << Array6A[4][i] << " ";
	}
	Fout << '\n';

	Fout << "\n1048576 elements array:\n";
	for(int i = 0; i < 1048576; ++i)
	{
		Array6A[5].Push(UKismetMathLibrary::RandomIntegerInRange(-50, 50));
		Fout << Array6A[5][i] << " ";
	}
	Fout << '\n';

	Fout << "\n4194304 elements array:\n";
	for(int i = 0; i < 4194304; ++i)
	{
		Array6A[6].Push(UKismetMathLibrary::RandomIntegerInRange(-50, 50));
		Fout << Array6A[6][i] << " ";
	}
	Fout << '\n';
	Fout.close();
}

void UMainMenuWidget::StartASeven()
{
	ActiveWidget = 0;
	NewIndex = 0;
	
	BCreateQueue->OnClicked.AddDynamic(this, &UMainMenuWidget::CreateQueueCreator);
	BMergeQueue->OnClicked.AddDynamic(this, &UMainMenuWidget::MergeQueues);
	BFindElement->OnClicked.AddDynamic(this, &UMainMenuWidget::FindElementIndex);
	BAddElement->OnClicked.AddDynamic(this, &UMainMenuWidget::AddElement);
}

void UMainMenuWidget::CreateQueueCreator()
{
	if(CreateQueueWidgetClass)
	{
		APlayerController* Controller = GetWorld()->GetFirstPlayerController();
		CreateQueueWidget = CreateWidget<UCreateQueueWidget>(Controller, CreateQueueWidgetClass);
		if(CreateQueueWidget)
		{
			CreateQueueWidget->CreateQueue.BindDynamic(this, &UMainMenuWidget::CreateQueue);
			CreateQueueWidget->DeleteWidget.BindDynamic(this, &UMainMenuWidget::RemoveWidgetCreator);
			CreateQueueWidget->AddToViewport();
		}
	}
}

void UMainMenuWidget::CreateQueue(FString Name, FString Elements)
{
	CreateQueueWidget->CreateQueue.Unbind();
	CreateQueueWidget->DeleteWidget.Unbind();
	CreateQueueWidget->RemoveFromViewport();
	
	if(QueueWidgetClass)
	{
		APlayerController* Controller = GetWorld()->GetFirstPlayerController();
		UQueueWidget* QWidget = CreateWidget<UQueueWidget>(Controller, QueueWidgetClass);
		if(QWidget)
		{
			QWidget->Setup(Name, ++NewIndex, Elements);
			QWidget->Activated.BindDynamic(this, &UMainMenuWidget::SetActiveWidget);
			QueueWidgets.Add(NewIndex, QWidget);
			SQueues->AddChild(QWidget);
		}
	}
	
}

void UMainMenuWidget::MergeQueues()
{
	UQueueWidget* First = nullptr;
	UQueueWidget* Second = nullptr;
	for(const TPair<int, UQueueWidget*>& NextQueue : QueueWidgets)
	{
		if(NextQueue.Value->IsCheckedState() && First == nullptr)
		{
			First = NextQueue.Value;
			continue;
		}
		if(NextQueue.Value->IsCheckedState() && Second == nullptr)
		{
			Second = NextQueue.Value;
			break;
		}
	}
	
	if(First != nullptr && Second != nullptr)
	{	
		if(QueueWidgetClass)
		{
			APlayerController* Controller = GetWorld()->GetFirstPlayerController();
			UQueueWidget* QWidget = CreateWidget<UQueueWidget>(Controller, QueueWidgetClass);
			if(QWidget)
			{
				QWidget->Setup("Merged", ++NewIndex, First->GetPriorityQueue(), Second->GetPriorityQueue());
				QWidget->Activated.BindDynamic(this, &UMainMenuWidget::SetActiveWidget);
				QueueWidgets.Add(NewIndex, QWidget);
				SQueues->AddChild(QWidget);
			}
		}
	}
}

void UMainMenuWidget::FindElementIndex()
{
	if(ActiveWidget != 0)
	{
		UQueueWidget* ActiveQueue = *QueueWidgets.Find(ActiveWidget);
		TPosition->SetText(FText::FromString(FString::FromInt(ActiveQueue->FindIndexByElement(ElementToFind->GetText().ToString()))));
	}
}

void UMainMenuWidget::AddElement()
{
	if(ActiveWidget != 0)
	{
		UQueueWidget* ActiveQueue = *QueueWidgets.Find(ActiveWidget);
		ActiveQueue->AddElement(ElementToAdd->GetText().ToString());
	}
}

void UMainMenuWidget::RemoveWidgetCreator()
{
	CreateQueueWidget->CreateQueue.Unbind();
	CreateQueueWidget->DeleteWidget.Unbind();
	CreateQueueWidget->RemoveFromViewport();
}

void UMainMenuWidget::SetActiveWidget(int WidgetIndex)
{
	if(ActiveWidget != 0)
	{
		UQueueWidget* Current = *QueueWidgets.Find(ActiveWidget);
		if(Current)
		{	
			Current->Deactivate();
		}
	}
	ActiveWidget = WidgetIndex;
	
	UQueueWidget* NewActive = *QueueWidgets.Find(ActiveWidget);
	NewActive->Activate();
	ShowStats(NewActive);
}

void UMainMenuWidget::ShowStats(UQueueWidget* Queue)
{
	TQuantity->SetText(FText::FromString(FString::FromInt(Queue->GetNumOfElements())));
	TMin->SetText(FText::FromString(Queue->GetMin()));
	TMax->SetText(FText::FromString(Queue->GetMax()));
	TElements->SetText(FText::FromString(Queue->GetAllElements()));
	TThirdFS->SetText(FText::FromString(Queue->GetThirdFS()));
	TSecondFE->SetText(FText::FromString(Queue->GetSecondFE()));
}
