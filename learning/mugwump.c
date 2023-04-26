#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

void showBoard(int x, int y)
{
    int i,j;        //Initialize for loop variables

    printf("\n  0  1  2  3  4  5  6  7  8  9\n");     //print x-axis

    //Print the board, and user guess
    for (j=0; j<10; j=j+1) {
        //Prints y-axis
        printf("%d",j);

        //Print '.'s and user guess
        for (i=0; i<10; i=i+1) {
            //Find users guess and print 'W' at that cooridinate
            if(j == y && i == x){
                printf(" W ");
            }

            //Otherwise print '.'
            else{
                printf(" . ");
            }
        }
        //Next line after ten dots have been printed
        printf("\n");
    }
}

int main(void)
{

    //Initialize variables
    int quit,guesses = 1;           //for do loop
    float mugX,mugY = rand()% 10;   //that calculate mugwumps position
    float toMugwump,userX,userY;    //for distance to Mungwump and the users guess
    char ans;                       //for answer to playing again

    //Game loop
    do{

        if(guesses == 1){
            mugX = rand()% 10;
            mugY = rand()% 10;
            printf("What is your guess (x y)?");
            scanf("%f %f", &userX, &userY);
        }

        if (mugX == userX && mugY == userY){
            printf("\nYou found the mungWump! In only %d guesses!!\n", guesses);
            quit = 1;
        }

        else{
            toMugwump = sqrt(((mugX-userX)*(mugX-userX)) + ((mugY-userY)*(mugY-userY)))  ;
            printf("You are %0.01f units from the Mungwump.\n",toMugwump);
            showBoard(userX,userY);

            if (guesses == 10){
		printf("guess = 10");
                printf("The mungwump was at %f %f\n", mugX,mugY);
            }

            else{
                guesses += 1;
		printf("Turn number %d\n",guesses);
           	printf("What is your guess (x y)?");
            	scanf("%f %f", &userX, &userY);
	    }
        }

        if (quit == 1 || guesses > 10){
            printf("Do you want to play again (y/n): ");
            scanf("%c", &ans);

            if(tolower(ans) == 'y'){
                printf("\nHope you find the mungwump ;)\n");
                guesses = 0;
                quit = 0;
            }
            else if(tolower(ans) == 'n'){
                printf("\nGame Over");
                quit = 1;
            }
            else{
                printf("\nYou didn't follow the rules. Bye Bye!");
                quit = 1;
            }
        }
    }while (guesses <= 10 && quit==0);

return 0;
}

