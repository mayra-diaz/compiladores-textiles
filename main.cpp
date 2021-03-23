#include <iostream>
#include "Lexer.h"
#include "FirstsAndFollows.h"


class Parser {
    std::stack<TOKEN> tokens;
public:
    Parser(std::string input){
        Lexer lexer(input);
        tokens = lexer.get_tokens();
    }
};

int main() {
    // Parser parser("A Sh1 Sv1 Ac1 N1 C1 C2 C4 A");
    // std::string grammar, std::string terminals, std::string non_terminals, std::string starti
    std::string grammar = "lexp : atom | list\n atom : number | identifier\n list : ( lexpseq )\n lexpseq : lexp lexpseq | lexp";
    FirstsAndFollows ff(grammar, "number identifier ( )", "lexp list atom lexpseq", "lexp");
    auto pair = ff.generate_firsts_follows();
    std::cout << "FIRSTS\n";
    for (auto x: pair.first){
        std::cout << x.first << '\t';
        for (auto v: x.second)
            std::cout << v << ' ';
        std::cout << '\n';
    }
    std::cout << "FOLLOWS\n";
    for (auto x: pair.second){
        std::cout << x.first << '\t';
        for (auto v: x.second)
            std::cout << v << ' ';
        std::cout << '\n';
    }
    return 0;
}
