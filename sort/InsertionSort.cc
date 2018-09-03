#include <vector>

using namespace std;

void InsertionSort(vector<int> &arr)
{
    for(int i = 0; i < arr.size(); i++)
    {   
        int key = arr[i];
        int j = i - 1;
        for(; j >= 0 && arr[j] > key; j--)
        {
            arr[j+1] = arr[j];
        }
        arr[j+1] = key;
    }    
}