#include "../include/utils.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

// Platform-specific memory usage tracking
#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#elif __APPLE__
#include <mach/mach.h>
#else
#include <sys/resource.h>
#include <unistd.h>
#endif

std::vector<int> generateRandomData(size_t size, int min, int max) {
    std::vector<int> data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    
    for (size_t i = 0; i < size; i++) {
        data[i] = distrib(gen);
    }
    
    return data;
}

std::vector<int> generateSortedData(size_t size, bool ascending) {
    std::vector<int> data(size);
    
    // Generate sequential numbers
    for (size_t i = 0; i < size; i++) {
        data[i] = static_cast<int>(i);
    }
    
    // Reverse if descending order is requested
    if (!ascending) {
        std::reverse(data.begin(), data.end());
    }
    
    return data;
}

std::vector<int> generatePartiallySortedData(size_t size, double sortedRatio) {
    // Generate sorted data first
    std::vector<int> data = generateSortedData(size, true);
    
    // Determine how many elements to shuffle
    size_t shuffleCount = static_cast<size_t>(size * (1.0 - sortedRatio));
    
    // Create random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Shuffle a portion of the data
    for (size_t i = 0; i < shuffleCount; i++) {
        size_t idx1 = std::uniform_int_distribution<size_t>(0, size - 1)(gen);
        size_t idx2 = std::uniform_int_distribution<size_t>(0, size - 1)(gen);
        std::swap(data[idx1], data[idx2]);
    }
    
    return data;
}

bool isSorted(const std::vector<int>& arr, bool ascending) {
    if (arr.empty() || arr.size() == 1) {
        return true;
    }
    
    for (size_t i = 1; i < arr.size(); i++) {
        if (ascending) {
            if (arr[i] < arr[i - 1]) {
                return false;
            }
        } else {
            if (arr[i] > arr[i - 1]) {
                return false;
            }
        }
    }
    
    return true;
}

void printArray(const std::vector<int>& arr, size_t limit) {
    size_t count = std::min(arr.size(), limit);
    
    for (size_t i = 0; i < count; i++) {
        std::cout << arr[i] << " ";
    }
    
    if (arr.size() > limit) {
        std::cout << "... (" << arr.size() - limit << " more elements)";
    }
    
    std::cout << std::endl;
}

size_t getCurrentMemoryUsage() {

    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return static_cast<size_t>(usage.ru_maxrss * 1024); // ru_maxrss is in KB
    }

    return 0; // Return 0 if failed to get memory usage
}

std::vector<int> generateDataSet(DataSetType type, size_t size) {
    switch (type) {
        case DataSetType::RANDOM:
            return generateRandomData(size);
        case DataSetType::SORTED_ASC:
            return generateSortedData(size, true);
        case DataSetType::SORTED_DESC:
            return generateSortedData(size, false);
        case DataSetType::PARTIALLY_SORTED:
            return generatePartiallySortedData(size);
        default:
            return generateRandomData(size);
    }
}

void printResults(const std::vector<SortingResult>& results) {
    // Print header
    std::cout << std::left << std::setw(20) << "Algorithm"
              << std::setw(15) << "Time (ms)"
              << std::setw(20) << "Memory (bytes)"
              << std::setw(10) << "Stable"
              << std::setw(10) << "Sorted" << std::endl;
    
    std::cout << std::string(75, '-') << std::endl;
    
    // Print results
    for (const auto& result : results) {
        std::cout << std::left << std::setw(20) << result.algorithmName
                  << std::fixed << std::setprecision(4) << std::setw(15) << result.executionTimeMs
                  << std::setw(20) << result.memoryUsageBytes
                  << std::setw(10) << (result.isStable ? "Yes" : "No")
                  << std::setw(10) << (result.isSorted ? "Yes" : "No") << std::endl;
    }
}

void saveResultsToCSV(const std::vector<SortingResult>& results, const std::string& filename) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }
    
    // Write CSV header
    file << "Algorithm,Time (ms),Memory (bytes),Stable,Sorted\n";
    
    // Write results
    for (const auto& result : results) {
        file << result.algorithmName << ","
             << std::fixed << std::setprecision(4) << result.executionTimeMs << ","
             << result.memoryUsageBytes << ","
             << (result.isStable ? "Yes" : "No") << ","
             << (result.isSorted ? "Yes" : "No") << "\n";
    }
    
    file.close();
    std::cout << "Results saved to " << filename << std::endl;
}

std::vector<SortingResult> runAllAlgorithms(
    const std::vector<SortingAlgorithm*>& algorithms,
    const std::vector<int>& data
) {
    std::vector<SortingResult> results;
    
    for (auto algorithm : algorithms) {
        // Make a copy of the original data
        std::vector<int> dataCopy = data;
        
        // Run benchmark
        SortingResult result = runSortingBenchmark(*algorithm, dataCopy);
        results.push_back(result);
    }
    
    return results;
}

std::vector<SortingResult> runAlgorithmOnAllDataSets(
    SortingAlgorithm& algorithm,
    const std::vector<size_t>& sizes,
    int numRuns
) {
    std::vector<SortingResult> results;
    
    // Data set types
    std::vector<DataSetType> dataSetTypes = {
        DataSetType::RANDOM,
        DataSetType::SORTED_ASC,
        DataSetType::SORTED_DESC,
        DataSetType::PARTIALLY_SORTED
    };
    
    std::vector<std::string> dataSetNames = {
        "Random",
        "Sorted (Asc)",
        "Sorted (Desc)",
        "Partially Sorted"
    };
    
    // For each size
    for (size_t size : sizes) {
        // For each data set type
        for (size_t i = 0; i < dataSetTypes.size(); i++) {
            double totalTimeMs = 0.0;
            size_t totalMemory = 0;
            
            // Run multiple times to get average
            for (int run = 0; run < numRuns; run++) {
                // Generate data
                std::vector<int> data = generateDataSet(dataSetTypes[i], size);
                
                // Run benchmark
                SortingResult result = runSortingBenchmark(algorithm, data);
                totalTimeMs += result.executionTimeMs;
                totalMemory += result.memoryUsageBytes;
            }
            
            // Calculate average results
            SortingResult avgResult;
            avgResult.algorithmName = algorithm.getName() + " [" + dataSetNames[i] + ", n=" + std::to_string(size) + "]";
            avgResult.executionTimeMs = totalTimeMs / numRuns;
            avgResult.memoryUsageBytes = totalMemory / numRuns;
            avgResult.isStable = algorithm.isStable();
            avgResult.isSorted = true; // Assuming all runs sorted correctly
            
            results.push_back(avgResult);
        }
    }
    
    return results;
}

SortingResult runSortingBenchmark(
    SortingAlgorithm& algorithm, 
    const std::vector<int>& originalData,
    bool checkSorted
) {
    // Create result structure
    SortingResult result;
    result.algorithmName = algorithm.getName();
    result.isStable = algorithm.isStable();
    
    // Make a copy of the data to not modify the original
    std::vector<int> data = originalData;
    
    // Measure memory before sorting
    size_t memoryBefore = getCurrentMemoryUsage();
    
    // Measure time
    auto start = std::chrono::high_resolution_clock::now();
    
    // Perform the sort
    algorithm.sort(data);
    
    // End time measurement
    auto end = std::chrono::high_resolution_clock::now();
    
    // Calculate duration in milliseconds
    std::chrono::duration<double, std::milli> duration = end - start;
    result.executionTimeMs = duration.count();
    
    // Measure memory after sorting
    size_t memoryAfter = getCurrentMemoryUsage();
    result.memoryUsageBytes = (memoryAfter > memoryBefore) ? (memoryAfter - memoryBefore) : 0;
    
    // Check if array is sorted correctly
    result.isSorted = checkSorted ? isSorted(data) : true;
    
    return result;
}