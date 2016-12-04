#include "memory_functions_Kelly.h"
#include <sstream>

using namespace std;

void aimTheGuns(ComputerMemory &memory);
void fireTheGuns(ComputerMemory &memory);

void initMemoryKelly(ComputerMemory &memory) {

   memory.mode        =  RANDOM;	// or SEARCH or DESTROY
   memory.hitRow      = -1;
   memory.hitCol      = -1;
   memory.hitShip     =  NONE;
   memory.fireDir     =  NORTH;
   memory.fireDist    =  1;
   memory.lastResult  =  NONE;

   for (int i = 0; i < BOARDSIZE; i++) {
      for (int j = 0; j < BOARDSIZE; j++) {
         memory.grid[i][j] = EMPTY_MARKER;
      }
   }
}

void aimTheGuns(ComputerMemory &memory){

	if (memory.fireDir == NONE){
		memory.fireDir = NORTH;
	}
	
	if (memory.mode == SEARCH){
	
		// If it would fire into an illegal area, this changes it
		switch (memory.hitRow){
		
			case 0:
				memory.fireDir = EAST;
				if (memory.hitCol = 9){
					memory.fireDir = SOUTH;
				} break;
		
			case 9:
				memory.fireDir = WEST;
				if (memory.hitCol = 0){
					memory.fireDir = NORTH;
				} break;
		}
	
		switch (memory.hitCol){
		
			case 0:
				memory.fireDir = NORTH;
				if (memory.hitRow = 0){
					memory.fireDir = EAST;
				} break;
		
			case 9:
				memory.fireDir = SOUTH;
				if (memory.hitRow = 9){
					memory.fireDir = WEST;
				} break;
		}
		
	} else if (memory.mode == DESTROY){
		
		switch (memory.hitRow){
		
			case 0:
				memory.fireDir = EAST;
				memory.hitRow -= memory.fireDist;
				memory.fireDist = 1;
			break;
			
			case 9:
				memory.fireDir = WEST;
				memory.hitRow -= memory.fireDist;
				memory.fireDist = 1;
			break;
		}
	
		switch (memory.hitCol){
		
			case 0:
				memory.fireDir = NORTH;
				memory.hitCol -= memory.fireDist;
				memory.fireDist = 1;
			break;
		
			case 9:
				memory.fireDir = SOUTH;
				memory.hitCol -= memory.fireDist;
				memory.fireDist = 1;
			break;
		}
	}
	
	fireTheGuns(memory);
}

void fireTheGuns(ComputerMemory &memory){
	
	switch (memory.fireDir){

		case NORTH:
			memory.hitRow -= 1;
		break;
		
		case EAST:
			memory.hitCol += 1;
		break;
		
		case SOUTH:
			memory.hitRow += 1;
		break;
		
		case WEST:
			memory.hitCol -= 1;
		break;
	}
	
	smartMoveKelly(memory);
}

//	sends smart move to board
string smartMoveKelly(const ComputerMemory &memory) {
	// fill in the code here to make a smart move based on what information
	// appears in the computer's memory
   
	string longitude = "ABCDEFGHIJ";
	string move = "";
	
	stringstream a;
	a << longitude[memory.hitRow];
	a >> move;

	move += numToString(memory.hitCol);
	writeMessage  (0, 0, move);
	//pauseForEnter();
	return move;
}

//	Updates memory, doesn't fire
void updateMemoryKelly(int row, int col, int result, ComputerMemory &memory){
															/*
	int  hitRow, hitCol;
	int  hitShip;
	int  fireDir;
	int  fireDist;
	int  lastResult;
	int  mode;
	char grid[BOARDSIZE][BOARDSIZE];
															*/
															
		if (ISASUNK(result)) {
			memory.mode        =  RANDOM;	// or SEARCH or DESTROY
   		memory.hitRow      = -1;
   		memory.hitCol      = -1;
   		memory.hitShip     =  NONE;
   		memory.fireDir     =  NONE;
   		memory.fireDist    =  1;
  			memory.lastResult  =  NONE;
		}
															
	if (memory.mode == RANDOM){
	
		if (ISAMISS(result)){
		//	stays random, randomly fires again
		
			memory.mode        =  RANDOM;	// or SEARCH or DESTROY
   		memory.hitRow      = -1;
   		memory.hitCol      = -1;
   		memory.hitShip     =  NONE;
   		memory.fireDir     =  NONE;
   		memory.fireDist    =  1;
  			memory.lastResult  =  NONE;
			
		} else if (ISAHIT(result)){ 	//	hit without sinking
			
			memory.mode = SEARCH;
			memory.hitShip = SHIPNUM(result);
			memory.hitRow = row;
			memory.hitCol = col;
			memory.fireDir = NONE;
			memory.fireDist = 1;
			memory.lastResult = result;
			
		}
	
	} else if (memory.mode == SEARCH){
	
		if (ISAHIT(result)) {
		
			memory.mode = DESTROY;
			memory.hitRow = row;
			memory.hitCol = col;
			memory.fireDist += 1;
			
		} else if (ISAMISS(result)){
		
			memory.fireDist = 1;
		
			switch (memory.fireDir){
			
				case NORTH:
					memory.fireDir = EAST;
					//memory.hitCol += 1;
				break;
				
				case EAST:
					memory.fireDir = SOUTH;
					//memory.hitRow += 1;
				break;
				
				case SOUTH:
					memory.fireDir = WEST;
					//memory.hitCol -= 1;
				break;
				
				case WEST:
					memory.fireDir = NORTH;
					//memory.hitRow -= 1;
				break;
			}
			smartMoveKelly(memory);
			return;
		}
		
	} else {	// (memory.mode == DESTROY)
	
		if (ISAHIT(result)){
			fireTheGuns(memory);
			return;
		}
	
	}

	aimTheGuns(memory);
}

