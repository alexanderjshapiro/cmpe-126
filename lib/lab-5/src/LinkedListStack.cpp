#include "LinkedListStack.h"
namespace lab5{
    LinkedListStack::LinkedListStack(std::string &string) {
        storage_structure.append(string);
    }

    std::string LinkedListStack::top() const {
        return storage_structure.at(size() - 1);
    }

    unsigned LinkedListStack::size() const {
        return storage_structure.size();
    }

    bool LinkedListStack::empty() const {
        return storage_structure.empty();
    }

    void LinkedListStack::push(const std::string &string) {
        storage_structure.append(string);
    }

    void LinkedListStack::pop() {
        storage_structure.remove(size() - 1);
    }

    std::ostream& operator<<(std::ostream &stream, LinkedListStack &linkedListStack) {
        stream << linkedListStack.storage_structure;
        return stream;
    }

    std::istream& operator>>(std::istream &stream, LinkedListStack &linkedListStack) {
        stream >> linkedListStack.storage_structure;
        return stream;
    }
}