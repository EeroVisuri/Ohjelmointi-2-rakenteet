#include "company.hh"
#include <algorithm>


/* Description: Adds a new Employee to the datastructure.
 * Parameters:
 *  Param1: Employee's ID string
 *  Param2: Employee's department
 *  Param3: Employee's time in service
 *  Param4: Output-stream for error-printing
 * Errormessages:
 *  If employees's ID is already in datastructure:
 *      "Error. Employee already added."
 */

void Company::addNewEmployee(const std::string &id, const std::string &dep,
                             const double &time, std::ostream &output) {


    //if employee exists already, print error "Error. Employee already added."

    for (unsigned long i = 0; i < employees.size(); ++i) {
        if (employees.at(i)->id_ == id) {
            output << "Error. Employee already added." << std::endl;
            return;
        }
    }
    //otherwise if we got to here, we can create the new employee
    //and add their information into the datastructure.
    //create the new_employee object
    Employee* new_employee = new Employee;
    new_employee->department_ = (dep);
    new_employee->time_in_service_ = (time);
    employees.push_back(new_employee);

}

/* Description: Prints all stored Employees: ID, department and time in service
 * Parameters:
 *  Param1: Output-stream for printing
 * Errormessages:
 *  None.
 */


void Company::printEmployees(std::ostream &output) const {

    //for-loop for printing out all employees in the employees-vector.

    for (unsigned long i = 0; i < employees.size(); ++i) {
        output << employees.at(i)->id_ << employees.at(i)->department_ << employees.at(i)->time_in_service_ << std::endl;
    }

}

/*
 * All the following functions have the same error messages:
 *  If ID wasn't found in datastructure:
 *      "Error. <ID> not found."
 *  If the printing list is empty:
 *      "Error. <ID> has no <group's name>."
 * -------------------------------------------------------------------
 */

/* Description: Adds new boss-subordinate relation
 * Parameters:
 *  Param1: ID of the subordinate
 *  Param2: ID of the boss
 *  Param3: Output-stream for error-printing
 */

void Company::addRelation(const std::string &subordinate, const std::string &boss,
                          std::ostream &output) {
    //todo: this

}
