#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include "interp.h"
#include "types.h"


int main(int argc, char **argv) {

  char input[256];
  list *env = NULL;

  printf("> ");
  while(strcmp(fgets(input, 256, stdin), "(exit)\n") != 0) {
    list *l = eval(expressionize(tokenize(input)), env);
    print_list(l);
    printf("\n> ");
  }

  return 0;
}
