#pragma once

class Coin {
public:
    Coin() : result(0) {}
    void throwCoin();

public:
    int result;
    bool active = true;
};
