#ifndef COMPILADORES_TEXTILES_PARSER_H
#define COMPILADORES_TEXTILES_PARSER_H

#include <utility>

#include "Lexer.h"
#include "CFGrammarHandler.h"

using Rule_t = std::vector<std::vector<std::string>>;
using SetString_t = std::unordered_set<std::string>;
using MapSets_t = std::unordered_map<std::string, SetString_t>;
using Grammar_t = std::unordered_map<std::string, Rule_t>;
using Table_t = std::vector<std::vector<std::vector<std::string>>>;
using result_t = std::pair<bool, std::string>;

class Parser {
    std::stack<TOKEN> tokens;
    std::string initial;
    SetString_t non_terminals;
    SetString_t terminals;
    MapSets_t Firsts{};

    Table_t tabla;

    std::unordered_map<std::string, int> ter_int;
    std::unordered_map<std::string, int> nter_int;
public:
    Parser(std::string grammari, std::string terminalsi, std::string non_terminalsi, std::string start);

    void initialize_t_int();
    int getIndexNonTerminal(std::string nter);
    int getIndexTerminal(std::string ter);
    Table_t fill_table_MNT(Grammar_t grammar);
    void analyze_string(std::string w);
    result_t lexeme(std::string input);
};


#endif //COMPILADORES_TEXTILES_PARSER_H
