#include "fifo.h"

namespace lab3 {
    unsigned QUEUE_SIZE = 100;

    fifo::fifo() {
        // Reserve 100 spaces in fifo_storage
        fifo_storage.reserve(QUEUE_SIZE);

        front_index = 0;
        back_index = -1;
    }

    fifo::fifo(std::string input_string) : fifo() {
        enqueue(std::move(input_string));
    }

    fifo::fifo(const fifo &original) = default;

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
        return fifo_storage[front_index];
    }

    void fifo::enqueue(std::string input) {
        if (size() == QUEUE_SIZE) {
            throw std::runtime_error("cannot enqueue because queue is full");
        } else {
            fifo_storage.append(std::move(input));
            back_index++;
        }
    }

    void fifo::dequeue() {
        if (size() == 0) {
            throw std::runtime_error("cannot dequeue because queue is empty");
        } else {
            front_index++;
        }
    }
}