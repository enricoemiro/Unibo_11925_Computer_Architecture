#include <stdio.h>

#include "src/code_writer.h"
#include "src/helpers.h"
#include "src/parser.h"

int main(int argc, char **argv) {
  FILE *fin;
  FILE *fout;
  char *file_asm;
  char buffer[512];

  // No arguments
  EXIT_IF_TRUE(argc <= 1, "No file passed as an argument\n");

  // Wrong extension
  EXIT_IF_TRUE(!has_extension(argv[1], "vm"), "The file has wrong extension\n");

  // Check if file exists
  EXIT_IF_TRUE((fin = fopen(argv[1], "r")) == NULL, "File not found\n");

  // Replace .vm with .asm
  fout = fopen(file_asm = replace_extension(argv[1], "asm"), "w");

  // Set the filename
  filename = set_filename(file_asm);

  // Begin the translation
  write_init(fout);

  while (!feof(fin) && fgets(buffer, sizeof(buffer), fin)) {
    char *command = trim(uncomment(&buffer[0]));

    if (strlen(command) != 0) {
      int c_type = command_type(command);

      EXIT_IF_TRUE(c_type == -1, "Invalid command!\n");

      char *a1 = arg1(command);
      char *a2 = arg2(command);

      if (c_type == C_ARITHMETIC) write_arithmetic(fout, command);
      if (c_type == C_PUSH) write_push(fout, a1, a2);
      if (c_type == C_POP) write_pop(fout, a1, a2);
      if (c_type == C_LABEL) write_label(fout, a1);
      if (c_type == C_GOTO) write_goto(fout, a1);
      if (c_type == C_IF) write_if_goto(fout, a1);
      if (c_type == C_FUNCTION) write_function(fout, a1, a2);
      if (c_type == C_RETURN) write_return(fout);
      if (c_type == C_CALL) write_call(fout, a1, a2);

      free(a1);
      free(a2);
    }
  }

  // Free the memory
  fclose(fin);
  fclose(fout);
  free(file_asm);
  free(filename);

  return 0;
}
