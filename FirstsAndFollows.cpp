#include "FirstsAndFollows.h"

#include <utility>


FirstsAndFollows::FirstsAndFollows(std::string grammari, std::string terminalsi, std::string non_terminalsi,
                                   std::string starti): initial(std::move(starti)){
    read_grammar(std::move(grammari));
    terminals = read_elements(std::move(terminalsi));
    non_terminals = read_elements(std::move(non_terminalsi));
}

void FirstsAndFollows::read_grammar(std::string grammari) {
    int i = 0;
    std::string current_rule;
    while (i < grammari.size()){
        current_rule = "";
        while (grammari[i] != ' ')
            current_rule.push_back(grammari[i++]);
        grammar.insert({current_rule, Rule()});
        do {
            ++i;
        } while (grammari[i] != ':');
        ++i;
        while (grammari[i] != '\n') {
            std::vector<std::string> production;
            while (grammari[i] != '|') {
                std::string current;
                while (grammari[i] != ' ')
                    current.push_back(grammari[i++]);
                production.push_back(current);
                while (grammari[i] == ' ')
                    ++i;
            }
            grammar[current_rule].push_back(production);
        }
    }
}

SetString FirstsAndFollows::read_elements(std::string elementsi){
    int i=0;
    SetString elements;
    while (i < elementsi.size()){
        if (elementsi[i] == ' ')
            ++i;
        else {
            std::string element;
            while (elementsi[i] == ' ')
                element.push_back(elementsi[i]);
            elements.insert(element);
        }
    }
    return elements;
}

std::pair<Sets, Sets> FirstsAndFollows::generate_firsts_follows(){
    Sets Firsts, Follows;
    for (const auto& nterminal: non_terminals){
        SetString firsts;
        for (auto production: grammar[nterminal]){
            if (terminals.find(production[0]) != terminals.end())
                firsts.insert(production[0]);
        }
        Firsts.insert({nterminal, firsts});
    }

    for (const auto& nterminal: non_terminals)
        Follows.insert({nterminal, SetString()});
    Follows[initial].insert("$");

    int changes = 1;
    while (changes != 0) {
        changes = 0;
        for (const auto &nterminal: non_terminals) {
            for (auto production: grammar[nterminal]) {
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
    return std::make_pair(Firsts, Follows);
}