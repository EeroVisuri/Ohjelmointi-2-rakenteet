#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

// Returns true if all integers in a vector are the same
bool same_values(std::vector<int>integers) {
    for (int var = 1; var < integers.size(); ++var) {
        int previndex = integers.at(var-1);
        if (previndex != integers.at(var)) {
            return false;
        }
    }
    return true;
}


// returns true if all integers in a vector are ascending (non-strict so identical values are allowed)
bool is_ordered_non_strict_ascending (std::vector<int>integers) {
    for (int var = 1; var < integers.size(); ++var) {
        int previndex = integers.at(var-1);
        if (previndex > integers.at(var)) {
            return false;
        }
    }
    return true;
}

// returns true if difference between consecutive terms in the vector is constant
bool is_arithmetic_series (std::vector<int>integers) {

}

// returns true if numbers in a vector have constant ratio between consecutive integers
bool is_geometric_series (std::vector<int>integers) {

}


int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
