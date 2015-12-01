//========================================================================
//Authors: Jeff Smith, Corey Brown, Vincent Heredia
//Date: 11/1/2015
//File: Board.cpp
//========================================================================

#include "Board.h"
#include "AI.h"




//Purpose: Default constructor, makes a 7X6 board
Board::Board(){
	//create spaces in the matrix
	board.resize(7);
	for (int i = 0; i < 7; i++){
		board[i].resize(6);
		for (int j = 0; j < 6; j++){
			board[i][j] = 0;
		}
	}
	gameWon = 0;
}

//Purpose: Constructor with height and width
//Parameters: The height and width of the new board
Board::Board(int width, int height){
	for (int i = 0; i < width; i++){
		board.resize(width);
		board[i].resize(height);
		for (int j = 0; j < height; j++){
			board[i][j] = 0;
		}
	}
	gameWon = 0;
}

//Purpose: Runs the game
void Board::playGame(){
	
	Display myDisplay;
	PlayerHuman Player1;
	PlayerHuman Player2;
	AI PlayerAI;
	string userInput = "";
	bool validInput = false; //various uses
	int playersMove = 0;
	int turn = 1;
	
	while (validInput == false){
		cout << "Type 1 to play with two people, type 2 to play with an AI.\nInput: ";
		getline(cin, userInput);
		if ((userInput == "1") || (userInput == "2")){
			validInput = true;
		}
		else{
			cout << "\nInvalid Input...\n" << endl;
		}
	}

	cout << "When it is your turn, input the number of the row"
		 << "\nyou wish to put your piece into.\n\n"
	     << "Game is starting...\n\n" << endl;
	
	//while the game has not be won, or there has not been a tie
	while (gameWon <= 0){
		
		validInput = false;
		myDisplay.displayBoard(board);


		if (turn == 1){//Player 1's turn
			//get player 1 input
			while (validInput == false){
				cout << "Red Player's turn: " << endl;
				playersMove = Player1.getInput();//get player 2's input
				validInput = checkIfValidMove(playersMove);
				cout << "Red Player's Move: " << playersMove << endl << endl;
			}//end of while
		}//end of if
		else {//Player 2's turn
			//get player 2 input
			while (validInput == false){
				cout << "Black Player's turn: " << endl;
				if (userInput == "1"){
					playersMove = Player2.getInput();//get player 2's input
				}
				else {
					//get AI input
					playersMove = PlayerAI.getInput(board, 2);
				}
				cout << "Black Player's Move: " << playersMove << endl << endl;
				validInput = checkIfValidMove(playersMove);
			}//end of while
		}//end of else
		
		//check if win state has been reached, or a tie

		gameWon = checkForWinState(playersMove, insertPiece(playersMove, turn), turn);
		
		if (turn == 1){ turn = 2; }
		else { turn = 1; }
		cout << endl;
	}

	myDisplay.displayBoard(board);

	//some has won the game, or there has been a tie
	if (gameWon == 1){
		cout << "\n\nRed Player has Won!" << endl;
	}
	else if (gameWon == 2){
		cout << "\n\nBlack Player has Won!" << endl;
	}
	else { cout << "\n\nTie!" << endl; }
}

//Purpose: Checks for winstate 
//(only checks the row, column, and diagonals of where the piece was inserted)
//Parameters: The column and row of the piece that was inserted, and the last player's turn
//Returns: the player if there is a winstate, else 0
int Board::checkForWinState(int column, int row, int player){
	int count = 0;//the amount of pieces in a row
	int x = 0;//used to check diagonals
	int y = 0;//used to check diagonals
	column--;//player input needs to be subtracted by 1 to get the correct column
	//check tie case
	if (checkForTie() == true){ return 3; }
	
	//check column for win
	count = 0;
	//check down the column (starting from the row) for 4 matching pieces
	for (int i = row; (i < board[column].size()); i++){
		if (countSpaces(player, count, column, i) == true) {
			return player;
		}
	}

	//check row for win
	count = 0;
	//parse the row and look for 4 in a row
	for (int i = 0; (i < board.size()); i++){
		if (countSpaces(player, count, i, row) == true){
			return player;
		}
	}

	
	//check \ diagonal
	count = 0;
	
	//move to left end of the diagonal
	x = column; y = row;
	while ((y > 0) && (x > 0)){ x--; y--; }
	
	while ((y < board[0].size()) && (x < board.size())){
		if (countSpaces(player, count, x, y) == true){
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
		if (countSpaces(player, count, x, y) == true){
			return player;
		}
		x++; y--;
	}

	return 0;
}

//Purpose: Used by checkForWinState() to count the amount
//         of pieces a player has in a row.
//Parameters: The player's number, the current count
//            the column and the row
//Returns: True if a player has won, else false
bool Board::countSpaces(int player, int& count, int x, int y){
	if (board[x][y] == player) { count++; }
	else { count = 0; }
	if (count == 4) { return true; }
	return false;
}

//Purpose: Checks if the board is full (a tie)
//Returns: true if there is a tie, else false
bool Board::checkForTie(){
	for (int i = 0; i < board.size(); i++){
		if (board[i][0] == 0){ return false; }
	}
	return true;
}


//Purpose: Inserts the piece into the board
//Parameters: the column, the player that is inserting the piece
//Returns: The row that the piece was inserted in
int Board::insertPiece(int column, int player){
	bool pieceInserted = false;
	int row;
	//Insert piece into board, start searching for an empty space from the bottom up
	for (int i = (board[column-1].size() - 1); (pieceInserted == false) && (i >= 0); i--){
		if (board[column-1][i] == 0){ 
			board[column-1][i] = player;
			pieceInserted = true;
			row = i;
		}
	}
	if (pieceInserted == false) { cout << "Something Went Wrong!!!\n\n\n\n" << endl; }
	return row;
}

//Purpose: Check if the player's move is valid
//Parameter: The column the piece will be inserted into
//Returns: true if the column is valid, else false
bool Board::checkIfValidMove(int column){
	if ((column > board.size()) ||
		(column <= 0)){//if the player didnt input a column that is out of bounds
		cout << "\nInvalid input. Column out of range\n" << endl;
		return false;
	}
	else if (board[column-1][0] != 0){//if the column is not full
		cout << "\nInvalid input. That column is full\n" << endl;
		return false;
	}
	return true;
}


