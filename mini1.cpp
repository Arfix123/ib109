#include "mini1.h"
#include <iostream>
#include <chrono>

// Function to manipulate the queue
template <typename Queue>
void manipulate_queue(Queue& queue){
    for(int i = 0; i < 1000000; i+=5){
        queue.enqueue(i);
        queue.enqueue(i+1);
        queue.enqueue(i+2);
        queue.enqueue(i+3);
        int discard = queue.dequeue();
    }
}

int main(int argc, const char** argv) {
    // Volatile keyword is removed because it's unnecessary for this context
    Student::queue<int> free_lock_queue;
    Student::posix_queue<int> posix_queue;

    // Measure time for free_lock_queue
    auto start_free_lock = std::chrono::high_resolution_clock::now();
    manipulate_queue(free_lock_queue);
    auto end_free_lock = std::chrono::high_resolution_clock::now();
    auto duration_free_lock = std::chrono::duration_cast<std::chrono::milliseconds>(end_free_lock - start_free_lock).count();
    std::cout << "Free-lock queue manipulation time: " << duration_free_lock << " ms" << std::endl;

    // Measure time for posix_queue
    auto start_posix = std::chrono::high_resolution_clock::now();
    manipulate_queue(posix_queue);
    auto end_posix = std::chrono::high_resolution_clock::now();
    auto duration_posix = std::chrono::duration_cast<std::chrono::milliseconds>(end_posix - start_posix).count();
    std::cout << "POSIX queue manipulation time: " << duration_posix << " ms" << std::endl;

    return 0;
}