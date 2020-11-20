#include "lib/assembler.h"

void code_A_instruction(symbol_table_t **st, char *string)
{
    symbol_table_t *symbol = get_symbol_by_name(st, string);
    if (symbol != NULL)
    {
        reset_string(string);
        copy_from_to(string, symbol->value, 0, strlen(symbol->value));
        return;
    }

    int dec = string_to_int(string);
    if (dec < 0 && dec > 24576)
        return;
    char *tmp = convert_dec_to_bin(dec);
    reset_string(string);
    copy_from_to(string, tmp, 0, strlen(tmp));
    free(tmp);
}

void code_C_instruction(char *string)
{
    char *dest = malloc(9 * sizeof(dest));
    char *comp = malloc(12 * sizeof(comp));
    char *jump = malloc(9 * sizeof(jump));

    // Find index of equal and semicolon characters
    int index_equal = index_of(string, '=');
    int index_sem = index_of(string, ';');

    // DEST = COMP ; JUMP
    if (index_equal != -1 && index_sem != -1)
    {
        copy_from_to(dest, string, 0, index_equal - 1);
        copy_from_to(comp, string, index_equal, index_sem - 1);
        copy_from_to(jump, string, index_sem, strlen(string));
    }

    // COMP; JMP
    if (index_equal == -1 && index_sem != -1)
    {
        strncpy(dest, "null", 5);
        copy_from_to(comp, string, 0, index_sem - 1);
        copy_from_to(jump, string, index_sem, strlen(string));
    }

    // DEST = COMP
    if (index_equal != -1 && index_sem == -1)
    {
        copy_from_to(dest, string, 0, index_equal - 1);
        copy_from_to(comp, string, index_equal, strlen(string));
        strncpy(jump, "null", 5);
    }

    // Encodes the instruction in binary
    get_binary_from_array(dest, dest_arr);
    get_binary_from_array(comp, comp_arr);
    get_binary_from_array(jump, jump_arr);

    // Concatenate
    reset_string(string);
    strncat(string, "111", 4);
    strncat(string, comp, strlen(comp));
    strncat(string, dest, strlen(dest));
    strncat(string, jump, strlen(jump));

    // Free the memory
    free(dest);
    free(comp);
    free(jump);
}

void first_pass(symbol_table_t **st, FILE *fin, char buffer[BUFFER_SIZE])
{
    char *line_ptr;
    int line_counter = 0;

    while (!feof(fin) && fgets(buffer, BUFFER_SIZE, fin) != NULL)
    {
        line_ptr = &buffer[0];
        line_ptr = trim(uncomment(line_ptr));

        if (strlen(line_ptr) != 0)
        {
            if (is_label(line_ptr))
            {
                line_ptr = line_ptr + 1;               // remove left bracket
                line_ptr[strlen(line_ptr) - 1] = '\0'; // remove right bracket

                if (get_symbol_by_name(st, line_ptr) == NULL)
                    prepend(st, line_counter, line_ptr);
            }
            else
            {
                line_counter++;
            }
        }

        reset_string(buffer);
    }

    fclose(fin);
}

void second_pass(symbol_table_t **st, FILE *fin, FILE *fout, char buffer[BUFFER_SIZE])
{
    char *line_ptr;
    int line_counter = 0;
    int register_counter = 16;

    while (!feof(fin) && fgets(buffer, BUFFER_SIZE, fin) != NULL)
    {
        line_ptr = &buffer[0];
        line_ptr = trim(uncomment(line_ptr));

        if (strlen(line_ptr) != 0 && !is_label(line_ptr))
        {
            if (is_A_instruction(line_ptr))
            {
                if (is_variable(line_ptr))
                {
                    line_ptr = line_ptr + 1;

                    if (get_symbol_by_name(st, line_ptr) == NULL)
                    {
                        prepend(st, register_counter, line_ptr);
                        register_counter++;
                    }
                }
                else
                {
                    line_ptr = line_ptr + 1;
                }

                code_A_instruction(st, line_ptr);
            }
            else if (is_C_instruction(line_ptr))
            {
                code_C_instruction(line_ptr);
            }
            else
            {
                printf("Invalid instruction: \"%s\" found at line %d\n", line_ptr, line_counter);
                exit(1);
            }

            fprintf(fout, "%s\n", line_ptr);
            line_counter++;
        }

        reset_string(buffer);
    }

    fclose(fin);
    fclose(fout);
}