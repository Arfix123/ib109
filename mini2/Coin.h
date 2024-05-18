#ifndef COIN_H
#define COIN_H

#include <iostream>
#include <mutex>
#include <random>
#include <mpi.h>

class Coin {
public:
    Coin();
    void throwCoin();
    void flipResult();
    void receiveMessage(int* buffer, int source, int tag);
    void broadcastMessage(const std::string& message);

    int getResult();

private:
    int result;
    std::mutex mtx;
};

#endif // COIN_H
