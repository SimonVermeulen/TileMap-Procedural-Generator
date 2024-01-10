#pragma once
#include <vector>
#include "Tiles.hpp"

class World {
    private:
        Vector2I _size;
        std::vector<std::vector<std::shared_ptr<Tiles>>> _tiles;
        std::vector<Vector2I> _lowestEntropies;
        int _maxEntropy;
    public:
        World(int width, int height, int maxEntropy);
        Vector2I &getSize();
        std::vector<std::vector<std::shared_ptr<Tiles>>> &getTiles();
        void generate();
        void setState();
        std::vector<std::shared_ptr<Tiles>> getNeighbours(Vector2I &tileCoords);
        void updateNeighbours(std::shared_ptr<Tiles> currentTile);
        void setLowestEntropies();
        std::vector<Vector2I> &getLowestEntropies();
};