#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int lineNumbering = 0;
    if (argc != 3) {
        printf("\nUsage:\n\trev [SHOW LINE NUMBERS] [MAX LINE LENGTH] files...\n\n");
        return 1;
    }

    if (strcmp(argv[1], "linenums") == 0) lineNumbering = 1;
    else if (strcmp(argv[1], "nolinenums") == 0);
    else {
        printf("First parameter should be either \"linenums\" or \"nolinenums\"\n");
        return 1;
    }

    if (lineNumbering) printf("Line numbering is on.\n");
    else printf("Line numbering is off.\n");

    return 0;
}