#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>
using namespace std;

struct Candidate {
    int id;
    string name;
    string party;
    int regionId;
    int voteCount;
    
    Candidate(int i = 0, string n = "", string p = "", int r = 0) {
        id = i;
        name = n;
        party = p;
        regionId = r;
        voteCount = 0;
    }
    
    bool operator<(const Candidate& other) const {
        return voteCount < other.voteCount;
    }
};

#endif
