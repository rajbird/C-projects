#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>

#include "storeRoom.h"
#include "loadRooms.h"
#include "game.h"
#include "hallway.h"

void toScreen(Room** room){
    initscr();

    srand(time(NULL)); 

    int longest;
	if( (room[0]->rowLen >= room[1]->rowLen) && (room[0]->rowLen >= room[2]->rowLen) ){
		longest = room[0]->rowLen;
	}
    else if( (room[1]->rowLen >= room[0]->rowLen ) && (room[1]->rowLen>= room[2]->rowLen) ){
    	longest = room[1]->rowLen;
    }
    else {
    	longest = room[2]->rowLen;
    }

    Hall* head;
	head = malloc(sizeof(Hall));
	if (head == NULL){
		mvprintw(0, 2, "malloc failded");
	}
	else{
		head->x = 0;
		head->next = NULL;
	    head->y = longest;
	}

    int rows, cols;
    getmaxyx(stdscr, rows, cols); 
    if(rows < 44 || cols < 100){
    	printw("Oh no, your screen size (%dX%d) is to small, we need atlest 43X100!", rows, cols);
		getch();
    }
    else {
    	int startX  = 10, startY = 2;
    	for(int i = 0; i < 6; i++){
    		if (i <= 2){
    			printWalls(startY, startX, room[i]);
    			printRoom(startY, startX, room[i]);
    			startX += room[i]->colLen + 10;		
    		}
    		else {
    			if (i == 3){
    				startX = 10;
    				startY = longest + 7;
    			}
    			printWalls(startY, startX, room[i]);
    			printRoom(startY, startX, room[i]);
    			startX += room[i]->colLen + 10;

    		}
    		room[i]->next = head;
    		hallways(room, i, longest, head);
    	}
 	}
}

void printWalls(int y, int x, Room* rmPtr){
	for(int i = x; i <=(rmPtr->colLen + (x + 1)); i++){
		mvaddch(y, i, '-');
		mvaddch((y + rmPtr->rowLen + 1), i, '-');
		refresh();
	}

	for(int i = (y+1); i <=(rmPtr->rowLen + y); i++){
		mvaddch(i, x,'|');
		mvaddch(i, (x + rmPtr->colLen + 1), '|');
		refresh();
	}			
}

void printRoom(int y, int x, Room* rmPtr){
	int numTiles = 0;
	int newY = (y + 1), newX = x;
	char monsta[] = ("AZSBT");
	
	while (numTiles < (rmPtr->rowLen * rmPtr->colLen )){
		newX++;
		if(newX == (rmPtr->colLen + (x + 1))){
			newX = x + 1;
			newY++;
			mvaddch(newY, newX , '.');
		}
		else {
			mvaddch(newY, newX, '.');
		}
		numTiles++;
	}
	for (int i = 0; i < 9; i++){
		rmPtr->item[i].row += y;
		rmPtr->item[i].col += x;
		char c;
		c = itemChar(rmPtr->item[i].type);
		if(strchr (monsta, c)){
			rmPtr->item[i].type = c;
		}
		mvaddch(rmPtr->item[i].row, rmPtr->item[i].col, c);
	}

}

char itemChar(char type){
	if(type == 'h'){
		return '@';
	}
	else if(type == 'z'){
		return '<';
	}
	else if(type == 'a'){
		return '>';
	}
	else if(type == 'g'){
		return '*';
	}
	else if(type == 'G'){
		return '8';
	}
	else if(type == 'w'){
		return ')';
	}
	else if(type == 'W'){
		return '(';
	}
	else if(type == 'm'){
		int randNum;
		randNum = rand() % 4;
		if(randNum == 1){
			return 'A';
		}
		else if(randNum == 2){
			return 'B';
		}
		if(randNum == 3){
			return 'S';
		}
		else{
			return 'Z';
		}
	}
	else if(type == 'M'){
		return 'T';
	}
	else if(type == 'e'){
		return ']';
	}
	else if(type == 'p'){
		return '!';
	}
	else if(type == 'd'){
		return '+';
	}
	else {
		return '-';
	}
}
