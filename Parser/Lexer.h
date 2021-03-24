#ifndef COMPILADORES_TEXTILES_LEXER_H
#define COMPILADORES_TEXTILES_LEXER_H

#include <stack>
#include "TOKEN.h"

class Lexer {
    std::stack<TOKEN> tokens;
public:
    explicit Lexer(std::string input);

    std::stack<TOKEN> get_tokens();
};


#endif //COMPILADORES_TEXTILES_LEXER_H
