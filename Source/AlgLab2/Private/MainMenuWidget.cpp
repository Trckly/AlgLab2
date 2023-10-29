// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "Kismet/KismetMathLibrary.h"
#include "Tools/UEdMode.h"

TArray<int> UMainMenuWidget::SelectionSort(TArray<int> Array)
{
	int MinIdx, N = Array.Num();
 
	// One by one move boundary of
	// unsorted subarray
	for (int i = 0; i < N - 1; i++) {
 
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

	for (int j = Max; j >= Min; j--)
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
		Array6D_1.Push(UKismetMathLibrary::RandomIntegerInRange(-1000000, 1000000));
		Fout << Array6D_1[i] << " ";
	}
	Fout << '\n';

	Fout << "\n4096 elements array:\n";
	for(int i = 0; i < 4096; ++i)
	{
		Array6D_2.Push(UKismetMathLibrary::RandomIntegerInRange(-1000000, 1000000));
		Fout << Array6D_2[i] << " ";
	}
	Fout << '\n';

	Fout << "\n16384 elements array:\n";
	for(int i = 0; i < 16384; ++i)
	{
		Array6D_3.Push(UKismetMathLibrary::RandomIntegerInRange(-1000000, 1000000));
		Fout << Array6D_3[i] << " ";
	}
	Fout << '\n';

	Fout << "\n65536 elements array:\n";
	for(int i = 0; i < 65536; ++i)
	{
		Array6D_4.Push(UKismetMathLibrary::RandomIntegerInRange(-1000000, 1000000));
		Fout << Array6D_4[i] << " ";
	}
	Fout << '\n';

	Fout << "\n262144 elements array:\n";
	for(int i = 0; i < 262144; ++i)
	{
		Array6D_5.Push(UKismetMathLibrary::RandomIntegerInRange(-1000000, 1000000));
		Fout << Array6D_5[i] << " ";
	}
	Fout << '\n';

	Fout << "\n1048576 elements array:\n";
	for(int i = 0; i < 1048576; ++i)
	{
		Array6D_6.Push(UKismetMathLibrary::RandomIntegerInRange(-1000000, 1000000));
		Fout << Array6D_6[i] << " ";
	}
	Fout << '\n';

	Fout << "\n4194304 elements array:\n";
	for(int i = 0; i < 4194304; ++i)
	{
		Array6D_7.Push(UKismetMathLibrary::RandomIntegerInRange(-1000000, 1000000));
		Fout << Array6D_7[i] << " ";
	}
	Fout << '\n';
	Fout.close();
}

void UMainMenuWidget::ProcessLab6D()
{
	TArray<int> Result;
	
	ProcessingTextBlock->SetText(FText::FromString(TEXT("Initializing arrays and writing to the file...")));
	InitArrays();
	
	FString EntryMessage = TEXT("Processing: ");
	FString SortType = TEXT("Selection Sort");
	ProcessingTextBlock->SetText(FText::FromString(EntryMessage + SortType));
	
	auto StartTime = std::chrono::high_resolution_clock::now();
	Result = SelectionSort(Array6D_1);
	auto StopTime = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds ExcecutionTime = std::chrono::duration_cast<std::chrono::milliseconds>(StopTime - StartTime);
	IsSorted(Result, TEXT("Selection Sort"), Array6D_1.Num());

	
	
	
}
