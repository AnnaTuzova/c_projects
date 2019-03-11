#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int kNumOfElementsGlobal = 100;
const char* kPath = "file.txt";
void FillingFile(const int kNumOfElements = kNumOfElementsGlobal);
void ReadingFile(int *data, const int kNumOfElements = kNumOfElementsGlobal);
void SelectionSort(int *data, const int kNumOfElements = kNumOfElementsGlobal);
void WritingFile(int *sorted_data, const int kNumOfElements = kNumOfElementsGlobal);
void CheckSort(int *test_array, int *test_sorted_data, const int kNumOfElements = kNumOfElementsGlobal);
void TestRanomdArray(const int kNumOfElements = kNumOfElementsGlobal);
void TestSortedArray(const int kNumOfElements = kNumOfElementsGlobal);
void TestOneMinusOneArray(const int kNumOfElements = kNumOfElementsGlobal);
void TestEmptyArray();
void TestReverseOrderSortedArray(const int kNumOfElements = kNumOfElementsGlobal);

int main()
{
	int *data = new int[kNumOfElementsGlobal];
	
	FillingFile();
	ReadingFile(data);
	SelectionSort(data);
	WritingFile(data);
	TestRanomdArray();
	TestSortedArray();
	TestOneMinusOneArray();
	TestEmptyArray();
	TestReverseOrderSortedArray();

	delete[] data;
	return 0;
}

void FillingFile(const int kNumOfElements)
{
	std::ofstream file(kPath, std::ios_base::out | std::ios_base::trunc); 
	if (!file.is_open())
	{
		std::cout << "File is not open for filling!" << std::endl;
	}

	std::srand(time(0)); 
	for (int i = 0; i < kNumOfElements; i++) 
	{
		file << std::rand() % 1000 << std::endl;
	}

	file.close();
}

void ReadingFile(int *data, const int kNumOfElements)
{
	std::ifstream file(kPath);
	if (!file.is_open()) 
	{
		std::cout << "File is not open for reading!" << std::endl;
	}

	file.seekg(0, std::ios_base::end); 
	std::cout << "Size of file: " << file.tellg() << " bytes" << std::endl;
	file.seekg(0, std::ios_base::beg); 

	for (int i = 0; i < kNumOfElements; i++) 
	{
		file >> data[i];
	}

	file.close();
}


void SelectionSort(int *data, const int kNumOfElements)
{

	for (int i = 0; i < kNumOfElements - 1; i++)
	{
		int min_index = i;
		for (int j = i + 1; j < kNumOfElements; j++)
		{
			if (data[min_index] > data[j])
			{
				min_index = j;
			}

		}

		if (min_index != i)
		{
			std::swap(data[i], data[min_index]);
		}
	}
}

void WritingFile(int *sorted_data, const int kNumOfElements)
{
	std::ofstream file(kPath, std::ios_base::app);
	if (!file.is_open()) 
	{
		std::cout << "File is not open for writing!" << std::endl;
	}

	file << "Sorted data: " << std::endl;

	for (int i = 0; i < kNumOfElements; i++)
	{
		file << sorted_data[i] << std::endl;
	}

	file.close();
}

void CheckSort(int *test_array, int *test_sorted_data, const int kNumOfElements)
{
	int *check = new int[kNumOfElements];
	int check_sum = 0;
	
	for (int i = 0; i < kNumOfElements; i++)
	{
		check[i] = test_array[i] - test_sorted_data[i];
		check_sum = check_sum + check[i];
	}

	if (check_sum == 0)
	{
		std::cout << "Check is passed. Sorting works correctly. \n";
	}
	else
	{
		std::cout << "Check is failed. Sorting does not work correctly. \n";
	}

	delete[] check;
}

void TestRanomdArray(const int kNumOfElements)
{
	int *actual_array = new int[kNumOfElements];
	int *expected_array = new int[kNumOfElements];

	std::srand(time(0));
	for (int i = 0; i < kNumOfElements; i++)
	{
		actual_array[i] = std::rand() % 1000;
	}

	std::copy(actual_array, actual_array + kNumOfElements, expected_array);
	std::sort(actual_array, actual_array + kNumOfElements);

	SelectionSort(expected_array);
	std::cout << "Check number one: comparing selection sorting with standard sorting. \n";
	CheckSort(actual_array, expected_array);

	delete[] actual_array, expected_array;
}

void TestSortedArray(const int kNumOfElements)
{
	int *actual_array = new int[kNumOfElements];
	int *expected_array = new int[kNumOfElements];

	for (int i = 0; i < kNumOfElements; i++)
	{
		actual_array[i] = i;
	}
	std::copy(actual_array, actual_array + kNumOfElements, expected_array);

	SelectionSort(expected_array);
	std::cout << "Check number two: comparing selection sorting with sorted array. \n";
	CheckSort(actual_array, expected_array);

	delete[] actual_array, expected_array;
}

void TestOneMinusOneArray(const int kNumOfElements)
{
	int *actual_array = new int[kNumOfElements];
	int *expected_array = new int[kNumOfElements];

	std::srand(time(0));
	for (int i = 0; i < kNumOfElements; i++)
	{
		actual_array[i] = std::rand() % 2;

		if (actual_array[i] == 0)
		{
			actual_array[i] = -1;
		}
	}

	std::copy(actual_array, actual_array + kNumOfElements, expected_array);
	std::sort(actual_array, actual_array + kNumOfElements);
	SelectionSort(expected_array);

	std::cout << "Check number three: comparing selection sorting with array of 1 and -1. \n";
	CheckSort(actual_array, expected_array);

	delete[] actual_array, expected_array;
}

void TestEmptyArray()
{
	int* zero_pointer = 0;
	SelectionSort(zero_pointer, 0);
	if (zero_pointer == 0)
	{
		std::cout << "Check number four: sorting empty array. \n" << "Passing an empty array returns an empty array. Sorting works correctly. \n";
	}
	else
	{
		std::cout << "Check is failed. Sorting does not work correctly. \n";
	}
}

void TestReverseOrderSortedArray(const int kNumOfElements)
{
	int *actual_array = new int[kNumOfElements];
	int *expected_array = new int[kNumOfElements];

	for (int i = 0; i < kNumOfElements; i++)
	{
		actual_array[i] = (kNumOfElements - 1) - i;
	}

	std::copy(actual_array, actual_array + kNumOfElements, expected_array);
	SelectionSort(expected_array);
	std::cout << "Check number five: comparing selection sorting with array that sorted in reverse order. \n";
	CheckSort(actual_array, expected_array);

	delete[] actual_array, expected_array;
}