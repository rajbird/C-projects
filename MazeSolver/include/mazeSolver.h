/**
 * Rajbir Deol
 * 0918139
 */
#ifndef __RDEOL_MAZESOLVER__
#define __RDEOL_MAZESOLVER__

/**
 * Pre-conditions: a valid data file containing a maze
 * Post-conditions: none
 */
void dataParse(char* dataFile);

/**
 * Pre-conditions: an intilized stack, containg the full maze
 * Post-conditions: returns stack containg solution path
 */
Stack * tracePath(Stack * toSolve);

/**
 * Pre-conditions: Intilized stack with maze outline and marked spots that have
 * been traversed, x and y coordinates to check if movable coordinates in maze
 * Post-conditions: returns 1 for valid next move or 0 for invalid
 */
int nextMove(Stack * toSolve, int x, int y);

/**
 * Pre-conditions: Intilized stack with maze outline, and intilized stack with
 * the solution path
 * Post-conditions: return stack with maze filled with solution path
 */
Stack * fillPath(Stack * maze, Stack * path);

/**
 * Pre-conditions: Initilzed stack with maze, width and height of maze 
 * in the stack
 * Post-conditions: none
 */
void printMaze(Stack * maze, int rows, int cols);

#endif