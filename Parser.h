#ifndef COMPILADORES_TEXTILES_PARSER_H
#define COMPILADORES_TEXTILES_PARSER_H

#include <utility>

#include "Lexer.h"
#include "CFGrammarHandler.h"

using result_t = std::pair<bool, std::string>;

class Parser {
    std::stack<TOKEN> tokens;

    std::unordered_map<std::string, int> nter_int;
public:
    Parser(std::string grammari, std::string terminalsi, std::string non_terminalsi, std::string start){
        /* CFGrammarHandler handler(std::move(grammari), std::move(terminalsi), std::move(non_terminalsi), std::move(start));
        auto pair = handler.get_firsts_follows();
        handler.print();*/

    }

    int getIndexNonTerminal(std::string nter) {
        return nter_int[nter];
    }

    std::unordered_map<std::string, int> ter_int;

    int getIndexTerminal(std::string ter) {
        return nter_int[ter];
    }

    using table = std::vector<std::vector<std::vector<std::string>>>;
    std::unordered_map<std::string, std::unordered_set<std::string>> Firsts;

    table fill_table_MNT(std::unordered_map<std::string, Rule_t> grammar) {
        table tabla;
        for (const auto &nter : grammar) {
            for (auto rule : nter.second) {//cada regla, '|'
                //rule[0] es al q le revisare los primeros
                for (const auto &llegada : Firsts[rule[0]]) {
                    //agregar en M[A,a] la regla A --> alpha
                    tabla[getIndexNonTerminal(nter.first)][getIndexTerminal(llegada)] = rule;
                }
            }
        }
        return tabla;
    }

    void analyze_string(std::string w, table tabla, std::string initial, SetString_t terminals) {
        std::stack<std::string> stack;
        std::string X;
        std::string a;
        int ip = 0;
        w += "$";
        stack.push("$");
        stack.push(initial);
        while (X != "$") {
            X = stack.top();
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

    result_t lexeme(std::string input) {
        Lexer lexer(input);
        tokens = lexer.get_tokens();
    }
};


#endif //COMPILADORES_TEXTILES_PARSER_H
