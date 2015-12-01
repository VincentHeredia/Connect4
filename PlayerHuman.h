//========================================================================
//Authors: Jeff Smith, Corey Brown, Vincent Heredia
//Date: 11/1/2015
//File: PlayerHuman.h
//========================================================================

#ifndef PLAYERHUMAN_H
#define PLAYERHUMAN_H

#include <iostream>
#include <sstream>//for converting an int to a string
#include <string>
using namespace std;

class PlayerHuman{
public:
	PlayerHuman();//default constructor

	//Purpose: Gets the input from the player
	//Returns: the column that the piece will be dropped into
	int getInput();


private:


};

#endif