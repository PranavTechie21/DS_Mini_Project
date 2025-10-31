#ifndef REGION_H
#define REGION_H

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include "candidate.h"
#include "voter.h"

using namespace std;

class Region {
private:
    int id;
    string name;
    vector<Candidate*> candidates;
    vector<Voter*> voters;
    unordered_map<int, Candidate*> candidateMap;
    unordered_map<int, Voter*> voterMap;
    
public:
    Region(int i, string n) : id(i), name(n) {}
    
    int getId() const { return id; }
    string getName() const { return name; }
    
    void addCandidate(Candidate* c) {
        candidates.push_back(c);
        candidateMap[c->id] = c;
    }
    
    void addVoter(Voter* v) {
        voters.push_back(v);
        voterMap[v->id] = v;
    }
    
    Candidate* getCandidateById(int id) {
        if (candidateMap.find(id) != candidateMap.end()) {
            return candidateMap[id];
        }
        return nullptr;
    }
    
    Voter* getVoterById(int id) {
        if (voterMap.find(id) != voterMap.end()) {
            return voterMap[id];
        }
        return nullptr;
    }
    
    Candidate* getWinner() {
        if (candidates.empty()) return nullptr;
        
        Candidate* winner = candidates[0];
        for (auto c : candidates) {
            if (c->voteCount > winner->voteCount) {
                winner = c;
            }
        }
        return winner;
    }
    
    int getTotalVotes() {
        int total = 0;
        for (auto c : candidates) {
            total += c->voteCount;
        }
        return total;
    }
    
    double getTurnout() {
        if (voters.empty()) return 0.0;
        int voted = 0;
        for (auto v : voters) {
            if (v->hasVoted) voted++;
        }
        return (voted * 100.0) / voters.size();
    }
    
    vector<Candidate*>& getCandidates() { return candidates; }
    vector<Voter*>& getVoters() { return voters; }
};

#endif
