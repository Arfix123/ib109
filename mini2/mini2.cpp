#include <iostream>
#include <thread>
#include <mpi.h>
#include "Coin.h"
#include "Thrower.h"

#define COIN_COUNT 6

void threadFunction(Coin& coin) {
    coin.throwCoin();
    coin.flipResult();
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int process_Rank, size_Of_Cluster;

    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);
    
    
    Coin coin;
    Thrower thrower(coin);

    std::thread t1(threadFunction, std::ref(coin));
    std::thread t2(&Thrower::decideWinner, &thrower);

    t1.join();
    t2.join();

    MPI_Finalize();
    return 0;
}