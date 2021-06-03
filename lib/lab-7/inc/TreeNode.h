#ifndef TREENODE_H
#define TREENODE_H

namespace lab7 {
    class TreeNode {
    public:
        TreeNode *left, *right;
        int value;
        unsigned frequency;

        explicit TreeNode(int value) : value(value), frequency(1), left(nullptr), right(nullptr) {}
        explicit TreeNode(TreeNode *treeNode) : value(treeNode->value), frequency(treeNode->frequency), left(nullptr), right(nullptr) {}
    };
}
#endif // TREENODE_H