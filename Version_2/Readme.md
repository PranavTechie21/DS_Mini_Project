# Voting Management System - Version 2 (Linked List)

## Overview
This is Version 2 of the Voting Management System implemented using **Singly Linked Lists** as the primary data structure. This version offers dynamic memory allocation and eliminates the fixed-size limitation of the array-based implementation.

## Data Structure Used
- **Singly Linked List**: Dynamic data structure with nodes containing data and a pointer to the next node
- **No Size Limitation**: Can grow dynamically as needed (limited only by available memory)
- **Two Separate Lists**: One for candidates and one for voters

## Features
1. **Add Candidate**: Register new candidates with ID, name, and party
2. **Display Candidates**: View all registered candidates
3. **Register Voter**: Add voters to the system
4. **Display Voters**: View all registered voters and their voting status
5. **Cast Vote**: Vote for a candidate (with voter verification)
6. **Display Results**: View voting results with percentages
7. **Find Winner**: Determine the election winner or detect ties
8. **Delete Candidate**: Remove a candidate from the system
9. **Search Candidate**: Find and display specific candidate information
10. **Voter Tracking**: Track which voters have cast their votes

## File Structure
```
Version2_LinkedList/
├── main.cpp       # Main program with menu interface
├── candidate.h    # Candidate linked list implementation
├── voter.h        # Voter linked list implementation
└── README.md      # This documentation file
```

## Implementation Details

### CandidateNode Structure
```cpp
struct CandidateNode {
    int id;              // Unique candidate identifier
    string name;         // Candidate's name
    string party;        // Political party
    int votes;           // Number of votes received
    CandidateNode* next; // Pointer to next node
};
```

### VoterNode Structure
```cpp
struct VoterNode {
    int id;           // Unique voter identifier
    string name;      // Voter's name
    bool hasVoted;    // Voting status flag
    VoterNode* next;  // Pointer to next node
};
```

### CandidateList Class
Main class managing candidates using linked list:
- `CandidateNode* head`: Pointer to the first candidate
- `int count`: Tracks number of candidates

**Key Methods:**
- `addCandidate(id, name, party)`: Adds candidate at the head of list
- `deleteCandidate(id)`: Removes candidate from list
- `searchCandidate(id)`: Finds and displays specific candidate
- `displayCandidates()`: Traverses and displays all candidates
- `castVote(candidateId)`: Increments vote count
- `displayResults()`: Shows results with percentages
- `findWinner()`: Identifies winner or ties

### VoterList Class
Manages voters using linked list:
- `VoterNode* head`: Pointer to the first voter
- `int count`: Tracks number of voters

**Key Methods:**
- `registerVoter(id, name)`: Registers new voter
- `displayVoters()`: Shows all voters and their status
- `hasVoted(id)`: Checks if voter already voted
- `markAsVoted(id)`: Updates voter status after voting
- `getVotedCount()`: Returns count of voters who voted
- `displayStatistics()`: Shows voter turnout statistics

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
2. Add `main.cpp`, `candidate.h`, and `voter.h` to the project
3. Build and run (F5)

## Usage Instructions

### Running the Program
```bash
./voting
```

### Menu Options
1. **Add Candidate**: Enter candidate ID, name, and party
2. **Display All Candidates**: View all registered candidates
3. **Register Voter**: Add a voter to the system
4. **Display All Voters**: View voter list and voting status
5. **Cast Vote**: Enter voter ID and candidate ID to vote
6. **Display Results**: View detailed voting results
7. **Find Winner**: See election winner or tie status
8. **Delete Candidate**: Remove a candidate by ID
9. **Search Candidate**: Find specific candidate details
10. **Exit**: Close the program

### Example Usage Flow
```
1. Register voters first:
   - Voter ID: 1001, Name: Alice Johnson
   - Voter ID: 1002, Name: Bob Smith
   
2. Add candidates:
   - ID: 101, Name: John Doe, Party: Democratic
   - ID: 102, Name: Jane Smith, Party: Republican
   
3. Cast votes:
   - Voter 1001 votes for candidate 101
   - Voter 1002 votes for candidate 102
   
4. Display results and find winner
```

## Advantages of Linked List Implementation
- ✅ **Dynamic size**: No fixed capacity limit
- ✅ **Efficient insertion**: O(1) insertion at head
- ✅ **Efficient deletion**: O(n) but no shifting needed
- ✅ **Memory efficient**: Only allocates memory for actual elements
- ✅ **Flexible**: Easy to add/remove elements
- ✅ **No wasted space**: Uses exactly the memory needed

## Limitations of Linked List Implementation
- ❌ **Slower search**: O(n) linear search required
- ❌ **No random access**: Cannot access elements by index
- ❌ **Extra memory**: Requires storage for next pointers
- ❌ **Cache unfriendly**: Non-contiguous memory allocation
- ❌ **No backward traversal**: Singly linked (only forward)

## Time Complexity Analysis
- **Add Candidate/Voter**: O(1) - insertion at head
- **Display Candidates/Voters**: O(n) - traverse entire list
- **Cast Vote**: O(n) - linear search to find candidate
- **Delete Candidate**: O(n) - search and remove
- **Search Candidate**: O(n) - linear search
- **Display Results**: O(n) - traverse all candidates
- **Find Winner**: O(n) - scan all candidates

## Space Complexity
- **O(n + m)** where:
  - n = number of candidates
  - m = number of voters
- Dynamic allocation based on actual usage
- Additional O(n + m) for next pointers

## Key Improvements Over Version 1
1. **No Size Limit**: Can handle unlimited candidates and voters
2. **Voter Management**: Separate voter tracking system
3. **Voter Verification**: Prevents double voting
4. **Delete Functionality**: Can remove candidates dynamically
5. **Search Functionality**: Find specific candidates quickly
6. **Memory Efficiency**: Only uses memory for actual data

## Sample Output
```
========================================
  VOTING MANAGEMENT SYSTEM (Linked List)
========================================
1. Add Candidate
2. Display All Candidates
3. Register Voter
4. Display All Voters
5. Cast Vote
6. Display Results
7. Find Winner
8. Delete Candidate
9. Search Candidate
10. Exit
========================================

================================================================================
ID        Name                     Party                    Votes     
================================================================================
102       Jane Smith               Republican               3         
101       John Doe                 Democratic               5         
================================================================================
Total Candidates: 2

======================================================================
Voter ID       Name                           Status         
======================================================================
1002          Bob Smith                      Voted          
1001          Alice Johnson                  Voted          
======================================================================
Total Registered Voters: 2
```

## Memory Management
- **Automatic Cleanup**: Destructors free all allocated memory
- **No Memory Leaks**: Proper deletion of nodes
- **Safe Operations**: Checks for null pointers

## Error Handling
- Duplicate candidate/voter IDs are rejected
- Invalid menu choices prompt re-entry
- Voting for non-existent candidates shows error
- Double voting prevention
- Null pointer checks throughout
- Input validation for non-numeric entries

## Testing Recommendations
1. Test adding multiple candidates and voters
2. Test duplicate ID rejection for both candidates and voters
3. Test voting with valid and invalid voter IDs
4. Test double voting prevention
5. Test candidate deletion (head, middle, tail)
6. Test search functionality
7. Test with no candidates/voters
8. Test tie scenarios
9. Test memory cleanup (use valgrind on Linux)

## Advanced Features
- **Voter Turnout**: Track percentage of voters who participated
- **Voter Statistics**: Display voting participation metrics
- **Dynamic Operations**: Add/remove candidates during election
- **Status Tracking**: Monitor which voters have voted

## Performance Considerations
- Insert candidates at head for O(1) insertion
- Linear search is acceptable for small to medium datasets
- For large datasets, consider Version 3 (BST) for better search performance
- Memory overhead per node: ~8 bytes (pointer)

## Future Improvements (See Other Versions)
- **Version 3**: Use BST for O(log n) search operations
- **Version 4**: Use Heap for automatic winner tracking
- **Version 5**: Use Graph for complex relationships
- **Version 6**: Complete system with all features

## Requirements
- C++11 or higher
- Standard C++ libraries (iostream, string, iomanip, limits)
- Sufficient memory for dynamic allocation

## Comparison with Version 1
| Feature | Version 1 (Array) | Version 2 (Linked List) |
|---------|------------------|------------------------|
| Size Limit | Fixed (100) | Dynamic (unlimited) |
| Memory | Pre-allocated | Dynamic |
| Insertion | O(n) check | O(1) at head |
| Deletion | Not supported | O(n) |
| Search | O(n) | O(n) |
| Voter Tracking | No | Yes |

## Author Notes
This version demonstrates linked list manipulation and is ideal for scenarios where:
- The number of candidates/voters is unknown
- Dynamic addition/removal is needed
- Memory efficiency is important
- Fixed size limitations are problematic

## License
Educational purposes - Free to use and modify

---
**Version**: 2.0  
**Data Structure**: Singly Linked List  
**Last Updated**: 2025
