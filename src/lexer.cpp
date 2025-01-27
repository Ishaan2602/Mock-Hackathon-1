#include "lexer.h"

Lexer::Lexer(const std::string& input_text): input_text(input_text), pos(0), currentChar(sourceCode[0]) {}

void Lexer::advance() {
    pos++;
    currentChar = (pos < input_text.size()) ? input_text[pos] : '\0';
}

Token Lexer::number() {
    std::string result;
    while(currentChar != '\0' && std::isdigit(currentChar)) {
        result += currentChar;
        advance();
    }
    return {TokenType::NUMBER, result};
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
     while (currentChar != '\0') {
        if (std::isspace(currentChar)) {
            advance();
        } else if (std::isdigit(currentChar)) {
            tokens.push_back(number());
        } else if (currentChar == '+') {
            tokens.push_back({TokenType::PLUS, "+"});
            advance();
        } else if (currentChar == '-') {
            tokens.push_back({TokenType::MINUS, "-"});
            advance();
        } else if (currentChar == '*') {
            tokens.push_back({TokenType::MULTIPLY, "*"});
            advance();
        } else if (currentChar == '/') {
            tokens.push_back({TokenType::DIVIDE, "/"});
            advance();
        } else if (currentChar == '(') {
            tokens.push_back({TokenType::LPAREN, "("});
            advance();
        } else if (currentChar == ')') {
            tokens.push_back({TokenType::RPAREN, ")"});
            advance();
        } else {
            throw std::runtime_error("Invalid character");
        }
    }
    tokens.push_back({TokenType::END,""});
    return tokens;
}
