#include "../inc/stringVector.h"

namespace lab2 {
    stringVector::stringVector() {
        // Initialize empty vector
        length = 0;
        allocated_length = 0;

        data = new std::string[allocated_length];
    }

    stringVector::~stringVector() {
        delete[] data;
    }

    unsigned stringVector::size() const {
        return length;
    }

    unsigned stringVector::capacity() const {
        return allocated_length;
    }

    void stringVector::reserve(unsigned new_size) {
        if (new_size == allocated_length) {
            return;
        }

        // Copy data to array with desired capacity
        allocated_length = new_size;
        auto *newData = new std::string[allocated_length];
        for (unsigned i = 0; i < length && i < allocated_length; ++i) {
            newData[i] = data[i];
        }

        // Delete data and replace it with our new array
        delete[] data;
        data = newData;

        // Adjust length in case data was truncated
        if (new_size < length) {
            length = new_size;
        }
    }

    bool stringVector::empty() const {
        return length == 0;
    }

    void stringVector::append(std::string new_data) {
        // Set capacity to 1 if empty, or double it if there's no space to add another string
        if (allocated_length == 0) {
            reserve(1);
        } else if (allocated_length == length) {
            reserve(allocated_length * 2);
        }

        data[length++] = std::move(new_data);
    }

    void stringVector::swap(unsigned pos1, unsigned pos2) {
        // Validate indices, then swap elements
        if (pos1 < 0 || pos1 >= length) {
            throw std::runtime_error("first index " + std::to_string(pos1) + " is invalid");
        } else if (pos2 < 0 || pos2 >= length) {
            throw std::runtime_error("second index " + std::to_string(pos2) + " is invalid");
        } else {
            std::swap(data[pos1], data[pos2]);
        }
    }

    stringVector &stringVector::operator=(stringVector const &rhs) {
        // Check for self-assignment
        if (this == &rhs) {
            return *this;
        }

        // Empty out the object, reserve memory, and copy data
        delete[] data;

        allocated_length = rhs.allocated_length;
        data = new std::string[allocated_length];
        for (int i = 0; i < rhs.length; ++i) {
            data[i] = rhs.data[i];
        }
        length = rhs.length;

        return *this;
    }

    std::string &stringVector::operator[](unsigned position) {
        if (position < 0 || position >= length) {
            throw std::runtime_error("index " + std::to_string(position) + " is invalid");
        } else {
            return data[position];
        }
    }

    void stringVector::sort() {
        // Bubble sort, where lowercase letters come before uppercase letters
        for (unsigned pass = 1; pass < length; pass++) {
            for (size_t j = 0; j < length - 1; ++j) {
                // Switch case of letters to override sort order
                std::string first = data[j];
                std::string second = data[j + 1];

                for (char &i : first) {
                    if (i >= 65 && i <= 90) {
                        i += 32;
                    } else if (i >= 97 && i <= 122) {
                        i -= 32;
                    }
                }

                for (char &i : second) {
                    if (i >= 65 && i <= 90) {
                        i += 32;
                    } else if (i >= 97 && i <= 122) {
                        i -= 32;
                    }
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