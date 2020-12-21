#ifndef CODE_WRITER_H
#define CODE_WRITER_H

#include <stdio.h>
#include <string.h>

#include "helpers.h"

extern char *filename;
extern int jump_counter;
extern int return_address_counter;

/**
 * Extract from a given path the name of the current VM file.
 */
char *set_filename(char *path);

/**
 * Bootstrap code.
 */
void write_init(FILE *fout);

/**
 * Writes assembly code for the following operations:
 * add, sub, neg, not, gt, lt, eq, and, or
 */
void write_arithmetic(FILE *fout, char *command);

/**
 * push segment index
 * 
 * Push segment[index] to the stack.
 */
void write_push(FILE *fout, char *segment, char *index);

/**
 * pop segment index
 * 
 * The stack’s topmost value is popped and it is pushed in segment[index].
 */
void write_pop(FILE *fout, char *segment, char *index);

/**
 * label label_name
 * 
 * This command labels the current location in the function’s code.
 * The label is an arbitrary string composed of any sequence of letters,
 * digits, underscore (_), dot (.), and colon (:) that does not begin with a digit.
 */
void write_label(FILE *fout, char *label_name);

/**
 * goto label_name
 * 
 * This command effects an unconditional goto operation, causing
 * execution to continue from the location marked by the label.
 */
void write_goto(FILE *fout, char *label_name);

/**
 * if-goto label_name
 * 
 * This command effects a conditional goto operation.
 * The stack’s topmost value is popped; if the value is
 * not zero, execution continues from the location marked 
 * by the label; otherwise, execution continues from the 
 * next command in the program.
 */
void write_if_goto(FILE *fout, char *label_name);

/**
 * call function_name num_args
 * 
 * 1) Push the return address
 * 2) Push the following segments: LCL, ARG, THIS, THAT (the sort is important)
 * 3) Reposition ARG
 * 4) Reposition LCL
 * 5) Transfer the control to the function
 * 6) Declare a label for the return address
 */
void write_call(FILE *fout, char *function_name, char *num_args);

/**
 * function function_name num_args
 * 
 * 1) Declare a label for the function_name
 * 2) Push num_args times 0
 */
void write_function(FILE *fout, char *function_name, char *num_args);

/*
 * return
 * 
 * 1) Store LCL in a general purpose register;
 * 2) Store the return address in a general purpose register;
 * 3) Reposition the return value for the caller;
 * 4) Restore SP, THAT, THIS, ARG, LCL of the caller
 * 5) Goto the return address
 */
void write_return(FILE *fout);

#endif
