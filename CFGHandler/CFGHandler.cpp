#include "CFGHandler.h"

#include <utility>

CFGHandler::CFGHandler(std::string grammari, std::string terminalsi, std::string non_terminalsi,
                       std::string starti): initial(std::move(starti)){
    read_grammar(std::move(grammari));
    read_elements(std::move(terminalsi));
    read_elements(std::move(non_terminalsi), false);
    generate_firsts_follows();
}

void CFGHandler::read_grammar(std::string grammari) {
    int i = 0;
    while (i < grammari.size()){
        std::string current_rule;
        while (grammari[i] != ':')
            current_rule.push_back(grammari[i++]);
        grammar.insert({current_rule, Rule_t()});
        i += 2;
        Production_t production;
        while (grammari[i] != '$' && i < grammari.size())  {
            if (grammari[i]=='|') {
                i += 2;
                grammar[current_rule].push_back(production);
                production.clear();
            }
            std::string current;
            while (grammari[i] != ' ' && i < grammari.size())
                current.push_back(grammari[i++]);
           production.push_back(current) ;
            while (grammari[i] == ' ' && i < grammari.size())
                ++i;
        }
        grammar[current_rule].push_back(production);
        i+=2;
    }
}

void CFGHandler::read_elements(std::string elementsi, bool is_ter){
    int i=0;
    SetS_t *elements;
    if (is_ter)
        elements = &terminals;
    else
        elements = &non_terminals;

    while (i < elementsi.size()){
        if (elementsi[i] == ' ')
            ++i;
        else {
            std::string element;
            while (elementsi[i] != ' ' && i < elementsi.size())
                element.push_back(elementsi[i++]);
            elements->insert(element);
        }
    }
}

void CFGHandler::generate_firsts_follows(){
    for (const auto& nterminal: non_terminals)
        Firsts.insert({nterminal, SetS_t()});
    for (const auto& nterminal: non_terminals)
        Follows.insert({nterminal, SetS_t()});
    Follows[initial].insert("$");

    int changes = 1;
    while (changes != 0) {
        changes = 0;
        for (const auto& rule: grammar){
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
        for (const auto& rule: grammar){
            for (auto production: rule.second){
                for (int i = 0; i < production.size()-1; ++i) {
                    if (non_terminals.find(production[i]) != non_terminals.end()) {
                        auto next = production[i + 1];
                        auto current = production[i];
                        if (terminals.find(next) != terminals.end()) {
                            if (Follows[current].find(next) == Follows[current].end()) {
                                Follows[current].insert(next);
                                changes++;
                            }
                        } else {
                            for (const auto &t: Firsts[next]) {
                                if (Follows[current].find(t) == Follows[current].end()) {
                                    Follows[current].insert(t);
                                    changes++;
                                }
                            }
                        }
                    }
                }
                if (non_terminals.find(production[production.size()-1]) != non_terminals.end()) {
                    auto last = production[production.size() - 1];
                    if (non_terminals.find(last) != non_terminals.end()) {
                        for (const auto &t: Follows[rule.first]) {
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
}

void CFGHandler::print() {
    std::cout << "GRAMMAR\n";
    for (auto x: grammar){
        std::cout << x.first << " -->  ";
        for (auto v: x.second) {
            for (auto v1: v)
                std::cout << v1 << ' ';
            std::cout << "  |  ";
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
        std::cout << x.first << ":  ";
        for (auto v: x.second)
            std::cout << v << ' ';
        std::cout << '\n';
    }
    std::cout << "FOLLOWS\n";
    for (auto x: Follows){
        std::cout << x.first << ":  ";
        for (auto v: x.second)
            std::cout << v << ' ';
        std::cout << '\n';
    }
}