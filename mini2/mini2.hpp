#include <iostream>
#include <thread>
#include <mpi.h>
#include "Coin.h"
#include "Thrower.h"

void threadFunction(Coin& coin) {
    coin.throwCoin();
    coin.flipResult();
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    Coin coin;
    Thrower thrower(coin);

    std::thread t1(threadFunction, std::ref(coin));
    std::thread t2(&Thrower::decideWinner, &thrower);

    t1.join();
    t2.join();

    MPI_Finalize();
    return 0;
}

