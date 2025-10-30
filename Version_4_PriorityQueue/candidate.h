#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>
using namespace std;

struct Candidate {
    int id;
    string name;
    string party;
    int voteCount;
    double weightedVotes;
    
    Candidate(int i = 0, string n = "", string p = "") {
        id = i;
        name = n;
        party = p;
        voteCount = 0;
        weightedVotes = 0.0;
    }
    
    // For Max Heap - higher weighted votes = higher priority
    bool operator<(const Candidate& other) const {
        if (weightedVotes == other.weightedVotes) {
            return voteCount < other.voteCount;
        }
        return weightedVotes < other.weightedVotes;
    }
};

#endif
