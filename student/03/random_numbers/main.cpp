#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    // Creating a random engine
    std::default_random_engine rand_engine;
    // Ask for seeds, if left empty, we use computer clock time
    std::cout << "Enter a seed value or an empty line: ";

    std::string seed_value = "";
    getline(std::cin, seed_value);
    if( seed_value == "" ) {
        // If the user did not give a seed value, use computer time as the seed value.
        rand_engine.seed( time(NULL) );
    } else {
        // If the user gave a seed value, use it.
        rand_engine.seed( stoi(seed_value) );
    }
    //A while-loop to run the rng until user_input is 'q'.
    char user_input = ' ';
    while (true) {
        //Let's give the user a random number
        uniform_int_distribution<int> randomNumberInRange(lower, upper);
        int number = randomNumberInRange(rand_engine);
        std::cout << "Your drawn random number is " << number << endl;

        //After user has gotten their first random number, ask them if they want to continue.
        std::cout << "Press enter to continue or q to quit: ";
        //save input, discarding whitespaces
        user_input = cin.get();
        //if input was 'q', we break the loop
        if (user_input == 'q') {
            break;
        }
        else {
            continue;
        }
    }
}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    // Reading the line feed, which was left unread by >> operator above.
    // This is necessary since the seed value will be read by getline
    // in the function produce_random_numbers.
    string line_feed = "";
    getline(cin, line_feed);

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound" << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
