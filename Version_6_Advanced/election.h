#ifndef ELECTION_H
#define ELECTION_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

// Candidate Structure
struct Candidate {
    int id;
    string name;
    string party;
    string region;
    int votes;
    int age;
    string qualification;
    
    Candidate() : id(0), name(""), party(""), region(""), votes(0), age(0), qualification("") {}
    
    Candidate(int cid, const string& cname, const string& cparty, 
              const string& creg, int cage = 0, const string& cqual = "")
        : id(cid), name(cname), party(cparty), region(creg), 
          votes(0), age(cage), qualification(cqual) {}
    
    void display() const {
        cout << left << setw(8) << id
             << setw(25) << name
             << setw(20) << party
             << setw(15) << region
             << setw(8) << votes
             << setw(6) << age
             << setw(20) << qualification << "\n";
    }
    
    void displayDetailed() const {
        cout << "\n" << string(60, '=') << "\n";
        cout << "Candidate ID: " << id << "\n";
        cout << "Name: " << name << "\n";
        cout << "Party: " << party << "\n";
        cout << "Region: " << region << "\n";
        cout << "Age: " << age << "\n";
        cout << "Qualification: " << qualification << "\n";
        cout << "Total Votes: " << votes << "\n";
        cout << string(60, '=') << "\n";
    }
};

// Voter Structure
struct Voter {
    int id;
    string name;
    string region;
    int age;
    bool hasVoted;
    time_t voteTime;
    int votedFor;
    
    Voter() : id(0), name(""), region(""), age(0), hasVoted(false), 
              voteTime(0), votedFor(-1) {}
    
    Voter(int vid, const string& vname, const string& vreg, int vage)
        : id(vid), name(vname), region(vreg), age(vage), 
          hasVoted(false), voteTime(0), votedFor(-1) {}
    
    void display() const {
        cout << left << setw(10) << id
             << setw(25) << name
             << setw(15) << region
             << setw(6) << age
             << setw(12) << (hasVoted ? "Voted" : "Not Voted");
        
        if (hasVoted && voteTime > 0) {
            char timeStr[20];
            strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M", localtime(&voteTime));
            cout << setw(20) << timeStr;
        }
        cout << "\n";
    }
};

// Election Statistics
struct ElectionStats {
    int totalCandidates;
    int totalVoters;
    int totalVotesCast;
    double voterTurnout;
    string leadingParty;
    int maxVotes;
    map<string, int> partyWiseVotes;
    map<string, int> regionWiseVotes;
    
    ElectionStats() : totalCandidates(0), totalVoters(0), totalVotesCast(0),
                      voterTurnout(0.0), leadingParty(""), maxVotes(0) {}
    
    void display() const {
        cout << "\n" << string(70, '=') << "\n";
        cout << "               ELECTION STATISTICS\n";
        cout << string(70, '=') << "\n";
        cout << "Total Candidates Registered: " << totalCandidates << "\n";
        cout << "Total Voters Registered: " << totalVoters << "\n";
        cout << "Total Votes Cast: " << totalVotesCast << "\n";
        cout << fixed << setprecision(2);
        cout << "Voter Turnout: " << voterTurnout << "%\n";
        cout << "Leading Party: " << leadingParty << " (" << maxVotes << " votes)\n";
        
        cout << "\n--- Party-wise Vote Distribution ---\n";
        for (const auto& pair : partyWiseVotes) {
            double percentage = (totalVotesCast > 0) ? 
                (pair.second * 100.0 / totalVotesCast) : 0.0;
            cout << left << setw(25) << pair.first 
                 << ": " << pair.second << " votes (" 
                 << percentage << "%)\n";
        }
        
        cout << "\n--- Region-wise Vote Distribution ---\n";
        for (const auto& pair : regionWiseVotes) {
            cout << left << setw(20) << pair.first 
                 << ": " << pair.second << " votes\n";
        }
        cout << string(70, '=') << "\n";
    }
};

// Region/Constituency Structure
struct Region {
    string name;
    int totalVoters;
    int votesPolled;
    vector<int> candidateIds;
    
    Region() : name(""), totalVoters(0), votesPolled(0) {}
    Region(const string& n) : name(n), totalVoters(0), votesPolled(0) {}
    
    double getTurnout() const {
        return (totalVoters > 0) ? (votesPolled * 100.0 / totalVoters) : 0.0;
    }
    
    void display() const {
        cout << left << setw(20) << name
             << setw(15) << totalVoters
             << setw(15) << votesPolled
             << fixed << setprecision(2)
             << setw(12) << getTurnout() << "%\n";
    }
};

#endif // ELECTION_H
