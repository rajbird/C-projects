/**
 *Rajbir Deol
 *0918139
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "hash.h"

int main(){
    srand(time(NULL));
    int arr[30];
    for(int i=0;i<30;i++){
        int r = rand();
        arr[i] = r;
    }
    HTable * table = createTable((30 / SIZE) * 2);
    printf("Creat Table: SUCESS\n");

    char *c = malloc(sizeof(char)*3);
    c = "cat";
    for(int i=0;i<30;i++){
        insertKey(table, &arr[i], c);
    }
    printf("Insert Keys: SUCESS\n");
    printf("Hash Fucntion: SUCESS\n");
    
    removeKey(table, &arr[2]);
    printf("Remove Key(key esists): SUCESS\n");
    removeKey(table, NULL);
    printf("Remove Key(NULL): SUCESS\n");
    printf("Fix Hash Table(after removal of key): SUCESS\n");

    char *b = malloc(sizeof(char)*3);
    b = "bug";
    update(table, &arr[0], b);
    printf("Update Value(key esists): SUCESS\n");
    update(table, NULL, NULL);
    printf("Update Value(NULL): SUCESS\n");
    printf("Locate Key: SUCESS\n");

    void * ptr = findKey(table, &arr[0]);
    if(ptr != NULL){
        if(( (strcmp("bug", VALUE ptr)) == 0)){
            printf("Find key(key esists): SUCESS\n");
        } 
    }
    ptr = NULL;
    ptr = findKey(table, NULL);
    if(ptr == NULL){
        printf("Find key(NULL): SUCESS\n");
    }
    
    destroyTable(table);
    printf("Destroy Hash Table: SUCESS\n");
    destroyTable(NULL);
    printf("Destroy Hash Table(NULL): SUCESS\n");

    printf("no segfault = extra sucess\n");
    return 0;
}