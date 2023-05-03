#ifndef _RDEOL_STOREROOM_
#define	 _RDEOL_STROEROOM_

/**
 * Hallways linked list struct, holds hallway coordinates and pointer to next struct. 
 */
typedef struct Hallways{
	int y;
	int x;
	struct Hallways* next;
}Hall;

/**
 * Struct to a room, contains rooms dimensions, number of doors and monster in a room,
 * and a item struct. array. The item struct stores item type, value and its coordinates. 
 */
typedef struct Rooms{
	int rowLen;
	int colLen;
	int door;
	int mon;
	Hall* next;

	struct{
		char type;
		int row;
		int col;
		int value;
	}item[9];

}Room;


/**
 * readinRoom
 * Opens file, creates memory for array of pointers that point to room structs. It
 * then parse a line from a file and calls storeElements. Then stores the return
 * pointer inside the room struct array. Once all lines parsed, toScreen is called. 
 * IN: pointer to datafile name.
 * OUT: returns pointer to an array of struct pointers
 * POST: Don't know what happens with empty memory 
 * ERROR: If less than 6 lines in dataFile, segfault and program is unusable until
 * datafile is fixed. If more that 6 lines in dataFile only first 6 are stored.
 */
Room** readinRoom(char* dataFile);

/**
 * storeElements
 * Creates memory for a room struct, and then seperates elements and stores them 
 * in that room struct. 
 * IN: Length of parsed line from datafile, line from dataFile, and room number.
 * OUT: Returns pointer to room struct
 * POST: If more than 10 elements given, only stores first 10. 
 */
Room* storeElements(int len, char line[len], int rmNum);

#endif