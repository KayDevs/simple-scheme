#include "types.h"
#include <stdio.h>
#include <string.h>


list *car(list *l) {
  return l->data;
}
list *cdr(list *l) {
  return l->next;
}
list *cons(list *a, list *b) {
  list *ret = calloc(1, sizeof(list));
  ret->data = a;
  ret->next = b;
  return ret;
}

list *consc(const char *a, list *b) {
  list *ret = calloc(1, sizeof(list));
  ret->type = SYMBOL;
  ret->symbol = a;
  ret->next = b;
  return ret;
}

list *reverse(list *l) {
  list *ret = NULL;
  for(list *p = l; p != NULL; p = cdr(p)) {
    ret = cons(car(p), ret);
    ret->type = p->type;
  }
  return ret;
}

void print_type(list *l) {
  switch(l->type) {
  case 0:
    printf("LIST\n");
    break;
  case 1:
    printf("SYMBOL\n");
    break;
  case 2:
    printf("NUMBER\n");
    break;
  }
}
void print_list(list *l) {
  printf("[");
  for(list *p = l; p != NULL; p = cdr(p)) {
    if(p->type == SYMBOL) {
      printf("%s ", car(p));
    } else {
      print_list(car(p));
    }
  }
  printf("]");
}
