#include "voting.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void displayMenu() {
    cout << "\n========================================\n";
    cout << "   VOTING MANAGEMENT SYSTEM (Arrays)\n";
    cout << "========================================\n";
    cout << "1. Add Candidate\n";
    cout << "2. Display All Candidates\n";
    cout << "3. Cast Vote\n";
    cout << "4. Display Results\n";
    cout << "5. Find Winner\n";
    cout << "6. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    VotingSystem voting;
    int choice;
    
    cout << "Welcome to Voting Management System!\n";
    
    while (true) {
        displayMenu();
        cin >> choice;
        
        if (cin.fail()) {
            clearInputBuffer();
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        
        switch (choice) {
            case 1: {
                int id;
                string name, party;
                
                cout << "\nEnter Candidate ID: ";
                cin >> id;
                clearInputBuffer();
                
                cout << "Enter Candidate Name: ";
                getline(cin, name);
                
                cout << "Enter Party Name: ";
                getline(cin, party);
                
                if (voting.addCandidate(id, name, party)) {
                    cout << "Candidate added successfully!\n";
                } else {
                    cout << "Failed to add candidate. System might be full or ID already exists.\n";
                }
                break;
            }
            
            case 2: {
                voting.displayCandidates();
                break;
            }
            
            case 3: {
                int candidateId;
                cout << "\nEnter Candidate ID to vote for: ";
                cin >> candidateId;
                
                if (voting.castVote(candidateId)) {
                    cout << "Vote cast successfully!\n";
                } else {
                    cout << "Failed to cast vote. Candidate not found.\n";
                }
                break;
            }
            
            case 4: {
                voting.displayResults();
                break;
            }
            
            case 5: {
                voting.findWinner();
                break;
            }
            
            case 6: {
                cout << "\nThank you for using Voting Management System!\n";
                cout << "Exiting...\n";
                return 0;
            }
            
            default: {
                cout << "Invalid choice! Please select 1-6.\n";
                break;
            }
        }
    }
    
    return 0;
}
