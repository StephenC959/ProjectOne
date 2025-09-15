#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;
//function prototypes
double search_cvl();
void clause_to_rule(int Ci, string rules[9], string clause[9][3]);
bool validate_Ri(int Ri, string rules[9], string clause[9][3]);
void update_VL();
bool process();
//global variables
queue<string> conclusionVarQ;
vector<string> knownVariables = {};
vector<string> derivedConclusionList = {};
/*1. search_cvl (double variable): This function will search for an entry in the
clause variable list and, find the entry that matches the argument variable,
and return the clause number, Ci, corresponding to the matching entry.
Then, first call update_VL (Ci). Then call clause_to_rule (Ci): */

double search_cvl(int){

};

/*2. clause_to_rule (integer variable): - This function will convert Clause
number, Ci, to rule number, Ri, using the following formula. After
computing the value of Ri, it will call validate_Ri (Ri)*/

void clause_to_rule(int Ci, string rules[9], string clause[9][3]){
    int Ri = ((Ci / 9) + 1) * 10;

    if(validate_Ri(Ri, rules, clause))
        validate_Ri(Ri, rules, clause);
    else
        cout << "Unsuccessful!" << endl;
};

/*3. update_VL (integer variable): For each variable (maximum of four)
starting location Ci, it will check whether the variable is instantiated in the
variable list. If not, it will ask the user to provide the variables' values and
instantiate them.*/

/*4. validate_Ri (integer variable): It will check if the values of the variable
in the ‘if’ clauses of the rule, Ri, are satisfied with the values in the variable
list. If they do, add the rule's conclusion to the ‘global’ derived conclusion
list and the Global Conclusion Variable Queue and return.*/
bool validate_Ri(int Ri, string rules[9], string clause[9][3]){
    int RiIndex = (Ri / 10) - 1;
    bool valid = true;

    if(!rules[Ri].empty()){
        if(std::find(knownVariables.begin(), knownVariables.end(),rules[Ri]) == knownVariables.end()){
            valid = false;
        }
    }
    if(valid){
        for(int i = 0; i < 3; i++){
            if(!clause[Ri][i].empty())
                conclusionVarQ.push(clause[Ri][i]);
        }
        return true;
    }
    return false;
};

/*5. process (variable)
a. Instantiate the value of the variable in the variable list. Call
search_cvl(variable)
b. return*/

/*6. FC_main function
Declaration of the FC_main function
• Write functions’ prototypes.
• Declare variables and arrays.
• Create a list of rules. It may need some organization. Determine
which format you want to use for efficient processing by the
Validate_Ri function.
• Create a Variable List as an array.
• Create a Clause Variable list as an array.
• Create a Global Conclusion variable queue as an array.
Processing of the main function:
a. Read the value of the given variable (the variable whose value is
provided) and call process (variable)
b. If the Global Conclusion Variable Queue is not empty, in a
loop, call process (variable) for each variable in the Global
Conclusion Variable Queue, which occurs in the clause
variable list. After the function returns, it will delete the
variable from the Global Conclusion Variable Queue.
c. Print all the derived conclusions from the Derived
Conclusion List*/


int FCmain(){



    string rules[9] = {
        "Schizophrenia",                    //rule 10
        "Schizo-Affective Disorder",        //rule 20
        "Major Depressive Disorder",        //rule 30
        "Bipolar Disorder",                 //rule 40
        "Dysthymia",                        //rule 50
        "Generalized Anxiety Disorder",     //rule 60
        "Panic Disorder with Agoraphobia",  //rule 70
        "Dissociative Identity Disorder",   //rule 80
        "No Diagnoses"                      //rule 90
    };
    //Clauses for each rule
    string clauses[9][3]{
        {"Antipsychotic	Medication","Social Support",""},           //rule 10
        {"Antipsychotic	Medication","Mood Stabilizers","Therapy"},  //rule 20
        {"Psychotherapy","SSRIs/SNRIs",""},                         //rule 30
        {"Psychotherapy","Sleep Regulation","Mood Stabilizers"},    //rule 40
        {"Long Term Therapy","SSRIs/SNRIs",""},                     //rule 50
        {"SSRIs/SNRIs","",""},                                      //rule 60
        {"SSRIs/SNRIs","",""},                                      //rule 70
        {"Therapy","Long Term Psychotherapy",""},                   //rule 80
        {"No Treatments Needed","",""}                              //rule 90
    };

    //TODO add known variables to global knownVariables


    return 0;
}
