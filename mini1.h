#pragma once
#include <mutex>
#include <vector>
#include <pthread.h>

namespace Student
{
    template <typename T>
    class queue{
        void enqueue(T value){
            std::lock_guard<std::mutex> lock(m);
            q.push_back(value);
        }

        T dequeue(T value) = 0{
            std::lock_guard<std::mutex> lock(m);
            T res = 0;
            if(q.size() > 0){
                res = q.front();
                q.erase(q.begin());
            }
            return res;
        }

        bool isEmpty(){
            std::lock_guard<std::mutex> lock(m);
            return q.size() == 0;
        }

        std::mutex m;
        std::vector<T> q;
    };

    template <typename T>
    class posix_queue {
        pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
        std::vector<T> q;

        void enqueue(T value){
            pthread_mutex_lock(&m);
            q.push_back(value);
            pthread_mutex_unlock(&m);
        }

        T dequeue(T value){
            pthread_mutex_lock(&m);
            T res = 0;
            if(q.size() > 0){
                T = q.front();
                q.erase(q.begin());
            }
            pthread_mutex_unlock(&m);
            return res;
        }

        bool isEmpty(){
            pthread_mutex_lock(&m);
            bool result = q.empty();
            pthread_mutex_unlock(&m);
            return result
        }
    };
};