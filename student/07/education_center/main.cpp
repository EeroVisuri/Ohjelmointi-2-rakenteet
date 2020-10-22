#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;



/*
 *
 * Muista header-comment
 * <location>;<theme>;<course_name>;<number_of_enrollments> dataformaatti
 */


//Saved some errors we'll be using as const strings

const string UNKNOWN_COMMAND = "Error: Unknown command: ";
const string ERROR_IN_COMMAND = "Error: error in command ";
const string ERROR_LOCATION = "Error: unknown location name";
const string ERROR_THEME = "Error: unknown theme";

const string WAITING_INPUT = "> ";

//Some commands as constants

const string QUIT = "quit";
const string LOCATIONS = "locations";
const string COURSES = "courses";
const string AVAILABLE = "available";
const string COURSES_IN_THEME = "courses_in_theme";
const string FAV_THEME = "favourite_theme";


//Structure for COURSES

struct Course {
    string name;
    string theme;
    int enrollments;
};

//function for splitting a string

vector<string> split(const string& s, const char delimiter, bool ignore_empty = false){
    vector<string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}


//loop that has while-running inside it, so basically the program runs here after it's been called from main

bool running_loop() {
    string filename = "";
    bool running = true;




    cout << "Input file: ";
    getline(cin, filename);
    ifstream input_file(filename);

    if (not input_file) {
        cout << "Error: the input file cannot be opened" << endl;
        return EXIT_FAILURE;
    }

    //TODO check that number of fields = 4 it not
    /* If the input file can be opened but the file does not correspond to the definition,
     * for example, the number of fields is not four or one field is missing a value,
     * the program prints the error message Error: empty field to the user
     * and terminates with the return value EXIT_FAILURE as follows:
     */

    //main loop that runs before user inputs quit
    //put the user command reading here
    while (running) {

        string user_command;

        cout << WAITING_INPUT;

        std::getline(std::cin, user_command);


        if (user_command == QUIT) {
            running = false;
            return EXIT_SUCCESS;
        }




    }
    return true;
}



int main()
{
    running_loop();


}
