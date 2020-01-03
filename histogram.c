/*
Assignment 1 by Kyle Keoviva zdn158
OS cs3733 with Korkmaz Spring 2019

Assignment 1 Independent Study Recitation extension
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>


struct wordFreq {
	char *word;
	int freq;
	struct wordFreq *next;
	struct wordFreq *prev;
};


void countWordsInFile(char fileName[]);
void getWordFromLine(char line[], int lengthOfLine);
void validWord(char word[], int lengthOfWord);
int checkWordLL(char word[]);
void insertIntoLL(char word[], int lengthOfWord);
void printLL();


struct wordFreq *HEAD = NULL;
int wordCount = 0;


int main (int argc, char *argv[]) {
    int i, n, numberOfWordsInFile;

    if (argc < 2) {
	fprintf(stderr, "Usage: ./wordcount <filename>\n");
	return (-1);
    }
	
    countWordsInFile(argv[1]);
    
    return (0);
}

void countWordsInFile(char fileName[]) {
    FILE *fileToRead;
    char buffer[BUFSIZ];

    HEAD = malloc(sizeof(struct wordFreq));

    // Opens file for read
    fileToRead = fopen(fileName, "r");
    if (fileToRead == NULL) {
        fprintf(stderr, "Failed to open file %s\n", fileName);
	exit(0);
    }

    // Parses files to for spaces/tabs/newlines
    while ((fgets(buffer, BUFSIZ, fileToRead)) != NULL) {
	int lenOfString = strlen(buffer);
	getWordFromLine(buffer, lenOfString);
    }

    // Print output and close file
    printf("Child process for %s: number of words is %d\n", fileName, wordCount);
    fclose(fileToRead);
    printLL();

    printf("\n\n");
}

void getWordFromLine(char line[], int lengthOfLine) {
    int i, j;
    char copyLine[BUFSIZ];
    char word[200];
    strcpy(copyLine, line);

    j = 0;
    for (i=0; i<lengthOfLine; i++) {
	if (copyLine[i] == ' ' || copyLine[i] == '\t'
	    || copyLine[i] == '\n') {
	    word[j] = '\0';
	    //printf("length of word is %d\n", j);
	    validWord(word, j);
	    j = 0;
	} else {
	    word[j] = copyLine[i];
	    j++;
	}
    }
}

void validWord(char word[], int lengthOfWord) {
    int verifyWord = -1;
    if (word[0] == '\0') {
	return;
    } else {
	//printf("word is %s, with a length of %d\n", word, lengthOfWord);
	wordCount += 1;
    }

    verifyWord = checkWordLL(word);
    if (verifyWord == 1) {
	insertIntoLL(word, lengthOfWord);
    }
}

int checkWordLL(char word[]) {
    struct wordFreq *tmp;
    int newWord = 1;
    if (HEAD->next == NULL) {
	return (newWord);
    } else {
	tmp = HEAD->next;
	while (tmp != NULL) {
	//printf("word %s vs current word = %s | %d\n", word, tmp->word, tmp->freq);
	    if (strcmp(tmp->word, word) == 0) {
		tmp->freq += 1;
		//printf("WORD MATCHES\n");
		newWord = 0;
		break;
	    }
	    tmp = tmp->next;
	}
    }

    return (newWord);
}

void insertIntoLL(char word[], int lengthOfWord) {
    struct wordFreq *tmp = malloc(sizeof(struct wordFreq));
    tmp->word = malloc(sizeof(char *) * lengthOfWord);
    strcpy(tmp->word, word);
    tmp->freq = 1;
    tmp->next = NULL;
    tmp->prev = NULL;

    if (HEAD->next == NULL) {
	HEAD->next = tmp;
    } else {
	if (strcmp(HEAD->next->word, word) > 0) {
	    tmp->next = HEAD->next;
	    HEAD->next->prev = tmp;
	    HEAD->next = tmp;
        } else {
	    struct wordFreq *traverse;
			
	    for (traverse = HEAD->next; traverse != NULL; traverse = traverse->next) {
	        if (strcmp(word, traverse->word) > 0) {
		    if (traverse->next == NULL) {
			traverse->next = tmp;
			tmp->prev = traverse;
			return;
		    }
	        } else {
		    tmp->next = traverse;
		    tmp->prev = traverse->prev;
		    traverse->prev->next = tmp;
		    traverse->prev = tmp;
		    //break;
		    return;
		}
	    }
        }		
    }
}

void printLL() {
    struct wordFreq *traverse;

    traverse = HEAD->next;
    while (traverse != NULL) {
	printf("'%s' appears %d times\n", traverse->word, traverse->freq);
	traverse = traverse->next;
    }
}

