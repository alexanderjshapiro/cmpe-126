#include "queue.h"
namespace lab5{
    queue::queue() = default;

    queue::queue(std::string &data) {
        storage_structure.append(data);
    }

    queue::queue(const queue &original) = default;

    queue::~queue() = default;

    queue &queue::operator=(const queue &RHS) = default;

    bool queue::isEmpty() const {
        return storage_structure.isEmpty();
    }

    unsigned queue::queueSize() const {
        return storage_structure.listSize();
    }

    std::string queue::top() const {
        return storage_structure.getValueAt(0);
    }

    void queue::enqueue(const std::string &data) {
        storage_structure.append(data);
    }

    void queue::dequeue() {
        storage_structure.remove(0);
    }

    std::ostream& operator<<(std::ostream &stream, queue &RHS) {
        stream << RHS.storage_structure;
        return stream;
    }

    std::istream& operator>>(std::istream &stream, queue &RHS) {
        stream >> RHS.storage_structure;
        return stream;
    }
}