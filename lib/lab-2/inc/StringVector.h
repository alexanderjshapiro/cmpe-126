#ifndef STRINGVECTOR_H
#define STRINGVECTOR_H

#include <string>

namespace lab2 {
    class StringVector {
    private:
        std::string *data;

        unsigned dataSize;
        unsigned dataCapacity;

    public:
        StringVector();
        StringVector(StringVector const &other);
        ~StringVector();

        std::string &at(unsigned index) const;
        unsigned size() const;
        bool empty() const;
        unsigned capacity() const;

        void append(std::string string);
        void reserve(unsigned capacity);
        void condense();
        void optimize();

        void swap(unsigned index1, unsigned index2);
        void sort();

        StringVector &operator=(StringVector const &other);
        std::string &operator[](unsigned index) const;
    };
}

#endif // STRINGVECTOR_H
