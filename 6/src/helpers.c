#include "helpers.h"

int is_space(char ch) {
  return ch == ' ' ||
         ch == '\n' ||
         ch == '\t' ||
         ch == '\v' ||
         ch == '\f' ||
         ch == '\r';
}

int is_digit(char ch) {
  return ch >= '0' && ch <= '9';
}

int index_of(const char *string, const char ch) {
  for (int i = 0; string[i] != '\0'; ++i)
    if (string[i] == ch) return i;

  return -1;
}

int last_index_of(const char *string, const char ch) {
  int index = -1;

  for (int i = 0; string[i] != '\0'; ++i)
    if (string[i] == ch) index = i;

  return index;
}

int has_extension(const char *file, const char *ext) {
  int find_dot = last_index_of(file, '.');

  // No extension found
  if (find_dot == -1) return 0;

  // Get file extension
  const char *file_ext = file + find_dot + 1;

  return strcmp(file_ext, ext) == 0;
}

char *replace_extension(char *file, const char *ext) {
  int find_dot = last_index_of(file, '.');
  if (find_dot == -1) return NULL;

  // Truncate the file
  file[find_dot + 1] = '\0';
  char *new_file = malloc_or_die(strlen(file) + strlen(ext) + 1);

  // Concatenate "file." + "ext"
  strcat(new_file, file);
  strcat(new_file, ext);

  return new_file;
}

char *uncomment(char *string) {
  for (int i = 0; string[i] != '\0'; ++i)
    if (string[i] == '/' && string[i + 1] == '/')
      string[i] = '\0';

  return string;
}

char *replace_multiples_spaces(char *string) {
  char *dest = string;
  char *start = dest;

  while (*string != '\0') {
    // Loop while the current and the next character are spaces
    while (*string == ' ' && *(string + 1) == ' ')
      string++;

    // Copy into the destination
    *dest++ = *string++;
  }

  *dest = '\0';

  return start;
}

char *ltrim(char *string) {
  while (is_space(*string) && strlen(string) != 0) *++string;

  return string;
}

char *rtrim(char *string) {
  if (strlen(string) == 0) return string;

  char *back = string + strlen(string) - 1;

  while (is_space(*back)) *--back;
  *(++back) = '\0';

  return string;
}

char *trim(char *string) {
  return replace_multiples_spaces(rtrim(ltrim(string)));
}

char *to_uppercase(char *string) {
  for (int i = 0; string[i] != '\0'; ++i)
    if (string[i] >= 'a' && string[i] <= 'z')
      string[i] -= 32;

  return string;
}

char *malloc_or_die(int size) {
  char *buffer = malloc(size * sizeof(*buffer));

  for (int i = 0; i < sizeof(*buffer); ++i) buffer[i] = '\0';

  EXIT_IF_TRUE(buffer == NULL, "Unable to allocate requested memory!\n");

  return buffer;
}
