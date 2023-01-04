#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

int myRead(char ***lines, FILE *reader, conf config, int readPtr, int mallocSize);

int mallocError() {
    fprintf(stderr, "Malloc error.");
    return -1;
}

int getInput(char ***lines, int argc, char *argv[], conf config, int mallocSize) {
    FILE *reader;
    int readPtr = 0;

    for (int i = 0; i < mallocSize; i++) {
        lines[0][i] = malloc(config.maxCharCount);
        if (lines[0][i] == NULL) return mallocError();
    } 

    if (argc == 3) {
        reader = stdin;
        return myRead(lines, reader, config, readPtr, mallocSize);
    }

    for (int i = 3; i < argc; i++)
    {
        reader = fopen(argv[i], "r");
        if (reader == NULL) fprintf(stderr, "Could not open the file: %s", argv[i]);
        else {
            mallocSize = myRead(lines, reader, config, readPtr, mallocSize);
        }
    }
    return mallocSize;
}

int myRead(char ***lines, FILE *reader, conf config, int readPtr, int mallocSize) {
    char *buffer = malloc(config.maxCharCount);

    fgets(buffer, config.maxCharCount, reader);
    buffer[strlen(buffer) - 1] = '\0';
    while (!feof(reader)) {
        if (readPtr == mallocSize - 1) {
            printf("realloc start\n");
            printf("%d\n", mallocSize);
            lines[0] = realloc(lines[0], mallocSize * 2 * sizeof(char*));
            if (lines == NULL) return mallocError();

            for (int i = mallocSize - 1; i < mallocSize * 2; i++) {
                lines[0][i] = malloc(config.maxCharCount);
                if (lines[0][i] == NULL) return mallocError();
            }

            mallocSize *= 2;
            printf("realloc end\n");
        }
        strcpy(lines[0][readPtr], buffer);

        fgets(buffer, config.maxCharCount, reader);
        buffer[strlen(buffer) - 1] = '\0';

        readPtr++;
    }
    char end[1] = { (char) -1 };
    strcpy(lines[0][readPtr], end);
    free(buffer);
    return mallocSize;
}