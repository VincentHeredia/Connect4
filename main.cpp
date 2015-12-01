//========================================================================
//Authors: Jeff Smith, Corey Brown, Vincent Heredia
//Date: 11/1/2015
//File: main.cpp
//========================================================================

#include "Board.h"
#include <iostream>
#include "Display.h"
using namespace std;

//program entry
int main(){
	string userInput = "";
	bool notDone = true;

	//loop for program, exits when the user types n when prompted
	while (notDone){
		cout << "Would you like to play Connect4? y/n: ";
		getline(cin, userInput);
		if (userInput == "n"){ notDone = false; }
		else if (userInput == "y"){
			Board myBoard;
			myBoard.playGame();
		}
		else { cout << "invalid input" << endl << endl; }
	}
}

