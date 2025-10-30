#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include "candidate.h"
#include "voter.h"

using namespace std;

class VotingSystem {
private:
    priority_queue<Candidate> candidateHeap;
    unordered_map<int, Candidate*> candidateMap;
    unordered_map<int, Voter*> voterMap;
    vector<Candidate*> allCandidates;
    
    void rebuildHeap() {
        while (!candidateHeap.empty()) {
            candidateHeap.pop();
        }
        for (auto candidate : allCandidates) {
            candidateHeap.push(*candidate);
        }
    }
    
public:
    VotingSystem() {}
    
    void addCandidate(int id, string name, string party) {
        if (candidateMap.find(id) != candidateMap.end()) {
            cout << "\n   ❌ Candidate ID " << id << " already exists!\n";
            return;
        }
        
        Candidate* newCandidate = new Candidate(id, name, party);
        candidateMap[id] = newCandidate;
        allCandidates.push_back(newCandidate);
        candidateHeap.push(*newCandidate);
        
        cout << "\n   ✅ Candidate '" << name << "' from party '" 
             << party << "' added successfully!\n";
    }
    
    void registerVoter(int id, string name, int age, int voterTypeInt) {
        if (voterMap.find(id) != voterMap.end()) {
            cout << "\n   ❌ Voter ID " << id << " already exists!\n";
            return;
        }
        
        if (age < 18) {
            cout << "\n   ❌ Voter must be at least 18 years old!\n";
            return;
        }
        
        VoterType type = (voterTypeInt == 2) ? VIP : NORMAL;
        Voter* newVoter = new Voter(id, name, age, type);
        voterMap[id] = newVoter;
        
        cout << "\n   ✅ Voter '" << name << "' registered as " 
             << newVoter->getVoterTypeString() << " voter!\n";
        cout << "   Vote Weight: " << newVoter->getVoteWeight() << "x\n";
    }
    
    void castVote(int voterId, int candidateId) {
        if (voterMap.find(voterId) == voterMap.end()) {
            cout << "\n   ❌ Voter ID " << voterId << " not registered!\n";
            return;
        }
        
        Voter* voter = voterMap[voterId];
        
        if (voter->hasVoted) {
            cout << "\n   ❌ Voter '" << voter->name 
                 << "' has already voted!\n";
            return;
        }
        
        if (candidateMap.find(candidateId) == candidateMap.end()) {
            cout << "\n   ❌ Candidate ID " << candidateId << " does not exist!\n";
            return;
        }
        
        Candidate* candidate = candidateMap[candidateId];
        double weight = voter->getVoteWeight();
        
        candidate->voteCount++;
        candidate->weightedVotes += weight;
        voter->hasVoted = true;
        voter->votedFor = candidateId;
        
        rebuildHeap();
        
        cout << "\n   ✅ Vote cast successfully!\n";
        cout << "   Voter: " << voter->name << " (" 
             << voter->getVoterTypeString() << ")\n";
        cout << "   Voted for: " << candidate->name << "\n";
        cout << "   Vote Weight: " << weight << "x\n";
        cout << "   " << candidate->name << "'s total: " 
             << candidate->voteCount << " votes (" 
             << fixed << setprecision(1) << candidate->weightedVotes 
             << " weighted)\n";
    }
    
    void getCurrentLeader() {
        if (candidateHeap.empty()) {
            cout << "\n   No candidates in the system.\n";
            return;
        }
        
        Candidate leader = candidateHeap.top();
        
        cout << "\n   ═══════════════════════════════════════\n";
        cout << "   🏆 CURRENT LEADER\n";
        cout << "   ═══════════════════════════════════════\n";
        cout << "   Candidate: " << leader.name << "\n";
        cout << "   Party: " << leader.party << "\n";
        cout << "   Total Votes: " << leader.voteCount << "\n";
        cout << "   Weighted Votes: " << fixed << setprecision(1) 
             << leader.weightedVotes << "\n";
        cout << "   ═══════════════════════════════════════\n";
    }
    
    void displayTopN(int n) {
        if (candidateHeap.empty()) {
            cout << "\n   No candidates in the system.\n";
            return;
        }
        
        priority_queue<Candidate> tempHeap = candidateHeap;
        
        cout << "\n   ═══════════════════════════════════════════════════════════\n";
        cout << "   🏆 TOP " << n << " CANDIDATES (LEADERBOARD)\n";
        cout << "   ═══════════════════════════════════════════════════════════\n";
        cout << "   " << left << setw(6) << "Rank" 
             << setw(20) << "Name" 
             << setw(15) << "Party" 
             << setw(12) << "Votes"
             << setw(15) << "Weighted" << "\n";
        cout << "   ───────────────────────────────────────────────────────────\n";
        
        int rank = 1;
        while (!tempHeap.empty() && rank <= n) {
            Candidate c = tempHeap.top();
            tempHeap.pop();
            
            cout << "   " << left << setw(6) << rank
                 << setw(20) << c.name
                 << setw(15) << c.party
                 << setw(12) << c.voteCount
                 << fixed << setprecision(1) << setw(15) << c.weightedVotes << "\n";
            rank++;
        }
        cout << "   ═══════════════════════════════════════════════════════════\n";
    }
    
    void displayLeaderboard() {
        if (candidateHeap.empty()) {
            cout << "\n   No candidates in the system.\n";
            return;
        }
        
        priority_queue<Candidate> tempHeap = candidateHeap;
        
        double totalWeighted = 0;
        priority_queue<Candidate> countHeap = candidateHeap;
        while (!countHeap.empty()) {
            totalWeighted += countHeap.top().weightedVotes;
            countHeap.pop();
        }
        
        cout << "\n   ═══════════════════════════════════════════════════════════\n";
        cout << "   📊 REAL-TIME LEADERBOARD (ALL CANDIDATES)\n";
        cout << "   ═══════════════════════════════════════════════════════════\n";
        cout << "   " << left << setw(6) << "Rank" 
             << setw(20) << "Name" 
             << setw(15) << "Party" 
             << setw(12) << "Votes"
             << setw(15) << "Weighted"
             << setw(10) << "%" << "\n";
        cout << "   ───────────────────────────────────────────────────────────\n";
        
        int rank = 1;
        while (!tempHeap.empty()) {
            Candidate c = tempHeap.top();
            tempHeap.pop();
            
            double percentage = (totalWeighted > 0) ? 
                (c.weightedVotes / totalWeighted * 100) : 0;
            
            cout << "   " << left << setw(6) << rank
                 << setw(20) << c.name
                 << setw(15) << c.party
                 << setw(12) << c.voteCount
                 << fixed << setprecision(1) << setw(15) << c.weightedVotes
                 << setprecision(2) << setw(10) << percentage << "%\n";
            rank++;
        }
        cout << "   ═══════════════════════════════════════════════════════════\n";
        cout << "   Total Weighted Votes: " << fixed << setprecision(1) 
             << totalWeighted << "\n";
    }
    
    void displayAllCandidates() {
        if (allCandidates.empty()) {
            cout << "\n   No candidates registered.\n";
            return;
        }
        
        cout << "\n   ═══════════════════════════════════════════════════════════\n";
        cout << "   📋 ALL CANDIDATES\n";
        cout << "   ═══════════════════════════════════════════════════════════\n";
        cout << "   " << left << setw(8) << "ID" 
             << setw(25) << "Name" 
             << setw(20) << "Party" << "\n";
        cout << "   ───────────────────────────────────────────────────────────\n";
        
        for (auto c : allCandidates) {
            cout << "   " << left << setw(8) << c->id
                 << setw(25) << c->name
                 << setw(20) << c->party << "\n";
        }
        cout << "   ═══════════════════════════════════════════════════════════\n";
    }
    
    void displayAllVoters() {
        if (voterMap.empty()) {
            cout << "\n   No voters registered.\n";
            return;
        }
        
        cout << "\n   ═══════════════════════════════════════════════════════════\n";
        cout << "   👥 ALL VOTERS\n";
        cout << "   ═══════════════════════════════════════════════════════════\n";
        cout << "   " << left << setw(8) << "ID" 
             << setw(20) << "Name" 
             << setw(6) << "Age"
             << setw(10) << "Type"
             << setw(12) << "Status" << "\n";
        cout << "   ───────────────────────────────────────────────────────────\n";
        
        for (auto& pair : voterMap) {
            Voter* v = pair.second;
            string status = v->hasVoted ? "Voted" : "Not Voted";
            
            cout << "   " << left << setw(8) << v->id
                 << setw(20) << v->name
                 << setw(6) << v->age
                 << setw(10) << v->getVoterTypeString()
                 << setw(12) << status << "\n";
        }
        cout << "   ═══════════════════════════════════════════════════════════\n";
    }
    
    void searchCandidate(int id) {
        if (candidateMap.find(id) == candidateMap.end()) {
            cout << "\n   ❌ Candidate ID " << id << " not found!\n";
            return;
        }
        
        Candidate* c = candidateMap[id];
        cout << "\n   ═══════════════════════════════════════\n";
        cout << "   🔍 CANDIDATE DETAILS\n";
        cout << "   ═══════════════════════════════════════\n";
        cout << "   ID: " << c->id << "\n";
        cout << "   Name: " << c->name << "\n";
        cout << "   Party: " << c->party << "\n";
        cout << "   Votes: " << c->voteCount << "\n";
        cout << "   Weighted Votes: " << fixed << setprecision(1) 
             << c->weightedVotes << "\n";
        cout << "   ═══════════════════════════════════════\n";
    }
    
    void searchVoter(int id) {
        if (voterMap.find(id) == voterMap.end()) {
            cout << "\n   ❌ Voter ID " << id << " not found!\n";
            return;
        }
        
        Voter* v = voterMap[id];
        string status = v->hasVoted ? "Voted" : "Not Voted";
        
        cout << "\n   ═══════════════════════════════════════\n";
        cout << "   🔍 VOTER DETAILS\n";
        cout << "   ═══════════════════════════════════════\n";
        cout << "   ID: " << v->id << "\n";
        cout << "   Name: " << v->name << "\n";
        cout << "   Age: " << v->age << "\n";
        cout << "   Type: " << v->getVoterTypeString() << "\n";
        cout << "   Vote Weight: " << v->getVoteWeight() << "x\n";
        cout << "   Status: " << status << "\n";
        if (v->hasVoted) {
            cout << "   Voted For: Candidate ID " << v->votedFor << "\n";
        }
        cout << "   ═══════════════════════════════════════\n";
    }
    
    void displayStatistics() {
        int totalVoters = voterMap.size();
        int votedCount = 0;
        int vipCount = 0;
        int normalCount = 0;
        
        for (auto& pair : voterMap) {
            if (pair.second->hasVoted) votedCount++;
            if (pair.second->type == VIP) vipCount++;
            else normalCount++;
        }
        
        double turnout = (totalVoters > 0) ? 
            (votedCount * 100.0 / totalVoters) : 0;
        
        cout << "\n   ═══════════════════════════════════════\n";
        cout << "   📈 VOTING STATISTICS\n";
        cout << "   ═══════════════════════════════════════\n";
        cout << "   Total Voters: " << totalVoters << "\n";
        cout << "   - Normal Voters: " << normalCount << "\n";
        cout << "   - VIP Voters: " << vipCount << "\n";
        cout << "   Votes Cast: " << votedCount << "\n";
        cout << "   Remaining: " << (totalVoters - votedCount) << "\n";
        cout << "   Turnout: " << fixed << setprecision(2) 
             << turnout << "%\n";
        cout << "   Total Candidates: " << allCandidates.size() << "\n";
        cout << "   ═══════════════════════════════════════\n";
    }
    
    ~VotingSystem() {
        for (auto c : allCandidates) delete c;
        for (auto& pair : voterMap) delete pair.second;
    }
};

void displayMenu() {
    cout << "\n╔════════════════════════════════════════════════╗\n";
    cout << "║   VOTING SYSTEM V4 - PRIORITY BASED           ║\n";
    cout << "║   (Heap & Priority Queue Implementation)      ║\n";
    cout << "╠════════════════════════════════════════════════╣\n";
    cout << "║  1. Add Candidate                              ║\n";
    cout << "║  2. Register Voter (Normal/VIP)                ║\n";
    cout << "║  3. Cast Vote                                  ║\n";
    cout << "║  4. Get Current Leader                         ║\n";
    cout << "║  5. Display Top N Candidates                   ║\n";
    cout << "║  6. Display Real-time Leaderboard              ║\n";
    cout << "║  7. Display All Candidates                     ║\n";
    cout << "║  8. Display All Voters                         ║\n";
    cout << "║  9. Search Candidate                           ║\n";
    cout << "║  10. Search Voter                              ║\n";
    cout << "║  11. Display Statistics                        ║\n";
    cout << "║  12. Exit                                      ║\n";
    cout << "╚════════════════════════════════════════════════╝\n";
    cout << "Enter your choice: ";
}

int main() {
    VotingSystem vs;
    int choice;
    
    cout << "\n╔════════════════════════════════════════════════╗\n";
    cout << "║  Welcome to Voting Management System V4       ║\n";
    cout << "║  Priority-Based with Weight System            ║\n";
    cout << "╚════════════════════════════════════════════════╝\n";
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                int id;
                string name, party;
                cout << "\nEnter Candidate ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Candidate Name: ";
                getline(cin, name);
                cout << "Enter Party Name: ";
                getline(cin, party);
                vs.addCandidate(id, name, party);
                break;
            }
            
            case 2: {
                int id, age, type;
                string name;
                cout << "\nEnter Voter ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Voter Name: ";
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Voter Type (1=Normal, 2=VIP): ";
                cin >> type;
                vs.registerVoter(id, name, age, type);
                break;
            }
            
            case 3: {
                int voterId, candidateId;
                cout << "\nEnter Voter ID: ";
                cin >> voterId;
                cout << "Enter Candidate ID to vote for: ";
                cin >> candidateId;
                vs.castVote(voterId, candidateId);
                break;
            }
            
            case 4:
                vs.getCurrentLeader();
                break;
            
            case 5: {
                int n;
                cout << "\nEnter number of top candidates to display: ";
                cin >> n;
                vs.displayTopN(n);
                break;
            }
            
            case 6:
                vs.displayLeaderboard();
                break;
            
            case 7:
                vs.displayAllCandidates();
                break;
            
            case 8:
                vs.displayAllVoters();
                break;
            
            case 9: {
                int id;
                cout << "\nEnter Candidate ID to search: ";
                cin >> id;
                vs.searchCandidate(id);
                break;
            }
            
            case 10: {
                int id;
                cout << "\nEnter Voter ID to search: ";
                cin >> id;
                vs.searchVoter(id);
                break;
            }
            
            case 11:
                vs.displayStatistics();
                break;
            
            case 12:
                cout << "\n╔════════════════════════════════════════════════╗\n";
                cout << "║  Thank you for using Voting System V4!        ║\n";
                cout << "║  Goodbye!                                      ║\n";
                cout << "╚════════════════════════════════════════════════╝\n\n";
                return 0;
            
            default:
                cout << "\n   ❌ Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}
