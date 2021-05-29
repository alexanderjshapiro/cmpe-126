#ifndef STRINGVECTORSTACK_H
#define STRINGVECTORSTACK_H

#include "StringVector.h"

namespace lab3 {
    class StringVectorStack {
    private:
        lab2::StringVector stack;
        unsigned topIndex;

    public:
        StringVectorStack();
        explicit StringVectorStack(std::string string);
        StringVectorStack(const StringVectorStack &other);
        StringVectorStack &operator=(const StringVectorStack &other) = default;
        ~StringVectorStack() = default;

        std::string top();
        unsigned size() const;
        bool empty() const;

        void push(std::string string);
        void pop();
    };
}

#endif // STRINGVECTORSTACK_H