#ifndef COMPILADORES_TEXTILES_CFGHANDLER_H
#define COMPILADORES_TEXTILES_CFGHANDLER_H

/*
 * std::string grammar, std::string terminals, std::string non_terminals, std::string starti
   Ejemplo gramática: "A: 0 Number $ Number: 1 2 Number 2 1 | 0 $";

   std::string grammar = "lexp: atom | list $ atom: number | identifier $ list: ( lexpseq ) $ lexpseq: lexp lexpseq | lexp $";
   CFGHandler ff(grammar, "number identifier ( )", "lexp atom list lexpseq", "lexp");
   auto pair = ff.get_firsts_follows();
   ff.print();
 */

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <iostream>

using identifier_t = std::string;
struct Element_t{
    identifier_t id;
    bool is_ter;
};

using Map_Int_String_t = std::unordered_map<int , std::string>;
using Map_String_Int_t = std::unordered_map<std::string, int>;

using Production_t = std::vector<identifier_t>;
using Rule_t = std::vector<Production_t>;
using SetS_t = std::unordered_set<identifier_t>;
using SetInt_t = std::unordered_set<int>;
using MapSets_t = std::unordered_map<identifier_t , SetS_t>;
using Grammar_t = std::unordered_map<identifier_t , Rule_t>;

class Parser;

class CFGHandler {
    Grammar_t grammar;

    SetS_t terminals;
    SetS_t non_terminals;

    MapSets_t Firsts{}, Follows{};

    std::string initial;

    void read_grammar(std::string grammari);
    void read_elements(std::string elementsi, bool is_ter=true);
    void generate_firsts_follows();

public:
    CFGHandler (std::string grammar, std::string terminals, std::string non_terminals, std::string starti);
    inline Grammar_t get_grammar(){
        return grammar;
    };
    inline SetS_t get_terminals(){
        return terminals;
    };
    inline SetS_t get_non_terminals(){
        return non_terminals;
    };
    inline std::pair<MapSets_t, MapSets_t> get_firsts_follows() {
        return std::make_pair(Firsts, Follows);
    };
    void print();

    friend class Parser;
};



#endif //COMPILADORES_TEXTILES_CFGHANDLER_H
