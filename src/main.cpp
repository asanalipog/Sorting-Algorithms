#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include "../include/sorting.h"
#include "../include/utils.h"

int main(int argc, char* argv[]) {
    std::cout << "CSE331 - Sorting Algorithm Analysis" << std::endl;
    std::cout << "====================================" << std::endl;
    
    // Create instances of all sorting algorithms
    std::vector<std::unique_ptr<SortingAlgorithm>> algorithms;
    algorithms.push_back(std::make_unique<MergeSort>());
    algorithms.push_back(std::make_unique<HeapSort>());
    algorithms.push_back(std::make_unique<QuickSort>());
    algorithms.push_back(std::make_unique<BubbleSort>());
    algorithms.push_back(std::make_unique<InsertionSort>());
    algorithms.push_back(std::make_unique<SelectionSort>());
    algorithms.push_back(std::make_unique<TournamentSort>());
    algorithms.push_back(std::make_unique<LibrarySort>());
    algorithms.push_back(std::make_unique<CombSort>());
    algorithms.push_back(std::make_unique<TimSort>());
    algorithms.push_back(std::make_unique<CocktailSort>());
    
    // Create a vector of raw pointers for the runAllAlgorithms function
    std::vector<SortingAlgorithm*> algorithmPtrs;
    for (const auto& alg : algorithms) {
        algorithmPtrs.push_back(alg.get());
    }
    
    // Print algorithm complexity information
    std::cout << "\nAlgorithm Complexity Analysis:" << std::endl;
    std::cout << std::left << std::setw(20) << "Algorithm" 
              << std::setw(15) << "Best Case"
              << std::setw(15) << "Average Case"
              << std::setw(15) << "Worst Case"
              << std::setw(15) << "Space"
              << std::setw(10) << "Stable" << std::endl;
    std::cout << std::string(90, '-') << std::endl;
    
    for (const auto& alg : algorithms) {
        std::cout << std::left << std::setw(20) << alg->getName()
                  << std::setw(15) << alg->getBestCase()
                  << std::setw(15) << alg->getAverageCase()
                  << std::setw(15) << alg->getWorstCase()
                  << std::setw(15) << alg->getSpaceComplexity()
                  << std::setw(10) << (alg->isStable() ? "Yes" : "No") << std::endl;
    }
    
    // Define test data sizes
    std::vector<size_t> dataSizes = {1000, 10000, 100000, 1000000};
    
    // Ask user which test to run
    std::cout << "\nChoose a test to run:" << std::endl;
    std::cout << "1. Quick test (small arrays, all algorithms)" << std::endl;
    std::cout << "2. Full benchmark (all sizes, all algorithms, all data types)" << std::endl;
    std::cout << "3. Single algorithm benchmark" << std::endl;
    std::cout << "4. Custom test" << std::endl;
    std::cout << "Enter your choice (1-4): ";
    
    int choice;
    std::cin >> choice;
    
    switch (choice) {
        case 1: {
            // Quick test with a small random array
            std::cout << "\nRunning quick test with random data (size=1000)..." << std::endl;
            std::vector<int> data = generateRandomData(1000);
            std::vector<SortingResult> results = runAllAlgorithms(algorithmPtrs, data);
            printResults(results);
            saveResultsToCSV(results, "quick_test_results.csv");
            break;
        }
        case 2: {
            // Full benchmark
            std::cout << "\nRunning full benchmark..." << std::endl;
            std::cout << "This may take a while for large data sizes." << std::endl;
            
            std::vector<SortingResult> allResults;
            
            // For each data size
            for (size_t size : dataSizes) {
                std::cout << "\nTesting with data size: " << size << std::endl;
                
                // For each data type
                std::vector<DataSetType> dataTypes = {
                    DataSetType::RANDOM, 
                    DataSetType::SORTED_ASC, 
                    DataSetType::SORTED_DESC, 
                    DataSetType::PARTIALLY_SORTED
                };
                
                std::vector<std::string> dataTypeNames = {
                    "Random", "Sorted (Asc)", "Sorted (Desc)", "Partially Sorted"
                };
                
                for (size_t i = 0; i < dataTypes.size(); i++) {
                    std::cout << "  Data type: " << dataTypeNames[i] << std::endl;
                    
                    // Generate data
                    std::vector<int> data = generateDataSet(dataTypes[i], size);
                    
                    // Run all algorithms
                    std::vector<SortingResult> results = runAllAlgorithms(algorithmPtrs, data);
                    
                    // Add dataset info to algorithm names
                    for (auto& result : results) {
                        result.algorithmName += " [" + dataTypeNames[i] + ", n=" + std::to_string(size) + "]";
                    }
                    
                    // Add to all results
                    allResults.insert(allResults.end(), results.begin(), results.end());
                }
            }
            
            // Print and save all results
            printResults(allResults);
            saveResultsToCSV(allResults, "full_benchmark_results.csv");
            break;
        }
        case 3: {
            // Single algorithm benchmark
            std::cout << "\nChoose an algorithm to benchmark:" << std::endl;
            for (size_t i = 0; i < algorithms.size(); i++) {
                std::cout << i + 1 << ". " << algorithms[i]->getName() << std::endl;
            }
            
            std::cout << "Enter your choice (1-" << algorithms.size() << "): ";
            size_t algChoice;
            std::cin >> algChoice;
            
            if (algChoice < 1 || algChoice > algorithms.size()) {
                std::cerr << "Invalid choice!" << std::endl;
                return 1;
            }
            
            // Run benchmark for chosen algorithm
            std::cout << "\nRunning benchmark for " << algorithms[algChoice-1]->getName() << "..." << std::endl;
            std::vector<SortingResult> results = runAlgorithmOnAllDataSets(
                *algorithms[algChoice-1], dataSizes, 10);
            
            printResults(results);
            saveResultsToCSV(results, algorithms[algChoice-1]->getName() + "_benchmark.csv");
            break;
        }
        case 4: {
            // Custom test
            std::cout << "\nEnter data size: ";
            size_t customSize;
            std::cin >> customSize;
            
            std::cout << "Choose data type:" << std::endl;
            std::cout << "1. Random" << std::endl;
            std::cout << "2. Sorted (Ascending)" << std::endl;
            std::cout << "3. Sorted (Descending)" << std::endl;
            std::cout << "4. Partially Sorted" << std::endl;
            std::cout << "Enter your choice (1-4): ";
            
            int dataTypeChoice;
            std::cin >> dataTypeChoice;
            
            DataSetType dataType;
            switch (dataTypeChoice) {
                case 1: dataType = DataSetType::RANDOM; break;
                case 2: dataType = DataSetType::SORTED_ASC; break;
                case 3: dataType = DataSetType::SORTED_DESC; break;
                case 4: dataType = DataSetType::PARTIALLY_SORTED; break;
                default: 
                    std::cerr << "Invalid choice!" << std::endl;
                    return 1;
            }
            
            // Generate data
            std::vector<int> data = generateDataSet(dataType, customSize);
            
            // Run all algorithms
            std::vector<SortingResult> results = runAllAlgorithms(algorithmPtrs, data);
            
            printResults(results);
            saveResultsToCSV(results, "custom_test_results.csv");
            break;
        }
        default:
            std::cerr << "Invalid choice!" << std::endl;
            return 1;
    }
    
    std::cout << "\nAll tests completed successfully." << std::endl;
    return 0;
}