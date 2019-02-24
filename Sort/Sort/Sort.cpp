#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int kNumOfElements = 100;
const char* kPath = "file.txt";
void FillingFile(int num_of_elements = kNumOfElements); 
int *ReadingFile(int num_of_elements = kNumOfElements); 
int *SelectionSort(int *data, int num_of_elements = kNumOfElements); 
void WritingFile(int *sorted_data, int num_of_elements = kNumOfElements); 
void CheckSort(int *test_array, int *test_sorted_data, int num_of_elements = kNumOfElements);
void FirstTest(int num_of_elements = kNumOfElements); 
void SecondTest(int num_of_elements = kNumOfElements); 

int main()
{
	FillingFile();
	int *data = ReadingFile();
	int *sorted_data = SelectionSort(data);
	WritingFile(sorted_data);
	FirstTest();
	SecondTest();
	
	return 0;
}

void FillingFile(int num_of_elements)
{
	std::ofstream file(kPath, std::ios_base::out | std::ios_base::trunc); 
	if (!file.is_open())
	{
		std::cout << "File is not open for filling!" << std::endl;
	}
	std::srand(time(0)); 
	for (int i = 0; i < num_of_elements; i++) 
	{
		file << std::rand() % 1000 << std::endl;
	}
	file.close();
}

int *ReadingFile(int num_of_elements)
{
	std::ifstream file(kPath);
	if (!file.is_open()) 
	{
		std::cout << "File is not open for reading!" << std::endl;
	}
	file.seekg(0, std::ios_base::end); 
	std::cout << "Size of file: " << file.tellg() << " bytes" << std::endl;
	file.seekg(0, std::ios_base::beg); 
	int *buffer = new int[num_of_elements]; 
	for (int i = 0; i < num_of_elements; i++) 
	{
		file >> buffer[i];
	}
	file.close();
	return buffer; 
}


int *SelectionSort(int *data, int num_of_elements)
{
	for (int i = 0; i < num_of_elements - 1; i++)
	{
		int min_ind = i;
		for (int j = i + 1; j < num_of_elements; j++)
		{
			if (data[min_ind] > data[j])
			{
				min_ind = j;
			}

		}
		if (min_ind != i)
		{
			std::swap(data[i], data[min_ind]);
		}
	}
	return data;
}

void WritingFile(int *sorted_data, int num_of_elements)
{
	std::ofstream file(kPath, std::ios_base::app);
	if (!file.is_open()) 
	{
		std::cout << "File is not open for writing!" << std::endl;
	}
	file << "Sorted data: " << std::endl;
	for (int i = 0; i < num_of_elements; i++)
	{
		file << sorted_data[i] << std::endl;
	}
	file.close();
}

void CheckSort(int *test_array, int *test_sorted_data, int num_of_elements)
{
	int *check = new int[num_of_elements];
	int check_sum = 0;
	for (int i = 0; i < num_of_elements; i++)
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

void FirstTest(int num_of_elements)
{
	int *test_array = new int[num_of_elements];
	std::srand(time(0));
	for (int i = 0; i < num_of_elements; i++)
	{
		test_array[i] = std::rand() % 1000;
	}
	std::sort(test_array, test_array + num_of_elements);
	int *test_sorted_data = SelectionSort(test_array, num_of_elements);
	std::cout << "Check number one: comparing selection sorting with standard sorting. \n";
	CheckSort(test_array, test_sorted_data);
	delete[] test_array;
}

void SecondTest(int num_of_elements)
{
	int *test_array = new int[num_of_elements];
	for (int i = 0; i < num_of_elements; i++)
	{
		test_array[i] = i;
	}
	int *test_sorted_data = SelectionSort(test_array);
	std::cout << "Check number two: comparing selection sorting with sorted array. \n";
	CheckSort(test_array, test_sorted_data);
	delete[] test_array;
}