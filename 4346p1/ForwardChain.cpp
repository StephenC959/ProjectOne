#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <cctype>

using namespace std;
//function prototypes
int search_cvl(string diagnoses);
void clause_to_rule(int Ci);
void validate_Ri(int Ri);
void update_VL(int Ci);
void process(string diagnoses);

//global variables
queue<string> conclusionVarQ= {};
vector<string> clauseVarList;
vector<string> rulesVarList;
vector<string> derivedConclusionList = {};
vector<string> varList;

/*1. search_cvl (double variable): This function will search for an entry in the
clause variable list and, find the entry that matches the argument variable,
and return the clause number, Ci, corresponding to the matching entry.
Then, first call update_VL (Ci). Then call clause_to_rule (Ci): */

int search_cvl(string diagnoses){
    //make diagnoses lowercase
    std::transform(diagnoses.begin(), diagnoses.end(), diagnoses.begin(),
    [](unsigned char c){ return std::tolower(c); });

    for(int i = 0; i < clauseVarList.size(); i++){
        if(diagnoses == clauseVarList.at(i)){
            update_VL(i);
            clause_to_rule(i);
            return i;
        }
    }
    return 0;
};

/*2. clause_to_rule (integer variable): - This function will convert Clause
number, Ci, to rule number, Ri, using the following formula. After
computing the value of Ri, it will call validate_Ri (Ri)*/

void clause_to_rule(int Ci){
    int numSlots = 3;
    int Ri = Ci * numSlots;
    validate_Ri(Ri);
};

/*3. update_VL (integer variable): For each variable (maximum of four)
starting location Ci, it will check whether the variable is instantiated in the
variable list. If not, it will ask the user to provide the variables' values and
instantiate them.*/

void update_VL(int Ci){
    bool valid = false;

    for(int i = Ci; i < Ci + 4  && i < clauseVarList.size(); i++){
        for(int j = 0; j < varList.size(); j++){
            if(clauseVarList.at(i) == varList.at(j)){
                valid = true;
                break;
            }
        }
    }

    if(!valid)
        varList.push_back(clauseVarList.at(Ci));
}

/*4. validate_Ri (integer variable): It will check if the values of the variable
in the �if� clauses of the rule, Ri, are satisfied with the values in the variable
list. If they do, add the rule's conclusion to the �global� derived conclusion
list and the Global Conclusion Variable Queue and return.*/
void validate_Ri(int Ri){

    bool valid = false;

    for(int j = 0; j < varList.size(); j++){
        if(varList.at(j) == clauseVarList.at(Ri/3)){
            valid = true;
            break;
        }
    }

    if(valid) {
        for(int i = Ri; i < Ri + 3; i++){
            if(!rulesVarList.at(i).empty()){
                conclusionVarQ.push(rulesVarList.at(i));
                derivedConclusionList.push_back(rulesVarList.at(i));
            }
        }
    }




};

/*5. process (variable)
a. Instantiate the value of the variable in the variable list. Call
search_cvl(variable)
b. return*/

void process(string diagnoses){
    bool exists = false;
    //check if diagnoses is already in variable list
    if(varList.size() != 0){
       for(int i = 0; i < varList.size();i++){
            if(diagnoses == varList.at(i))
                exists = true;
        }
    }

    //if not in variable list then push and call search cvl
    if(!exists){
       varList.push_back(diagnoses);
       search_cvl(diagnoses);
    }
};

/*6. FC_main function
Declaration of the FC_main function
� Write functions� prototypes.
� Declare variables and arrays.
� Create a list of rules. It may need some organization. Determine
which format you want to use for efficient processing by the
Validate_Ri function.
� Create a Variable List as an array.
� Create a Clause Variable list as an array.
� Create a Global Conclusion variable queue as an array.
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


void forwardChainTreatments(){

    rulesVarList =  {
        "Antipsychotic Medication","Social Support","",                //rule 1-3
        "Antipsychotic Medication","Mood Stabilizers","Therapy",       //rule 4-6
        "Psychotherapy","SSRIs/SNRIs","",                              //rule 7-9
        "Psychotherapy","Sleep Regulation","Mood Stabilizers",         //rule 10-12
        "Long Term Therapy","SSRIs/SNRIs","",                          //rule 13-15
        "SSRIs/SNRIs","","",                                           //rule 16-18
        "SSRIs/SNRIs","","",                                           //rule 19-21
        "Therapy","Long Term Psychotherapy","",                        //rule 22-24
        "No Treatments Needed","",""                                   //rule 25-27
    };

    //Clauses for each rule
    clauseVarList = {
        "schizophrenia",                             //clause 1
        "schizo-affective disorder",                //clause 2
        "major depressive disorder",                //clause 3
        "bipolar disorder",                         //clause 4
        "dysthymia",                                //clause 5
        "generalized anxiety disorder",             //clause 6
        "panic disorder with agoraphobia",          //clause 7
        "dissociative identity disorder",           //clause 8
        "no diagnoses"                              //clause 9
    };

    string done = "not";
    string input;
    string next;
    vector<string> testCase = {};


//get diagnoses
    while(done != "done"){
            cout << "Enter Diagnoses:(Enter 'done' when done) " << endl;
            getline(cin, input);
            if(input != "done"){
                testCase.push_back(input);
            }
            else{
                done = "done";
            }
    }

//load global conclusion variable queue
    for(int i = 0; i < testCase.size(); i++){
        if(!testCase.at(i).empty()){
            process(testCase.at(i));
        }
    }

//process all variables
    while(!conclusionVarQ.empty()){
            next = conclusionVarQ.front();
            conclusionVarQ.pop();
            process(next);
    }

//print all of the derived conclusions
    cout << "Recommended treatments: " << endl;
    if(derivedConclusionList.empty())
        cout << "No Diagnoses Provided";
    for(int i = 0; i < derivedConclusionList.size(); i++){
        cout << derivedConclusionList.at(i) << endl;
    }
}
