#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;



/*
 * Program reads data from a txt-file in format of: <location>;<theme>;<course_name>;<number_of_enrollments>
 * It puts the data into a multimap of locations and struct Courses which is an object that contains coursedata.
 * A running loop is called from main, where program takes inputs from user and based on the inputs either
 * throws errors or calls functions to perform commands given by the user.
 *
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
const string FAV_THEME = "favorite_theme";


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
};


//simple string to integer-function.


int string_to_int (vector<string> split_line) {
    string enrolled = split_line[3];
    stringstream stringtoint(enrolled);
    int x = 0;
    stringtoint >> x;
    return x;
};

/* Function to create new course. Only called from read_file_to_struct in case
 * error checks pass. Takes the multimap of courses and the split line
 * from the file as parameters.
 *
 */

void create_new_course(multimap<string, Course> &courses_map, vector<string>split_line) {
    struct Course NewCourse;
    NewCourse.name = split_line[2];
    NewCourse.theme = split_line[1];
    if (split_line[3] == "full") {
        NewCourse.enrollments = 50;
    }
    else {
        int x = string_to_int(split_line);
        NewCourse.enrollments = x;
    }
    string location = split_line[0];
    pair<string, Course> pair(location, NewCourse);
    courses_map.insert(pair);
};


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
            bool duplicate = false;
            //save info into map of structs
            if (errorchecking(line)) {
                vector<string>split_line = split(line, ';');
                string course_name = split_line[2];
                string location = split_line[0];
                if (courses_map.size() == 0) {
                    create_new_course(courses_map, split_line);
                }
                else if (courses_map.size() > 0) {
                    for (multimap<string, Course>::iterator iter = courses_map.begin();
                         iter != courses_map.end() ; ++iter) {


                        if (iter->first == location && iter->second.name == course_name) {
                            iter->second.enrollments = string_to_int(split_line);
                            duplicate = true;
                        }

                    }
                    if (!duplicate) {
                        create_new_course(courses_map, split_line);
                    }
                }
                else if(!errorchecking(line)) {
                    cout << "Error: empty field";
                    filereader.close();
                    return false;
                }

            }
        }
    }
    filereader.close();
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
};

/*
 * Function for printing locations stored in the data structure.
 * Takes the map where courses data is stored as parameter reference
 * Puts the locations found of the map to a vector and then prints out
 * the vector.
 *
 */



void print_locations (multimap<string, Course> &courses_map) {
    //a vector of strings to store our locations
    set<string> locations;
    //saving the locations to the vector from courses_map.
    for (multimap<string, Course>::iterator it = courses_map.begin();
         it != courses_map.end() ; ++it) {
        locations.insert(it->first);
    }
    //printing out the locations in the map.
    for (auto i = locations.begin(); i != locations.end(); ++i) {
        cout << *i << ' '  << endl;
    }
};



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

/* Function to sort the strings into alphabetical order.
 *
 */
bool compareFunction (std::string a, std::string b) {
    return a<b;}

/*
 * Prints available courses in alphabetical order, firstly by location,
 * secondly by theme, then by course name. Available means enrollment < 50.
 */

void print_available_courses (multimap<string, Course> & courses_map) {
    vector<string> courses_alphabetical_order;
    for (multimap<string, Course>::iterator it3 = courses_map.begin();
         it3 != courses_map.end() ; ++it3) {
        if (!(it3->second.enrollments == 50)) {
            string course_info;
            course_info = it3->first+ " : " + it3->second.theme+ " : "+it3->second.name;
            courses_alphabetical_order.push_back(course_info);
        }
    }
    sort(courses_alphabetical_order.begin(), courses_alphabetical_order.end(), compareFunction);
    for(auto const &courses : courses_alphabetical_order) {
        cout << courses << endl;
    }
};


/*
 *  A function for printing out the courses from courses_map in a given them (string theme).
 */

void print_courses_in_theme (multimap<string, Course> & courses_map, string theme) {
    set<string> coursethemes_alphabetical_order;
    for (multimap<string, Course>::iterator iter = courses_map.begin();
         iter != courses_map.end() ; ++iter) {
        if (iter->second.theme == theme) {
            coursethemes_alphabetical_order.insert(iter->second.name);
        }
    }

    for(auto const &coursethemes : coursethemes_alphabetical_order) {
        cout << coursethemes << endl;
    }

};

/* This function takes the courses_map, counts the most popular theme and outputs the theme.
 *
 */

void favourite_theme (multimap<string, Course> & courses_map) {
    map<string, int> most_popular_theme;

    if (courses_map.size() == 0) {
        cout << "No enrollments" << endl;
        return;
    }

    for (multimap<string, Course>::iterator iter = courses_map.begin();
         iter != courses_map.end() ; ++iter) {
        string theme = iter->second.theme;

        if (most_popular_theme.find(theme) == most_popular_theme.end()) {
            int enrollments = iter->second.enrollments;
            pair <string, int> tpair (theme, enrollments);
            most_popular_theme.insert(tpair);
        }
        else if (most_popular_theme.find(theme) != most_popular_theme.end()) {
            int enrollments = iter->second.enrollments;
            int previous = most_popular_theme.at(theme);
            int total = enrollments+previous;
            most_popular_theme.at(theme) = total;

        }
    }
    map<string, int>::iterator itr;
    map<string, int> topscorers;
    string highest_theme = "";
    int highest_enrollment = 0;
    for ( itr = most_popular_theme.begin(); itr != most_popular_theme.end(); ++itr) {
        if (itr->second == highest_enrollment) {
            highest_theme = itr->first;
            highest_enrollment = itr->second;
            pair <string, int> highscorer (highest_theme, highest_enrollment);
            topscorers.insert(highscorer);
        }
        if(itr->second > highest_enrollment) {
            topscorers.clear();
            highest_theme = itr->first;
            highest_enrollment = itr->second;
            pair <string, int> highscorer (highest_theme, highest_enrollment);
            topscorers.insert(highscorer);

        }

    }
    cout << highest_enrollment << " enrollments in themes" << endl;
    for(auto it = topscorers.cbegin(); it != topscorers.cend(); ++it) {
        cout << "--- " << it->first <<endl;
    }
};


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

        //print out the course with most popular theme
        if (user_command == FAV_THEME) {
            favourite_theme(courses_map);
            continue;

        }

        //splitting the user command into parts for easier handling later on
        vector<string> command_parts = split(user_command, ' ');




        //Prints out command_parts[1] as location and command_parts[2] as theme


        //special case of 2 theme being 2 words and quotation marks.
        if (command_parts[0] == COURSES) {
            bool noerrors = false;
            if (user_command.back() == '"' && command_parts.size() == 4) {

                string s1 = command_parts[2];
                string s2 = command_parts[3];
                string result = s1 + " " + s2;
                result = result.substr(1, result.size()-2);

                command_parts.pop_back();
                command_parts.pop_back();
                command_parts.push_back(result);


            }
            //special case for courses in theme with quotation marks but only 1 word as theme.
            else if (user_command.back() == '"' && command_parts.size() == 3) {
                string removing_quotes = command_parts[2];
                removing_quotes = removing_quotes.substr(1, removing_quotes.size()-2);
                command_parts.pop_back();
                command_parts.push_back(removing_quotes);

            }
            //error checks

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
            //if earlier checks didn't flag commands as erroneus we call the print function.
            if (noerrors == true) {
                print_location_and_themes(courses_map, command_parts[1], command_parts[2]);
                continue;
            }
            //otherwise something has gone wrong.
            else {
                cout << ERROR_THEME << command_parts[2] << endl;
                continue;
            }
        }




        //prints out all the courses with these of command_parts[1]
        if (command_parts[0] == COURSES_IN_THEME) {
            bool noerrors = false;
            for (multimap<string, Course>::iterator it = courses_map.begin();
                 it != courses_map.end(); it++ ) {
                if (it->second.theme == command_parts[1]) {
                    noerrors = true;
                }
            }
            if (noerrors) {
                print_courses_in_theme(courses_map, command_parts[1]);
                continue;
            }
            else {
                cout << ERROR_THEME <<command_parts[1] << endl;
                continue;
            }
        }





        else {
            cout << UNKNOWN_COMMAND << command_parts[0] << endl;

        }




    }
    return true;
}



int main()
{
    running_loop();


}
