#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;
//function prototypes
void search_cvl(double Ci);
void clause_to_rule(int Ci);
bool validate_Ri(int Ri);
void update_VL();
bool process();

//global variables
queue<string> conclusionVarQ= {};
vector<string> clauseVarList;
vector<string> rulesVarList;
vector<string> derivedConclusionList = {};

/*1. search_cvl (double variable): This function will search for an entry in the
clause variable list and, find the entry that matches the argument variable,
and return the clause number, Ci, corresponding to the matching entry.
Then, first call update_VL (Ci). Then call clause_to_rule (Ci): */

void search_cvl(string diagnoses){
    for(int i)
};

/*2. clause_to_rule (integer variable): - This function will convert Clause
number, Ci, to rule number, Ri, using the following formula. After
computing the value of Ri, it will call validate_Ri (Ri)*/

void clause_to_rule(int Ci){
    int numSlots = 1;
    int Ri = ((Ci / numSlots) + 1) * 10;
    validate_Ri(Ri);
};

/*3. update_VL (integer variable): For each variable (maximum of four)
starting location Ci, it will check whether the variable is instantiated in the
variable list. If not, it will ask the user to provide the variables' values and
instantiate them.*/

/*4. validate_Ri (integer variable): It will check if the values of the variable
in the ‘if’ clauses of the rule, Ri, are satisfied with the values in the variable
list. If they do, add the rule's conclusion to the ‘global’ derived conclusion
list and the Global Conclusion Variable Queue and return.*/
void validate_Ri(int Ri){


    if(!rulesVarList[Ri].empty()){
        if((rulesVarList.find(Ri)) == rulesVarList.end()){
            conclusionVarQ.push(rulesVarList.at(Ri));
            derivedConclusionList.push_back(rulesVarList.at(Ri));
        }
    }

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



    rulesVarList =     {"Antipsychotic Medication","Social Support","",                //rule 1-4
                        "Antipsychotic Medication","Mood Stabilizers","Therapy",       //rule 5-8
                        "Psychotherapy","SSRIs/SNRIs","",                              //rule 9-12
                        "Psychotherapy","Sleep Regulation","Mood Stabilizers",         //rule 13-16
                        "Long Term Therapy","SSRIs/SNRIs","",                          //rule 17-20
                        "SSRIs/SNRIs","","",                                           //rule 21-24
                        "SSRIs/SNRIs","","",                                           //rule 24-28
                        "Therapy","Long Term Psychotherapy","",                        //rule 29-32
                        "No Treatments Needed","",""};                                 //rule 33-36

    //Clauses for each rule
    clauseVarList{
        "Schizoprenia",                             //clause 1
        "Schizo-Affective Disorder",                //clause 2
        "Major Depressive Disorder",                //clause 3
        "Bipolar Disorder",                         //clause 4
        "Dysthymia",                                //clause 5
        "Generalized Anxiety Disorder",             //clause 6
        "Panic Disorder with Agoraphobia",          //clause 7
        "Dissociative Identity Disorder",           //clause 8
        "No Diagnoses"                              //clause 9
    };

    //TODO add known variables to global knownVariables


    return 0;
}
