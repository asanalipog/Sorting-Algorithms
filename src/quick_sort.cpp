#include "../include/sorting.h"
#include <random>

void QuickSort::sort(std::vector<int>& arr) {
    if (arr.empty()) return;
    quickSort(arr, 0, arr.size() - 1);
}

void QuickSort::quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // pi is partitioning index
        int pi = partition(arr, low, high);
        
        // Separately sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int QuickSort::partition(std::vector<int>& arr, int low, int high) {
    // Use a more robust pivot selection (median of three)
    int mid = low + (high - low) / 2;
    
    // Sort low, mid, high
    if (arr[mid] < arr[low])
        std::swap(arr[mid], arr[low]);
    if (arr[high] < arr[low])
        std::swap(arr[high], arr[low]);
    if (arr[high] < arr[mid])
        std::swap(arr[high], arr[mid]);
    
    // Place pivot at position high-1
    std::swap(arr[mid], arr[high-1]);
    int pivot = arr[high-1];
    
    // Index of smaller element
    int i = (low - 1);
    
    for (int j = low; j <= high - 2; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++;    // increment index of smaller element
            std::swap(arr[i], arr[j]);
        }
    }
    
    std::swap(arr[i + 1], arr[high - 1]);
    return (i + 1);
}