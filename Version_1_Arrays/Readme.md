# Voting Management System - Version 1 (Arrays)

## Overview
This is Version 1 of the Voting Management System implemented using **Arrays** as the primary data structure. The system allows users to manage candidates, cast votes, and view election results.

## Data Structure Used
- **Arrays**: Fixed-size array to store candidate information
- **Maximum Capacity**: 100 candidates (defined by `MAX_CANDIDATES`)

## Features
1. **Add Candidate**: Register new candidates with ID, name, and party
2. **Display Candidates**: View all registered candidates
3. **Cast Vote**: Vote for a candidate by their ID
4. **Display Results**: View voting results with vote counts and percentages
5. **Find Winner**: Determine the election winner or detect ties
6. **Input Validation**: Prevents duplicate IDs and handles invalid inputs

## File Structure
```
Version1_Arrays/
├── main.cpp       # Main program with menu interface
├── voting.h       # Header file with VotingSystem class and Candidate struct
└── README.md      # This documentation file
```

## Implementation Details

### Candidate Structure
```cpp
struct Candidate {
    int id;           // Unique candidate identifier
    string name;      // Candidate's name
    string party;     // Political party
    int votes;        // Number of votes received
};
```

### VotingSystem Class
The main class uses a fixed-size array to store candidates:
- `Candidate candidates[MAX_CANDIDATES]`: Array to store all candidates
- `int candidateCount`: Tracks the number of registered candidates

### Key Methods
- `addCandidate(id, name, party)`: Adds a new candidate to the system
- `displayCandidates()`: Displays all registered candidates in a formatted table
- `castVote(candidateId)`: Increments vote count for specified candidate
- `displayResults()`: Shows voting results with percentages
- `findWinner()`: Identifies the winner or detects ties

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
2. Add `main.cpp` and `voting.h` to the project
3. Build and run (F5)

## Usage Instructions

### Running the Program
```bash
./voting
```

### Menu Options
1. **Add Candidate**: Enter candidate ID, name, and party affiliation
2. **Display All Candidates**: View current candidates and their vote counts
3. **Cast Vote**: Enter candidate ID to cast a vote
4. **Display Results**: View detailed results with percentages
5. **Find Winner**: See who won or if there's a tie
6. **Exit**: Close the program

### Example Usage Flow
```
1. Add candidates first
   - ID: 101, Name: John Doe, Party: Democratic
   - ID: 102, Name: Jane Smith, Party: Republican
   
2. Cast votes
   - Vote for candidate 101
   - Vote for candidate 102
   - Vote for candidate 101
   
3. Display results to see vote distribution

4. Find winner to see who has the most votes
```

## Advantages of Array Implementation
- ✅ **Simple and straightforward**: Easy to understand and implement
- ✅ **Fast access**: O(1) access time by index
- ✅ **Memory efficient**: Contiguous memory allocation
- ✅ **No dynamic memory management**: No need for pointers or manual memory management

## Limitations of Array Implementation
- ❌ **Fixed size**: Cannot exceed MAX_CANDIDATES (100)
- ❌ **Inefficient insertion**: Finding candidate by ID requires linear search O(n)
- ❌ **Wasted space**: Memory allocated even if not all slots are used
- ❌ **No dynamic resizing**: Cannot grow beyond initial capacity

## Time Complexity Analysis
- **Add Candidate**: O(n) - needs to check for duplicate IDs
- **Display Candidates**: O(n) - iterates through all candidates
- **Cast Vote**: O(n) - linear search to find candidate by ID
- **Display Results**: O(n) - iterates through all candidates
- **Find Winner**: O(n) - scans all candidates to find maximum votes

## Space Complexity
- **O(n)** where n = MAX_CANDIDATES (100)
- Fixed space regardless of actual number of candidates

## Sample Output
```
========================================
   VOTING MANAGEMENT SYSTEM (Arrays)
========================================
1. Add Candidate
2. Display All Candidates
3. Cast Vote
4. Display Results
5. Find Winner
6. Exit
========================================

================================================================================
ID        Name                     Party                    Votes     
================================================================================
101       John Doe                 Democratic               5         
102       Jane Smith               Republican               3         
================================================================================

========================================
              WINNER ANNOUNCEMENT
========================================
Winner: John Doe
Party: Democratic
Total Votes: 5
========================================
```

## Error Handling
- Duplicate candidate IDs are rejected
- Invalid menu choices prompt re-entry
- Voting for non-existent candidates shows error message
- System full message when MAX_CANDIDATES reached
- Input validation for non-numeric entries

## Future Improvements (See Other Versions)
- **Version 2**: Use Linked List for dynamic sizing
- **Version 3**: Use BST for faster searching O(log n)
- **Version 4**: Use Heap/Priority Queue for automatic winner tracking

## Testing Recommendations
1. Test adding candidates up to the maximum limit
2. Test duplicate ID rejection
3. Test voting for non-existent candidates
4. Test tie scenarios with equal votes
5. Test results with zero votes
6. Test invalid menu inputs

## Requirements
- C++11 or higher
- Standard C++ libraries (iostream, string, iomanip, limits)

## Author Notes
This version demonstrates basic array manipulation and is suitable for learning fundamental data structures. For production systems with large-scale requirements, consider using dynamic data structures (Version 2, 3, or 4).

## License
Educational purposes - Free to use and modify

---
**Version**: 1.0  
**Data Structure**: Arrays  
**Last Updated**: 2025
