//
// Created by WuMiaoLiang on 27/08/2018.
//
#include <vector>
#include <iostream>

using namespace std;

#define PARENT(i) (i)/2
#define LEFT(i) (i)*2
#define RIGHT(i) (i)*2+1

void swap(int &a, int &b);
void PrintVector(vector<int> arr);

int MaxNumInArray(vector<int> &arr, int a, int b)
{
    return arr[a] > arr[b] ? a : b;
}

void MaintainMaxHeap(vector<int> &arr, int index, int heap_size)
{
    if (LEFT(index) > heap_size) {
        return;
    } else if (LEFT(index) == heap_size) {
        if (arr[index-1] < arr[LEFT(index)-1]) {
            swap(arr[index-1], arr[LEFT(index)-1]);
            MaintainMaxHeap(arr, LEFT(index), heap_size);
        }
        return;
    } else {
        int max_index = MaxNumInArray(arr, LEFT(index)-1, RIGHT(index)-1);
        if (arr[index-1] < arr[max_index]) {
            swap(arr[index-1], arr[max_index]);
            MaintainMaxHeap(arr, max_index+1, heap_size);
        }
    }
}

void BuildMaxHeap(vector<int> &arr)
{
    for (int i = PARENT(arr.size()); i > 0; --i) {
        MaintainMaxHeap(arr, i, arr.size());
    }
}

void HeapSort(vector<int> &arr)
{
    BuildMaxHeap(arr);

    for (int i = arr.size()-1; i > 0 ; --i) {
        swap(arr[0], arr[i]);
        MaintainMaxHeap(arr, 1, i);
    }
}