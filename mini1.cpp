#include "mini1.h"
#include "queue.h"
#include <chrono>
#include <iostream>
#include <thread>

#define UCO 524659
/*
aplikace vypíše na konzolu právě 2 řádky

    na 1. prvním řádku Vaše učo
    na 2. druhém řádku jedno celé číslo, které vyjadřuje kolik procent času POSIXového řešení zabralo Lock-Free řešení
    (tj. bude-li Lock-Free přístup o pětinu rychlejší, vypíše se 80, pokud o pětinu pomalejší, vypíše se 120)
*/

int main(int argc, const char** argv) {
    LockFreeQueue<int> lock_free_queue;
    PosixQueue<int> posix_queue;

    std::cout << UCO << std::endl;

    // Measure time for free_lock_queue
    auto start_lock_free = std::chrono::high_resolution_clock::now();
    std::thread t1(manipulate_queue<int>, &lock_free_queue);
    std::thread t2(manipulate_queue<int>, &lock_free_queue);
    std::thread t3(manipulate_queue<int>, &lock_free_queue);
    auto end_lock_free = std::chrono::high_resolution_clock::now();
    auto duration_lock_free = std::chrono::duration_cast<std::chrono::milliseconds>(end_lock_free - start_lock_free).count();
    std::cout << "Lock-free time: " << duration_lock_free << " ms" << std::endl;

    // Measure time for posix_queue
    auto start_posix = std::chrono::high_resolution_clock::now();
    std::thread t1(manipulate_queue<int>, &posix_queue);
    std::thread t2(manipulate_queue<int>, &posix_queue);
    std::thread t3(manipulate_queue<int>, &posix_queue);
    auto end_posix = std::chrono::high_resolution_clock::now();
    auto duration_posix = std::chrono::duration_cast<std::chrono::milliseconds>(end_posix - start_posix).count();
    std::cout << "POSIX time: " << duration_posix << " ms" << std::endl;

    return 0;
}