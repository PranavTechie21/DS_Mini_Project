#include "candidate.h"
#include "voter.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void displayMenu() {
    cout << "\n========================================\n";
    cout << "  VOTING MANAGEMENT SYSTEM (Linked List)\n";
    cout << "========================================\n";
    cout << "1. Add Candidate\n";
    cout << "2. Display All Candidates\n";
    cout << "3. Register Voter\n";
    cout << "4. Display All Voters\n";
    cout << "5. Cast Vote\n";
    cout << "6. Display Results\n";
    cout << "7. Find Winner\n";
    cout << "8. Delete Candidate\n";
    cout << "9. Search Candidate\n";
    cout << "10. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    CandidateList candidateList;
    VoterList voterList;
    int choice;
    
    cout << "Welcome to Voting Management System (Linked List Version)!\n";
    
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
                
                if (candidateList.addCandidate(id, name, party)) {
                    cout << "Candidate added successfully!\n";
                } else {
                    cout << "Failed to add candidate. ID already exists.\n";
                }
                break;
            }
            
            case 2: {
                candidateList.displayCandidates();
                break;
            }
            
            case 3: {
                int voterId;
                string voterName;
                
                cout << "\nEnter Voter ID: ";
                cin >> voterId;
                clearInputBuffer();
                
                cout << "Enter Voter Name: ";
                getline(cin, voterName);
                
                if (voterList.registerVoter(voterId, voterName)) {
                    cout << "Voter registered successfully!\n";
                } else {
                    cout << "Failed to register voter. ID already exists.\n";
                }
                break;
            }
            
            case 4: {
                voterList.displayVoters();
                break;
            }
            
            case 5: {
                int voterId, candidateId;
                
                cout << "\nEnter Your Voter ID: ";
                cin >> voterId;
                
                if (!voterList.hasVoted(voterId)) {
                    cout << "Enter Candidate ID to vote for: ";
                    cin >> candidateId;
                    
                    if (candidateList.castVote(candidateId)) {
                        voterList.markAsVoted(voterId);
                        cout << "Vote cast successfully!\n";
                    } else {
                        cout << "Failed to cast vote. Candidate not found.\n";
                    }
                } else {
                    cout << "You have already voted or voter ID not found!\n";
                }
                break;
            }
            
            case 6: {
                candidateList.displayResults();
                break;
            }
            
            case 7: {
                candidateList.findWinner();
                break;
            }
            
            case 8: {
                int id;
                cout << "\nEnter Candidate ID to delete: ";
                cin >> id;
                
                if (candidateList.deleteCandidate(id)) {
                    cout << "Candidate deleted successfully!\n";
                } else {
                    cout << "Failed to delete candidate. ID not found.\n";
                }
                break;
            }
            
            case 9: {
                int id;
                cout << "\nEnter Candidate ID to search: ";
                cin >> id;
                candidateList.searchCandidate(id);
                break;
            }
            
            case 10: {
                cout << "\nThank you for using Voting Management System!\n";
                cout << "Exiting...\n";
                return 0;
            }
            
            default: {
                cout << "Invalid choice! Please select 1-10.\n";
                break;
            }
        }
    }
    
    return 0;
}
