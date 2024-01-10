#include <iostream>
#include "World.hpp"

int getRandomNumberBetween(int lower, int upper);
std::string &getIndexSet(std::set<std::string> set, int index);

World::World(int width, int height, int maxEntropy) {
    this->_size = Vector2I(width, height);
    this->_maxEntropy = maxEntropy;

    this->_tiles.resize(height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            this->_tiles[y].push_back(std::make_shared<Tiles>(x, y, maxEntropy));
        }
    }
}

Vector2I &World::getSize() {
    return this->_size;
}

std::vector<std::vector<std::shared_ptr<Tiles>>> &World::getTiles() {
    return this->_tiles;
}

void World::setLowestEntropies() {
    int lowestEntropy = this->_maxEntropy;
    this->_lowestEntropies.clear();

    for (int y = 0; y < this->_size.getY(); y++) {
        for (int x = 0; x < this->_size.getX(); x++) {
            int currentEntropy = this->_tiles[y][x]->_entropy;

            if (currentEntropy < lowestEntropy && currentEntropy != -1) {
                lowestEntropy = currentEntropy;
                this->_lowestEntropies.clear();
            }
            if (currentEntropy == lowestEntropy) {
                this->_lowestEntropies.push_back(Vector2I(x, y));
            }
        }
    }
}

void World::generate() {
    this->setLowestEntropies();
    if (_lowestEntropies.size() == 0)
        return;
    this->setState();
    this->setLowestEntropies();
}

void World::setState() {
    int index = getRandomNumberBetween(0, this->_lowestEntropies.size() - 1);
    Vector2I tileCoords = this->_lowestEntropies[index];
    std::shared_ptr<Tiles> tile = this->_tiles[tileCoords.getY()][tileCoords.getX()];
    Possibilities *tilePossibilities = &tile->getPossiblities();
    int typeIndex = getRandomNumberBetween(0, tilePossibilities->getPossiblities().size() - 1);

    tile->setEntropy(-1);
    tile->setType(getIndexSet(tilePossibilities->getPossiblities(), typeIndex));
    tilePossibilities->setPossibilities(tile->getType());
    tilePossibilities->getPossiblities().clear();
    tilePossibilities->getPossiblities().insert(tile->getType());

    this->updateNeighbours(tile);
}

std::vector<std::shared_ptr<Tiles>> World::getNeighbours(Vector2I &tileCoords) {
    std::vector<std::shared_ptr<Tiles>> neighbours;
    int x = tileCoords.getX();
    int y = tileCoords.getY();

    if (tileCoords.getY() > 0)
        neighbours.push_back(this->getTiles()[y - 1][x]);
    if (tileCoords.getY() < this->getSize().getY() - 1)
        neighbours.push_back(this->getTiles()[y + 1][x]);
    if (tileCoords.getX() > 0)
        neighbours.push_back(this->getTiles()[y][x - 1]);
    if (tileCoords.getX() < this->getSize().getX() - 1)
        neighbours.push_back(this->getTiles()[y][x + 1]);

    return neighbours;
}

void World::updateNeighbours(std::shared_ptr<Tiles> currentTile) {
    std::vector<std::shared_ptr<Tiles>> neighbours = this->getNeighbours(currentTile->getCoords());
    bool test = true;

    for (int i = 0; i < neighbours.size(); i++) {
        test = neighbours[i]->getPossiblities().restrictPossibilities(this->getNeighbours(neighbours[i]->getCoords()));
        if (neighbours[i]->_entropy != -1)
            neighbours[i]->_entropy = neighbours[i]->getPossiblities().getPossiblities().size();
        if (test)
            updateNeighbours(neighbours[i]);
    }
}

std::vector<Vector2I> &World::getLowestEntropies() {
    return this->_lowestEntropies;
}
