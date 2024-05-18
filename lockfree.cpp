#include <atomic>
#include <iostream>
#include <memory>
#include <optional>
#include <thread>
#include "queue.h"

// Implementation based on the paper "Simple, Fast, and Practical Non-Blocking and Blocking Concurrent Queue Algorithms"
template <typename T>
class LockFreeQueue : public Queue<T> {
private:
    struct Node {
        T data;
        std::atomic<Node*> next;
        
        Node(T value) : data(value), next(nullptr) {}
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;

public:
    LockFreeQueue() {
        Node* dummy = new Node(T{}); // Create a dummy node
        head.store(dummy);
        tail.store(dummy);
    }

    ~LockFreeQueue() {
        while (dequeue().has_value()); // Dequeue all elements to clean up
        Node* dummy = head.load();
        delete dummy; // Delete the last dummy node
    }

    void enqueue(T value) override {
        Node* newNode = new Node(value);
        Node* oldTail;
        while (true) {
            oldTail = tail.load();
            Node* tailNext = oldTail->next.load();
            if (oldTail == tail.load()) {
                if (tailNext == nullptr) {
                    if (oldTail->next.compare_exchange_weak(tailNext, newNode)) {
                        break;
                    }
                } else {
                    tail.compare_exchange_weak(oldTail, tailNext);
                }
            }
        }
        tail.compare_exchange_weak(oldTail, newNode);
    }

    std::optional<T> dequeue() override {
        Node* oldHead;
        Node* nextNode;
        while (true) {
            oldHead = head.load();
            Node* oldTail = tail.load();
            nextNode = oldHead->next.load();
            if (oldHead == head.load()) {
                if (oldHead == oldTail) {
                    if (nextNode == nullptr) {
                        return std::nullopt; // Queue is empty
                    }
                    tail.compare_exchange_weak(oldTail, nextNode);
                } else {
                    if (head.compare_exchange_weak(oldHead, nextNode)) {
                        break;
                    }
                }
            }
        }
        T value = nextNode->data;
        delete oldHead;
        return value;
    }

    bool isEmpty() override {
        Node* oldHead = head.load();
        Node* nextNode = oldHead->next.load();
        return nextNode == nullptr;
    }
};

int main() {
    LockFreeQueue<int> queue;

    // Create 3 threads to manipulate the queue
    std::thread t1(manipulate_queue<int>, &queue);
    std::thread t2(manipulate_queue<int>, &queue);

    // Wait for all threads to finish
    t1.join();
    t2.join();

    std::cout << "All threads finished execution." << std::endl;
    std::cout << "==============================" << std::endl;
    while (!queue.isEmpty()) {
        auto val = queue.dequeue();
        if (val.has_value()) {
            std::cout << "Dequeued: " << val.value() << std::endl;
        }
    }

    return 0;
}