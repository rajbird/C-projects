/**
 * Rajbir Deol
 * 0918139
 */ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"
#include "stack.h"
#include "mazeSolver.h"

void dataParse(char* dataFile){
    FILE* dfp;
    dfp = fopen(dataFile, "r");
    if(dfp == NULL){
        printf("Data file couldn't be opened\n");
    }

    char line[105];
    int row = 0, len;
    Stack * maze = create();
    Stack * toSolve = create();

	while (fgets(line, 105, dfp)){
        len = strlen(line);
		if( len > 1){
            for(int i=0; i<len; i++){
            	if(line[i+1] == '\n' ){
            	    push(maze, i, row, line[i+1]);
            	    push(toSolve, i, row, line[i+1]);
            	    i++;
            	}
            	else{
            	    push(maze, i, row, line[i]);
            	    push(toSolve, i, row, line[i]);	
            	}
                
            }
            row++;
        }
    }

    fclose(dfp);

    Stack * pathFin = tracePath(toSolve);
    maze = fillPath(maze, pathFin);
    printMaze(maze, row, len+2);
    printf("\n");
    
    destroy(maze);
    destroy(toSolve);
    destroy(pathFin);
}

Stack * tracePath(Stack * toSolve){
    Stack * path = create();
    Node * temp;
    temp = toSolve->top;

    int x, y, endX, endY;
    while(temp != NULL){
    	if(temp->c == 'S'){
    		x = temp->x;
    		y = temp->y;
    	}
        else if(temp->c == 'F'){
            endX = temp->x;
            endY = temp->y;
        }
    	temp = temp->next;
    }

    char quit = 'q';
    while(quit != 'Q'){
        if( (nextMove(toSolve, x+1, y)) == 1){
            x += 1;
            push(path, x, y, '@');
        }
        else if( (nextMove(toSolve, x-1, y)) == 1){
            x -= 1;
            push(path, x, y, '@');
        }
        else if( (nextMove(toSolve, x, y+1)) == 1){
            y += 1;
            push(path, x, y, '@');
        }
        else if( (nextMove(toSolve, x, y-1)) == 1){
            y -= 1;
            push(path, x, y, '@');
        }
        else{
        	pop(path);
        	x = path->top->x;
        	y = path->top->y;
        }
        if(endX == x && endY == y){
        	quit = 'Q';
        }
    }
    
    return path;
}

int nextMove(Stack * toSolve, int x, int y){
    Node * temp;
    temp = toSolve->top;

    while(temp != NULL){
    	if(temp->x == x && temp->y == y){
    		if(temp->c == 'F'){
    			return 1;
    		}
    		else if(temp->c == ' '){
    			temp->c = '1';
    			return 1;
    		}
    		break;
    	}
    	temp = temp->next;
    }
    return 0;	
}

Stack * fillPath(Stack * maze, Stack * path){
    Node * temp, * dummy;
    temp = maze->top;
    dummy = path->top;

    while(dummy != NULL){
    	while(temp != NULL){
    		if(temp->x == dummy->x && temp->y == dummy->y){
    		    if(temp->c == 'F'){
    		    	break;
    		    }
    		    temp->c = dummy->c;
    		    break;
    		}
    		temp = temp->next;
    	}
    	dummy = dummy->next;
    	temp = maze->top;
    }
    return maze;	
}

void printMaze(Stack * maze, int rows, int cols){
	Node * temp;
    temp = maze->top;
    
    int col = 0, row = 0;
    for(int i=0; i<(cols*rows); i++){
        while(temp != NULL){
    	    if(temp->x == col && temp->y == row){
    	      printf("%c", temp->c);
    	      break;
    	    }
    	    temp = temp->next;
        }
       
        temp = maze->top;
        col++;
        if(col == cols){
        	col = 0;
        	row++;
        }
    }     
}