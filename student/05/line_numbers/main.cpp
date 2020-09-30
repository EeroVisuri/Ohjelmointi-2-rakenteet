#include <iostream>
#include <fstream>
#include <string>


using namespace std;




int main()
{

    string inputfile = "";
    string outputfile = "";

    //First ask for input file
    cout << "Input file: ";
    getline(cin, inputfile);

    //Then ask for output file
    cout << "Output file: ";
    getline(cin, outputfile);

    //Creating the file_object stream to read from the file with given name

    ifstream file_object;


    ofstream file_object_for_output;


    //if we can't read from inputfile, print out an error
    if (not file_object) {
        cout << "Error! The file " << inputfile << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else {

        string line;
        int linenumber = 1;
        file_object.open(inputfile);
        file_object_for_output.open(outputfile);
        while (std::getline(file_object, line)) {
            file_object_for_output << linenumber << " " << line <<endl;
            linenumber++;
        }
        //close the file_objects after the file runs out of lines
        file_object.close();
        file_object_for_output.close();

    }
}
