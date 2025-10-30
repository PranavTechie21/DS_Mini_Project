# 🗳️ Voting Management System - Version 4

## Priority-Based Voting System (Heap & Priority Queue)

---

## 📋 Overview

Version 4 implements a **priority-based voting system** using **Max Heap** and **Hash Tables** to provide real-time rankings and efficient vote management with weighted voting support.

### Key Enhancement over Version 3:
- ✅ **Real-time Rankings** using Max Heap
- ✅ **O(1) Leader Access** 
- ✅ **Weighted Voting System** (Normal vs VIP voters)
- ✅ **Priority Queue** for candidate ranking
- ✅ **Hash Map** for O(1) lookups
- ✅ **Live Leaderboard** updates

---

## 🎯 Features

### 1. **Priority Queue Implementation**
- Max Heap for automatic candidate ranking
- Real-time updates after each vote
- Top-K candidates retrieval in O(k log n)

### 2. **Weighted Voting System**
- **Normal Voters**: 1.0x vote weight
- **VIP Voters**: 2.0x vote weight
- Dual counting system (actual votes + weighted votes)

### 3. **Hash Table Integration**
- O(1) voter lookup and validation
- O(1) candidate search
- Fast duplicate detection

### 4. **Real-time Analytics**
- Instant leader identification
- Live leaderboard with percentages
- Voting statistics and turnout tracking

---

## 🏗️ Data Structures Used

### 1. **Max Heap (Priority Queue)**
```cpp
priority_queue<Candidate> candidateHeap;
```
- **Purpose**: Maintain real-time candidate rankings
- **Operations**: 
  - Get Max (Leader): O(1)
  - Insert: O(log n)
  - Extract Max: O(log n)
- **Advantage**: Always know the current leader instantly

### 2. **Hash Table (Unordered Map)**
```cpp
unordered_map<int, Candidate*> candidateMap;
unordered_map<int, Voter*> voterMap;
```
- **Purpose**: O(1) lookups for voters and candidates
- **Operations**:
  - Insert: O(1) average
  - Search: O(1) average
  - Delete: O(1) average
- **Advantage**: Instant validation during vote casting

### 3. **Vector**
```cpp
vector<Candidate*> allCandidates;
```
- **Purpose**: Maintain list of all candidates for iteration
- **Advantage**: Easy traversal and heap rebuilding

---

## 📊 Time Complexity Analysis

| Operation | Data Structure | Time Complexity |
|-----------|---------------|-----------------|
| Register Voter | Hash Map | O(1) average |
| Add Candidate | Hash Map + Heap | O(log n) |
| Cast Vote | Hash Map + Heap | O(log n) |
| Get Current Leader | Max Heap | O(1) |
| Search Voter | Hash Map | O(1) average |
| Search Candidate | Hash Map | O(1) average |
| Top K Candidates | Heap | O(k log n) |
| Display Leaderboard | Heap | O(n log n) |

---

## 🔧 File Structure

```
Version_4_Heap/
│
├── main.cpp              # Main program with menu
├── candidate.h           # Candidate structure and operations
├── voter.h               # Voter structure and operations
├── voting_system.h       # Core voting system class
└── README.md            # This file
```

---

## 💻 How to Compile and Run

### Compilation:
```bash
g++ -std=c++11 -o voting_v4 main.cpp
```

### Run:
```bash
./voting_v4
```

### For Windows:
```bash
g++ -std=c++11 -o voting_v4.exe main.cpp
voting_v4.exe
```

---

## 📖 Usage Guide

### 1. **Add Candidates**
```
Choose Option 1
Enter Candidate ID: 101
Enter Name: John Doe
Enter Party: Democratic Party
```

### 2. **Register Voters**
```
Choose Option 2
Enter Voter ID: 1001
Enter Name: Alice Smith
Enter Age: 25
Enter Type: 1 (Normal) or 2 (VIP)
```

### 3. **Cast Vote**
```
Choose Option 3
Enter Voter ID: 1001
Enter Candidate ID: 101
```

### 4. **View Current Leader**
```
Choose Option 4
Displays: Current leading candidate with vote count
```

### 5. **View Leaderboard**
```
Choose Option 6
Displays: All candidates ranked by weighted votes
```

---

## 🎮 Menu Options

```
1.  Add Candidate
2.  Register Voter (Normal/VIP)
3.  Cast Vote
4.  Get Current Leader (O(1))
5.  Display Top N Candidates
6.  Display Real-time Leaderboard
7.  Display All Candidates
8.  Display All Voters
9.  Search Candidate
10. Search Voter
11. Display Statistics
12. Exit
```

---

## 📈 Example Scenario

### Setup:
```cpp
// Add 3 candidates
Candidate 101: "John Doe" - Democratic Party
Candidate 102: "Jane Smith" - Republican Party
Candidate 103: "Bob Johnson" - Independent

// Register 5 voters
Voter 1001: Alice (Normal - 1.0x weight)
Voter 1002: Bob (VIP - 2.0x weight)
Voter 1003: Charlie (Normal - 1.0x weight)
Voter 1004: Diana (VIP - 2.0x weight)
Voter 1005: Eve (Normal - 1.0x weight)
```

### Voting:
```
Alice votes for Candidate 101   → +1 vote, +1.0 weighted
Bob votes for Candidate 101     → +1 vote, +2.0 weighted
Charlie votes for Candidate 102 → +1 vote, +1.0 weighted
Diana votes for Candidate 102   → +1 vote, +2.0 weighted
Eve votes for Candidate 103     → +1 vote, +1.0 weighted
```

### Results:
```
┌─────────────────────────────────────────────┐
│ REAL-TIME LEADERBOARD                       │
├─────────────────────────────────────────────┤
│ Rank 1: John Doe                            │
│         Votes: 2 | Weighted: 3.0 | 37.5%    │
├─────────────────────────────────────────────┤
│ Rank 2: Jane Smith                          │
│         Votes: 2 | Weighted: 3.0 | 37.5%    │
├─────────────────────────────────────────────┤
│ Rank 3: Bob Johnson                         │
│         Votes: 1 | Weighted: 1.0 | 12.5%    │
└─────────────────────────────────────────────┘
```

---

## 🔑 Key Algorithms

### 1. **Vote Casting with Heap Update**
```
1. Validate voter (O(1) using hash map)
2. Validate candidate (O(1) using hash map)
3. Update vote count
4. Rebuild heap with new counts (O(n log n))
5. Mark voter as voted
```

### 2. **Get Current Leader**
```
1. Access heap.top() → O(1)
2. Return leader information
```

### 3. **Top-K Candidates**
```
1. Create temporary heap copy
2. Extract K elements → O(k log n)
3. Display in ranked order
```

---

## 🎯 Learning Outcomes

After implementing Version 4, you will understand:

1. ✅ **Max Heap / Priority Queue** operations
2. ✅ **Hash Table** for O(1) lookups
3. ✅ **Heap Rebuilding** strategies
4. ✅ **Weighted voting systems**
5. ✅ **Real-time ranking algorithms**
6. ✅ **Combining multiple data structures** effectively
7. ✅ **Trade-offs** between different approaches

---

## 🆚 Comparison with Previous Versions

| Feature | V1 (Array) | V2 (LinkedList) | V3 (BST) | V4 (Heap) |
|---------|-----------|----------------|----------|-----------|
| Dynamic Size | ❌ | ✅ | ✅ | ✅ |
| Fast Search | ❌ | ❌ | ✅ | ✅ |
| Real-time Ranking | ❌ | ❌ | ❌ | ✅ |
| O(1) Leader Access | ❌ | ❌ | ❌ | ✅ |
| Weighted Voting | ❌ | ❌ | ❌ | ✅ |
| Vote Validation | O(n) | O(n) | O(log n) | O(1) |

---

## 🐛 Known Limitations

1. **Heap Rebuild**: Currently rebuilds entire heap after each vote (O(n log n))
   - *Future Enhancement*: Implement heap update without full rebuild
   
2. **Memory Usage**: Stores candidates in both heap and hash map
   - *Trade-off*: Memory for speed (O(1) lookups)

3. **Tie Handling**: Candidates with same weighted votes may have inconsistent ordering
   - *Solution*: Uses vote count as tiebreaker

---

## 🚀 Future Enhancements (Version 5)

Version 5 will add:
- **Graph Data Structure** for voter networks
- **Fraud Detection** using graph algorithms
- **Regional Voting** support
- **Voting Pattern Analysis**
- **BFS/DFS** for network traversal

---

## 📚 References

### Data Structures:
- Max Heap: [GeeksforGeeks - Heap](https://www.geeksforgeeks.org/heap-data-structure/)
- Priority Queue: [C++ STL Priority Queue](https://www.cplusplus.com/reference/queue/priority_queue/)
- Hash Tables: [Unordered Map in C++](https://www.cplusplus.com/reference/unordered_map/unordered_map/)

### Concepts:
- Heapify Algorithm
- Hash Functions
- Collision Resolution
- Weighted Voting Systems

---

## 👨‍💻 Author Notes

**Version**: 4.0  
**Date**: October 2025  
**Focus**: Priority Queue & Real-time Rankings  
**Difficulty**: ⭐⭐⭐⭐ Advanced  

**Prerequisites**:
- Understanding of heap operations
- Knowledge of hash tables
- Familiarity with priority queues
- C++ STL usage

**Estimated Implementation Time**: 4-6 hours

---

## ✅ Testing Checklist

- [ ] Add multiple candidates
- [ ] Register normal and VIP voters
- [ ] Cast votes with different weights
- [ ] Verify leader updates in real-time
- [ ] Test top-K candidate retrieval
- [ ] Check duplicate voting prevention
- [ ] Validate age restrictions
- [ ] Test with empty system
- [ ] Verify percentage calculations
- [ ] Test leaderboard with ties

---

## 📞 Support

For questions or issues:
- Review the code comments
- Check the algorithm section
- Compare with Version 3 for BST reference
- Refer to C++ STL documentation

---

## 📄 License

Educational/Academic Use

---

**Happy Coding! 🎉**

Next: Proceed to Version 5 (Graph & Analytics) →
