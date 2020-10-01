#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;


    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }

        // TODO: implement your solution



        std::vector<char> mixed_word(word.length());
        copy(word.begin(), word.end(), mixed_word.begin());
        shuffle(mixed_word.begin(), mixed_word.end(), generator);
        copy(mixed_word.begin(), mixed_word.end(), word.begin());
	
        std::cout << word << std::endl;
    }
}
