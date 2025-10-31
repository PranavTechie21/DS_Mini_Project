#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <map>
#include "candidate.h"
#include "voter.h"
#include "region.h"
#include "graph.h"

using namespace std;

class VotingSystem {
private:
    unordered_map<int, Region*> regions;
    unordered_map<int, Candidate*> allCandidates;
    unordered_map<int, Voter*> allVoters;
    unordered_map<int, int> voterIdToGraphIndex;  // Map voter ID to graph index
    Graph* voterNetwork;
    int graphSize;
    int nextGraphIndex;
    
public:
    VotingSystem() {
        graphSize = 10000;  // Max voters
        voterNetwork = new Graph(graphSize);
        nextGraphIndex = 0;
    }
    
    void createRegion(int id, string name) {
        if (regions.find(id) != regions.end()) {
            cout << "\n   ❌ Region ID " << id << " already exists!\n";
            return;
        }
        
        Region* newRegion = new Region(id, name);
        regions[id] = newRegion;
        
        cout << "\n   ✅ Region '" << name << "' created successfully!\n";
    }
    
    void addCandidate(int id, string name, string party, int regionId) {
        if (regions.find(regionId) == regions.end()) {
            cout << "\n   ❌ Region ID " << regionId << " does not exist!\n";
            return;
        }
        
        if (allCandidates.find(id) != allCandidates.end()) {
            cout << "\n   ❌ Candidate ID " << id << " already exists!\n";
            return;
        }
        
        Candidate* newCandidate = new Candidate(id, name, party, regionId);
        allCandidates[id] = newCandidate;
        regions[regionId]->addCandidate(newCandidate);
        
        cout << "\n   ✅ Candidate '" << name << "' from '" << party 
             << "' added to region '" << regions[regionId]->getName() << "'!\n";
    }
    
    void registerVoter(int id, string name, int age, int regionId) {
        if (regions.find(regionId) == regions.end()) {
            cout << "\n   ❌ Region ID " << regionId << " does not exist!\n";
            return;
        }
        
        if (allVoters.find(id) != allVoters.end()) {
            cout << "\n   ❌ Voter ID " << id << " already exists!\n";
            return;
        }
        
        if (age < 18) {
            cout << "\n   ❌ Voter must be at least 18 years old!\n";
            return;
        }
        
        Voter* newVoter = new Voter(id, name, age, regionId);
        allVoters[id] = newVoter;
        regions[regionId]->addVoter(newVoter);
        
        // Add to graph
        voterIdToGraphIndex[id] = nextGraphIndex++;
        
        cout << "\n   ✅ Voter '" << name << "' registered in region '" 
             << regions[regionId]->getName() << "'!\n";
    }
    
    void addVoterConnection(int voterId1, int voterId2) {
        if (allVoters.find(voterId1) == allVoters.end()) {
            cout << "\n   ❌ Voter ID " << voterId1 << " not found!\n";
            return;
        }
        
        if (allVoters.find(voterId2) == allVoters.end()) {
            cout << "\n   ❌ Voter ID " << voterId2 << " not found!\n";
            return;
        }
        
        int idx1 = voterIdToGraphIndex[voterId1];
        int idx2 = voterIdToGraphIndex[voterId2];
        
        voterNetwork->addEdge(idx1, idx2);
        
        cout << "\n   ✅ Connection added between " << allVoters[voterId1]->name 
             << " and " << allVoters[voterId2]->name << "!\n";
    }
    
    void castVote(int voterId, int candidateId) {
        if (allVoters.find(voterId) == allVoters.end()) {
            cout << "\n   ❌ Voter ID " << voterId << " not registered!\n";
            return;
        }
        
        Voter* voter = allVoters[voterId];
        
        if (voter->hasVoted) {
            cout << "\n   ❌ Voter '" << voter->name << "' has already voted!\n";
            return;
        }
        
        if (allCandidates.find(candidateId) == allCandidates.end()) {
            cout << "\n   ❌ Candidate ID " << candidateId << " does not exist!\n";
            return;
        }
        
        Candidate* candidate = allCandidates[candidateId];
        
        if (voter->regionId != candidate->regionId) {
            cout << "\n   ❌ Cannot vote for candidate from different region!\n";
            return;
        }
        
        candidate->voteCount++;
        voter->hasVoted = true;
        voter->votedFor = candidateId;
        
        cout << "\n   ✅ Vote cast successfully!\n";
        cout << "   Voter: " << voter->name << "\n";
        cout << "   Voted for: " << candidate->name << " (" << candidate->party << ")\n";
        cout << "   Region: " << regions[voter->regionId]->getName() << "\n";
    }
    
    void displayRegionalResults(int regionId) {
        if (regions.find(regionId) == regions.end()) {
            cout << "\n   ❌ Region ID " << regionId << " not found!\n";
            return;
        }
        
        Region* region = regions[regionId];
        vector<Candidate*> candidates = region->getCandidates();
        
        if (candidates.empty()) {
            cout << "\n   No candidates in this region.\n";
            return;
        }
        
        cout << "\n   ═══════════════════════════════════════════════════════════\n";
        cout << "   📊 REGIONAL RESULTS: " << region->getName() << "\n";
        cout << "   ═══════════════════════════════════════════════════════════\n";
        
        int totalVotes = region->getTotalVotes();
        Candidate* winner = region->getWinner();
        
        cout << "   🏆 WINNER: " << winner->name << " (" << winner->party << ")\n";
        cout << "   Votes: " << winner->voteCount << "\n";
        cout << "   ───────────────────────────────────────────────────────────\n";
        cout << "   " << left << setw(25) << "Candidate" 
             << setw(20) << "Party" 
             << setw(10) << "Votes" 
             << setw(10) << "%" << "\n";
        cout << "   ───────────────────────────────────────────────────────────\n";
        
        for (auto c : candidates) {
            double percentage = (totalVotes > 0) ? 
                (c->voteCount * 100.0 / totalVotes) : 0;
            
            cout << "   " << left << setw(25) << c->name
                 << setw(20) << c->party
                 << setw(10) << c->voteCount
                 << fixed << setprecision(2) << setw(10) << percentage << "%\n";
        }
        
        cout << "   ═══════════════════════════════════════════════════════════\n";
        cout << "   Total Votes: " << totalVotes << "\n";
        cout << "   Turnout: " << fixed << setprecision(2) 
             << region->getTurnout() << "%\n";
    }
    
    void displayOverallResults() {
        if (regions.empty()) {
            cout << "\n   No regions created.\n";
            return;
        }
        
        map<string, int> partyVotes;  // Party → Total votes
        
        for (auto& pair : allCandidates) {
            Candidate* c = pair.second;
            partyVotes[c->party] += c->voteCount;
        }
        
        cout << "\n   ═══════════════════════════════════════════════════════════\n";
        cout << "   🌐 OVERALL RESULTS (ALL REGIONS)\n";
        cout << "   ═══════════════════════════════════════════════════════════\n";
        cout << "   " << left << setw(30) << "Party" << setw(15) << "Total Votes" << "\n";
        cout << "   ───────────────────────────────────────────────────────────\n";
        
        for (auto& pair : partyVotes) {
            cout << "   " << left << setw(30) << pair.first 
                 << setw(15) << pair.second << "\n";
        }
        
        cout << "   ═══════════════════════════════════════════════════════════\n";
    }
    
    void displayAllRegions() {
        if (regions.empty()) {
            cout << "\n   No regions created.\n";
            return;
        }
        
        cout << "\n   ═══════════════════════════════════════════════════════════\n";
        cout << "   🗺️  ALL REGIONS\n";
        cout << "   ═══════════════════════════════════════════════════════════\n";
        cout << "   " << left << setw(8) << "ID" 
             << setw(25) << "Name" 
             << setw(12) << "Candidates"
             << setw(10) << "Voters"
             << setw(12) << "Turnout" << "\n";
        cout << "   ───────────────────────────────────────────────────────────\n";
        
        for (auto& pair : regions) {
            Region* r = pair.second;
            cout << "   " << left << setw(8) << r->getId()
                 << setw(25) << r->getName()
                 << setw(12) << r->getCandidates().size()
                 << setw(10) << r->getVoters().size()
                 << fixed << setprecision(1) << setw(12) 
                 << r->getTurnout() << "%\n";
        }
        cout << "   ═══════════════════════════════════════════════════════════\n";
    }
    
    void findConnectedVoters(int voterId) {
        if (allVoters.find(voterId) == allVoters.end()) {
            cout << "\n   ❌ Voter ID " << voterId << " not found!\n";
            return;
        }
        
        int graphIdx = voterIdToGraphIndex[voterId];
        vector<int> connected = voterNetwork->BFS(graphIdx);
        
        cout << "\n   ═══════════════════════════════════════\n";
        cout << "   🔗 CONNECTED VOTERS (BFS Traversal)\n";
        cout << "   Starting from: " << allVoters[voterId]->name << "\n";
        cout << "   ═══════════════════════════════════════\n";
        
        if (connected.size() <= 1) {
            cout << "   No connections found.\n";
        } else {
            cout << "   Connected voters (" << connected.size() << "):\n";
            for (int idx : connected) {
                // Find voter ID from graph index
                for (auto& pair : voterIdToGraphIndex) {
                    if (pair.second == idx && pair.first != voterId) {
                        Voter* v = allVoters[pair.first];
                        cout << "   - " << v->name << " (ID: " << v->id << ")\n";
                    }
                }
            }
        }
        cout << "   ═══════════════════════════════════════\n";
    }
    
    void detectFraudPatterns() {
        cout << "\n   ═══════════════════════════════════════════════════════════\n";
        cout << "   🔍 FRAUD DETECTION ANALYSIS\n";
        cout << "   ═══════════════════════════════════════════════════════════\n";
        
        vector<vector<int>> components = voterNetwork->getConnectedComponents();
        bool fraudFound = false;
        
        for (auto& component : components) {
            if (component.size() >= 3) {  // Threshold: groups of 3+
                // Check if all voted for same candidate
                map<int, int> voteDistribution;
                int votedCount = 0;
                
                for (int idx : component) {
                    for (auto& pair : voterIdToGraphIndex) {
                        if (pair.second == idx) {
                            Voter* v = allVoters[pair.first];
                            if (v->hasVoted) {
                                voteDistribution[v->votedFor]++;
                                votedCount++;
                            }
                        }
                    }
                }
                
                if (votedCount >= 3) {
                    for (auto& vote : voteDistribution) {
                        double similarity = (vote.second * 100.0) / votedCount;
                        
                        if (similarity >= 80.0) {  // 80%+ similarity threshold
                            fraudFound = true;
                            cout << "\n   ⚠️  SUSPICIOUS PATTERN DETECTED!\n";
                            cout << "   Connected Group Size: " << component.size() << "\n";
                            cout << "   Voters who voted: " << votedCount << "\n";
                            cout << "   All voted for: Candidate ID " << vote.first;
                            if (allCandidates.find(vote.first) != allCandidates.end()) {
                                cout << " (" << allCandidates[vote.first]->name << ")";
                            }
                            cout << "\n   Vote Similarity: " << fixed << setprecision(1) 
                                 << similarity << "%\n";
                            cout << "   ───────────────────────────────────────────────────────────\n";
                        }
                    }
                }
            }
        }
        
        if (!fraudFound) {
            cout << "\n   ✅ No suspicious patterns detected.\n";
            cout << "   Voting appears normal.\n";
        }
        
        cout << "\n   Network Statistics:\n";
        cout << "   Total Voters: " << allVoters.size() << "\n";
        cout << "   Connected Components: " << components.size() << "\n";
        cout << "   Total Connections: " << voterNetwork->getEdgeCount() << "\n";
        cout << "   ═══════════════════════════════════════════════════════════\n";
    }
    
    void crossRegionAnalysis() {
        if (regions.size() < 2) {
            cout << "\n   Need at least 2 regions for cross-region analysis.\n";
            return;
        }
        
        cout << "\n   ═══════════════════════════════════════════════════════════\n";
        cout << "   📈 CROSS-REGION ANALYSIS\n";
        cout << "   ═══════════════════════════════════════════════════════════\n";
        
        for (auto& pair : regions) {
            Region* r = pair.second;
            Candidate* winner = r->getWinner();
            
            cout << "\n   Region: " << r->getName() << "\n";
            cout << "   Winner: " << winner->name << " (" << winner->party << ")\n";
            cout << "   Total Votes: " << r->getTotalVotes() << "\n";
            cout << "   Turnout: " << fixed << setprecision(2) 
                 << r->getTurnout() << "%\n";
            cout << "   ───────────────────────────────────────────────────────────\n";
        }
        
        cout << "   ═══════════════════════════════════════════════════════════\n";
    }
    
    void displayStatistics() {
        cout << "\n   ═══════════════════════════════════════\n";
        cout << "   📊 SYSTEM STATISTICS\n";
        cout << "   ═══════════════════════════════════════\n";
        cout << "   Total Regions: " << regions.size() << "\n";
        cout << "   Total Candidates: " << allCandidates.size() << "\n";
        cout << "   Total Voters: " << allVoters.size() << "\n";
        
        int votedCount = 0;
        for (auto& pair : allVoters) {
            if (pair.second->hasVoted) votedCount++;
        }
        
        double overallTurnout = (allVoters.size() > 0) ? 
            (votedCount * 100.0 / allVoters.size()) : 0;
        
        cout << "   Votes Cast: " << votedCount << "\n";
        cout << "   Overall Turnout: " << fixed << setprecision(2) 
             << overallTurnout << "%\n";
        cout << "   Voter Connections: " << voterNetwork->getEdgeCount() << "\n";
        cout << "   ═══════════════════════════════════════\n";
    }
    
    ~VotingSystem() {
        delete voterNetwork;
        for (auto& pair : regions) delete pair.second;
        for (auto& pair : allCandidates) delete pair.second;
        for (auto& pair : allVoters) delete pair.second;
    }
};

void displayMenu() {
    cout << "\n╔════════════════════════════════════════════════╗\n";
    cout << "║   VOTING SYSTEM V5 - GRAPH & ANALYTICS        ║\n";
    cout << "╠════════════════════════════════════════════════╣\n";
    cout << "║  1.  Create Region/Constituency                ║\n";
    cout << "║  2.  Add Candidate to Region                   ║\n";
    cout << "║  3.  Register Voter in Region                  ║\n";
    cout << "║  4.  Add Voter Connection (Network)            ║\n";
    cout << "║  5.  Cast Vote                                 ║\n";
    cout << "║  6.  Display Regional Results                  ║\n";
    cout << "║  7.  Display Overall Results                   ║\n";
    cout << "║  8.  Display All Regions                       ║\n";
    cout << "║  9.  Find Connected Voters (BFS)               ║\n";
    cout << "║  10. Detect Fraud Patterns (DFS)               ║\n";
    cout << "║  11. Cross-Region Analysis                     ║\n";
    cout << "║  12. Display Statistics                        ║\n";
    cout << "║  13. Exit                                      ║\n";
    cout << "╚════════════════════════════════════════════════╝\n";
    cout << "Enter your choice: ";
}

int main() {
    VotingSystem vs;
    int choice;
    
    cout << "\n╔════════════════════════════════════════════════╗\n";
    cout << "║  Welcome to Voting Management System V5       ║\n";
    cout << "║  Graph-Based Regional Analytics               ║\n";
    cout << "╚════════════════════════════════════════════════╝\n";
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                int id;
                string name;
                cout << "\nEnter Region ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Region Name: ";
                getline(cin, name);
                vs.createRegion(id, name);
                break;
            }
            
            case 2: {
                int id, regionId;
                string name, party;
                cout << "\nEnter Candidate ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Candidate Name: ";
                getline(cin, name);
                cout << "Enter Party Name: ";
                getline(cin, party);
                cout << "Enter Region ID: ";
                cin >> regionId;
                vs.addCandidate(id, name, party, regionId);
                break;
            }
            
            case 3: {
                int id, age, regionId;
                string name;
                cout << "\nEnter Voter ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Voter Name: ";
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Region ID: ";
                cin >> regionId;
                vs.registerVoter(id, name, age, regionId);
                break;
            }
            
            case 4: {
                int id1, id2;
                cout << "\nEnter First Voter ID: ";
                cin >> id1;
                cout << "Enter Second Voter ID: ";
                cin >> id2;
                vs.addVoterConnection(id1, id2);
                break;
            }
            
            case 5: {
                int voterId, candidateId;
                cout << "\nEnter Voter ID: ";
                cin >> voterId;
                cout << "Enter Candidate ID: ";
                cin >> candidateId;
                vs.castVote(voterId, candidateId);
                break;
            }
            
            case 6: {
                int regionId;
                cout << "\nEnter Region ID: ";
                cin >> regionId;
                vs.displayRegionalResults(regionId);
                break;
            }
            
            case 7:
                vs.displayOverallResults();
                break;
            
            case 8:
                vs.displayAllRegions();
                break;
            
            case 9: {
                int voterId;
                cout << "\nEnter Voter ID to find connections: ";
                cin >> voterId;
                vs.findConnectedVoters(voterId);
                break;
            }
            
            case 10:
                vs.detectFraudPatterns();
                break;
            
            case 11:
                vs.crossRegionAnalysis();
                break;
            
            case 12:
                vs.displayStatistics();
                break;
            
            case 13:
                cout << "\n╔════════════════════════════════════════════════╗\n";
                cout << "║  Thank you for using Voting System V5!        ║\n";
                cout << "║  Goodbye!                                      ║\n";
                cout << "╚════════════════════════════════════════════════╝\n\n";
                return 0;
            
            default:
                cout << "\n   ❌ Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}
