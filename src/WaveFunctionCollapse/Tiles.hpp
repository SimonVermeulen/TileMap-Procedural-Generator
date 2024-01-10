#pragma once
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Vector2I.hpp"
#include "Possibilities.hpp"

class Tiles {
    private:
        Possibilities _possibilities;
        std::string _type = "";
        Vector2I _coords;
    public:
        int _entropy = 1;
        Tiles();
        Tiles(int x, int y, int maxEntropy);
        Vector2I &getCoords();
        std::string &getType();
        int getEntropy();
        void setEntropy(int entropy);
        void setType(std::string type);
        Possibilities &getPossiblities();
};