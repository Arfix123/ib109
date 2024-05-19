#include <iostream>
#include <thread>
#include <map>
#include <mpi.h>
#include "Coin.h"

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int process_Rank, size_Of_Cluster, message;

    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    std::cout << "Process " << process_Rank << " of " << size_Of_Cluster << " is running." << std::endl;

    if (process_Rank == 0){
        Coin favorite_coin(&message);
        std::map<int, int> results;
        bool favorite_is_active = true;

        do {
            bool round_has_winner = false;
            if (favorite_is_active){
                favorite_coin.throwCoin();
                if (favorite_coin.getResult() == 1){
                    round_has_winner = true;
                }
            }
            for (int i = 1; i < size_Of_Cluster; i++){
                MPI_Recv(&message, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if (message == 1) {
                    round_has_winner = true;
                    break;
                }
                results[i] = message;
            }

            if (round_has_winner){
                if (favorite_is_active){
                    if (favorite_coin.getResult() == 0){
                        favorite_is_active = false;
                    }
                }
                else {
                    std::cout << "Favorite lost!" << std::endl;
                    break;
                }

            }
            else {
                for (int i = 1; i < size_Of_Cluster; i++){
                    message = 1;
                    MPI_Send(&message, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                }
            }





        } while (true);
    }
    else {
        Coin me(&message);
        do {
            me.throwCoin();
            message = me.getResult();
            MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        } while (!me.finished());

        MPI_Barrier(MPI_COMM_WORLD);
        if (me.getResult() == 0){
            std::cout << loss_message << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}