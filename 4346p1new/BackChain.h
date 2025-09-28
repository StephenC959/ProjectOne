#ifndef BACKCHAIN_H
#define BACKCHAIN_H

#include <string>
#include <vector>
#include <map>

// Declare global data structures with 'extern'
extern std::map<std::string, int> bc_conclusion_map;
extern std::map<int, std::vector<std::string>> bc_rules;
extern std::map<std::string, std::string> bc_variable_list;
extern std::map<std::string, std::string> bc_derived_global_variable_list;
extern const int BC_SLOTS_PER_RULE;

// Declare function prototypes
int search_con(const std::string& variable);
int rule_to_clause(int ruleNumber);
void update_VL_BC(int ruleNumber);
bool validate_Ri_BC(int ruleNumber, std::string& conclusion);
void Process_BC(const std::string& variable);
void backwardChainTreatments();

#endif // BACKCHAIN_H