#include "../include/sorting.h"

void CocktailSort::sort(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return;
    
    bool swapped = true;
    int start = 0;
    int end = n - 1;
    
    while (swapped) {
        // Reset swapped flag for forward pass
        swapped = false;
        
        // Forward pass (like bubble sort)
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        
        // If nothing was swapped, array is sorted
        if (!swapped)
            break;
            
        // Reset swapped flag for backward pass
        swapped = false;
        
        // Move the end point back as the largest element is now at the end
        end--;
        
        // Backward pass (bubble largest element towards start)
        for (int i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        
        // Increment start because smallest element is now at the start
        start++;
    }
}
