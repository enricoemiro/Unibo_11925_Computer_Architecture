#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include "symbol_table.h"
#include "constant.h"
#include "helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void code_A_instruction(symbol_table_t **st, char *string);
void code_C_instruction(char *string);
void first_pass(symbol_table_t **st, FILE *fin, char buffer[BUFFER_SIZE]);
void second_pass(symbol_table_t **st, FILE *fin, FILE *fout, char buffer[BUFFER_SIZE]);

#endif