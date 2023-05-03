#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>

#include "storeRoom.h"
#include "loadRooms.h"
#include "game.h"
#include "hallway.h"

void hallways(Room** r, int rmCount, int max, Hall* head){
	int where = 10;
	if(rmCount == 1 || rmCount == 4){
		where += r[rmCount - 1]->colLen + 10;
	}
	else if( rmCount == 2 || rmCount == 5){
		where += r[rmCount - 1]->colLen + r[rmCount - 2]->colLen + 20;
	}
	
	int pointX = (r[0]->rowLen + (r[1]->rowLen / 2) + 25);
	int pointY = max + 5;
	
	for(int i=0; i < r[rmCount]->door; i++){
		int x, y;
		y = r[rmCount]->item[i].row;
		x = r[rmCount]->item[i].col;
		if(r[rmCount]->item[i].value == 1){
			drawHallway(y, x, pointY - y, pointX - x, 5, 0, head);

		}
		else if(r[rmCount]->item[i].value == 2){
			drawHallway(y, x, pointY - y, pointX - x, 1, 0, head);
		}
		else if(r[rmCount]->item[i].value  == 3){
			if(rmCount < 3){
				drawHallway(y, x, pointY - y, pointX - x, 2, 1, head);
			}
			else{
				drawHallway(y, x, pointY - y, pointX - x, 1, (r[rmCount]->colLen + where) - x, head);
			}
			
		}
		else{
			if(rmCount >= 3){
				drawHallway(y, x, pointY - y, pointX - x, 3, 1, head);
			}
			else{
				drawHallway(y, x, pointY - y, pointX - x, -1, (r[rmCount]->colLen + where) - x, head);
			}
		}
		mvaddch(y, x, '+');
	}
		
}

void drawHallway(int doorY, int doorX, int maxY, int maxX, int odd, int yes, Hall* head){ 
	int width;
	width = rand() % 5 + 2;
	//When near other walls
	if(yes == 0){
		if(odd == 1){
			doorX -= width;
			for(int i=0; i <= width; i++){
				mvaddch(doorY, doorX+i, '#');
				storeHallways(doorY, doorX+i, head);
			}
		}
		else{
			for(int i=0; i <= width; i++){
				mvaddch(doorY, doorX+i, '#');
				storeHallways(doorY, doorX+i, head);
			}
			doorX += width;
		}
	}
	else if((odd == 1 || odd == -1) && yes != 0){
		for(int i=0; i <= (3+yes); i++){
			mvaddch(doorY+odd, doorX+i, '#');
			storeHallways(doorY+odd, doorX+i, head);
		}
		doorX += (yes + 3);
		if(odd == -1){
			mvaddch(doorY+odd+1, doorX, '#');
			storeHallways(doorY+odd+1, doorX, head);
		}
	}
	
	//The up or down	
	if(doorY > maxY && odd != 2){
		for(int i=maxY; i <= 0; i++){
			mvaddch(doorY+i, doorX, '#');
			storeHallways(doorY+i, doorX, head);
		}
		if(odd == 5){
			for(int i=1; i <= maxY; i++){
				mvaddch(doorY+i, doorX, '#');
				storeHallways(doorY+i, doorX, head);
			}
		}
		doorY += maxY;
	}
	else{
		for(int i=1; i <= maxY; i++){
			mvaddch(doorY+i, doorX, '#');
			storeHallways(doorY+i, doorX, head);
		}
		doorY += maxY;
	}
	
	//Side to side on the line with the mark
	if(maxX <= 0){
		for(int i = (maxX - width); i < 0; i++){
			mvaddch(doorY, doorX+i, '#');
			storeHallways(doorY, doorX+i, head);
		}
	}
	else {
		for(int i=0; i <= (maxX + width); i++){
			mvaddch(doorY, doorX+i, '#');
			storeHallways(doorY, doorX+i, head);
		}
	}
}

void storeHallways(int y, int x, Hall* head){
	Hall* new;
	Hall* temp;

	new = malloc(sizeof(Hall));
	if (new == NULL){
		mvprintw(0, 2, "malloc failded");
	}

	new->y = y;
	new->x = x;
	new->next = NULL;

	temp = head;
	if(head->next == NULL){
		head->next = new;
	}
	else{
		int freed = 0;
		while(temp->next){
			if(x == temp->x && y == temp->y){
				freed = 1;
				free(new);
				break;
			}
			temp = temp->next;
		}
		if(freed == 0){
			temp->next = new;
		}
	}
	
}

int inHallway(Room** r, Hero* h, int y, int x){
	Hall* temp;
	temp = r[0]->next;

	if(h->in == 1){
		mvprintw(0, 2, "You stepped on a door");
		cleanUp();
		mvaddch(h->y, h->x, '+');
		h->in = 2;
		return 1;
	}

	for(int i=0; i<6; i++){
		for(int j=0; j < r[i]->door; j++){
			if(x == r[i]->item[j].col && y == r[i]->item[j].row){
				cleanUp();
				mvaddch(h->y, h->x, '#');
				h->in = -1;
				h->level = i;
				if(h->level == 1 || h->level == 4){
					h->startX = r[h->level - 1]->colLen + 20;
				}
				else if( h->level == 2 || h->level == 5){
					h->startX = r[h->level - 1]->colLen + r[h->level - 2]->colLen + 30;
				}
				else{
					h->startX = 10;
				}
				if(h->level > 2){
					h->startY = temp->y + 7;
				}
				else{
					h->startY = 2;
				}
				return 1;
			}
		}
	}

	while(temp->next != NULL){
		temp = temp->next;
		if(temp->y == y && temp->x == x){
			mvaddch(h->y, h->x, '#');
			return 1;
		}
	}
	return 0;
}
