#ifndef CMPE126S18_LABS_TREE_H
#define CMPE126S18_LABS_TREE_H
#include "node.h"
#include <iostream>
#include <vector>

namespace lab7 {
    class tree {
        node *root;
        unsigned tree_size;
    public:
        tree();
        tree(const tree &copy);
        ~tree();

        void insert(int value);
        bool remove(int key);
        bool in_tree(int key);
        unsigned get_frequency(int key);

        std::string to_string();
        int level(int key);
        void path_to(int key);
        unsigned size() const;
        unsigned depth();
        void print();

        tree &operator=(const tree &rhs);
        friend std::ostream &operator<<(std::ostream &stream, tree &RHS);

//        std::vector<int> values_above(int key);
//        tree operator+(const tree &rhs) const;
//        void balance();
    };
}

#endif //CMPE126S18_LABS_TREE_H