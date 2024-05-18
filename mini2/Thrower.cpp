#include "Thrower.h"

Thrower::Thrower(Coin& coin) : coin(coin) {}

void Thrower::decideWinner() {
    int result = coin.getResult();
    std::string winner = (result == 1) ? "Heads" : "Tails";
    coin.broadcastMessage("Winner: " + winner);
}
