#include <iostream>
using namespace std;

int main()
{
    int number; //variable to store the number from user in
    std::cout << "How many numbers would you like to have? ";
    std::cin >> number; //lets put the number user gave us in the variable
    int i;
    for (i=1; i<=number;) { //this loop prints out numbers and zips and boings
        if (i%3==0 && i%7==0) { //if variable i is divisible by both 3 and 7, we print zip boing
            cout << "zip boing"<<endl;
            i++;
        }
        else if (i%3==0) {  //if variable i is divisible by 3, we print zip instead of the number
            cout << "zip"<<endl;
            i++;
        }
        else if (i%7==0) { //if i is divisible by 7, we print boing instead of the number
            cout << "boing"<<endl;
            i++;
        }
        else { //in any other case we print out the current number
            cout << i<<endl;
            i++;
        }
    }
}
