#include <cmath>
#include "../inc/HashTable.h"

namespace lab8 {
    unsigned HashTable::DJB2(const std::string& to_hash) {
        unsigned int hash = 5381;
        for (char c : to_hash) hash = ((hash << 5) + hash) + c;
        return hash;
    }

    unsigned HashTable::BKDR(const std::string& to_hash) {
        unsigned int seed = 131;
        unsigned int hash = 0;
        for (char c : to_hash) hash = (hash * seed) + c;
        return hash;
    }

    void HashTable::expand() {
        // Consider the table to be full at 70% of the largest maxSize
        if (maxSize == PRIMES[15]) throw std::runtime_error("maximum array size " + std::to_string(currentSize) + " reached");

        // Keep track of the old array and size
        auto *oldTable = hashTableArray;
        unsigned oldCurrentSize = currentSize;

        // Get the next maxSize, create a new array with the new maxSize, and reset the size
        for (unsigned PRIME : PRIMES) {
            if (maxSize < PRIME) {
                maxSize = PRIME;
                break;
            }
        }
        hashTableArray = new key_value[maxSize];
        currentSize = 0;

        // Each value must be reinserted since the new maxSize changes the hash index
        for (unsigned i = 0; currentSize < oldCurrentSize; i++) if (!oldTable[i].key.empty()) insert(oldTable[i].key, oldTable[i].value);

        delete[] oldTable;
    }

    HashTable::HashTable(char probingTechnique) {
        if (probingTechnique == 'l' || probingTechnique == 'q' || probingTechnique == 'd') this->probingTechnique = probingTechnique;
        else throw std::runtime_error("probingTechnique technique '" + std::to_string(probingTechnique) + "' is invalid (valid techniques: 'l' for linear, 'q' for quadratic, 'd' for double");

        maxSize = PRIMES[0];
        hashTableArray = new key_value[maxSize];
        currentSize = 0;
    }

    HashTable::~HashTable() {
        delete[] hashTableArray;
    }

    bool HashTable::insert(const std::string &key, int value) {
        if (key.empty()) throw std::runtime_error("key cannot be empty");
        if (value == 0) throw std::runtime_error("value cannot be 0");

        unsigned hash1 = DJB2(key);
        for (unsigned attempt = 0; attempt < maxSize; attempt++) {
            unsigned index;
            if (probingTechnique == 'l') index = (hash1 + attempt) % maxSize;
            else if (probingTechnique == 'q') index = (hash1 + unsigned(pow(attempt, 2))) % maxSize;
            else index = (hash1 + attempt * BKDR(key)) % maxSize;

            if (hashTableArray[index].key.empty()) {
                hashTableArray[index].key = key;
                hashTableArray[index].value = value;
                currentSize++;

                if (currentSize >= maxSize * 0.7) expand();

                return true;
            } else if (hashTableArray[index].key == key) return false;
        }
        return false;
    }

    bool HashTable::inTable(const std::string &key) {
        if (key.empty()) throw std::runtime_error("key cannot be empty");

        unsigned hash1 = DJB2(key);
        for (unsigned attempt = 0; attempt < maxSize; attempt++) {
            unsigned index;
            if (probingTechnique == 'l') index = (hash1 + attempt) % maxSize;
            else if (probingTechnique == 'q') index = (hash1 + unsigned(pow(attempt, 2))) % maxSize;
            else index = (hash1 + attempt * BKDR(key)) % maxSize;

            if (hashTableArray[index].key == key) return true;
        }
        return false;
    }

    int HashTable::get(const std::string &key) {
        if (key.empty()) throw std::runtime_error("key cannot be empty");

        unsigned hash1 = DJB2(key);
        for (unsigned attempt = 0; attempt < maxSize; attempt++) {
            unsigned index;
            if (probingTechnique == 'l') index = (hash1 + attempt) % maxSize;
            else if (probingTechnique == 'q') index = (hash1 + unsigned(pow(attempt, 2))) % maxSize;
            else index = (hash1 + attempt * BKDR(key)) % maxSize;

            if (hashTableArray[index].key == key) return hashTableArray[index].value;
        }
        return 0;
    }

    void HashTable::update(const std::string &key, int value) {
        if (key.empty()) throw std::runtime_error("key cannot be empty");
        if (value == 0) throw std::runtime_error("value cannot be 0");

        unsigned hash1 = DJB2(key);
        for (unsigned attempt = 0; attempt < maxSize; attempt++) {
            unsigned index;
            if (probingTechnique == 'l') index = (hash1 + attempt) % maxSize;
            else if (probingTechnique == 'q') index = (hash1 + unsigned(pow(attempt, 2))) % maxSize;
            else index = (hash1 + attempt * BKDR(key)) % maxSize;

            if (hashTableArray[index].key == key) {
                hashTableArray[index].value = value;
                return;
            }
        }
        insert(key, value);
    }

    void HashTable::remove(const std::string &key) {
        if (key.empty()) throw std::runtime_error("key cannot be empty");

        unsigned hash1 = DJB2(key);
        for (unsigned attempt = 0; attempt < maxSize; attempt++) {
            unsigned index;
            if (probingTechnique == 'l') index = (hash1 + attempt) % maxSize;
            else if (probingTechnique == 'q') index = (hash1 + unsigned(pow(attempt, 2))) % maxSize;
            else index = (hash1 + attempt * BKDR(key)) % maxSize;

            if (hashTableArray[index].key == key) {
                hashTableArray[index].key.clear();
                hashTableArray[index].value = 0;
                currentSize--;

                return;
            }
        }
    }

    // Format: [index]key:value
    std::string HashTable::toString() {
        std::string string;
        for (unsigned i = 0; i < maxSize; i++) if (!hashTableArray[i].key.empty()) string += "[" + std::to_string(i) + "]" + hashTableArray[i].key + ":" + std::to_string(hashTableArray[i].value) + "\n";
        return string;
    }
}
