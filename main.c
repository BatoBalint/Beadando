#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "validate.h"
#include "config.h"
#include "reverse.h"
#include "input.h"

void test();

int main(int argc, char *argv[]) {
    // test();
    // return 0;

    // validate arguments
    if (validateArgumentCount(argc)) return 1;

    if (validateArguments(argv)) return 1;

    // if correct save values
    conf config = {(strcmp(argv[1], "linenums") == 0) ? 1 : 0, atoi(argv[2])};

    char ***lines = malloc(sizeof(char**));
    lines[0] = malloc(8 * sizeof(char*));
    if (lines == NULL) {
        fprintf(stderr, "Malloc error.");
        return 1;
    }

    int linesCount = getInput(lines, argc, argv, config, 8);

    int dataCount = 0;
    while(lines[0][dataCount][0] != -1) {
        dataCount++;
    }

    for (int i = 0; i < dataCount; i++)
    {
        printf("%s\n", lines[0][i]);
    }
    

    for (int i = 0; i < linesCount; i++) free(lines[0][i]);
    
    free(lines[0]);
    free(lines);

    return 0;
}

void test() {
    printf("%ld\n", sizeof(char***));
}
