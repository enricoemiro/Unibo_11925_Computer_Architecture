#include "lib/symbol_table.h"

void print(symbol_table_t *st)
{
    if (st == NULL)
        return;

    int counter = 0;
    while (st != NULL)
    {
        printf("%s %d %s\n", st->name, st->dec, st->value);
        st = st->next;
        counter++;
    }
    printf("Size: %d\n", counter);
}

symbol_table_t *get_symbol_by_name(symbol_table_t **st, char *name)
{
    symbol_table_t *tmp = *st;

    while (tmp != NULL)
    {
        if (strlen(tmp->name) == strlen(name) && strncmp(tmp->name, name, strlen(tmp->name)) == 0)
            return tmp;

        tmp = tmp->next;
    }

    return NULL;
}

symbol_table_t *create_new_symbol(int dec, char *name)
{
    symbol_table_t *new_symbol = malloc(sizeof(symbol_table_t));
    new_symbol->dec = dec;
    new_symbol->name = duplicate_string(name);
    new_symbol->value = convert_dec_to_bin(new_symbol->dec);
    new_symbol->next = NULL;

    return new_symbol;
}

void initialize_with_predefined_symbols(symbol_table_t **st)
{
    char *name = malloc(7 * sizeof(name));
    char *dec = malloc(3 * sizeof(dec));

    for (int i = 0; predefined_symbols_arr[i] != 0; ++i)
    {
        int index_equal = index_of(predefined_symbols_arr[i], '=');
        copy_from_to(name, (char *)predefined_symbols_arr[i], 0, index_equal - 1);
        copy_from_to(dec, (char *)predefined_symbols_arr[i], index_equal, strlen(predefined_symbols_arr[i]));
        prepend(st, string_to_int(dec), name);
        reset_string(name);
        reset_string(dec);
    }

    free(name);
    free(dec);
}

void prepend(symbol_table_t **st, int dec, char *name)
{
    symbol_table_t *new_symbol = create_new_symbol(dec, name);

    if (*st == NULL)
    {
        *st = new_symbol;
        return;
    }

    new_symbol->next = *st;
    *st = new_symbol;
}

void free_symbol_table(symbol_table_t *st)
{
    symbol_table_t *tmp = NULL;
    symbol_table_t *symbol = st;

    while (symbol != NULL)
    {
        tmp = symbol;
        symbol = symbol->next;
        free(tmp->name);
        free(tmp->value);
        free(tmp);
    }

    st = NULL;
}