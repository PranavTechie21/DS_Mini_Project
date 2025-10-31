#ifndef VOTER_H
#define VOTER_H

#include <string>
using namespace std;

struct Voter {
    int id;
    string name;
    int age;
    int regionId;
    bool hasVoted;
    int votedFor;
    
    Voter(int i = 0, string n = "", int a = 0, int r = 0) {
        id = i;
        name = n;
        age = a;
        regionId = r;
        hasVoted = false;
        votedFor = -1;
    }
};
