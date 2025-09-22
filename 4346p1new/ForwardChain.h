#ifndef FORWARDCHAIN_H_INCLUDED
#define FORWARDCHAIN_H_INCLUDED

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <cctype>

using namespace std;

// Global variables
extern queue<string> conclusionVarQ;
extern vector<string> clauseVarList;
extern vector<string> rulesVarList;
extern vector<string> derivedConclusionList;
extern vector<string> varList;

// Function prototypes
int search_cvl(string diagnoses);
void clause_to_rule(int Ci);
void validate_Ri(int Ri);
void update_VL(int Ci);
void process(string diagnoses);
void forwardChainTreatments();


#endif // FORWARDCHAIN_H_INCLUDED
