#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"

#include <iostream>
// #include <vector>

namespace lab7 {
    class Tree {
    private:
        TreeNode *root;
        unsigned treeSize;

    public:
        Tree();
        Tree(const Tree &other);
        ~Tree();

        bool inTree(int value) const;
        unsigned frequency(int value) const;
        int level(int value) const;
        void pathTo(int value) const;
        unsigned size() const;
        unsigned depth() const;

        void insert(int value);
        bool remove(int value);

        // std::vector<int> valuesAbove(int value) const;

        // void balance();

        std::string toString() const;
        void print() const;

        Tree &operator=(const Tree &other);
        // Tree operator+(const Tree &other) const;

        friend std::ostream &operator<<(std::ostream &stream, const Tree &tree);
    };
}

#endif // TREE_H