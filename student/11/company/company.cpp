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
        output << employees.at(i)->id_ << employees.at(i)->department_ <<
                  employees.at(i)->time_in_service_ << std::endl;
    }

}

/*
 * All the following functions have the same error message:
 *  If ID wasn't found in datastructure:
 *  "Error. <ID> not found."
 */

/* Description: Adds new boss-subordinate relation
 * Parameters:
 *  Param1: ID of the subordinate
 *  Param2: ID of the boss
 *  Param3: Output-stream for error-printing
 */

void Company::addRelation(const std::string &subordinate,
                          const std::string &boss, std::ostream &output) {

    //If the boss given as a parameter does not exist,
    //it is assumed that the given employee has no boss.
    //This is not considered as an error, and no error message is given.

    Employee* subordPTR = getPointer(subordinate);
    if (subordPTR != nullptr) {
        Employee* bossPTR = getPointer(boss);
        subordPTR->boss_ = bossPTR;
        bossPTR->subordinates_.push_back(subordPTR);
        return;
    }
    else {
        printNotFound(subordinate, output);
    }
}


/* Description: Prints the direct boss of the employee.
 * Parameters:
 *  Param1: ID of the employee
 *  Param2: Output-stream for printing
 */
void Company::printBoss(const std::string &id, std::ostream &output) const {
    Employee* workerPTR = getPointer(id);
    if (workerPTR != nullptr) {
        output << id << " has " << "1" << " bosses:" << std::endl;
        output << workerPTR->boss_ << std::endl;
    }
    else {
        printNotFound(id, output);
    }
}

/* Description: Prints direct subordinates for the employee.
 * Parameters:
 *  Param1: ID of the employee
 *  Param2: Output-stream for printing
 */

void Company::printSubordinates(const std::string &id, std::ostream &output)
    const {

    Employee* bossPTR = getPointer(id);
    if (bossPTR != nullptr) {
        output << id << " has " << bossPTR->subordinates_.size() << "subordinates:" << std::endl;
        for (unsigned long i = 0; i < bossPTR->subordinates_.size(); ++i) {
            output << bossPTR->subordinates_.at(i) << std::endl;
        }
    }
    else {
        printNotFound(id, output);
    }

}


/* Description: Prints the colleagues for the employee.
 *  (Employees who shares their direct boss)
 * Parameters:
 *  Param1: ID of the employee
 *  Param2: Output-stream for printing
 */


void Company::printColleagues(const std::string &id, std::ostream &output) const {

    Employee* workerPTR = getPointer(id);
    Employee* bossPTR = workerPTR->boss_;
    int colleagues = 0;

    for (unsigned long i = 0; i < employees.size(); ++i) {
        if (employees.at(i)->boss_ == bossPTR && employees.at(i)->id_ != workerPTR->id_) {
            colleagues++;
        }
    }
    output << id << " has " << colleagues << " department collagues:" << std::endl;
    for (unsigned long i = 0; i < employees.size(); ++i) {
        if (employees.at(i)->boss_ == bossPTR && employees.at(i)->id_ != workerPTR->id_) {
            output << employees.at(i)->id_ << std::endl;
        }
    }
}



// Return a pointer for ID.
// Reduces the amount of for-loops we'd have to write otherwise
// Since we can just use this one.
// Returns a nullptr if ID wasn't found.
Employee* Company::getPointer(const std::string &id) const {
    for (unsigned long i = 0; i < employees.size(); ++i) {
        if (employees.at(i)->id_ == id) {
            return employees.at(i);
        }
    }
    return nullptr;
}


// Printing errors.
void Company::printNotFound(const std::string &id, std::ostream &output) const{
    output << "Error. " << id << " not found." << std::endl;
}


