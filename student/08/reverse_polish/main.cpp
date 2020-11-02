#include <iostream>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;



//function to split strings by a delimiter char. returns the split string as a vector<string>

vector<string> split(const string& s, const char delimiter, bool ignore_empty = false){
    vector<string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
};

//function to go through the stack until it has 1 number left and then return that number.
//takes a vector<string> as parameter.

int return_final_evaluation (vector<string>& vector_for_calculations) {
    stack<int> numberstack;
    for (auto a : vector_for_calculations) {
        //first we check if we've got a number. if we did, push it into numberstack.
        if (isdigit(a[0])) {
            stringstream intvalue(a);
            int number = 0;
            intvalue >> number;
            numberstack.push(number);
        }
        //if it's an operator, check what kind and do the operations, then push result to stack.

        if (a.size() == 1 && !isdigit(a[0])) {
            //unless it's a '#', then we know we're done.
            if (a[0] == '#') {
                return numberstack.top();
                break;
            }
            //if it is an operator, we pop 2 times and then do the operation inferred by the operator
            if (numberstack.size() < 2) {
                cout << "Error: too few operands" << endl;

            }
            int num2 = numberstack.top();
            numberstack.pop();
            int num1 = numberstack.top();
            numberstack.pop();
            if (a[0] == '+') {
                numberstack.push(num1 + num2);

            }
            else if (a[0] == '-') {
                numberstack.push(num1 - num2);

            }
            //we don't wanna divide by zero.
            else if (a[0] == '/') {
                if (num2 == 0) {
                    cout << "Error: Division by zero"<< endl;;
                    exit(EXIT_FAILURE);
                }
                else {
                    numberstack.push(num1 / num2);
                }
            }
            else if (a[0] == '*') {
                numberstack.push(num1 * num2);
            }
            else {
                cout << "Error: Unknown character" << endl;
                exit(EXIT_FAILURE);
            }

        }
    }

    if (numberstack.size() == 1) {
        return numberstack.top();
    }
    else {
        cout << "Error: Too few operators" << endl;
        exit(EXIT_FAILURE);
    }
}





int main()
{

    cout << "Input an expression in reverse Polish notation (end with #):" << endl;
    cout << "EXPR> ";
    string input;
    getline (cin, input);

    if (input.back() != '#') {
        cout << "End with '#'!" << endl;
        return EXIT_FAILURE;
    }

    if (!isdigit(input[0])) {
        cout << "Error: Expression must start with a number" << endl;
        return EXIT_FAILURE;
    }


    vector<string>vector_for_calculations = split(input, ' ');


    int final_eval = return_final_evaluation(vector_for_calculations);

    cout << "Correct: " << final_eval << " is the result" << endl;

    return EXIT_SUCCESS;
}
