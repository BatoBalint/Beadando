#include <string.h>

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
