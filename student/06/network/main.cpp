#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <iterator>

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






int main() {
    // TODO: Implement the datastructure here

    std::map<std::string, std::vector<std::string>> Marketer_map;


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
            if (Marketer_map.find(id1) == Marketer_map.end()) {
                Marketer_map[id1].push_back(id2);

            }
        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            int depth = 2;
            std::map<std::string, std::vector<std::string>>::iterator itr = Marketer_map.find(id);
            std::cout << id << std::endl;
            for (itr = Marketer_map.find(id) ; itr != Marketer_map.end() ; itr++ ) {
                std::cout << std::string(depth, '.') << &itr->second << std::endl;
                depth++;
            }





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

