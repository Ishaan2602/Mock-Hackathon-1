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
    }
    
    return 0;
}
