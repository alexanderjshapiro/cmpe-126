#include "DoublyLinkedList.h"

namespace lab6 {
    DoublyLinkedList::DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    DoublyLinkedList::DoublyLinkedList(int integer) : DoublyLinkedList() {
        append(integer);
    }

    DoublyLinkedList::DoublyLinkedList(const std::vector<int>& integers) : DoublyLinkedList() {
        for (int num : integers) append(num);
    }

    DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList &other) : DoublyLinkedList() {
        *this = other;
    }

    DoublyLinkedList::~DoublyLinkedList() {
        while (!empty()) remove(0);
    }

    int DoublyLinkedList::at(unsigned index) const {
        if (empty()) throw std::runtime_error("invalid access index " + std::to_string(index) + " for empty list");

        DoublyLinkedListNode *current = head;
        for (unsigned i = 0; i < index; i++) {
            current = current->next;
            if (!current) throw std::runtime_error("invalid access index " + std::to_string(index) + " for list of size " + std::to_string(size()));
        }

        return current->getValue();
    }

    std::vector<int> DoublyLinkedList::getSet(unsigned indexFrom, unsigned indexTo) const {
        // Swap wrongly ordered indices
        if (indexFrom > indexTo) std::swap(indexFrom, indexTo);

        std::vector<int> set;

        DoublyLinkedListNode *start = head;
        for (unsigned i = 0; i < indexFrom; i++) {
            start = start->next;
            if (!start) throw std::runtime_error("invalid set start index " + std::to_string(indexFrom) + " for list of size " + std::to_string(size()));
        }

        unsigned setSize = indexTo - indexFrom;
        DoublyLinkedListNode *current = start;
        for (unsigned i = 0; i <= setSize; i++) {
            if (!current) throw std::runtime_error("invalid set end index " + std::to_string(indexTo) + " for list of size " + std::to_string(size()));
            set.push_back(current->getValue());
            current = current->next;
        }

        return set;
    }

    unsigned DoublyLinkedList::size() const {
        unsigned count = 0;
        for (DoublyLinkedListNode *current = head; current != nullptr; current = current->next) count++;
        return count;
    }

    bool DoublyLinkedList::empty() const {
        return head == nullptr;
    }

    void DoublyLinkedList::append(int integer) {
        if (empty()) {
            head = new DoublyLinkedListNode(integer);
            tail = head;
        } else {
            // Create a new LinkedListNode after the tail and update the tail
            tail->next = new DoublyLinkedListNode(integer);
            tail->next->prev = tail;
            tail = tail->next;
        }
    }

    void DoublyLinkedList::insert(int integer, unsigned int index) {
        if (empty()) {
            if (index == 0) append(integer);
            else throw std::runtime_error("invalid insertion index " + std::to_string(index) + " for empty list");
        } else if (index == 0) {
            // Create a new LinkedListNode before the head and update the head
            head->prev = new DoublyLinkedListNode(integer);
            head->prev->next = head;
            head = head->prev;
        } else {
            // Find the LinkedListNode preceding the index to be inserted
            DoublyLinkedListNode *before = head;
            for (unsigned i = 0; i < index - 1; i++) {
                before = before->next;
                if (!before) throw std::runtime_error("invalid insertion index " + std::to_string(index) + " for list of size " + std::to_string(size()));
            }

            // Make the new LinkedListNode point backwards to the LinkedListNode before and forwards to the LinkedListNode after
            DoublyLinkedListNode *toBeInserted = new DoublyLinkedListNode(integer);
            toBeInserted->next = before->next;
            toBeInserted->prev = before;

            // Make the LinkedListNode before point forwards to the LinkedListNode after
            toBeInserted->prev->next = toBeInserted;

            // Make the LinkedListNode after point backwards to the LinkedListNode before
            // If there is no LinkedListNode after, update the tail
            if (toBeInserted->next) toBeInserted->next->prev = toBeInserted;
            else tail = toBeInserted;
        }
    }

    void DoublyLinkedList::remove(unsigned index) {
        if (empty()) throw std::runtime_error("invalid removal index " + std::to_string(index) + " for empty list");

        DoublyLinkedListNode *toBeRemoved = head;
        for (unsigned i = 0; i < index; i++) {
            toBeRemoved = toBeRemoved->next;
            if (!toBeRemoved) throw std::runtime_error("invalid split index " + std::to_string(index) + " for list of size " + std::to_string(size()));
        }

        // Make the LinkedListNode before point forwards to the LinkedListNode after
        // If there is no LinkedListNode before, update the head
        if (toBeRemoved->prev) toBeRemoved->prev->next = toBeRemoved->next;
        else head = toBeRemoved->next;

        // Make the LinkedListNode after point backwards to the LinkedListNode before
        // If there is no LinkedListNode after, update the tail
        if (toBeRemoved->next) toBeRemoved->next->prev = toBeRemoved->prev;
        else tail = toBeRemoved->prev;
    }

    DoublyLinkedList DoublyLinkedList::split(unsigned index) {
        DoublyLinkedList list;

        if (empty()) throw std::runtime_error("invalid split index " + std::to_string(index) + " for empty list");

        DoublyLinkedListNode *first = head;
        for (unsigned i = 0; i < index; i++) {
            first = first->next;
            if (!first) throw std::runtime_error("invalid split index " + std::to_string(index) + " for list of size " + std::to_string(size()));
        }

        // Soft copy the desired nodes to the new list
        list.head = first;
        list.tail = tail;

        // Update the list tail and make it point forwards to nothing
        tail = first->prev;
        if (tail) tail->next = nullptr;

        // Make the set head point backwards to nothing
        first->prev = nullptr;

        // If the set is the list, update the list head
        if (first == head) head = nullptr;

        return list;
    }

    DoublyLinkedList DoublyLinkedList::splitSet(unsigned indexFrom, unsigned indexTo) {
        // Swap wrongly ordered indices
        if (indexFrom > indexTo) std::swap(indexFrom, indexTo);

        DoublyLinkedList list;

        // Navigate to where the split will occur
        DoublyLinkedListNode *first = head;
        for (unsigned i = 0; i < indexFrom; i++) {
            first = first->next;
            if (!first) throw std::runtime_error("invalid split start index " + std::to_string(indexFrom) + " for list of size " + std::to_string(size()));
        }

        DoublyLinkedListNode *last = head;
        for (unsigned i = 0; i < indexTo; i++) {
            last = last->next;
            if (!last) throw std::runtime_error("invalid split end index " + std::to_string(indexTo) + " for list of size " + std::to_string(size()));
        }

        // Soft copy the desired nodes to the new list
        list.head = first;
        list.tail = last;

        // If the set head is the list head, update the list head
        // Otherwise, make the LinkedListNode before the set head point to forwards to the LinkedListNode after the set tail
        // Make the set head point backwards to nothing
        if (first == head) head = last->next;
        else first->prev->next = last->next;
        first->prev = nullptr;

        // If the set tail is the list tail, update the list tail
        // Otherwise, make the LinkedListNode after the set tail point to backwards to the LinkedListNode before the set head
        // Make the set tail point forwards to nothing
        if (last == tail) tail = first->prev;
        else last->next->prev = first->prev;
        last->next = nullptr;

        return list;
    }

    void DoublyLinkedList::swap(unsigned firstIndex, unsigned secondIndex) {
        // Swap wrongly ordered indices and check for same indices
        if (firstIndex > secondIndex) std::swap(firstIndex, secondIndex);
        else if (firstIndex == secondIndex) {
            if (firstIndex >= size()) throw std::runtime_error("invalid swap indices");
            return;
        }

//        LinkedListNode *beforeFirst, *first, *afterFirst;
//        first = head;
//        for (unsigned i = 0; i < firstIndex; i++) {
//            first = first->next;
//            if (!first) throw std::runtime_error("invalid first swap index " + std::to_string(firstIndex) + " for list of size " + std::toString(size()));
//        }
//        beforeFirst = first->prev;
//        afterFirst = first->next;
//
//        unsigned gapSize = secondIndex - firstIndex;
//        LinkedListNode *beforeSecond, *second, *afterSecond;
//        second = first;
//        for (unsigned i = 0; i < gapSize; i++) {
//            second = second->next;
//            if (!second) throw std::runtime_error("invalid second swap index " + std::to_string(secondIndex) + " for list of size " + std::toString(size()));
//        }
//
//        beforeSecond = second->prev;
//        afterSecond = second->next;
//
//        if (beforeFirst) beforeFirst->next = second;
//        second->prev = beforeFirst;
//
//        second->next = afterFirst;
//        afterFirst->prev = second;
//
//        beforeSecond->next = first;
//        first->prev = beforeSecond;
//
//        first->next = afterSecond;
//        afterSecond->prev = first;

        int one = at(firstIndex);
        int two = at(secondIndex);

        remove(firstIndex);
        remove(secondIndex - 1);

        insert(one, secondIndex - 1);
        insert(two, firstIndex);
    }

    void DoublyLinkedList::swapSet(unsigned firstIndexFrom, unsigned firstIndexTo, unsigned secondIndexFrom, unsigned secondIndexTo) {
        // Swap wrongly ordered indices
        if (firstIndexFrom > firstIndexTo) std::swap(firstIndexFrom, firstIndexTo);
        if (secondIndexFrom > secondIndexTo) std::swap(secondIndexFrom, secondIndexTo);

        // Check for overlapping indices
        if (secondIndexFrom < firstIndexTo) throw std::runtime_error("sets to swap cannot overlap");

        unsigned setSize = firstIndexTo - firstIndexFrom + 1;
        for (unsigned i = 0; i < setSize; i++) {
            swap(firstIndexFrom + i, secondIndexFrom + i);
        }
    }

    void DoublyLinkedList::sort() {
        // Selection sort
        unsigned listSize = size();
        if (listSize == 0) return;
        for (unsigned current = 0; current < listSize - 1; current++) {
            unsigned smallest = current;
            for (unsigned candidate = current + 1; candidate < listSize; candidate++) if (at(candidate) <
                                                                                          at(smallest)) smallest = candidate;
            swap(current, smallest);
        }
    }

    DoublyLinkedList &DoublyLinkedList::operator=(const DoublyLinkedList &other) {
        // Check for self-assignment
        if (this == &other) {
            return *this;
        }

        // Clear this linked list if it's not empty
        while (!empty()) remove(0);

        // Copy the values from the other list to this list
        *this += other;

        return *this;
    }

    DoublyLinkedList DoublyLinkedList::operator+(const DoublyLinkedList &other) const {
        DoublyLinkedList list(*this);

        list += other;

        return list;
    }

    DoublyLinkedList &DoublyLinkedList::operator+=(const DoublyLinkedList &other) {
        // Copy the values from the other list to the end of this list
        for (DoublyLinkedListNode *currentNode = other.head; currentNode != nullptr; currentNode = currentNode->next) append(currentNode->getValue());

        return *this;
    }

    bool DoublyLinkedList::operator==(const DoublyLinkedList &other) const {
        // Check for difference in value
        DoublyLinkedListNode* leftCurrent = head;
        DoublyLinkedListNode* rightCurrent = other.head;
        while (leftCurrent != nullptr && rightCurrent != nullptr) {
            if ((leftCurrent->getValue()) != (rightCurrent->getValue())) return false;

            leftCurrent = leftCurrent->next;
            rightCurrent = rightCurrent->next;
        }

        // Check for difference in length
        if (leftCurrent == rightCurrent) return true;
        else return false;
    }

    std::istream &operator>>(std::istream &stream, DoublyLinkedList &list) {
        int input;
        stream >> input;
        list.append(input);

        return stream;
    }

    std::ostream &operator<<(std::ostream &stream, const DoublyLinkedList &list) {
        stream << "NULL <- ";
        for (DoublyLinkedListNode *value = list.head; value != nullptr; value = value->next) {
            stream << std::to_string(value->getValue());
            if (value->next != nullptr) stream << " <-> ";
        }
        stream << " -> NULL";

        return stream;
    }
}