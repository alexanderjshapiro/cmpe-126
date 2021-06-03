#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "DoublyLinkedListNode.h"

#include <iostream>
#include <vector>

namespace lab6 {
    class DoublyLinkedList {
    private:
        lab6::DoublyLinkedListNode *head, *tail;

    public:
        DoublyLinkedList();
        explicit DoublyLinkedList(int integer);
        explicit DoublyLinkedList(const std::vector<int> &integers);
        DoublyLinkedList(const DoublyLinkedList &other);
        ~DoublyLinkedList();

        int at(unsigned index) const;
        std::vector<int> getSet(unsigned indexFrom, unsigned indexTo) const;
        unsigned size() const;
        bool empty() const;

        void append(int integer);
        void insert(int integer, unsigned index = 0);
        void remove(unsigned index = 0);

        DoublyLinkedList split(unsigned index);
        DoublyLinkedList splitSet(unsigned indexFrom, unsigned indexTo);
        void swap(unsigned firstIndex, unsigned secondIndex);
        void swapSet(unsigned firstIndexFrom, unsigned firstIndexTo, unsigned secondIndexFrom, unsigned secondIndexTo);
        void sort();

        DoublyLinkedList &operator=(const DoublyLinkedList &other);
        DoublyLinkedList operator+(const DoublyLinkedList &other) const;
        DoublyLinkedList &operator+=(const DoublyLinkedList &other);

        bool operator==(const DoublyLinkedList &other) const;

        friend std::istream &operator>>(std::istream &stream, DoublyLinkedList &RHS);
        friend std::ostream &operator<<(std::ostream &stream, const DoublyLinkedList &RHS);
    };
}

#endif // DOUBLYLINKEDLIST_H