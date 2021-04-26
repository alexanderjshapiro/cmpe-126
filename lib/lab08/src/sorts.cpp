#include "DoublyLinkedList.h"

namespace lab6 {
    unsigned partition(DoublyLinkedList &list, unsigned low, unsigned high) {
        int pivot = list.getValue(high);

        unsigned i = low;
        for (unsigned j = low; j < high; j++) {
            // If current element is smaller than the pivot
            if (list.getValue(j) < pivot) list.swap(i++, j);
        }

        list.swap(i, high);

        return i;
    }

    void quickSort(DoublyLinkedList &list, unsigned low, unsigned high) {
        // Check if list is empty or only has one element
        unsigned size = (high - low) + 1;
        if (size < 2) return;

        if (low < high) {
            unsigned partitionIndex = partition(list, low, high);

            // Sort the half below and above the partition index
            quickSort(list, low, partitionIndex - 1);
            quickSort(list, partitionIndex + 1, high);
        }
    }

    DoublyLinkedList merge(DoublyLinkedList left, DoublyLinkedList right) {
        DoublyLinkedList list;

        // From left to right in each half, add the smaller value between the two lists to the list
        unsigned leftSize = left.size(), rightSize = right.size();
        unsigned leftIndex = 0, rightIndex = 0;
        while (leftIndex < leftSize && rightIndex < rightSize) {
            if (left.getValue(leftIndex) <= right.getValue(rightIndex)) list.append(left.getValue(leftIndex++));
            else list.append(right.getValue(rightIndex++));
        }

        // Add the remaining values from the non-empty list
        while (leftIndex < leftSize) list.append(left.getValue(leftIndex++));
        while (rightIndex < rightSize) list.append(right.getValue(rightIndex++));

        return list;
    }

    DoublyLinkedList mergeSortRecursive(DoublyLinkedList list) {
        // Check if the list is empty or has one element, meaning it is already sorted
        unsigned listSize = list.size();
        if (listSize < 2) return list;

        // Split the list in half
        DoublyLinkedList left = list.splitSet(0, (listSize - 1) / 2);
        DoublyLinkedList right = list;

        // Sort each half of the list
        left = mergeSortRecursive(left);
        right = mergeSortRecursive(right);

        // Combine the halves together in sorted order
        return merge(left, right);
    }

    void mergeSort(DoublyLinkedList &list) {
        list = mergeSortRecursive(list);
    }
}