#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Path
 *
 * Desc:
 *  This program generates a Path puzzle. The board is ROWS x COLUMNS (5x4),
 * and every round the player chooses a source point and a target point
 * (totally four numbers), making the given button to be moved to the target
 * position (if possible). The game checks if the user-given move can be made.
 *  At start all green buttons are on the top row, and all red buttons are on
 * the bottom row. Game will end when all green buttons have been moved to the
 * bottom row, and all red buttons to the top row. It is not allowed to move a
 * button over another button.
 *  When printing the game board, green button is represented by 'G', red
 * button by 'R', empty hole by 'o', and unused position by empty space.
 *
 * Program author
 * Name: Eero Visuri
 * Student number: 439504
 * UserID: kneevi
 * E-Mail: eero.visuri@tuni.fi
 * Feedback language (fi/en): fi
 *
 * Notes about the program and it's implementation:
 * nothing yet
 * */




enum Slot_type {RED, GREEN, EMPTY, UNUSED};
const unsigned int ROWS = 5;
const unsigned int COLUMS = 4;

const string INPUT_TEXT = "Enter start point (x, y) and destination point (x, y), or q to quit: ";
const string INVALID_POINT = "Invalid start/destination point.";
const string CANNOT_MOVE = "There is no path between start point and destination point.";
const string GAME_OVER = "Game over. Congratulations!";
const string MOVES_MADE = " move(s) made.";

// Prints the grid
void print(const vector<vector<Slot_type>>& board) {
    cout << "===============" << endl;
    cout << "|   | 1 2 3 4 |" << endl;
    cout << "---------------" << endl;
    for(unsigned int i = 0; i < ROWS; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < COLUMS; ++j)
        {
            switch(board.at(i).at(j))
            {
            case GREEN: cout << "G "; break;
            case RED: cout << "R "; break;
            case EMPTY: cout << "o "; break;
            case UNUSED: cout << "  "; break;
            }
        }
        cout << "|" << endl;
    }
    cout << "===============" << endl;
}

// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns 0.
unsigned int stoi_with_check(const string& str) {
    bool is_numeric = true;
    string s = str;
    for(unsigned int i = 0; i < str.length(); ++i) {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric) {
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        return stoi(s);
    }
    else {
        return 0;
    }
}
// More functions

//if win condition has been met, returns true, otherwise false.

bool game_over(const vector<vector<Slot_type>>& board) {
    if (board[1][1]&&board[1][2]&&board[1][3]&&board[1][4] == RED) {
        if (board[5][1]&&board[5][2]&&board[5][3]&&board[5][4] == GREEN) {
            return true;
        }
    }
    return false;
}


//todo
//void move_piece (int sx, int sy, int dx, int dy) {

//}


//todo
//bool is_legal_move (int sx, int sy, int dx, int dy) {

//}

//this function checks if user inputs are valid in the current boardstate
//does NOT take into account hopping over pieces so we gotta do that still

bool is_valid_input (int sx, int sy, int dx, int dy,
                     const vector<vector<Slot_type>>& board) {

//if the starting position has either a green or a red knob, we can proceed
    if (board[sx][sy] == GREEN || RED) {
        //if the destination space is unused, it's a valid move and we return true
        if (board[dx][dy] == UNUSED) {
            return true;
        //else we just return false
        } else {
            return false;
        }
    }
    return false;
}


std::vector<std::vector<Slot_type> > initialize_board () {
    // Initializing 2D vector "board" with starting values
    vector<vector<Slot_type> > board  { { GREEN, GREEN, GREEN, GREEN },
                                        { UNUSED, EMPTY, UNUSED, UNUSED} ,
                                        { UNUSED, EMPTY, EMPTY, UNUSED },
                                        { UNUSED, EMPTY, UNUSED, UNUSED },
                                        { RED, RED, RED, RED } };

    return board;



}

void playloop () {


    //initializing the board so we can play and printing the initial position of knobs
    vector<std::vector<Slot_type>>board = initialize_board();
    print(board);



    //some variables to store gamestates
    bool playing = true;


    //check if game ended
    if (game_over(board)) {
        cout << GAME_OVER;
        playing = false;
    }


    while (playing) {
        int movestotal = 0;
        //variable to save current move
        string current_move;
        cout << INPUT_TEXT;
        cin >>  current_move;



        //if the command was the order to quit, print out how many moves we made and stop playing.
        if (current_move == "q") {
                    cout << movestotal << MOVES_MADE <<endl;
                    playing = false;
                    break;
                }

        //checking if current move was input properly and was legal
        int moves = stoi_with_check(current_move);
        if (moves == 0) {
            cout << INVALID_POINT << endl;
        }


        //if the input was proper, we move it's digits into gamestate variables
        else {
            int sx = moves / 1000 % 10;       //first digit
            int sy = moves / 100 % 10;        //second digit
            int dx = moves / 10 % 10;         //third digit
            int dy = moves  % 10;             //fourth digit

            if (!is_valid_input(sx, sy, dx, dy, board)) {
                cout << CANNOT_MOVE << endl;
            }
            else {
                //liike vai tsekkaus?
            }
        }

//        else if (is_legal_move) {
//            //move the pieces and add to moves made calculator
//        }

    }
}




int main() {
    playloop();
}
