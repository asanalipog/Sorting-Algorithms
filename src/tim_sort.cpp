#include "../include/sorting.h"
#include <algorithm>

// Minimum size for applying merge sort
const int MIN_MERGE = 32;

void TimSort::sort(std::vector<int>& arr) {
    int n = arr.size();
    if (n < 2) return;
    
    // Sort individual subarrays of size MIN_MERGE using insertion sort
    for (int i = 0; i < n; i += MIN_MERGE) {
        insertionSort(arr, i, std::min((i + MIN_MERGE - 1), (n - 1)));
    }
    
    // Start merging from size MIN_MERGE
    for (int size = MIN_MERGE; size < n; size = 2 * size) {
        // Pick starting point of left sub array. We merge
        // arr[left:left+size-1] and arr[left+size:left+2*size-1]
        for (int left = 0; left < n; left += 2 * size) {
            // Find ending point of left subarray
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));
            
            // Merge subarrays arr[left:mid] and arr[mid+1:right]
            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

// Insertion sort for small arrays
void TimSort::insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Merge function similar to merge sort
void TimSort::merge(std::vector<int>& arr, int left, int mid, int right) {
    // Calculate lengths of subarrays
    int len1 = mid - left + 1;
    int len2 = right - mid;
    
    // Create temp arrays
    std::vector<int> leftArr(len1);
    std::vector<int> rightArr(len2);
    
    // Copy data to temp arrays
    for (int i = 0; i < len1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < len2; i++)
        rightArr[i] = arr[mid + 1 + i];
    
    // Merge the temp arrays
    
    // Initial indices of subarrays
    int i = 0, j = 0;
    
    // Initial index of merged array
    int k = left;
    
    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements of leftArr[]
    while (i < len1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    // Copy remaining elements of rightArr[]
    while (j < len2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}