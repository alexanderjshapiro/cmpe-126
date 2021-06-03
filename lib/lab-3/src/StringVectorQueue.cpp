#include "StringVectorQueue.h"

namespace lab3 {
    unsigned QUEUE_SIZE = 100;

    StringVectorQueue::StringVectorQueue() {
        queue.reserve(QUEUE_SIZE);
        frontIndex = 0;
        backIndex = -1;
    }

    StringVectorQueue::StringVectorQueue(std::string string) : StringVectorQueue() {
        enqueue(std::move(string));
    }

    StringVectorQueue::StringVectorQueue(const StringVectorQueue &other) : StringVectorQueue() {
        *this = other;
    }

    std::string StringVectorQueue::front() const {
        if (empty()) throw std::runtime_error("cannot get front because StringVectorQueue is empty");
        else return queue[frontIndex % 100];
    }

    unsigned StringVectorQueue::size() const {
        return backIndex - frontIndex + 1;
    }

    bool StringVectorQueue::empty() const {
        return size() == 0;
    }

    void StringVectorQueue::enqueue(std::string string) {
        if (size() == QUEUE_SIZE) { throw std::runtime_error("cannot enqueue because StringVectorQueue is full");
        } else {
            // Hack: Append to StringVectorQueue to avoid problems with StringVector length validation
            queue.append("");

            queue[++backIndex % 100] = std::move(string);
        }
    }

    void StringVectorQueue::dequeue() {
        // Pseudo-dequeue by moving the front index forward
        if (empty()) throw std::runtime_error("cannot dequeue because StringVectorQueue is empty");
        else frontIndex++;
    }
}