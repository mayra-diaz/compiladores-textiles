#include "TOKEN.h"

TOKEN::TOKEN(Type type, int n): type(type), num(n) {
    name = get_name();
}
TOKEN::TOKEN(Type type, std::string e): type(type), name(std::move(e)) {}

std::string TOKEN::get_name() const{
    switch (type) {
        case A:
            return "Almacén";
        case SH:
            return "Tejido horizontal";
        case SV:
            return "Tejido vertical";
        case N:
            return "Teñido";
        case AC:
            return "Acabado";
        case C:
            return "Confección";
        default:
            return "ERROR";
    }
}