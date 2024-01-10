#pragma once
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <string>

class Tiles;
class Possibilities {
    private:
        std::map<std::string, std::set<std::string>> _possibilitiesMap;
        std::set<std::string> _possibilities;
    public:
        Possibilities();
        Possibilities(std::string configPath);
        void setPossibilities(std::string &type);
        bool restrictPossibilities(std::vector<std::shared_ptr<Tiles>> neighbours);
        void calculatePossibilities(Possibilities &pos1, Possibilities &pos2);
        std::set<std::string> &getPossiblities();
};