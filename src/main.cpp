#include "interpreter.h"
#include "lexer.h"

#include <iostream>
#include <string>

void signalHandler(int signum) {
    exit(signum);
}

int main()
{
    signal(SIGINT, signalHandler);
    std::string input;
    std::cout << "A Python interpreter in C++! (Type 'exit' or 'Ctrl-C' to quit!)" << '\n';

    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }

        try {
            Lexer lexer(input);
            std::vector<Token> tokens = lexer.tokenize();
            Parser parser(tokens);
            AST *root = parser.parse();
            Interpreter interpreter(root);
            int result = interpreter.evaluate();
            std::cout << result << '\n';
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
    
    return 0;
}
