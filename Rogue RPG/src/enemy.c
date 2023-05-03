#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>

#include "storeRoom.h"
#include "loadRooms.h"
#include "game.h"
#include "enemy.h"

Monster** loadMonsters(Room** r){
	char monsta[] = ("ABSZT");
	srand(time(NULL));

	int monstas = 0;
	for(int i=0; i < 6; i++){
		monstas += r[i]->mon;
	}

	Monster** villian = malloc(sizeof(Monster*) * monstas);
	if (villian == NULL){
		mvprintw(0, 2, "malloc failded");
	}
	
	r[1]->item[0].value = monstas;
	for(int i=0; i < 6; i++){
		int count = r[i]->mon;
		for(int j=0; j < 9; j++){
			if(strchr(monsta, r[i]->item[j].type) && count > 0){
				monstas--;
				count--;
				Monster* v = malloc(sizeof(Monster));
				if (v == NULL){
					mvprintw(0, 2, "malloc failded");
				}
				if(r[i]->item[j].type == 'A'){
					v->health = 5;
					v->attack = 1;
					v->speed = 2;
				}
				else if(r[i]->item[j].type == 'B'){
					v->health = 2;
					v->attack = 5;
					v->speed = 4;
				}
				else if(r[i]->item[j].type == 'S'){
					v->health = 5;
					v->attack = 5;
					v->speed = 4;
				}
				else if(r[i]->item[j].type == 'Z'){
					v->health = 15;
					v->attack = 5;
					v->speed = 2;
				}
				else{
					v->health = 50;
					v->attack = 5;
					v->speed = 3;
				}
				v->arr[0] = i;
				v->arr[1] = j;
				v->cycle = 0;
				r[i]->item[j].value = monstas;
				villian[monstas] = v;
			}
		}
	}

	return villian;
}

void moveMonsters(Room** r, Hero* h, Monster** m, Status* s){
	for(int i=0; i < r[1]->item[0].value; i++){
		mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, '.');
		if(r[m[i]->arr[0]]->item[m[i]->arr[1]].type == 'B'){
			int random = rand() % 4;
			if(random == 0){
				r[m[i]->arr[0]]->item[m[i]->arr[1]].col += canMonster(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col+1, m[i]->arr[0], r, h, m[i], s);
				mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, 'B');
			}
			else if(random == 1){
				r[m[i]->arr[0]]->item[m[i]->arr[1]].col -= canMonster(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col-1, m[i]->arr[0], r, h, m[i], s);
				mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, 'B');
			}
			else if(random == 2){
				r[m[i]->arr[0]]->item[m[i]->arr[1]].row += canMonster(r[m[i]->arr[0]]->item[m[i]->arr[1]].row+1, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, m[i]->arr[0], r, h, m[i], s);
				mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, 'B');
			}
			else{
				r[m[i]->arr[0]]->item[m[i]->arr[1]].row -= canMonster(r[m[i]->arr[0]]->item[m[i]->arr[1]].row-1, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, m[i]->arr[0], r, h, m[i], s);
				mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, 'B');
			}

		}
		else if(r[m[i]->arr[0]]->item[m[i]->arr[1]].type == 'T'){
			if(m[i]->cycle == 0){
				m[i]->cycle = 1;
				r[m[i]->arr[0]]->item[m[i]->arr[1]].row -= canMonster(r[m[i]->arr[0]]->item[m[i]->arr[1]].row-1, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, m[i]->arr[0], r, h, m[i], s);
				mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, 'T');
			}
			else if(m[i]->cycle  == 1){
				m[i]->cycle = 2;
				r[m[i]->arr[0]]->item[m[i]->arr[1]].col += canMonster(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col+1, m[i]->arr[0], r, h, m[i], s);
				mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, 'T');
			}
			else if(m[i]->cycle  == 2){
				m[i]->cycle = 3;
				r[m[i]->arr[0]]->item[m[i]->arr[1]].row += canMonster(r[m[i]->arr[0]]->item[m[i]->arr[1]].row+1, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, m[i]->arr[0], r, h, m[i], s);
				mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, 'T');
			}
			else{
				m[i]->cycle = 0;
				r[m[i]->arr[0]]->item[m[i]->arr[1]].col -= canMonster(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col-1, m[i]->arr[0], r, h, m[i], s);
				mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, 'T');}

		}
		else if(r[m[i]->arr[0]]->item[m[i]->arr[1]].type == 'S'){
			if(m[i]->cycle == 0 || m[i]->cycle == 1){
				if(m[i]->cycle == 0){
					m[i]->cycle = 1;
				}
				else{
					m[i]->cycle = 2;
				}
				r[m[i]->arr[0]]->item[m[i]->arr[1]].col += canMonster(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col+1, m[i]->arr[0], r, h, m[i], s);
				mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, 'S');
			}
			else{
				if(m[i]->cycle == 3){
					m[i]->cycle = 0;
				}
				else{
					m[i]->cycle = 3;
				}
				r[m[i]->arr[0]]->item[m[i]->arr[1]].col -= canMonster(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col-1, m[i]->arr[0], r, h, m[i], s);
				mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, 'S');
			}
		}
		else if(r[m[i]->arr[0]]->item[m[i]->arr[1]].type == 'Z'){
			if(m[i]->cycle == 0){
				m[i]->cycle = 1;
				r[m[i]->arr[0]]->item[m[i]->arr[1]].row += canMonster(r[m[i]->arr[0]]->item[m[i]->arr[1]].row+1, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, m[i]->arr[0], r, h, m[i], s);
				mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, 'Z');
			}
			else{
				m[i]->cycle = 0;
				r[m[i]->arr[0]]->item[m[i]->arr[1]].row -= canMonster(r[m[i]->arr[0]]->item[m[i]->arr[1]].row-1, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, m[i]->arr[0], r, h, m[i], s);
				mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, 'Z');
			}
		}
		else if(r[m[i]->arr[0]]->item[m[i]->arr[1]].type == 'A'){
			mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, 'A');
		}
		else{
			if(h->y == r[m[i]->arr[0]]->item[m[i]->arr[1]].row && h->x == r[m[i]->arr[0]]->item[m[i]->arr[1]].col){
				mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, '@');
			}
			else{
				mvaddch(r[m[i]->arr[0]]->item[m[i]->arr[1]].row, r[m[i]->arr[0]]->item[m[i]->arr[1]].col, '.');
			}
		}
	}
}

int canMonster(int y, int x, int rmNum, Room** rm, Hero* h, Monster* m, Status* s){
	if(h->combat == 1){
		h->combat = 0;
		return 0;
	}

	int startX, startY;
	if(rmNum == 1 || rmNum == 4){
		startX = rm[rmNum - 1]->colLen + 20;
	}
	else if( rmNum == 2 || rmNum == 5){
		startX = rm[rmNum - 1]->colLen + rm[rmNum - 2]->colLen + 30;
	}
	else{
		startX = 10;
	}
	if(rmNum > 2){
		startY = rm[0]->next->y + 7;
	}
	else{
		startY = 2;
	}
	for(int i = 0; i < 9; i++){
		if(y == (rm[rmNum]->item[i].row) && x == (rm[rmNum]->item[i].col)){
			return 0;
			
		}
	}
	if(y > (rm[rmNum]->rowLen + startY) || y <= startY ||  x > (rm[rmNum]->colLen + startX) || x <= startX){
		return 0;
	}
	if(y == h->y && x == h->x){
		h->combat = 1;
		mvprintw(0, 2, "A monster stepped on you, BEGIN COMBAT with monster: %c",rm[m->arr[0]]->item[m->arr[1]].type);
		cleanUp(); 
		int random = rand() % 10 + 1;
		if(random <= m->speed ){
			if(rm[m->arr[0]]->item[m->arr[1]].type =='A'){
				s->attack -= m->attack;
				mvprintw(0, 2, "Oh oh monster %c decreased your attack bye", rm[m->arr[0]]->item[m->arr[1]].type, m->attack);
				cleanUp();
			}
			else{
				mvprintw(0, 2, "Monster %c attacked and gave %d damage",rm[m->arr[0]]->item[m->arr[1]].type, m->attack);
				cleanUp();
				s->health -= m->attack;
			}
		}
		else {
			mvprintw(0, 2, "You gave monster %c %d damage",rm[m->arr[0]]->item[m->arr[1]].type, s->attack);
			cleanUp();
			m->health -= s->attack;
			if(m->health == 0){
				mvprintw(0, 2, "You are legendary, you killed monster %c", rm[m->arr[0]]->item[m->arr[1]].type);
				cleanUp();
				rm[m->arr[0]]->item[m->arr[1]].type = 'K';
				return 1;
			}	
		}
		return 0;

	}

	return 1;
	
}