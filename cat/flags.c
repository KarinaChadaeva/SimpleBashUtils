#include "flags.h"

void flags_parser(char *flags, int argc, char **argv, int *check_flag) {
  char flag = '-';
  for (int i = 0; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (strlen(argv[i]) > 2 && strcmp(argv[i], "--number-nonblank") &&
          strcmp(argv[i], "--number") && strcmp(argv[i], "--squeeze-blank")) {
        append_multiple(flags, argv[i]);
      }
      *check_flag = 1;
      flag = unify_equivalents(argv[i]);
      if (flag == 'T') {
        append_flags('t', flags);
        append_flags('v', flags);
      } else if (flag == 'E') {
        append_flags('e', flags);
        append_flags('v', flags);
      } else if (flag != '-') {
        append_flags(flag, flags);
      }
    }
  }
}

void print_with_flags(char *flags, char *filename) {
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    int new_line = 1, num_line = 1, is_empty = 0, prev_is_empty = 0;
    int ch = fgetc(file);

    while (ch != EOF) {
      is_empty = check_empty_line(ch, new_line);
      e_flag(flags, ch);
      t_flag(flags, ch);
      v_flag(flags, ch);
      bn_flag(flags, new_line, is_empty, &num_line);
      s_flag(flags, ch, is_empty, prev_is_empty);

      if (!(strchr(flags, 's')) && !(strchr(flags, 'v')) &&
          !(strchr(flags, 't') && ch == '\t')) {
        putc(ch, stdout);
      }
      check_new_line(ch, &new_line, is_empty, &prev_is_empty);
      ch = fgetc(file);
    }
  } else {
    fprintf(stderr, "No such file or directory\n");
  }
  fclose(file);
}

void append_multiple(char *flags, char *arg) {
  char flag;
  char tmp[3] = "--\0";
  for (unsigned long i = 1; i < strlen(arg); i++) {
    tmp[1] = arg[i];
    flag = unify_equivalents(tmp);
    if (flag == 'E') {
      append_flags('e', flags);
      append_flags('v', flags);
    } else if (flag == 'T') {
      append_flags('t', flags);
      append_flags('v', flags);
    } else if (flag != '-') {
      append_flags(flag, flags);
    }
  }
}

int check_empty_line(char ch, int new_line) {
  int is_empty = 0;

  if (new_line && ch == '\n') {
    is_empty = 1;
  } else {
    is_empty = 0;
  }
  return is_empty;
}

void check_new_line(char ch, int *new_line, int is_empty, int *prev_is_empty) {
  if (ch == '\n') {
    *new_line = 1;
    if (is_empty) {
      *prev_is_empty = 1;
    } else {
      *prev_is_empty = 0;
    }
  } else {
    *new_line = 0;
  }
}

void s_flag(char *flags, char ch, int is_empty, int prev_is_empty) {
  if (strchr(flags, 's')) {
    if (!(is_empty && prev_is_empty)) {
      putc(ch, stdout);
    }
  }
}

void v_flag(char *flags, int ch) {
  if (strchr(flags, 'v')) {
    if (ch < 32 && ch != 9 && ch != 10)
      printf("^%c", ch + 64);
    else if (ch > 127 && ch < 160)
      printf("M-^%c", ch - 64);
    else if (ch == 127)
      printf("^%c", ch - 64);
    else if (!(strchr(flags, 't') && ch == '\t'))
      printf("%c", ch);
  }
}

void t_flag(char *flags, char ch) {
  if (strchr(flags, 't') && ch == '\t') {
    putc('^', stdout);
    putc('I', stdout);
  }
}

void e_flag(char *flags, char ch) {
  if (strchr(flags, 'e') && ch == '\n') {
    putc('$', stdout);
  }
}

void bn_flag(char *flags, int new_line, int is_empty, int *num_line) {
  if (strchr(flags, 'b')) {
    if (new_line && !is_empty) {
      printf("%6d\t", *num_line);
      (*num_line)++;
    }
  } else if (strchr(flags, 'n')) {
    if (new_line) {
      printf("%6d\t", *num_line);
      (*num_line)++;
    }
  }
}

void append_flags(char flag, char *flags) {
  if (strchr(flags, flag) == NULL) {
    char tmp[2] = " ";
    tmp[0] = flag;
    strcat(flags, tmp);
  }
}

char unify_equivalents(char *arg) {
  char flag = ' ';

  if (!strcmp(arg, "-b") || !strcmp(arg, "--number-nonblank")) {
    flag = 'b';
  } else if (!strcmp(arg, "-e")) {
    flag = 'E';
  } else if (!strcmp(arg, "-E")) {
    flag = 'e';
  } else if (!strcmp(arg, "-n") || !strcmp(arg, "--number")) {
    flag = 'n';
  } else if (!strcmp(arg, "-t")) {
    flag = 'T';
  } else if (!strcmp(arg, "-T")) {
    flag = 't';
  } else if (!strcmp(arg, "-v")) {
    flag = 'v';
  } else if (!strcmp(arg, "-s") || !strcmp(arg, "--squeeze-blank")) {
    flag = 's';
  }
  return flag;
}