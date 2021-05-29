#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cmath>
#include <string>

namespace lab8 {

    struct HashTableEntry {
        std::string key;
        int value;

        HashTableEntry() : key(std::string()), value(0) {}
    };

    class HashTable {
    private:
        HashTableEntry *hashTableArray;
        char probingTechnique;
        unsigned maxSize;
        unsigned currentSize;

        const unsigned PRIMES[16] = {31, 67, 137, 277, 557, 1117, 2237, 4481, 8963, 17929, 35863, 71741, 143483, 286999, 574003, 1148029};

        static unsigned hashDJB2(const std::string &string);
        static unsigned hashBKDR(const std::string &string);

        void expand();

    public:
        HashTable(char probingTechnique);
        ~HashTable();

        int get(const std::string &key);
        bool inTable(const std::string &key);

        bool insert(const std::string &key, int value);
        void update(const std::string &key, int value);
        void remove(const std::string &key);

        unsigned getSize() { return currentSize; };
        unsigned getMaxSize() { return maxSize; };
        std::string toString();
    };
}

#endif // HASHTABLE_H