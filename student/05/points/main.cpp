#include <iostream>
#include <string>
#include <fstream>
#include <map>


using namespace std;




int main() {

    string filename = "";

    cout << "Input file: ";
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
        //grabbing the score
        int score_to_add = stoi(line.substr(line.find(':' ) +1));
        //if name exist on the list, we just add additional scores to it
        if (scores.find(name) != scores.end()) {
            scores[name]+=score_to_add;
        }
        //if name doesn't exist on a list, we can add a new name with initial score.
        else {
            scores.insert(pair <string, int>(name, score_to_add));
        }

    }

    cout << "Final scores: " << endl;
    map <string, int>::iterator iter;
    iter = scores.begin();
    while (iter != scores.end()) {
        cout << iter->first << ": " << iter->second << endl;
        ++iter;
    }


    //todo print out final scores for each player organized alphabetically by playernames



}
