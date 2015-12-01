//========================================================================
//Authors: Jeff Smith, Corey Brown, Vincent Heredia
//Date: 11/1/2015
//File: Display.h
//========================================================================

#ifndef DISPLAY_H
#define DISPLAY_H
#include <vector>
#include <iostream>
using namespace std;

class Display{
public:

	//Purpose: default constructor
	Display();


	//Purpose: Displays the current board.
	void displayBoard(vector<vector<int> > board);

	void displayBoardTest(vector<vector<int> > board);

private:




};


#endif