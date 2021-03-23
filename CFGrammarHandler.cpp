#include "CFGrammarHandler.h"

CFGrammarHandler::CFGrammarHandler(std::string grammari, std::string terminalsi, std::string non_terminalsi,
                                   std::string starti): initial(std::move(starti)){
    read_grammar(grammari);
    terminals = read_elements(std::move(terminalsi));
    non_terminals = read_elements(std::move(non_terminalsi));
    generate_firsts_follows();
}

void CFGrammarHandler::read_grammar(std::string grammari) {
    int i = 0;
    std::string current_rule;
    while (i < grammari.size()){
        current_rule = "";
        while (grammari[i] != ':')
            current_rule.push_back(grammari[i++]);
        grammar.insert({current_rule, Rule_t()});
        i += 2;
        std::vector<std::string> production;
        while (grammari[i] != '$' && i < grammari.size()) {
            if (grammari[i]=='|') {
                i += 2;
                grammar[current_rule].push_back(production);
                production.clear();
            }
            std::string current;
            while (grammari[i] != ' ' && i < grammari.size())
                current.push_back(grammari[i++]);
            production.push_back(current);
            while (grammari[i] == ' ' && i < grammari.size())
                ++i;
        }
        grammar[current_rule].push_back(production);
        i+=2;
    }
}

SetString_t CFGrammarHandler::read_elements(std::string elementsi){
    int i=0;
    SetString_t elements;
    while (i < elementsi.size()){
        if (elementsi[i] == ' ')
            ++i;
        else {
            std::string element;
            while (elementsi[i] != ' ' && i < elementsi.size())
                element.push_back(elementsi[i++]);
            elements.insert(element);
        }
    }
    return elements;
}

void CFGrammarHandler::generate_firsts_follows(){
    for (const auto& nterminal: non_terminals)
        Firsts.insert({nterminal, SetString_t()});
    for (const auto& nterminal: non_terminals)
        Follows.insert({nterminal, SetString_t()});
    Follows[initial].insert("$");

    int changes = 1;
    while (changes != 0) {
        changes = 0;
        for (auto rule: grammar){
            for (auto production: rule.second){
                if (terminals.find(production[0]) != terminals.end()) {
                    if (Firsts[rule.first].find(production[0]) == Firsts[rule.first].end()) {
                        Firsts[rule.first].insert(production[0]);
                        ++changes;
                    }
                }
                else {
                    for (const auto &first: Firsts[production[0]]){
                        if (Firsts[rule.first].find(first) == Firsts[rule.first].end()){
                            Firsts[rule.first].insert(first);
                            ++changes;
                        }
                    }
                }
            }
        }
    }

    changes = 1;
    while (changes != 0) {
        changes = 0;
        for (const auto &nterminal: non_terminals) {
            for (auto &production: grammar[nterminal]) {
                for (int i = 0; i < production.size()-1; ++i) {
                    auto next = production[i + 1];
                    auto current = production[i];
                    if (terminals.find(next) != terminals.end()) {
                        if (Follows[current].find(next) == Follows[current].end()) {
                            Follows[current].insert(next);
                            changes++;
                        }
                    }
                    else {
                        for (const auto& t: Firsts[next]){
                            if (Follows[current].find(t) == Follows[current].end()) {
                                Follows[current].insert(t);
                                changes++;
                            }
                        }
                    }
                }
                auto last = production[production.size()-1];
                if (non_terminals.find(last) != non_terminals.end()){
                    for (const auto& t: Follows[nterminal]){
                        if (Follows[last].find(t) == Follows[last].end()) {
                            Follows[last].insert(t);
                            changes++;
                        }
                    }
                }
            }
        }
    }
}

void CFGrammarHandler::print() {
    std::cout << "GRAMMAR\n";
    for (auto x: grammar){
        std::cout << x.first << " --> \t";
        for (auto v: x.second) {
            for (auto v1: v)
                std::cout << v1 << ' ';
            std::cout << "\t|\t";
        }
        std::cout << '\n';
    }
    std::cout << "\nTERMINALS\n";
    for (auto t: terminals)
        std::cout << t << ' ';
    std::cout << "\nNON-TERMINALS\n";
    for (auto n: non_terminals)
        std::cout << n << ' ';
    std::cout << "\n\nFIRSTS\n";
    for (auto x: Firsts){
        std::cout << x.first << ":\t";
        for (auto v: x.second)
            std::cout << v << ' ';
        std::cout << '\n';
    }
    std::cout << "FOLLOWS\n";
    for (auto x: Follows){
        std::cout << x.first << ":\t";
        for (auto v: x.second)
            std::cout << v << ' ';
        std::cout << '\n';
    }

}