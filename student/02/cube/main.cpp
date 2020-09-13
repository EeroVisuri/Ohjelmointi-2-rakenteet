#include <iostream>
#include <climits>
#include <cstdint>
using namespace std;



//if this method returns 1, you have overflowed. It will return 0 otherwise.
int overFlowcheck(int usersnnumber, int result) {
    if (result > INT_MAX) {
        return 1;
    }
    if (result < usersnnumber) {
        return 1;
    }
    if (usersnnumber > 0 && result > 0) {
        return 0;
    }
    if (usersnnumber < 0 && result < 0) {
        return 0;
    }
    else {
        return 1;
    }
}


int main() {
    //taking the input and saving it in a variable
    int usersnumber;
    cout << "Enter a number: ";
    cin >> usersnumber;
    //doing the calculations
    int result = usersnumber*usersnumber*usersnumber;
    //checking if we overflowed
    if (overFlowcheck(usersnumber, result) > 0) {
        cout << "Error! The cube of " << usersnumber << " is not " << result << "." << endl;
    }
    else {
        cout << "The cube of " << usersnumber << " is " << result << "." << endl;
    }

}
