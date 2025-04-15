#include "../include/sorting.h"
#include <limits>
#include <cmath>

void TournamentSort::sort(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return;
    
    // Create result array (output array)
    std::vector<int> result(n);
    
    // Create tournament tree
    // The tree size is 2^(ceil(log2(n))+1)-1
    int treeHeight = static_cast<int>(std::ceil(std::log2(n)));
    int treeSize = (1 << (treeHeight + 1)) - 1;
    int leafStart = (1 << treeHeight) - 1;
    
    std::vector<int> tree(treeSize, std::numeric_limits<int>::max());
    
    // Initialize the leaf nodes
    for (int i = 0; i < n; i++) {
        tree[leafStart + i] = arr[i];
    }
    
    // Build the initial tournament tree
    buildTournamentTree(tree, leafStart);
    
    // Extract elements one by one
    for (int i = 0; i < n; i++) {
        // Get the minimum element (winner of tournament)
        result[i] = tree[0];
        
        // Replace the winner with infinity and rebuild the tree
        int idx = 0;
        while (idx < leafStart) {
            // Find which child has the minimum value
            int leftChild = 2 * idx + 1;
            int rightChild = 2 * idx + 2;
            
            if (tree[leftChild] == result[i]) {
                // Replace with infinity
                tree[leftChild] = std::numeric_limits<int>::max();
                idx = leftChild;
            } else {
                // Replace with infinity
                tree[rightChild] = std::numeric_limits<int>::max();
                idx = rightChild;
            }
        }
        
        // Find the leaf node that had the minimum value
        tree[idx] = std::numeric_limits<int>::max();
        
        // Rebuild the tree from that leaf node upward
        rebuildTournamentTree(tree, idx);
    }
    
    // Copy sorted array back to original
    for (int i = 0; i < n; i++) {
        arr[i] = result[i];
    }
}

void TournamentSort::buildTournamentTree(std::vector<int>& tree, int leafStart) {
    // Start from one level above leaves and go up to the root
    for (int i = leafStart - 1; i >= 0; i--) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        
        tree[i] = std::min(tree[leftChild], tree[rightChild]);
    }
}

void TournamentSort::rebuildTournamentTree(std::vector<int>& tree, int index) {
    // Rebuild the tournament tree from a leaf node upward
    while (index > 0) {
        int parent = (index - 1) / 2;
        int sibling = (index % 2 == 0) ? index - 1 : index + 1;
        
        tree[parent] = std::min(tree[index], tree[sibling]);
        index = parent;
    }
}