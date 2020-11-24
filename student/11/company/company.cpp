#include "company.hh"
#include <algorithm>
#include <memory>


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

Company::Company()
{

}

Company::~Company()
{

}


//comparison function for ordering vectors alphabetically

bool compare(const Employee* a, const Employee* b) {
    return a->id_ < b->id_;
}


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
    //create the new_employee
    Employee* new_employee = new Employee;
    new_employee->id_ = (id);
    new_employee->department_ = (dep);
    new_employee->time_in_service_ = (time);
    employees.push_back(new_employee);
    if (employees.size() > 2) {
        std::sort(employees.begin(), employees.end(), compare);
    }


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
        output << employees.at(i)->id_ << ", " <<employees.at(i)->department_
               <<", " <<employees.at(i)->time_in_service_ << std::endl;
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
        if (bossPTR != nullptr) {
            bossPTR->subordinates_.push_back(subordPTR);
        }
        return;
    }
    //if the id points to a nullpointer, print error, free memory and return.
    else {
        printNotFound(subordinate, output);
        return;
    }
}


/* Description: Prints the direct boss of the employee.
 * Parameters:
 *  Param1: ID of the employee
 *  Param2: Output-stream for printing
 */
void Company::printBoss(const std::string &id, std::ostream &output) const {

    Employee* workerPTR = getPointer(id);

    //if the id points to a nullpointer, print error, free memory and return.
    if (workerPTR != nullptr) {
        if (workerPTR->boss_ == nullptr) {
            output << id << " has no bosses." << std::endl;
            delete workerPTR;
            return;
        }
        output << id << " has " << "1" << " bosses:" << std::endl;
        output << workerPTR->boss_->id_ << std::endl;
        delete workerPTR;
    }
    else {
        printNotFound(id, output);
        delete workerPTR;
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
    //if the id points to a nullpointer, print error and return.
    if (bossPTR != nullptr) {
        if (bossPTR->subordinates_.size() == 0) {
            output << id << " has no subordinates." << std::endl;
            return;
        }
        output << id << " has " << bossPTR->subordinates_.size() << " subordinates:" << std::endl;
        std::sort(bossPTR->subordinates_.begin(),bossPTR->subordinates_.end(), compare);
        for (unsigned long i = 0; i < bossPTR->subordinates_.size(); ++i) {
            output << bossPTR->subordinates_.at(i)->id_ << std::endl;

        }
    }
    else {
        printNotFound(id, output);
        delete bossPTR;
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

    if (workerPTR == nullptr) {
        printNotFound(id, output);
        return;
    }
    //count how many colleagues people have, if boss is a nullpointer, that's
    //not a real boss
    for (unsigned long i = 0; i < employees.size(); ++i) {
        if (employees.at(i)->boss_ == bossPTR && bossPTR != nullptr &&
                employees.at(i)->id_ != workerPTR->id_) {
            colleagues++;
        }
    }

    //if there are no colleagues, print out so
    if (colleagues == 0) {
        output << id << " has no colleagues." << std::endl;
        return;
    }
    //print how many colleagues id had
    output << id << " has " << colleagues << " colleagues:" << std::endl;
    //print out id's colleagues, if boss is a nullpointer, that's
    //not a real boss
    for (unsigned long i = 0; i < employees.size(); ++i) {
        if (employees.at(i)->boss_ == bossPTR && bossPTR != nullptr &&
                employees.at(i)->id_ != workerPTR->id_) {
            output << employees.at(i)->id_ << std::endl;
        }
    }
}

/* Description: Prints all-level colleagues for the employee.
 *  (Employees who share their department and belong to the same hierarchy)
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Output-stream for printing
 */


void Company::printDepartment(const std::string &id, std::ostream &output)
const {

    Employee* workerPTR = getPointer(id);
    //if the id points to a nullpointer, print error and return
    if (workerPTR == nullptr) {
        printNotFound(id, output);
        return;
    }
    //A vector to store the colleagues
    std::vector<Employee*> departmentColleagues;
    //Set a pointer to dpmHead
    Employee* dpmHeadPTR = workerPTR;
    //Find the department head
    // Careful that we dont run into nullpointers, that'll crash it


    if (dpmHeadPTR != nullptr && dpmHeadPTR->boss_ != nullptr) {
        if (dpmHeadPTR->boss_ != nullptr &&
                dpmHeadPTR->boss_->department_==workerPTR->department_){
            while (dpmHeadPTR->boss_ != nullptr && dpmHeadPTR->boss_->department_ ==
                   workerPTR->department_ ) {
                dpmHeadPTR = dpmHeadPTR->boss_;
            }
        }

        else if (dpmHeadPTR->boss_ == nullptr) {
            output << "U broke it" << std::endl;
            return;
        }
    }
    //still afraid of nullpointers
    if (dpmHeadPTR == nullptr) {
        output << id << " has no department colleagues." << std::endl;
        return;
    }
    //add all the department head's underlings to departmentColleagues
    for (unsigned long i = 0; i < dpmHeadPTR->subordinates_.size(); ++i) {
        if (dpmHeadPTR->subordinates_.at(i)->department_ ==
                workerPTR->department_) {
            departmentColleagues.push_back(dpmHeadPTR->subordinates_.at(i));
        }
    }


    //then we go through their subordinates and add them to the
    //departmentColleagues as well
    for (unsigned long i = 0; i < departmentColleagues.size(); ++i) {
        if (departmentColleagues.at(i)->subordinates_.size() != 0) {
            for (unsigned long j = 0; j < departmentColleagues.at(i)->subordinates_.size(); ++j) {
                    departmentColleagues.push_back(departmentColleagues.at(i)->subordinates_.at(j));               
            }
        }
    }
    //put the department head as colleague as well
    departmentColleagues.push_back(dpmHeadPTR);
    if (departmentColleagues.size() == 0) {
        output << id << " has no department colleagues." << std::endl;
        return;
    }
    //print out the department colleagues
    if (departmentColleagues.size() > 1) {
        std::sort(departmentColleagues.begin(), departmentColleagues.end(), compare);
    }

    output << id << " has " << departmentColleagues.size()-1 <<
              " department colleagues:" << std::endl;
    for (unsigned long i = 0; i < departmentColleagues.size(); ++i) {
        if (departmentColleagues.at(i)->id_ != id) {
            output << departmentColleagues.at(i)->id_ << std::endl;
        }
    }
}



/* Description: Prints the employee with the longest time in service
 *  in the ID's line management.
 * Parameters:
 *  Param1: ID of the employee
 *  Param2: Output-stream for printing
 */



void Company::printLongestTimeInLineManagement(const std::string &id,
                                               std::ostream &output) const {

    Employee* workerPTR = getPointer(id);
    Employee* longestServingPTR = workerPTR;

    if (workerPTR == nullptr) {
        printNotFound(id, output);
        delete workerPTR;
        delete longestServingPTR;
        return;
    }


    for (unsigned long i = 0; i < workerPTR->subordinates_.size(); ++i) {
        if (workerPTR->subordinates_.at(i)->time_in_service_ >
                longestServingPTR->time_in_service_ ) {
            longestServingPTR = workerPTR->subordinates_.at(i);
        }

    }
    if (workerPTR == longestServingPTR) {
        output << "With the time of "<< longestServingPTR->time_in_service_ <<
                  ", "<< longestServingPTR->id_ << " is the longest-served employee in "
               << "their line management." << std::endl;
    }
    else {
        output << "With the time of "<< longestServingPTR->time_in_service_ <<
                  ", "<< longestServingPTR->id_ << " is the longest-served employee in "
               << id <<"'s line management." << std::endl;
    }




}

//3 dummy functions for voluntary stuff.

void Company::printShortestTimeInLineManagement(const std::string &id, std::ostream &output) const
{
    Employee* durr = getPointer(id);
    if(output) {};
    delete durr;
}

void Company::printBossesN(const std::string &id, const int n, std::ostream &output) const
{
    Employee* durr = getPointer(id);
    for (int i = 0; i < n; ++i) {

    }
    if(output) {};
    delete durr;
}

void Company::printSubordinatesN(const std::string &id, const int n, std::ostream &output) const
{
    Employee* durr = getPointer(id);
    for (int i = 0; i < n; ++i) {

    }
    if(output) {};
    delete durr;
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



// Printing error if no ID can be found.
void Company::printNotFound(const std::string &id, std::ostream &output) const{
    output << "Error. " << id << " not found." << std::endl;
}



