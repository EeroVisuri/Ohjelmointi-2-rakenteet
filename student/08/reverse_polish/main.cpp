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
                exit(EXIT_FAILURE);

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
            //if we got this far, the operator must've been something else so we throw an error.
            else {
                cout << "Error: Unknown character" << endl;
                exit(EXIT_FAILURE);
            }

        }
    }
        return numberstack.top();
}
//function to check if char is a number. returns true if yes, otherwise false.
bool is_number(char c)
{
    if (isdigit(c))
        return true;
    return false;
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

    //splitting the input with our method
    vector<string>vector_for_calculations = split(input, ' ');

    //doing an ugly hack to check that there are enough operators for our calculations.
    int numbers_in_input = 0;
    int input_length = input.size();
    for (int i = 0; i < input_length; ++i) {
        if (is_number(input.at(i))) {
            numbers_in_input++;
        }
    }
    if (numbers_in_input != (input_length/2+1)/2) {
        cout << numbers_in_input << "Numbers in input" << endl;
        cout << input_length/2+1 << "half inputlength" << endl;
        cout << "Too few operators" << endl;
        return EXIT_FAILURE;
    }
    //variable to save our final number and printing it out.
    int final_eval = return_final_evaluation(vector_for_calculations);

    cout << "Correct: " << final_eval << " is the result" << endl;

    return EXIT_SUCCESS;
}
