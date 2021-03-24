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

    void fill_table_MNT();

    SetS_t get_First(identifier_t element);



    Map_String_Int_t nter_int;
    Map_Int_String_t int_nter;
    Map_String_Int_t ter_int;
    Map_Int_String_t int_ter;

    void initialize();

public:
    Parser(std::string grammari, std::string terminalsi, std::string non_terminalsi, std::string start);

    //void analyze_string(std::string w);
    result_t lexeme(std::string input);

    void print_grammar_info();
    void print_LL_table();
};


#endif //COMPILADORES_TEXTILES_PARSER_H
