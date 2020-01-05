# histogram-histograph

To run program:

```
$ gcc -o histogram histogram.c
$ ./histogram <filename>
```
or
```
$ make
$ ./histogram <filename>
```

If you have docker available:

```
$ docker build -t histogram:v1
$ docker run -it histogram:v1
```
or if you want to specify a different file in the same directory
```
$ docker run -it histogram:v1 ./histogram <filename>
```

alternatively if you want to run it but don't want to change default input file
```
$ docker-compose up
```

Functions:
```
void countWordsInFile(char fileName[]);
```
This function is the main driver function, it will take in a filename and parse the file line by line

```
void getWordFromLine(char line[], int lengthOfLine);
```
After the driver function takes in the line, this function will parse the line and get words that are whitespace delimited including tabs

```
void validWord(char word[], int lengthOfWord);
```
After the parse the word from the line, this function will determine if the word is valid i.e. not null terminated or newline

int checkWordLL(char word[]);

void insertIntoLL(char word[], int lengthOfWord);

void printLL();

void printOccurence(int occurence);

void sortLL();

void outputContentsToFile();

void printToFile(FILE *pointerToFile);

void printOccurenceToFile(int occurence, FILE *pointerToFile);


