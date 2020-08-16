#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//spaces on board
int BLANK = 0;
int XMOVE = 1;
int OMOVE = 2;

//how many wins does each player have
int XWINS = 0;
int OWINS = 0;

//whose turn is it
int XTURN = 0;
int OTURN = 1;
int turn = XTURN;

//what row / column the player inputted
int row = 0;
int column = 0;

//game board
int board[3][3] = { {BLANK,BLANK,BLANK},
				   {BLANK,BLANK,BLANK},
				   {BLANK,BLANK,BLANK} };

//displaying the board
string input = "";
string output = "";

bool isPlaying = true;

//display the board to the players
void printBoard() {
	//print row header
	cout << "\t1\t2\t3" << endl;

	for (int x = 0; x < 3; x++) {
		//column header abc
		output = (static_cast<char>('a' + x));
		output += "\t";

		//displaying the cells in the board
		for (int y = 0; y < 3; y++) {
			if (board[x][y] == BLANK) {
				output += " \t";
			}
			else if (board[x][y] == XMOVE) {
				output += "X\t";
			}
			else if (board[x][y] == OMOVE) {
				output += "O\t";
			}
		}
		//display the row of the board
		cout << output << endl;
	}
}

void userTurns() {
	//reset input
	input = "";

	//get the input
	cin >> input;

	//what did the player input

	//exit game
	if (input == "exit" || input == "quit") {
		exit(0);
	}
	
	//validate the input if not exiting
	if (input.length() != 2 || input.length() < 2 || input.length() > 2) {
		cout << "Enter a letter followed by a number." << endl;
	}
	else if (input[0] != 'a' && input[0] != 'b' && input[0] != 'c') {
		cout << "Row must be a, b, or c." << endl;
	}
	else if (input[1] != '1' && input[1] != '2' && input[1] != '3') {
		cout << "Column must be 1, 2, or 3." << endl;
	}
	else { //if the input is valid then place move
		//get the move coordinates
		row = input[0] - 'a';
		column = input[1] - '1';

		//if the board is blank in that spot then make the move with the respective player
		if (board[row][column] == BLANK) {
			if (turn == XTURN) {
				board[row][column] = XMOVE;
				turn = OTURN;
				cout << "Turn: 0." << endl;
			}
			else if (turn == OTURN) {
				board[row][column] = OMOVE;
				turn = XTURN;
				cout << "Turn: X." << endl;
			}
		}
		else { //error message
			cout << "There is a piece there!" << endl;
		}
	}
}

//check if the board is in a tying state return boolean accordingly
bool checkTie() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == BLANK) {
				return false;
			}
		}
	}
	return true;
}

//check for wins for inputted player
bool checkWin(int p) {
	//check rows
	if (board[0][0] == p && board[0][1] == p && board[0][2] == p) {
		return true;
	}
	else if (board[1][0] == p && board[1][1] == p && board[1][2] == p) {
		return true;
	}
	else if (board[2][0] == p && board[2][1] == p && board[2][2] == p) {
		return true;
	}
	
	//check columns
	if (board[0][0] == p && board[1][0] == p && board[2][0] == p) {
		return true;
	}
	else if (board[0][1] == p && board[1][1] == p && board[2][1] == p) {
		return true;
	}
	else if (board[0][2] == p && board[1][2] == p && board[2][2] == p) {
		return true;
	}
	
	//check diagonals
	if (board[0][0] == p && board[1][1] == p && board[2][2] == p) {
		return true;
	}
	else if (board[0][2] == p && board[1][1] == p && board[2][0] == p) {
		return true;
	}

	//inputted player did not win
	return false;
}

//set board to blank and make turn X
void resetGame() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = BLANK;
		}
	}
	turn = XTURN;
}

int main() {
	//if playing
	while (isPlaying) {
		//display X turn
		cout << "Turn: X" << endl;

		//while there are no wins or ties print the board and make moves
		while (!checkWin(XMOVE) && !checkWin(OMOVE) && !checkTie()) {
			printBoard();
			userTurns();
		}

		//add the number of wins accordingly
		if (checkWin(XMOVE)) {
			XWINS++;
			printBoard();
			resetGame();
		}
		else if (checkWin(OMOVE)) {
			OWINS++;
			printBoard();
			resetGame();
		}
		else if (checkTie()) { //display tie game
			printBoard();
			cout << "Tie Game!" << endl;
			resetGame();
		}

		//how many wins does x and o have
		cout << "X Wins: " << XWINS << endl;
		cout << "O Wins: " << OWINS << endl;

		//quit and restart message message
		cout << "If you want to quit at anytime you can enter: 'exit' or 'quit'." << endl;
		cout << endl << "------Restarting------" << endl << endl;
	}

	return 0;
}
