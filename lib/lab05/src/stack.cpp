#include "stack.h"
namespace lab5{
    stack::stack() = default;

    stack::stack(std::string &data) {
        storage_structure.append(data);
    }

    stack::stack(const stack &original) = default;

    stack::~stack() = default;

    stack &stack::operator=(const stack &RHS) = default;

    bool stack::isEmpty() const {
        return storage_structure.isEmpty();
    }

    unsigned stack::stackSize() const {
        return storage_structure.listSize();
    }

    std::string stack::top() const {
        return storage_structure.getValueAt(stackSize() - 1);
    }

    void stack::push(const std::string &data) {
        storage_structure.append(data);
    }

    void stack::pop() {
        storage_structure.remove(stackSize() - 1);
    }

    std::ostream& operator<<(std::ostream &stream, stack &RHS) {
        stream << RHS.storage_structure;
        return stream;
    }

    std::istream& operator>>(std::istream &stream, stack &RHS) {
        stream >> RHS.storage_structure;
        return stream;
    }
}