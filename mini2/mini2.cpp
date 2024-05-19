#include <iostream>
#include <thread>
#include <map>
#include <mpi.h>
#include <string>
#include "Coin.h"

#define loss_message "Sloužím ti, můj vládče, slunce naše jasné."
#define UCO 524659

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int process_Rank, size_Of_Cluster, message;
    int winner = 4;

    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    if (process_Rank == 0) {
        std::cout << UCO << std::endl;
    }

    Coin coin;
    std::map<int, int> state;

    do {
        for (int i = 0; i < size_Of_Cluster; i++) {
            message = -1;
            if (i == process_Rank) {
                coin.throwCoin();
                message = coin.result;
            }
            MPI_Bcast(&message, 1, MPI_INT, i, MPI_COMM_WORLD);
            state[i] = message;
        }

        int winner_count = 0;
        for (auto& [coin_id, side] : state) {
            if (side == 1) {
                winner = coin_id;
                winner_count++;
                break;
            }
        }

        if (winner_count == 0){
            continue;
        }
        if (winner_count == 1 || state[process_Rank] == 0){
            coin.active = false;
        }
        
    } while (coin.active);

    MPI_Barrier(MPI_COMM_WORLD);

    if (winner != process_Rank){
        std::cout << loss_message << " " << std::to_string(winner) << std::endl;
    }

    MPI_Finalize();
    return 0;
}