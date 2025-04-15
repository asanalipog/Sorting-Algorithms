#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <string>
#include <chrono>
#include <functional>

// Common interface for all sorting algorithms
class SortingAlgorithm {
public:
    virtual ~SortingAlgorithm() = default;
    
    // Main sorting function
    virtual void sort(std::vector<int>& arr) = 0;
    
    // Get algorithm name
    virtual std::string getName() const = 0;
    
    // Check if algorithm is stable
    virtual bool isStable() const = 0;
    
    // Time complexity information
    virtual std::string getBestCase() const = 0;
    virtual std::string getAverageCase() const = 0;
    virtual std::string getWorstCase() const = 0;
    
    // Space complexity information
    virtual std::string getSpaceComplexity() const = 0;
};

// Concrete implementations of sorting algorithms
class MergeSort : public SortingAlgorithm {
public:
    void sort(std::vector<int>& arr) override;
    std::string getName() const override { return "Merge Sort"; }
    bool isStable() const override { return true; }
    std::string getBestCase() const override { return "O(n log n)"; }
    std::string getAverageCase() const override { return "O(n log n)"; }
    std::string getWorstCase() const override { return "O(n log n)"; }
    std::string getSpaceComplexity() const override { return "O(n)"; }

private:
    void mergeSort(std::vector<int>& arr, int left, int right);
    void merge(std::vector<int>& arr, int left, int mid, int right);
};

class HeapSort : public SortingAlgorithm {
public:
    void sort(std::vector<int>& arr) override;
    std::string getName() const override { return "Heap Sort"; }
    bool isStable() const override { return false; }
    std::string getBestCase() const override { return "O(n log n)"; }
    std::string getAverageCase() const override { return "O(n log n)"; }
    std::string getWorstCase() const override { return "O(n log n)"; }
    std::string getSpaceComplexity() const override { return "O(1)"; }

private:
    void heapify(std::vector<int>& arr, int n, int i);
};

class QuickSort : public SortingAlgorithm {
public:
    void sort(std::vector<int>& arr) override;
    std::string getName() const override { return "Quick Sort"; }
    bool isStable() const override { return false; }
    std::string getBestCase() const override { return "O(n log n)"; }
    std::string getAverageCase() const override { return "O(n log n)"; }
    std::string getWorstCase() const override { return "O(n²)"; }
    std::string getSpaceComplexity() const override { return "O(log n)"; }

private:
    void quickSort(std::vector<int>& arr, int low, int high);
    int partition(std::vector<int>& arr, int low, int high);
};

class BubbleSort : public SortingAlgorithm {
public:
    void sort(std::vector<int>& arr) override;
    std::string getName() const override { return "Bubble Sort"; }
    bool isStable() const override { return true; }
    std::string getBestCase() const override { return "O(n)"; }
    std::string getAverageCase() const override { return "O(n²)"; }
    std::string getWorstCase() const override { return "O(n²)"; }
    std::string getSpaceComplexity() const override { return "O(1)"; }
};

class InsertionSort : public SortingAlgorithm {
public:
    void sort(std::vector<int>& arr) override;
    std::string getName() const override { return "Insertion Sort"; }
    bool isStable() const override { return true; }
    std::string getBestCase() const override { return "O(n)"; }
    std::string getAverageCase() const override { return "O(n²)"; }
    std::string getWorstCase() const override { return "O(n²)"; }
    std::string getSpaceComplexity() const override { return "O(1)"; }
};

class SelectionSort : public SortingAlgorithm {
public:
    void sort(std::vector<int>& arr) override;
    std::string getName() const override { return "Selection Sort"; }
    bool isStable() const override { return false; }
    std::string getBestCase() const override { return "O(n²)"; }
    std::string getAverageCase() const override { return "O(n²)"; }
    std::string getWorstCase() const override { return "O(n²)"; }
    std::string getSpaceComplexity() const override { return "O(1)"; }
};
class LibrarySort : public SortingAlgorithm {
    public:
        void sort(std::vector<int>& arr) override;
        std::string getName() const override { return "Library Sort"; }
        bool isStable() const override { return true; }
        std::string getBestCase() const override { return "O(n)"; }
        std::string getAverageCase() const override { return "O(n log n)"; }
        std::string getWorstCase() const override { return "O(n²)"; }
        std::string getSpaceComplexity() const override { return "O(n)"; }
    
    private:
        void rebalance(std::vector<std::pair<int, bool>>& library, size_t count);
    };
    
    class TimSort : public SortingAlgorithm {
    public:
        void sort(std::vector<int>& arr) override;
        std::string getName() const override { return "Tim Sort"; }
        bool isStable() const override { return true; }
        std::string getBestCase() const override { return "O(n)"; }
        std::string getAverageCase() const override { return "O(n log n)"; }
        std::string getWorstCase() const override { return "O(n log n)"; }
        std::string getSpaceComplexity() const override { return "O(n)"; }
    
    private:
        void insertionSort(std::vector<int>& arr, int left, int right);
        void merge(std::vector<int>& arr, int left, int mid, int right);
    };
    
    class CocktailSort : public SortingAlgorithm {
        public:
            void sort(std::vector<int>& arr) override;  // Declaration of sort function
            std::string getName() const override { return "Cocktail Shaker Sort"; }
            bool isStable() const override { return true; }
            std::string getBestCase() const override { return "O(n)"; }
            std::string getAverageCase() const override { return "O(n²)"; }
            std::string getWorstCase() const override { return "O(n²)"; }
            std::string getSpaceComplexity() const override { return "O(1)"; }
        };
        
    
    class CombSort : public SortingAlgorithm {
    public:
        void sort(std::vector<int>& arr) override;
        std::string getName() const override { return "Comb Sort"; }
        bool isStable() const override { return false; }
        std::string getBestCase() const override { return "O(n log n)"; }
        std::string getAverageCase() const override { return "O(n²/2^p)"; }
        std::string getWorstCase() const override { return "O(n²)"; }
        std::string getSpaceComplexity() const override { return "O(1)"; }
    };
    
class TournamentSort : public SortingAlgorithm {
    public:
        void sort(std::vector<int>& arr) override;
        std::string getName() const override { return "Tournament Sort"; }
        bool isStable() const override { return false; }
        std::string getBestCase() const override { return "O(n log n)"; }
        std::string getAverageCase() const override { return "O(n log n)"; }
        std::string getWorstCase() const override { return "O(n log n)"; }
        std::string getSpaceComplexity() const override { return "O(n)"; }
    
    private:
        void buildTournamentTree(std::vector<int>& tree, int leafStart);
        void rebuildTournamentTree(std::vector<int>& tree, int index);
    };


// Helper struct to store performance metrics
struct SortingResult {
    std::string algorithmName;
    double executionTimeMs;
    size_t memoryUsageBytes;
    bool isStable;
    bool isSorted;
};

// Run benchmark on a specific algorithm with the given data
SortingResult runSortingBenchmark(
    SortingAlgorithm& algorithm, 
    const std::vector<int>& originalData,
    bool checkSorted = true
);

#endif // SORTING_H