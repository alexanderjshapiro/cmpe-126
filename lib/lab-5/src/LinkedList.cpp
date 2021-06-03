#include "LinkedList.h"

namespace lab5 {
    LinkedList::LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    LinkedList::LinkedList(std::string &string) : LinkedList() {
        append(string);
    }

    LinkedList::LinkedList(const LinkedList &other) : LinkedList() {
        *this = other;
    }

    LinkedList &lab5::LinkedList::operator=(const LinkedList &other) {
        // Check for self-assignment
        if (this == &other) return *this;

        // Clear this linked list if it's not empty
        while (head != nullptr) remove();

        // Append the data from each LinkedListNode in the other linked list to this linked list, starting at the head
        for (LinkedListNode *currentNode = other.head; currentNode != nullptr; currentNode = currentNode->next) {
            append(currentNode->data);
        }

        return *this;
    }

    LinkedList::~LinkedList() {
        while (!empty()) remove();
    }

    std::string LinkedList::at(unsigned index) const {
        // Traverse the linked list up until the desired index
        LinkedListNode *value = head;
        for (int i = 0; i < index && value != nullptr; i++) {
            value = value->next;
        }
        if (value == nullptr)
            throw std::runtime_error(
                    "invalid access index " + std::to_string(index) + " for linked list of size " +
                    std::to_string(
                            size()));
        return value->data;
    }

    unsigned LinkedList::size() const {
        // Traverse the linked list and count the nodes
        unsigned count = 0;
        for (LinkedListNode *current = head; current != nullptr; current = current->next) {
            count++;
        }
        return count;
    }

    bool LinkedList::empty() const {
        return head == nullptr;
    }

    void LinkedList::append(const std::string& string) {
        if (empty()) {
            // Create a new LinkedListNode which is both the head and tail of the one-LinkedListNode linked list
            head = new LinkedListNode(string);
            tail = head;
        } else {
            // Create a new LinkedListNode after the tail LinkedListNode, then set the tail to that new LinkedListNode
            tail->next = new LinkedListNode(string);
            tail = tail->next;
        }
    }

    void LinkedList::insert(const std::string& string, unsigned int index) {
        if (empty()) {
            if (index != 0) {
                throw std::runtime_error(
                        "invalid insertion index " + std::to_string(index) + " for linked list of size " +
                        std::to_string(
                                size()));
            }

            append(string);
        } else if (index == 0) {
            // Save the address of the LinkedListNode to be inserted, change the LinkedListNode to be inserted to point to what was the
            // head, and change the head to be the LinkedListNode that was inserted
            auto *toBeInserted = new LinkedListNode(string);
            toBeInserted->next = head;
            head = toBeInserted;
        } else {
            // Find the LinkedListNode preceding the index to be inserted
            LinkedListNode *before = head;
            for (unsigned i = 0; i < index - 1; i++) {
                before = before->next;
                if (before == nullptr) {
                    throw std::runtime_error(
                            "invalid insertion index " + std::to_string(index) + " for linked list of size " +
                            std::to_string(
                                    size()));
                }
            }

            // Save the address of the LinkedListNode to be inserted, change the LinkedListNode to be inserted to point to the succeeding
            // LinkedListNode, and change the preceding LinkedListNode to point to the LinkedListNode being inserted
            auto *toBeInserted = new LinkedListNode(string);
            toBeInserted->next = before->next;
            before->next = toBeInserted;

            // If the LinkedListNode was inserted at the end, change tail to be the LinkedListNode that was inserted
            if (toBeInserted->next == nullptr) {
                tail = toBeInserted;
            }
        }
    }

    void LinkedList::remove(unsigned index) {
        if (empty()) {
            throw std::runtime_error("cannot remove from empty linked list");
        } else if (index == 0) {
            // Save the address of the head, change head to be the following LinkedListNode, and delete what was the head
            LinkedListNode *toBeRemoved = head;
            head = toBeRemoved->next;
            delete toBeRemoved;

            // Change tail to be nullptr if the only LinkedListNode is being removed from a one-LinkedListNode linked list
            if (head == nullptr) {
                tail = nullptr;
            }
        } else {
            // Find the LinkedListNode preceding the LinkedListNode to be removed
            LinkedListNode *before = head;
            for (unsigned nodeIndex = 0; nodeIndex < index - 1; nodeIndex++) {
                before = before->next;
                if (before->next == nullptr) {
                    throw std::runtime_error(
                            "invalid removal index " + std::to_string(index) + " for linked list of size " +
                            std::to_string(
                                    size()));
                }
            }

            // Save the address of the LinkedListNode to be removed, change the preceding LinkedListNode to point to the succeeding LinkedListNode,
            // and delete the LinkedListNode to be removed
            LinkedListNode *toBeRemoved = before->next;
            before->next = toBeRemoved->next;
            delete toBeRemoved;

            // If the last LinkedListNode was removed, change tail to be what used to be the preceding LinkedListNode
            if (before->next == nullptr) {
                tail = before;
            }
        }
    }

    void LinkedList::sort() {
        for (LinkedListNode *current = head; current != nullptr; current = current->next) {
            LinkedListNode *smallest = current;
            for (LinkedListNode *candidate = current->next; candidate != nullptr; candidate = candidate->next) {
                if (candidate->data < smallest->data) {
                    smallest = candidate;
                }
            }

            std::string temp = current->data;
            current->data = smallest->data;
            smallest->data = temp;
        }
    }

    std::istream &operator>>(std::istream &stream, LinkedList &linkedList) {
        std::string input;
        getline(stream, input);
        linkedList.append(input);
        return stream;
    }

    std::ostream &operator<<(std::ostream &stream, const LinkedList &linkedList) {
        for (LinkedListNode *value = linkedList.head; value != nullptr; value = value->next) {
            stream << value->data + " -> ";
        }
        stream << "NULL";
        return stream;
    }
}