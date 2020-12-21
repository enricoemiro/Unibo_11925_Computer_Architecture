#ifndef HELPERS_H
#define HELPERS_H
#include "constant.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int has_extension(const char *file, const char *ext);
char *get_extension(const char *file);
int string_to_int(char *string);
int is_space(const char ch);
int is_alpha(const char ch);
int last_index_of(const char *string, const char ch);
int index_of(const char *string, const char ch);
void reset_string(char *string);
void get_binary_from_array(char *string, const char *arr[]);
void copy_from_to(char *dst, char *src, int from, int to);
char *duplicate_string(char *src);
char *convert_dec_to_bin(int dec);
char *uncomment(char *string);
char *ltrim(char *string);
char *rtrim(char *string);
char *trim(char *string);
int is_label(char *string);
int is_variable(char *string);
int is_A_instruction(char *string);
int is_C_instruction(char *string);

#endif