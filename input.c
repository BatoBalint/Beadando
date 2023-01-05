#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

int myRead(char ***lines, FILE *reader, conf config, int mallocSize);

// easier to write error with this
int mallocError() {
    fprintf(stderr, "Malloc error.");
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
    }
    return mallocSize;
}

int myRead(char ***lines, FILE *reader, conf config, int mallocSize) {
    int readPtr = 0;        // current memory index
    if (mallocSize != 8) while (lines[0][readPtr][0] != -1) readPtr++;  // when reading from file finds the real end of the array

    char *buffer = malloc(config.maxCharCount);

    fgets(buffer, config.maxCharCount, reader);
    buffer[strlen(buffer) - 1] = '\0';

    while (!feof(reader)) {
        if (readPtr == mallocSize - 1) {
            lines[0] = realloc(lines[0], mallocSize * 2 * sizeof(char*));
            if (lines == NULL) return mallocError();

            for (int i = mallocSize; i < mallocSize * 2; i++) {
                lines[0][i] = malloc(config.maxCharCount);
                if (lines[0][i] == NULL) return mallocError();
            }

            mallocSize *= 2;
        }

        strcpy(lines[0][readPtr], buffer);          // in this read order, last line ins't duplicated
        fgets(buffer, config.maxCharCount, reader);
        buffer[strlen(buffer) - 1] = '\0';          // remove line break from fgets result
        readPtr++;
    }

    char end[1] = { (char) -1 };        // lazy way to tell the end of the array anywhere
    strcpy(lines[0][readPtr], end);

    free(buffer);

    return mallocSize;
}