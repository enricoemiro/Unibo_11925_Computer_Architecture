#include "code_writer.h"

char *filename = NULL;
int jump_counter = 0;
int return_address_counter = 0;

char *set_filename(char *path) {
  int idx_slash = last_index_of(path, '/');

  char *filename = malloc_or_die(strlen(path) + 1);
  strcat(filename, path + (idx_slash != -1 ? idx_slash + 1 : 0));
  filename[last_index_of(filename, '.')] = '\0';

  return filename;
}

void write_init(FILE *fout) {
  fprintf(fout,
#if DEBUG == 1
          "// bootstrap\n"
#endif
          "@256\n"
          "D=A\n"
          "@SP\n"
          "M=D\n");
}

void write_arithmetic(FILE *fout, char *command) {
#if DEBUG == 1
  fprintf(fout, "// %s\n", command);
#endif

  // Binary operators
  if (strcmp(command, "add") == 0 ||
      strcmp(command, "sub") == 0 ||
      strcmp(command, "and") == 0 ||
      strcmp(command, "or") == 0) {
    fprintf(fout,
            "@SP\n"
            "AM=M-1\n"
            "D=M\n"
            "A=A-1\n");

    if (strcmp(command, "add") == 0) fprintf(fout, "M=M+D\n");
    if (strcmp(command, "sub") == 0) fprintf(fout, "M=M-D\n");
    if (strcmp(command, "and") == 0) fprintf(fout, "M=M&D\n");
    if (strcmp(command, "or") == 0) fprintf(fout, "M=M|D\n");
  }

  // Binary boolean operators
  if (strcmp(command, "gt") == 0 ||
      strcmp(command, "lt") == 0 ||
      strcmp(command, "eq") == 0) {
    fprintf(fout,
            "@SP\n"
            "AM=M-1\n"
            "D=M\n"
            "A=A-1\n"
            "D=M-D\n"
            "@IF_TRUE_%d\n"
            "D;J%s\n"
            "@SP\n"
            "A=M-1\n"
            "M=0\n"
            "@CONTINUE_%d\n"
            "0;JMP\n"
            "(IF_TRUE_%d)\n"
            "@SP\n"
            "A=M-1\n"
            "M=-1\n"
            "(CONTINUE_%d)\n",
            jump_counter,
            to_uppercase(command),
            jump_counter,
            jump_counter,
            jump_counter);

    // Update the global jump_counter
    jump_counter++;
  }

  // Unary operators
  if (strcmp(command, "neg") == 0 ||
      strcmp(command, "not") == 0) {
    fprintf(fout,
            "@SP\n"
            "A=M-1\n");

    if (strcmp(command, "neg") == 0) fprintf(fout, "M=-M\n");
    if (strcmp(command, "not") == 0) fprintf(fout, "M=!M\n");
  }
}

void write_push(FILE *fout, char *segment, char *index) {
#if DEBUG == 1
  fprintf(fout, "// push %s %s\n", segment, index);
#endif

  if (strcmp(segment, "static") == 0)
    fprintf(fout, "@%s.%s\n", filename, index);
  else
    fprintf(fout, "@%s\n", index);

  if (strcmp(segment, "constant") == 0)
    fprintf(fout,
            "D=A\n"
            "@SP\n"
            "A=M\n"
            "M=D\n"
            "@SP\n"
            "M=M+1\n");

  if (strcmp(segment, "local") == 0 ||
      strcmp(segment, "argument") == 0) {
    fprintf(fout, "D=A\n");

    if (strcmp(segment, "local") == 0) fprintf(fout, "@LCL\n");
    if (strcmp(segment, "argument") == 0) fprintf(fout, "@ARG\n");

    fprintf(fout,
            "A=D+M\n"
            "D=M\n"
            "@SP\n"
            "A=M\n"
            "M=D\n"
            "@SP\n"
            "M=M+1\n");
  }

  if (strcmp(segment, "static") == 0)
    fprintf(fout,
            "D=M\n"
            "@SP\n"
            "A=M\n"
            "M=D\n"
            "@SP\n"
            "M=M+1\n");
}

void write_pop(FILE *fout, char *segment, char *index) {
#if DEBUG == 1
  fprintf(fout, "// pop %s %s\n", segment, index);
#endif

  if (strcmp(segment, "local") == 0 ||
      strcmp(segment, "argument") == 0) {
    fprintf(fout, "@%s\nD=A\n", index);

    if (strcmp(segment, "local") == 0) fprintf(fout, "@LCL\n");
    if (strcmp(segment, "argument") == 0) fprintf(fout, "@ARG\n");

    fprintf(fout,
            "D=M+D\n"
            "@R13\n"
            "M=D\n"
            "@SP\n"
            "AM=M-1\n"
            "D=M\n"
            "@R13\n"
            "A=M\n"
            "M=D\n");
  }

  if (strcmp(segment, "static") == 0)
    fprintf(fout,
            "@SP\n"
            "AM=M-1\n"
            "D=M\n"
            "@%s.%s\n"
            "M=D\n",
            filename,
            index);
}

void write_label(FILE *fout, char *label_name) {
#if DEBUG == 1
  fprintf(fout, "// label %s\n", label_name);
#endif

  EXIT_IF_TRUE(is_digit(label_name[0]), "A label name can\'t start with a digit\n");

  fprintf(fout, "(%s)\n", label_name);
}

void write_goto(FILE *fout, char *label_name) {
#if DEBUG == 1
  fprintf(fout, "// goto %s\n", label_name);
#endif

  fprintf(fout,
          "@%s\n"
          "0;JMP\n",
          label_name);
}

void write_if_goto(FILE *fout, char *label_name) {
#if DEBUG == 1
  fprintf(fout, "// if-goto %s\n", label_name);
#endif

  fprintf(fout,
          "@SP\n"
          "AM=M-1\n"
          "D=M\n"
          "@%s\n"
          "D;JNE\n",
          label_name);
}

void write_call(FILE *fout, char *function_name, char *num_args) {
#if DEBUG == 1
  fprintf(fout, "// call %s %s\n", function_name, num_args);
#endif

  // Push the return address
  fprintf(fout,
          "@RETURN_ADDRESS_%d\n"
          "D=A\n"
          "@SP\n"
          "A=M\n"
          "M=D\n"
          "@SP\n"
          "M=M+1\n",
          return_address_counter);

  // Saves to the stack the caller segments (LCL, ARG, THIS, THAT)
  const char *segments[] = {"LCL", "ARG", "THIS", "THAT"};
  for (unsigned int i = 0; i < 4; ++i)
    fprintf(fout,
            "@%s\n"
            "D=M\n"
            "@SP\n"
            "A=M\n"
            "M=D\n"
            "@SP\n"
            "M=M+1\n",
            segments[i]);

  // ARG = RAM[SP] - 5 - nArgs
  fprintf(fout,
          "@SP\n"
          "D=M\n"
          "@%s\n"
          "D=D-A\n"
          "@5\n"
          "D=D-A\n"
          "@ARG\n"
          "M=D\n",
          num_args);

  // LCL = RAM[SP]
  fprintf(fout,
          "@SP\n"
          "D=M\n"
          "@LCL\n"
          "M=D\n");

  write_goto(fout, function_name);
  fprintf(fout,
          "(RETURN_ADDRESS_%d)\n",
          return_address_counter);

  // Update the global return address counter
  return_address_counter++;
}

void write_function(FILE *fout, char *function_name, char *num_args) {
#if DEBUG == 1
  fprintf(fout, "// function %s %s\n", function_name, num_args);
#endif

  write_label(fout, function_name);

  for (int i = 0; i < atoi(num_args); ++i)
    fprintf(fout,
            "@SP\n"
            "A=M\n"
            "M=0\n"
            "@SP\n"
            "M=M+1\n");
}

void write_return(FILE *fout) {
  fprintf(fout,
#if DEBUG == 1
          "// return\n"
#endif
          // FRAME = LCL
          "@LCL\n"
          "D=M\n"
          "@R13\n"
          "M=D\n"

          // RET_ADDRESS = *(FRAME - 5)
          "@5\n"
          "A=D-A\n"
          "D=M\n"
          "@R14\n"
          "M=D\n"

          // *ARG = pop()
          "@SP\n"
          "A=M-1\n"
          "D=M\n"
          "@ARG\n"
          "A=M\n"
          "M=D\n"
          "@SP\n"
          "M=M-1\n"

          // SP = ARG + 1
          "@ARG\n"
          "D=M+1\n"
          "@SP\n"
          "M=D\n");

  // Restore the segments of the caller
  const char *segments[] = {"THAT", "THIS", "ARG", "LCL"};
  for (unsigned int i = 0; i < 4; ++i)
    fprintf(fout,
            "@R13\n"
            "D=M\n"
            "@%d\n"
            "A=D-A\n"
            "D=M\n"
            "@%s\n"
            "M=D\n",
            i + 1,
            segments[i]);

  // Goto return address
  fprintf(fout,
          "@R14\n"
          "A=M\n"
          "0;JMP\n");
}
