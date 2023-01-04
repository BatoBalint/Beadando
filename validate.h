#ifndef VALIDATE_H
    #define VALIDATE_H

    #include "validate.c"

    // Validates the arguments and returns 0 if correct, 1 if incorrect
    int validateArgumentCount(int argc);
    int validateArguments(char *argv[]);

#endif // VALIDATE_H