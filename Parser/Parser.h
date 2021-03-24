#ifndef COMPILADORES_TEXTILES_PARSER_H
#define COMPILADORES_TEXTILES_PARSER_H

#include <utility>

#include "Lexer.h"
#include "../CFGHandler/CFGHandler.h"

using Table_t = std::vector<std::vector<Production_t>>;
using result_t = std::pair<bool, std::string>;

class Parser {
    std::stack<TOKEN> tokens;
    CFGHandler handler;

    Table_t tabla;

   // void fill_table_MNT();
    SetInt_t get_First(identifier_t element);

    inline name_t get_cfg_element_name(identifier_t e, bool is_ter){
        return "handler.get_element_name(e, is_ter)";
    };
    inline identifier_t get_cfg_element_id(name_t e) {
        return "handler.get_element_id(e)";
    };

public:
    Parser(std::string grammari, std::string terminalsi, std::string non_terminalsi, std::string start);

    //void analyze_string(std::string w);
    result_t lexeme(std::string input);

    void print_grammar_info();
    //void print_LL_table();
};


#endif //COMPILADORES_TEXTILES_PARSER_H
