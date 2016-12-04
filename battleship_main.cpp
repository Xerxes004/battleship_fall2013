// Author:	Wesley Kelly
// Date:	11/12/13
// Purpose:	Uses premade functions to create the game of Battleship

#include "battleship.h"
#include <string>

int main() {
	bool done = false;
	string playerMove;
	string computerMove;
	int playerShot;
	int computerShot;
	int playerShipsSunk = 0;
	int computerShipsSunk = 0;
	int playerMoveRow = -1;
	int playerMoveCol = -1;
	int computerMoveRow = -1;
	int computerMoveCol = -1;
	
	// Welcome the player to the game
	welcome();

	// Initialize the game boards
	Board playerBoard, computerBoard;
	
	initializeBoard(playerBoard);
	initializeBoard(computerBoard);

	// Play the game until one player has sunk the other's ships
	while(!done) {

		// Clear the screen to prepare show the game situation before the moves
		clearTheScreen();
		
		// Display the game board situation
		displayBoard(4, 0, HUMAN, playerBoard);
		displayBoard(4, 40, COMPUTER, computerBoard);
		
		// Get and validate the human player's move
		while(playerMoveRow == -1 || playerMoveCol == -1){
			playerMove = getResponse(0, 0, "Enter a move: ");
			checkMove(playerMove, computerBoard, playerMoveRow, playerMoveCol);
			if (playerMoveRow == -1 || playerMoveCol == -1){
				writeMessage(0, 0, "Invalid move! Press enter to continue.");
				pauseForEnter();
			}
		}

		// Get and validate the computer's move
		while(computerMoveRow == -1 || computerMoveCol == -1) {
			computerMove = randomMove();
			checkMove(computerMove, playerBoard, computerMoveRow, computerMoveCol);
		}
		
		// Execute both moves
		playerShot = playMove(playerMoveRow, playerMoveCol, computerBoard);
		computerShot = playMove(computerMoveRow, computerMoveCol, playerBoard);
				
		// Clear the screen to show the new game situation after the moves
		clearTheScreen();
		
		// Display the new game board situation
		displayBoard(4, 0, HUMAN, playerBoard);
		displayBoard(4, 40, COMPUTER, computerBoard);
		
		// Display the move choices each player made
		
		
		// Show the results of the moves
		writeResult(0, 0, playerShot, HUMAN);
		writeResult(1, 0, computerShot, COMPUTER);
		
		// Take note if there are any sunken ships
		if (isItSunk(playerShot)){
			computerShipsSunk++;
		}
		if (isItSunk(computerShot)){
			playerShipsSunk++;
		}

		// determine if we have a winner
		if(computerShipsSunk == 5 || playerShipsSunk == 5) {
			// if one of the player's has sunk five ships the game is over
			done = true;
		} else {
			// pause to let the user assess the situation
			pauseForEnter();
		}
		
		//	Reset the variables for the next round
		playerMoveRow = -1;
		playerMoveCol = -1;
		computerMoveRow = -1;
		computerMoveCol = -1;
		
	}

	// Announce the winner
	if(computerShipsSunk == 5) {
		clearTheLine(1);
		for (int i = 0; i < 4; i++){
			writeMessage(i, 0, "The player wins!!");
		}
	} else if (playerShipsSunk == 5) {
		clearTheLine(1);
		for (int i = 0; i < 4; i++){
			writeMessage(i, 0, "The computer wins!!");
		}
	} else {
		clearTheLine(1);
     	for (int i = 0; i < 4; i++){
			writeMessage(i, 0, "The game is a tie!!");
		}
   	}

	// pause to let the result of the game sink in
	pauseForEnter();
	clearTheScreen();

	return 0;
}
