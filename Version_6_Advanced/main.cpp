#include "election.h"
#include "database.h"
#include "analytics.h"
#include "utils.h"
#include <iostream>
#include <limits>

using namespace std;

void displayMainMenu() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "      COMPLETE VOTING MANAGEMENT SYSTEM v6.0\n";
    cout << string(60, '=') << "\n";
    cout << "1.  Candidate Management\n";
    cout << "2.  Voter Management\n";
    cout << "3.  Voting Operations\n";
    cout << "4.  Results & Statistics\n";
    cout << "5.  Analytics & Reports\n";
    cout << "6.  Data Management\n";
    cout << "7.  System Utilities\n";
    cout << "8.  Exit\n";
    cout << string(60, '=') << "\n";
    cout << "Enter your choice: ";
}

void candidateManagementMenu(ElectionDatabase& db) {
    while (true) {
        cout << "\n--- Candidate Management ---\n";
        cout << "1. Add Candidate\n";
        cout << "2. Display All Candidates\n";
        cout << "3. Search Candidate by ID\n";
        cout << "4. Delete Candidate\n";
        cout << "5. View Candidates by Region\n";
        cout << "6. View Candidates by Party\n";
        cout << "7. Back to Main Menu\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            ElectionUtils::clearInputBuffer();
            cout << "Invalid input!\n";
            continue;
        }
        
        if (choice == 7) break;
        
        switch (choice) {
            case 1: {
                int id, age;
                string name, party, region, qualification;
                
                cout << "\nEnter Candidate ID: ";
                cin >> id;
                ElectionUtils::clearInputBuffer();
                
                cout << "Enter Name: ";
                getline(cin, name);
                
                cout << "Enter Party: ";
                getline(cin, party);
                
                cout << "Enter Region: ";
                getline(cin, region);
                
                cout << "Enter Age: ";
                cin >> age;
                ElectionUtils::clearInputBuffer();
                
                cout << "Enter Qualification: ";
                getline(cin, qualification);
                
                Candidate c(id, name, party, region, age, qualification);
                if (db.addCandidate(c)) {
                    cout << "Candidate added successfully!\n";
                } else {
                    cout << "Failed to add candidate.\n";
                }
                break;
            }
            
            case 2:
                db.displayAllCandidates();
                break;
            
            case 3: {
                int id;
                cout << "Enter Candidate ID: ";
                cin >> id;
                
                Candidate* c = db.findCandidate(id);
                if (c) {
                    c->displayDetailed();
                } else {
                    cout << "Candidate not found.\n";
                }
                break;
            }
            
            case 4: {
                int id;
                cout << "Enter Candidate ID to delete: ";
                cin >> id;
                
                if (db.deleteCandidate(id)) {
                    cout << "Candidate deleted successfully!\n";
                } else {
                    cout << "Failed to delete candidate.\n";
                }
                break;
            }
            
            case 5: {
                string region;
                cout << "Enter Region: ";
                ElectionUtils::clearInputBuffer();
                getline(cin, region);
                
                auto candidates = db.getCandidatesByRegion(region);
                if (candidates.empty()) {
                    cout << "No candidates found in this region.\n";
                } else {
                    cout << "\nCandidates in " << region << ":\n";
                    cout << string(80, '-') << "\n";
                    for (const auto& c : candidates) {
                        c.display();
                    }
                }
                break;
            }
            
            case 6: {
                string party;
                cout << "Enter Party: ";
                ElectionUtils::clearInputBuffer();
                getline(cin, party);
                
                auto candidates = db.getCandidatesByParty(party);
                if (candidates.empty()) {
                    cout << "No candidates found for this party.\n";
                } else {
                    cout << "\nCandidates from " << party << ":\n";
                    cout << string(80, '-') << "\n";
                    for (const auto& c : candidates) {
                        c.display();
                    }
                }
                break;
            }
            
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void voterManagementMenu(ElectionDatabase& db) {
    while (true) {
        cout << "\n--- Voter Management ---\n";
        cout << "1. Register Voter\n";
        cout << "2. Display All Voters\n";
        cout << "3. Search Voter by ID\n";
        cout << "4. Check Voter Status\n";
        cout << "5. Back to Main Menu\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            ElectionUtils::clearInputBuffer();
            cout << "Invalid input!\n";
            continue;
        }
        
        if (choice == 5) break;
        
        switch (choice) {
            case 1: {
                int id, age;
                string name, region;
                
                cout << "\nEnter Voter ID: ";
                cin >> id;
                ElectionUtils::clearInputBuffer();
                
                cout << "Enter Name: ";
                getline(cin, name);
                
                cout << "Enter Region: ";
                getline(cin, region);
                
                cout << "Enter Age: ";
                cin >> age;
                
                Voter v(id, name, region, age);
                if (db.addVoter(v)) {
                    cout << "Voter registered successfully!\n";
                } else {
                    cout << "Failed to register voter.\n";
                }
                break;
            }
            
            case 2:
                db.displayAllVoters();
                break;
            
            case 3: {
                int id;
                cout << "Enter Voter ID: ";
                cin >> id;
                
                Voter* v = db.findVoter(id);
                if (v) {
                    cout << "\n" << string(50, '=') << "\n";
                    cout << "Voter ID: " << v->id << "\n";
                    cout << "Name: " << v->name << "\n";
                    cout << "Region: " << v->region << "\n";
                    cout << "Age: " << v->age << "\n";
                    cout << "Status: " << (v->hasVoted ? "Voted" : "Not Voted") << "\n";
                    if (v->hasVoted) {
                        cout << "Voted For: Candidate ID " << v->votedFor << "\n";
                    }
                    cout << string(50, '=') << "\n";
                } else {
                    cout << "Voter not found.\n";
                }
                break;
            }
            
            case 4: {
                int id;
                cout << "Enter Voter ID: ";
                cin >> id;
                
                Voter* v = db.findVoter(id);
                if (v) {
                    if (v->hasVoted) {
                        cout << "Voter " << v->name << " has already voted.\n";
                    } else {
                        cout << "Voter " << v->name << " has not voted yet.\n";
                    }
                } else {
                    cout << "Voter not found.\n";
                }
                break;
            }
            
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void votingOperationsMenu(ElectionDatabase& db) {
    while (true) {
        cout << "\n--- Voting Operations ---\n";
        cout << "1. Cast Vote\n";
        cout << "2. View Regional Voting Status\n";
        cout << "3. Back to Main Menu\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            ElectionUtils::clearInputBuffer();
            cout << "Invalid input!\n";
            continue;
        }
        
        if (choice == 3) break;
        
        switch (choice) {
            case 1: {
                int voterId, candidateId;
                
                cout << "\nEnter Your Voter ID: ";
                cin >> voterId;
                
                Voter* voter = db.findVoter(voterId);
                if (!voter) {
                    cout << "Voter ID not found!\n";
                    break;
                }
                
                if (voter->hasVoted) {
                    cout << "You have already voted!\n";
                    break;
                }
                
                cout << "\nCandidates in your region (" << voter->region << "):\n";
                auto candidates = db.getCandidatesByRegion(voter->region);
                
                if (candidates.empty()) {
                    cout << "No candidates available in your region.\n";
                    break;
                }
                
                cout << string(80, '-') << "\n";
                for (const auto& c : candidates) {
                    cout << "ID: " << c.id << " | Name: " << c.name 
                         << " | Party: " << c.party << "\n";
                }
                cout << string(80, '-') << "\n";
                
                cout << "\nEnter Candidate ID to vote for: ";
                cin >> candidateId;
                
                if (db.castVote(voterId, candidateId)) {
                    cout << "\n*** Vote cast successfully! ***\n";
                } else {
                    cout << "Failed to cast vote.\n";
                }
                break;
            }
            
            case 2:
                db.displayRegions();
                break;
            
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void resultsAndStatisticsMenu(ElectionDatabase& db) {
    while (true) {
        cout << "\n--- Results & Statistics ---\n";
        cout << "1. Display Election Results\n";
        cout << "2. Find Winner\n";
        cout << "3. View Election Statistics\n";
        cout << "4. View Regional Results\n";
        cout << "5. Back to Main Menu\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            ElectionUtils::clearInputBuffer();
            cout << "Invalid input!\n";
            continue;
        }
        
        if (choice == 5) break;
        
        switch (choice) {
            case 1:
                db.displayResults();
                break;
            
            case 2:
                db.findWinner();
                break;
            
            case 3: {
                ElectionStats stats = db.getStatistics();
                stats.display();
                break;
            }
            
            case 4:
                db.displayRegions();
                break;
            
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void analyticsMenu(ElectionDatabase& db) {
    ElectionAnalytics analytics(&db);
    
    while (true) {
        cout << "\n--- Analytics & Reports ---\n";
        cout << "1. Age Group Analysis\n";
        cout << "2. Party Performance by Region\n";
        cout << "3. Find Swing Regions\n";
        cout << "4. Turnout Trends\n";
        cout << "5. Predict Winner\n";
        cout << "6. Find Inactive Voters\n";
        cout << "7. Generate Comprehensive Report\n";
        cout << "8. Back to Main Menu\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            ElectionUtils::clearInputBuffer();
            cout << "Invalid input!\n";
            continue;
        }
        
        if (choice == 8) break;
        
        switch (choice) {
            case 1:
                analytics.analyzeByAgeGroup();
                break;
            
            case 2:
                analytics.analyzePartyByRegion();
                break;
            
            case 3:
                analytics.findSwingRegions();
                break;
            
            case 4:
                analytics.analyzeTurnoutTrends();
                break;
            
            case 5:
                analytics.predictWinner();
                break;
            
            case 6:
                analytics.findInactiveVoters();
                break;
            
            case 7:
                analytics.generateComprehensiveReport();
                break;
            
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void dataManagementMenu(ElectionDatabase& db) {
    while (true) {
        cout << "\n--- Data Management ---\n";
        cout << "1. Save Candidates to File\n";
        cout << "2. Save Voters to File\n";
        cout << "3. Load Candidates from File\n";
        cout << "4. Load Voters from File\n";
        cout << "5. Export Results to CSV\n";
        cout << "6. Back to Main Menu\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            ElectionUtils::clearInputBuffer();
            cout << "Invalid input!\n";
            continue;
        }
        
        if (choice == 6) break;
        
        string filename;
        ElectionUtils::clearInputBuffer();
        
        switch (choice) {
            case 1:
                cout << "Enter filename: ";
                getline(cin, filename);
                ElectionUtils::saveCandidatesToFile(db, filename);
                break;
            
            case 2:
                cout << "Enter filename: ";
                getline(cin, filename);
                ElectionUtils::saveVotersToFile(db, filename);
                break;
            
            case 3:
                cout << "Enter filename: ";
                getline(cin, filename);
                ElectionUtils::loadCandidatesFromFile(db, filename);
                break;
            
            case 4:
                cout << "Enter filename: ";
                getline(cin, filename);
                ElectionUtils::loadVotersFromFile(db, filename);
                break;
            
            case 5:
                cout << "Enter filename: ";
                getline(cin, filename);
                ElectionUtils::exportResultsToCSV(db, filename);
                break;
            
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void systemUtilitiesMenu(ElectionDatabase& db) {
    while (true) {
        cout << "\n--- System Utilities ---\n";
        cout << "1. Generate Sample Data\n";
        cout << "2. Simulate Voting\n";
        cout << "3. Validate Data\n";
        cout << "4. System Information\n";
        cout << "5. Back to Main Menu\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            ElectionUtils::clearInputBuffer();
            cout << "Invalid input!\n";
            continue;
        }
        
        if (choice == 5) break;
        
        switch (choice) {
            case 1: {
                char confirm;
                cout << "This will generate 25 candidates and 100 voters. Continue? (y/n): ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    ElectionUtils::generateSampleData(db);
                }
                break;
            }
            
            case 2: {
                int numVotes;
                cout << "Enter number of votes to simulate: ";
                cin >> numVotes;
                ElectionUtils::simulateVoting(db, numVotes);
                break;
            }
            
            case 3:
                ElectionUtils::validateData(db);
                break;
            
            case 4:
                cout << "\n" << string(60, '=') << "\n";
                cout << "         SYSTEM INFORMATION\n";
                cout << string(60, '=') << "\n";
                cout << "Version: 6.0 (Complete System)\n";
                cout << "Total Candidates: " << db.getCandidateCount() << "\n";
                cout << "Total Voters: " << db.getVoterCount() << "\n";
                cout << "Total Regions: " << db.getRegionCount() << "\n";
                cout << string(60, '=') << "\n";
                break;
            
            default:
                cout << "Invalid choice!\n";
        }
    }
}

int main() {
    ElectionDatabase db;
    
    cout << "\n" << string(60, '*') << "\n";
    cout << "    WELCOME TO COMPLETE VOTING MANAGEMENT SYSTEM\n";
    cout << "                  Version 6.0\n";
    cout << string(60, '*') << "\n";
    
    while (true) {
        displayMainMenu();
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            ElectionUtils::clearInputBuffer();
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                candidateManagementMenu(db);
                break;
            
            case 2:
                voterManagementMenu(db);
                break;
            
            case 3:
                votingOperationsMenu(db);
                break;
            
            case 4:
                resultsAndStatisticsMenu(db);
                break;
            
            case 5:
                analyticsMenu(db);
                break;
            
            case 6:
                dataManagementMenu(db);
                break;
            
            case 7:
                systemUtilitiesMenu(db);
                break;
            
            case 8:
                cout << "\n" << string(60, '=') << "\n";
                cout << "  Thank you for using the Voting Management System!\n";
                cout << "                   Goodbye!\n";
                cout << string(60, '=') << "\n\n";
                return 0;
            
            default:
                cout << "Invalid choice! Please select 1-8.\n";
        }
    }
    
    return 0;
}
