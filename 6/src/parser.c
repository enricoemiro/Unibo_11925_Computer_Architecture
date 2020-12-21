#include "parser.h"

int command_type(char *command) {
  if (strncmp(command, "add", 3) == 0 ||
      strncmp(command, "sub", 3) == 0 ||
      strncmp(command, "and", 3) == 0 ||
      strncmp(command, "neg", 3) == 0 ||
      strncmp(command, "not", 3) == 0 ||
      strncmp(command, "or", 2) == 0 ||
      strncmp(command, "eq", 2) == 0 ||
      strncmp(command, "gt", 2) == 0 ||
      strncmp(command, "lt", 2) == 0)
    return C_ARITHMETIC;

  if (strncmp(command, "push", 4) == 0) return C_PUSH;
  if (strncmp(command, "pop", 3) == 0) return C_POP;
  if (strncmp(command, "label", 5) == 0) return C_LABEL;
  if (strncmp(command, "goto", 4) == 0) return C_GOTO;
  if (strncmp(command, "if-goto", 7) == 0) return C_IF;
  if (strncmp(command, "function", 8) == 0) return C_FUNCTION;
  if (strncmp(command, "return", 6) == 0) return C_RETURN;
  if (strncmp(command, "call", 4) == 0) return C_CALL;

  return -1;
}

char *arg1(char *command) {
  int idx_first_space = index_of(command, ' ');

  if (idx_first_space == -1) return NULL;

  char *buffer = malloc_or_die(strlen(command) + 1);
  strcat(buffer, command + idx_first_space + 1);

  int idx_last_space = index_of(buffer, ' ');
  if (idx_last_space != -1) buffer[idx_last_space] = '\0';

  return buffer;
}

char *arg2(char *command) {
  int idx_first_space = index_of(command, ' ');
  int idx_last_space = last_index_of(command, ' ');

  if (idx_first_space == -1 ||
      idx_first_space == idx_last_space) return NULL;

  char *buffer = malloc_or_die(strlen(command) + 1);
  strcat(buffer, command + idx_last_space + 1);

  return buffer;
}
