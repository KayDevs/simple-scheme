#include <stdlib.h>
#ifndef TYPES_H
#define TYPES_H
//main list type
typedef struct list list;
struct list {
  enum types {
    LIST = 0x0,
    SYMBOL = 0x1,
    NUMBER = 0x2,
  } type;
  //data can be an atom (symbol) or a pair
  union {
    const char *symbol;
    double number;
    list *data;
  };
  list *next; //pointer to the next element in list
};


list *car(list *l);
list *cdr(list *l);
list *cons(list *a, list *b);
list *consc(const char *a, list *b);
list *consd(double a, list *b);
list *reverse(list *l);
void print_type(list *l);
void print_list(list *l);
#endif
