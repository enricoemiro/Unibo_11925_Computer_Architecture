#include "lib/helpers.h"

int has_extension(const char *file, const char *ext)
{
    char *extension = get_extension(file);

    if (extension == NULL)
        return 0;

    return strncmp(extension, ext, strlen(extension)) == 0 &&
           strlen(extension) == strlen(ext);
}

char *get_extension(const char *file)
{
    char *tmp = (char *)file;
    int index_dot = last_index_of(file, '.');

    if (index_dot == -1)
        return NULL;

    for (int i = 0; i < index_dot && *tmp != '\0'; ++i)
        *tmp++;

    return tmp;
}

int string_to_int(char *string)
{
    int result = 0;

    for (int i = 0; string[i] != '\0'; ++i)
        result = result * 10 + string[i] - '0';

    return result;
}

int is_space(const char ch)
{
    return ch == ' ' ||  // space
           ch == '\n' || // newline
           ch == '\t' || // tab
           ch == '\v' || // vertical tab
           ch == '\f' || // form feed
           ch == '\r';   // carraige return
}

int is_alpha(const char ch)
{
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z');
}

int last_index_of(const char *string, const char ch)
{
    int index = -1;
    char *tmp = (char *)string;

    for (int i = 0; *tmp != '\0'; ++i)
    {
        if (*tmp == ch)
            index = (i + 1);
        tmp++;
    }

    return index;
}

int index_of(const char *string, const char ch)
{
    char *tmp = (char *)string;

    for (int i = 0; *tmp != '\0'; ++i)
    {
        if (*tmp == ch)
            return i + 1;
        tmp++;
    }

    return -1;
}

void reset_string(char *string)
{
    char *tmp = string;

    for (int i = strlen(string); i > 0; --i)
    {
        *tmp = '\0';
        tmp++;
    }
}

void get_binary_from_array(char *string, const char *arr[])
{
    if (arr != dest_arr && arr != comp_arr && arr != jump_arr)
        return;

    for (int i = 0; arr[i] != 0; ++i)
    {
        int index_equal = index_of(arr[i], '=');
        if (strncmp(string, arr[i], strlen(string)) == 0)
        {
            reset_string(string);
            copy_from_to(string, (char *)arr[i], index_equal, strlen(arr[i]));
            return;
        }
    }
}

void copy_from_to(char *dst, char *src, int from, int to)
{
    if (from < 0 || from > to || to > strlen(src))
        return;

    strncpy(dst, src + from, to - from);
    dst[to - from] = '\0';
}

char *duplicate_string(char *src)
{
    char *dst = malloc(strlen(src) + 1);
    copy_from_to(dst, src, 0, strlen(src));
    return dst;
}

char *convert_dec_to_bin(int dec)
{
    char *binary = malloc((NUMBER_OF_BITS + 1) * (sizeof binary));

    for (int i = 0; i < NUMBER_OF_BITS; ++i)
        binary[i] = '0';
    binary[NUMBER_OF_BITS] = '\0';

    for (int i = NUMBER_OF_BITS - 1; i > 0 && dec > 0; --i)
    {
        binary[i] = dec % 2 + '0';
        dec = dec / 2;
    }

    return binary;
}

char *uncomment(char *string)
{
    char *tmp = string;

    while (*tmp != '\0' && *tmp != '/' && *(++tmp) != '/')
        ++tmp;

    *tmp = '\0';

    return string;
}

char *ltrim(char *string)
{
    if (!is_space(*string))
        return string;

    return ltrim(++string);
}

char *rtrim(char *string)
{
    char *tail = string + strlen(string);

    while (is_space(*--tail))
        ;

    *(++tail) = '\0';

    return string;
}

char *trim(char *string)
{
    return rtrim(ltrim(string));
}

int is_label(char *string)
{
    return string[0] == '(' &&
           string[strlen(string) - 1] == ')' &&
           is_alpha(string[1]);
}

int is_variable(char *string)
{
    return string[0] == '@' &&
           is_alpha(string[1]);
}

int is_A_instruction(char *string)
{
    return string[0] == '@';
}

int is_C_instruction(char *string)
{
    char *tmp = string;

    while (*tmp != '\0')
    {
        if (*tmp == '=' || *tmp == ';')
            return 1;
        tmp++;
    }

    return 0;
}