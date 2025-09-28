#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// --- Global Data Structures ---
map<string, int> bc_conclusion_map;
map<int, vector<string>> bc_rules;
map<string, string> bc_variable_list;
map<string, string> bc_derived_global_variable_list;

const int SLOTS_PER_RULE = 4;

// --- Function Prototypes ---
int search_con(const string& variable);
int rule_to_clause(int ruleNumber);
void update_VL_BC(int ruleNumber);
bool validate_Ri_BC(int ruleNumber, string& conclusion);
void Process_BC(const string& variable);

/*
* 1. search_con: Finds the rule that concludes the given variable (goal).
*/
int search_con(const string& variable) {
    if (bc_conclusion_map.count(variable)) {
        return bc_conclusion_map.at(variable);
    }
    return -1;
}

/*
* 2. rule_to_clause: Converts a rule number to its clause number.
*/
int rule_to_clause(int ruleNumber) {
    return SLOTS_PER_RULE * (ruleNumber - 1) + 1;
}

/*
* 3. update_VL_BC: Asks user for symptom values.
*/
void update_VL_BC(int ruleNumber) {
    auto it = bc_rules.find(ruleNumber);
    if (it != bc_rules.end()) {
        const auto& variables = it->second;
        for (const auto& var : variables) {
            if (bc_variable_list.find(var) == bc_variable_list.end()) {
                if (bc_conclusion_map.count(var)) {
                    Process_BC(var);
                    if (bc_variable_list.find(var) != bc_variable_list.end()) {
                        continue;
                    }
                }
                string answer;
                cout << "Does the patient have the symptom '" << var << "'? (yes/no): ";
                cin >> answer;
                bc_variable_list[var] = (answer == "yes" || answer == "y") ? "yes" : "no";
            }
        }
    }
}

/*
* 4. validate_Ri_BC: Checks if a rule's conditions are met.
*/
bool validate_Ri_BC(int ruleNumber, string& conclusion) {
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
* 5. Process_BC: The main backward chaining algorithm.
*/
void Process_BC(const string& variable) {
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
        update_VL_BC(ruleNumber);
        string conclusion = "";
        if (validate_Ri_BC(ruleNumber, conclusion)) {
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
void backwardChainTreatments() {
    // --- Initialize Knowledge Base for Backward Chaining (Diagnosis) ---
    bc_conclusion_map = {
        {"Bipolar Disorder", 1}, {"Bipolar Disorder", 2}, {"Bipolar Disorder", 3}, {"Bipolar Disorder", 4},
        {"Schizophrenia", 5}, {"Schizophrenia", 6}, {"Schizophrenia", 7}, {"Schizophrenia", 8},
        {"Schizo-Affective Disorder", 9}, {"Schizo-Affective Disorder", 10}, {"Schizo-Affective Disorder", 11},
        {"Major Depressive Disorder", 12}, {"Major Depressive Disorder", 13}, {"Major Depressive Disorder", 14}, {"Major Depressive Disorder", 15},
        {"Panic Disorder with Agoraphobia", 16}, {"Panic Disorder with Agoraphobia", 17}, {"Panic Disorder with Agoraphobia", 18}, {"Panic Disorder with Agoraphobia", 19},
        {"Dissociative Identity Disorder", 20}, {"Dissociative Identity Disorder", 21}, {"Dissociative Identity Disorder", 22},
        {"Dysthymia", 23}, {"Dysthymia", 24}, {"Dysthymia", 25}, {"Dysthymia", 26},
        {"Generalized Anxiety Disorder", 27}, {"Generalized Anxiety Disorder", 28}, {"Generalized Anxiety Disorder", 29}, {"Generalized Anxiety Disorder", 30}
    };

    // The rules link a rule number to its "if" clauses (symptoms).
    bc_rules[1] = {"patient_has_elated_mood", "patient_has_racing_thoughts", "patient_has_increased_energy"};
    bc_rules[2] = {"patient_has_grandiosity", "patient_has_decreased_need_for_sleep", "patient_talks_excessively"};
    bc_rules[3] = {"patient_has_agitation", "patient_has_reckless_behavior", "patient_has_distractibility"};
    bc_rules[4] = {"patient_has_depressed_mood", "patient_has_loss_of_interest", "patient_has_fatigue"};
    bc_rules[5] = {"patient_has_delusions", "patient_has_hallucinations", "patient_has_disorganized_speech"};
    bc_rules[6] = {"patient_has_grossly_disorganized_behavior", "patient_has_catatonic_behavior"};
    bc_rules[7] = {"patient_has_negative_symptoms", "patient_has_alogia"};
    bc_rules[8] = {"patient_has_avolition", "patient_has_anhedonia"};
    bc_rules[9] = {"patient_has_schizophrenia_symptoms", "patient_has_mood_disorder_symptoms"};
    bc_rules[10] = {"patient_has_delusions", "patient_has_depressed_mood"};
    bc_rules[11] = {"patient_has_hallucinations", "patient_has_manic_episode"};
    bc_rules[12] = {"patient_has_depressed_mood", "patient_has_anhedonia", "patient_has_weight_change"};
    bc_rules[13] = {"patient_has_sleep_disturbance", "patient_has_fatigue", "patient_has_feelings_of_worthlessness"};
    bc_rules[14] = {"patient_has_indecisiveness", "patient_has_thoughts_of_death"};
    bc_rules[15] = {"patient_has_psychomotor_agitation", "patient_has_self_blame"};
    bc_rules[16] = {"patient_has_recurrent_panic_attacks", "patient_has_fear_of_public_spaces"};
    bc_rules[17] = {"patient_avoids_public_transportation", "patient_avoids_crowds"};
    bc_rules[18] = {"patient_avoids_enclosed_spaces", "patient_avoids_open_spaces"};
    bc_rules[19] = {"patient_fears_being_helpless", "patient_fears_embarrassment"};
    bc_rules[20] = {"patient_has_amnesia", "patient_has_two_or_more_identities"};
    bc_rules[21] = {"patient_has_sense_of_detachment", "patient_has_blurred_identity"};
    bc_rules[22] = {"patient_has_severe_stress", "patient_has_anxiety_and_depression_symptoms"};
    bc_rules[23] = {"patient_has_sadness_for_most_of_the_day", "patient_has_low_self_esteem"};
    bc_rules[24] = {"patient_has_sleep_problems", "patient_has_fatigue", "patient_has_poor_appetite"};
    bc_rules[25] = {"patient_avoids_social_activities", "patient_has_feelings_of_hopelessness"};
    bc_rules[26] = {"patient_has_low_energy", "patient_has_irritability"};
    bc_rules[27] = {"patient_has_persistent_worrying", "patient_has_difficulty_controlling_worry"};
    bc_rules[28] = {"patient_has_restlessness", "patient_is_easily_fatigued"};
    bc_rules[29] = {"patient_has_muscle_tension", "patient_has_sleep_disturbance"};
    bc_rules[30] = {"patient_has_irritability", "patient_has_difficulty_concentrating"};

    cout << "--- Mental Health Expert System (Backward Chaining) ---" << endl;

    string final_diagnosis = "";
    string diagnoses_to_try[] = {"Bipolar Disorder", "Schizophrenia", "Schizo-Affective Disorder", "Major Depressive Disorder", "Panic Disorder with Agoraphobia", "Dissociative Identity Disorder", "Dysthymia", "Generalized Anxiety Disorder"};
    
    for (const auto& diagnosis_goal : diagnoses_to_try) {
        bc_variable_list.clear();
        bc_derived_global_variable_list.clear();
        Process_BC(diagnosis_goal);
        
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
}