#include "Parser.h"

#include <utility>

Parser::Parser(string_t grammari, string_t terminalsi, string_t non_terminalsi, string_t start) :
        handler(std::move(grammari), std::move(terminalsi), std::move(non_terminalsi), std::move(start)) {
    initialize();
    fill_table_MNT();
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
                table[nter_int[nter.first]][ter_int[first]] = production;
            }
        }
    }
}

std::vector<string_t> split_string(const string_t &w) {
    string_t curr = "";
    std::vector<string_t> split;
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

void Parser::print_stack(std::stack<string_t> stack) {
    std::stack<string_t> temp;
    while (!stack.empty()) {
        temp.push(stack.top());
        stack.pop();
    }
    while (!temp.empty()) {
        std::cout << temp.top() << " ";
        temp.pop();
    }
}

void Parser::print_input(std::vector<string_t> input, int ip) {
    while (ip < input.size())
        std::cout << input[ip++] << " ";
}

void Parser::print_input(VToken_t input, int ip) {
    for (int i = ip; i < input.size(); ++i) {
        std::cout << input[i].id << ' ';
    }
}

void Parser::analyze_string(const string_t &ws) {
    std::vector<std::string> w = split_string(ws);
    std::stack<std::string> stack;
    std::string X;
    std::string a;
    int ip = 0;
    w.emplace_back("$");
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
            if (a == "$" || handler.Follows.find(a) != handler.Follows.end()) {
                stack.pop();
                std::cout << "extraer ( error )\n";
            } else {
                ip++;
                std::cout << "explorar ( error )\n";
            }
            //std::cerr << "ERROR NO HAY PRODUCCION";
            //return;
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

void Parser::analyze_tokens(string_t input) {
    Lexer lexer(std::move(input));
    for (auto &token: lexer.get_tokens())
        std::cout << token << '\t';
    std::cout << '\n';
}

result_t Parser::analyze_lexeme(string_t input) {
    Lexer lexer(std::move(input));
    auto tokens = lexer.get_tokens();
    std::stack<string_t> stack;
    string_t X, a;
    bool fatal_error = tokens[0].type == TOKEN::Type::FATAL_ERROR, error = false;
    int ip = fatal_error ? 1 : 0;
    tokens.emplace_back(TOKEN::Type::$, "$", "ACCEPTED");
    stack.push("$");
    stack.push(handler.initial);
    X = stack.top();

    std::cout << "STACK\t\t\t\t||\t\t\t\tINPUT\t\t\t\t||\t\t\t\tACTION\n";
    std::cout << "____________________________________________________________________________________________\n";

    while (X != "$") {
        print_stack(stack);
        std::cout << "\t\t\t\t";
        print_input(tokens, ip);
        std::cout << "\t\t\t\t\t\t\t\t";
        a = tokens[ip].id;
        if (tokens[ip].type == TOKEN::Type::ERROR) {
            std::cout << "error ( " << tokens[ip].description << " )\n";
            error = true;
            ++ip;
        } else if (tokens[ip].type == TOKEN::Type::FATAL_ERROR) {
            std::cout << "explorar ( " << tokens[ip].description << " )\n";
            fatal_error = true;
            ++ip;
        } else if (X == a) {
            stack.pop();
            ip++;
            std::cout << "matching ( " << a << " )\n";
        } else if (table[nter_int[X]][ter_int[a]].empty()) {
            if (a == "$" || handler.Follows[X].find(a) != handler.Follows[X].end()) {
                stack.pop();
                fatal_error = true;
                std::cout << "extraer ( error )\n";
            } else {
                ip++;
                fatal_error = true;
                std::cout << "explorar ( error )\n";
            }
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
    std::cout << "$\t\t\t\t\t$\n";
    string_t acceptance;
    if (fatal_error) {
        acceptance = "REJECTED";
        if (tokens[0].type == TOKEN::Type::FATAL_ERROR)
            acceptance += ": " + tokens[0].description;
        else
            acceptance += ": Syntax error";
    } else
        acceptance = error ? "ACCEPTED WITH ERRORS, Lexical Error" : "ACCEPTED";
    if (ip != tokens.size() - 1)
        acceptance += ", unnecessary tokens";
    std::cout << "\t\t\t\t\t\t\t" << acceptance << "\n\n";
    return result_t{fatal_error, acceptance};
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

