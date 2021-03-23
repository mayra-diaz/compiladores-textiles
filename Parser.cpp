#include "Parser.h"

Parser::Parser(std::string grammari, std::string terminalsi, std::string non_terminalsi, std::string start): initial(start){
        CFGrammarHandler handler(std::move(grammari), std::move(terminalsi), std::move(non_terminalsi), start);
        auto pair = handler.get_firsts_follows();
        Firsts = pair.first;
        auto grammar = handler.get_grammar();
        terminals = handler.get_terminals();
        non_terminals = handler.get_non_terminals();
        initialize_t_int();
        fill_table_MNT(grammar);
}

void Parser::initialize_t_int(){
    int c = 0;
    for(auto x: terminals)
        ter_int.insert({x, c++});
    c = 0;
    for(auto x: non_terminals)
        nter_int.insert({x, c++});
}

int Parser::getIndexNonTerminal(std::string nter) {
    return nter_int[nter];
}

int Parser::getIndexTerminal(std::string ter) {
    return ter_int[ter];
}

Table_t Parser::fill_table_MNT(Grammar_t grammar) {
    for(int i = 0; i < non_terminals.size(); ++i){
        tabla.push_back(std::vector<std::vector<std::string>>(terminals.size()));
    }
    for (const auto &nter : grammar) {
        for (auto rule : nter.second) {//cada regla, '|'
            //rule[0] es al q le revisare los primeros
            for (const auto &llegada : Firsts[rule[0]]) {
                //agregar en M[A,a] la regla A --> alpha
                tabla[getIndexNonTerminal(nter.first)][getIndexTerminal(llegada)] = rule;
            }
        }
    }
}

void Parser::analyze_string(std::string w) {
    std::stack<std::string> stack;
    std::string X;
    std::string a;
    int ip = 0;
    w += "$";
    stack.push("$");
    stack.push(initial);
    while (X != "$") {
        X = stack.top();
        a = w[ip];
        if (X == a) {
            stack.pop();
            ip++;
        } else if (terminals.find(X) != terminals.end()) {
            throw "ERROR";
        } else if (tabla[getIndexNonTerminal(X)][getIndexTerminal(a)].empty()) {
            throw "ERROR";
        } else if (!tabla[getIndexNonTerminal(X)][getIndexTerminal(a)].empty()) {
            auto rule = tabla[getIndexNonTerminal(X)][getIndexTerminal(a)];
            stack.pop();
            for (int i = rule.size() - 1; i >= 0; --i)
                stack.push(rule[i]);
        }
    }
}

result_t Parser::lexeme(std::string input) {
    Lexer lexer(input);
    tokens = lexer.get_tokens();
}
