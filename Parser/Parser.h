#ifndef COMPILADORES_TEXTILES_PARSER_H
#define COMPILADORES_TEXTILES_PARSER_H

#include <utility>
#include <stack>

#include "Lexer.h"
#include "../CFGHandler/CFGHandler.h"

using string_t = std::string;
using Table_t = std::vector<std::vector<Production_t>>;
using result_t = std::pair<bool, string_t>;

class Parser {
    CFGHandler handler;
    Table_t table;

    void fill_table_MNT();

    SetS_t get_First(identifier_t element);

    Map_String_Int_t nter_int;
    Map_Int_String_t int_nter;
    Map_String_Int_t ter_int;
    Map_Int_String_t int_ter;

    void initialize();

public:
    Parser(string_t grammari, string_t terminalsi, string_t non_terminalsi, string_t start);

    void analyze_string(const string_t &w);

    result_t analyze_lexeme(string_t input);

    void analyze_tokens(string_t input);

    void print_grammar_info();

    void print_LL_table();

    static void print_stack(std::stack<string_t> stack);

    static void print_input(std::vector<string_t> input, int ip);

    static void print_input(VToken_t input, int ip);
};


#endif //COMPILADORES_TEXTILES_PARSER_H
