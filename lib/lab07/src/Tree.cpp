#include "Tree.h"

namespace lab7 {
    void clear(TreeNode *treeNode);

    Tree::Tree() {
        root = nullptr;
        treeSize = 0;
    }

    Tree::Tree(const Tree &other) : Tree() {
        *this = other;
    }

    Tree::~Tree() {
        clear(root);
    }

    TreeNode *getNodeRecursive(TreeNode *current, int key) {
        if (!current) return nullptr;
        else if (key == current->value) return current;
        else if (key < current->value) return getNodeRecursive(current->left, key);
        else if (key > current->value) return getNodeRecursive(current->right, key);
        return nullptr;
    }

    bool Tree::inTree(int value) const {
        return getNodeRecursive(root, value);
    }

    unsigned Tree::getFrequency(int value) const {
        TreeNode *node = getNodeRecursive(root, value);
        return (node) ? node->frequency : 0;
    }

    int levelRecursive(TreeNode *current, int key, const int level = 0) {
        if (!current) return -1;
        else if (key == current->value) return level;
        else if (key < current->value) return levelRecursive(current->left, key, level + 1);
        else if (key > current->value) return levelRecursive(current->right, key, level + 1);
        return -1;
    }

    int Tree::level(int value) const {
        return levelRecursive(root, value);
    }

    std::string pathToRecursive(TreeNode *current, int key, const std::string &path = "") {
        if (!current) return "";
        else if (key == current->value) return path + std::to_string(current->value) + "\n";
        else if (key < current->value) return pathToRecursive(current->left, key, path + std::to_string(current->value) + " -> ");
        else if (key > current->value) return pathToRecursive(current->right, key, path + std::to_string(current->value) + " -> ");
        return "";
    }

    void Tree::pathTo(int value) const {
        std::cout << pathToRecursive(root, value);
    }

    unsigned Tree::size() const {
        return treeSize;
    }

    unsigned depthRecursive(TreeNode *current) {
        return (!current) ? 0 : std::max(depthRecursive(current->left), depthRecursive(current->right)) + 1;
    }

    unsigned Tree::depth() const {
        return depthRecursive(root);
    }

    void recursiveInsert(TreeNode *&current, int value) {
        if (!current) current = new TreeNode(value);
        else if (value < current->value) recursiveInsert(current->left, value);
        else if (value > current->value) recursiveInsert(current->right, value);
        else if (value == current->value) current->frequency++;
    }

    void Tree::insert(int value) {
        recursiveInsert(root, value);
        treeSize++;
    }

    TreeNode *minimumRecursive(TreeNode *&current) {
        return (!current->left) ? current : minimumRecursive(current->left);
    }

    bool recursiveRemove(TreeNode *&current, int key) {
        if (!current) return false;
        else if (key < current->value) return recursiveRemove(current->left, key);
        else if (key > current->value) return recursiveRemove(current->right, key);
        else if (key == current->value) {
            if (current->frequency == 1) {
                if (!current->left && !current->right) {
                    // LinkedListNode being removed has no child nodes
                    // Delete the LinkedListNode
                    delete current;
                    current = nullptr;
                } else if (!current->left ^ !current->right) {
                    // LinkedListNode being removed has one child LinkedListNode
                    // Replace the LinkedListNode with the child LinkedListNode
                    TreeNode *toBeRemoved = current;
                    current = (current->left) ? current->left : current->right;
                    delete toBeRemoved;
                } else {
                    // LinkedListNode being removed has two child nodes
                    // Replace the LinkedListNode with the smallest larger LinkedListNode
                    TreeNode *rightMinimum = minimumRecursive(current->right);
                    current->value = rightMinimum->value;
                    current->frequency = rightMinimum->frequency;

                    recursiveRemove(rightMinimum, rightMinimum->value);
                }
            } else current->frequency--;
            return true;
        }
        return false;
    }

    bool Tree::remove(int value) {
        if (recursiveRemove(root, value)) {
            treeSize--;
            return true;
        } else return false;
    }

    std::string operator*(const std::string &str, unsigned cnt) {
        std::string output;
        while (cnt--) output += str + " ";
        return output;
    }

    std::string toStringRecursive(TreeNode *current) {
        return (current) ? toStringRecursive(current->left) + " " + std::to_string(current->value) * current->frequency + " " + toStringRecursive(current->right) : "";
    }

    std::string trimWhitespace(std::string str) {
        if (str.empty()) return str;

        if (str[0] == ' ') str.erase(str.begin());
        for (unsigned i = 1; i < str.length() - 1; i++) {
            if (str[i] == ' ' && str[i + 1] == ' ') str.erase(str.begin() + i--);
        }

        return str + "\n";
    }

    std::string Tree::toString() const {
        return trimWhitespace(toStringRecursive(root));
    }

    void Tree::print() const {
        std::cout << *this;
    }

    std::ostream &operator<<(std::ostream &stream, const Tree &tree) {
        stream << tree.toString();
        return stream;
    }

    void operatorEqualsRecursive(TreeNode *root, TreeNode *current) {
        if (!current) return;
        if (current->left != nullptr) operatorEqualsRecursive(root, current->left);
        if (current->right != nullptr) operatorEqualsRecursive(root, current->right);
        for (int i = 0; i < current->frequency; i++) recursiveInsert(root, current->value);
    }

    Tree &Tree::operator=(const Tree &other) {
        if (this == &other) return *this;

        clear(root);
        root = new TreeNode(other.root);

        operatorEqualsRecursive(root, other.root);

        remove(root->value);

        treeSize = other.treeSize;

        return *this;
    }

//    std::vector<int> tree::values_above(int key) {
//        return std::vector<int>();
//    }

//    tree tree::operator+(const tree &rhs) const {
//        return tree();
//    }

//    void tree::balance() {
//        return;
//    }

    void clear(TreeNode *treeNode) {
        if (!treeNode) return;
        if (treeNode->left != nullptr) clear(treeNode->left);
        if (treeNode->right != nullptr) clear(treeNode->right);
        delete treeNode;
    }
}