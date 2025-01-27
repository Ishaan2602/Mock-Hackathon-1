#include "lexer.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

struct AST {
    Token token; 
    AST *left;  
    AST *right;

    AST(Token token, AST *left = nullptr, AST *right = nullptr)
        : token(token), left(left), right(right) {}
};

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}
    AST* parse();

private:
    const std::vector<Token>& tokens;
    int pos = 0;

    Token currentToken();
    void eat(TokenType type); //consumes token if it matches expected type
    AST* factor();
    AST* term();
    AST* expression();
};
