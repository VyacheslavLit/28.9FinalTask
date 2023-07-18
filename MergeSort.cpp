#include "MergeSort.h"


//�������, ��������� �������
void merge(vector<int>&arr, int first, int last)
{
	int middle, start, final, j;
	middle = (first + last) / 2; //���������� �������� ��������
	start = first; //������ ����� �����
	final = middle + 1; //������ ������ �����
	int* mas = new int[last + 1];

	for (j = first; j <= last; j++) //��������� �� ������ �� �����
	{
		if ((start <= middle) && ((final > last) || (arr[start] < arr[final])))
		{
			mas[j] = arr[start];
			start++;
		}
		else
		{
			mas[j] = arr[final];
			final++;
		}
	}
	//����������� ���������� � ������
	for (j = first; j <= last; j++) arr[j] = mas[j];
	delete[]mas;
}

//����������� ������������� ��������� ����������
void MergeSort(vector<int>& arr, int first, int last)
{

	if (last - first > 100000)
	{
		// ���� ��������� ������ 10000
		// �������� �������� ����������
		future<void> f = async(launch::async, [&]() {MergeSort(arr, first, (first + last) / 2);	});
		cout << "����� �����\n";
		MergeSort(arr, (first + last) / 2 + 1, last); 
		f.get();
	}
	else {
			// ��������� ��������������� ��� ����� � ������������ ������
			MergeSortOne(arr, first, (first + last) / 2);
			MergeSortOne(arr, (first + last) / 2 + 1, last);
	}
	merge(arr, first, last); //������� ���� ������ ��� ������� merge
}

//����������� ������������� ��������� ����������
void MergeSortThread(vector<int>& arr, int first, int last)
{

	if (last - first > 100000)
	{
		// ���� ��������� ������ 10000
		// �������� �������� ����������
		thread f(MergeSortThread, std::ref(arr), first, (first + last) / 2);
		cout << "����� �����\n";
		MergeSortThread(arr, (first + last) / 2 + 1, last);
		if (f.joinable())f.join();

	}
	else {
		// ��������� ��������������� ��� ����� � ������������ ������
		MergeSortOne(arr, first, (first + last) / 2);
		MergeSortOne(arr, (first + last) / 2 + 1, last);
	}
	merge(arr, first, last); //������� ���� ������ ��� ������� merge
}


//����������� ������������ ��������� ����������
void MergeSortOne(vector<int>& arr, int first, int last)
{
	if (first < last)
	{
		MergeSortOne(arr, first, (first + last) / 2);	//���������� ����� �����
		MergeSortOne(arr, (first + last) / 2 + 1, last); //���������� ������ �����
		merge(arr, first, last); //������� ���� ������ ��� ������� merge
	}
}

