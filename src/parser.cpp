#include "parser.h"

Token Parser::currentToken() {
    return (pos < tokens.size()) ? tokens[pos] : Token{TokenType::, ""};
}

void Parser::eat(TokenType type) {
    if (currentToken().type == type) {
        pos++; // Move to the next token
    } else {
        throw std::runtime_error("Unexpected token: " + currentToken().value);
    }
}

AST *Parser::factor() { //for partenthesis
    Token token = currentToken();
    if (token.type == TokenType::NUMBER) {
        eat(TokenType::NUMBER); // Consume the number token
        return new AST(token); // Return a leaf node for the number
    } else if (token.type == TokenType::LPAREN) {
        eat(TokenType::LPAREN);           // Consume '('
        AST *node = expression(); // Parse the inner expression
        eat(TokenType::RPAREN);           // Consume ')'
        return node;           // Return the parsed subtree
    }
    throw std::runtime_error("Invalid factor");
}

AST *Parser::term() { //for multiplication and division
    AST *node = factor(); // Start with a factor

    // While the current token is '*' or '/'
    while (currentToken().type == TokenType::MULTIPLY || currentToken().type == TokenType::DIVIDE) {
        Token token = currentToken();
        if (token.type == TokenType::MULTIPLY) {
            eat(TokenType::MULTIPLY);
        } else if (token.type == TokenType::DIVIDE) {
            eat(TokenType::DIVIDE);
        }
        node = new AST(token, node, factor()); //Create  binary operator node
    }
    return node;
}

AST *Parser::expression() {
    AST *node = term();

    while (currentToken().type == TokenType::PLUS || currentToken().type == TokenType::MINUS) {
        Token token = currentToken();
        if (token.type == TokenType::PLUS) {
            eat(TokenType::PLUS);
        } else if (token.type == TokenType::MINUS) {
            eat(TokenType::MINUS);
        }
        node = new AST(token, node, term()); //Create binary operator node
    }
    return node;
}

AST *Parser::parse() {
    return expression(); //Start parsing from expression
}

/*
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
    return peek().type == TokenType::END;
}

Token Parser::peek() const {
    return tokens[current];
}

Token Parser::previous() const {
    return tokens[current - 1];
}
*/
