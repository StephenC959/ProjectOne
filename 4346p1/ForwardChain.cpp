/*1. search_cvl (double variable): This function will search for an entry in the
clause variable list and, find the entry that matches the argument variable,
and return the clause number, Ci, corresponding to the matching entry.
Then, first call update_VL (Ci). Then call clause_to_rule (Ci): */

/*2. clause_to_rule (integer variable): - This function will convert Clause
number, Ci, to rule number, Ri, using the following formula. After
computing the value of Ri, it will call validate_Ri (Ri):
If the clause numbers in the clause variable list are sequenced like
1,2,3,4,5, ......), the formula is:
Rule # = [({Quotient (Clause # / 4)} +1)]

If the rule numbers are sequenced like 10,20,30,40,50, ......), the formula is:
Rule # = [({Quotient (Clause # / 4)} +1) * 10]

It has been assumed that four slots have been assigned for each rule in the
Clause Variable list. If a number other than four has been assigned, replace
4 with that number.*/

/*3. update_VL (integer variable): For each variable (maximum of four)
starting location Ci, it will check whether the variable is instantiated in the
variable list. If not, it will ask the user to provide the variables' values and
instantiate them.*/

/*4. validate_Ri (integer variable): It will check if the values of the variable
in the ‘if’ clauses of the rule, Ri, are satisfied with the values in the variable
list. If they do, add the rule's conclusion to the ‘global’ derived conclusion
list and the Global Conclusion Variable Queue and return.*/

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
