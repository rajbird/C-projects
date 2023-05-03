/**
 *Rajbir Deol
 *0918139
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "menuProgram.h"

void menu(char * dirPath){
    Tree * tree = createBinTree(&compareFile, &destroyFile);
    parseDirectory(dirPath, tree);
    int user = -1;
    printf("Menu Program\n1. Search for file\n2. Delete file\n3. Rename file\n4. Move file\n5. Print Directory\n6. Quit\n");


    while(user != 6){
        if(user != -1){
            printf("\nMenu Program\n1. Search  2. Delete  3. Rename  4. Move  5. Print  6. Quit\n");

        }
        printf("> ");
        scanf("%d", &user);
        if(user == 1){
            printf("\nEnter a file name of the file to search, between 1-99 characters\n>");
            char file[99];
            scanf("%s", file);
            int * dups = search(file, tree, 1);
            if(*dups == 0){
                printf("File was not found\n");
            }
            free(dups);
        }
        else if(user == 2){
            deleteFile(tree);
        }
        else if(user == 3){
            renameFile(tree);
        }
        else if(user == 4){
            moveFile(tree);
        }
        else if(user == 5){
            printf("\n");
            printInOrder(tree->root, &printFile);
        }
    }
    printf("Program was quit! Toodles\n");
    destroyBinTree(tree->root, &destroyFile);
    free(tree);
}

int * search(char * data, Tree * tree, int print){
    if(tree != NULL){
        int * repeats = malloc(sizeof(int)); 
        *repeats = 0;
        searchTree(data, tree->root, print, repeats);
        return repeats;
    }
    return NULL;
}

void searchTree(char * data, TreeNode * root, int print, int * dups){
    if(root == NULL){
        return ;
    }
    if(strstr( ((File *)root->data)->name, data)){
        if(print == 1){
            printf("File Path:%s\n", ((File *)root->data)->name);
        }
        *dups +=1;
    }
    searchTree(data, root->left, print, dups);
    searchTree(data, root->right, print, dups);
}

void deleteFile(Tree * tree){
    if(tree != NULL){
        printf("\nEnter a file name of the file to delete, between 1-99 characters\n");
        char file[99];
        int quit = 0;
        while(quit != 3){
            printf("> ");
            scanf("%s", file);
            int * dups = search(file, tree, 0);
            if(*dups == 1){
                char * path = malloc(sizeof(char) * 300);
                searchPath(file, tree->root, path, 0);
                free(dups);

                int ret = remove(path);
                if(ret == 0){
                  printf("File deleted successfully\n");
                  File * toDie = createEntry(path);
                  removeFromTree(tree, toDie);
                  destroyFile(toDie);
                }
                else {
                  printf("Error: unable to delete the file\n");
                }

                free(path);
                break;
            }
            else if(*dups > 1){
                dups = search(file, tree, 1);
                printf("There is more than one file named: %s. Not sure which to delete\nENTER a more specific file path(choose from above)\n", file);
                quit += 1;
                free(dups);
            }
            else{
                printf("File: %s was not found! Try again\n", file);
                quit += 1;
                free(dups);
            }
            if(quit == 3){
                printf("You do not know what file you want, try again when you do\n");
            }
        }
    }
}

void renameFile(Tree * tree){
    if(tree != NULL){
        printf("\nEnter a file name of the file to rename, between 1-99 characters\n");
        char oldFile[99];
        int quit = 0;
        char * path = malloc(sizeof(char) * 300);
        char * newPath;
        while(quit != 3){
            printf("> ");
            scanf("%s", oldFile);
            int * dups = search(oldFile, tree, 0);
            if(*dups == 1){
                searchPath(oldFile, tree->root, path, 0);
                free(dups);
                break;
            }
            else if(*dups > 0){
                dups = search(oldFile, tree, 1);
                printf("There is more than one file named: %s. Not sure which to delete\nENTER a more specific file path(choose from above)\n", oldFile);
                quit += 1;
                free(dups);
            }
            else{
                printf("File: %s was not found! Try again\n", oldFile);
                quit += 1;
                free(dups);
            }
            if(quit == 3){
                printf("You do not know what file you want, try again when you do\n");
            }
        }
        char newFile[99];
        quit = 0;
        printf("\nEnter the new file name, between 1-99 characters\n");
        while(quit != 3){
            printf("> ");
            scanf("%s", newFile);
            newPath = replaceStr(path, oldFile, newFile);
            int * dups = search(newPath, tree, 0);
            if(*dups == 0){
                free(dups);
                int ret = rename(path, newPath);
                if(ret == 0){
                    printf("File renamed successfully\n");
                    File * toDie = createEntry(path);
                    File * add = createEntry(newPath);
                    removeFromTree(tree, toDie);
                    addToTree(tree, add);
                    destroyFile(toDie);
                }
                else {
                    printf("Error: unable to rename the file\n");
                }
                break;
            }
            else if(*dups > 0){
                dups = search(newFile, tree, 1);
                printf("There is already a file named: %s. Cannot rename\nENTER a different file name\n", newPath);
                quit += 1;
                free(dups);
                if(quit == 3){
                    printf("You do not know what file you want, try again when you do\n");
                }
                continue;
            }
        }
        free(path);
        free(newPath);
    }
}

void moveFile(Tree * tree){
    if(tree != NULL){
        printf("\nEnter the file name of the file to move, between 1-99 characters\n");
        char moveFile[99];
        int quit = 0;
        char * path = malloc(sizeof(char) * 300);
        while(quit != 3){
            printf("> ");
            scanf("%s", moveFile);
            int * dups = search(moveFile, tree, 0);
            if(*dups == 1){
                searchPath(moveFile, tree->root, path, 0);
                free(dups);
                break;
            }
            else if(*dups > 0){
                dups = search(moveFile, tree, 1);
                printf("There is more than one file named: %s. Not sure which to move\nENTER a more specific file path(choose from above)\n", moveFile);
                quit += 1;
                free(dups);
            }
            else{
                printf("File: %s was not found! Try again\n", moveFile);
                quit += 1;
                free(dups);
            }
            if(quit == 3){
                printf("You do not know what file you want, try again when you do\n");
                return; 
            }
        }
        char newDir[150];
        quit = 0;
        printf("\nEnter the directory to which the file should be moved, between 1-150 characters\n");
        char * dirPath = malloc(sizeof(char) * 300);
        while(quit != 3){
            printf("> ");
            scanf("%s", newDir);
            strcpy(dirPath, "..");
            searchPath(newDir, tree->root, dirPath, 1);
            if(strcmp(dirPath, "..") == 0){
                printf("Directory not found\n");
                quit++;
            }
            else{
                if(checkIfDir(dirPath, newDir) == 1){
                    strncat(dirPath, "/", 1);
                    strncat(dirPath, moveFile, strlen(moveFile));

                    int ret = rename(path, dirPath);
                    if(ret == 0){
                        printf("File moved successfully\n");
                        File * toDie = createEntry(path);
                        File * add = createEntry(dirPath);
                        removeFromTree(tree, toDie);
                        addToTree(tree, add);
                        destroyFile(toDie);
                    }
                    else {
                        printf("Error: unable to move the file\n");
                    }
                    break;
                }
                else{
                    printf("%s is not a directory! Try again\n", dirPath);
                    quit++;
                }
            }
            if(quit == 3){
                printf("You do not know what directory to move file to, try again when you do\n");
            }
        }
        free(dirPath);
        free(path);
    }
}

char * replaceStr(char * str, char * orig, char * rep){
    char * buffer = malloc(sizeof(char) * 300);
    char *p;

    if(!(p = strstr(str, orig))){
        strcpy(buffer, str);
        return buffer;
    }
        

    strncpy(buffer, str, p-str); 
    buffer[p-str] = '\0';

    sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

    return buffer;
}

void searchPath(char * data, TreeNode * root, char * path, int dir){
    if(root == NULL){
        return;
    }
    if(strstr( ((File *)root->data)->name, data)){
        if(checkIfDir(((File *)root->data)->name, data) == 1 && dir == 1){
            strcpy(path, ((File *)root->data)->name);
            return;
        }
        else{
            strcpy(path, ((File *)root->data)->name);
        }
    }
    searchPath(data, root->left, path, dir);
    searchPath(data, root->right, path, dir);
}

