#include "MergeSort.h"

std::mutex m_cout;

void print_cout(string str)
{
	lock_guard<mutex> raii(m_cout);
	cout << str << endl;
}

//�������, ��������� �������
void merge(vector<int>&arr, int first, int last)
{
	int middle, start, startR, j;
	middle = (first + last) / 2; //���������� �������� ��������(����� ������ �����)
	start = first; //������ ����� �����
	startR = middle + 1; //������ ������ �����
	int* mas = new int[last + 1];

	for (j = first; j <= last; j++) //��������� �� ������ �� �����
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
		print_cout("����� �����");
		MergeSort(arr, (first + last) / 2 + 1, last);
		f.get();
	}
	else {
		// ��������� ��������������� ��� ����� � ������������ ������
		MergeSortOne(arr, first, (first + last) / 2);
		MergeSortOne(arr, (first + last) / 2 + 1, last);
	}
	merge(arr, first, last); //������� ���� ������ 
}

//����������� ������������� ��������� ����������
void MergeSortThread(vector<int>& arr, int first, int last)
{

	if (last - first > 100000)
	{
		// ���� ��������� ������ 10000
		// �������� �������� ����������
		thread f(MergeSortThread, std::ref(arr), first, (first + last) / 2);
		print_cout("����� �����");
		MergeSortThread(arr, (first + last) / 2 + 1, last);
		if (f.joinable())f.join();

	}
	else {
		// ��������� ��������������� ��� ����� � ������������ ������
		MergeSortOne(arr, first, (first + last) / 2);
		MergeSortOne(arr, (first + last) / 2 + 1, last);
	}
	merge(arr, first, last); //������� ���� ������ 
}

//����������� ������������ ��������� ����������
void MergeSortOne(vector<int>& arr, int first, int last)
{
	if (first < last)
	{
		MergeSortOne(arr, first, (first + last) / 2);	//���������� ����� �����
		MergeSortOne(arr, (first + last) / 2 + 1, last); //���������� ������ �����
		merge(arr, first, last); //������� ���� ������ 
	}
}

