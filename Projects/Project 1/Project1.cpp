
// SpellCheck <Project1.cpp>
// EE 312 Project 1 submission by
// Viraj Parikh
// VHP286
// Slip days used: <0>
// Spring 2018

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types
#include <ctype.h> //For isalpha and toupper
#include <string.h> //For string commands

//This functions makes everything into upper case to prevent case issues
char* Case(char Input[]) {
	for (int32_t i = 0; Input[i] !=0 ;i++)
		Input[i] = toupper(Input[i]);
	return Input;
}

//this function calculates the length of the dictionary
int32_t dictionaryFix (char dictionary[]) {
	int32_t len =0;
	for(int32_t i=0;dictionary[i]!=0;i++)
		len++;
	return len;
}

//Checks if the input word is a part (substring) of the dictionary return 1 is spelled right 0 if wrong. The substring has '\n' at each end 
char isSpell(char Word[],char dictionary[]) {
	if (strstr(dictionary,Word) == NULL)
		return 0;
	else 
		return 1;
}

/* The function newWord creates a new string called Word which is initilized to 0 
 * The current word is coppied over from the article into the array Word which is passed 
 * to the function which cheks if the word is a substring of the dictionary
 */

void newWord(char article[], char dictionary[], int32_t length, int32_t end) {
	int32_t start = (end - length); //Determines the start index of the word from the article
	char Word[32] = {'\n'}; //Initilize Word with all 0s and leading \n
	int32_t i = 1; //counter
	for (int32_t j = start+1 ; j <= end; j++) {
		Word[i]=article[j]; //copies into Word
		i++;
	}

	Word[length+1]='\n'; //adds a \n at the end of the function 

	if (isSpell(Word,dictionary)==0) { //calls function isSpell if 0 is returned then the string is not a part of the dictionary
		for (i = 1; i<= length; i++)
			printf("%c",Word[i]);
		printf("\n");
	}
}

void spellCheck(char article[], char dictionary[])
{
	//Fix issue of case by makeing everything same case
	article = Case(article); 
	dictionary = Case(dictionary);
	int32_t sum =0; //Initilize sum to 0 to pass to other support functions
	
	int32_t length_d = dictionaryFix(dictionary)+1; //length of the dictionary +1
	char dictionary_n[length_d]; //creates new dictionary with one element more than the original 
	dictionary_n[0]='\n'; 
	for (int32_t i =1; dictionary[i]!=0; i++) {
		dictionary_n[i]=dictionary[i-1];
	}
	dictionary_n[length_d-1]='\n';
	//the above segment adds a leading \n to the dictionary to prevent the substring from being unable
	//to detect the first word in the dictionary. Dictionary_n is the same as dictionary but has a leading \n to help with the rest of the algorithm 


	for (int32_t i = 1; article[i] !=0 ;i++) { //main loop -> loops job is to seperate words from non words
		if(isalpha(article[i]) && (isalpha(article[i+1]) || isalpha(article[i-1]))) { //this condition code signifies if it meets the definition of a word
			if (i == 1) //accounts for starting at 1 instead of 0
				sum++;
			sum++;
			if (!(isalpha(article[i+1]))) { //signifies end of the word 
				newWord(article,dictionary_n,sum,i);
				sum = 0;
			}
		}
	}
}





