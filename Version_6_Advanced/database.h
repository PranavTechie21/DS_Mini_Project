#ifndef DATABASE_H
#define DATABASE_H

#include "election.h"
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class ElectionDatabase {
private:
    vector<Candidate> candidates;
    vector<Voter> voters;
    map<string, Region> regions;
    
public:
    // Candidate Management
    bool addCandidate(const Candidate& candidate) {
        // Check if ID already exists
        for (const auto& c : candidates) {
            if (c.id == candidate.id) {
                return false;
            }
        }
        
        candidates.push_back(candidate);
        
        // Update region
        if (regions.find(candidate.region) == regions.end()) {
            regions[candidate.region] = Region(candidate.region);
        }
        regions[candidate.region].candidateIds.push_back(candidate.id);
        
        return true;
    }
    
    bool deleteCandidate(int id) {
        for (auto it = candidates.begin(); it != candidates.end(); ++it) {
            if (it->id == id) {
                // Remove from region
                auto& region = regions[it->region];
                region.candidateIds.erase(
                    remove(region.candidateIds.begin(), 
                           region.candidateIds.end(), id),
                    region.candidateIds.end()
                );
                
                candidates.erase(it);
                return true;
            }
        }
        return false;
    }
    
    Candidate* findCandidate(int id) {
        for (auto& c : candidates) {
            if (c.id == id) {
                return &c;
            }
        }
        return nullptr;
    }
    
    vector<Candidate> getCandidatesByRegion(const string& region) {
        vector<Candidate> result;
        for (const auto& c : candidates) {
            if (c.region == region) {
                result.push_back(c);
            }
        }
        return result;
    }
    
    vector<Candidate> getCandidatesByParty(const string& party) {
        vector<Candidate> result;
        for (const auto& c : candidates) {
            if (c.party == party) {
                result.push_back(c);
            }
        }
        return result;
    }
    
    // Voter Management
    bool addVoter(const Voter& voter) {
        for (const auto& v : voters) {
            if (v.id == voter.id) {
                return false;
            }
        }
        
        voters.push_back(voter);
        
        // Update region
        if (regions.find(voter.region) == regions.end()) {
            regions[voter.region] = Region(voter.region);
        }
        regions[voter.region].totalVoters++;
        
        return true;
    }
    
    Voter* findVoter(int id) {
        for (auto& v : voters) {
            if (v.id == id) {
                return &v;
            }
        }
        return nullptr;
    }
    
    bool castVote(int voterId, int candidateId) {
        Voter* voter = findVoter(voterId);
        Candidate* candidate = findCandidate(candidateId);
        
        if (!voter || !candidate) {
            return false;
        }
        
        if (voter->hasVoted) {
            return false;
        }
        
        // Check if voter and candidate are from same region
        if (voter->region != candidate->region) {
            cout << "Error: Voter can only vote in their registered region!\n";
            return false;
        }
        
        voter->hasVoted = true;
        voter->voteTime = time(nullptr);
        voter->votedFor = candidateId;
        candidate->votes++;
        regions[candidate->region].votesPolled++;
        
        return true;
    }
    
    // Display Functions
    void displayAllCandidates() {
        if (candidates.empty()) {
            cout << "\nNo candidates registered.\n";
            return;
        }
        
        cout << "\n" << string(120, '=') << "\n";
        cout << left << setw(8) << "ID"
             << setw(25) << "Name"
             << setw(20) << "Party"
             << setw(15) << "Region"
             << setw(8) << "Votes"
             << setw(6) << "Age"
             << setw(20) << "Qualification" << "\n";
        cout << string(120, '=') << "\n";
        
        for (const auto& c : candidates) {
            c.display();
        }
        cout << string(120, '=') << "\n";
        cout << "Total Candidates: " << candidates.size() << "\n";
    }
    
    void displayAllVoters() {
        if (voters.empty()) {
            cout << "\nNo voters registered.\n";
            return;
        }
        
        cout << "\n" << string(100, '=') << "\n";
        cout << left << setw(10) << "ID"
             << setw(25) << "Name"
             << setw(15) << "Region"
             << setw(6) << "Age"
             << setw(12) << "Status"
             << setw(20) << "Vote Time" << "\n";
        cout << string(100, '=') << "\n";
        
        for (const auto& v : voters) {
            v.display();
        }
        cout << string(100, '=') << "\n";
        cout << "Total Voters: " << voters.size() << "\n";
    }
    
    void displayRegions() {
        if (regions.empty()) {
            cout << "\nNo regions registered.\n";
            return;
        }
        
        cout << "\n" << string(70, '=') << "\n";
        cout << left << setw(20) << "Region"
             << setw(15) << "Total Voters"
             << setw(15) << "Votes Polled"
             << setw(12) << "Turnout" << "\n";
        cout << string(70, '=') << "\n";
        
        for (const auto& pair : regions) {
            pair.second.display();
        }
        cout << string(70, '=') << "\n";
    }
    
    // Statistics
    ElectionStats getStatistics() {
        ElectionStats stats;
        stats.totalCandidates = candidates.size();
        stats.totalVoters = voters.size();
        
        int votedCount = 0;
        for (const auto& v : voters) {
            if (v.hasVoted) {
                votedCount++;
            }
        }
        stats.totalVotesCast = votedCount;
        stats.voterTurnout = (voters.size() > 0) ? 
            (votedCount * 100.0 / voters.size()) : 0.0;
        
        // Party-wise votes
        for (const auto& c : candidates) {
            stats.partyWiseVotes[c.party] += c.votes;
            stats.regionWiseVotes[c.region] += c.votes;
            
            if (c.votes > stats.maxVotes) {
                stats.maxVotes = c.votes;
                stats.leadingParty = c.party;
            }
        }
        
        // Find leading party by total votes
        int maxPartyVotes = 0;
        for (const auto& pair : stats.partyWiseVotes) {
            if (pair.second > maxPartyVotes) {
                maxPartyVotes = pair.second;
                stats.leadingParty = pair.first;
            }
        }
        
        return stats;
    }
    
    // Results
    void displayResults() {
        if (candidates.empty()) {
            cout << "\nNo candidates registered.\n";
            return;
        }
        
        // Sort by votes
        vector<Candidate> sorted = candidates;
        sort(sorted.begin(), sorted.end(), 
             [](const Candidate& a, const Candidate& b) {
                 return a.votes > b.votes;
             });
        
        int totalVotes = 0;
        for (const auto& c : sorted) {
            totalVotes += c.votes;
        }
        
        cout << "\n" << string(110, '=') << "\n";
        cout << "                           ELECTION RESULTS\n";
        cout << string(110, '=') << "\n";
        cout << left << setw(8) << "Rank"
             << setw(25) << "Name"
             << setw(20) << "Party"
             << setw(15) << "Region"
             << setw(10) << "Votes"
             << setw(15) << "Percentage" << "\n";
        cout << string(110, '=') << "\n";
        
        for (size_t i = 0; i < sorted.size(); i++) {
            double percentage = (totalVotes > 0) ? 
                (sorted[i].votes * 100.0 / totalVotes) : 0.0;
            
            cout << left << setw(8) << (i + 1)
                 << setw(25) << sorted[i].name
                 << setw(20) << sorted[i].party
                 << setw(15) << sorted[i].region
                 << setw(10) << sorted[i].votes
                 << fixed << setprecision(2)
                 << percentage << "%\n";
        }
        cout << string(110, '=') << "\n";
        cout << "Total Votes Cast: " << totalVotes << "\n";
        cout << string(110, '=') << "\n";
    }
    
    void findWinner() {
        if (candidates.empty()) {
            cout << "\nNo candidates registered.\n";
            return;
        }
        
        Candidate* winner = &candidates[0];
        int maxVotes = winner->votes;
        bool tie = false;
        
        for (auto& c : candidates) {
            if (c.votes > maxVotes) {
                winner = &c;
                maxVotes = c.votes;
                tie = false;
            } else if (c.votes == maxVotes && c.votes > 0) {
                tie = true;
            }
        }
        
        if (maxVotes == 0) {
            cout << "\nNo votes have been cast yet.\n";
            return;
        }
        
        cout << "\n" << string(70, '=') << "\n";
        cout << "                 WINNER ANNOUNCEMENT\n";
        cout << string(70, '=') << "\n";
        
        if (tie) {
            cout << "There is a TIE with " << maxVotes << " votes!\n\n";
            cout << "Tied candidates:\n";
            for (const auto& c : candidates) {
                if (c.votes == maxVotes) {
                    cout << "  - " << c.name << " (" << c.party 
                         << ", " << c.region << ")\n";
                }
            }
        } else {
            cout << "WINNER: " << winner->name << "\n";
            cout << "Party: " << winner->party << "\n";
            cout << "Region: " << winner->region << "\n";
            cout << "Total Votes: " << winner->votes << "\n";
        }
        cout << string(70, '=') << "\n";
    }
    
    // Getters
    const vector<Candidate>& getAllCandidates() const { return candidates; }
    const vector<Voter>& getAllVoters() const { return voters; }
    const map<string, Region>& getAllRegions() const { return regions; }
    
    int getCandidateCount() const { return candidates.size(); }
    int getVoterCount() const { return voters.size(); }
    int getRegionCount() const { return regions.size(); }
};

#endif // DATABASE_H
