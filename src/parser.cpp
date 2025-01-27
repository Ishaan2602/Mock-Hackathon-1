#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include "parser.h"

std::shared_ptr<Expr> Parser::parse() {
    return expression();
}

std::shared_ptr<Expr> Parser::expression() {
    return equality();
}

std::shared_ptr<Expr> Parser::equality() {
    auto expr = comparison();
    
    while (match({TokenType::OPERATOR}) && 
           (peek().lexeme == "==" || peek().lexeme == "!=")) {
        Token op = advance();
        auto right = comparison();
        expr = std::make_shared<BinaryExpr>(expr, op.lexeme, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::comparison() {
    auto expr = term();

    while (match({TokenType::OPERATOR}) && 
           (peek().lexeme == "<" || peek().lexeme == ">")) {
        Token op = advance();
        auto right = term();
        expr = std::make_shared<BinaryExpr>(expr, op.lexeme, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::term() {
    auto expr = factor();

    while (match({TokenType::OPERATOR}) && 
           (peek().lexeme == "+" || peek().lexeme == "-")) {
        Token op = advance();
        auto right = factor();
        expr = std::make_shared<BinaryExpr>(expr, op.lexeme, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::factor() {
    auto expr = primary();

    while (match({TokenType::OPERATOR}) && 
           (peek().lexeme == "*" || peek().lexeme == "/")) {
        Token op = advance();
        auto right = primary();
        expr = std::make_shared<BinaryExpr>(expr, op.lexeme, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::primary() {
    if (match({TokenType::NUMBER, TokenType::STRING})) {
        return std::make_shared<LiteralExpr>(previous().lexeme);
    }

    throw std::runtime_error("Expected expression at line " + std::to_string(peek().line));
}

bool Parser::match(const std::vector<TokenType>& types) {
    for (const auto& type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::EOF_TOKEN;
}

Token Parser::peek() const {
    return tokens[current];
}

Token Parser::previous() const {
    return tokens[current - 1];
}
