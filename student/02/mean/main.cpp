#include <iostream>
using namespace std;


// Function that asks user to input numbers and counts the mean
float meanCalculator(int integers) {
    float mean;
    int allintegers = 0;
    for (int var = 1; var <= integers; ++var) {
        int addnumber;
        cout << "Input " << var << ". number: ";
        cin >>  addnumber;
        allintegers = allintegers + addnumber;
    }

    float givenints = static_cast < float > (integers);
    float allints = static_cast< float >(allintegers);
    mean = allints / givenints;
    return mean;
}

int main()
{
    int integers;
    std::cout << "From how many integer numbers you want to count the mean value? ";
    cin >> integers;

    if (integers >0 ) {
        float answer = meanCalculator(integers);
        cout << "Mean value of the given numbers is " << answer<<endl;

    }
    else {
        cout << "Cannot count mean value from " <<integers << " numbers" << endl;
    }
}
