#ifndef COMPILADORES_TEXTILES_TOKEN_H
#define COMPILADORES_TEXTILES_TOKEN_H

#include <string>
#include <iostream>

struct TOKEN {
    enum Type {
        A, SH, SV, N, AC, C, ERROR, $, FATAL_ERROR
    };
    Type type;
    std::string id;
    std::string description;

    TOKEN(Type type, std::string id);

    TOKEN(Type type, std::string id, std::string e);

    friend std::ostream &operator<<(std::ostream &os, const TOKEN &token);

private:
    std::string get_description() const;
};


#endif //COMPILADORES_TEXTILES_TOKEN_H
