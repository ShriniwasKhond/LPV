#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (int x = left; x <= right; x++) {
        arr[x] = temp[x];
    }
}

void mergeSortParallel(vector<int>& arr, vector<int>& temp, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            mergeSortParallel(arr, temp, left, mid);
        }
        #pragma omp section
        {
            mergeSortParallel(arr, temp, mid + 1, right);
        }
    }

    merge(arr, temp, left, mid, right);
}

void mergeSort(vector<int>& arr) {
    int n = arr.size();
    vector<int> temp(n);

    mergeSortParallel(arr, temp, 0, n - 1);
}

int main() {
    cout<<"Enter the number of elements :"<<endl;
    cin>>n;

    vector<int> arr(n);

    cout<<"enter the elements :"<<endl;

    for(int i=0; i<n; i++){
        cin>>arr[i];
    }

    // vector<int> arr = {9, 5, 7, 1, 3, 6, 2, 8, 4};

    cout << "Original Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    double startTime = omp_get_wtime();

    mergeSort(arr);

    double endTime = omp_get_wtime();
    double interval = (endTime - startTime)*1000.0;

    cout << "Sorted Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Time taken: " << interval << " milliseconds" << endl;

    return 0;
}