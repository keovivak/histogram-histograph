/*

Header file to for histgoram HEB coding challenge

*/

// struct def
struct wordFreq {
    char *word;
    int freq;
    struct wordFreq *next;
    struct wordFreq *prev;
};

// Function declarations
void countWordsInFile(char fileName[]);
void getWordFromLine(char line[], int lengthOfLine);
void validWord(char word[], int lengthOfWord);
int checkWordLL(char word[]);
void insertIntoLL(char word[], int lengthOfWord);
void printLL();
void printOccurence(int occurence);
void sortLL();
void outputContentsToFile();
void printToFile(FILE *pointerToFile);
void printOccurenceToFile(int occurence, FILE *pointerToFile);
