#ifndef THROWER_H
#define THROWER_H

#include "Coin.h"

class Thrower {
public:
    Thrower(Coin& coin);
    void decideWinner();

private:
    Coin& coin;
};

#endif // THROWER_H
