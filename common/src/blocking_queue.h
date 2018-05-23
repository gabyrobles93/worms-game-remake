#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

#include <mutex>
#include <condition_variable>
#include <queue>

template <typename T>
class Queue {
    private:
        std::queue<T> q;
	    const unsigned int max_size;
        std::mutex mtx;
        std::condition_variable is_not_full;
        std::condition_variable is_not_empty;

        Queue(const Queue&) = delete;
        Queue& operator=(const Queue&) = delete;

    public:
        Queue(const unsigned int ms) : max_size(ms) {};

        void push(const T & val) {
            std::unique_lock<std::mutex> lck(mtx);
            if (q.empty()) {
                is_not_empty.notify_all();
            }

            while (q.size() >= this->max_size) {
                is_not_full.wait(lck);
            }

            q.push(val);           
        }

        T pop(void) {
            std::unique_lock<std::mutex> lck(mtx);

            while (q.empty()) {
                is_not_empty.wait(lck);
            }

            const T val = q.front();
            q.pop();
            is_not_full.notify_all();

            return val;            
        }
};

#endif