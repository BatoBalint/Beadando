#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

int myRead(char ***lines, FILE *reader, conf config, int mallocSize);

// easier to write error with this
int mallocError() {
    fprintf(stderr, "Memory allocation failed!");
    return -1;
}

int getInput(char ***lines, int argc, char *argv[], conf config, int mallocSize) {
    FILE *reader;

    for (int i = 0; i < mallocSize; i++) {
        lines[0][i] = malloc(config.maxCharCount);
        if (lines[0][i] == NULL) return mallocError();
    } 

    if (argc == 3) {                    // read from console then exit with allocated memory size
        reader = stdin;
        return myRead(lines, reader, config, mallocSize);
    }

    for (int i = 3; i < argc; i++)      // read from files then exit with allocated memory size
    {
        reader = fopen(argv[i], "r");
        if (reader == NULL) fprintf(stderr, "Could not open the file: %s\n", argv[i]);
        else {
            mallocSize = myRead(lines, reader, config, mallocSize);
        }
        fclose(reader);
    }
    return mallocSize;
}

int myRead(char ***lines, FILE *reader, conf config, int mallocSize) {
    int ch;                // temporary storage
    int readerIndex = 0;
    if (mallocSize != 8) while (lines[0][readerIndex][0] != -1) readerIndex++;        // when reading from file finds the last index

    char* buffer = malloc(config.maxCharCount * sizeof(char));
    if (buffer == NULL) return mallocError();
    
    while (fgets(buffer, config.maxCharCount, reader)) {
        if (readerIndex == mallocSize - 1) {                // memory alloc
            lines[0] = realloc(lines[0], mallocSize * 2 * sizeof(char*));
            if (lines[0] == NULL) return mallocError();

            for (int i = mallocSize; i < mallocSize * 2; i++)
            {
                lines[0][i] = malloc(config.maxCharCount * sizeof(char));
                if (lines[0][i] == NULL) return mallocError();
            }

            mallocSize *= 2;
        }

        if (!strrchr(buffer, '\n')) while ((ch = fgetc(reader)) != '\n' && ch != EOF);      // clears input buffer if input was more than maxChar
        else buffer[strlen(buffer) - 1] = 0;
        if (buffer[strlen(buffer) - 1] == 13) buffer[strlen(buffer) - 1] = 0;               // clears a character which returns to the start of the same line
        strcpy(lines[0][readerIndex], buffer);

        readerIndex++;
    }
    
    
    char end[1] = { (char) -1 };            // lazy way to find last active index anywhere
    strcpy(lines[0][readerIndex], end); 
    
    free(buffer);

    return mallocSize;
}