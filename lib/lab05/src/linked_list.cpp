#include "linked_list.h"

namespace lab5 {
    linked_list::linked_list() {
        // Initialize empty linked list
        head = nullptr;
        tail = nullptr;
    }

    linked_list::linked_list(std::string &data) : linked_list() {
        // Initialize empty linked list, then append initial data
        append(data);
    }

    linked_list::linked_list(const linked_list &original) : linked_list() {
        // Initialize empty linked list, then use overloaded equals operator to handle copying
        *this = original;
    }

    linked_list::~linked_list() {
        // Delete each node using remove
        while (head != nullptr) {
            remove(0);
        }
    }

    linked_list &lab5::linked_list::operator=(const linked_list &RHS) {
        // Check for self-assignment
        if (this == &RHS) {
            return *this;
        }

        // Clear this linked list if it's not empty
        while (head != nullptr) {
            remove(0);
        }

        // Append the data from each node in the other linked list to this linked list, starting at the head
        for (node *currentNode = RHS.head; currentNode != nullptr; currentNode = currentNode->next) {
            append(currentNode->data);
        }

        return *this;
    }


    bool linked_list::isEmpty() const {
        return head == nullptr;
    }

    unsigned linked_list::listSize() const {
        // Traverse the linked list and count the nodes
        unsigned count = 0;
        for (node *current = head; current != nullptr; current = current->next) {
            count++;
        }
        return count;
    }

    void linked_list::insert(const std::string input, unsigned int location) {
        if (isEmpty()) {
            if (location != 0) {
                throw std::runtime_error("invalid insertion location " + std::to_string(location) + " for linked list of size " + std::to_string(listSize()));
            }

            append(input);
        } else if (location == 0) {
            // Save the address of the node to be inserted, change the node to be inserted to point to what was the
            // head, and change the head to be the node that was inserted
            node *toBeInserted = new node(input);
            toBeInserted->next = head;
            head = toBeInserted;
        } else {
            // Find the node preceding the location to be inserted
            node *before = head;
            for (unsigned i = 0; i < location - 1; i++) {
                before = before->next;
                if (before == nullptr) {
                    throw std::runtime_error("invalid insertion location " + std::to_string(location) + " for linked list of size " + std::to_string(listSize()));
                }
            }

            // Save the address of the node to be inserted, change the node to be inserted to point to the succeeding
            // node, and change the preceding node to point to the node being inserted
            node *toBeInserted = new node(input);
            toBeInserted->next = before->next;
            before->next = toBeInserted;

            // If the node was inserted at the end, change tail to be the node that was inserted
            if (toBeInserted->next == nullptr) {
                tail = toBeInserted;
            }
        }
    }

    void linked_list::append(const std::string input) {
        if (isEmpty()) {
            // Create a new node which is both the head and tail of the one-node linked list
            head = new node(input);
            tail = head;
        } else {
            // Create a new node after the tail node, then set the tail to that new node
            tail->next = new node(input);
            tail = tail->next;
        }
    }

    void linked_list::remove(unsigned location) {
        if (isEmpty()) {
            throw std::runtime_error("cannot remove from empty linked list");
        } else if (location == 0) {
            // Save the address of the head, change head to be the following node, and delete what was the head
            node *toBeRemoved = head;
            head = toBeRemoved->next;
            delete toBeRemoved;

            // Change tail to be nullptr if the only node is being removed from a one-node linked list
            if (head == nullptr) {
                tail = nullptr;
            }
        } else {
            // Find the node preceding the node to be removed
            node *before = head;
            for (unsigned nodeIndex = 0; nodeIndex < location - 1; nodeIndex++) {
                before = before->next;
                if (before->next == nullptr) {
                    throw std::runtime_error("invalid removal location " + std::to_string(location) + " for linked list of size " + std::to_string(listSize()));
                }
            }

            // Save the address of the node to be removed, change the preceding node to point to the succeeding node,
            // and delete the node to be removed
            node *toBeRemoved = before->next;
            before->next = toBeRemoved->next;
            delete toBeRemoved;

            // If the last node was removed, change tail to be what used to be the preceding node
            if (before->next == nullptr) {
                tail = before;
            }
        }
    }

    std::ostream &operator<<(std::ostream &stream, linked_list &RHS) {
        for (node *value = RHS.head; value != nullptr; value = value->next) {
            stream << value->data + " -> ";
        }
        stream << "NULL";
        return stream;
    }

    std::istream &operator>>(std::istream &stream, linked_list &RHS) {
        std::string input;
        getline(stream, input);
        RHS.append(input);
        return stream;
    }

    void linked_list::sort() {
        for (node *current = head; current != nullptr; current = current->next) {
            node *smallest = current;
            for (node *candidate = current->next; candidate != nullptr; candidate = candidate->next) {
                if (candidate->data < smallest->data) {
                    smallest = candidate;
                }
            }

            std::string temp = current->data;
            current->data = smallest->data;
            smallest->data = temp;
        }
    }

    std::string linked_list::getValueAt(unsigned location) const {
        // Traverse the linked list up until the desired index
        node *value = head;
        for (int i = 0; i < location && value != nullptr; i++) {
            value = value->next;
        }
        if (value == nullptr) throw std::runtime_error("invalid access location " + std::to_string(location) + " for linked list of size " + std::to_string(listSize()));
        return value->data;
    }
}