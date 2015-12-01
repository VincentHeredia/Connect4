//========================================================================
//Authors: Jeff Smith, Corey Brown, Vincent Heredia
//Date: 11/1/2015
//File: AI.cpp
//========================================================================


#include "AI.h"
#include "Display.h"

using namespace std;



//Purpose: Default constructor
AI::AI(){
	//no variables to assign
	depthMax = 3;
}

//Purpose: Constructor to assign the depth
AI::AI(int newDepthMax){
	depthMax = newDepthMax;
}

//Purpose: Gets the input from the AI
//Returns: the column that the piece will be dropped into
int AI::getInput(vector<vector <int> > originalBoard, int player){
	int AImove = 0;

	
	//Sets the value of the player
	//because we are using recursion, we have to set the value of the player
	//to the oppocite of the AI on the first function call
	if (player == 2){player = 1;}
	else{player = 2;}

	//initializes the search to start at column 1, depth 0,
	//the worse alpha, and the worse beta
	AImove = search(originalBoard, 1, 0, player, -1000, 1000);

	return AImove;//should never be 0 or greater then the board size
}

//Purpose: Recursive search function
//Parameters: the current board
//Returns: The node's value
int AI::search(vector<vector<int> > currentBoard, int column, int depth, 
	int player, int alpha, int beta){
	//Variables
	int nextPlayer = 0; //Player starts as 2 from original function call from Board...
	int nodeValue = 0;	//Variable to store the node value
	int nodeName = 0;	//variable to store the node name (1-7)
	int newValue = 0;	//Variable to store the search function recursive value
	int currentRow = 0;
	int winner = 0;
	bool min = false;
	bool max = false;

	srand(time(NULL));//random seed

	//Determines if depth is min or max
	if (depth % 2 == 0) { max = true; }
	else { min = true; }

	if (depth != 0) {
		if (checkIfValidMove(currentBoard, column)) {
			currentRow = insertPiece(currentBoard, column, player);
			winner = checkForWinState(currentBoard, column, currentRow, player);
			if (winner == 2){ return ((50 / depth) + 100); }//if the agent wins, this is a good node
			else if (winner == 1){ return -10; }//if the human wins, this is a bad node
			else if (winner == 3){ return 0; }//if there is a tie, the node is worthless	
		}
		//invalid move
		else { 
			if (max){ return 20; }//should not be selected by min or max
			else { return -20; }
		}
	}

	//if we are at the max depth, estimate the node's value
	if (depth >= depthMax) { return heuristic(currentBoard, column, player); }
	
	//Sets the value of the player for the next depth of the recursive search function
	if (player == 2) { nextPlayer = 1; }
	else { nextPlayer = 2; }

	//Begin for loop for recursive function
	for (int i = 1; i < 8; i++) {
		//Sets the variable to the next depth level
		newValue = search(currentBoard, i, 1 + depth, nextPlayer, alpha, beta);

		/*
		if (depth == 0){
			cout << "Name: " << i << " Value: " << newValue << " Alpha: " << alpha << " Beta: " << beta << endl;
		}
		*/
		
		if (min){//if at a minimum node
			if (newValue < beta){
				beta = newValue;
				nodeName = i;
				nodeValue = newValue;
			}
		}
		else if (max){//if at a max node
			if (newValue > alpha){
				alpha = newValue;
				nodeName = i;
				nodeValue = newValue;
			}
		}

		if (alpha >= beta){
			//prune
			return newValue;
		}
	}
	
	//if this is the root node
	if (depth == 0) {
		//otherwise just return the node name
		return nodeName;
	}
	//if this is not the root
	else {
		//return this node's value
		return nodeValue;
	}

}//End of search function






//Purpose: Determines the value of the node
//Parameter: The board
//Returns: The value for the node
int AI::heuristic(vector<vector<int> > board, int move, int player){

	//heuristic variables
	int count = 0;//counts the amount of pieces near each other
	int value = 0;//the value of the move (to be determined)
	int gap = 0;
	bool blocked = false;

	//other variables
	int x = 0;//used to check diagonals
	int y = 0;//used to check diagonals
	int column = move - 1;//player input needs to be subtracted by 1 to get the correct column
	int row = getRow(board, column);//gets the row the piece was inserted into
	int opponent = 0;//the opponent's number
	int startAt = 0;//used to start the counting from a specific space

	if (player == 1){ opponent = 2; }
	else{ opponent = 1; }

	//-----------------------------column------------------------------
	count = 0;
	//check down the column (starting from the row)
	for (int i = row + 1; (i < board[column].size()) && (!blocked); i++){

		if (board[column][i] == player){
			count = count + 1;
		}
		else {//(board[column][i] == opponent)
			//if the opponent has the 3rd row occupied, then the player can not
			// win by connecting 4 vertically
			if (board[column][i] > 4){
				blocked = true;
				count = 0;
			}
		}
	}
	value = value + count;

	//-----------------------------column------------------------------


	//-----------------------------row------------------------------
	count = 0;
	blocked = false;
	//parse the row

	//move right
	for (int i = column + 1; (i < column + 4) && (!blocked) && (i < board.size()); i++){

		if (board[i][row] == player){
			count = count + 1;
		}
		else if (board[i][row] == opponent){
			blocked = true;
		}
		else {// == 0
			//gap
		}
	}
	blocked = false;
	//move left
	for (int i = column - 1; (i > column - 4) && (!blocked) && (i > -1); i--){

		if (board[i][row] == player){
			count = count + 2;
		}
		else if (board[i][row] == opponent){
			blocked = true;
		}
		else {// == 0
			//gap
		}
	}

	value = value + count;

	//-----------------------------row------------------------------


	//-------------------------\ diagonal------------------------------
	count = 0;
	blocked = false;
	//move to left end of the diagonal
	x = column + 1; y = row + 1;

	while ((y < board[0].size()) && (y < y + 4) && (x < board.size()) && (x < x + 4) && (!blocked)){

		if (board[x][y] == player){
			count = count + 1;
		}
		else if (board[x][y] == opponent){
			blocked = true;
		}
		else {// == 0
			//gap
		}
		x++; y++;
	}

	blocked = false;
	x = column - 1; y = row - 1;

	while ((y >= 0) && (y > y - 4) && (x >= 0) && (x > x - 4) && (!blocked)){

		if (board[x][y] == player){
			count = count + 1;
		}
		else if (board[x][y] == opponent){
			blocked = true;
		}
		else {// == 0
			//gap
		}
		x--; y--;
	}
	value = value + count;

	//-------------------------\ diagonal------------------------------


	//-------------------------/ diagonal--------------------------------
	count = 0;
	blocked = false;
	//move to left end of the diagonal
	x = column + 1; y = row - 1;

	while ((y >= 0) && (y > y - 4) && (x < board.size()) && (x < x + 4) && (!blocked)){

		if (board[x][y] == player){
			count = count + 1;
		}
		else if (board[x][y] == opponent){
			blocked = true;
		}
		else {// == 0
			//gap
		}
		x++; y--;
	}
	blocked = false;
	x = column - 1; y = row + 1;
	while ((x >= 0) && (x > x - 4) && (y < board[0].size()) && (y < y + 4) && (!blocked)){

		if (board[x][y] == player){
			count = count + 1;
		}
		else if (board[x][y] == opponent){
			blocked = true;
		}
		else {// == 0
			//gap
		}
		x--; y++;
	}

	value = value + count;

	//-------------------------/ diagonal--------------------------------


	return value;


}//End of heuristic function

//Purpose: Takes the column, and returns the row of the first empty space 
//Parameter: the board, the column
//Returns: The row
int AI::getRow(vector<vector<int> > board, int column){
	bool foundEmptySpot = false;
	int row;
	//start searching for an empty space from the bottom up
	for (int i = (board[column].size() - 1); (foundEmptySpot == false) && (i >= 0); i--){
		if (board[column][i] == 0){
			foundEmptySpot = true;
			row = i + 1;
		}
	}
	//if the piece was inserted in the top row
	if (foundEmptySpot == false) { return 0; }
	return row;
}


//Purpose: Checks for winstate 
//(only checks the row, column, and diagonals of where the piece was inserted)
//Parameters: The board, the column and row of the piece that was inserted, and the last player's turn
//Returns: the player if there is a winstate, 3 if there is a tie, else 0
int AI::checkForWinState(vector<vector<int> > board, int column, int row, int player){
	int count = 0;//the amount of pieces in a row
	int x = 0;//used to check diagonals
	int y = 0;//used to check diagonals
	column--;//player input needs to be subtracted by 1 to get the correct column
	//check tie case
	if (checkForTie(board) == true){ return 3; }

	//check column for win
	count = 0;
	//check down the column (starting from the row) for 4 matching pieces
	for (int i = row; (i < board[i].size()); i++){
		if (countSpaces(board, player, count, column, i) == true) {
			return player;
		}
	}

	//check row for win
	count = 0;
	//parse the row and look for 4 in a row
	for (int i = 0; (i < board.size()); i++){
		if (countSpaces(board, player, count, i, row) == true){
			return player;
		}
	}


	//check \ diagonal
	count = 0;

	//move to left end of the diagonal
	x = column; y = row;
	while ((y > 0) && (x > 0)){ x--; y--; }

	while ((y < board[0].size()) && (x < board.size())){
		if (countSpaces(board, player, count, x, y) == true){
			return player;
		}
		x++; y++;
	}

	//check / diagonal
	count = 0;

	//move to left end of the diagonal
	x = column; y = row;
	while ((y < (board[x].size() - 1)) && (x > 0)){ x--; y++; }

	while ((y >= 0) && (x < board.size())){
		if (countSpaces(board, player, count, x, y) == true){
			return player;
		}
		x++; y--;
	}

	return 0;
}

//Purpose: Used by checkForWinState() to count the amount
//         of pieces a player has in a row.
//Parameters: The board, the player's number, the current count
//            the column and the row
//Returns: True if a player has won, else false
bool AI::countSpaces(vector<vector<int> > board, int player, int& count, int x, int y){
	if (board[x][y] == player) { count++; }
	else { count = 0; }
	if (count == 4) { return true; }
	return false;
}

//Purpose: Checks if the board is full (a tie)
//Parameter: The board
//Returns: true if there is a tie, else false
bool AI::checkForTie(vector<vector<int> > board){
	for (int i = 0; i < board.size(); i++){
		if (board[i][0] == 0){ return false; }
	}
	return true;
}


//Purpose: Inserts the piece into the board
//Parameters: The board, the column, the player that is inserting the piece
//Returns: The row that the piece was inserted in
int AI::insertPiece(vector<vector<int> >& board, int column, int player){
	bool pieceInserted = false;
	int row;
	//Insert piece into board, start searching for an empty space from the bottom up
	for (int i = (board[column - 1].size() - 1); (pieceInserted == false) && (i >= 0); i--){
		if (board[column - 1][i] == 0){
			board[column - 1][i] = player;
			pieceInserted = true;
			row = i;
		}
	}
	if (pieceInserted == false) { cout << "Something Went Wrong!!!\n\n\n\n" << endl; }
	return row;
}

//Purpose: Check if the player's move is valid
//Parameter: The board, The column the piece will be inserted into
//Returns: true if the column is valid, else false
bool AI::checkIfValidMove(vector<vector<int> > board, int column){
	if ((column > board.size()) ||
		(column <= 0)){//if the player inputed a column that is out of bounds
		//cout << "Testing cout1: " << column << endl;
		//cout << "\nInvalid input. Column out of range\n" << endl;
		return false;
	}
	else if (board[column - 1][0] != 0){//if the column is not full
		//cout << "\nInvalid input. That column is full\n" << endl;
		//cout << "Testing cout2: " << column << endl;
		//column++;
		return false;
	}
	return true;
}