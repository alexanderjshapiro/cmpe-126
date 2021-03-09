#include "fifo.h"

#include <utility>

namespace lab3 {
    unsigned QUEUE_SIZE = 100;

    fifo::fifo() {
        // Reserve 100 spaces in fifo_storage
        fifo_storage.reserve(QUEUE_SIZE);

        // Hack: Append to lifo_storage to avoid problems with stringVector length validation
        for (int i = 0; i < QUEUE_SIZE; i++) {
            fifo_storage.append("");
        }

        front_index = 0;
        back_index = -1;
    }

    fifo::fifo(std::string input_string) : fifo() {
        enqueue(std::move(input_string));
    }

    fifo::fifo(const fifo &original) {
        *this = original;
    }

    // fifo_storage is deleted by stringVector when this goes out of scope
    fifo::~fifo() = default;

    fifo &fifo::operator=(const fifo &right) = default;

    bool fifo::is_empty() {
        return size() == 0;
    }

    int fifo::size() {
        return back_index - front_index + 1;
    }

    std::string fifo::top() {
        if (is_empty()) {
            throw std::runtime_error("cannot get top because queue is empty");
        } else {
            return fifo_storage[front_index % 100];
        }
    }

    void fifo::enqueue(std::string input) {
        if (size() == QUEUE_SIZE) {
            throw std::runtime_error("cannot enqueue because queue is full");
        } else {
            fifo_storage[++back_index % 100] = std::move(input);
        }
    }

    void fifo::dequeue() {
        if (is_empty()) {
            throw std::runtime_error("cannot dequeue because queue is empty");
        } else {
            front_index++;
        }
    }
}