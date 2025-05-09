#include "../include/sorting.h"

void SelectionSort::sort(std::vector<int>& arr) {
    int n = arr.size();
    
    // One by one move boundary of unsorted subarray
    for (int i = 0; i < n - 1; i++) {
        // Find the minimum element in unsorted array
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        // Swap the found minimum element with the first element
        if (min_idx != i) {
            std::swap(arr[min_idx], arr[i]);
        }
    }
}