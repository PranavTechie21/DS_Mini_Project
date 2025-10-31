#ifndef ANALYTICS_H
#define ANALYTICS_H

#include "database.h"
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

class ElectionAnalytics {
private:
    ElectionDatabase* db;
    
public:
    ElectionAnalytics(ElectionDatabase* database) : db(database) {}
    
    // Analyze voting patterns by age group
    void analyzeByAgeGroup() {
        map<string, int> ageGroups;
        ageGroups["18-25"] = 0;
        ageGroups["26-35"] = 0;
        ageGroups["36-50"] = 0;
        ageGroups["51-65"] = 0;
        ageGroups["65+"] = 0;
        
        map<string, int> votedInGroup;
        votedInGroup["18-25"] = 0;
        votedInGroup["26-35"] = 0;
        votedInGroup["36-50"] = 0;
        votedInGroup["51-65"] = 0;
        votedInGroup["65+"] = 0;
        
        for (const auto& voter : db->getAllVoters()) {
            string group;
            if (voter.age >= 18 && voter.age <= 25) group = "18-25";
            else if (voter.age >= 26 && voter.age <= 35) group = "26-35";
            else if (voter.age >= 36 && voter.age <= 50) group = "36-50";
            else if (voter.age >= 51 && voter.age <= 65) group = "51-65";
            else group = "65+";
            
            ageGroups[group]++;
            if (voter.hasVoted) {
                votedInGroup[group]++;
            }
        }
        
        cout << "\n" << string(70, '=') << "\n";
        cout << "           AGE GROUP VOTING ANALYSIS\n";
        cout << string(70, '=') << "\n";
        cout << left << setw(15) << "Age Group"
             << setw(20) << "Total Voters"
             << setw(20) << "Voted"
             << setw(15) << "Turnout" << "\n";
        cout << string(70, '=') << "\n";
        
        for (const auto& pair : ageGroups) {
            double turnout = (pair.second > 0) ? 
                (votedInGroup[pair.first] * 100.0 / pair.second) : 0.0;
            
            cout << left << setw(15) << pair.first
                 << setw(20) << pair.second
                 << setw(20) << votedInGroup[pair.first]
                 << fixed << setprecision(2)
                 << turnout << "%\n";
        }
        cout << string(70, '=') << "\n";
    }
    
    // Analyze party performance by region
    void analyzePartyByRegion() {
        map<string, map<string, int>> regionPartyVotes;
        
        for (const auto& candidate : db->getAllCandidates()) {
            regionPartyVotes[candidate.region][candidate.party] += candidate.votes;
        }
        
        cout << "\n" << string(80, '=') << "\n";
        cout << "         PARTY PERFORMANCE BY REGION\n";
        cout << string(80, '=') << "\n";
        
        for (const auto& regionPair : regionPartyVotes) {
            cout << "\nRegion: " << regionPair.first << "\n";
            cout << string(60, '-') << "\n";
            
            vector<pair<string, int>> partyVotes(
                regionPair.second.begin(), regionPair.second.end()
            );
            
            sort(partyVotes.begin(), partyVotes.end(),
                 [](const pair<string, int>& a, const pair<string, int>& b) {
                     return a.second > b.second;
                 });
            
            for (const auto& party : partyVotes) {
                cout << "  " << left << setw(30) << party.first 
                     << ": " << party.second << " votes\n";
            }
        }
        cout << string(80, '=') << "\n";
    }
    
    // Find swing regions (close races)
    void findSwingRegions() {
        map<string, vector<int>> regionVotes;
        
        for (const auto& candidate : db->getAllCandidates()) {
            regionVotes[candidate.region].push_back(candidate.votes);
        }
        
        cout << "\n" << string(70, '=') << "\n";
        cout << "           SWING REGION ANALYSIS\n";
        cout << string(70, '=') << "\n";
        cout << "Regions with close races (vote difference < 20%):\n\n";
        
        for (auto& pair : regionVotes) {
            if (pair.second.size() < 2) continue;
            
            sort(pair.second.begin(), pair.second.end(), greater<int>());
            
            int first = pair.second[0];
            int second = pair.second[1];
            int total = 0;
            for (int v : pair.second) total += v;
            
            if (total > 0) {
                double diff = abs(first - second) * 100.0 / total;
                if (diff < 20.0) {
                    cout << "  " << left << setw(20) << pair.first
                         << " - Difference: " << fixed << setprecision(2) 
                         << diff << "%\n";
                }
            }
        }
        cout << string(70, '=') << "\n";
    }
    
    // Voter turnout trends
    void analyzeTurnoutTrends() {
        const auto& regions = db->getAllRegions();
        
        if (regions.empty()) {
            cout << "\nNo regions data available.\n";
            return;
        }
        
        vector<pair<string, double>> turnouts;
        for (const auto& pair : regions) {
            turnouts.push_back({pair.first, pair.second.getTurnout()});
        }
        
        sort(turnouts.begin(), turnouts.end(),
             [](const pair<string, double>& a, const pair<string, double>& b) {
                 return a.second > b.second;
             });
        
        cout << "\n" << string(60, '=') << "\n";
        cout << "        VOTER TURNOUT BY REGION\n";
        cout << string(60, '=') << "\n";
        cout << left << setw(25) << "Region" 
             << setw(20) << "Turnout" << "\n";
        cout << string(60, '-') << "\n";
        
        for (const auto& pair : turnouts) {
            cout << left << setw(25) << pair.first
                 << fixed << setprecision(2)
                 << pair.second << "%\n";
        }
        cout << string(60, '=') << "\n";
        
        // Calculate average
        double avgTurnout = 0;
        for (const auto& pair : turnouts) {
            avgTurnout += pair.second;
        }
        if (!turnouts.empty()) {
            avgTurnout /= turnouts.size();
            cout << "Average Turnout: " << fixed << setprecision(2) 
                 << avgTurnout << "%\n";
        }
    }
    
    // Predict winner based on current trends
    void predictWinner() {
        const auto& candidates = db->getAllCandidates();
        
        if (candidates.empty()) {
            cout << "\nNo candidates available.\n";
            return;
        }
        
        int totalVotes = 0;
        for (const auto& c : candidates) {
            totalVotes += c.votes;
        }
        
        if (totalVotes == 0) {
            cout << "\nNo votes cast yet. Cannot predict winner.\n";
            return;
        }
        
        vector<Candidate> sorted = candidates;
        sort(sorted.begin(), sorted.end(),
             [](const Candidate& a, const Candidate& b) {
                 return a.votes > b.votes;
             });
        
        cout << "\n" << string(70, '=') << "\n";
        cout << "           WINNER PREDICTION\n";
        cout << string(70, '=') << "\n";
        
        if (sorted.size() > 0) {
            double winPercentage = (totalVotes > 0) ? 
                (sorted[0].votes * 100.0 / totalVotes) : 0.0;
            
            cout << "Current Leader: " << sorted[0].name << "\n";
            cout << "Party: " << sorted[0].party << "\n";
            cout << "Votes: " << sorted[0].votes << " (" 
                 << fixed << setprecision(2) << winPercentage << "%)\n\n";
            
            if (sorted.size() > 1) {
                double runnerUpPercentage = (totalVotes > 0) ? 
                    (sorted[1].votes * 100.0 / totalVotes) : 0.0;
                cout << "Runner-up: " << sorted[1].name << "\n";
                cout << "Votes: " << sorted[1].votes << " (" 
                     << runnerUpPercentage << "%)\n\n";
                
                double margin = winPercentage - runnerUpPercentage;
                cout << "Lead Margin: " << margin << "%\n\n";
                
                if (margin > 10) {
                    cout << "Prediction: Strong lead. Likely winner.\n";
                } else if (margin > 5) {
                    cout << "Prediction: Moderate lead. Competitive race.\n";
                } else {
                    cout << "Prediction: Very close race. Too close to call.\n";
                }
            }
        }
        cout << string(70, '=') << "\n";
    }
    
    // Generate comprehensive report
    void generateComprehensiveReport() {
        cout << "\n" << string(80, '=') << "\n";
        cout << "              COMPREHENSIVE ELECTION REPORT\n";
        cout << string(80, '=') << "\n";
        
        ElectionStats stats = db->getStatistics();
        stats.display();
        
        cout << "\n";
        analyzeTurnoutTrends();
        
        cout << "\n";
        analyzeByAgeGroup();
        
        cout << "\n";
        analyzePartyByRegion();
        
        cout << "\n";
        findSwingRegions();
        
        cout << "\n";
        predictWinner();
    }
    
    // Identify inactive voters
    void findInactiveVoters() {
        vector<Voter> inactive;
        
        for (const auto& voter : db->getAllVoters()) {
            if (!voter.hasVoted) {
                inactive.push_back(voter);
            }
        }
        
        cout << "\n" << string(70, '=') << "\n";
        cout << "           INACTIVE VOTERS\n";
        cout << string(70, '=') << "\n";
        cout << "Total Inactive Voters: " << inactive.size() << "\n";
        
        if (!inactive.empty()) {
            cout << "\nSample of inactive voters:\n";
            cout << string(70, '-') << "\n";
            
            int displayCount = min(10, (int)inactive.size());
            for (int i = 0; i < displayCount; i++) {
                cout << "  ID: " << inactive[i].id 
                     << " | Name: " << inactive[i].name
                     << " | Region: " << inactive[i].region << "\n";
            }
            
            if (inactive.size() > 10) {
                cout << "... and " << (inactive.size() - 10) << " more\n";
            }
        }
        cout << string(70, '=') << "\n";
    }
};

#endif // ANALYTICS_H
