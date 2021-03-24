#ifndef COMPILADORES_TEXTILES_LEXER_H
#define COMPILADORES_TEXTILES_LEXER_H

#include <vector>
#include "TOKEN.h"

using VToken_t = std::vector<TOKEN>;

class Lexer {
    VToken_t tokens;
public:
    explicit Lexer(std::string input);

    VToken_t get_tokens();
};


#endif //COMPILADORES_TEXTILES_LEXER_H
