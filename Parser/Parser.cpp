#include "Parser.h"

#include <utility>

Parser::Parser(std::string grammari, std::string terminalsi, std::string non_terminalsi, std::string start):
                            handler(std::move(grammari), std::move(terminalsi), std::move(non_terminalsi), std::move(start)){
    /*fill_table_MNT();
    print_LL_table();*/
    handler.print();
}

SetInt_t Parser::get_First(identifier_t element) {
    if (handler.terminals.find(element) != handler.terminals.end())
        return SetInt_t {element};
    return handler.Firsts[element];
}

/*
void Parser::fill_table_MNT() {
    for(int i = 0; i < handler.non_terminals.size(); ++i){
        tabla.push_back(std::vector<Production_t>(handler.terminals.size()));
    }
    for (const auto &nter : handler.grammar) {
        for (auto production : nter.second) {//cada regla, '|', rule es un vector
            //rule[0] es al q le revisare los primeros
            for (const auto &first : get_First(production[0])) {//llegada es un token
                //agregar en M[A,a] la regla A --> alpha
                tabla[nter.first][first] = production;
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
    stack.push(handler.initial);
    while (X != "$") {
        X = stack.top();
        a = w[ip];
        if (X == a) {
            stack.pop();
            ip++;
        } else if (handler.terminals.find(get_cfg_element_id(X)) != handler.terminals.end()) {
            throw "ERROR";
        } else if (tabla[get_cfg_element_id(X)][get_cfg_element_id(a)].empty()) {
            throw "ERROR";
        } else if (!tabla[get_cfg_element_id(X)][get_cfg_element_id(a)].empty()) {
            auto rule = tabla[get_cfg_element_id(X)][get_cfg_element_id(a)];
            stack.pop();
            for (int i = rule.size() - 1; i >= 0; --i)
                stack.push(get_cfg_element_name(rule[i].id, rule[i].is_ter));
        }
    }
}*/

result_t Parser::lexeme(std::string input) {
    Lexer lexer(input);
    tokens = lexer.get_tokens();
    return result_t ();
}

void Parser::print_grammar_info(){
    handler.print();
}

/*
void Parser::print_LL_table(){
    std::cout << "     \n        ";
    for (auto ter: handler.terminals)
        std::cout << ter << "  ";
    std::cout << '\n';
    for (int i = 0; i < tabla.size(); ++i) {
        std::cout << get_cfg_element_name(i, false) << ":  ";
        for (int j = 0; j < tabla[0].size(); ++j) {
            for (auto p: tabla[i][j])
                std::cout << get_cfg_element_name(p.id, p.is_ter) << " ";
            std::cout << '\n';
        }
    }
}*/

