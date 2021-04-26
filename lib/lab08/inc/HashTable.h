#ifndef CMPE126S18_LABS_HASH_TABLE_H
#define CMPE126S18_LABS_HASH_TABLE_H

#include <string>
#include <vector>

namespace lab8 {

    struct key_value {
        std::string key;
        int value;

        key_value() : key(""), value(0) { }
    };

    class HashTable {
        key_value *hashTableArray;
        char probingTechnique;
        unsigned maxSize;
        unsigned currentSize;

        const unsigned PRIMES[16] = {31, 67, 137, 277, 557, 1117, 2237, 4481, 8963, 17929, 35863, 71741, 143483, 286999, 574003, 1148029}; // PRIME[n+1]= next prime after 2*PRIME[n]. Use this for setting max size

        static unsigned DJB2(const std::string& to_hash);
        static unsigned BKDR(const std::string& to_hash);
        void expand();

    public:
        HashTable(char probingTechnique);
        ~HashTable();

        bool insert(const std::string& key, int value);
        int get(const std::string& key);
        void remove(const std::string& key);
        bool inTable(const std::string &key);
        void update(const std::string& key, int value);

        // Functions use for testings
        unsigned getSize() { return currentSize; };
        unsigned getMaxSize() { return maxSize; };
        std::string toString(); //Used for testing
    };
}

#endif //CMPE126S18_LABS_HASH_TABLE_H