#include "../include/sorting.h"
#include <algorithm>
#include <cmath>

void LibrarySort::sort(std::vector<int>& arr) {
    if (arr.empty()) return;
    
    const double epsilon = 1.0; // Gap factor
    
    // Compute initial capacity based on epsilon
    size_t n = arr.size();
    size_t capacity = static_cast<size_t>(std::ceil((1 + epsilon) * n));
    
    // Create library array with gaps
    std::vector<std::pair<int, bool>> library(capacity, {0, false});
    
    // Insert the first element
    library[0] = {arr[0], true};
    
    // Insert remaining elements
    for (size_t i = 1; i < n; i++) {
        int element = arr[i];
        
        // Binary search to find position for insertion
        size_t left = 0;
        size_t right = static_cast<size_t>(i * (1 + epsilon));
        
        while (left < right) {
            size_t mid = left + (right - left) / 2;
            
            if (!library[mid].second || library[mid].first < element) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        // Find actual position (might be occupied)
        size_t pos = left;
        while (pos < capacity && library[pos].second && library[pos].first <= element) {
            pos++;
        }
        
        // Shift elements to make room for insertion
        for (size_t j = i; j > pos; j--) {
            library[j] = library[j - 1];
        }
        
        // Insert the element
        library[pos] = {element, true};
        
        // Every log(n) operations, rebalance
        if (i > 0 && (i & (i - 1)) == 0) { // If i is a power of 2
            rebalance(library, i);
        }
    }
    
    // Copy elements back to original array
    size_t idx = 0;
    for (size_t i = 0; i < capacity && idx < n; i++) {
        if (library[i].second) {
            arr[idx++] = library[i].first;
        }
    }
}

void LibrarySort::rebalance(std::vector<std::pair<int, bool>>& library, size_t count) {
    // Temporary storage for occupied elements
    std::vector<int> elements;
    elements.reserve(count);
    
    // Gather all occupied elements
    for (size_t i = 0; i < library.size(); i++) {
        if (library[i].second) {
            elements.push_back(library[i].first);
            library[i].second = false; // Mark as unoccupied
        }
        
        if (elements.size() >= count) break;
    }
    
    // Place elements back with even spacing
    size_t interval = library.size() / (count + 1);
    for (size_t i = 0; i < elements.size(); i++) {
        size_t pos = (i + 1) * interval;
        library[pos] = {elements[i], true};
    }
}
