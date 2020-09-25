#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>





// TODO: Implement split function here
// Do not change main function





//function to split a string vector, gets string to be separated, separator char and can take a bool to ignore empty spaces.
std::vector<std::string> split(std::string line, char separator, bool ignoreEmpty = false) {



    //initialize the vector we're going to return
    std::vector<std::string> splitUpString;
    std::string s;
    std::istringstream stringStream(line);



    while (std::getline(stringStream, s, separator)) {
        if (!ignoreEmpty || !s.empty()) {
            splitUpString.push_back(s);
        }
    }


    //ugly hack to get newline correctly in if last character was a separator character
    char lastchar = line.back();
    //if the last character in line is the separator character, we push a newline at the vector's back.
    if (lastchar == separator) {
        splitUpString.push_back("");
    } else {
        return splitUpString;
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
