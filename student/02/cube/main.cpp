#include <iostream>
#include <climits>
using namespace std;



//if this method returns 1, you have overflowed. It will return 0 otherwise.
int overFlowcheck(int usersnnumber, int result) {
    if (usersnnumber > 0 && result > 0) {
        return 0;
    }
    if (usersnnumber < 0 && result < 0) {
        return 0;
    }
    if (usersnnumber < INT_MAX && result < INT_MAX) {
        return 1;
    }
    else {
        return 1;
    }
}


int main() {
    //taking the input and saving it in a variable
    int usersnumber;
    cout << "Enter a number: " <<endl;
    cin >> usersnumber;

    int result = usersnumber*usersnumber*usersnumber;

    if (overFlowcheck(usersnumber, result) > 0) {
        cout << "Error! The cube of " << usersnumber << " is not " << result << "." << endl;
    }
    else {
        cout << "The cube of " << usersnumber << " is " << result << "." << endl;
    }

}
