// Author: Nagham Wael Mohamed
// ID: 20231189
// Section: S19
// TA: Ahmed Ihab
// Version: 1.0

/*
 * This is a simple implementation of the Misere Tic Tac Toe.
 * The game is played on a 3x3 board where each cell is filled with either 'X' or 'O'.
 * The game is played between two players:
    ** The first player has the symbol 'X'.
    ** The second player has the symbol 'O'.
 * The players take turns to place their symbol in an empty cell.
 * The player who places three symbols in a row, column, or diagonal loses the game.
 * The game ends in a draw if all cells are filled and no player wins.
*/

//--------------------------------------- HEADERS

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
using namespace std;

//--------------------------------------- GLOBAL VARIABLES

string name1, name2;
int countNum = 0;

//--------------------------------------- HELPER FUNCTIONS

void checkPlayerType(string &playerType, int num) {
    cout << "\nWhat is player " << num << " type ?\n[1] Human.\n[2] Computer.\nChoice:";
    getline(cin, playerType);
    while (true) {
        if (playerType != "1" && playerType != "2") {
            cout << "Please enter a valid choice!\n\n";
            cout << "What is player " << num << " type ?\n[1] Human.\n[2] Computer.\nChoice:";
            getline(cin, playerType);
            continue;
        }
        return;
    }
}

//--------------------------------------- CLASSES

class Misere_Tic_Tac_Toe_Board : public Board<char> {
public:
    Misere_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    void getNames(string namePlayer1, string namePlayer2);
};

class Misere_Tic_Tac_Toe_Player : public Player<char> {
public:
    Misere_Tic_Tac_Toe_Player(string name, char symbol);
    void getmove(int &x, int &y) override;
};

class Misere_Tic_Tac_Toe_Random_Player : public RandomPlayer<char> {
public:
    Misere_Tic_Tac_Toe_Random_Player(char symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- IMPLEMENTATION

// ---------------------------- BOARD CLASS

void Misere_Tic_Tac_Toe_Board::getNames(std::string namePlayer1, std::string namePlayer2) {
    name1 = namePlayer1;
    name2 = namePlayer2;
}

// Constructor for X_O_Board
Misere_Tic_Tac_Toe_Board::Misere_Tic_Tac_Toe_Board() { //the constructor here is where we initialize the board
    this->rows = this->columns = 3;    //3 rows and 3 columns to make the grid
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;   //initialized the board with zeros
        }
    }
    this->n_moves = 0;
}

bool Misere_Tic_Tac_Toe_Board::update_board(int x, int y, char mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            countNum++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

void Misere_Tic_Tac_Toe_Board::display_board() {
    cout << "\n     1   2   3\n";
    cout << "   -------------\n";

    for (int i = 0; i < this->rows; i++) {
        cout << ' ' << i + 1 << " |";
        for (int j = 0; j < this->columns; j++) {
            cout << " " << setw(1);

            if (this->board[i][j] == 0) cout << " ";
            else cout << this->board[i][j];

            cout << " |";
        }
        cout << "\n   -------------\n";
    }
    cout << endl;
}

// Returns true if there is any winner
bool Misere_Tic_Tac_Toe_Board::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] &&
             this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] &&
             this->board[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }
    return false;
}

// Return true if 9 moves are done and no winner
bool Misere_Tic_Tac_Toe_Board::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

bool Misere_Tic_Tac_Toe_Board::game_is_over() {
    return is_win() || is_draw();
}

// ---------------------------- PLAYER CLASS

// Constructor for X_O_Player
Misere_Tic_Tac_Toe_Player::Misere_Tic_Tac_Toe_Player(string name, char symbol) : Player<char>(name, symbol) {}

void Misere_Tic_Tac_Toe_Player::getmove(int &x, int &y) {
    if (countNum % 2 == 0) this->name = name2;
    else this->name = name1;

    while (true) {
        cout << "Enter your move in this form(row space column,e.g 1 3): ";
        cin >> x >> y;

        // Convert to 0-based indexing
        x--;
        y--;

        if (cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 3) {
            cin.clear(); // Clear error flags
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
            cout << "Invalid input. Try again.\n";
        } else {
            break;
        }
    }
}

// ---------------------------- RANDOM PLAYER CLASS

// Constructor for X_O_Random_Player
Misere_Tic_Tac_Toe_Random_Player::Misere_Tic_Tac_Toe_Random_Player(char symbol) : RandomPlayer<char>(symbol) {
    this->dimension = 3;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

void Misere_Tic_Tac_Toe_Random_Player::getmove(int &x, int &y) {
    if (countNum % 2 == 0) this->name = name2;
    else this->name = name1;
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

//--------------------------------------- MAIN FUNCTION

int main(){
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    auto *gameBoard = new Misere_Tic_Tac_Toe_Board();
    cout << "<--------- Welcome To Misere Tic Tac Toe --------->\n";

    checkPlayerType(player1Type, 1);                // Get info of player 1.
    if (player1Type == "1") {
        cout << "Please enter Player 1 name:";
        getline(cin, player1Name);
    } else player1Name = "Random Computer Player";

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    if (player2Type == "1") {
        cout << "Please enter Player 2 name:";
        getline(cin, player2Name);
    } else player2Name = "Random Computer Player";

    if (player1Type == "1") {
        players[0] = new Misere_Tic_Tac_Toe_Player(player1Name, 'X');
    } else {
        players[0] = new Misere_Tic_Tac_Toe_Random_Player('X');
    }

    if (player2Type == "1") {
        players[1] = new Misere_Tic_Tac_Toe_Player(player2Name, 'O');
    } else {
        players[1] = new Misere_Tic_Tac_Toe_Random_Player('O');
    }
    gameBoard->getNames(player1Name, player2Name);

    // Use the customized MisereGameManager
    GameManager<char> Misere_Tic_Tac_Toe_Game(gameBoard, players);
    Misere_Tic_Tac_Toe_Game.run();

    delete gameBoard;                                           // Delete board.
    delete players[0];                                          // Delete players.
    delete players[1];
    cout << "\nTHANKS FOR PLAYING THIS GAME :)\n\n";
}
