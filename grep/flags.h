#ifndef FLAGS_H
#define FLAGS_H

#include "node_func.h"

void flags_parser(char *flags, int argc, char **argv);
void append_multiple(char *flags, char *arg);
void append_flags(char flag, char *flags);
void flags_nh(char *flags, int files_count, char *str, char *filename,
              int line_count);
void flags_cl(int *match_count, int *match_file, char *flags);
void flags_process(char *flags, int result, int *match_count, int *match_file,
                   char *filename, int files_count, char *str, int line_count);
void print_cl(char *flags, int *match_count, int files_count, char *filename,
              int *match_file);
void flag_o(int result, char *filename, char *str, regmatch_t *pmatch,
            int files_count, char *flags, int line_count);

#endif