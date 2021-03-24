#ifndef COMPILADORES_TEXTILES_TEXTILESFLUJOPRODUCCION_H
#define COMPILADORES_TEXTILES_TEXTILESFLUJOPRODUCCION_H

#include "../Parser/Parser.h"

void TextilesFlujoProduccion();
int print_menu();
void analyze(Parser& parser, bool is_lexeme, std::string message);

#endif //COMPILADORES_TEXTILES_TEXTILESFLUJOPRODUCCION_H
