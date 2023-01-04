#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "validate.h"
#include "config.h"

int main(int argc, char *argv[]) {
    // validate arguments
    if (validateArgumentCount(argc)) return 1;

    if (validateArguments(argv)) return 1;

    // if correct save values
    conf config = {(strcmp(argv[1], "linenums") == 0) ? 1 : 0, atoi(argv[2])};



    return 0;
}