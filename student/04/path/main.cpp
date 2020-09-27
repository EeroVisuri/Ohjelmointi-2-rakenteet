#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

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



string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric) {
        removeSpaces(str);
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// More functions

//if win condition has been met, returns true, otherwise false.





bool game_over(const vector<vector<Slot_type>>& board) {
    if (board[0][0]&&board[0][1]&&board[0][2]&&board[0][3] == RED) {
        if (board[4][0]&&board[4][1]&&board[4][2]&&board[4][3] == GREEN) {
            return true;
        }
    }
    return false;
}



void move_piece (int sx, int sy, int dx, int dy, vector<vector<Slot_type>>& board ) {

    Slot_type prev_slot;
    prev_slot = board.at(sx).at(sy);
    board[dx][dy] = prev_slot;

}


bool horizontal_movement_check(int sx, int dx, int sy, const vector<vector<Slot_type>>& board) {

    //Check if there's a knob in the way in a horizontal path
    cout << "Got to horizontal_movement_check before crashing";
    for (int i = sx; i <= dx; ++i) {
        if (board[i][sy] != UNUSED ) {
            return false;
        }
    }
    return true;
}

bool vertical_movement_check(int sy, int dy, int sx, const vector<vector<Slot_type>>& board) {

    //first we check if we're on the right path. Only at x 1 or 5 can we move
    //check if there's a knob in the way of the vertical path



    cout << "Got to vertical_movement_check before crashing";
    for (int i = sy; i <= dy; ++i) {
        if (board[sx][i] != UNUSED) {
            return false;
        }
    }
    return true;
}


bool is_valid_move (int sx, int sy, int dx, int dy,
                    const vector<vector<Slot_type>>& board) {
    cout << "Got to is_valid_move before crashing";

    if (horizontal_movement_check(sx, dx, sy, board) == true) {
        if (vertical_movement_check(sy, dy, sx, board) == true) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}


//this function checks if user inputs are valid in the current boardstate
//does NOT take into account hopping over pieces so we gotta do that in other functions above

//this function checks if pieces are in correct
bool is_valid_input (int sx, int sy, int dx, int dy,
                     const vector<vector<Slot_type>>& board) {

//if the starting position has either a green or a red knob we can proceed
    if (board[sx][sy] == GREEN || RED) {
        //if the destination space is unused, it's a valid move
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
    bool playing = true;
    print(board);
    while (playing) {


        //variable to save current move total
        int movestotal = 0;

        //command given by user
        string user_command = "";
        //command sorted into an integer
        int moves = 0;
        //variables to save move
        int sx;
        int sy;
        int dx;
        int dy;
        //check if game ended
        if (game_over(board)) {
            cout << GAME_OVER <<endl;
            playing = false;
        }

        //grabbing command from user
        cout << INPUT_TEXT;
        cin >>  user_command;



        //if the command was the order to quit, print out how many moves we made and stop playing.
        if (user_command == "q") {
                    cout << movestotal << MOVES_MADE <<endl;
                    playing = false;
                    break;
                }

        //checking if current move was input properly
        moves = stoi_with_check(user_command);
        cout <<"here's moves: "<< moves <<endl;
        //if stoi_with_check returns a 0, we know something was wrong with input
        if (moves == 0) {
            cout << INVALID_POINT << endl;
            continue;
        }
        //if the input was proper, we move it's digits into gamestate variables
        else {
            sx = (moves / 1000 % 10);           //first digit
            sy = (moves / 100 % 10);            //second digit
            dx = (moves / 10 % 10);             //third digit
            dy = (moves  % 10);                 //fourth digit
            cout << "moves is: " << moves << endl;
            cout << "sx is: " <<sx <<endl;
            cout << "sy is: " <<sx<<endl;
            cout << "dx is: " <<sx<<endl;
            cout << "dy is: " <<sx<<endl;
        }
        //if there's an issue with the command, print cannot move and continue
        if (!is_valid_input(sx, sy, dx, dy, board)) {
            cout << CANNOT_MOVE << endl;
            continue;
        }

        //if all else went well we'll check if we can move
        else if (is_valid_move(sx, sy, dx, dy, board)) {      
            move_piece(sx, sy, dx, dy, board);
            movestotal = movestotal +1;
            print(board);
            continue;
        }
        else {
            cout << CANNOT_MOVE << endl;
            continue;
        }


    }
}




int main() {
    playloop();

}
