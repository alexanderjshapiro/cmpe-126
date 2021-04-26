#ifndef CMPE126S18_LABS_DOUBLY_LINKED_LIST_H
#define CMPE126S18_LABS_DOUBLY_LINKED_LIST_H

#include "Node.h"
#include <vector>
#include <iostream>

namespace lab6 {
    class DoublyLinkedList {
        lab6::Node *head;
        lab6::Node *tail;
    public:
        DoublyLinkedList();
        DoublyLinkedList(int firstValue);
        DoublyLinkedList(const std::vector<int>& vector);
        DoublyLinkedList(const DoublyLinkedList &original);
        ~DoublyLinkedList();

        int getValue(unsigned index);
        std::vector<int> getSet(unsigned indexFrom, unsigned indexTo);
        unsigned size();
        bool empty();

        void append(int value);
        void insert(int value, unsigned index = 0);
        void remove(unsigned index);
        DoublyLinkedList split(unsigned index);
        DoublyLinkedList splitSet(unsigned indexFrom, unsigned indexTo);

        void swap(unsigned firstIndex, unsigned secondIndex);
        void swapSet(unsigned firstIndexFrom, unsigned firstIndexTo, unsigned secondIndexFrom, unsigned secondIndexTo);

        void sort();

        DoublyLinkedList operator+(const DoublyLinkedList &other) const;
        DoublyLinkedList &operator=(const DoublyLinkedList &other);
        DoublyLinkedList &operator+=(const DoublyLinkedList &other);
        bool operator==(const DoublyLinkedList &other);

        friend std::ostream &operator<<(std::ostream &stream, DoublyLinkedList &RHS);
        friend std::istream &operator>>(std::istream &stream, DoublyLinkedList &RHS);
    };
}

#endif //CMPE126S18_LABS_DOUBLY_LINKED_LIST_H