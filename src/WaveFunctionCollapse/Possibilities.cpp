#include "Possibilities.hpp"
#include "Tiles.hpp"

Possibilities::Possibilities() {
    std::map<std::string, std::set<std::string>> possibilities = {
        {"FOREST", {"FOREST", "GRASS"}},
        {"GRASS", {"SAND", "FOREST", "PATH", "MOUNTAIN"}},
        {"MOUNTAIN", {"GRASS", "MOUNTAIN"}},
        {"WATER", {"WATER", "SAND"}},
        {"SAND", {"WATER", "GRASS", "SAND"}},
        {"PATH", {"GRASS", "PATH"}}
    };
    this->_possibilitiesMap = possibilities;

    this->_possibilities.insert("FOREST");
    this->_possibilities.insert("GRASS");
    this->_possibilities.insert("MOUNTAIN");
    this->_possibilities.insert("WATER");
    this->_possibilities.insert("SAND");
    this->_possibilities.insert("PATH");
}

Possibilities::Possibilities(std::string configPath) {
    std::map<std::string, std::set<std::string>> possibilities = {
        {"FOREST", {"FOREST", "GRASS"}},
        {"GRASS", {"SAND", "FOREST", "PATH", "MOUNTAIN"}},
        {"MOUNTAIN", {"GRASS", "MOUNTAIN"}},
        {"WATER", {"WATER", "SAND"}},
        {"SAND", {"WATER", "GRASS", "SAND"}},
        {"PATH", {"GRASS", "FOREST", "PATH"}}
    };
    this->_possibilitiesMap = possibilities;

    this->_possibilities.insert("FOREST");
    this->_possibilities.insert("GRASS");
    this->_possibilities.insert("MOUNTAIN");
    this->_possibilities.insert("WATER");
    this->_possibilities.insert("SAND");
    this->_possibilities.insert("PATH");
}

void Possibilities::setPossibilities(std::string &type) {
    std::set<std::string> possibilitySet = this->_possibilitiesMap.at(type);

    this->_possibilities.clear();
    for (auto it = possibilitySet.begin(); it != possibilitySet.end(); ++it) {
        this->_possibilities.insert(*it);
    }
}

void Possibilities::calculatePossibilities(Possibilities &neighbour, Possibilities &pos2) {
    std::set<std::string> neighbourPos = neighbour.getPossiblities();
    std::set<std::string> allPos;

    for (auto it = neighbourPos.begin(); it != neighbourPos.end(); ++it) {
        std::set<std::string> posMap = this->_possibilitiesMap.at(*it);
        for (auto itMap = posMap.begin(); itMap != posMap.end(); ++itMap) {
            allPos.insert(*itMap);
        }
    }
    for (const auto& pair : this->_possibilitiesMap) {
        if (allPos.find(pair.first) == allPos.end())
            pos2.getPossiblities().erase(pair.first);
    }
}


bool Possibilities::restrictPossibilities(std::vector<std::shared_ptr<Tiles>> neighbours) {
    int size = this->_possibilities.size();

    for (int i = 0; i < neighbours.size(); i++) {
        Possibilities neighboursPoss = neighbours[i]->getPossiblities();
        this->calculatePossibilities(neighbours[i]->getPossiblities(), *this);
    }
    if (this->_possibilities.size() != size)
        return true;
    return false;
}

std::set<std::string> &Possibilities::getPossiblities() {
    return this->_possibilities;
}
