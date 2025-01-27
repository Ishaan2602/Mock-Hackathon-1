#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <parser.h>

// Token Structure
struct Token {
    TokenType type;
    std::string lexeme;
    int line;  // Line number for error reporting

    Token(TokenType type, const std::string& lexeme, int line)
        : type(type), lexeme(lexeme), line(line) {}
};

// Abstract Syntax Tree (AST) Nodes
struct Expr {
    virtual ~Expr() = default;
};

struct LiteralExpr : public Expr {
    std::string value;
    explicit LiteralExpr(const std::string& value) : value(value) {}
};

struct BinaryExpr : public Expr {
    std::shared_ptr<Expr> left;
    std::string op;
    std::shared_ptr<Expr> right;

    BinaryExpr(std::shared_ptr<Expr> left, const std::string& op, std::shared_ptr<Expr> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}
};

// Parser Class
class Parser {
    const std::vector<Token>& tokens;
    size_t current = 0;

public:
    explicit Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

    std::shared_ptr<Expr> parse() {
        return expression();
    }

private:
    std::shared_ptr<Expr> expression() {
        return equality();
    }

    std::shared_ptr<Expr> equality() {
        auto expr = comparison();

        while (match({TokenType::OPERATOR}) && (peek().lexeme == "==" || peek().lexeme == "!=")) {
            Token op = advance();
            auto right = comparison();
            expr = std::make_shared<BinaryExpr>(expr, op.lexeme, right);
        }

        return expr;
    }

    std::shared_ptr<Expr> comparison() {
        auto expr = term();

        while (match({TokenType::OPERATOR}) && (peek().lexeme == "<" || peek().lexeme == ">")) {
            Token op = advance();
            auto right = term();
            expr = std::make_shared<BinaryExpr>(expr, op.lexeme, right);
        }

        return expr;
    }

    std::shared_ptr<Expr> term() {
        auto expr = factor();

        while (match({TokenType::OPERATOR}) && (peek().lexeme == "+" || peek().lexeme == "-")) {
            Token op = advance();
            auto right = factor();
            expr = std::make_shared<BinaryExpr>(expr, op.lexeme, right);
        }

        return expr;
    }

    std::shared_ptr<Expr> factor() {
        auto expr = primary();

        while (match({TokenType::OPERATOR}) && (peek().lexeme == "*" || peek().lexeme == "/")) {
            Token op = advance();
            auto right = primary();
            expr = std::make_shared<BinaryExpr>(expr, op.lexeme, right);
        }

        return expr;
    }

    std::shared_ptr<Expr> primary() {
        if (match({TokenType::NUMBER, TokenType::STRING})) {
            return std::make_shared<LiteralExpr>(previous().lexeme);
        }

        throw std::runtime_error("Expected expression at line " + std::to_string(peek().line));
    }

    // Utility Methods
    bool match(const std::vector<TokenType>& types) {
        for (const auto& type : types) {
            if (check(type)) {
                advance();
                return true;
            }
        }
        return false;
    }

    bool check(TokenType type) const {
        if (isAtEnd()) return false;
        return peek().type == type;
    }

    Token advance() {
        if (!isAtEnd()) current++;
        return previous();
    }

    bool isAtEnd() const {
        return peek().type == TokenType::EOF_TOKEN;
    }

    Token peek() const {
        return tokens[current];
    }

    Token previous() const {
        return tokens[current - 1];
    }
};