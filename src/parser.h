#include "lexer.h"

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

class Parser {
private:
    const std::vector<Token>& tokens;
    size_t current = 0;

    bool match(const std::vector<TokenType>& types);
    bool check(TokenType type) const;
    bool isAtEnd() const;
    Token peek() const;
    Token previous() const;

    std::shared_ptr<Expr> expression();
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> comparison();
    std::shared_ptr<Expr> term();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> primary();

    Token advance();

public:
    explicit Parser(const std::vector<Token>& tokens) : tokens(tokens) {}
    std::shared_ptr<Expr> parse();
};
