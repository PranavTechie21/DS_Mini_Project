#ifndef VOTER_H
#define VOTER_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

// Node structure for Voter
struct VoterNode {
    int id;
    string name;
    bool hasVoted;
    VoterNode* next;
    
    VoterNode(int voterId, const string& voterName)
        : id(voterId), name(voterName), hasVoted(false), next(nullptr) {}
};

// Voter Linked List Class
class VoterList {
private:
    VoterNode* head;
    int count;
    
    // Helper function to find voter by ID
    VoterNode* findVoter(int id) {
        VoterNode* current = head;
        while (current != nullptr) {
            if (current->id == id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    
public:
    VoterList() : head(nullptr), count(0) {}
    
    // Destructor to free memory
    ~VoterList() {
        VoterNode* current = head;
        while (current != nullptr) {
            VoterNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    
    // Register a new voter
    bool registerVoter(int id, const string& name) {
        // Check if voter already exists
        if (findVoter(id) != nullptr) {
            cout << "Error: Voter with ID " << id << " already registered!\n";
            return false;
        }
        
        // Create new voter node
        VoterNode* newNode = new VoterNode(id, name);
        
        // Insert at the beginning
        newNode->next = head;
        head = newNode;
        count++;
        
        return true;
    }
    
    // Display all voters
    void displayVoters() {
        if (head == nullptr) {
            cout << "\nNo voters registered yet.\n";
            return;
        }
        
        cout << "\n" << string(70, '=') << "\n";
        cout << left << setw(15) << "Voter ID" 
             << setw(30) << "Name" 
             << setw(15) << "Status" << "\n";
        cout << string(70, '=') << "\n";
        
        VoterNode* current = head;
        while (current != nullptr) {
            cout << left << setw(15) << current->id
                 << setw(30) << current->name
                 << setw(15) << (current->hasVoted ? "Voted" : "Not Voted") << "\n";
            current = current->next;
        }
        cout << string(70, '=') << "\n";
        cout << "Total Registered Voters: " << count << "\n";
    }
    
    // Check if voter has already voted
    bool hasVoted(int id) {
        VoterNode* voter = findVoter(id);
        if (voter == nullptr) {
            return true; // Voter not found, prevent voting
        }
        return voter->hasVoted;
    }
    
    // Mark voter as having voted
    bool markAsVoted(int id) {
        VoterNode* voter = findVoter(id);
        if (voter == nullptr) {
            return false;
        }
        voter->hasVoted = true;
        return true;
    }
    
    // Get voter count
    int getVoterCount() const {
        return count;
    }
    
    // Get count of voters who have voted
    int getVotedCount() const {
        int votedCount = 0;
        VoterNode* current = head;
        while (current != nullptr) {
            if (current->hasVoted) {
                votedCount++;
            }
            current = current->next;
        }
        return votedCount;
    }
    
    // Display voting statistics
    void displayStatistics() {
        if (count == 0) {
            cout << "\nNo voters registered yet.\n";
            return;
        }
        
        int votedCount = getVotedCount();
        double turnoutPercentage = (count > 0) ? (votedCount * 100.0 / count) : 0.0;
        
        cout << "\n" << string(50, '=') << "\n";
        cout << "         VOTER STATISTICS\n";
        cout << string(50, '=') << "\n";
        cout << "Total Registered Voters: " << count << "\n";
        cout << "Voters Who Voted: " << votedCount << "\n";
        cout << "Voters Who Haven't Voted: " << (count - votedCount) << "\n";
        cout << fixed << setprecision(2);
        cout << "Voter Turnout: " << turnoutPercentage << "%\n";
        cout << string(50, '=') << "\n";
    }
};

#endif // VOTER_H
