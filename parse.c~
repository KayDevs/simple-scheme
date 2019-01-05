#include "parse.h"
#include <stdio.h>

//returns list of tokens [(, ), symbol]
list *tokenize(const char *src) {
  list *ret = NULL;
  int src_index = 0;
  char nextchar;
  while(nextchar = src[src_index++]) {
    if(nextchar == '(' || nextchar == ')') {
      char *t = calloc(2, sizeof(char));
      t[0] = nextchar;
      t[1] = '\0';
      ret = consc(t, ret);
    } else if (nextchar == ' ' || nextchar == '\n') {
      continue;
    } else { //symbol
      char *t = calloc(32, sizeof(char));
      int offset = src_index;
      while(nextchar && !(nextchar == '(' || nextchar == ')' || nextchar == ' ' || nextchar == '\n')) {
        t[src_index-offset] = nextchar;
        nextchar = src[src_index++]; 
      }
      //make sure to not skip the parens, because they are both delimiters here as well as valid tokens on their own
      if(nextchar == '(' || nextchar == ')') {
        src_index--;
      }
      ret = consc(t, ret);
    }
  }
  //reverse the list
  return reverse(ret);
}

//note: a proper s-expression should have at most 1 cons nest
//but due to syntactic sugar and special forms, this doesn't apply.
list *expressionize(list *tokens) {
  //note: assumed that tokens is a SYMBOL list (consc),
  //otherwise this func doesn't really apply
  list *exps = NULL;
  int stack = 0;
  for(list *p = tokens; p != NULL; p = cdr(p)) {
    if(strncmp((char *)car(p), "(", 1) == 0) {
      //push;
      if(stack == 0) {
        exps = cons(expressionize(cdr(p)), exps);
      }
      stack++;
    } else if(strncmp((char *)car(p), ")", 1) == 0){
      //pop; 
      if(stack == 0) {
        break;
      }
      stack--;
    } else {
      //append symbol;
      if(stack == 0) {
        exps = consc((char *)car(p), exps);
      }
    }
  }
  return reverse(exps);
}
