#include "Coin.h"

void Coin::throwCoin() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    result = dis(gen);
}

bool Coin::finished(){
    MPI_Recv(message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    if (*message == 0){
        return true;
    }
}

int Coin::getResult() const{
    return result;
}
