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
        StringVector &operator=(StringVector const &other);
        virtual ~StringVector();

        std::string &operator[](unsigned index) const;
        unsigned size() const;
        bool empty() const;
        unsigned capacity() const;

        void append(std::string string);
        void reserve(unsigned capacity);

        void swap(unsigned index1, unsigned index2);
        void sort();
    };
}

#endif // STRINGVECTOR_H
