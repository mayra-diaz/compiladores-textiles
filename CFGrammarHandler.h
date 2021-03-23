#ifndef COMPILADORES_TEXTILES_CFGRAMMARHANDLER_H
#define COMPILADORES_TEXTILES_CFGRAMMARHANDLER_H

/*
 * std::string grammar, std::string terminals, std::string non_terminals, std::string starti
   Ejemplo gramática: "A: 0 Number $ Number: 1 2 Number 2 1 | 0 $";

   std::string grammar = "lexp: atom | list $ atom: number | identifier $ list: ( lexpseq ) $ lexpseq: lexp lexpseq | lexp $";
   CFGrammarHandler ff(grammar, "number identifier ( )", "lexp atom list lexpseq", "lexp");
   auto pair = ff.get_firsts_follows();
   ff.print();
 */

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <iostream>

using Rule_t = std::vector<std::vector<std::string>>;
using SetString_t = std::unordered_set<std::string>;
using MapSets_t = std::unordered_map<std::string, SetString_t>;
using Grammar_t = std::unordered_map<std::string, Rule_t>;

class CFGrammarHandler {
    Grammar_t grammar;
    SetString_t terminals;
    SetString_t non_terminals;
    MapSets_t Firsts{}, Follows{};

    std::string initial;

    void read_grammar(std::string grammari);
    static SetString_t read_elements(std::string elementsi);
    void generate_firsts_follows();
public:
    CFGrammarHandler (std::string grammar, std::string terminals, std::string non_terminals, std::string starti);
    inline Grammar_t get_grammar(){
        return grammar;
    };
    inline SetString_t get_terminals(){
        return terminals;
    };
    inline SetString_t get_non_terminals(){
        return non_terminals;
    };
    inline std::pair<MapSets_t, MapSets_t> get_firsts_follows() {
        return std::make_pair(Firsts, Follows);
    };
    void print();
};



#endif //COMPILADORES_TEXTILES_CFGRAMMARHANDLER_H
