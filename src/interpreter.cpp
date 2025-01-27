#include "interpreter.h"
#include <stdexcept>

Interpreter::Interpreter(AST *root) : root(root) {}

// Start evaluating from the root of the AST.
int Interpreter::evaluate() {
    return visit(root);
}

// Recursively visit nodes in the AST and compute their values.
int Interpreter::visit(AST *node) {
    // If the node is a number, just return its value.
    if (node->token.type == TokenType::NUMBER) {
        return std::stoi(node->token.value); // Convert the string value to an integer.
    }

    // If the node is an operator, evaluate its children.
    if (node->token.type == TokenType::PLUS) {
        return visit(node->left) + visit(node->right); // Add left and right.
    } else if (node->token.type == TokenType::MINUS) {
        return visit(node->left) - visit(node->right); // Subtract right from left.
    } else if (node->token.type == TokenType::MULTIPLY) {
        return visit(node->left) * visit(node->right); // Multiply left and right.
    } else if (node->token.type == TokenType::DIVIDE) {
        int rightValue = visit(node->right);
        if (rightValue == 0) {
            throw std::runtime_error("Division by zero is not allowed.");
        }
        return visit(node->left) / rightValue;         // Divide left by right.
    }

    throw std::runtime_error("Unknown node type in AST.");
}
