#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H

#include <string>

namespace lab5 {
    class LinkedListNode {
    public:
        LinkedListNode *next;
        std::string data;

        explicit LinkedListNode(std::string data) : data(std::move(data)), next(nullptr) {};
    };
}

#endif // LINKEDLISTNODE_H