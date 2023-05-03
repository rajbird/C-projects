#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"
#include "menuProgram.h"

void menuStart(char * file){
    int quit = 0, load = 0;
    Node * theList;
    HTable * theMap;
    char newFile[99];
    int user = 7;
    printf("Menu Options\n   1. Load File\n   2. Add Entry\n   3. Print List\n   4. Lookup Name\n   5. Quit\nEnter a number between 1-5\n");
    
    do{
        printf("MENU OPTION >");
        scanf("%d", &user);
        if(user == 1){
            if(load == 1){
                destroyTable(theMap);
                destroyList(theList);
                theList = NULL;
                theMap = NULL;
                printf("Enter a file name, with .txt between 1-99 characters\n>");
	            scanf("%s", newFile);
                theList = dataStore(newFile);
                theMap = loadFile(theList);
            }
            else{
                theList = dataStore(file);
                theMap = loadFile(theList);
            }
            printf("File Loaded\n");
            load = 1;
        }
        else if(user == 2 && load == 1){
        	newEntry(theMap, theList);
            printf("Entry added\n");
        }
        else if(user == 3 && load == 1){
            printf("\n");
            printList(theList);
            printf("\n"); 
        }
        else if(user == 4 && load == 1){
            checkNum(theList, theMap);
        }
        else if(user == 5){
            destroyTable(theMap);
            destroyList(theList);
            quit = 1;
            printf("Program was quitted, Toodles\n");
        }
        else{
            if(load != 1){
            	printf("No file has been loaded, TRY AGAIN\n");
            }
            else{
                printf("Entry: %d was not between 1-5, TRY AGAIN\n>", user);
                printf("Menu Options\n   1. Load File\n   2. Add Entry\n   3. Print List\n   4. Lookup Name\n   5. Quit\nEnter a number between 1-5\n");
            }
            user = 7;
        }
    }while(quit != 1);
}

Node * dataStore(char * dataFile){
    FILE* dfp;
    dfp = fopen(dataFile, "r");
    if(dfp == NULL){
        printf("Data file couldn't be opened\n");
    }
        
    Node* head = NULL;
    char line[115];
    while (fgets(line, 115, dfp) != NULL){
        int len;
        len = strlen(line);
        if(line[len - 1] == '\n' && len > 1){
            Node * add;
            char * pos1, * pos2;
                
            pos1 = strchr(line, ',');
            line[(int)(pos1 - line)] = ' ';

            pos2 = strchr(line, ',');
            line[(int)(pos2 - line)] = '\0';

            char * name = malloc(sizeof(char) * strlen(line) +1);
            long long *num = malloc(sizeof(long long));
            if(name == NULL || num == NULL){
		    	printf("Malloc Failed\n");
		    	free(name);
		    	free(num);
		    }
            strcpy(name, line);
            char *eptr;
            *num = strtoll (pos2 + 1, &eptr, 10);
            if(num == 0){
            	printf("Conversion error occured: %s\n", eptr);
            }

            add = createNode(name, num);
            head = addNode(add, head);
        }
    }
    fclose(dfp);
    return head;
}

HTable * loadFile( Node * theList){
    if(theList != NULL){
        HTable * map = createTable( ((listLength(theList)) / SIZE)*2);
        Node* temp = theList;
        while(temp != NULL){
            insertKey(map, temp->value, temp->data);
            temp = temp->next;
        }
        return map;
    }
    return NULL;
}

void newEntry(HTable * map, Node * theList){
    char * name = malloc(sizeof(char) * 101);
    long long * num = malloc(sizeof(long long));
    if(name == NULL || num == NULL){
    	printf("Malloc Failed\n");
    	free(name);
    	free(num);
    }

    printf("\nEnter new entries number\n>");
    scanf("%lld", num);

    char first[50], last[50];
    printf("Enter new entries name(firstname(space)lastname)\n>");
    scanf("%s %s", first, last);

    int j = 0;
    for(int i=0; i<50; i++){
    	if(i < strlen(first)){
    		name[i] = first[i];
    	}
    	else if(i == strlen(first)){
    	    name[i] = ' ';
    	}
    	else{
    		name[i] = last[j];
    		j++;
    	}
    }

    Node * add = createNode(name, num);
    theList = addNode(add, theList);
    if(map->len > listLength(theList)){
    	destroyTable(map);
    	map = NULL;
    	map = loadFile(theList);
    	insertKey(map, add->value, add->data);
    }
    else{
    	insertKey(map, add->value, add->data);
    }
}

void checkNum(Node * theList, HTable * map){
    int found = 0;
    if(theList != NULL){
        long long num;
        printf("Enter number to find name with\n>");
        scanf("%lld", &num);
        Node * temp = theList;
        
        while(temp != NULL){
            if( VAL temp->value) == num){
				void * ptr = findKey(map, &num);
				printf("Name found: %s with number: %lld\n", VALUE ptr, num);
				found = 1;
				break;
			}
			temp = temp->next;
        }
    }
    if(found == 0){
    	printf("Number was not found in list\n");
    }
}