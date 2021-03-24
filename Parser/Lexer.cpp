#include "Lexer.h"

Lexer::Lexer(std::string input) {
    int i = 0, phases = 0;
    while (i < input.size()) {
        std::string id;
        if (input[i] == ' ')
            ++i;
        if (input[i] == 'A') {
            if (input[++i] == 'c') {
                bool isd = std::isdigit(input[++i]);
                if (isd && input[i] - '0' < 5 && input[i] - '0' > 0) {
                    tokens.push_back(TOKEN{TOKEN::Type::AC, "ac" + std::string(1, input[i++])});
                    ++phases;
                } else {
                    id = isd ? "Ac" + std::string(1, input[i++]) : "Ac";
                    tokens.push_back(TOKEN{TOKEN::Type::ERROR, id, "Invalid phase"});
                }
            } else {
                tokens.push_back(TOKEN{TOKEN::Type::A, "a"});
            }
        } else if (input[i] == 'S') {
            if (input[++i] == 'h' || input[i] == 'v') {
                auto type = input[i] == 'h' ? TOKEN::Type::SH : TOKEN::Type::SV;
                id = type == TOKEN::Type::SH ? "sh" + std::string(1, input[++i]) : "sv" + std::string(1, input[++i]);
                bool isd = std::isdigit(input[i]);
                if (isd && input[i] - '0' < 6 && input[i++] - '0' > 0) {
                    tokens.push_back(TOKEN{type, id});
                    ++phases;
                } else {
                    id = isd ? "S" + std::string(1, input[i - 1]) + std::string(1, input[i++]) : "S" + std::string(1,
                                                                                                                   input[-1]);
                    tokens.push_back(TOKEN{TOKEN::Type::ERROR, id, "Invalid phase"});
                }
            } else
                tokens.push_back(TOKEN{TOKEN::Type::ERROR, "S", "Invalid phase"});
        } else if (input[i] == 'N') {
            bool isd = std::isdigit(input[++i]);
            if (isd && input[i] - '0' < 6 && input[i] - '0' > 0) {
                tokens.push_back(TOKEN{TOKEN::Type::N, "n" + std::string(1, input[i++])});
                ++phases;
            } else {
                id = isd ? "N" + std::string(1, input[i++]) : "N";
                tokens.push_back(TOKEN{TOKEN::Type::ERROR, id, "Invalid phase"});
            }
        } else if (input[i] == 'C') {
            bool isd = std::isdigit(input[++i]);
            if (isd && input[i] - '0' < 6 && input[i] - '0' > 0) {
                tokens.push_back(TOKEN{TOKEN::Type::C, "c" + std::string(1, input[i++])});
                ++phases;
            } else {
                tokens.push_back(TOKEN{TOKEN::Type::ERROR, "C", "Invalid phase"});
            }
        } else {
            tokens.push_back(TOKEN{TOKEN::Type::ERROR, std::string(1, input[i++]), "Invalid character"});
        }
    }
    if (phases > 5) {
        tokens.insert(tokens.begin(), TOKEN{TOKEN::Type::FATAL_ERROR, "ERROR", "More than 5 phases."});
    }
}

VToken_t Lexer::get_tokens() {
    return tokens;
}

