#ifndef GREP_H
#define GREP_H

#include "flags.h"
#include "node_func.h"

void grep_str(char *flags, int files_count, Filename *head, char *patterns);
int reg_compile(char *flags, char *pattern, char *str, regmatch_t *pmatch);
void analyze_args(int argc, char **argv, Filename **head, int *files_count,
                  char *patterns, char *flags);
void flag_f(int argc, char **argv, Filename **head, int *files_count,
            char *patterns);
void get_pat_from_file(char *pat_filename, char *patterns);

#endif