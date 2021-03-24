#include "TOKEN.h"

TOKEN::TOKEN(Type type, std::string id): type(type), id(id) {
    description = get_description();
}
TOKEN::TOKEN(Type type, std::string id, std::string e): type(type), id(id), description(std::move(e)) {}

std::string TOKEN::get_description() const{
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

std::ostream& TOKEN::operator<<(std::ostream& os) {
    os << id << ": " << description << '\n';
    return os;
}
