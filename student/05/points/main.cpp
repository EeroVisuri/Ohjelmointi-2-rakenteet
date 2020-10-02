#include <iostream>
#include <string>
#include <fstream>
#include <map>


using namespace std;




int main() {

    string filename = "";

    cout << "Input file: " << endl;
    getline(cin, filename);

    ifstream input_file(filename);
    //check if something went wrong and toss an exit failure if so
    if (not input_file) {
        cout << "Error! The file <" << filename << "> cannot be opened." << endl;
        return EXIT_FAILURE;
    }


    //create the map we're gonna put names and scores in
    map<string, int> scores;

    //todo read the scores from the file an count them together for each name
    string line;

    while (getline(input_file, line)) {
        //grabbing the name
        string name = line.substr(0, line.find(':'));
        //grabbing the score and converting it to integer
        char score_as_char = line.back();
        int score_to_add = (int) score_as_char;
        if (scores.find(name) != scores.end()) {

            //this could be prettier check out if there's a way to do score = score + score_to_add.
            for (int i = 0; i < score_to_add; ++i) {
                scores[name]++;
            }
        }
        else {
            scores.insert(pair <string, int>("name", score_to_add));
        }

    }


    //todo print out final scores for each player organized alphabetically by playernames



}
