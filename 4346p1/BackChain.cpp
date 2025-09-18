#include <iostream>
/*search_con (string variable): with passing the variable as a parameter
(variable). This function will find the matching variable in the conclusion list
and the corresponding rule number, Ri.*/


/*2. rule_to_clause (integer variable): - This function will convert Rule # Ri
to clause number Ci using the following formula. If the rule numbers are
sequenced like 1,2,3,4,5, ......), formula is:

CLAUSE NUMBER (Ci) = 4* (RULE NUMBER (Ri) - 1) + 1
If the rule numbers are sequenced like 10,20,30,40,50, ......), formula is:
CLAUSE NUMBER = 4* (RULE NUMBER / 10 - 1) + 1

It has been assumed that four slots have been assigned for each rule in the
Clause Variable list. If a ‘number’ other than four has been assigned,
replace 4 with that number.*/

/*3. update_VL (integer variable): with passing Ci to it. It will all questions
and will instantiate all (maximum of 4) variables starting from the location
Ci in the variable list. If the variable is not in the variable list, it could be in
the then clause of some rule. call Process (variable) to find its value-it will
be a recursive call.*/


/*4. validate_Ri (integer variable, string conclusion): with passing, Ri,
to it. It will check if the values of the variables in the ‘if’ clauses of
the rule, Ri, are satisfied with the values in the variable list and
the derived global variable list. If they do, it will assign the
conclusion of the rule to the variable conclusion; otherwise, it will
not assign any value, and then it will return.*/


/*5. Process (variable)
o Start a loop. In each cycle of the loop, do the following:
o call search_con (variable) by passing the goal variable as a parameter
(variable). It will find the matching variable in the conclusion list and
the corresponding rule number, Ri.
o call Rule_to_clause (Ri) by passing Ri as a parameter. This function
will convert the rule number, Ri, to clause number, Ci.
o call Update_VL (Ci) with passing Ci to it. It may ask questions and will
instantiate all (maximum of 4) variables starting from the location Ci
in the variable list. If the variable is not in the variable list, it could be
in the then clause of some rule. call Process (variable) to find its
value-it will be a recursive call.
o Initialize conclusion to null and call Validate_Ri (Ri,
Conclusion) with passing, Ri, to it. This function will check if
the values of the variables in the ‘if’ clauses of the rule, Ri,
are satisfied with the values in the variable list and the
derived global variable list. If they do, it will assign the
conclusion of the rule to the conclusion variable. Save the
value of the conclusion variable in the derived global
variable list and return. If the values of the variables in the
‘if’ clauses of the rule, Ri, are not satisfied with the values in
the variable list and the derived global variable list, use the
‘continue’ statement to continue the loop. It will repeat the
process with the next entry of the conclusion list.*/


/*6. main function
Declaration
(you are allowed to declare variables and lists global)
• Write functions’ prototypes
• Declare variables and arrays
• Create a list of rules. It may need some organization. Determine
which format you want to use for efficient processing by the
Validate_Ri function.
• Create a Variable List (could be an array).
• Create a conclusion list (could be an array).
• Create a Clause Variable list (could be an array).
• Create the Derived Global Variable list.
Processing in the main function:
o Identify the Goal variable (the variable whose value needs to be
determined)
o call Process ( Goal variable)*/

int BCmain(){

    string clauses[9] = {
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
    //Rules for each clause
    string rules [9][3] = {
        {"Feels sick","Having hallucinations",""},                                //rule 10
        {"Feels sick","Unusually sad/tired","Having hallucinations"},             //rule 20
        {"Feels sick","Unusually sad/tired",""},                                  //rule 30
        {"Feels sick","Unusually sad/tired","Bouts of elation/mania",},           //rule 40
        {"Feels sick","Unusually sad/tired","Depressive spurts intermittent"},    //rule 50
        {"Feels sick","Feels anxious",""},                                        //rule 60
        {"Feels sick","Feels anxious","Crowds cause anxiety"},                                      //rule 70
        {"Feels sick","Feels anxious","Blurred sense of personality"},                   //rule 80
        {"Doesn't feel sick","",""}                              //rule 90
    };

    //TODO add known variables to global knownVariables


    return 0;
}

/*o After the program is complete, check if the derived global variable
list contains the goal variable and is not null. If it does, that is the
answer to processing the backward chaining. Print the value of the
variable and pass it to the Forward chaining program. If it is null,
print a comment that the Goal cannot be determined.*/

void basicFunction(){
    std::cout << "This Works";
}
