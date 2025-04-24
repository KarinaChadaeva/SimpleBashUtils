#ifndef NODE_FUNC_H
#define NODE_FUNC_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Filename {
  char *filename;
  struct Filename *next;
} Filename;

void push_f(Filename **head, char *filename);
char *pop_f(Filename **head);

#endif