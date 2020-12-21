#include "lib/symbol_table.h"
#include "lib/constant.h"
#include "lib/helpers.h"
#include "lib/assembler.h"
#include <stdio.h>
#define RETURN_IF_TRUE(expression, msg) \
    {                                   \
        if (expression)                 \
        {                               \
            printf("%s", msg);          \
            exit(1);                    \
        }                               \
    }

int main(int argcv, char **argv)
{
    FILE *fin;
    FILE *fout;
    char *path;
    char *hack;
    char buffer[BUFFER_SIZE];
    symbol_table_t *st = NULL;

    // Check conditions
    RETURN_IF_TRUE(argcv <= 1, "No file was passed as argument\n");
    RETURN_IF_TRUE(!has_extension(argv[1], "asm"), "Invalid file. Wrong extension\n");
    fin = fopen(argv[1], "r");
    RETURN_IF_TRUE(fin == NULL, "File not found\n");

    // Create hack file
    path = duplicate_string(argv[1]);
    hack = malloc((strlen(path) + 5) * sizeof(hack));
    copy_from_to(hack, path, 0, last_index_of(path, '.'));
    strncat(hack, "hack", 5);

    // Assemble
    initialize_with_predefined_symbols(&st);
    first_pass(&st, fin, buffer);
    fin = fopen(argv[1], "r");
    fout = fopen(hack, "w");
    second_pass(&st, fin, fout, buffer);

    // Free the memory
    free(path);
    free(hack);
    free_symbol_table(st);
    path = NULL;
    hack = NULL;
    st = NULL;

    return 0;
}