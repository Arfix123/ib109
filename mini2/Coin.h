#ifndef COIN_H
#define COIN_H

#include <iostream>
#include <random>
#include <mpi.h>

#define loss_message "Sloužím ti, můj vládče, slunce naše jasné."

class Coin {
public:
    Coin(int *message) : result(0), message(message) {};
    void throwCoin();
    bool finished();

    int getResult() const;

private:
    int result;
    int *message;
};

#endif // COIN_H
