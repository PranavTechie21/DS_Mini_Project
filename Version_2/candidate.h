#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

// Node structure for Candidate
struct CandidateNode {
    int id;
    string name;
    string party;
    int votes;
    CandidateNode* next;
    
    CandidateNode(int candidateId, const string& candidateName, const string& candidateParty)
        : id(candidateId), name(candidateName), party(candidateParty), votes(0), next(nullptr) {}
};

// Candidate Linked List Class
class CandidateList {
private:
    CandidateNode* head;
    int count;
    
    // Helper function to find candidate by ID
    CandidateNode* findCandidate(int id) {
        CandidateNode* current = head;
        while (current != nullptr) {
            if (current->id == id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    
public:
    CandidateList() : head(nullptr), count(0) {}
    
    // Destructor to free memory
    ~CandidateList() {
        CandidateNode* current = head;
        while (current != nullptr) {
            CandidateNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    
    // Add a new candidate
    bool addCandidate(int id, const string& name, const string& party) {
        // Check if candidate already exists
        if (findCandidate(id) != nullptr) {
            cout << "Error: Candidate with ID " << id << " already exists!\n";
            return false;
        }
        
        // Create new candidate node
        CandidateNode* newNode = new CandidateNode(id, name, party);
        
        // Insert at the beginning (most efficient for linked list)
        newNode->next = head;
        head = newNode;
        count++;
        
        return true;
    }
    
    // Display all candidates
    void displayCandidates() {
        if (head == nullptr) {
            cout << "\nNo candidates registered yet.\n";
            return;
        }
        
        cout << "\n" << string(80, '=') << "\n";
        cout << left << setw(10) << "ID" 
             << setw(25) << "Name" 
             << setw(25) << "Party" 
             << setw(10) << "Votes" << "\n";
        cout << string(80, '=') << "\n";
        
        CandidateNode* current = head;
        while (current != nullptr) {
            cout << left << setw(10) << current->id
                 << setw(25) << current->name
                 << setw(25) << current->party
                 << setw(10) << current->votes << "\n";
            current = current->next;
        }
        cout << string(80, '=') << "\n";
        cout << "Total Candidates: " << count << "\n";
    }
    
    // Cast a vote
    bool castVote(int candidateId) {
        CandidateNode* candidate = findCandidate(candidateId);
        
        if (candidate == nullptr) {
            cout << "Error: Candidate with ID " << candidateId << " not found!\n";
            return false;
        }
        
        candidate->votes++;
        return true;
    }
    
    // Display voting results
    void displayResults() {
        if (head == nullptr) {
            cout << "\nNo candidates registered yet.\n";
            return;
        }
        
        int totalVotes = 0;
        CandidateNode* current = head;
        
        // Calculate total votes
        while (current != nullptr) {
            totalVotes += current->votes;
            current = current->next;
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
        
        current = head;
        while (current != nullptr) {
            double percentage = (totalVotes > 0) ? 
                (current->votes * 100.0 / totalVotes) : 0.0;
            
            cout << left << setw(10) << current->id
                 << setw(25) << current->name
                 << setw(25) << current->party
                 << setw(10) << current->votes
                 << fixed << setprecision(2) << percentage << "%\n";
            current = current->next;
        }
        cout << string(90, '=') << "\n";
        cout << "Total Votes Cast: " << totalVotes << "\n";
        cout << string(90, '=') << "\n";
    }
    
    // Find and display winner
    void findWinner() {
        if (head == nullptr) {
            cout << "\nNo candidates registered yet.\n";
            return;
        }
        
        CandidateNode* winner = head;
        CandidateNode* current = head->next;
        bool tie = false;
        
        // Find maximum votes
        while (current != nullptr) {
            if (current->votes > winner->votes) {
                winner = current;
                tie = false;
            } else if (current->votes == winner->votes && current->votes > 0) {
                tie = true;
            }
            current = current->next;
        }
        
        if (winner->votes == 0) {
            cout << "\nNo votes have been cast yet.\n";
            return;
        }
        
        cout << "\n" << string(60, '=') << "\n";
        cout << "                    WINNER ANNOUNCEMENT\n";
        cout << string(60, '=') << "\n";
        
        if (tie) {
            cout << "There is a TIE with " << winner->votes << " votes!\n";
            cout << "Tied candidates:\n\n";
            current = head;
            while (current != nullptr) {
                if (current->votes == winner->votes) {
                    cout << "- " << current->name 
                         << " (" << current->party << ")\n";
                }
                current = current->next;
            }
        } else {
            cout << "Winner: " << winner->name << "\n";
            cout << "Party: " << winner->party << "\n";
            cout << "Total Votes: " << winner->votes << "\n";
        }
        cout << string(60, '=') << "\n";
    }
    
    // Delete a candidate
    bool deleteCandidate(int id) {
        if (head == nullptr) {
            return false;
        }
        
        // If head needs to be deleted
        if (head->id == id) {
            CandidateNode* temp = head;
            head = head->next;
            delete temp;
            count--;
            return true;
        }
        
        // Search for the candidate to delete
        CandidateNode* current = head;
        while (current->next != nullptr && current->next->id != id) {
            current = current->next;
        }
        
        if (current->next == nullptr) {
            return false;
        }
        
        CandidateNode* temp = current->next;
        current->next = current->next->next;
        delete temp;
        count--;
        return true;
    }
    
    // Search for a candidate
    void searchCandidate(int id) {
        CandidateNode* candidate = findCandidate(id);
        
        if (candidate == nullptr) {
            cout << "\nCandidate with ID " << id << " not found!\n";
            return;
        }
        
        cout << "\n" << string(60, '=') << "\n";
        cout << "Candidate Found:\n";
        cout << string(60, '=') << "\n";
        cout << "ID: " << candidate->id << "\n";
        cout << "Name: " << candidate->name << "\n";
        cout << "Party: " << candidate->party << "\n";
        cout << "Votes: " << candidate->votes << "\n";
        cout << string(60, '=') << "\n";
    }
    
    // Get candidate count
    int getCandidateCount() const {
        return count;
    }
};

#endif // CANDIDATE_H
