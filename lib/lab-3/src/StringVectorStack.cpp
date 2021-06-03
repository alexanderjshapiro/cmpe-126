#include "StringVectorStack.h"

namespace lab3 {
    unsigned STACK_SIZE = 100;

    StringVectorStack::StringVectorStack() {
        stack.reserve(STACK_SIZE);
        topIndex = -1;
    }

    StringVectorStack::StringVectorStack(std::string string) : StringVectorStack() {
        push(std::move(string));
    }

    StringVectorStack::StringVectorStack(const StringVectorStack &other) : StringVectorStack() {
        *this = other;
    }

    std::string StringVectorStack::top() {
        return stack[topIndex];
    }

    unsigned StringVectorStack::size() const {
        return topIndex + 1;
    }

    bool StringVectorStack::empty() const {
        return size() == 0;
    }

    void StringVectorStack::push(std::string string) {
        if (size() == STACK_SIZE) throw std::runtime_error("cannot push because stack is full");
        else {
            // Hack: Append to stack to avoid problems with StringVector length validation
            stack.append("");

            stack[++topIndex] = std::move(string);
        }
    }

    void StringVectorStack::pop() {
        // Pseudo-pop by moving the top index back
        if (size() == 0) throw std::runtime_error("cannot pop because stack is empty");
        else topIndex--;
    }
}