#include "flags.h"

void flag_o(int result, char *filename, char *str, regmatch_t *pmatch,
            int files_count, char *flags, int line_count) {
  if (result == 0) {
    int length = pmatch[0].rm_eo - pmatch[0].rm_so;
    char match[length + 10];
    strncpy(match, str + pmatch[0].rm_so, length);
    if (strchr(match, '\n') == NULL) {
      strcat(match, "\n");
    }
    strcat(match, "\0");
    flags_nh(flags, files_count, match, filename, line_count);
  }
}

void flags_cl(int *match_count, int *match_file, char *flags) {
  if (strchr(flags, 'c')) {
    (*match_count)++;
  }
  if (strchr(flags, 'l')) {
    *match_file = 0;
  }
}

void print_cl(char *flags, int *match_count, int files_count, char *filename,
              int *match_file) {
  if (strchr(flags, 'c')) {
    if (files_count == 1 || strchr(flags, 'h'))
      printf("%d\n", *match_count);
    else
      printf("%s:%d\n", filename, *match_count);
    *match_count = 0;
  }
  if (strchr(flags, 'l')) {
    if (match_file) {
      printf("%s\n", filename);
    }
  }
}

void flags_nh(char *flags, int files_count, char *str, char *filename,
              int line_count) {
  if (strchr(flags, 'n') && files_count > 1 && !(strchr(flags, 'h'))) {
    printf("%s:%d:%s", filename, line_count, str);
  } else if (strchr(flags, 'n')) {
    printf("%d:%s", line_count, str);
  } else if (strchr(flags, 'h') || files_count == 1) {
    printf("%s", str);
  } else if (files_count > 1) {
    printf("%s:%s", filename, str);
  }
}

void flags_process(char *flags, int result, int *match_count, int *match_file,
                   char *filename, int files_count, char *str, int line_count) {
  if (strchr(flags, 'v')) {
    if (result == REG_NOMATCH) {
      if (strchr(flags, 'c') || strchr(flags, 'l')) {
        flags_cl(match_count, match_file, flags);
      } else {
        flags_nh(flags, files_count, str, filename, line_count);
      }
    }
  } else {
    if (result == 0) {
      if (strchr(flags, 'c') || strchr(flags, 'l')) {
        flags_cl(match_count, match_file, flags);
      } else {
        flags_nh(flags, files_count, str, filename, line_count);
      }
    }
  }
}

void flags_parser(char *flags, int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (strlen(argv[i]) > 2) {
        append_multiple(flags, argv[i]);
      } else {
        append_flags(argv[i][1], flags);
      }
    }
    if (argv[i][0] != '-') {
      break;
    }
  }
}

void append_multiple(char *flags, char *arg) {
  for (unsigned long i = 1; i < strlen(arg); i++) {
    append_flags(arg[i], flags);
  }
}

void append_flags(char flag, char *flags) {
  if (strchr(flags, flag) == NULL) {
    char tmp[2] = " ";
    tmp[0] = flag;
    strcat(flags, tmp);
  }
}