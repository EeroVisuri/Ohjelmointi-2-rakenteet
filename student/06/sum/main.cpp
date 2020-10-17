#include <iostream>
#include <string>
#include <vector>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

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

int sum_recursive(std::vector<int> v){
    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------


    // Add your implementation here

    //save the last number in the vector to a variable
    int number_at_back = v.back();
    //then delete it
    v.pop_back();

    //if we're not down to 1 number left, return the number_at_back and call function again
    if (v.size() > 1) {
        return number_at_back + sum_recursive(v);
    }
    //else we can just return number_at_back and last number left in the vector.
    return number_at_back+v.back();




}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter integers separated by spaces: ";
    std::string line;
    getline(std::cin, line);
    std::vector<std::string> strings = split(line, ' ', true);
    std::vector<int> integers;
    for(auto s : strings){
        integers.push_back(stoi(s));
    }

    std::cout << "Sum: " << sum_recursive(integers) << std::endl;
}
#endif
