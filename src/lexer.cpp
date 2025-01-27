#include <iostream>
#include <string>
#include <vector>

#include "lexer.h"

std::vector<std::string> split(std::string sourceCode) {
    std::vector<std::string> lines;
    std::string line;

    int len = sourceCode.length();

    for (int i = len; i >= 0; i--) {
        if (sourceCode[i] == ' ') {
            lines.push_back(line);
            line = "";
        } else {
            line += sourceCode[i];
        }
    }
    return lines;
};

std::vector<Token> totoken(std::string sourceCode) {
    std::vector<Token> tokens;
    std::vector<std::string> lines = split(sourceCode);

    return tokens;
};
