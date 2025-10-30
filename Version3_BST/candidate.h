#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>
#include <iostream>

using namespace std;

// Candidate structure
struct Candidate {
    int id;
    string name;
    string party;
    int votes;
    
    Candidate() : id(0), name(""), party(""), votes(0) {}
    
    Candidate(int candidateId, const string& candidateName, const string& candidateParty)
        : id(candidateId), name(candidateName), party(candidateParty), votes(0) {}
    
    // Display candidate information
    void display() const {
        cout << "ID: " << id 
             << " | Name: " << name 
             << " | Party: " << party 
             << " | Votes: " << votes << "\n";
    }
    
    // Display with percentage
    void displayWithPercentage(int totalVotes) const {
        double percentage = (totalVotes > 0) ? (votes * 100.0 / totalVotes) : 0.0;
        cout << "ID: " << id 
             << " | Name: " << name 
             << " | Party: " << party 
             << " | Votes: " << votes 
             << " | Percentage: " << percentage << "%\n";
    }
};

#endif // CANDIDATE_H
