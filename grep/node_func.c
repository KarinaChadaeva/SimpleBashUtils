#include "node_func.h"

char *pop_f(Filename **head) {
  Filename *prev = NULL;
  char *filename = "";
  if (head != NULL) {
    prev = (*head);
    filename = prev->filename;
    (*head) = (*head)->next;
  }
  free(prev);
  return filename;
}

void push_f(Filename **head, char *filename) {
  Filename *last = *head;
  Filename *tmp = (Filename *)malloc(sizeof(Filename));
  tmp->filename = filename;
  tmp->next = NULL;
  if (*head == NULL) {
    *head = tmp;
  } else {
    while (last->next != NULL) {
      last = last->next;
    }
    last->next = tmp;
  }
}