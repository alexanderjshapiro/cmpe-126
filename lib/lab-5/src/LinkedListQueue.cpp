#include "LinkedListQueue.h"
namespace lab5{
    LinkedListQueue::LinkedListQueue(std::string &string) {
        list.append(string);
    }

    std::string LinkedListQueue::top() const {
        return list.at(0);
    }

    unsigned LinkedListQueue::size() const {
        return list.size();
    }

    bool LinkedListQueue::empty() const {
        return list.empty();
    }

    void LinkedListQueue::enqueue(const std::string &string) {
        list.append(string);
    }

    void LinkedListQueue::dequeue() {
        list.remove(0);
    }

    std::istream& operator>>(std::istream &stream, LinkedListQueue &linkedListQueue) {
        stream >> linkedListQueue.list;
        return stream;
    }

    std::ostream& operator<<(std::ostream &stream, const LinkedListQueue &linkedListQueue) {
        stream << linkedListQueue.list;
        return stream;
    }
}