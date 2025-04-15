#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <random>
#include "sorting.h"

// Generate test data
std::vector<int> generateRandomData(size_t size, int min = 0, int max = 1000);
std::vector<int> generateSortedData(size_t size, bool ascending = true);
std::vector<int> generatePartiallySortedData(size_t size, double sortedRatio = 0.7);

// Validate if array is sorted
bool isSorted(const std::vector<int>& arr, bool ascending = true);

// Print array (for debugging)
void printArray(const std::vector<int>& arr, size_t limit = 10);

// Get current memory usage (platform dependent)
size_t getCurrentMemoryUsage();

// Data set type enum
enum class DataSetType {
    RANDOM,
    SORTED_ASC,
    SORTED_DESC,
    PARTIALLY_SORTED
};

// Generate data set of specified type and size
std::vector<int> generateDataSet(DataSetType type, size_t size);

// Pretty-print the results
void printResults(const std::vector<SortingResult>& results);

// Save results to CSV file
void saveResultsToCSV(const std::vector<SortingResult>& results, const std::string& filename);

// Run all algorithms on a specific data set
std::vector<SortingResult> runAllAlgorithms(
    const std::vector<SortingAlgorithm*>& algorithms,
    const std::vector<int>& data
);

// Run a specific algorithm on all data set types with multiple runs
std::vector<SortingResult> runAlgorithmOnAllDataSets(
    SortingAlgorithm& algorithm,
    const std::vector<size_t>& sizes,
    int numRuns = 10
);

#endif // UTILS_H