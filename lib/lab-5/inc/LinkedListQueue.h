#ifndef LINKEDLISTQUEUE_H
#define LINKEDLISTQUEUE_H

#include "LinkedList.h"

namespace lab5 {
    class LinkedListQueue {
    private:
        LinkedList list;

    public:
        LinkedListQueue() = default;
        explicit LinkedListQueue(std::string &string);
        LinkedListQueue(const LinkedListQueue &other) = default;
        LinkedListQueue &operator=(const LinkedListQueue &other) = default;
        virtual ~LinkedListQueue() = default;

        std::string top() const;
        unsigned size() const;
        bool empty() const;

        void enqueue(const std::string &string);
        void dequeue();

        friend std::istream &operator>>(std::istream &stream, LinkedListQueue &linkedListQueue);
        friend std::ostream &operator<<(std::ostream &stream, const LinkedListQueue &linkedListQueue);
    };
}
#endif // LINKEDLISTQUEUE_H