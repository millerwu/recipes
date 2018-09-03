//
// Created by WuMiaoLiang on 27/08/2018.
//

#include <vector>
#include <iostream>

using namespace std;

void swap(int& a, int& b);

void QuickSortHelper(vector<int>& arr, size_t begin, size_t end)
{
    if (begin >= end)
    {
        return;
    }
    int mid = arr[end];
    size_t index = begin;
    for (size_t i = begin; i < end; ++i) {
        if (arr[i] < mid) {
            swap(arr[i], arr[index]);
            index++;
        }
    }
    swap(arr[index], arr[end]);
    QuickSortHelper(arr, begin, index-1);
    QuickSortHelper(arr, index+1, end);
}

void QuickSort(vector<int> &arr)
{
    return QuickSortHelper(arr, 0, arr.size()-1);
}