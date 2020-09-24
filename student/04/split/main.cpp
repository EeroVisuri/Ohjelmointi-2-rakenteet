#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;




// TODO: Implement split function here
// Do not change main function





//function to split a string vector, gets string to be separated, separator char and can take a bool to ignore empty spaces.
std::vector<std::string> split(std::string line, char separator, bool includingEmpty = false) {


    //initialize the vector we're going to return
    std::vector<std::string> splitUpString;
    std::string s;
    std::istringstream stringStream(line);
    //if we're told to ignore the empty parts we do this
    if(!includingEmpty) {
        while (std::getline(stringStream, s, separator)) {
            splitUpString.push_back(s);
        }
        return splitUpString;
    }

    //if not, we do this instead to skip whitespaces
    if(includingEmpty) {
        while (std::getline(stringStream, s, separator)) {
            if (!s.empty()) {
                splitUpString.push_back(s);
            }
            else {
                continue;
            }
        }
    }
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
