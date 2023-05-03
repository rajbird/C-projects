#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>

#include "storeRoom.h"
#include "game.h"
#include "enemy.h"
#include "hallway.h"

void gameLoop(Room** room){
	char moveKeys[] = "wasd";

	Hero* hero;
	hero = malloc(sizeof(Hero));
	if (hero == NULL){
		mvprintw(0, 2, "malloc failded");
	}
	else {
		hero->gold = 0;
		hero->level = 0;
		hero->startY = 2;
		hero->startX = 10;
		hero->quit = 0;
		hero->in = 0;
		hero->combat = 0;
	}

	Status* bar;
	bar = malloc(sizeof(Status));
	if(bar == NULL){
		mvprintw(0, 2, "malloc failded");
		hero->quit = 1;
	}
	else{
		bar->health = 50;
		bar->attack = 5;
		bar->potions = 1;
		bar->numItems = 0;
	}

	Monster** monster = loadMonsters(room);

	noecho();
	curs_set(0);

	int rows, cols;
	getmaxyx(stdscr, rows, cols); 
    if(rows < 44 || cols < 99){
    	mvprintw(0, 2, "The screen size is still too small we needed atleast 44X100, the game will not continue.");
    }
 
	mvprintw(0, 2, "Welcome, to move use w(up) a(left) s(down) d(right) and q or step on stairs to Quit");
	cleanUp();

	for (int i = 0; i<9; i++){
		if (room[0]->item[i].type == 'h'){
			hero->y = room[0]->item[i].row;
			hero->x = room[0]->item[i].col;
			break;
		} 
	}
	while(hero->quit != 1){
		mvprintw(rows-1, 0, "Health: <%d>, Potions: <%d>, Attack: <%d>, Inv: <%d>    ", bar->health, bar->potions, bar->attack, bar->numItems);
		moveMonsters(room, hero, monster, bar);
		char key = getch();

		if(bar->health <= 1){
			mvprintw(0,2, "Your health is less than 1, you die");
		}
		if(strchr(moveKeys, key)){
			if (key == 'w'){
				if(hero->in > 0){
					hero->y -= inHallway(room, hero, hero->y-1, hero->x);;
					mvaddch(hero->y, hero->x, '@');
				}
				else{
					mvaddch(hero->y, hero->x, '.');
					hero->y -= collision(room, hero, bar, monster, hero->y-1, hero->x);
					mvaddch(hero->y, hero->x, '@');
				}
				
			}
			else if (key == 's'){
				if(hero->in > 0 ){
					hero->y += inHallway(room, hero, hero->y+1, hero->x);;
					mvaddch(hero->y, hero->x, '@');
				}
				else{
					mvaddch(hero->y, hero->x, '.');
					hero->y += collision(room, hero, bar, monster, hero->y+1, hero->x);
					mvaddch(hero->y, hero->x, '@');
				}
			}
			else if (key == 'a'){
				if(hero->in > 0){
					hero->x -= inHallway(room, hero, hero->y, hero->x-1);;
					mvaddch(hero->y, hero->x, '@');
				}
				else{
					mvaddch(hero->y, hero->x, '.');
					hero->x -= collision(room, hero, bar, monster, hero->y, hero->x-1);
					mvaddch(hero->y, hero->x, '@');
				}
			}
			else{
				if(hero->in > 0 ){
					hero->x += inHallway(room, hero, hero->y, hero->x+1);;
					mvaddch(hero->y, hero->x, '@');
				}
				else{
					mvaddch(hero->y, hero->x, '.');
					hero->x += collision(room, hero, bar, monster, hero->y, hero->x+1);
					mvaddch(hero->y, hero->x, '@');	
				}
			}
		}
		else if(key == 'p'){
			if(bar->potions == 0){
				mvprintw(0,2, "Sorry, you have no potions");
				cleanUp();
			}
			else{
				bar->potions--;
				bar->health = 50;
				mvprintw(0,2, "Yay, you are back at full health");
				cleanUp();
			}
		}
		else if (key == 'q'){
			mvprintw(0,0, "You quit");
			hero->quit = 1;
		}
	}
	quit(room, hero, bar, monster);
}

int collision(Room** rm, Hero* h, Status* s, Monster** m, int y, int x){
	char canGo[] = ("wWe");
	char monsta[] = ("AZSBT");
	
	if(h->in == -1){
		mvprintw(0, 2, "You stepped on a door");
		cleanUp();
		mvaddch(h->y, h->x, '+');
		h->in = -2;
		return 1;
	}
	if(h->combat == 1){
		h->combat = 0;
		return -1;
	}

	for(int i = 0; i < 9; i++){
		if(y == (rm[h->level]->item[i].row) && x == (rm[h->level]->item[i].col)){
			if(rm[h->level]->item[i].type == 'a' || rm[h->level]->item[i].type == 'z' ){
				mvprintw(0,0, "You quit");
				h->quit = 1;
				return 0;
			}
			else if(rm[h->level]->item[i].type == 'd'){
				h->in = 1;
			}
			else if(rm[h->level]->item[i].type == 'p'){
				mvprintw(0, 2, "Wow, you've picked up a potion");
				cleanUp();
				s->potions++;
			}
			
			else if(rm[h->level]->item[i].type == 'g'){
				h->gold += rm[h->level]->item[i].value;
				mvprintw(0, 2, "You collected * gold, you now have %d", h->gold);
				cleanUp();
			}
			else if (rm[h->level]->item[i].type == 'G'){
				h->gold += rm[h->level]->item[i].value;;
				mvprintw(0, 2, "You collected 8 gold, you now have %d", h->gold);
				cleanUp();
			}
			else if (strchr (canGo, rm[h->level]->item[i].type)){
				if (s->numItems < 5){
					mvprintw(0, 2, "Wow, you've picked up an item of type: %c with stat: %d", rm[h->level]->item[i].type, rm[h->level]->item[i].value);
					cleanUp();
					s->numItems++;
					s->members[s->numItems].type = rm[h->level]->item[i].type;
					s->members[s->numItems].value = rm[h->level]->item[i].value;
					rm[h->level]->item[i].col = 0;
					rm[h->level]->item[i].row = 0;
				}
				else {
					mvprintw(0, 2,"Uh oh, you stepped on and broke %c. You couldn't collect %c because your inventory is full.", rm[h->level]->item[i].type, rm[h->level]->item[i].type);
					cleanUp();
					rm[h->level]->item[i].col = 0;
					rm[h->level]->item[i].row = 0;
				}
			}
				
			else if(strchr(monsta, rm[h->level]->item[i].type)){
				h->combat = 1;
				mvprintw(0, 2, "Oh no a monster, BEGIN COMBAT with monster: %c",rm[h->level]->item[i].type);
				cleanUp(); 
				int random = rand() % 10 + 1;
				if(random <= m[rm[h->level]->item[i].value]->speed ){
					if(rm[h->level]->item[i].type =='A'){
						s->attack -= m[rm[h->level]->item[i].value]->attack;
						mvprintw(0, 2, "Oh oh monster %c decreased your attack bye", rm[h->level]->item[i].type, m[rm[h->level]->item[i].value]->attack);
						cleanUp();
					}
					else{
						mvprintw(0, 2, "Monster %c attacked and gave %d damage",rm[h->level]->item[i].type, m[rm[h->level]->item[i].value]->attack);
						cleanUp();
						s->health -= m[rm[h->level]->item[i].value]->attack;
					}
				}
				else {
					mvprintw(0, 2, "You gave monster %c %d damage",rm[h->level]->item[i].type, s->attack);
					cleanUp();
					m[rm[h->level]->item[i].value]->health -= s->attack;
					if(m[rm[h->level]->item[i].value]->health == 0){
						mvprintw(0, 2, "You are legendary, you killed monster %c", rm[h->level]->item[i].type);
						cleanUp();
						rm[h->level]->item[i].type = 'K';
						return 1;
					}	
				}
				return 0;
			}
			else if(rm[h->level]->item[i].type =='K'){
				mvaddch(y, x, '@');
			}
			return 1;
		}
	}
	if(y > (rm[h->level]->rowLen + h->startY) || y <= h->startY ||  x > (rm[h->level]->colLen + h->startX) || x <= h->startX){
		return 0;
	}
	else {
		return 1;
	}
}

void cleanUp(){
    getch();
    int xCoord = 0;
    for (int i=0; i < 120; i++){
    	mvaddch(0, xCoord+i,' ');
    }

}

void quit(Room** r, Hero* h, Status* s, Monster** m){
	clear();
	mvprintw(2,2, "In total you've collected %d gold!!!", h->gold);
	if(s->numItems != 0){
		mvprintw(3,2, "In your inventory you have");
		for(int i=0; i<s->numItems; i++){
			mvprintw(4+i,4, "item: %c stat: %d", s->members[i].type, s->members[i].value);
		}
	}
	else{
		mvprintw(3,2, "In your inventory you have NOTHING");
	}
		
	mvprintw(8,6, "Press any key to leave");
	mvprintw(10,6, "toodaloo");
	getch();
	endwin();

	free(h);
	free(s);
	for(int i = 0; i < r[1]->item[0].value; i++){
		free(m[i]);
	}
	free(m);
	Hall* curr;
	Hall* head = r[0]->next->next;
	for(int i = 0; i < 6; i++){
		free(r[i]);
	}
	free(r);
	while ((curr = head) != NULL) { 
	    head = head->next;    
	    free (curr);                
	}

}
