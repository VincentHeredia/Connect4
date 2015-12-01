//========================================================================
//Authors: Jeff Smith, Corey Brown, Vincent Heredia
//Date: 11/1/2015
//File: AI.h
//========================================================================


#ifndef AI_H
#define AI_H

#include <vector>
#include <iostream>//for bug testing
#include <stdlib.h>//for random function
#include <time.h>//for time
using namespace std;

class AI{
public:

	//Purpose: Default constructor
	AI();
	//Purpose: Constructor that assigns the depth of the search 
	AI(int newDepthMax);

	//Purpose: Gets the input from the AI
	//Returns: the column that the piece will be dropped into
	int getInput(vector<vector <int> > originalBoard, int player);

	//Purpose: Recursive search function
	//Parameters: the current board, the next move to try
	//Returns: The node's value
	int search(vector<vector<int> > currentBoard, int nextMove, int count, 
		int player, int alpha, int beta);

	//Purpose: Determines the value of the node
	//Parameter: The board
	//Returns: The value for the node
	int heuristic(vector<vector<int> > board, int move, int player);

	//Purpose: Takes the column, and returns the row of the first empty space 
	//Parameter: the board, the column that the new piece is inserted into
	//Returns: The row
	int getRow(vector<vector<int> > board, int column);




	//-----------Functions similar to ones in board.h, but have been repurposed for the AI to use----------

	//Purpose: Checks for winstate 
	//(only checks the row, column, and diagonals of where the piece was inserted)
	//Parameters: The board, the column and row of the piece that was inserted, and the last player's turn
	//Returns: the player if there is a winstate, else 0
	int checkForWinState(vector<vector<int> > board, int column, int row, int player);

	//Purpose: Used by checkForWinState() to count the amount
	//         of pieces a player has in a row.
	//Parameters: The board, the player's number, the current count
	//            the column and the row
	//Returns: True if a player has won, else false
	bool countSpaces(vector<vector<int> > board, int player, int& count, int x, int y);

	//Purpose: Checks if the board is full (a tie)
	//Parameter: the board
	//Returns: true if there is a tie, else false
	bool checkForTie(vector<vector<int> > board);

	//Purpose: Inserts the piece into the board
	//Parameters: the board (reference), the column, the player that is inserting the piece
	//Returns: The row that the piece was inserted in
	int insertPiece(vector<vector<int> >& board, int column, int player);

	//Purpose: Check if the player's move is valid
	//Parameter: The board, The column the piece will be inserted into
	//Returns: true if the column is valid, else false
	bool checkIfValidMove(vector<vector<int> > board, int column);

private:
	int depthMax; //depth is set to 3, which is 0-3 (4 levels: Current Board, Max, Min, Max)
	int player;//which player the AI is (red or black, 1 or 2)
	int column; //the column that the next piece is inserted into
};


#endif