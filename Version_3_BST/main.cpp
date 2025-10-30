#include "bst.h"
#include "candidate.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void displayMenu() {
    cout << "\n========================================\n";
    cout << "     VOTING MANAGEMENT SYSTEM (BST)\n";
    cout << "========================================\n";
    cout << "1. Add Candidate\n";
    cout << "2. Display All Candidates (In-Order)\n";
    cout << "3. Display Candidates (Pre-Order)\n";
    cout << "4. Display Candidates (Post-Order)\n";
    cout << "5. Cast Vote\n";
    cout << "6. Display Results\n";
    cout << "7. Find Winner\n";
    cout << "8. Delete Candidate\n";
    cout << "9. Search Candidate\n";
    cout << "10. Find Minimum ID Candidate\n";
    cout << "11. Find Maximum ID Candidate\n";
    cout << "12. Count Total Candidates\n";
    cout << "13. Display Tree Height\n";
    cout << "14. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    CandidateBST candidateBST;
    int choice;
    
    cout << "Welcome to Voting Management System (BST Version)!\n";
    cout << "Candidates are organized in a Binary Search Tree by ID.\n";
    
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
                
                if (candidateBST.insert(id, name, party)) {
                    cout << "Candidate added successfully!\n";
                } else {
                    cout << "Failed to add candidate. ID already exists.\n";
                }
                break;
            }
            
            case 2: {
                cout << "\nCandidates (In-Order - Sorted by ID):\n";
                candidateBST.displayInOrder();
                break;
            }
            
            case 3: {
                cout << "\nCandidates (Pre-Order Traversal):\n";
                candidateBST.displayPreOrder();
                break;
            }
            
            case 4: {
                cout << "\nCandidates (Post-Order Traversal):\n";
                candidateBST.displayPostOrder();
                break;
            }
            
            case 5: {
                int candidateId;
                cout << "\nEnter Candidate ID to vote for: ";
                cin >> candidateId;
                
                if (candidateBST.castVote(candidateId)) {
                    cout << "Vote cast successfully!\n";
                } else {
                    cout << "Failed to cast vote. Candidate not found.\n";
                }
                break;
            }
            
            case 6: {
                candidateBST.displayResults();
                break;
            }
            
            case 7: {
                candidateBST.findWinner();
                break;
            }
            
            case 8: {
                int id;
                cout << "\nEnter Candidate ID to delete: ";
                cin >> id;
                
                if (candidateBST.deleteCandidate(id)) {
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
                candidateBST.searchCandidate(id);
                break;
            }
            
            case 10: {
                candidateBST.findMinimum();
                break;
            }
            
            case 11: {
                candidateBST.findMaximum();
                break;
            }
            
            case 12: {
                int count = candidateBST.countNodes();
                cout << "\nTotal Candidates: " << count << "\n";
                break;
            }
            
            case 13: {
                int height = candidateBST.getHeight();
                cout << "\nTree Height: " << height << "\n";
                cout << "(Height represents the longest path from root to leaf)\n";
                break;
            }
            
            case 14: {
                cout << "\nThank you for using Voting Management System!\n";
                cout << "Exiting...\n";
                return 0;
            }
            
            default: {
                cout << "Invalid choice! Please select 1-14.\n";
                break;
            }
        }
    }
    
    return 0;
}
