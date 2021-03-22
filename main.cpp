#include <iostream>
#include "Lexer.h"


class Parser {
    std::stack<TOKEN> tokens;
public:
    Parser(std::string input){
        Lexer lexer(input);
        tokens = lexer.get_tokens();
    }
};

int main() {
    Parser parser("A Sh1 Sv1 Ac1 N1 C1 C2 C4 A");
    return 0;
}
