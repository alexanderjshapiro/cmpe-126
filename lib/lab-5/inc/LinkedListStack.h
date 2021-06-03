#ifndef LINKEDLISTSTACK_H
#define LINKEDLISTSTACK_H

#include "LinkedList.h"

namespace lab5 {
    class LinkedListStack {
    private:
        LinkedList storage_structure;

    public:
        LinkedListStack() = default;
        explicit LinkedListStack(std::string &string);
        LinkedListStack(const LinkedListStack &other) = default;
        LinkedListStack &operator=(const LinkedListStack &other) = default;
        virtual ~LinkedListStack() = default;

        std::string top() const;
        unsigned size() const;
        bool empty() const;

        void push(const std::string &string);
        void pop();

        friend std::istream &operator>>(std::istream &stream, LinkedListStack &linkedListStack);
        friend std::ostream &operator<<(std::ostream &stream, LinkedListStack &linkedListStack);
    };
}
#endif // LINKEDLISTSTACK_H