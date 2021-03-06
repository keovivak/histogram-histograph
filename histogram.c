/*
HEB Dev I Coding Challenge - histogram
    by Kyle Keoviva

*/


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "histogram.h"


struct wordFreq *HEAD = NULL;
int longestWord = 0;


int main (int argc, char *argv[]) {
    if (argc < 2) {
	fprintf(stderr, "Usage: ./histogram <filename>\n");
	return (-1);
    }
	
    countWordsInFile(argv[1]);
    sortLL();
    printLL();
    outputContentsToFile();
    
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
        int i;
        for (i = 0; i<lenOfString; i++) {
            buffer[i] = tolower(buffer[i]);
        }
	getWordFromLine(buffer, lenOfString);
    }

    fclose(fileToRead);
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
        if (word[lengthOfWord-1] == ','
                || word[lengthOfWord-1] == '.') {
            word[lengthOfWord-1] = '\0';
            lengthOfWord--;
        }
        if (lengthOfWord > longestWord) {
            longestWord = lengthOfWord;
        }
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
    tmp->word = malloc(sizeof(char *) * (lengthOfWord*2));
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
	printf("%*s | ", longestWord, traverse->word);
        printOccurence(traverse->freq);
        printf("(%d)\n", traverse->freq);
	traverse = traverse->next;
    }
}

void printOccurence(int occurence) {
    int i;
    for (i = 0; i < occurence; i++) {
        printf("=");
    }
    printf(" ");
}

void sortLL() {
    struct wordFreq *current;
    struct wordFreq *index = NULL;

    char *tmpWord;
    tmpWord = malloc(sizeof(char *));
    int tmpValue;

    current = HEAD->next;
    if (current == NULL) {
        return;
    } else {
        while (current != NULL) {
            index = current->next;

            while (index != NULL) {
                if (current->freq < index->freq) {
                    strcpy(tmpWord, current->word);
                    tmpValue = current->freq;

                    strcpy(current->word, index->word);
                    current->freq = index->freq;

                    strcpy(index->word, tmpWord);
                    index->freq = tmpValue;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

void outputContentsToFile() {
    FILE *fileToWrite;
    char buffer[BUFSIZ];

    fileToWrite = fopen("output.txt", "w+");
    printToFile(fileToWrite);

    fclose(fileToWrite);
}

void printToFile(FILE *pointerToFile) {
    struct wordFreq *traverse;

    traverse = HEAD->next;
    while (traverse != NULL) {
	fprintf(pointerToFile, "%*s | ", longestWord, traverse->word);
        printOccurenceToFile(traverse->freq, pointerToFile);
        fprintf(pointerToFile, "(%d)\n", traverse->freq);
	traverse = traverse->next;
    }
}

void printOccurenceToFile(int occurence, FILE *pointerToFile) {
    int i;
    for (i = 0; i < occurence; i++) {
        fprintf(pointerToFile, "=");
    }
    fprintf(pointerToFile, " ");
}

