#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// --- Global Data Structures ---
// A map to link a diagnosis (conclusion) to its rule number
map<string, int> bc_conclusion_map;
// A map to link a rule number to its "if" clauses (symptoms)
map<int, vector<string>> bc_rules;
// A map to store variables (symptoms) and their values ("yes" or "no")
map<string, string> bc_variable_list;
// A map to store variables that have been proven
map<string, string> bc_derived_global_variable_list;

const int SLOTS_PER_RULE = 4;

// --- Function Prototypes ---
int search_con(const string& variable);
int rule_to_clause(int ruleNumber);
void update_VL(int ruleNumber);
bool validate_Ri(int ruleNumber, string& conclusion);
void Process(const string& variable);

// --- Backward Chaining Function Implementations ---

/*
* 1. search_con(string variable): Finds the rule that concludes the given variable (goal).
*/
int search_con(const string& variable) {
    if (bc_conclusion_map.count(variable)) {
        return bc_conclusion_map.at(variable);
    }
    return -1; // Not found
}

/*
* 2. rule_to_clause(integer variable): Converts a rule number to its clause number.
*/
int rule_to_clause(int ruleNumber) {
    return SLOTS_PER_RULE * (ruleNumber - 1) + 1;
}

/*
* 3. update_VL(integer ruleNumber): Asks the user for symptom values.
* This is where the questions are asked.
*/
void update_VL(int ruleNumber) {
    auto it = bc_rules.find(ruleNumber);
    if (it != bc_rules.end()) {
        const auto& variables = it->second;
        for (const auto& var : variables) {
            // Check if the variable is already known
            if (bc_variable_list.find(var) == bc_variable_list.end()) {
                // If it's a conclusion of another rule, try to prove it recursively
                if (bc_conclusion_map.count(var)) {
                    Process(var);
                    // If the recursive call succeeds, skip asking
                    if (bc_variable_list.find(var) != bc_variable_list.end()) {
                        continue;
                    }
                }
                
                // If the variable is still unknown, ask the user
                string answer;
                cout << "Does the patient have the symptom '" << var << "'? (yes/no): ";
                cin >> answer;
                bc_variable_list[var] = (answer == "yes" || answer == "y") ? "yes" : "no";
            }
        }
    }
}

/*
* 4. validate_Ri(integer ruleNumber, string& conclusion): Checks if a rule's conditions are met.
*/
bool validate_Ri(int ruleNumber, string& conclusion) {
    if (bc_rules.find(ruleNumber) == bc_rules.end()) {
        return false;
    }
    const auto& conditions = bc_rules.at(ruleNumber);
    
    for (const auto& condition : conditions) {
        if (bc_variable_list.find(condition) == bc_variable_list.end() || bc_variable_list.at(condition) != "yes") {
            if (bc_derived_global_variable_list.find(condition) == bc_derived_global_variable_list.end() || bc_derived_global_variable_list.at(condition) != "yes") {
                return false;
            }
        }
    }
    
    for (const auto& pair : bc_conclusion_map) {
        if (pair.second == ruleNumber) {
            conclusion = pair.first;
            return true;
        }
    }
    return false;
}

/*
* 5. Process(variable): The main backward chaining algorithm.
*/
void Process(const string& variable) {
    cout << "\nStarting backward chaining for goal: " << variable << endl;
    
    vector<int> candidate_rules;
    for (const auto& pair : bc_conclusion_map) {
        if (pair.first == variable) {
            candidate_rules.push_back(pair.second);
        }
    }
    
    if (candidate_rules.empty()) {
        cout << "No rules found for goal: " << variable << endl;
        return;
    }

    for (int ruleNumber : candidate_rules) {
        update_VL(ruleNumber);
        
        string conclusion = "";
        if (validate_Ri(ruleNumber, conclusion)) {
            bc_derived_global_variable_list[variable] = conclusion;
            cout << "Goal '" << variable << "' successfully derived with value: " << conclusion << endl;
            return;
        } else {
            cout << "Rule " << ruleNumber << " failed. Trying next rule if available." << endl;
        }
    }
    
    cout << "Goal '" << variable << "' could not be determined." << endl;
}

/*
* The main function for this module.
*/
int main() {
    // --- Initialize Knowledge Base for Backward Chaining (Diagnosis) ---
    // The conclusion map links a diagnosis string to its rule number.
    bc_conclusion_map = {
        {"Bipolar Disorder", 1},
        {"Schizophrenia", 2},
        {"Schizo-Affective Disorder", 3},
        {"Major Depressive Disorder", 4},
        {"Panic Disorder with Agoraphobia", 5},
        {"Dissociative Identity Disorder", 6},
        {"Dysthymia", 7},
        {"Generalized Anxiety Disorder", 8}
    };

    // The rules link a rule number to its "if" clauses (symptoms).
    bc_rules[1] = {"patient_has_elated_mood", "patient_has_increased_energy", "patient_has_racing_thoughts", "patient_has_mood_swings"};
    bc_rules[2] = {"patient_has_hallucinations", "patient_has_delusions", "patient_has_disorganized_speech", "patient_has_lack_of_motivation"};
    bc_rules[3] = {"symptoms_of_schizophrenia", "symptoms_of_depression_or_mania", "persistent_symptoms_for_2_weeks"};
    bc_rules[4] = {"patient_has_depressed_mood", "patient_has_anhedonia", "patient_has_sleep_disturbances", "patient_has_feelings_of_worthlessness"};
    bc_rules[5] = {"patient_experiences_panic_attacks", "patient_avoids_crowds", "patient_avoids_open_spaces", "patient_avoids_public_transport"};
    bc_rules[6] = {"patient_has_amnesia", "patient_feels_detached", "patient_has_blurred_identity", "patient_has_distinct_identities"};
    bc_rules[7] = {"patient_has_persistent_sadness", "patient_has_low_self_esteem", "patient_avoids_social_activities", "patient_has_poor_appetite_or_overeating"};
    bc_rules[8] = {"patient_has_persistent_worrying", "patient_has_difficulty_concentrating", "patient_has_muscle_tension", "patient_has_trouble_sleeping"};

    cout << "--- Mental Health Expert System (Backward Chaining) ---" << endl;

    string final_diagnosis = "";
    string diagnoses_to_try[] = {"Bipolar Disorder", "Schizophrenia", "Major Depressive Disorder", "Panic Disorder with Agoraphobia", "Dissociative Identity Disorder", "Dysthymia", "Generalized Anxiety Disorder", "Schizo-Affective Disorder"};
    
    for (const auto& diagnosis_goal : diagnoses_to_try) {
        bc_variable_list.clear();
        bc_derived_global_variable_list.clear();
        Process(diagnosis_goal);
        
        if (bc_derived_global_variable_list.count(diagnosis_goal)) {
            final_diagnosis = bc_derived_global_variable_list[diagnosis_goal];
            break; 
        }
    }
    
    if (final_diagnosis.empty()) {
        cout << "\nNo diagnosis could be determined from the symptoms provided." << endl;
    } else {
        cout << "\nFinal Diagnosis: " << final_diagnosis << endl;
    }

    return 0;
}