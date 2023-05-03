#ifndef _RDEOL_ENEMY_
#define	 _RDEOL_ENEMY_

/**
 * loadMonsters
 * Stores every monster into a struct array found in game.h
 * IN:  Pointer to the room struct array
 * OUT: Pointer to the monster struct array 
 * POST: Could not declare monster struct in this .h file due to compiler errors
 */
Monster** loadMonsters(Room** r);

/**
 * moveMonsters
 * Moves monsters on screen each type any key is pressed.
 * IN: Pointer to the room struct array, pointer to the hero struct, pointer to the monster 
 * struct array and pointer to the status bar struct. 
 * OUT: void
 */
void moveMonsters(Room** r, Hero* h, Monster** m, Status* s);

/**
 * canMonster
 * Checks if monster can move to the space it wants to, if space is occupied by hero combat begins
 * IN: Monsters coordinates, pointer to the room struct array, pointer to the hero struct, pointer
 * to the monster 
 * struct array and pointer to the status bar struct. 
 * OUT: 1 if the monster can move on to space and 0 if it can't
 */
int canMonster(int y, int x, int rmNum, Room** rm, Hero* h, Monster* m, Status* s);

#endif