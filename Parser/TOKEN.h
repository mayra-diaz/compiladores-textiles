#ifndef COMPILADORES_TEXTILES_TOKEN_H
#define COMPILADORES_TEXTILES_TOKEN_H

#include <string>

struct TOKEN {
    enum Type {
        A, SH, SV, N, AC, C, ERROR
    };
    Type type;
    int num=0;
    std::string name;

    TOKEN(Type type, int n);
    TOKEN(Type type, std::string e);

private:
    std::string get_name() const;
};


#endif //COMPILADORES_TEXTILES_TOKEN_H
