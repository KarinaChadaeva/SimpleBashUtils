#ifndef FLAGS_H
#define FLAGS_H

#include <stdio.h>
#include <string.h>

void flags_parser(char *flags, int argc, char **argv, int *check_flag);
void append_flags(char flag, char *flags);
void append_multiple(char *flags, char *arg);
char unify_equivalents(char *arg);
void print_with_flags(char *flags, char *filename);
void e_flag(char *flags, char ch);
void t_flag(char *flags, char ch);
void v_flag(char *flags, int ch);
void check_new_line(char ch, int *new_line, int is_empty, int *prev_is_empty);
int check_empty_line(char ch, int new_line);
void bn_flag(char *flags, int new_line, int is_empty, int *num_line);
void s_flag(char *flags, char ch, int is_empty, int prev_is_empty);

#endif