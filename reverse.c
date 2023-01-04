#include <string.h>
#include <stdlib.h>

void myReverse(char chars[]) {
    int length = strlen(chars);
    char help;
    for (int i = 0; i < length / 2; i++)
    {
        help = chars[i];
        chars[i] = chars[length - 1 - i];
        chars[length - 1 - i] = help;
    }
}

void reverseLines(char **lines, int length, int lineLength) {
    char *help = malloc(lineLength * sizeof(char));
    for (int i = 0; i < length / 2; i++)
    {
        strcpy(help, lines[i]);
        strcpy(lines[i], lines[length - 1 - i]);
        strcpy(lines[length - 1 - i], help);
    }
    free(help);
}
