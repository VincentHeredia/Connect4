//========================================================================
//Authors: Jeff Smith, Corey Brown, Vincent Heredia
//Date: 11/1/2015
//File: PlayerHuman.cpp
//========================================================================

#include "PlayerHuman.h"


PlayerHuman::PlayerHuman(){//default constructor
	//nothing to do
}

//Purpose: Gets the input from the player
//Returns: the column that the piece will be dropped into
int PlayerHuman::getInput(){
	string userInput = "";
	cout << "Input: ";
	getline(cin, userInput);
	return atoi(userInput.c_str());
}