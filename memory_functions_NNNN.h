#include <string>
#include "memory.h"

using namespace std;

void   initMemoryKelly(ComputerMemory &memory);
void   updateMemoryKelly(int row, int col, int result, ComputerMemory &memory);
string smartMoveKelly(const ComputerMemory &memory);

