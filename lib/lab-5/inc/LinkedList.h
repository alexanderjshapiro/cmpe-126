#ifndef CMPE126S18_LABS_LIB_LAB05_INC_LINKED_LIST_H
#define CMPE126S18_LABS_LIB_LAB05_INC_LINKED_LIST_H

#include "LinkedListNode.h"
#include <iostream>

namespace lab5 {
    class LinkedList {
        LinkedListNode *head, *tail;

    public:
        LinkedList();
        explicit LinkedList(std::string &string);
        LinkedList(const LinkedList &other);
        LinkedList &operator=(const LinkedList &other);
        virtual ~LinkedList();

        std::string at(unsigned index) const;
        unsigned size() const;
        bool empty() const;

        void append(const std::string& string);
        void insert(const std::string& string, unsigned index = 0);
        void remove(unsigned index = 0);

        void sort();

        friend std::istream& operator>>(std::istream& stream, LinkedList& linkedList);
        friend std::ostream& operator<<(std::ostream& stream, const LinkedList& linkedList);
    };
}

#endif