#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>

#include "helpers.h"

#define C_ARITHMETIC 0
#define C_PUSH 1
#define C_POP 2
#define C_LABEL 3
#define C_GOTO 4
#define C_IF 5
#define C_FUNCTION 6
#define C_RETURN 7
#define C_CALL 8

// Returns the type of the current command.
// If the command is not valid it returns -1.
int command_type(char *command);

// Returns the first argument of the current command.
char *arg1(char *command);

// Returns the second argument of the current command.
char *arg2(char *command);

#endif
