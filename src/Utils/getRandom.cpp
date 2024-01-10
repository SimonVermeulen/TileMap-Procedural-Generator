#include <iostream>
#include <random>

int getRandomNumberBetween(int lower, int upper) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(lower, upper);

    return distrib(gen);
}
