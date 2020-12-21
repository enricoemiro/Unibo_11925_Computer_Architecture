#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_IF_TRUE(expression, msg) \
  {                                   \
    if (expression) {                 \
      printf("%s", msg);              \
      exit(EXIT_FAILURE);             \
    }                                 \
  }

// Check if a given character is a space.
int is_space(char ch);

// Check if a given character is a digit.
int is_digit(char ch);

// Convert a given string to uppercase.
char *to_uppercase(char *string);

// Returns the position of the first occurence of
// a specified character in a string.
int index_of(const char *string, const char ch);

// Returns the position of the last occurence of a
// specified character in a string.
int last_index_of(const char *string, const char ch);

// If returns 1 => the file has the given extension.
// If returns 0 => the file has not the given extension.
int has_extension(const char *file, const char *ext);

// Replace file with a specified extension.
char *replace_extension(char *file, const char *ext);

// Replace multiples spaces with a single space.
char *replace_multiples_spaces(char *string);

// Removes all right spaces from a given string.
char *rtrim(char *string);

// Removes all left spaces from a given string.
char *ltrim(char *string);

// Replace multiples spaces with a single space and
// remove all right and left spaces.
char *trim(char *string);

// Remove all comments from a given string.
char *uncomment(char *string);

// If allocating succedeed return the buffer, exit otherwise.
char *malloc_or_die(int size);

#endif
