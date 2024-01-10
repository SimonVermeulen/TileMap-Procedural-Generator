#include <iostream>
#include <random>
#include <vector>

struct WeightedChoice {
    std::string value;
    int weight;
};

std::string weightedRandom(std::vector<WeightedChoice> choices) {
    int totalWeight = 0;
    for (const auto& choice : choices) {
        totalWeight += choice.weight;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, totalWeight);

    int rnd = dis(gen);

    int currentWeight = 0;
    for (const auto& choice : choices) {
        currentWeight += choice.weight;
        if (rnd <= currentWeight) {
            return choice.value;
        }
    }
    return choices[0].value;
}