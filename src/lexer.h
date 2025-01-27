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
    std::string lexeme;
    TokenType type;
};

class Lexer {
    public:
        Lexer(std::string sourceCode);
    
        std::string sourceCode;
        std::vector<std::string> split();
        std::vector<Token> totoken(std::string sourceCode);
};
