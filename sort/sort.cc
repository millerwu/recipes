#include <iostream>
#include <vector>
#include <sys/time.h>


#define ACCURACY_TEST
#define MERGESORT_TEST
#define QUICKSORT_TEST
#define INSERTIONSORT_TEST
#define SELECTIONSORT_TEST
#define HEAPSORT_TEST

using namespace std;

void InsertionSort(vector<int> &arr);

void MergeSort(vector<int> &arr);

void SelectionSort(vector<int> &arr);

void QuickSort(vector<int> &arr);

void HeapSort(vector<int> &arr);

uint64_t getCurrentTime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    uint64_t time = t.tv_sec*1000 + t.tv_usec/1000;
    return time;
}

vector<int> InitArray(int size)
{
    vector<int> arr;
    
    for(size_t i = 0; i < size; i++)
    {
        arr.insert(arr.begin(), rand());
    }
    return arr;
}

vector<int> InitArrayWithThousand(int size)
{
    vector<int> arr;
    for (size_t i = 0; i < size; ++i) {
        arr.insert(arr.begin(), rand() % 1000);
    }
    return arr;
}

void PrintVector(vector<int> arr)
{
    for(size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << endl;
    }
}

int main(int argc, char const *argv[])
{

    uint64_t time, cost;
#ifdef ACCURACY_TEST
    vector<int> v1 = {100, 10, 29, 47, 18, 28, 34};
    cout << "input array: " << endl;
    HeapSort(v1);
    cout << "result: " << endl;
    PrintVector(v1);
    vector<int> ran_v = InitArrayWithThousand(20);
    cout << "Input: " << endl;
    PrintVector(ran_v);
    HeapSort(ran_v);
    cout << "result: " << endl;
    PrintVector(ran_v);
#endif
    vector<int> performenttest = InitArray(1000*100);

#ifdef MERGESORT_TEST
    vector<int> merge_performenttest = performenttest;
    time = getCurrentTime();
    MergeSort(merge_performenttest);
    cost = getCurrentTime() - time;
    cout << "MergeSort cost time = " << cost << " ms"<< endl;
#endif

#ifdef QUICKSORT_TEST
    vector<int> quick_performenttest = performenttest;
    time = getCurrentTime();
    QuickSort(performenttest);
    cost = getCurrentTime() - time;
    cout << "QuickSort cost time = " << cost << " ms"<< endl;
#endif

#ifdef HEAPSORT_TEST
    vector<int> heap_performenttest = performenttest;
    time = getCurrentTime();
    HeapSort(heap_performenttest);
    cost = getCurrentTime() - time;
    cout << "HeapSort cost time = " << cost << " ms"<< endl;
#endif

#ifdef INSERTIONSORT_TEST
    vector<int> insert_performenttest = performenttest;
    time = getCurrentTime();
    InsertionSort(insert_performenttest);
    cost = getCurrentTime() - time;
    cout << "InsertionSort cost time = " << cost << " ms"<< endl;
#endif

#ifdef SELECTIONSORT_TEST
    vector<int> selection_performenttest = performenttest;
    time = getCurrentTime();
    SelectionSort(selection_performenttest);
    cost = getCurrentTime() - time;
    cout << "SelectionSort cost time = " << cost << " ms"<< endl;
#endif

    return 0;
}
