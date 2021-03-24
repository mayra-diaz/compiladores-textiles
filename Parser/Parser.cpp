#include "Parser.h"

#include <utility>

Parser::Parser(std::string grammari, std::string terminalsi, std::string non_terminalsi, std::string start) :
        handler(std::move(grammari), std::move(terminalsi), std::move(non_terminalsi), std::move(start)) {
    initialize();
    fill_table_MNT();
    //print_LL_table();
    //handler.print();
}


void Parser::initialize() {
    for (int i = 0; i < handler.non_terminals.size(); ++i) {
        table.push_back(std::vector<Production_t>(handler.terminals.size()));
    }
    int c = 0;
    for (auto nter: handler.non_terminals) {
        nter_int.insert({nter, c});
        int_nter.insert({c++, nter});
    }
    c = 0;
    for (auto ter: handler.terminals) {
        ter_int.insert({ter, c});
        int_ter.insert({c++, ter});
    }
}

SetS_t Parser::get_First(identifier_t element) {
    if (handler.terminals.find(element) != handler.terminals.end())
        return SetS_t{element};
    return handler.Firsts[element];
}

void Parser::fill_table_MNT() {
    for (auto nter : handler.grammar) {
        for (auto production : nter.second) {//cada regla, '|', rule es un vector
            //rule[0] es al q le revisare los primeros
            auto first_conj = get_First(production[0]);
            for (const auto &first : first_conj) {//llegada es un token
                //agregar en M[A,a] la regla A --> alpha
                int x = nter_int[nter.first];
                int y = ter_int[first];
                std::vector<std::string> copia = production;
                table[x][y] = copia;
            }
        }
    }
}

std::vector<std::string> split_string(const std::string &w) {
    std::string curr = "";
    std::vector<std::string> split;
    for (int i = 0; i < w.size(); ++i) {
        if (w[i] == ' ') {
            split.push_back(curr);
            curr = "";
        }
        if (w[i] != ' ')
            curr += w[i];
    }
    split.push_back(curr);
    return split;
}

void print_stack(std::stack<std::string> stack) {
    std::stack<std::string> temp;
    while (!stack.empty()) {
        temp.push(stack.top());
        stack.pop();
    }
    while (!temp.empty()) {
        std::cout << temp.top() << " ";
        temp.pop();
    }
}

void print_input(std::vector<std::string> input, int ip) {
    while (ip < input.size())
        std::cout << input[ip++] << " ";
}

void print_input(VToken_t input, int ip) {
    for (auto& token: input){
        std::cout << token << '\t';
    }
}

void Parser::analyze_string(const std::string &ws) {
    std::vector<std::string> w = split_string(ws);
    std::stack<std::string> stack;
    std::string X;
    std::string a;
    int ip = 0;
    w.push_back("$");
    stack.push("$");
    stack.push(handler.initial);
    X = stack.top();

    std::cout << "STACK\t\t||\t\tINPUT\t\t||\t\tACTION\n";
    std::cout << "________________________________________________________________________\n";

    while (X != "$") {
        print_stack(stack);
        std::cout << "\t ";
        print_input(w, ip);
        std::cout << "\t";
        a = w[ip];
        if (X == a) {
            stack.pop();
            ip++;
            std::cout << "matching ( " << a << " )\n";
        } else if (handler.terminals.find(X) != handler.terminals.end()) {
            std::cerr << "TERMINAL ERROR";
            return;
        } else if (table[nter_int[X]][ter_int[a]].empty()) {
            std::cerr << "ERROR NO HAY PRODUCCION";
            return;
        } else if (!table[nter_int[X]][ter_int[a]].empty()) {
            auto rule = table[nter_int[X]][ter_int[a]];
            stack.pop();
            for (int i = rule.size() - 1; i >= 0; --i)
                stack.push(rule[i]);
            std::cout << X << " --> ";
            for (int i = 0; i < rule.size(); ++i)
                std::cout << rule[i] << " ";
            std::cout << "\n";
        }
        X = stack.top();

    }
    std::cout << "$\t\t\t$\n";
    std::cout << "\t\tACCEPTED";
}

result_t Parser::lexeme(std::string input) {
    Lexer lexer(std::move(input));
    auto tokens = lexer.get_tokens();
    std::stack<std::string> stack;
    std::string X;
    std::string a;
    int ip = 0;
    tokens.emplace_back(TOKEN::Type::$, "$", "ACCEPTED");
    stack.push("$");
    stack.push(handler.initial);
    X = stack.top();

    std::cout << "STACK\t\t||\t\tINPUT\t\t||\t\tACTION\n";
    std::cout << "________________________________________________________________________\n";

    while (X != "$") {
        print_stack(stack);
        std::cout << "\t ";
        print_input(tokens, ip);
        std::cout << "\t";
        a = tokens[ip];
        if (X == a) {
            stack.pop();
            ip++;
            std::cout << "matching ( " << a << " )\n";
        } else if (handler.terminals.find(X) != handler.terminals.end()) {
            std::cerr << "TERMINAL ERROR";
            return;
        } else if (table[nter_int[X]][ter_int[a]].empty()) {
            std::cerr << "ERROR NO HAY PRODUCCION";
            return;
        } else if (!table[nter_int[X]][ter_int[a]].empty()) {
            auto rule = table[nter_int[X]][ter_int[a]];
            stack.pop();
            for (int i = rule.size() - 1; i >= 0; --i)
                stack.push(rule[i]);
            std::cout << X << " --> ";
            for (int i = 0; i < rule.size(); ++i)
                std::cout << rule[i] << " ";
            std::cout << "\n";
        }
        X = stack.top();

    }
    std::cout << "$\t\t\t$\n";
    std::cout << "\t\tACCEPTED";

    return result_t();
}

void Parser::print_grammar_info() {
    handler.print();
}


void Parser::print_LL_table() {
    std::cout << "     \n        ";
    for (int j = 0; j < table[0].size(); ++j)
        std::cout << int_ter[j] << " ";
    std::cout << '\n';
    for (int i = 0; i < table.size(); ++i) {
        std::cout << int_nter[i] << ":  ";
        for (int j = 0; j < table[0].size(); ++j) {
            for (auto p: table[i][j])
                std::cout << p << " ";
        }
        std::cout << "\n";
    }
}

