/**
 *Rajbir Deol
 *0918139
 */
#include <stdlib.h>
#include <stdio.h>

#include "hash.h"

HTable * createTable(int len){
    HTable * h = malloc(sizeof(HTable));
    h->arr = malloc(sizeof(Elem *) * len);
    if(h == NULL || h->arr == NULL){
    	printf("Malloc Failed\n");
        destroyTable(h);
        return NULL;
    }

    for(int i=0;i<=len;i++){
        h->arr[i] = malloc(sizeof(Elem));
        if(h->arr[i] == NULL){
    	    printf("Malloc Failed\n");
            free(h->arr[i]);
            return NULL;
        }
        h->arr[i]->index = 0;
    }

    h->len = len;
    return h;
}

void destroyTable(HTable * map){
    if(map != NULL){
	    for(int i=0;i<map->len;i++){
	        free(ARR[i]);
	    }
        free(map);
    }
}

int hashFunc(void * key, HTable * map){
    int code = KEY key) % map->len;
    int quit =1;
    while(quit != 0){        
        if(code > map->len){
            code = 0;
        }
        if(ARR[code]->index < SIZE-1){
        	break;
        }
        else if(code-1 >= 0 && ARR[code-1]->index < SIZE-1){
            code--;
            break;
        }
        else if(code+1 <= map->len && ARR[code+1]->index < SIZE-1){
            code++;
            break;
        }
        code += 3;
    }
    return code;
}

void insertKey(HTable * map, void * key, void * value){
    int pos = hashFunc(key, map);
    if(map != NULL){
        ARR[pos]->Item[ARR[pos]->index].key = key;
        ARR[pos]->Item[ARR[pos]->index].value = value;
        ARR[pos]->index++;
    }
}

void removeKey(HTable * map, void * key){
	if(key != NULL){
        int code = KEY key) % map->len;
        int pos = -1;
	    while(pos != 7){
	        if((pos = locate(ARR[code], key)) != SIZE){
	            break;
	        }
	        else if(code >= 0 && (pos = locate(ARR[code-1], key)) != SIZE){
	            break;
	        }
	        else if(code <= map->len && (pos = locate(ARR[code+1], key)) != SIZE){
	            break;
	        }
	        code += 3;
	        if(code >= map->len){
	            code = 0;
	        }
	    }
	    ARR[code]->index--;
	    ARR[code]->Item[pos].value = NULL;
	    ARR[code]->Item[pos].key = NULL;
	    fix(map, pos, code);
	}
}

void * findKey(HTable * map, void * key){
    if(key != NULL){
	    int code = KEY key) % map->len;
	    while(code != map->len+7){
            if(code > map->len){
	            code = 0;
	        }
	        int pos;
	        if((pos = locate(ARR[code], key)) != SIZE){
	            return ARR[code]->Item[pos].value;
	        }
	        else if(code-1 >= 0 && (pos = locate(ARR[code-1], key)) != SIZE){
	            return ARR[code-1]->Item[pos].value;
	        }
	        else if(code+1 <= map->len-1 && (pos = locate(ARR[code+1], key)) != SIZE){
	            return ARR[code+1]->Item[pos].value;
	        }
	        code += 3;
	    }
    }
    return NULL;
}

void update(HTable * map, void * key, void * newValue){
    if(key != NULL && newValue != NULL){
	    int code = KEY key) % map->len;
        int pos;
	    while(code < map->len){
	        if((pos = locate(ARR[code], key)) != SIZE){
	        	break;
	        }
	        else if(code-1 >= 0 && (pos = locate(ARR[code-1], key)) != SIZE){
	        	break;
	        }
	        else if(code+1 <= map->len-1 && (pos = locate(ARR[code+1], key)) != SIZE){
	        	break;
	        }
	        code += 3;
	        if(code >= map->len){
	            code = 0;
	        }
	    }
	    ARR[code]->Item[pos].value = newValue;
    }
}

int locate(Elem * arr, void * key){
    if(arr != NULL){
        for(int i=0;i<arr->index;i++){
        	if( KEY arr->Item[i].key) == KEY key)){
        		return i;
        	}
        }	
    }
    return SIZE;
}
void fix(HTable * map, int pos, int code){
    if(ARR[code]->index != SIZE || ARR[code]->index != 1){
	    for(int i=pos;i<ARR[code]->index;i++){
            ARR[code]->Item[i].key = ARR[code]->Item[i+1].key; 
            ARR[code]->Item[i].value = ARR[code]->Item[i+1].value; 
        }
    }
}
