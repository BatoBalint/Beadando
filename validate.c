#include <stdio.h>
#include <string.h>

int validateArgumentCount(int argc) {
    // Not enough arguments were passed to the program
    if (argc < 3) {
        fprintf(stderr, "\nUsage:\n\trev [SHOW LINE NUMBERS] [MAX LINE LENGTH] files...\n\n");
        return 1;
    } 
    return 0;
}

int validateArguments(char *argv[]) {
    // The first argument not "linenums" or "nolinenums" 
    if (!(strcmp(argv[1], "linenums") == 0 || strcmp(argv[1], "nolinenums") == 0)) {
        fprintf(stderr, "\tFirst argument should be either \"linenums\" or \"nolinenums\"!\n");
        return 1;
    }

    // The second argument contains non-numeric characters
    int i = 0;
    while (argv[2][i] != 0) {
        if (argv[2][i] - '0' < 0 || argv[2][i] - '0' > 9) {
            fprintf(stderr, "\tThe second argument cannot be converted to integer!\n");
            return 1;
        }
        i++;
    }

    return 0;
}
