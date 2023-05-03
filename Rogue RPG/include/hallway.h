#ifndef _RDEOL_HALLWAY_
#define	 _RDEOL_HALLWAY_

/**
 * hallways
 * Finds every door in a room, assigns its coordinates to y and y variables, then passes info
 * to drawHallways.  
 * IN: Pointer to the room struct array, room number, longest room from rooms 1,2 and 3, and
 * a pointer to the head node that points to the hallways linked list
 * OUT: void
 */
void hallways(Room** r, int rmCount, int max, Hall* head);

/**
 * drawHallway
 * Draws hallways in three sections, the width(until between two walls), the up and down(when
 * two walls) and the left and right(between rooms 1-3 and 4-6). Calls store hallways each time
 * a hallway character is drawn.
 * IN: The door coordinates from which the hallway starts, maximum number of hallway characters
 * to draw for y and x, two variables that help describe where the door is, and a pointer to the
 * head node that points to the hallways linked list
 * OUT: void 
 * ERROR: If door is on edge of room, for example de1, hallway is drawns weridly. 
 */
void drawHallway(int doorY, int doorX, int maxY, int maxX, int odd, int yes, Hall* head);

/**
 * storeHallways
 * Stores the y and x coordinates of every door in a linked list struct.
 * IN: Hallway characters coordinates, and a pointer to the head node that points to the hallways
 * linked list.
 * OUT: void
 */
void storeHallways(int y, int x, Hall* head);

/**
 * inHallway
 * Deals with player once they have stepped on a door and into a hallway. Player is restricted 
 * to only move on hallway characters. 
 * IN: Pointer to the room struct array, pointer to the hero struct, player coordinates. 
 * OUT: Returns 1 is player can move on hallway they want to and 0 if they can't.
 * ERROR: If player is on door and tries to step on wall, they can. Sometimes won't be able to move
 * afterwards. 
 */
int inHallway(Room** r, Hero* h, int y, int x);

#endif
