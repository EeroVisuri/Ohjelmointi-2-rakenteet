#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

class WordObject  {
public:
    string name;
    int times_found_in_text = 0;
    set<int> text_lines_object_found_in;
    string information_in_stringform;
    string get_lines_as_string () {
        stringstream ss;
        ss << times_found_in_text;
        string times_as_string = ss.str();
        stringstream textlinesstream;
        copy(text_lines_object_found_in.begin(), text_lines_object_found_in.end(), ostream_iterator<int>(textlinesstream, ", "));
        string lines_as_string = textlinesstream.str().c_str();
        string lines_with_comma = lines_as_string.erase(lines_as_string.size()-2);

        information_in_stringform+= name + " " + times_as_string + ": " + lines_with_comma;
        return information_in_stringform;
    }
};



int main()
{
    string filename = "";

    cout << "Input file: ";
    getline(cin, filename);

    ifstream input_file(filename);
    //check if something went wrong and toss an exit failure if so
    if (not input_file) {
        cout << "Error! The file " << filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    //map to store our word, amount of words and what line they're on.
    map <string, WordObject>Wordsmap;

    string line;

    int linenumber = 1;
    //while-loop to read through file and find the words per line
    while (getline(input_file, line)) {
        istringstream instream(line);
        string word;
        //word per word going through line, if we don't find word in map, we
        //create a new WordObject and put it in the map
        while (instream >> word) {
            if (Wordsmap.find(word) == Wordsmap.end()) {
                WordObject Wordobj;
                Wordobj.name = word;
                Wordobj.times_found_in_text = 1;
                Wordobj.text_lines_object_found_in.insert(linenumber);
                Wordsmap.insert({word, Wordobj});
                instream.clear();
            }
            //if we do find the word, we increment the amount it was found and
            //save the linenumber in the WordObject's vector of numbers.
            else if (Wordsmap.find(word) != Wordsmap.end()) {
                Wordsmap.at(word).times_found_in_text++;
                Wordsmap.at(word).text_lines_object_found_in.insert(linenumber);

            }
            else {

                break;
            }
        }
        linenumber++;
    }
    map<string, WordObject>::iterator iter;
    iter = Wordsmap.begin();
    while (iter != Wordsmap.end()) {
        cout <<iter->second.get_lines_as_string() << endl;
        ++iter;
    }
    return EXIT_SUCCESS;



}



