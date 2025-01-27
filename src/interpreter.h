#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser.h"

class Interpreter {
public:
    explicit Interpreter(AST *root);
    int evaluate();

private:
    AST *root;
    int visit(AST *node);
};

#endif
