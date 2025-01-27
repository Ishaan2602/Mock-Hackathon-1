# Mock-Hackathon-1

4 friends: [kidskoding](https://github.com/kidskoding), [Ishaan2602](https://github.com/Ishaan2602), [GodlyCarrot](https://github.com/GodlyCarrot), [flamebird797](https://github.com/flamebird797) built a simple Python interpreter using the C++ standard library in 6 hours.

Like any other Python interpreter, this Python interpreter interprets Python code in 3 steps
- Lexer - The `Lexer` (lexical analyzer) will convert the input string into a sequence of tokens, the basic building blocks of the Python language that include keywords, operators, identifiers, and literals.
- Parser - The `Parser` takes the sequence of tokens produced by the Lexer and constructs an Abstract Syntax Tree (AST). The AST represents the hierarchical structure of the source code
- Interpreter - The `Interpreter` traverses through the AST and evaluates the expressions. It performs the actual computation based on the structure of the AST.
