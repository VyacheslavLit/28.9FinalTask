#include "MergeSort.h"

std::mutex m_cout;

void print_cout(string str)
{
	lock_guard<mutex> raii(m_cout);
	cout << str << endl;
}

//функция, сливающая массивы
void merge(vector<int>&arr, int first, int last)
{
	int middle, start, startR, j;
	middle = (first + last) / 2; //вычисление среднего элемента(конец первой части)
	start = first; //начало левой части
	startR = middle + 1; //начало правой части
	int* mas = new int[last + 1];

	for (j = first; j <= last; j++) //выполнять от начала до конца
	{
		if ((start <= middle) && ((startR > last) || (arr[start] < arr[startR])))
		{
			mas[j] = arr[start];
			start++;
		}
		else
		{
			mas[j] = arr[startR];
			startR++;
		}
	}
	//возвращение результата в список
	for (j = first; j <= last; j++) arr[j] = mas[j];
	delete[]mas;
}

//рекурсивная многопоточная процедура сортировки
void MergeSort(vector<int>& arr, int first, int last)
{

	if (last - first > 100000)
	{
		// если элементов больше 10000
		// вызываем рекурсию паралельно
		future<void> f = async(launch::async, [&]() {MergeSort(arr, first, (first + last) / 2);	});
		print_cout("Новый поток");
		MergeSort(arr, (first + last) / 2 + 1, last);
		f.get();
	}
	else {
		// запускаем последовательно обе части в однопоточном режиме
		MergeSortOne(arr, first, (first + last) / 2);
		MergeSortOne(arr, (first + last) / 2 + 1, last);
	}
	merge(arr, first, last); //слияние двух частей 
}

//рекурсивная многопоточная процедура сортировки
void MergeSortThread(vector<int>& arr, int first, int last)
{

	if (last - first > 100000)
	{
		// если элементов больше 10000
		// вызываем рекурсию паралельно
		thread f(MergeSortThread, std::ref(arr), first, (first + last) / 2);
		print_cout("Новый поток");
		MergeSortThread(arr, (first + last) / 2 + 1, last);
		if (f.joinable())f.join();

	}
	else {
		// запускаем последовательно обе части в однопоточном режиме
		MergeSortOne(arr, first, (first + last) / 2);
		MergeSortOne(arr, (first + last) / 2 + 1, last);
	}
	merge(arr, first, last); //слияние двух частей 
}

//рекурсивная однопоточная процедура сортировки
void MergeSortOne(vector<int>& arr, int first, int last)
{
	if (first < last)
	{
		MergeSortOne(arr, first, (first + last) / 2);	//сортировка левой части
		MergeSortOne(arr, (first + last) / 2 + 1, last); //сортировка правой части
		merge(arr, first, last); //слияние двух частей 
	}
}

