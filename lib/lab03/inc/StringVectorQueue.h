#ifndef STRINGVECTORQUEUE_H
#define STRINGVECTORQUEUE_H

#include "StringVector.h"

namespace lab3 {
    class StringVectorQueue {
    private:
        lab2::StringVector queue;
        unsigned frontIndex;
        unsigned backIndex;

    public:
        StringVectorQueue();
        explicit StringVectorQueue(std::string string);
        StringVectorQueue(const StringVectorQueue &other);
        StringVectorQueue &operator=(const StringVectorQueue &other) = default;
        ~StringVectorQueue() = default;

        std::string front() const;
        unsigned size() const;
        bool empty() const;

        void enqueue(std::string string);
        void dequeue();
    };
}

#endif // STRINGVECTORQUEUE_H