#include <iostream>
using namespace std;

int main()
{
    int number; //variable to store the number from user in
    std::cout << "How many numbers would you like to have? ";
    std::cin >> number; //lets put the number user gave us in the variable
    int i;
    for (i=1; i<=number;) { //this loop prints out numbers from 1 to the number stored in variable int number.
        cout << i<<endl;
        i++;
    }
}
