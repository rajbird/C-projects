#ifndef _RDEOL_LOADROOMS_
#define	 _RDEOL_LOADROOMS_

/**
 * toScreen
 * Initializes ncurses screen, manages starting room positions, and makes calls to functions 
 * that print rooms and hallways to the screen.
 * IN: Pointer to the room struct array
 * NOTE: If window size, should be 43X99, is too small program quits.
 */
void toScreen(Room** room);

/**
 * printWalls
 * Prints walls of a room.
 * IN: Rooms starting coordinates, and pointer to an indvidual room struct 
 * OUT: void
 */
void printWalls(int y, int x, Room* rmPtr);

/**
 * printRoom
 * Prints items and floor pieces for a room. When printing items calls itemChar
 * to find what character is assoicated with item.
 * IN: Rooms starting coordinates, and pointer to an indvidual room struct 
 * OUT: void
 * POST: If room has less than 9 items, I don't know what happens with the empty
 * memory of empty item structs
 * ERROR: If any items have smae coordinates, the last item in the struct
 * is printed.
 */
void printRoom(int y, int x, Room* rmPtr);

/**
 * itemChar
 * Finds what character an item should print
 * IN: Item to be printed symbol, eg if door accepts d
 * OUT: returns character assoicated with that item
 */
char itemChar(char type);

#endif