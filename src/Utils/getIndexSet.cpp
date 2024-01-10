#include <iostream>
#include <set>

std::string &getIndexSet(std::set<std::string> set, int index) {
    auto it = set.begin();
    std::advance(it, index);
    return const_cast<std::string&>(*it);
}
