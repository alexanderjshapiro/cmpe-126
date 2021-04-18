#ifndef CMPE126S18_LABS_LIB_LAB7_NODE_H
#define CMPE126S18_LABS_LIB_LAB7_NODE_H

namespace lab7 {
    class node {
    public:
        node *left, *right;
        int data;
        unsigned frequency;

        explicit node(int input_data) : data(input_data), frequency(1), left(nullptr), right(nullptr) {}

        explicit node(node *copy_node) {
            data = copy_node->data;
            frequency = copy_node->frequency;
            left = nullptr;
            right = nullptr;
        }
    };
}
#endif //CMPE126S18_LABS_NODE_H