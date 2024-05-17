#include "mini1.h"
#include <iostream>
#include <chrono>

void manipulate_queue(auto queue){
    for(int i = 0; i < 1000000; i+=5){
        queue.enqueue(i);
        queue.enqueue(i+1);
        queue.enqueue(i+2);
        queue.enqueue(i+3);
        int discard = queue.dequeue();
    }
}

int main(int argc, const char** argv) {
    volatile Student::queue<int> free_lock_queue;
    volatile Student::posix_queue<int> posix_queue;

    
}