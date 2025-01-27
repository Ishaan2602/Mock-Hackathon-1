#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <vector>

enum class TokenType {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    //EQUALS,
    //NOTEQUALS,
    LPAREN,
    RPAREN,
    END
};

struct Token {
    TokenType type;
    int line;
    std::string value;
};

class Lexer {
    public:
        explicit Lexer(const std::string& input_text);
        std::vector<Token> tokenize(); //main function

    private:
        std::string input_text;
        int pos;
        char currentChar;
        
        void advance(); //updates pos and currentChar
        Token number(); //helper func to recognize numbers
};

#endif
N