#pragma once
#include <optional>
#include <iostream>
#include <chrono>

template <typename T>
struct Queue {
    virtual void enqueue(T value) = 0;
    virtual std::optional<T> dequeue() = 0;
    virtual bool isEmpty() = 0;
};

// Function to manipulate the queue
template <typename T>
void manipulate_queue(Queue<T>* queue){
    int i = 1;
    for(; i <= 10000; i+=5){
        std::cout << "Enqueueing: " << i << std::endl;
        queue->enqueue(i);
        std::cout << "Enqueueing: " << i+1 << std::endl;
        queue->enqueue(i+1);
        std::cout << "Enqueueing: " << i+2 << std::endl;
        queue->enqueue(i+2);
        std::cout << "Enqueueing: " << i+3 << std::endl;
        queue->enqueue(i+3);
        std::cout << "Enqueueing: " << i+4 << std::endl;
        queue->enqueue(i+4);
    }
    std::cout << "Last value: " << i << std::endl;
}