//This program opens a text file, reads it in and scrambles the letters

#include <stdio.h>			//used for input output
#include <stdlib.h>			//used to generate random numbers
#include <time.h>			//used to generate random numbers with out repeats
#include <string.h>			//used for string liabrary

//Funtion that prompts the user for a file name
void getFileName(char filename[99]){
	//Prompt user to enter filename
	printf("Enter a file name, with .txt between 1-99 characters\n");
	scanf("%s", filename);
}

//This function scrambles words
void scrambleWord (int wordLen, char word[wordLen]){
	int randNum, i, a, subLen, len;			//declare interger variables
	char *pos;								//declares pointer variable
	char temp[wordLen];						//declares temp char array
	char punctuation [] = ".,;:'\"!?()-";	//declares and initalizes punctuation string

	subLen = 0;								//initalizes subLen to zero
	len = wordLen - 1;						//initalizes len to index length of word

	//fills array temp with word, and sets word array to intial values
	for (i = 0; i < (wordLen); i++) {
		temp[i] = word[i];
		word[i] = '*';
	}

	//makes sure teh first letter of the word stays the same
	word[0] = temp[0];

	//checks if the last letter in word is punctuation
	if(strchr(punctuation, temp[len])){
	    //if yes sets fills word at that postion with punctuation
		word[len] = temp[len];
		//ensures that the last letter of the word stays the same
	    word[len - 1] = temp[len - 1];
	    //Incraments subLen
	    subLen++;
    }
    //Otherwise makes sure last letter of word stays the same
    else{
		word[len] = temp[len];
	}

	//Check if apostrophe is in word
	if(strchr(temp, '\'')){
		//Finds postion of apostrophe
		pos = strchr(temp, '\'');
		//Finds interger value of postion of apostrophe
		a = (int)(pos - temp);
		//Puts apostrophe in word
		word[a] = temp[a];
		subLen++;
	}

	//Generate random number between
	randNum = (rand() % (len-1)) + 1;

	//Loop that scrambles word (len-
	for(i=1; i<(len-subLen); ++i){
		//Check if postion to enter scrambled letter is empty
		if(word[randNum] != '*'){
			//Continue to generate random number until position is empty
			while(word[randNum] != '*'){
				randNum = (rand() % (len-1)) +1;
			}
			//fill position
			word[randNum] = temp[i];
		}
		//Otherwise fill postion as is
		else{
			word[randNum] = temp[i];
		}
		//Generate new random number
		randNum = (rand() % (len -1)) +1;
	}
}

//This function process the words in the text file
void processText (int fileLen, char filename[fileLen]){
    int wordLen;					//declare variable for word length
    char c;							//declare char variables to store spaces and newline
    char word[50];					//declare character array for word
    FILE *ifp;						//input file pointer

    //opens the file
    ifp = fopen(filename, "r");

    //Loops that goes through file
    while(fscanf(ifp,"%8s%c",word, &c) != EOF){
    	//Find word length
    	wordLen = strlen(word);

		//If word length is over three scramble word
    	if(wordLen > 3){
        	scrambleWord(wordLen, word);
        }

		//Print word
		printf("%s%c", word, c);
	}
	fclose(ifp);
}


int main ()
{
	char filename[99];				//a character array to store file name

	srand(time(NULL));

	//Calling getFileName function
	getFileName(filename);

	//Call processText function
	processText(strlen(filename), filename);

	return(0);
}
