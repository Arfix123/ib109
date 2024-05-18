#pragma once
#include <optional>
#include <iostream>
#include <chrono>
#include <thread>

# define TEST_SIZE 50000

template <typename T>
struct Queue {
    virtual void enqueue(T value) = 0;
    virtual std::optional<T> dequeue() = 0;
    virtual bool isEmpty() = 0;
};

// Function to manipulate the queue
template <typename T, bool delay = false>
void manipulate_queue(Queue<T>* queue){
    int i = 1;
    for(; i <= TEST_SIZE; i+=5){
        if (delay) {
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
        queue->enqueue(i);
        queue->enqueue(i+1);
        queue->enqueue(i+2);
        queue->enqueue(i+3);
        queue->enqueue(i+4);
    }
}