#include "Coin.h"
#include <iostream>
#include <random>
#include <mpi.h>

void Coin::throwCoin() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    result = dis(gen);
}
