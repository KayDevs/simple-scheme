#include "types.h"
#include <string.h>

#ifndef PARSE_H
#define PARSE_H
list *tokenize(const char *src);
list *expressionize(list *tokens);
#endif
