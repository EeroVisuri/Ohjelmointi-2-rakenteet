#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <iterator>
#include <set>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
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


void recursive_printing(std::string id, std::multimap<std::string, std::string> marketerMap) {


    int index = 1;
    std::string recruiter = id;
    std::string recruited;
    if (marketerMap.find(id) != marketerMap.end()) {
        for (std::multimap<std::string, std::string>::iterator it = marketerMap.find(id);
             it != marketerMap.end(); it++) {
            index = index + std::distance(marketerMap.begin(), it);

            recruited = it->second;

            std::cout << std::string(index, '.') << it->second << std::endl;
            index = 1;
            return recursive_printing(recruited, marketerMap);
        }
    }
    else if (marketerMap.find(recruited) != marketerMap.end()) {
        for (std::multimap<std::string, std::string>::iterator it2 = marketerMap.find(recruited);
             it2 != marketerMap.end(); it2++) {
            index = index + std::distance(marketerMap.begin(), it2);
            recruited = it2 -> second;
            std::cout << std::string(index, '.') << it2->second << std::endl;
            return recursive_printing(recruited, marketerMap);
        }
    }
    else {
        index = 1;
        return recursive_printing(recruiter, marketerMap);
    }
}



int main() {
    // TODO: Implement the datastructure here
    std::multimap<std::string, std::string> marketerMap;



    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            if (marketerMap.find(id1) == marketerMap.end()) {
                marketerMap.insert(std::pair<std::string, std::string>(id1, id2));
            }
            else if (marketerMap.find(id1) != marketerMap.end()) {
                marketerMap.insert(std::pair<std::string, std::string>(id1, id2));
            }

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << id << std::endl;
            recursive_printing(id, marketerMap);




        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

        } else if(command == "Q" or command == "q"){
            return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}

