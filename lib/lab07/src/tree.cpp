#include "../inc/tree.h"
#include <iostream>

namespace lab7 {
    void clear(node *to_clear);

    tree::tree() {
        root = nullptr;
        tree_size = 0;
    }

    tree::tree(const tree &copy) : tree() {
        *this = copy;
    }

    tree::~tree() {
        clear(root);
    }

    void recursiveInsert(node *&current, int value) {
        if (!current) current = new node(value);
        else if (value < current->data) recursiveInsert(current->left, value);
        else if (value > current->data) recursiveInsert(current->right, value);
        else if (value == current->data) current->frequency++;
    }

    void tree::insert(int value) {
        recursiveInsert(root, value);
        tree_size++;
    }

    node *minimumRecursive(node *&current) {
        return (!current->left) ? current : minimumRecursive(current->left);
    }

    bool recursiveRemove(node *&current, int key) {
        if (!current) return false;
        else if (key < current->data) return recursiveRemove(current->left, key);
        else if (key > current->data) return recursiveRemove(current->right, key);
        else if (key == current->data) {
            if (current->frequency == 1) {
                if (!current->left && !current->right) {
                    // Node being removed has no child nodes
                    // Delete the node
                    delete current;
                    current = nullptr;
                } else if (!current->left ^ !current->right) {
                    // Node being removed has one child node
                    // Replace the node with the child node
                    node *toBeRemoved = current;
                    current = (current->left) ? current->left : current->right;
                    delete toBeRemoved;
                } else {
                    // Node being removed has two child nodes
                    // Replace the node with the smallest larger node
                    node *rightMinimum = minimumRecursive(current->right);
                    current->data = rightMinimum->data;
                    current->frequency = rightMinimum->frequency;

                    recursiveRemove(rightMinimum, rightMinimum->data);
                }
            } else current->frequency--;
            return true;
        }
        return false;
    }

    bool tree::remove(int key) {
        if (recursiveRemove(root, key)) {
            tree_size--;
            return true;
        } else return false;
    }

    int levelRecursive(node *current, int key, const int level = 0) {
        if (!current) return -1;
        else if (key == current->data) return level;
        else if (key < current->data) return levelRecursive(current->left, key, level + 1);
        else if (key > current->data) return levelRecursive(current->right, key, level + 1);
        return -1;
    }

    int tree::level(int key) {
        return levelRecursive(root, key);
    }

    std::string pathToRecursive(node *current, int key, const std::string &path = "") {
        if (!current) return "";
        else if (key == current->data) return path + std::to_string(current->data) + "\n";
        else if (key < current->data) return pathToRecursive(current->left, key, path + std::to_string(current->data) + " -> ");
        else if (key > current->data) return pathToRecursive(current->right, key, path + std::to_string(current->data) + " -> ");
        return "";
    }

    void tree::path_to(int key) {
        std::cout << pathToRecursive(root, key);
    }

    unsigned tree::size() const {
        return tree_size;
    }

    unsigned depthRecursive(node *current) {
        return (!current) ? 0 : std::max(depthRecursive(current->left), depthRecursive(current->right)) + 1;
    }

    unsigned tree::depth() {
        return depthRecursive(root);
    }

    node *getNodeRecursive(node *current, int key) {
        if (!current) return nullptr;
        else if (key == current->data) return current;
        else if (key < current->data) return getNodeRecursive(current->left, key);
        else if (key > current->data) return getNodeRecursive(current->right, key);
        return nullptr;
    }

    bool tree::in_tree(int key) {
        return getNodeRecursive(root, key);
    }

    unsigned tree::get_frequency(int key) {
        node *node = getNodeRecursive(root, key);
        return (node) ? node->frequency : 0;
    }

    std::string operator*(const std::string &str, unsigned cnt) {
        std::string output;
        while (cnt--) output += str + " ";
        return output;
    }

    std::string toStringRecursive(node *current) {
        return (current) ? toStringRecursive(current->left) + " " + std::to_string(current->data) * current->frequency + " " + toStringRecursive(current->right) : "";
    }

    std::string trimWhitespace(std::string str) {
        if (str.empty()) return str;

        if (str[0] == ' ') str.erase(str.begin());
        for (unsigned i = 1; i < str.length() - 1; i++) {
            if (str[i] == ' ' && str[i + 1] == ' ') str.erase(str.begin() + i--);
        }

        return str + "\n";
    }

    std::string tree::to_string() {
        return trimWhitespace(toStringRecursive(root));
    }

    void tree::print() {
        std::cout << *this;
    }

    std::ostream &operator<<(std::ostream &stream, tree &RHS) {
        stream << RHS.to_string();
        return stream;
    }

    void operatorEqualsRecursive(node *root, node *current) {
        if (!current) return;
        if (current->left != nullptr) operatorEqualsRecursive(root, current->left);
        if (current->right != nullptr) operatorEqualsRecursive(root, current->right);
        for (int i = 0; i < current->frequency; i++) recursiveInsert(root, current->data);
    }

    tree &tree::operator=(const tree &rhs) {
        if (this == &rhs) return *this;

        clear(root);
        root = new node(rhs.root);

        operatorEqualsRecursive(root, rhs.root);

        remove(root->data);

        tree_size = rhs.tree_size;

        return *this;
    }

//    // Return a vector with all of the nodes that are greater than the input key in the tree
//    std::vector<int> tree::values_above(int key) {
//        return std::vector<int>();
//    }
//
//    // Merge rhs into this
//    tree tree::operator+(const tree &rhs) const {
//        return tree();
//    }
//
//    // Balance the tree using any published algorithm
//    void tree::balance() {
//        return;
//    }

    void clear(node *to_clear) {
        if (!to_clear) return;
        if (to_clear->left != nullptr) clear(to_clear->left);
        if (to_clear->right != nullptr) clear(to_clear->right);
        delete to_clear;
    }
}