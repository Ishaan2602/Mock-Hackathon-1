#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <memory>

// Token types
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

// Token structure
struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    Token(TokenType type, const std::string& lexeme, int line);
};

// Abstract Syntax Tree (AST) nodes
struct Expr {
    virtual ~Expr() = default;
};

struct LiteralExpr : public Expr {
    std::string value;

    explicit LiteralExpr(const std::string& value);
};

struct BinaryExpr : public Expr {
    std::shared_ptr<Expr> left;
    std::string op;
    std::shared_ptr<Expr> right;

    BinaryExpr(std::shared_ptr<Expr> left, const std::string& op, std::shared_ptr<Expr> right);
};

// Parser class
class Parser {
private:
    const std::vector<Token>& tokens;
    size_t current = 0;

    std::shared_ptr<Expr> expression();
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> comparison();
    std::shared_ptr<Expr> term();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> primary();

    bool match(const std::vector<TokenType>& types);
    bool check(TokenType type) const;
    Token advance();
    bool isAtEnd() const;
    Token peek() const;
    Token previous() const;

public:
    explicit Parser(const std::vector<Token>& tokens);
    std::shared_ptr<Expr> parse();
};

#endif // PARSER_H
