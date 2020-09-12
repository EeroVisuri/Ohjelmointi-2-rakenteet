#include <iostream>
using namespace std;
// Write here a function counting the mean value
float meanCalculator(int integers) {
    float mean;
    for (int var = 0; var < integers; ++var) {

    }
    return mean;
}

int main()
{
    int integers;
    std::cout << "From how many integer numbers you want to count the mean value? ";
    cin >> integers;

    if (integers >0 ) {
        meanCalculator(integers);
    }
    else {
        cout << "Cannot count mean value from "<<integers;
    }
}
