#ifndef _RDEOL_GAME_
#define	 _RDEOL_GAME_

/**
 * Player sturct, contains their actual position, the start position of the room
 * their in, gold count, a number that helps track their hallway condition, a number
 * that tracks if they were recently in combat, their current room, and quit variable.
 */
typedef struct Player{
	int x;
	int y;
	int startX;
	int startY;
	int in;
	int combat;
	int gold;
	int level;
	int quit;
}Hero;

/**
 * Status bar struct, contain heros health, attack, number of potions, number of items
 * in inventory and Inventory struct array of 5 that hold item type and stats.
 */
typedef struct statusBar
{
	int health;
	int attack;
	int potions;
	int numItems;
	struct Inventory
	{
		char type;
		int value;
	}members[5];
}Status;

/**
 * Monsters struct, holds monsters health, attack, speed, cycle, and in a array it holds
 * the monsters position in the hero struct array. 
 */
typedef struct Monsters
{
	int health;
	int attack;
	int speed;
	int cycle;
	int arr[2];
}Monster;

/**
 * gameLoop
 * Controls game screen, declares and initailzes Hero and statusBar struct. Gets user key stroke 
 * and if key stroke is w,a,s,d calls collison/inHallway function, and then moves user acorrdingly. 
 * If user presses p potions stuff happens and if they press q game quits. Calls quit function. 
 * IN: Pointer to the room struct array 
 * OUT: void
 * NOTE: if hero malloc fails or if screen is size too small, game will quit.
 * POST: If there is no hero declared in first room, hero will automatically be at postion 1,1
 * but invisible until moved.  
 */
void gameLoop(Room** room);

/**
 * collision
 * Depending on the move key pressed, collision checks if the next space is a space the hero
 * can occupy, or if something on that space affects game play. IF space is occupied by monster
 * combat begins and ends. 
 * IN: Pointer to the room struct array, hero struct, statusBar struct and monster array struct 
 * future y and x coordinates
 * OUT: Returns 0 if user cannot pass through. Returns 1 if hero can step on space.
 * POST: If item or monster in front of door, hero collects and no notification is displayed
 */
int collision(Room** rm, Hero* h, Status* s, Monster** m, int y, int x);

/**
 * Cleans a row in ncurces after message is printed
 * NOTE: If row is to be cleared, user has to press any key to continue
 */
void cleanUp();

/**
 * quit 
 * Prints game ending messages to user, frees memory, and ends ncurses.
 * IN: Pointer to the room struct array, hero struct, statusBar struct and monster struct array
 * OUT: void 
 */
void quit(Room** r, Hero* h, Status* s, Monster** m);


#endif