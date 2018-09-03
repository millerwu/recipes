#include <vector>
#include <iostream>

using namespace std;

void MergeSortByIteration(vector<int> &arr)
{
    vector<int> reg(arr.size());
    
    for(size_t i = 1; i < arr.size(); i *= 2)
    {
        for(size_t j = 0; j < arr.size() / (2 * i) + 1; j++)
        {
            size_t g1_begin = j * i * 2;
            size_t g1_end = j * i * 2 - 1 + i;
            size_t g2_begin = min(arr.size()-1, j * i * 2 + i);
            size_t g2_end = min(arr.size()-1, (j + 1) * i * 2 - 1);
            size_t reg_index = g1_begin;

            while (reg_index <= g2_end)
            {
                if ((g1_begin <= g1_end) && (g2_begin <= g2_end))
                {
                   if (arr[g1_begin] <= arr[g2_begin]) {
                       reg[reg_index] = arr[g1_begin];
                       g1_begin++;
                   } else {
                       reg[reg_index] = arr[g2_begin];
                       g2_begin++;
                   }
                } else if (g1_begin <= g1_end) {
                    reg[reg_index] = arr[g1_begin];
                    g1_begin++;
                } 
                else
                {
                    reg[reg_index] = arr[g2_begin];
                    g2_begin++;
                }
                reg_index++;
            }
        }
        
        for(size_t i = 0; i < arr.size(); i++)
        {
            arr[i] = reg[i];
        }
    }
}

void RecursionHelper(vector<int> &arr, vector<int>& reg, size_t begin, size_t end)
{
    if (begin >= end) {
        return;
    }
    size_t mid = (end + begin) / 2;
    RecursionHelper(arr, reg, begin, mid);
    RecursionHelper(arr, reg, mid+1, end);

    size_t index = begin;
    size_t g1_begin = begin;
    size_t g1_end = mid;
    size_t g2_begin = mid + 1;
    size_t g2_end = end;
    while (index <= end) {
        if ((g1_begin <= g1_end) && (g2_begin <= g2_end)) {
            if (arr[g1_begin] <= arr[g2_begin]) {
                reg[index] = arr[g1_begin];
                g1_begin++;
            } else {
                reg[index] = arr[g2_begin];
                g2_begin++;
            }
        } else if (g1_begin <= g1_end) {
            reg[index] = arr[g1_begin];
            g1_begin++;
        } else {
            reg[index] = arr[g2_begin];
            g2_begin++;
        }
        index++;
    }
    for (size_t i = begin; i <= end; ++i) {
        arr[i] = reg[i];
    }
}

void MergeSortByRecursion(vector<int> &arr)
{
    vector<int> reg(arr.size());
    return RecursionHelper(arr, reg, 0, arr.size()-1);
}

void MergeSort(vector<int> &arr)
{
    MergeSortByRecursion(arr);
}