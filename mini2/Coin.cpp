#include "Coin.h"

Coin::Coin() : result(0) {}

void Coin::throwCoin() {
    std::lock_guard<std::mutex> lock(mtx);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    result = dis(gen);
}

void Coin::flipResult() {
    std::lock_guard<std::mutex> lock(mtx);
    result = 1 - result;
}

void Coin::receiveMessage(int* buffer, int source, int tag) {
    MPI_Recv(buffer, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::lock_guard<std::mutex> lock(mtx);
    result = buffer[0];
}

void Coin::broadcastMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << message << std::endl;
}

int Coin::getResult() {
    std::lock_guard<std::mutex> lock(mtx);
    return result;
}
