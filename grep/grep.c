#include "grep.h"

int main(int argc, char *argv[]) {
  char flags[40] = "";
  int files_count = 0;
  Filename *head = NULL;
  char patterns[3000] = "";

  flags_parser(flags, argc, argv);
  if (strchr(flags, 'f')) {
    flag_f(argc, argv, &head, &files_count, patterns);
  } else
    analyze_args(argc, argv, &head, &files_count, patterns, flags);
  grep_str(flags, files_count, head, patterns);

  return 0;
}

void grep_str(char *flags, int files_count, Filename *head, char *patterns) {
  int line_count = 0, match_count = 0, match_file = 0, result = 0;
  char str[5000] = "";
  char *filename = "";
  regmatch_t pmatch[100];

  while (head != NULL) {
    filename = pop_f(&head);
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
      while (fgets(str, sizeof(str), file)) {
        if (strchr(str, '\n') == NULL) {
          strcat(str, "\n");
        }
        line_count++;
        result = reg_compile(flags, patterns, str, pmatch);
        if (strchr(flags, 'o') &&
            !(strchr(flags, 'c') || strchr(flags, 'l') || strchr(flags, 'v')))
          flag_o(result, filename, str, pmatch, files_count, flags, line_count);
        else
          flags_process(flags, result, &match_count, &match_file, filename,
                        files_count, str, line_count);
      }
      fclose(file);
    } else if (!(strchr(flags, 's'))) {
      fprintf(stderr, "No such file or directory\n");
    }
    line_count = 0;
    print_cl(flags, &match_count, files_count, filename, &match_file);
  }
}

int reg_compile(char *flags, char *pattern, char *str, regmatch_t *pmatch) {
  regex_t reg;
  int result;
  if (strchr(flags, 'i')) {
    regcomp(&reg, pattern, REG_ICASE | REG_EXTENDED);
  } else {
    regcomp(&reg, pattern, REG_EXTENDED);
  }
  result = regexec(&reg, str, 100, pmatch, 0);
  regfree(&reg);
  return result;
}

void analyze_args(int argc, char **argv, Filename **head, int *files_count,
                  char *patterns, char *flags) {
  int check_flag = 0, check_pattern = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      check_flag = 1;
      if (argv[i][0] == '-' && strchr(argv[i], 'e')) {
        check_flag = 2;
      }
      check_pattern = 0;
    } else if (check_flag == 2 && argv[i][0] != '-' && argv[i - 1][0] == '-') {
      if (strcmp(patterns, "\0") &&
          (argv[i - 1][0] == '-' && strchr(argv[i - 1], 'e'))) {
        strcat(patterns, "|");
        strncat(patterns, argv[i], strlen(argv[i]));
        check_pattern = 1;
      } else if (argv[i - 1][0] == '-' && strchr(argv[i - 1], 'e')) {
        strcpy(patterns, argv[i]);
        check_pattern = 1;
      } else if (!(strchr(flags, 's')))
        fprintf(stderr, "error\n");
    } else if ((check_flag == 0 && argv[i] == argv[1]) ||
               (check_flag && argv[i][0] != '-' && argv[i - 1][0] == '-')) {
      strcpy(patterns, argv[i]);
      check_pattern = 1;
    } else if (argv[i][0] != '-' && check_pattern) {
      push_f(head, argv[i]);
      (*files_count)++;
    }
  }
}

void flag_f(int argc, char **argv, Filename **head, int *files_count,
            char *patterns) {
  char pat_filename[500];
  for (int i = 1; i < argc; i++) {
    if (argv[i - 1][0] == '-' && strchr(argv[i - 1], 'f')) {
      strcpy(pat_filename, argv[i]);
      get_pat_from_file(pat_filename, patterns);
    } else if (argv[i][0] != '-' &&
               !(argv[i - 1][0] == '-' && strchr(argv[i - 1], 'e'))) {
      push_f(head, argv[i]);
      (*files_count)++;
    }
  }
}

void get_pat_from_file(char *pat_filename, char *patterns) {
  FILE *file = fopen(pat_filename, "r");
  if (file != NULL) {
    char ch = fgetc(file);
    while (ch != EOF) {
      if ((ch == '\n' || ch == ' ') && strcmp(patterns, "\0")) {
        strcat(patterns, "|");
      } else {
        strncat(patterns, &ch, 1);
      }
      ch = fgetc(file);
    }
    fclose(file);
  } else {
    fprintf(stderr, "No such file or directory\n");
  }
}