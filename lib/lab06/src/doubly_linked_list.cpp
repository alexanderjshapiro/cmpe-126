#include "../inc/doubly_linked_list.h"

namespace lab6 {
    doubly_linked_list::doubly_linked_list() {
        head = nullptr;
        tail = nullptr;
    }

    doubly_linked_list::doubly_linked_list(int input) : doubly_linked_list() {
        append(input);
    }

    doubly_linked_list::doubly_linked_list(std::vector<int> vector_input) : doubly_linked_list() {
        for (int num : vector_input) append(num);
    }

    doubly_linked_list::doubly_linked_list(const doubly_linked_list &original) : doubly_linked_list() {
        *this = original;
    }

    doubly_linked_list::~doubly_linked_list() {
        while (!is_empty()) remove(0);
    }

    int doubly_linked_list::get_data(unsigned position) {
        node *current = head;
        for (unsigned i = 0; i < position; i++) {
            if (current->next == nullptr) throw std::runtime_error("invalid access index " + std::to_string(position) + " for list of size " + std::to_string(size()));
            current = current->next;
        }

        return current->get_data();
    }

    std::vector<int> doubly_linked_list::get_set(unsigned position_from, unsigned position_to) {
        std::vector<int> set;

        node *start = head;
        for (unsigned i = 0; i < position_from; i++) {
            if (start->next == nullptr) throw std::runtime_error("invalid set start index " + std::to_string(position_from) + " for list of size " + std::to_string(size()));

            start = start->next;
        }

        node *current = start;
        for (unsigned i = 0; i <= position_to - position_from; i++) {
            if (current == nullptr) throw std::runtime_error("invalid set end index " + std::to_string(position_to) + " for list of size " + std::to_string(size()));

            set.push_back(current->get_data());

            current = current->next;
        }

        return set;
    }

    unsigned doubly_linked_list::size() {
        unsigned count = 0;
        for (node *current = head; current != nullptr; current = current->next) count++;
        return count;
    }

    bool doubly_linked_list::is_empty() {
        return head == nullptr;
    }

    void doubly_linked_list::append(int input) {
        if (head == nullptr) {
            head = new node(input);
            tail = head;
        } else {
            tail->next = new node(input);
            tail->next->prev = tail;
            tail = tail->next;
        }
    }

    void doubly_linked_list::insert(int input, unsigned int location) {
        if (is_empty()) {
            if (location != 0) throw std::runtime_error("invalid insertion location " + std::to_string(location) + " for list of size " + std::to_string(size()));

            append(input);
        } else if (location == 0) {
            node *toBeInserted = new node(input);
            toBeInserted->next = head;
            head->prev = toBeInserted;
            head = toBeInserted;
        } else {
            // Find the node preceding the location to be inserted
            node *before = head;
            for (unsigned i = 0; i < location - 1; i++) {
                before = before->next;
                if (before == nullptr) {
                    throw std::runtime_error("invalid insertion location " + std::to_string(location) + " for list of size " + std::to_string(size()));
                }
            }

            node *toBeInserted = new node(input);
            toBeInserted->next = before->next;
            if (before->next != nullptr) before->next->prev = toBeInserted;
            toBeInserted->prev = before;
            before->next = toBeInserted;

            // If the node was inserted at the end, change tail to be the node that was inserted
            if (toBeInserted->next == nullptr) {
                tail = toBeInserted;
            }
        }
    }

    void doubly_linked_list::remove(unsigned location) {
        if (is_empty()) {
            throw std::runtime_error("cannot remove from empty list");
        } else if (location == 0) {
            node *toBeRemoved = head; // Save the address of the head
            head = toBeRemoved->next; // Set the new head to the node after the old head
            if (head != nullptr) head->prev = nullptr; // Set the new head to point backwards to nothing
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
                if (before->next == nullptr) throw std::runtime_error("invalid removal location " + std::to_string(location) + " for list of size " + std::to_string(size()));
            }

            node *toBeRemoved = before->next; // Save the address of the node to be removed
            before->next = toBeRemoved->next; // Set the node before to point forwards to the node after
            if (before->next != nullptr) before->next->prev = before; // Set the node after to point backwards to the node before
            delete toBeRemoved;

            // If the last node was removed, change tail to be what used to be the preceding node
            if (before->next == nullptr) {
                tail = before;
            }
        }
    }

    doubly_linked_list doubly_linked_list::split(unsigned position) {
        doubly_linked_list list;

        if (is_empty()) {
            return list;
        } else if (position == 0) {
            list.head = head;
            list.tail = tail;

            head = nullptr;
            tail = nullptr;
        } else {
            // Navigate to where the split will occur
            node *first = head;
            for (unsigned i = 0; i < position; i++) {
                first = first->next;
                if (first == nullptr) {
                    throw std::runtime_error("invalid split location " + std::to_string(position) + " for list of size " + std::to_string(size()));
                }
            }

            // Soft copy the nodes to the new list
            list.head = first;
            list.tail = tail;

            // Separate the two lists by disconnecting the nodes at the split location
            tail = first->prev;
            tail->next = nullptr;
            first->prev = nullptr;
        }

        return list;
    }

    doubly_linked_list doubly_linked_list::split_set(unsigned position_1, unsigned position_2) {
        doubly_linked_list list;

        // Navigate to where the split will occur
        node *first = head;
        for (unsigned i = 0; i < position_1; i++) {
            first = first->next;
            if (first == nullptr) {
                throw std::runtime_error("invalid split start location " + std::to_string(position_1) + " for list of size " + std::to_string(size()));
            }
        }

        node *last = head;
        for (unsigned i = 0; i < position_2; i++) {
            last = last->next;
            if (last == nullptr) {
                throw std::runtime_error("invalid split end location " + std::to_string(position_2) + " for list of size " + std::to_string(size()));
            }
        }

        // Soft copy the nodes to the new list
        list.head = first;
        list.tail = last;

        // Separate the two lists by disconnecting the nodes at the split locations
        first->prev->next = last->next;
        last->next->prev = first->prev;
        first->prev = nullptr;
        last->next = nullptr;

        return list;
    }

    void doubly_linked_list::swap(unsigned position_1, unsigned position_2) {
        if (position_1 == position_2) return;
        int one = get_data(position_1);
        int two = get_data(position_2);

        remove(position_1);
        remove(position_2 - 1);

        insert(one, position_2 - 1);
        insert(two, position_1);
    }

    void doubly_linked_list::swap_set(unsigned location_1_start, unsigned location_1_end, unsigned location_2_start, unsigned location_2_end) {
        unsigned second = location_2_start;
        for (unsigned first = location_1_start; first <= location_1_end; first++) {
            swap(first, second);
            second++;
        }
    }

    void doubly_linked_list::sort() {
        unsigned listSize = size();
        for (unsigned current = 0; current < listSize - 1; current++) {
            unsigned smallest = current;
            for (unsigned candidate = current + 1; candidate < listSize; candidate++) {
                if (get_data(candidate) < get_data(smallest)) smallest = candidate;
            }
            swap(current, smallest);
        }
    }

    doubly_linked_list doubly_linked_list::operator+(const doubly_linked_list &rhs) const {
        doubly_linked_list list(*this);
        list += rhs;
        return list;
    }

    doubly_linked_list &doubly_linked_list::operator=(const doubly_linked_list &rhs) {
        // Check for self-assignment
        if (this == &rhs) {
            return *this;
        }

        // Clear this linked list if it's not empty
        while (head != nullptr) {
            remove(0);
        }

        // Add the data from each node in the other list to this list
        *this += rhs;

        return *this;
    }

    doubly_linked_list &doubly_linked_list::operator+=(const doubly_linked_list &rhs) {
        // Append the data from each node in the other list to this list, starting at the head
        for (node *currentNode = rhs.head; currentNode != nullptr; currentNode = currentNode->next) append(currentNode->get_data());

        return *this;
    }

    bool doubly_linked_list::operator==(const doubly_linked_list &rhs) {
        bool done = false;
        node* lh = head;
        node* rh = rhs.head;
        while (!done) {
            if ((lh == nullptr) != (rh == nullptr)) return false;
            if ((lh->get_data()) != (rh->get_data())) return false;

            lh = lh->next;
            rh = rh->next;

            if (lh == nullptr && rh == nullptr) done = true;
        }
        return true;
    }

    std::ostream &operator<<(std::ostream &stream, doubly_linked_list &RHS) {
        stream << "NULL <- ";
        for (node *value = RHS.head; value != nullptr; value = value->next) {
            stream << std::to_string(value->get_data());
            if (value->next != nullptr) stream << " <-> ";
        }
        stream << " -> NULL";
        return stream;
    }

    std::istream &operator>>(std::istream &stream, doubly_linked_list &RHS) {
        int input;
        stream >> input;
        RHS.append(input);
        return stream;
    }
}