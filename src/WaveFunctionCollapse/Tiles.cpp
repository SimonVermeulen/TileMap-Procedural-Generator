#include "Tiles.hpp"
#include <iostream>

Tiles::Tiles() {
    this->_coords = Vector2I(0, 0);
}

Tiles::Tiles(int x, int y, int maxEntropy) {
    this->_coords = Vector2I(x, y);
    this->_entropy = maxEntropy;
}

Vector2I &Tiles::getCoords() {
    return this->_coords;
}

std::string &Tiles::getType() {
    return this->_type;
}

int Tiles::getEntropy() {
    return this->_entropy;
}

void Tiles::setEntropy(int entropy) {
    this->_entropy = entropy;
}

void Tiles::setType(std::string type) {
    this->_type = type;
}

Possibilities &Tiles::getPossiblities() {
    return this->_possibilities;
}
