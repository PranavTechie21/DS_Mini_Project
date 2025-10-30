#ifndef VOTER_H
#define VOTER_H

#include <string>
using namespace std;

enum VoterType {
    NORMAL = 1,
    VIP = 2
};

struct Voter {
    int id;
    string name;
    int age;
    VoterType type;
    bool hasVoted;
    int votedFor;
    
    Voter(int i = 0, string n = "", int a = 0, VoterType t = NORMAL) {
        id = i;
        name = n;
        age = a;
        type = t;
        hasVoted = false;
        votedFor = -1;
    }
    
    double getVoteWeight() const {
        return (type == VIP) ? 2.0 : 1.0;
    }
    
    string getVoterTypeString() const {
        return (type == VIP) ? "VIP" : "Normal";
    }
};

#endif
