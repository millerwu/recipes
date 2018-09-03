#include <vector>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void SelectionSort(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); ++i) {
        int index = i;
        for (int j = i; j < arr.size(); ++j) {
            if (arr[index] > arr[j]) {
                index = j;
            }
        }
        swap(arr[i], arr[index]);
    }
}