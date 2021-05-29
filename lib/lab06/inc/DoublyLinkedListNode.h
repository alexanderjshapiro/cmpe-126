#ifndef DOUBLYLINKEDLISTNODE_H
#define DOUBLYLINKEDLISTNODE_H

namespace lab6 {
    class DoublyLinkedListNode {
    private:
        int value;
    public:
        DoublyLinkedListNode *next;
        DoublyLinkedListNode *prev;

        explicit DoublyLinkedListNode(int value) : value(value), next(nullptr), prev(nullptr) {};

        int getValue() const { return value; };
    };
}

#endif // DOUBLYLINKEDLISTNODE_H