//========================================================================
//Authors: Jeff Smith, Corey Brown, Vincent Heredia
//Date: 11/1/2015
//File: Board.h
//========================================================================

#ifndef BOARD_H
#define BOARD_H


#include <vector>
#include "Display.h"
#include "PlayerHuman.h"
using namespace std;


class Board{
public:
	//Purpose: Default constructor, makes a 7X6 board
	Board();

	//Purpose: Constructor with height and width
	//Parameters: The height and width of the new board
	Board(int width, int height);

	//Purpose: Runs the game
	void playGame();

	//Purpose: Checks for winstate 
	//(only checks the row, column, and diagonals of where the piece was inserted)
	//Parameters: The column and row of the piece that was inserted, and the last player's turn
	//Returns: the player if there is a winstate, else 0
	int checkForWinState(int column, int row, int player);

	//Purpose: Checks if the board is full (a tie)
	//Returns: true if there is a tie, else false
	bool checkForTie();

	//Purpose: Inserts the piece into the board
	//Parameters: the column, the player that is inserting the piece
	//Returns: The row that the piece was inserted in
	int insertPiece(int column, int player);

	//Purpose: Check if the player's move is valid
	//Parameter: The column the piece will be inserted into
	//Returns: true if the column is valid, else false
	bool checkIfValidMove(int column);

	//Purpose: Used by checkForWinState() to count the amount
	//         of pieces a player has in a row.
	//Parameters: The player's number, the current count
	//            the column and the row
	bool countSpaces(int player, int& count, int i, int j);

private:
	int gameWon;//0 if no one has won, 1 if player 1 has won, 
	            //2 if player 2 has won, 3 if tie
	
	vector<vector <int> > board; //the connect 4 board, able to be resized

	//board is constructed like this
	//  1   2   3   4   5   6   7
	//-----------------------------
	//|0,0|1,0|2,0|3,0|4,0|5,0|6,0|
	//-----------------------------
	//|0,1|1,1|2,1|3,1|4,1|5,1|6,1|
	//-----------------------------
	//|0,2|1,2|2,2|3,2|4,2|5,2|6,2|
	//-----------------------------
	//|0,3|1,3|2,3|3,3|4,3|5,3|6,3|
	//-----------------------------
	//|0,4|1,4|2,4|3,4|4,4|5,4|6,4|
	//-----------------------------
	//|0,5|1,5|2,5|3,5|4,5|5,5|6,5|
	//-----------------------------
};

#endif