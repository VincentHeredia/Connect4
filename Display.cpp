//========================================================================
//Authors: Jeff Smith, Corey Brown, Vincent Heredia
//Date: 11/1/2015
//File: Display.cpp
//========================================================================

#include "Display.h"





//Purpose: default constructor
Display::Display(){
	//nothing to do
}

//Purpose: Displays the current board.
void Display::displayBoard(vector<vector<int> > board){
	//print out column numbers
	for (int i = 0; i < board.size(); i++){
		cout << "   " << (i+1);
	}
	cout << endl;
	//print out board
	for (int j = 0; j < board[0].size(); j++){

		cout << " -----------------------------" << endl;
		for (int i = 0; i < board.size(); i++){
			cout << " | ";
			if (board[i][j] == 0){
				cout << " ";
			}
			else if (board[i][j] == 1){
				cout << "R";
			}
			else{
				cout << "B";
			}
		}
		cout << " | " << endl;
	}//end of for loop
	cout << " -----------------------------" << endl;
}

//Purpose: Used for debugging
void Display::displayBoardTest(vector<vector<int> > board){
	//print out column numbers
	for (int i = 0; i < board.size(); i++){
		cout << "   " << (i + 1);
	}
	cout << endl;
	//print out board
	for (int j = 0; j < board[0].size(); j++){

		cout << " -----------------------------" << endl;
		for (int i = 0; i < board.size(); i++){
			cout << " | ";
			cout << board[i][j];
		}
		cout << " | " << endl;
	}//end of for loop
	cout << " -----------------------------" << endl;
}