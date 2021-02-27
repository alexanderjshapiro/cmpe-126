#ifndef CMPE126S18_LABS_STRINGVECTOR_H
#define CMPE126S18_LABS_STRINGVECTOR_H

#include <string>

namespace lab2 {
    class stringVector {
    private:
        std::string *data;
        unsigned length;
        unsigned allocated_length;

    public:
        stringVector();
        virtual ~stringVector();
        stringVector &operator=(stringVector const &rhs);

        unsigned size() const;
        bool empty() const;

        unsigned capacity() const;
        void reserve(unsigned new_size);

        void append(std::string new_data);
        void swap(unsigned pos1, unsigned pos2);
        std::string &operator[](unsigned position);

        void sort();
    };
}

#endif //CMPE126S18_LABS_STRINGVECTOR_H
