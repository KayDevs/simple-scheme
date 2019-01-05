#include "types.h"
#include "parse.h"
#include <string.h>
#include <stdio.h>

//global symbol table
list *symbols = NULL; 

//register a program func to be visible to the interpreter
int regfunc() {
}

//function for breaking out of atoms wrapped in nested lists from the evaluator
const char *get_atom(list *at) {
  while(at->type == LIST) {
    at = car(at);
  }
  return (const char *)car(at);
}

//check if it's in the global symbol list, if not then cons it into the symbol list
const char *intern(const char *symbol) {
  for(list *p = symbols; p != NULL; p = cdr(p)) {
    if(strncmp((const char *)car(p), symbol, 32) == 0) {
      return (const char *)car(p);
    }
  }
  symbols = consc(strdup(symbol), symbols);
  return (const char *)car(symbols);
}

//evaluate arbitrary s-expressions:
//all of the form (symbol (arg-expr) (ret-expr))
// - lambda, define, if
//always returns an expr
//OR
//(funtion (args))
// - apply, quote
//OR an evaluatable atom
// - anything else really

list *eval(list *exps, list *env);

list *add(list *args) {
  const char *op1s = get_atom(args);
  const char *op2s = get_atom(cdr(args));
  double op1 = atof(op1s);
  double op2 = atof(op2s);
  double ret = op1 + op2;
  char *c = calloc(32, sizeof(char));
  sprintf(c, "%f", ret);
  return consc((const char *)c, NULL);
}
list *add_list(list *args) {
  double accumulator = 0.0;
  for(list *p = args; p != NULL; p = cdr(p)) {
    accumulator += atof(get_atom(car(p)));
  }
  char *c = calloc(32, sizeof(char));
  sprintf(c, "%f", accumulator);
  return consc((const char *)c, NULL);
}

list *apply(list *(func)(list *), list *args, list *env) {
  list *a = NULL;
  for(list *p = args; p != NULL; p = cdr(p)) {
    a = cons(eval(p, env), a);
  }
  return consc(get_atom(func(a)), NULL);
}

list *lexical_scope = NULL;
//env is this local scope
list *eval(list *exps, list *env) {
  if(exps != NULL) {
    if(strncmp((const char *)car(exps), intern("+"), 32) == 0) {
      return apply(add, cdr(exps), env);
    } else if(strncmp((const char *)car(exps), intern("++"), 32) == 0) {
      return apply(add_list, cdr(exps), env);
    } else if(strncmp((const char *)car(exps), intern("quote"), 32) == 0) {
      //return without evaluating
      return car(cdr(exps));
    } else if(strncmp((const char *)car(exps), intern("define"), 32) == 0) {
      //if it's already bound, just return it
      for(list *p = lexical_scope; p != NULL; p = cdr(p)) {
        if(intern(get_atom(p)) == intern(get_atom(cdr(exps)))) {
          return cdr(car(p));
        }
      }
      //add to lexical scope and return a pointer to the new item
      lexical_scope = cons(consc(intern(get_atom(cdr(exps))), cdr(cdr(exps))), lexical_scope);
      return cdr(car(lexical_scope));
    } else if(strncmp((const char *)car(exps), intern("env"), 32) == 0) {
      return env;
    } else if (strncmp((const char *)car(exps), intern("lex"), 32) == 0) {
      return lexical_scope;
    } else if (strncmp((const char *)car(exps), intern("lambda"), 32) == 0) {
      return exps;
    } else if (exps->type == LIST) {
      return cons(eval(car(exps), env), eval(cdr(exps), env));
    } else if (exps->type == SYMBOL) {
      //if it's bound, then evaluate it
      for(list *p = lexical_scope; p != NULL; p = cdr(p)) {
        if(strncmp(get_atom(p), get_atom(exps), 32) == 0) {
          return cdr(car(p));
        }
      }
      //otherwise just return the symbol itself
      return consc((const char *)car(exps), NULL);
    }
  }
  return NULL;
}
