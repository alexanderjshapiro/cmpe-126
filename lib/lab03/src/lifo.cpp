#include "lifo.h"

namespace lab3 {
    unsigned STACK_SIZE = 100;

    lifo::lifo() {
        // Reserve 100 spaces in lifo_storage
        lifo_storage.reserve(STACK_SIZE);

        index = -1;
    }

    lifo::lifo(std::string input_string) : lifo() {
        push(std::move(input_string));
    }

    lifo::lifo(const lifo &original) = default;

    // lifo_storage is deleted by stringVector when this goes out of scope
    lifo::~lifo() = default;

    lifo &lifo::operator=(const lifo &right) = default;

    bool lifo::is_empty() {
        return size() == 0;
    }

    int lifo::size() {
        return index + 1;
    }

    std::string lifo::top() {
        return lifo_storage[index];
    }

    void lifo::push(std::string input) {
        if (size() == STACK_SIZE) {
            throw std::runtime_error("cannot push because stack is full");
        } else {
            lifo_storage.append(std::move(input));
            index++;
        }
    }

    void lifo::pop() {
        if (size() == 0) {
            throw std::runtime_error("cannot pop because stack is empty");
        } else {
            index--;
        }
    }
}