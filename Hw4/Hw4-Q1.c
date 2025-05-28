#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word; // Store the words.
    int count; // Store the word counts.
} wordfreq;

wordfreq *wordarray = NULL;
int wordcount = 0;

void processfile(FILE *file);
char* cleanword(char *word);
void addword(char *word);
void displayresult();
void wordsort();
void countsort();
void cleanmemory();

int main() {
    printf("Reading text.txt in current directory.\n\n");

    FILE *file = fopen("text.txt", "r"); 
    if (file == NULL) { // Returns an error if the file doesnt exist.
        perror("File doesn't exist, exiting program.");
        return 0;
    }

    processfile(file);
    fclose(file);

    displayresult();
    cleanmemory();

    return 0;
}

void processfile(FILE *file) { // Honestly probably could just write this in main or integrate the rest of it here.
    char wordtemp[100]; // Not really necessary, but we set the buffer size to 100 to prevent overflow.
    while (fscanf(file, "%s", wordtemp) == 1) { // As long as a viable string exists we write it to wordtemp.
        addword(cleanword(wordtemp)); // We pass the cleaned word *pointer* to addword.
    }
}

char* cleanword(char *word) { // Make sure its a pointer as addword looks for one, also I dunno how to pass a string to a function.
    int j = 0;
    for(int i = 0; i < strlen(word); i++) {
        if(isalnum(word[i])) {
            word[j++] = tolower(word[i]); // Increase j *after* you use it, not before.
        }
    }
    word[j] = '\0'; // Null terminate.

    return word;
}

void addword(char *word) {
    if(strlen(word) == 0) { // If the word is "empty" (basically just spaces or whatever) end the function.
        return;
    }

    for(int i = 0; i < wordcount; i++) { 
        if(strcmp(wordarray[i].word, word) == 0) { // If the word is equal to a word we already store, increase count by 1, and end function.
            wordarray[i].count++;
            return;
        }
    }

    wordarray = realloc(wordarray, (wordcount + 1) * sizeof(wordfreq)); // We just increase the size of wordarray by enough to store one more wordfreq structure.
    if(wordarray == NULL) {
        perror("Realloc failed, exiting program.");
        exit(EXIT_FAILURE); // return would only exit the function so we use exit to terminate the script.
    }
   
    wordarray[wordcount].word = malloc(strlen(word) + 1); // We allocate enough memory to store every letter and a null terminator.
    if(wordarray[wordcount].word == NULL) {
        perror("Malloc failed, exiting program.");
        exit(EXIT_FAILURE);
    }

    strcpy(wordarray[wordcount].word, word); // Copy word into the array. I think this null terminates the string too?
    wordarray[wordcount].count = 1; // Set the count to 1.
    wordcount++; // Increase the wordcount variable so that we can assign another word next time.
}

void displayresult() {
    char sorttype;

    do {
        printf("Select sort type (a for alphabetical, c for by count): ");
        scanf(" %c", &sorttype);
        printf("\n");
    } 
    while(sorttype != 'a' && sorttype != 'c'); // Continue until you get either a or b.
    
    if(sorttype == 'a') {
        wordsort();
        printf("Word Frequency (alphabetically):\n");
    }
    else{
        countsort();
        printf("Word Frequency (by count):\n");
    }

    for (int i = 0; i < wordcount; i++) { // Print every array in sorted order.
        printf("%s: %d\n", wordarray[i].word, wordarray[i].count);
    }
}

void wordsort() { // Bubble sort using the word strings.
    for (int i = 0; i < wordcount - 1; i++) {
        for (int j = 0; j < wordcount - i - 1; j++) {
            if(strcmp(wordarray[j].word, wordarray[j + 1].word) > 0) {
                char *tempword = wordarray[j].word;
                int tempcount = wordarray[j].count;
                
                wordarray[j].word = wordarray[j + 1].word;
                wordarray[j].count= wordarray[j + 1].count;
                
                wordarray[j + 1].word = tempword;
                wordarray[j + 1].count= tempcount;
            }
        }
    }
}

void countsort() { // Bubble sort using the value of the count arrays.
    for (int i = 0; i < wordcount - 1; i++) {
        for (int j = 0; j < wordcount - i - 1; j++) {
            if(wordarray[j].count < wordarray[j + 1].count) {
                char *tempword = wordarray[j].word;
                int tempcount = wordarray[j].count;
                
                wordarray[j].word = wordarray[j + 1].word;
                wordarray[j].count= wordarray[j + 1].count;
                
                wordarray[j + 1].word = tempword;
                wordarray[j + 1].count= tempcount;
            }
        }
    }
}

void cleanmemory() {
    for (int i = 0; i < wordcount; i++) {
        free(wordarray[i].word); // Free every pointer to a word.
    }
    free(wordarray); // Free the array itself.
}
