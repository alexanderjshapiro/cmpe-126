#include "StringVector.h"

namespace lab2 {
    StringVector::StringVector() {
        dataSize = 0;
        dataCapacity = 0;
        data = new std::string[dataCapacity];
    }

    StringVector::StringVector(const StringVector &other) : StringVector() {
        *this = other;
    }

    StringVector &StringVector::operator=(StringVector const &other) {
        // Check for self-assignment
        if (this == &other) return *this;

        // Delete this data, reserve memory, and copy other data
        delete[] data;
        dataCapacity = other.dataCapacity;
        data = new std::string[dataCapacity];
        for (int i = 0; i < other.dataSize; ++i) data[i] = other.data[i];
        dataSize = other.dataSize;

        return *this;
    }

    StringVector::~StringVector() {
        delete[] data;
    }

    std::string &StringVector::operator[](unsigned index) const {
        if (index >= 0 && index < dataSize) return data[index];
        else throw std::runtime_error("index " + std::to_string(index) + " is invalid");
    }

    unsigned StringVector::size() const {
        return dataSize;
    }

    bool StringVector::empty() const {
        return size() == 0;
    }

    unsigned StringVector::capacity() const {
        return dataCapacity;
    }

    void StringVector::append(std::string string) {
        // Increase capacity if data is full
        if (dataCapacity == 0) reserve(1);
        else if (dataSize == dataCapacity) reserve(dataCapacity * 2);

        data[dataSize++] = std::move(string);
    }

    void StringVector::reserve(unsigned capacity) {
        if (capacity == dataCapacity) return;

        // Copy this data to new array with desired capacity, then replace this data with new array
        dataCapacity = capacity;
        auto *newData = new std::string[dataCapacity];
        for (unsigned i = 0; i < dataSize && i < dataCapacity; i++) newData[i] = data[i];
        delete[] data;
        data = newData;

        // Adjust dataSize in case data was truncated
        if (capacity < dataSize) dataSize = capacity;
    }

    void StringVector::swap(unsigned index1, unsigned index2) {
        if (index1 < 0 || index1 >= dataSize) throw std::runtime_error("first index " + std::to_string(index1) + " is invalid");
        else if (index2 < 0 || index2 >= dataSize) throw std::runtime_error("second index " + std::to_string(index2) + " is invalid");
        else std::swap(data[index1], data[index2]);
    }

    void StringVector::sort() {
        // Bubble sort, except lowercase letters come before uppercase letters
        for (unsigned pass = 1; pass < dataSize; pass++) {
            for (size_t j = 0; j < dataSize - 1; ++j) {
                // Switch case of letters to override sort order
                std::string first = data[j];
                std::string second = data[j + 1];

                for (char &i : first) {
                    if (i >= 65 && i <= 90) i += 32;
                    else if (i >= 97 && i <= 122) i -= 32;
                }

                for (char &i : second) {
                    if (i >= 65 && i <= 90) i += 32;
                    else if (i >= 97 && i <= 122) i -= 32;
                }

                if (first > second) {
                    std::string temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }
}