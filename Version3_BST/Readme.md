# Voting Management System - Version 3 (Binary Search Tree)

## Overview
This is Version 3 of the Voting Management System implemented using a **Binary Search Tree (BST)** as the primary data structure. This version provides efficient searching, insertion, and maintains candidates in sorted order by ID.

## Data Structure Used
- **Binary Search Tree (BST)**: A hierarchical tree structure where each node has at most two children
- **Ordering Property**: For each node, all left subtree values < node value < all right subtree values
- **Dynamic Size**: No fixed capacity limit
- **Self-Organizing**: Data naturally organized for efficient operations

## Features
1. **Add Candidate**: Insert candidates maintaining BST property (O(log n) average)
2. **Display Candidates (In-Order)**: View candidates sorted by ID automatically
3. **Display Candidates (Pre-Order)**: View tree structure in pre-order traversal
4. **Display Candidates (Post-Order)**: View tree structure in post-order traversal
5. **Cast Vote**: Vote for candidates with efficient search
6. **Display Results**: View voting results with percentages
7. **Find Winner**: Determine election winner or detect ties
8. **Delete Candidate**: Remove candidates while maintaining BST property
9. **Search Candidate**: Find specific candidates efficiently (O(log n) average)
10. **Find Minimum**: Get candidate with smallest ID (leftmost node)
11. **Find Maximum**: Get candidate with largest ID (rightmost node)
12. **Count Candidates**: Get total number of candidates
13. **Tree Height**: Display the height of the BST
14. **Three Traversal Methods**: In-order, Pre-order, Post-order

## File Structure
```
Version3_BST/
├── main.cpp       # Main program with menu interface
├── bst.h          # Binary Search Tree implementation
├── candidate.h    # Candidate structure
└── README.md      # This documentation file
```

## Implementation Details

### BSTNode Structure
```cpp
struct BSTNode {
    Candidate data;    // Candidate information
    BSTNode* left;     // Pointer to left child
    BSTNode* right;    // Pointer to right child
};
```

### Candidate Structure
```cpp
struct Candidate {
    int id;           // Unique identifier (BST key)
    string name;      // Candidate name
    string party;     // Political party
    int votes;        // Vote count
};
```

### CandidateBST Class
Main class managing candidates using BST:
- `BSTNode* root`: Pointer to root of tree
- `int totalCandidates`: Count of nodes

**Key Methods:**
- `insert(id, name, party)`: Add candidate maintaining BST property
- `searchCandidate(id)`: Find candidate using binary search
- `deleteCandidate(id)`: Remove candidate (handles 3 cases)
- `castVote(id)`: Increment vote count for candidate
- `displayInOrder()`: Show candidates sorted by ID (ascending)
- `displayPreOrder()`: Root → Left → Right traversal
- `displayPostOrder()`: Left → Right → Root traversal
- `findMinimum()`: Get leftmost node (smallest ID)
- `findMaximum()`: Get rightmost node (largest ID)
- `getHeight()`: Calculate tree height
- `countNodes()`: Count total nodes recursively
- `displayResults()`: Show results in sorted order
- `findWinner()`: Identify winner from all candidates

## Tree Traversal Methods

### In-Order Traversal (Left → Root → Right)
- Visits nodes in ascending order of IDs
- **Use Case**: Display candidates sorted by ID
- **Output**: Always sorted ascending

### Pre-Order Traversal (Root → Left → Right)
- Visits root before children
- **Use Case**: Create copy of tree, save tree structure
- **Output**: Root appears first

### Post-Order Traversal (Left → Right → Root)
- Visits root after children
- **Use Case**: Delete tree, evaluate expressions
- **Output**: Root appears last

## BST Deletion Cases

### Case 1: Node with No Children (Leaf)
Simply remove the node and update parent pointer

### Case 2: Node with One Child
Remove node and connect parent to child directly

### Case 3: Node with Two Children
1. Find in-order successor (minimum in right subtree)
2. Replace node's data with successor's data
3. Delete successor node

## Compilation Instructions

### Using g++
```bash
g++ -o voting main.cpp -std=c++11
```

### Using clang++
```bash
clang++ -o voting main.cpp -std=c++11
```

### Using Visual Studio (Windows)
1. Create a new C++ Console Application project
2. Add `main.cpp`, `bst.h`, and `candidate.h` to the project
3. Build and run (F5)

## Usage Instructions

### Running the Program
```bash
./voting
```

### Menu Options (14 Total)
1. **Add Candidate**: Insert new candidate into BST
2. **Display All Candidates (In-Order)**: Sorted by ID
3. **Display Candidates (Pre-Order)**: Tree structure view
4. **Display Candidates (Post-Order)**: Alternative tree view
5. **Cast Vote**: Vote for a candidate
6. **Display Results**: Show voting results
7. **Find Winner**: Announce winner
8. **Delete Candidate**: Remove from tree
9. **Search Candidate**: Find specific candidate
10. **Find Minimum ID**: Get smallest ID
11. **Find Maximum ID**: Get largest ID
12. **Count Total Candidates**: Node count
13. **Display Tree Height**: Tree depth
14. **Exit**: Close program

### Example Usage Flow
```
1. Add candidates (inserted in BST order):
   - ID: 105, Name: Alice, Party: Independent
   - ID: 102, Name: Bob, Party: Democratic
   - ID: 108, Name: Carol, Party: Republican
   
   Tree Structure:
         105
        /   \
      102   108
      
2. Display In-Order (sorted): 102, 105, 108
3. Search for candidate 102 (efficient search)
4. Cast votes
5. Find winner
6. Delete candidate if needed
```

## Advantages of BST Implementation
- ✅ **Fast Search**: O(log n) average time for balanced tree
- ✅ **Fast Insertion**: O(log n) average time
- ✅ **Sorted Output**: In-order traversal gives sorted data
- ✅ **Dynamic Size**: No fixed capacity
- ✅ **Efficient Min/Max**: O(log n) to find extremes
- ✅ **Natural Organization**: Data self-organizes hierarchically
- ✅ **Multiple Views**: Three traversal methods
- ✅ **Memory Efficient**: Only stores actual data

## Limitations of BST Implementation
- ❌ **Can become unbalanced**: Worst case O(n) if data inserted in sorted order
- ❌ **No guaranteed balance**: Performance depends on insertion order
- ❌ **Complex deletion**: Three cases to handle
- ❌ **More memory**: Two pointers per node vs one in linked list
- ❌ **Recursive overhead**: Most operations use recursion
- ⚠️ **Best case**: Balanced tree (log n height)
- ⚠️ **Worst case**: Skewed tree (n height) - becomes linked list

## Time Complexity Analysis (Average Case - Balanced BST)
- **Insert**: O(log n) - binary search path to leaf
- **Search**: O(log n) - binary search through tree
- **Delete**: O(log n) - search + restructure
- **Cast Vote**: O(log n) - search to find candidate
- **In-Order Traversal**: O(n) - visit all nodes
- **Find Min/Max**: O(log n) - follow left/right path
- **Count Nodes**: O(n) - visit all nodes
- **Get Height**: O(n) - examine all paths
- **Find Winner**: O(n) - check all candidates

## Time Complexity Analysis (Worst Case - Skewed BST)
- **Insert**: O(n) - linear search in skewed tree
- **Search**: O(n) - degrades to linear search
- **Delete**: O(n) - linear search + restructure

## Space Complexity
- **O(n)** for n candidates
- **Additional O(n)** for two pointers per node
- **Recursion Stack**: O(h) where h = tree height
  - Balanced: O(log n)
  - Skewed: O(n)

## BST vs Previous Versions Comparison

| Feature | Array (V1) | Linked List (V2) | BST (V3) |
|---------|-----------|------------------|----------|
| Search | O(n) | O(n) | O(log n) avg |
| Insert | O(n) | O(1) head | O(log n) avg |
| Delete | ❌ | O(n) | O(log n) avg |
| Sorted Display | O(n log n) | O(n log n) | O(n) free |
| Min/Max | O(n) | O(n) | O(log n) |
| Memory | Pre-allocated | Dynamic | Dynamic |
| Structure | Linear | Linear | Hierarchical |

## Key Improvements Over Version 2
1. **Faster Search**: O(log n) vs O(n) for balanced tree
2. **Sorted Output**: In-order traversal automatically sorted
3. **Efficient Min/Max**: O(log n) to find extremes
4. **Multiple Traversals**: Three different tree views
5. **Tree Analytics**: Height calculation, node counting
6. **Hierarchical Organization**: Better logical structure

## Sample Output
```
========================================
     VOTING MANAGEMENT SYSTEM (BST)
========================================

Candidates (In-Order - Sorted by ID):
================================================================================
ID: 101 | Name: Alice Johnson | Party: Democratic | Votes: 5
ID: 103 | Name: Bob Smith | Party: Republican | Votes: 3
ID: 107 | Name: Carol Davis | Party: Independent | Votes: 2
================================================================================
Total Candidates: 3

Tree Height: 1
(Balanced tree with root 103, left child 101, right child 107)
```

## BST Balance Considerations

### Best Case: Balanced Tree
```
     105
    /   \
  102   108
  /       \
101       110
```
Height: log₂(n) ≈ 2 for 5 nodes

### Worst Case: Skewed Tree (Insert in sorted order)
```
101
  \
  102
    \
    105
      \
      108
        \
        110
```
Height: n-1 = 4 for 5 nodes (degrades to linked list)

### Recommendation
- Insert candidates in random or mixed order
- For production, use **AVL Tree** or **Red-Black Tree** (self-balancing)
- Monitor tree height with `getHeight()` function

## Error Handling
- Duplicate IDs rejected during insertion
- Search for non-existent candidates returns error
- Delete on empty tree handled gracefully
- Null pointer checks throughout
- Invalid menu choices prompt re-entry
- Recursive functions have base cases

## Testing Recommendations
1. Test with various insertion orders:
   - Random: Good balance
   - Sorted ascending: Creates right-skewed tree
   - Sorted descending: Creates left-skewed tree
2. Test all three traversals
3. Test deletion of all three cases:
   - Leaf nodes
   - Nodes with one child
   - Nodes with two children
4. Test min/max functions
5. Verify sorted output in in-order traversal
6. Test tree height with different insertion patterns
7. Test with empty tree

## Advanced Features
- **Multiple Traversals**: See tree structure different ways
- **Tree Analytics**: Height and node count
- **Min/Max Queries**: Efficient extreme value finding
- **Automatic Sorting**: In-order traversal gives sorted data
- **Recursive Design**: Elegant and maintainable code

## Performance Tips
1. **Insert in Random Order**: Helps maintain balance
2. **Monitor Height**: Use `getHeight()` to check balance
3. **Balanced Input**: Mix high and low IDs during insertion
4. **Avoid Sorted Input**: Prevents skewed tree formation

## Memory Management
- **Automatic Cleanup**: Destructor recursively frees all nodes
- **No Memory Leaks**: Post-order traversal for deletion
- **Dynamic Allocation**: Memory allocated as needed
- **Safe Deletion**: Three-case deletion preserves tree structure

## Use Cases Best Suited for BST
✅ Frequent searches by ID  
✅ Need for sorted output  
✅ Finding min/max IDs quickly  
✅ Dynamic add/remove operations  
✅ Moderate dataset size (hundreds to thousands)  
✅ Range queries (future enhancement)  

## Future Improvements
- **AVL Tree**: Self-balancing BST (Version enhancement)
- **Red-Black Tree**: Another self-balancing option
- **B-Tree**: For very large datasets
- **Range Queries**: Find candidates in ID range
- **Rank Operations**: Find k-th smallest/largest

## Comparison with Future Versions
- **Version 4 (Heap)**: Better for frequent "find winner" operations
- **Version 5 (Graph)**: Better for relationship modeling
- **Version 6 (Complete)**: Combines multiple data structures

## Requirements
- C++11 or higher
- Standard C++ libraries (iostream, string, iomanip, algorithm)
- Sufficient memory for dynamic allocation
- Understanding of tree concepts helpful

## Learning Objectives
This version teaches:
- Binary Search Tree concepts
- Tree traversals (in-order, pre-order, post-order)
- Recursive algorithms
- Tree node deletion (three cases)
- BST balance considerations
- Hierarchical data organization

## Author Notes
This version demonstrates the power of BST for searching and maintaining sorted data. While linked lists are simpler, BSTs offer significant performance improvements for search-heavy applications. However, be aware of balance issues and consider self-balancing trees for production systems.

## License
Educational purposes - Free to use and modify

---
**Version**: 3.0  
**Data Structure**: Binary Search Tree (BST)  
**Last Updated**: 2025  
**Complexity**: O(log n) average, O(n) worst case
