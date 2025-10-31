#ifndef UTILS_H
#define UTILS_H

#include "database.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

class ElectionUtils {
public:
    // Save data to file
    static bool saveCandidatesToFile(const ElectionDatabase& db, const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << "\n";
            return false;
        }
        
        file << "ID,Name,Party,Region,Votes,Age,Qualification\n";
        for (const auto& c : db.getAllCandidates()) {
            file << c.id << ","
                 << c.name << ","
                 << c.party << ","
                 << c.region << ","
                 << c.votes << ","
                 << c.age << ","
                 << c.qualification << "\n";
        }
        
        file.close();
        cout << "Candidates saved to " << filename << "\n";
        return true;
    }
    
    static bool saveVotersToFile(const ElectionDatabase& db, const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << "\n";
            return false;
        }
        
        file << "ID,Name,Region,Age,HasVoted,VotedFor\n";
        for (const auto& v : db.getAllVoters()) {
            file << v.id << ","
                 << v.name << ","
                 << v.region << ","
                 << v.age << ","
                 << (v.hasVoted ? "1" : "0") << ","
                 << v.votedFor << "\n";
        }
        
        file.close();
        cout << "Voters saved to " << filename << "\n";
        return true;
    }
    
    // Load data from file
    static bool loadCandidatesFromFile(ElectionDatabase& db, const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << "\n";
            return false;
        }
        
        string line;
        getline(file, line); // Skip header
        
        int count = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string item;
            vector<string> tokens;
            
            while (getline(ss, item, ',')) {
                tokens.push_back(item);
            }
            
            if (tokens.size() >= 7) {
                Candidate c;
                c.id = stoi(tokens[0]);
                c.name = tokens[1];
                c.party = tokens[2];
                c.region = tokens[3];
                c.votes = stoi(tokens[4]);
                c.age = stoi(tokens[5]);
                c.qualification = tokens[6];
                
                if (db.addCandidate(c)) {
                    count++;
                }
            }
        }
        
        file.close();
        cout << "Loaded " << count << " candidates from " << filename << "\n";
        return true;
    }
    
    static bool loadVotersFromFile(ElectionDatabase& db, const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << "\n";
            return false;
        }
        
        string line;
        getline(file, line); // Skip header
        
        int count = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string item;
            vector<string> tokens;
            
            while (getline(ss, item, ',')) {
                tokens.push_back(item);
            }
            
            if (tokens.size() >= 6) {
                Voter v;
                v.id = stoi(tokens[0]);
                v.name = tokens[1];
                v.region = tokens[2];
                v.age = stoi(tokens[3]);
                v.hasVoted = (tokens[4] == "1");
                v.votedFor = stoi(tokens[5]);
                
                if (db.addVoter(v)) {
                    count++;
                }
            }
        }
        
        file.close();
        cout << "Loaded " << count << " voters from " << filename << "\n";
        return true;
    }
    
    // Generate sample data
    static void generateSampleData(ElectionDatabase& db) {
        srand(time(nullptr));
        
        vector<string> parties = {"Democratic Party", "Republican Party", 
                                 "Independent", "Green Party", "Liberal Party"};
        vector<string> regions = {"North District", "South District", 
                                 "East District", "West District", "Central District"};
        vector<string> qualifications = {"Graduate", "Post-Graduate", "PhD", 
                                        "Professional", "Diploma"};
        
        vector<string> firstNames = {"John", "Jane", "Michael", "Sarah", "David",
                                    "Emily", "Robert", "Lisa", "James", "Mary"};
        vector<string> lastNames = {"Smith", "Johnson", "Williams", "Brown", "Jones",
                                   "Garcia", "Miller", "Davis", "Rodriguez", "Martinez"};
        
        // Generate candidates
        cout << "\nGenerating sample candidates...\n";
        for (int i = 0; i < 25; i++) {
            Candidate c;
            c.id = 1000 + i;
            c.name = firstNames[rand() % firstNames.size()] + " " + 
                    lastNames[rand() % lastNames.size()];
            c.party = parties[rand() % parties.size()];
            c.region = regions[rand() % regions.size()];
            c.age = 25 + rand() % 45; // 25-70 years
            c.qualification = qualifications[rand() % qualifications.size()];
            
            db.addCandidate(c);
        }
        
        // Generate voters
        cout << "Generating sample voters...\n";
        for (int i = 0; i < 100; i++) {
            Voter v;
            v.id = 5000 + i;
            v.name = firstNames[rand() % firstNames.size()] + " " + 
                    lastNames[rand() % lastNames.size()];
            v.region = regions[rand() % regions.size()];
            v.age = 18 + rand() % 62; // 18-80 years
            
            db.addVoter(v);
        }
        
        cout << "Sample data generated successfully!\n";
        cout << "25 candidates and 100 voters created.\n";
    }
    
    // Simulate voting
    static void simulateVoting(ElectionDatabase& db, int numVotes) {
        srand(time(nullptr));
        
        const auto& voters = db.getAllVoters();
        const auto& candidates = db.getAllCandidates();
        
        if (voters.empty() || candidates.empty()) {
            cout << "Error: No voters or candidates available.\n";
            return;
        }
        
        int successfulVotes = 0;
        int attempts = 0;
        
        while (successfulVotes < numVotes && attempts < numVotes * 3) {
            int voterIdx = rand() % voters.size();
            const Voter& voter = voters[voterIdx];
            
            if (!voter.hasVoted) {
                // Find candidates in same region
                vector<int> candidatesInRegion;
                for (const auto& c : candidates) {
                    if (c.region == voter.region) {
                        candidatesInRegion.push_back(c.id);
                    }
                }
                
                if (!candidatesInRegion.empty()) {
                    int candidateId = candidatesInRegion[rand() % candidatesInRegion.size()];
                    
                    if (db.castVote(voter.id, candidateId)) {
                        successfulVotes++;
                    }
                }
            }
            attempts++;
        }
        
        cout << "\nSimulation complete: " << successfulVotes 
             << " votes cast successfully.\n";
    }
    
    // Data validation
    static void validateData(const ElectionDatabase& db) {
        cout << "\n" << string(70, '=') << "\n";
        cout << "           DATA VALIDATION REPORT\n";
        cout << string(70, '=') << "\n";
        
        int issues = 0;
        
        // Check for duplicate IDs
        set<int> candidateIds;
        for (const auto& c : db.getAllCandidates()) {
            if (candidateIds.count(c.id)) {
                cout << "Warning: Duplicate candidate ID found: " << c.id << "\n";
                issues++;
            }
            candidateIds.insert(c.id);
        }
        
        set<int> voterIds;
        for (const auto& v : db.getAllVoters()) {
            if (voterIds.count(v.id)) {
                cout << "Warning: Duplicate voter ID found: " << v.id << "\n";
                issues++;
            }
            voterIds.insert(v.id);
        }
        
        // Check for invalid ages
        for (const auto& c : db.getAllCandidates()) {
            if (c.age < 25 || c.age > 100) {
                cout << "Warning: Invalid candidate age: " << c.name 
                     << " (Age: " << c.age << ")\n";
                issues++;
            }
        }
        
        for (const auto& v : db.getAllVoters()) {
            if (v.age < 18 || v.age > 120) {
                cout << "Warning: Invalid voter age: " << v.name 
                     << " (Age: " << v.age << ")\n";
                issues++;
            }
        }
        
        if (issues == 0) {
            cout << "All data validated successfully. No issues found.\n";
        } else {
            cout << "\nTotal issues found: " << issues << "\n";
        }
        cout << string(70, '=') << "\n";
    }
    
    // Clear input buffer
    static void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    // Display progress bar
    static void displayProgressBar(int current, int total, int barWidth = 50) {
        float progress = (float)current / total;
        int pos = barWidth * progress;
        
        cout << "[";
        for (int i = 0; i < barWidth; i++) {
            if (i < pos) cout << "=";
            else if (i == pos) cout << ">";
            else cout << " ";
        }
        cout << "] " << int(progress * 100.0) << "%\r";
        cout.flush();
        
        if (current == total) cout << "\n";
    }
    
    // Export results to CSV
    static bool exportResultsToCSV(const ElectionDatabase& db, const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not create file " << filename << "\n";
            return false;
        }
        
        // Get sorted candidates
        vector<Candidate> sorted = db.getAllCandidates();
        sort(sorted.begin(), sorted.end(),
             [](const Candidate& a, const Candidate& b) {
                 return a.votes > b.votes;
             });
        
        int totalVotes = 0;
        for (const auto& c : sorted) {
            totalVotes += c.votes;
        }
        
        file << "Rank,ID,Name,Party,Region,Votes,Percentage\n";
        for (size_t i = 0; i < sorted.size(); i++) {
            double percentage = (totalVotes > 0) ? 
                (sorted[i].votes * 100.0 / totalVotes) : 0.0;
            
            file << (i + 1) << ","
                 << sorted[i].id << ","
                 << sorted[i].name << ","
                 << sorted[i].party << ","
                 << sorted[i].region << ","
                 << sorted[i].votes << ","
                 << fixed << setprecision(2) << percentage << "\n";
        }
        
        file.close();
        cout << "Results exported to " << filename << "\n";
        return true;
    }
};

#endif // UTILS_H
