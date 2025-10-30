#ifndef VOTING_H
#define VOTING_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_CANDIDATES = 100;

// Candidate structure
struct Candidate {
    int id;
    string name;
    string party;
    int votes;
    
    Candidate() : id(0), name(""), party(""), votes(0) {}
    
    Candidate(int candidateId, const string& candidateName, const string& candidateParty)
        : id(candidateId), name(candidateName), party(candidateParty), votes(0) {}
};

// Voting System Class using Arrays
class VotingSystem {
private:
    Candidate candidates[MAX_CANDIDATES];
    int candidateCount;
    
    // Helper function to find candidate index by ID
    int findCandidateIndex(int id) {
        for (int i = 0; i < candidateCount; i++) {
            if (candidates[i].id == id) {
                return i;
            }
        }
        return -1;
    }
    
public:
    VotingSystem() : candidateCount(0) {}
    
    // Add a new candidate
    bool addCandidate(int id, const string& name, const string& party) {
        if (candidateCount >= MAX_CANDIDATES) {
            cout << "Error: Maximum candidate limit reached!\n";
            return false;
        }
        
        // Check if candidate ID already exists
        if (findCandidateIndex(id) != -1) {
            cout << "Error: Candidate with ID " << id << " already exists!\n";
            return false;
        }
        
        candidates[candidateCount] = Candidate(id, name, party);
        candidateCount++;
        return true;
    }
    
    // Display all candidates
    void displayCandidates() {
        if (candidateCount == 0) {
            cout << "\nNo candidates registered yet.\n";
            return;
        }
        
        cout << "\n" << string(80, '=') << "\n";
        cout << left << setw(10) << "ID" 
             << setw(25) << "Name" 
             << setw(25) << "Party" 
             << setw(10) << "Votes" << "\n";
        cout << string(80, '=') << "\n";
        
        for (int i = 0; i < candidateCount; i++) {
            cout << left << setw(10) << candidates[i].id
                 << setw(25) << candidates[i].name
                 << setw(25) << candidates[i].party
                 << setw(10) << candidates[i].votes << "\n";
        }
        cout << string(80, '=') << "\n";
    }
    
    // Cast a vote for a candidate
    bool castVote(int candidateId) {
        int index = findCandidateIndex(candidateId);
        
        if (index == -1) {
            cout << "Error: Candidate with ID " << candidateId << " not found!\n";
            return false;
        }
        
        candidates[index].votes++;
        return true;
    }
    
    // Display voting results
    void displayResults() {
        if (candidateCount == 0) {
            cout << "\nNo candidates registered yet.\n";
            return;
        }
        
        int totalVotes = 0;
        for (int i = 0; i < candidateCount; i++) {
            totalVotes += candidates[i].votes;
        }
        
        cout << "\n" << string(90, '=') << "\n";
        cout << "                         VOTING RESULTS\n";
        cout << string(90, '=') << "\n";
        cout << left << setw(10) << "ID" 
             << setw(25) << "Name" 
             << setw(25) << "Party" 
             << setw(10) << "Votes"
             << setw(15) << "Percentage" << "\n";
        cout << string(90, '=') << "\n";
        
        for (int i = 0; i < candidateCount; i++) {
            double percentage = (totalVotes > 0) ? 
                (candidates[i].votes * 100.0 / totalVotes) : 0.0;
            
            cout << left << setw(10) << candidates[i].id
                 << setw(25) << candidates[i].name
                 << setw(25) << candidates[i].party
                 << setw(10) << candidates[i].votes
                 << fixed << setprecision(2) << percentage << "%\n";
        }
        cout << string(90, '=') << "\n";
        cout << "Total Votes Cast: " << totalVotes << "\n";
        cout << string(90, '=') << "\n";
    }
    
    // Find and display the winner
    void findWinner() {
        if (candidateCount == 0) {
            cout << "\nNo candidates registered yet.\n";
            return;
        }
        
        int maxVotes = -1;
        int winnerIndex = -1;
        bool tie = false;
        
        // Find maximum votes
        for (int i = 0; i < candidateCount; i++) {
            if (candidates[i].votes > maxVotes) {
                maxVotes = candidates[i].votes;
                winnerIndex = i;
                tie = false;
            } else if (candidates[i].votes == maxVotes && maxVotes > 0) {
                tie = true;
            }
        }
        
        if (maxVotes == 0) {
            cout << "\nNo votes have been cast yet.\n";
            return;
        }
        
        cout << "\n" << string(60, '=') << "\n";
        cout << "                    WINNER ANNOUNCEMENT\n";
        cout << string(60, '=') << "\n";
        
        if (tie) {
            cout << "There is a TIE with " << maxVotes << " votes!\n";
            cout << "Tied candidates:\n\n";
            for (int i = 0; i < candidateCount; i++) {
                if (candidates[i].votes == maxVotes) {
                    cout << "- " << candidates[i].name 
                         << " (" << candidates[i].party << ")\n";
                }
            }
        } else {
            cout << "Winner: " << candidates[winnerIndex].name << "\n";
            cout << "Party: " << candidates[winnerIndex].party << "\n";
            cout << "Total Votes: " << candidates[winnerIndex].votes << "\n";
        }
        cout << string(60, '=') << "\n";
    }
    
    // Get candidate count
    int getCandidateCount() const {
        return candidateCount;
    }
};

#endif // VOTING_H
