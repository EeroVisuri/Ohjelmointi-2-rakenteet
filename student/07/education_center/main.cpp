#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>


using namespace std;



/*
 *
 * Muista header-comment
 * <location>;<theme>;<course_name>;<number_of_enrollments> dataformaatti
 */


//Saved some errors we'll be using as const strings

const string UNKNOWN_COMMAND = "Error: Unknown command: ";
const string ERROR_IN_COMMAND = "Error: error in command ";
const string ERROR_LOCATION = "Error: unknown location name ";
const string ERROR_THEME = "Error: unknown theme ";

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




//forward declaration so read_file function can use the error checking.
bool errorchecking(string line);




//function to split strings by a delimiter char. returns the split string as a vector<string>

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

//function to load data from a file

/* If the input file can be opened but the file does not correspond to the definition,
 * for example, the number of fields is not four or one field is missing a value,
 * the program prints the error message Error: empty field to the user
 * and terminates with the return value EXIT_FAILUR
 *
 * Otherwise returns "true" on read success.
 */



bool read_file_to_struct (string filename, multimap<string, Course> &courses_map) {
    ifstream filereader;
    filereader.open(filename);
    if (not filereader) {
        cout << "Error: the input file cannot be opened" << endl;
        return false;
    }

    string line;
    while (getline(filereader, line)) {
        if (!line.empty()) {

            //save info into map of structs
            if (errorchecking(line)) {
                cout << "Here's line: " << line << endl;
                vector<string>split_line = split(line, ';');
                struct Course NewCourse;
                NewCourse.name = split_line[2];
                NewCourse.theme = split_line[1];
                if (split_line[3] == "full") {
                    NewCourse.enrollments = 50;
                }
                else {
                    string enrolled = split_line[3];
                    stringstream stringtoint(enrolled);
                    int x = 0;
                    stringtoint >> x;
                    NewCourse.enrollments = x;
                }
                string location = split_line[0];
                pair<string, Course> pair(location, NewCourse);
                courses_map.insert(pair);
            }
            else {
                cout << "Error: empty field";
                return false;
            }
        }

    }
    return true;
};





/*
 * A function for error-checking the lines from a file.
 * Takes the string read from the file as a parameter.
 * Line must consist of four fields, none of them can be empty
 * or filled with only white spaces
 * last field must be a positive integer or the word "full"
 * Returns true if fields are fine, otherwise returns false.
 */


bool errorchecking (string line) {



    //splitting the line into a vector for error checking.
    vector<string>lineparts = split(line, ';');
    for (auto i = lineparts.begin(); i != lineparts.end(); ++i) {
        cout << *i << ' '  << endl;
    }
    if (lineparts.size() != 4) {
        return false;
    }
    int size = lineparts.size();
    for (int i = 0; i < size; ++i) {
        string s = lineparts[i];
        if (s.empty()) {
            return false;
        }
    }
    //
    if (lineparts[3] != "full") {
        string last =(lineparts[3]);
        if (isdigit(last.back())) {
            if (last.back() > 0) {
                return true;
            }

        }
        else {
            return false;
        }
    }

    return true;
}

/*
 * Function for printing locations stored in the data structure.
 * Takes the map where courses data is stored as parameter reference
 * Puts the locations found of the map to a vector and then prints out
 * the vector.
 *
 */



void print_locations (multimap<string, Course> &courses_map) {
    //a vector of strings to store our locations
    vector<string> locations;
    //saving the locations to the vector from courses_map.
    for (multimap<string, Course>::iterator it = courses_map.begin();
         it != courses_map.end() ; ++it) {
        locations.push_back(it->first);

    }
    //printing out the locations in the map.
    for (auto i = locations.begin(); i != locations.end(); ++i) {
        cout << *i << ' '  << endl;
    }
};


//this does not work yet if course is in more than one location.
void print_location_and_themes (multimap<string, Course> &courses_map, string location, string theme) {
    //a vector of strings to store our locations
    map<string, int> names_and_enrollments;
    //saving the locations to the vector from courses_map.


    //a for-loop for going through the courses_map, if we find a location matching the parameter,
    //we move onto next part
    for (const auto& elem: courses_map) {
        if (elem.first != location) {
            continue;
        }

        //here we check if the courses in location match the theme given in parameter
        if (elem.second.theme == theme) {
            //if yes, we put course name and number of enrollments into the map we created earlier
            pair<string, int> name_enrollments_pair (elem.second.name, elem.second.enrollments);
            names_and_enrollments.insert(name_enrollments_pair);
        }


    }
    //printing out the locations in the map.
    //debug print remove when done
    cout << "Size of locations_and_themes is " << names_and_enrollments.size() << endl;
    for(map<string, int>::const_iterator it2 = names_and_enrollments.begin();
        it2 != names_and_enrollments.end(); ++it2) {
        if (it2->second == 50) {
            cout << it2->first << " " << "--- " << "full" << "\n";
        }
        else {
            cout << it2->first << " " << "--- " << it2->second << " enrollments " << "\n";
        }
    }
};




void print_available_courses (multimap<string, Course> & courses_map) {
    for (multimap<string, Course>::iterator it3 = courses_map.begin();
         it3 != courses_map.end() ; ++it3) {
        if (!(it3->second.enrollments == 50)) {
            cout << it3->first << " : " << it3->second.theme << " : " << it3->second.name << endl;
        }
    }
}



//loop that has while-running inside it, so basically the program runs here after it's been called from main

bool running_loop() {

    //some variables to help run the thing and save stuff
    string filename = "";
    bool running = true;

    //creating map where to store our structs
    multimap<string, Course> courses_map;

    //asking user for input file's name
    cout << "Input file: ";
    getline(cin, filename);



    //check if reading from file to struct is successful, if not, return exit_failure.
    if (not read_file_to_struct(filename, courses_map)) {
        return EXIT_FAILURE;
    }




    //command reading loop that runs before user inputs quit

    while (running) {



        string user_command;

        cout << WAITING_INPUT;

        getline(std::cin, user_command);


        //Quits the program. Works.
        if (user_command == QUIT) {
            running = false;
            return EXIT_SUCCESS;
        }

        //Prints out the locations in alphabetical order
        if (user_command == LOCATIONS) {
            //prints out known locations in alphabetical order do a function for this
            print_locations(courses_map);
            continue;
        }

        //prints out all courses that are not full
        //outputs a single alphabetically ordered list, firstly by location, then theme, then course name
        if (user_command == AVAILABLE) {
            print_available_courses(courses_map);
            continue;

        }







        vector<string> command_parts = split(user_command, ' ');




        //Prints out command_parts[1] as location and command_parts[2] as theme
        //arranged alphabetically by course name
        //also maybe put this error checking somewhere else?
        if (command_parts[0] == COURSES) {
            bool noerrors = false;
            cout << command_parts.size() << " <- command parts size" <<endl;

            if (user_command.back() == '"' && command_parts.size() == 4) {
                cout << "Ollaan iffis";
                cout << "Command parts size is: " << command_parts.size();
                //special case of 2 theme being 2 words OR ONE thx specs.
                string s1 = command_parts[2];
                string s2 = command_parts[3];
                string result = s1 + " " + s2;
                result = result.substr(1, result.size()-2);

                command_parts.pop_back();
                command_parts.pop_back();
                command_parts.push_back(result);


            }
            else if (user_command.back() == '"' && command_parts.size() == 3) {
                string removing_quotes = command_parts[2];
                cout << "Removing quotes is: " << removing_quotes << endl;
                removing_quotes = removing_quotes.substr(1, removing_quotes.size()-2);
                command_parts.pop_back();

                command_parts.push_back(removing_quotes);
                cout << command_parts[3] << "<- command parts 3" << endl;
            }

            else if (command_parts.size() != 3) {
                cout << ERROR_IN_COMMAND << command_parts[0] <<endl;
                continue;
            }

            if (!courses_map.count(command_parts[1])) {
                cout << ERROR_LOCATION << command_parts[1] << endl;
                continue;
            }

            for (multimap<string, Course>::iterator it = courses_map.begin();
                 it != courses_map.end(); it++ ) {
                if (it->second.theme == command_parts[2]) {
                    noerrors = true;
                }


            }
            if (noerrors == true) {
                print_location_and_themes(courses_map, command_parts[1], command_parts[2]);
                continue;
            }
            else {
                cout << ERROR_THEME << command_parts[2] << endl;
                continue;
            }
        }




        //prints out all the courses with these of command_parts[1]
        if (command_parts[0] == COURSES_IN_THEME) {
            cout << "YOu hit courses in theme!";

        }
        //todo print out the course with most popular theme
        if (user_command == FAV_THEME) {
            cout << "You hit favourite theme!";

        }

        //debug command remove from working version
        if (user_command == "debug") {
            for (auto x : courses_map) {
                  cout << x.first << " " << x.second.name << x.second.theme << x.second.enrollments << endl;

            }
        }

        else {
            cout << UNKNOWN_COMMAND << user_command << endl;

        }




    }
    return true;
}



int main()
{
    running_loop();


}
