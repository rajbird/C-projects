#ifndef __RDEOL_DATAFILE__
#define __RDEOL_DATAFILE__

/**
 * dataStore
 * Parse lines from data file, calls funtion to create Food
 * pointer, then calls functions to store items.
 * IN: Name of data file
 * OUT: Pointer to the head of linked list
 */
Food* dataStore(char* dataFile);

/**
 * functionName
 * A short description of what the function does
 * IN: Length of parsed line from data file, adn the parsed
 * line.
 * OUT: Pointer to the new node 
 */
Food* dataParse(int len, char line[len]);

#endif