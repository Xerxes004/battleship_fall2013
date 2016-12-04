#include "memory_functions_Kelly.h"

using namespace std;

void initMemoryKelly(ComputerMemory &memory) {
   memory.mode        =  RANDOM;	// or SEARCH or DESTROY
   memory.hitRow      = -1;
   memory.hitCol      = -1;
   memory.hitShip     =  NONE;
   memory.fireDir     =  NONE;
   memory.fireDist    =  1;
   memory.lastResult  =  NONE;

   for (int i = 0; i < BOARDSIZE; i++) {
      for (int j = 0; j < BOARDSIZE; j++) {
         memory.grid[i][j] = EMPTY_MARKER;
      }
   }
}

string smartMoveKelly(const ComputerMemory &memory) {
   // fill in the code here to make a smart move based on what information
   // appears in the computer's memory
   string move;

   return move;
}

void updateMemoryKelly(int row, int col, int result, ComputerMemory &memory) {
	
	if (memory.mode == RANDOM){
	
		if (ISAMISS(result)){
		
		} else if (ISASUNK(result)){
		
		} else { 	//	hit without sinking
		
		}
	
	} else if (memory.mode == SEARCH){
	
	} else {	// (memory.mode == DESTROY)
	
	
	}


}

