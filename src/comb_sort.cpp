#include "../include/sorting.h"

void CombSort::sort(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return;
    
    // Initialize gap
    int gap = n;
    
    // Initialize shrink factor
    const double shrink = 1.3; // common shrink factor
    
    bool swapped = true;
    
    // Keep running while gap is more than 1 and last iteration caused a swap
    while (gap > 1 || swapped) {
        // Update the gap using shrink factor
        gap = static_cast<int>(gap / shrink);
        if (gap < 1)
            gap = 1;
            
        swapped = false;
        
        // Compare elements with gap
        for (int i = 0; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}