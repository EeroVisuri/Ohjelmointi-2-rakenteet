#include <iostream>
#include <string>
#include <algorithm>
#include <random>


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


        std::string mixed_word = "";
        std::string first_letter = "";
        std::string last_letter = "";
        if (word.size() > 2) {
            copy(word.begin(), word.end(), mixed_word.begin());
            first_letter = word.front();
            last_letter = word.back();
            mixed_word = mixed_word.substr(0, mixed_word.size()-2);
            shuffle(mixed_word.begin(), mixed_word.end(), generator);
            mixed_word.insert(0, first_letter);
            mixed_word.append(last_letter);
            copy(mixed_word.begin(), mixed_word.end(), word.begin());
        }






        std::cout << word << std::endl;
    }
}
