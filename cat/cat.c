#include "flags.h"

void print_file(char *filename);
void redirect_content(char *first_filename, char *second_filename);
void concatenar(char *first_filename, char *second_filename,
                char *result_filename);
void basic_cat_func(int argc, char **argv);

int main(int argc, char *argv[]) {
  int check_flag = 0;
  char flags[20] = " ";
  basic_cat_func(argc, argv);
  flags_parser(flags, argc, argv, &check_flag);

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      if (check_flag) {
        print_with_flags(flags, argv[i]);
      } else {
        print_file(argv[i]);
      }
    }
  }

  return 0;
}

void print_file(char *filename) {
  FILE *file = fopen(filename, "rt");
  if (file != NULL) {
    int ch = fgetc(file);
    while (ch != EOF) {
      putc(ch, stdout);
      ch = fgetc(file);
    }
  }
  fclose(file);
}

void basic_cat_func(int argc, char **argv) {
  if (argc == 4 && argv[2][0] == '>') {
    redirect_content(argv[1], argv[3]);
  } else if (argc == 5 && argv[3][0] == '>') {
    concatenar(argv[1], argv[2], argv[4]);
  }
}

void redirect_content(char *first_filename, char *second_filename) {
  FILE *file1 = fopen(first_filename, "rt");
  FILE *file2 = fopen(second_filename, "wb");

  if (file1 != NULL) {
    int ch = fgetc(file1);
    while (ch != EOF) {
      fputc(ch, file2);
    }
  }
  fclose(file1);
  fclose(file2);
}

void concatenar(char *first_filename, char *second_filename,
                char *result_filename) {
  FILE *file1 = fopen(first_filename, "rt");
  FILE *file2 = fopen(second_filename, "rt");
  FILE *file3 = fopen(result_filename, "wb");
  if (file1 != NULL && file2 != NULL) {
    int ch = fgetc(file1);
    while (ch != EOF) {
      fputc(ch, file3);
    }
    fclose(file3);
    FILE *file3 = fopen(result_filename, "ab");
    ch = fgetc(file2);
    while (ch != EOF) {
      fputc(ch, file3);
    }
  }
  fclose(file1);
  fclose(file2);
  fclose(file3);
}