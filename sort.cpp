#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdlib.h>

using namespace std;

void mergeArrays(int* array, int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* first = new int[n1];
    int* second = new int[n2];

    for (i = 0; i < n1; ++i)
        first[i] = array[left + i];
    for (j = 0; j < n2; ++j)
        second[j] = array[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    
    while (i < n1 && j < n2)
    {
        if (first[i] <= second[j])
        {
            array[k] = first[i];
            ++i;
        }
        else
        {
            array[k] = second[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        array[k] = first[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        array[k] = second[j];
        ++j;
        ++k;
    }
    delete[] first;
    delete[] second;
}

void mergeSort(int* array, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left)/2;
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        mergeArrays(array, left, mid, right);
    }
}

void insertSort(int* array, int size)
{
    int i, j, k;
    for (i = 1; i < size; ++i)
    {
        k = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > k)
        {
            array[j+1] = array[j];
            --j;
        }
        array[j+1] = k;
    }
}

void makeRandomArray(int* array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array[i] = rand();
    }
}

void makeHybridArray(int array[], int size, int sortedPercent)
{
    array[0] = 0;
    int index = size*sortedPercent/100;
    for (int i = 1; i < size; ++i)
    {
        if (i < index - 1)
            array[i] = array[i - 1] + 1;
        else
            array[i] = rand();
    }
}

int main()
{
    clock_t start1, end1, start2, end2;
    int size = 10000;
    int array[size];
    cout << "Array size: " << size << endl;

    //RANDOM LIST
    cout << "Random list:" << endl;
    makeRandomArray(array, size);
    //copy to another array to reuse
    int array2[size];
    copy(array, array + size, array2);
    //insertion sort
    start1 = clock();
    insertSort(array, size);
    end1 = clock();
    double runtime1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
    cout << "Insertion: " << runtime1 << endl;
    //merge sort
    start2 = clock();
    mergeSort(array2, 0, size - 1);
    end2 = clock();
    double runtime2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;
    cout << "Merge: " << runtime2 << endl << endl;

    //SORTED LIST
    //at this time array and array2 are already sorted, we can reuse them for this test
    //but since I test this with much larger array sizes so I create another array to save time and stack
    int largeSize = 1000000;
    int* sortedArray = new int[largeSize];
    cout << "Array size: " << largeSize << endl;
    makeRandomArray(sortedArray, largeSize);
    //sort this array first
    sort(sortedArray, sortedArray + largeSize);
    cout << endl << "SORTED LIST:" << endl;
    //insertion sort
    start1 = clock();
    insertSort(sortedArray, largeSize);
    end1 = clock();
    runtime1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
    cout << "Insertion: " << runtime1 << endl;
    //merge sort
    start2 = clock();
    mergeSort(sortedArray, 0, largeSize - 1);
    end2 = clock();
    runtime2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;
    cout << "Merge: " << runtime2 << endl << endl;
    //free array
    delete[] sortedArray;

    //HYBRID ARRAY
    //create new array for the same reason above
    cout << "HYBRID ARRAY:" << endl;
    int hybridSize = 300;
    int hybridArray[hybridSize];
    int sortedPercent = 5;
    makeHybridArray(hybridArray, hybridSize, sortedPercent);
    //insertion sort
    start1 = clock();
    insertSort(hybridArray, hybridSize);
    end1 = clock();
    runtime1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
    cout << "Insertion: " << runtime1*1000 << endl;
    //merge sort
    start2 = clock();
    mergeSort(hybridArray, 0, hybridSize - 1);
    end2 = clock();
    runtime2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;
    cout << "Merge: " << runtime2*1000 << endl << endl;

    return 0;
}
