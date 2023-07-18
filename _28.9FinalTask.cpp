#include <Windows.h>
#include "MergeSort.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));
    time_t start, end;
    const int size = 500000;
    vector <int> arr;
    for (int i = 0; i < size; i++) arr.push_back(rand());
    cout << "Контейнер заполнен.\n";
     time(&start);
    //запуск сортировки в многопоточном режиме
    MergeSort(arr, 0, size-1);
    time(&end);

    double seconds = difftime(end, start);
    cout << "Затраченное время при многопоточке с использованием Future: " << seconds << " секунд" << endl;
    //проверяем, что контейнер отсортирован
    bool sort = true;
    for (int i = 0; i < size-1; i++) {
        if (arr[i] > arr[i + 1]) {
            cout << "Не отсортировано." << endl;
            sort = false;
            break;
        }
    }
    if (sort) cout << "Контейнер отсортирован.\n";

    for (int i = 0; i < size; i++) arr[i] = rand();
    cout << "Контейнер заполнен.\n";

    time(&start);
    //запуск сортировки в однопоточном режиме
    MergeSortThread(arr, 0, size - 1);
    time(&end);

    seconds = difftime(end, start);
    cout << "Затраченное время при многопоточке с использованием Thread: " << seconds << " секунд" << endl;
    //проверяем, что контейнер отсортирован
    sort = true;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            cout << "Не отсортировано." << endl;
            sort = false;
            break;
        }
    }
    if (sort) cout << "Контейнер отсортирован.\n";

    for (int i = 0; i < size; i++) arr[i]=rand();
    cout << "Контейнер заполнен.\n";

    time(&start);
    //запуск сортировки в однопоточном режиме
    MergeSortOne(arr, 0, size - 1);
    time(&end);

    seconds = difftime(end, start);
    cout << "Затраченное время при многопоточке: " << seconds << " секунд" << endl;
    //проверяем, что контейнер отсортирован
    sort = true;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            cout << "Не отсортировано." << endl;
            sort = false;
            break;
        }
    }
    if (sort) cout << "Контейнер отсортирован.\n";
    return 0;
}