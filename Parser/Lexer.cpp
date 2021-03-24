#include "Lexer.h"

Lexer::Lexer(std::string input) {
    int i = 0;
    while (i < input.size()) {
        if (input[i] == ' ')
            ++i;
        if (input[i] == 'A') {
            if (input[++i] == 'c') {
                bool isd = std::isdigit(input[++i]);
                if (isd && input[i] - '0' < 5 && input[i] - '0' > 0)
                    tokens.push(TOKEN{TOKEN::Type::AC, input[i++] - '0'});
                else {
                    tokens.push(TOKEN{TOKEN::Type::ERROR, "Invalid phase"});
                    if (isd)
                        ++i;
                }
            } else
                tokens.push(TOKEN{TOKEN::Type::A, 0});
        } else if (input[i] == 'S') {
            if (input[++i] == 'h' || input[i] == 'v') {
                auto type = input[i] == 'h' ? TOKEN::Type::SH : TOKEN::Type::SV;
                bool isd = std::isdigit(input[++i]);
                if (isd && input[i] - '0' < 6 && input[i] - '0' > 0)
                    tokens.push(TOKEN{type, input[i++] - '0'});
                else {
                    tokens.push(TOKEN{TOKEN::Type::ERROR, "Invalid phase"});
                    if (isd)
                        ++i;
                }
            } else
                tokens.push(TOKEN{TOKEN::Type::ERROR, "Invalid phase"});
        } else if (input[i] == 'N') {
            bool isd = std::isdigit(input[++i]);
            if (isd && input[i] - '0' < 6 && input[i] - '0' > 0)
                tokens.push(TOKEN{TOKEN::Type::N, input[i++] - '0'});
            else {
                tokens.push(TOKEN{TOKEN::Type::ERROR, "Invalid phase"});
                if (isd)
                    ++i;
            }
        } else if (input[i] == 'C') {
            bool isd = std::isdigit(input[++i]);
            if (isd && input[i] - '0' < 6 && input[i] - '0' > 0)
                tokens.push(TOKEN{TOKEN::Type::N, input[i++] - '0'});
            else {
                tokens.push(TOKEN{TOKEN::Type::ERROR, "Invalid phase"});
                if (isd)
                    ++i;
            }
        } else {
            tokens.push(TOKEN{TOKEN::Type::ERROR, "Invalid character"});
            ++i;
        }
    }
}

std::stack<TOKEN> Lexer::get_tokens() {
    return tokens;
}

