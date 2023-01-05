#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "validate.h"
#include "config.h"
#include "reverse.h"
#include "input.h"

int main(int argc, char *argv[]) {
    // validate arguments
    if (validateArgumentCount(argc)) return 1;

    if (validateArguments(argv)) return 1;

    // if correct save values
    conf config = {(strcmp(argv[1], "linenums") == 0) ? 1 : 0, atoi(argv[2]) + 1};      // + 1 so it can store '\0'

    char ***lines = malloc(sizeof(char**));     // 3 levels because it wouldn't let me free otherwise
    if (lines == NULL) {
        fprintf(stderr, "Memory allocation failed!");
        return 1;
    }
    lines[0] = malloc(8 * sizeof(char*));
    for (int i = 0; i < 8; i++)
    {
        if (lines == NULL) {
            fprintf(stderr, "Memory allocation failed!");
            return 1;
        }
    }

    int linesCount = getInput(lines, argc, argv, config, 8);        // read data and store it in lines

    if (linesCount == -1) return 1;                                 // -1 indicates malloc error

    int dataCount = 0;                                              // find real end of array
    while(lines[0][dataCount][0] != -1) {
        dataCount++;
    }
    for (int i = dataCount; i < linesCount; i++) free(lines[0][i]); // shrink allocated memory
    lines[0] = realloc(lines[0], dataCount * sizeof(char*));

    for (int i = dataCount - 1; i >= 0; i--)                        // write to console
    {
        if (config.linenums) printf("%d ", i + 1);
        myReverse(lines[0][i]);
        printf("%s\n", lines[0][i]);
    }

    for (int i = 0; i < dataCount; i++) free(lines[0][i]);          // free alocated memory
    free(lines[0]);
    free(lines);

    return 0;
}
