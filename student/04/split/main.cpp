#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// TODO: Implement split function here
// Do not change main function


std::vector<std::string> split(std::string line, char separator, ...) {

    //save the line's length into a variable and another variable for if we're ignoring empty parts
    int n = line.size();

    //I'll fix this later
    bool includingEmpty = false;
    //    if (ignoreEmpty == true) {
    //        includingEmpty = true;
    //    }

    //initialize the vector we're going to return
    std::vector<std::string> splitUpString;
    std::string s;
    std::istringstream stringStream(line);
    //if we're told to ignore the empty parts we do this
    if(!includingEmpty) {
        while (std::getline(stringStream, s, separator)) {
            splitUpString.push_back(s);
        }
    }

    //if not, we do this instead
 //   if(includingEmpty) {

 // }
    return splitUpString;
}



int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
