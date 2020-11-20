#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "constant.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Symbol_Table
{
    int dec;
    char *name;
    char *value;
    struct Symbol_Table *next;
} symbol_table_t;

void print(symbol_table_t *st);
symbol_table_t *get_symbol_by_name(symbol_table_t **st, char *name);
symbol_table_t *create_new_symbol(int dec, char *name);
void initialize_with_predefined_symbols(symbol_table_t **st);
void prepend(symbol_table_t **st, int dec, char *name);
void free_symbol_table(symbol_table_t *st);

#endif