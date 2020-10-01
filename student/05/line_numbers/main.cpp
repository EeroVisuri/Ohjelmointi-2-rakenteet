#include <iostream>
#include <fstream>
#include <string>


using namespace std;





int main() {

    string inputfile = "";
    string outputfile = "";

    //First ask for input file
    cout << "Input file: ";
    getline(cin, inputfile);

    //Then ask for output file
    cout << "Output file: ";
    getline(cin, outputfile);


    ifstream readstream(inputfile);

    if (not readstream) {
        cout << "Error! The file " << inputfile << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else {
        ofstream writestream(outputfile);
        int linenumber = 1;
        string line;
        while (getline(readstream, line)) {
            writestream << linenumber << " " << line << endl;
            linenumber++;

        }
        writestream.close();
    }
    readstream.close();
}
