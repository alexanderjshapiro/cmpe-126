#ifndef CMPE126S18_LABS_LIB_LAB6_NODE_H
#define CMPE126S18_LABS_LIB_LAB6_NODE_H

namespace lab6 {
    class Node {
        int value;
    public:
        Node *next;
        Node *prev;

        explicit Node(int value) : value(value), next(nullptr), prev(nullptr) {};

        int getValue() { return value; };
    };
}

#endif //CMPE126S18_LABS_NODE_H