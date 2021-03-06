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
   memory.fireDir     =  NONE;
   memory.fireDist    =  0;
   memory.lastResult  =  NONE;

   for (int i = 0; i < BOARDSIZE; i++) {
      for (int j = 0; j < BOARDSIZE; j++) {
         memory.grid[i][j] = EMPTY_MARKER;
      }
   }
}

//	Orients the next move
void aimTheGuns(ComputerMemory &memory){
	
	if (memory.mode == SEARCH){
		
		//	Assures that a value is assigned
		if (memory.fireDir == NONE){
			memory.fireDir = NORTH;
		}
		
		// If it would fire into an illegal area, this fixes it
		switch (memory.hitRow){
			case 0:
				memory.fireDir = EAST;
				if (memory.hitCol == 9){
					memory.fireDir = SOUTH;
				} break;
		
			case 9:
				memory.fireDir == WEST;
				if (memory.hitCol == 0){
					memory.fireDir = NORTH;
				} break;
		}
	
		switch (memory.hitCol){
		
			case 0:
				memory.fireDir == NORTH;
				if (memory.hitRow == 0){
					memory.fireDir = EAST;
				} break;
		
			case 9:
				memory.fireDir == SOUTH;
				if (memory.hitRow == 9){
					memory.fireDir = WEST;
				} break;
		}
		
	} else if (memory.mode == DESTROY){ // Different rules if destroying
		
		if (memory.fireDir == NONE){
			memory.fireDir = NORTH;
		}
		
		//	Fixes any wrong moves
		switch (memory.hitRow){
		
			case 0:
				if (memory.fireDir == NORTH){
					memory.fireDir = SOUTH;
				} else if (memory.fireDir == WEST){
					memory.fireDir = EAST;
				} else {
					memory.fireDir = WEST;
				}
				if (memory.hitCol == 9){
					if (memory.fireDir == EAST){
						memory.fireDir = WEST;
					} else {
						memory.fireDir = SOUTH;
					}
				}
				memory.hitRow += memory.fireDist - 1;
				memory.fireDist = 1;
			break;
			
			case 9:
				if (memory.fireDir == SOUTH){
					memory.fireDir = NORTH;
				} else if (memory.fireDir == WEST){
					memory.fireDir = EAST;
				} else {
					memory.fireDir = WEST;
				}
				if (memory.hitCol == 0){
					if (memory.fireDir == WEST){
						memory.fireDir = EAST;
					} else {
						memory.fireDir = NORTH;
					}
				}
				memory.hitRow -= memory.fireDist + 1;
				memory.fireDist = 1;
			break;
		}
	
		switch (memory.hitCol){
		
			case 0:
				if (memory.fireDir == EAST){
					memory.fireDir = WEST;
				} else if (memory.fireDir == NORTH){
					memory.fireDir = SOUTH;
				} else {
					memory.fireDir = NORTH;
				}
				if (memory.hitRow == 0){
					if (memory.fireDir == WEST){
						memory.fireDir = EAST;
					} else {
						memory.fireDir = SOUTH;
					}
				}
				memory.hitCol -= memory.fireDist + 1;
				memory.fireDist = 1;
			break;
		
			case 9:
				if (memory.fireDir == WEST){
					memory.fireDir = EAST;
				} else if (memory.fireDir == NORTH){
					memory.fireDir = SOUTH;
				} else {
					memory.fireDir = NORTH;
				}
				if (memory.hitRow == 9){
					if (memory.fireDir == EAST){
						memory.fireDir = WEST;
					} else {
						memory.fireDir = NORTH;
					}
				}
				memory.hitCol += memory.fireDist - 1;
				memory.fireDist = 1;
			break;
		}
	}
	
	fireTheGuns(memory);
}

//	Assigns the correct value to the next move
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

	move += numToString(memory.hitCol + 1);
	return move;
}

//	Updates memory, doesn't fire
void updateMemoryKelly(int row, int col, int result, ComputerMemory &memory){
													
	if (ISASUNK(result)) {
	
		memory.mode        =  RANDOM;	// or SEARCH or DESTROY
		memory.hitRow      = -1;
		memory.hitCol      = -1;
		memory.hitShip     =  NONE;
		memory.fireDir     =  NONE;
		memory.fireDist    =  0;
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
   		memory.fireDist    =  0;
  			memory.lastResult  =  NONE;
			
		} else if (ISAHIT(result) && !ISASUNK(result)){ 	//	hit without sinking
			
			memory.mode = SEARCH;
			memory.hitShip = SHIPNUM(result);
			memory.hitRow = row;
			memory.hitCol = col;
			memory.fireDir = NORTH;
			memory.fireDist = 0;
			memory.lastResult = result;
			
		}

	} else if (memory.mode == SEARCH){
	
		if (ISAHIT(result) && SHIPNUM(result) == memory.hitShip) {
		
			memory.mode = DESTROY;
			
		} else if (ISAMISS(result)){
		
			memory.mode = SEARCH;
		
			memory.fireDist = 1;
		
			switch (memory.fireDir){
			
				case NORTH:
					memory.fireDir = EAST;
					memory.hitRow += 1;
				break;
				
				case EAST:
					memory.fireDir = SOUTH;
					memory.hitCol -= 1;
				break;
				
				case SOUTH:
					memory.fireDir = WEST;
					memory.hitRow -= 1;
				break;
				
				case WEST:
					memory.fireDir = NORTH;
					memory.hitCol += 1;
				break;
			}
		} 		
		
	} else if (memory.mode == DESTROY){	
	
		memory.fireDist += 1;
		
		if (ISAMISS(result)){
			
			switch (memory.fireDir){
				
				case NORTH:
					memory.fireDir = SOUTH;
					memory.hitRow  += (memory.fireDist + 1);
					memory.fireDist = 0;
				break;
				
				case EAST:
					memory.fireDir = WEST;
					memory.hitCol -= (memory.fireDist);
					memory.fireDist = 0;
				break;
				
				case SOUTH:
					memory.fireDir = NORTH;
					memory.hitRow -= (memory.fireDist + 1);
					memory.fireDist = 0;
				break;
				
				case WEST:
					memory.fireDir = EAST;
					memory.hitCol += (memory.fireDist);
					memory.fireDist = 0;
				break;
			}
		}
	}
	
	aimTheGuns(memory);
}

