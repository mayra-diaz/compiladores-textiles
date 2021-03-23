#ifndef COMPILADORES_TEXTILES_FIRSTSANDFOLLOWS_H
#define COMPILADORES_TEXTILES_FIRSTSANDFOLLOWS_H

/*
 * terminals && non_terminals:
 * A B BK
 *
 * GRAMMAR:
 * E -> a A | O o
 */

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <tuple>

using Rule = std::vector<std::vector<std::string>>;
using SetString = std::unordered_set<std::string>;
using Sets = std::unordered_map<std::string, SetString>;

class FirstsAndFollows {
    std::unordered_map<std::string, Rule> grammar;
    SetString terminals;
    SetString non_terminals;

    std::string initial;

    void read_grammar(std::string grammari);
    static SetString read_elements(std::string elementsi);
public:
    FirstsAndFollows (std::string grammar, std::string terminals, std::string non_terminals, std::string starti);
    std::pair<Sets, Sets> generate_firsts_follows();
};



#endif //COMPILADORES_TEXTILES_FIRSTSANDFOLLOWS_H
