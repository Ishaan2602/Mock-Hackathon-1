#include <iostream>
#include <string>
#include <vector>

enum class TokenType {
    IDENTIFIER,   
    NUMBER,       
    STRING,
    NEWLINE,
    INDENT,
    DEDENT,
    OPERATOR,
    KEYWORD,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    COLON,
    COMMA,
    EOF_TOKEN
};

struct Token {
    std::string value;
    TokenType type;
};