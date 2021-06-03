#include "gtest/gtest.h"
#include "DoublyLinkedList.h"
#include <algorithm>
#include <random>

class DoublyLinkedListTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        doublyLinkedListUT = new lab6::DoublyLinkedList();
    }

public:
    lab6::DoublyLinkedList *doublyLinkedListUT;
};

TEST(CrashTest, doublyLinkedList_crashTest) {
    auto *doublyLinkedListUT = new lab6::DoublyLinkedList();
    delete doublyLinkedListUT;
}

TEST_F(DoublyLinkedListTest, append_doesNotCrash) {
    ASSERT_NO_FATAL_FAILURE(doublyLinkedListUT->append(1));
}

TEST_F(DoublyLinkedListTest, append_emptyList_addsValueToList) {
    doublyLinkedListUT->append(10);
    doublyLinkedListUT->append(11);
    doublyLinkedListUT->append(12);
    EXPECT_EQ(11, doublyLinkedListUT->at(1));
}

TEST_F(DoublyLinkedListTest, append_populatedList_addsValueToEnd) {
    doublyLinkedListUT->append(10);
    ASSERT_EQ(10, doublyLinkedListUT->at(0));

    doublyLinkedListUT->append(11);
    EXPECT_EQ(10, doublyLinkedListUT->at(0));
    EXPECT_EQ(11, doublyLinkedListUT->at(1));

    doublyLinkedListUT->append(12);
    EXPECT_EQ(10, doublyLinkedListUT->at(0));
    EXPECT_EQ(11, doublyLinkedListUT->at(1));
    EXPECT_EQ(12, doublyLinkedListUT->at(2));

    for (int i = 13; i < 1000; i++) doublyLinkedListUT->append(i);
    for (int i = 0; i < 990; i++) ASSERT_EQ(i + 10, doublyLinkedListUT->at(i));
}

TEST_F(DoublyLinkedListTest, at_doesNotCrash) {
    doublyLinkedListUT->append(10);
    doublyLinkedListUT->append(11);
    doublyLinkedListUT->append(12);
    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT->at(1));
}

TEST_F(DoublyLinkedListTest, at_validIndex_getsDataAtIndex) {
    doublyLinkedListUT->append(10);
    ASSERT_EQ(10, doublyLinkedListUT->at(0));

    doublyLinkedListUT->append(11);
    EXPECT_EQ(10, doublyLinkedListUT->at(0));
    EXPECT_EQ(11, doublyLinkedListUT->at(1));
}

TEST_F(DoublyLinkedListTest, at_invalidIndex_throws) {
    doublyLinkedListUT->append(10);
    ASSERT_NO_THROW(doublyLinkedListUT->at(0));
    EXPECT_ANY_THROW(doublyLinkedListUT->at(10));
    EXPECT_ANY_THROW(doublyLinkedListUT->at(-1));
    EXPECT_ANY_THROW(doublyLinkedListUT->at(1000000));
}

TEST_F(DoublyLinkedListTest, at_emptyList_throws) {
    ASSERT_ANY_THROW(doublyLinkedListUT->at(0));
    EXPECT_ANY_THROW(doublyLinkedListUT->at(10));
    EXPECT_ANY_THROW(doublyLinkedListUT->at(-1));
    EXPECT_ANY_THROW(doublyLinkedListUT->at(1000000));
}

TEST_F(DoublyLinkedListTest, getSet_doesNotCrash) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT->getSet(2, 7));
}

TEST_F(DoublyLinkedListTest, getSet_validIndices_getsSetAtIndices) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    ASSERT_EQ(std::vector<int>({12, 13, 14, 15, 16, 17}), doublyLinkedListUT->getSet(2, 7));
    EXPECT_EQ(std::vector<int>({14}), doublyLinkedListUT->getSet(4, 4));
    EXPECT_EQ(std::vector<int>({10, 11, 12, 13, 14, 15, 16, 17, 18, 19}), doublyLinkedListUT->getSet(0, 9));
}

TEST_F(DoublyLinkedListTest, getSet_wronglyOrdredIndices_getsSetAtIndices) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    ASSERT_EQ(std::vector<int>({12, 13, 14, 15, 16, 17}), doublyLinkedListUT->getSet(7, 2));
    EXPECT_EQ(std::vector<int>({10, 11, 12, 13, 14, 15, 16, 17, 18, 19}), doublyLinkedListUT->getSet(9, 0));
}

TEST_F(DoublyLinkedListTest, getSet_invalidIndices_throws) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    ASSERT_ANY_THROW(doublyLinkedListUT->getSet(0, 10));
    EXPECT_ANY_THROW(doublyLinkedListUT->getSet(10, 0));
    EXPECT_ANY_THROW(doublyLinkedListUT->getSet(100, 200));
    EXPECT_ANY_THROW(doublyLinkedListUT->getSet(200, 100));
}

TEST_F(DoublyLinkedListTest, getSet_emptyList_throws) {
    ASSERT_ANY_THROW(doublyLinkedListUT->getSet(0, 1));
    EXPECT_ANY_THROW(doublyLinkedListUT->getSet(0, 10));
    EXPECT_ANY_THROW(doublyLinkedListUT->getSet(0, -1));
    EXPECT_ANY_THROW(doublyLinkedListUT->getSet(0, 1000000));
    EXPECT_ANY_THROW(doublyLinkedListUT->getSet(0, 0));
    EXPECT_ANY_THROW(doublyLinkedListUT->getSet(1, 0));
    EXPECT_ANY_THROW(doublyLinkedListUT->getSet(10, 0));
    EXPECT_ANY_THROW(doublyLinkedListUT->getSet(-1, 0));
    EXPECT_ANY_THROW(doublyLinkedListUT->getSet(1000000, 0));
}

TEST_F(DoublyLinkedListTest, insert_doesNotCrash) {
    doublyLinkedListUT->append(10);
    doublyLinkedListUT->append(11);
    doublyLinkedListUT->append(12);
    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT->insert(100, 1));
}

TEST_F(DoublyLinkedListTest, insert_validIndex_addsValueAtIndex) {
    doublyLinkedListUT->append(10);
    doublyLinkedListUT->append(11);
    doublyLinkedListUT->append(12);
    doublyLinkedListUT->insert(100, 1);
    ASSERT_EQ(10, doublyLinkedListUT->at(0));
    EXPECT_EQ(100, doublyLinkedListUT->at(1));
    EXPECT_EQ(11, doublyLinkedListUT->at(2));
    EXPECT_EQ(12, doublyLinkedListUT->at(3));

    doublyLinkedListUT->insert(200, 0);
    ASSERT_EQ(200, doublyLinkedListUT->at(0));
    EXPECT_EQ(10, doublyLinkedListUT->at(1));
    EXPECT_EQ(100, doublyLinkedListUT->at(2));
    EXPECT_EQ(11, doublyLinkedListUT->at(3));
    EXPECT_EQ(12, doublyLinkedListUT->at(4));

    doublyLinkedListUT->insert(300, 5);
    ASSERT_EQ(200, doublyLinkedListUT->at(0));
    EXPECT_EQ(10, doublyLinkedListUT->at(1));
    EXPECT_EQ(100, doublyLinkedListUT->at(2));
    EXPECT_EQ(11, doublyLinkedListUT->at(3));
    EXPECT_EQ(12, doublyLinkedListUT->at(4));
    EXPECT_EQ(300, doublyLinkedListUT->at(5));
}

TEST_F(DoublyLinkedListTest, insert_emptyList_addsValue) {
    doublyLinkedListUT->insert(100, 0);
    EXPECT_EQ(100, doublyLinkedListUT->at(0));
}

TEST_F(DoublyLinkedListTest, insert_invalidIndex_throws) {
    ASSERT_ANY_THROW(doublyLinkedListUT->insert(100, 2));

    doublyLinkedListUT->append(10);
    doublyLinkedListUT->append(11);
    doublyLinkedListUT->append(12);

    EXPECT_ANY_THROW(doublyLinkedListUT->insert(200, 10));
}

TEST_F(DoublyLinkedListTest, remove_doesNotCrash) {
    doublyLinkedListUT->append(10);
    doublyLinkedListUT->append(11);
    doublyLinkedListUT->append(12);
    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT->remove(1));
}

TEST_F(DoublyLinkedListTest, remove_validIndex_removesValueAtIndex) {
    doublyLinkedListUT->append(10);
    doublyLinkedListUT->append(11);
    doublyLinkedListUT->append(12);
    doublyLinkedListUT->append(13);

    doublyLinkedListUT->remove(1);
    ASSERT_EQ(10, doublyLinkedListUT->at(0));
    EXPECT_EQ(12, doublyLinkedListUT->at(1));
    EXPECT_EQ(13, doublyLinkedListUT->at(2));

    doublyLinkedListUT->remove(0);
    EXPECT_EQ(12, doublyLinkedListUT->at(0));
    EXPECT_EQ(13, doublyLinkedListUT->at(1));

    doublyLinkedListUT->remove(1);
    EXPECT_EQ(12, doublyLinkedListUT->at(0));

    doublyLinkedListUT->remove(0);
    EXPECT_ANY_THROW(doublyLinkedListUT->at(0));
}

TEST_F(DoublyLinkedListTest, remove_invalidIndex_throws) {
    doublyLinkedListUT->append(10);
    doublyLinkedListUT->append(11);
    doublyLinkedListUT->append(12);

    ASSERT_ANY_THROW(doublyLinkedListUT->remove(3));
    EXPECT_ANY_THROW(doublyLinkedListUT->remove(10));
    EXPECT_ANY_THROW(doublyLinkedListUT->remove(-1));
    EXPECT_ANY_THROW(doublyLinkedListUT->remove(1000000));
}

TEST_F(DoublyLinkedListTest, remove_emptyList_throws) {
    ASSERT_ANY_THROW(doublyLinkedListUT->remove(0));
    EXPECT_ANY_THROW(doublyLinkedListUT->remove(3));
    EXPECT_ANY_THROW(doublyLinkedListUT->remove(10));
    EXPECT_ANY_THROW(doublyLinkedListUT->remove(-1));
    EXPECT_ANY_THROW(doublyLinkedListUT->remove(1000000));
}

TEST_F(DoublyLinkedListTest, initialValueConstructor_doesNotCrash) {
    delete doublyLinkedListUT;
    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT = new lab6::DoublyLinkedList(10));
}

TEST_F(DoublyLinkedListTest, initialValueConstructor_addsValue) {
    delete doublyLinkedListUT;
    doublyLinkedListUT = new lab6::DoublyLinkedList(10);
    EXPECT_EQ(10, doublyLinkedListUT->at(0));
}

TEST_F(DoublyLinkedListTest, vectorConstructor_doesNotCrash) {
    delete doublyLinkedListUT;
    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT = new lab6::DoublyLinkedList(std::vector<int>({10, 11, 12, 13, 14})));
}

TEST_F(DoublyLinkedListTest, vectorConstructor_addsValue) {
    delete doublyLinkedListUT;
    doublyLinkedListUT = new lab6::DoublyLinkedList(std::vector<int>({10, 11, 12, 13, 14}));
    ASSERT_EQ(10, doublyLinkedListUT->at(0));
    EXPECT_EQ(11, doublyLinkedListUT->at(1));
    EXPECT_EQ(12, doublyLinkedListUT->at(2));
    EXPECT_EQ(13, doublyLinkedListUT->at(3));
    EXPECT_EQ(14, doublyLinkedListUT->at(4));
}

TEST_F(DoublyLinkedListTest, copyConstructor_doesNotCrash) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    EXPECT_NO_FATAL_FAILURE(auto *copy = new lab6::DoublyLinkedList(*doublyLinkedListUT));
}

TEST_F(DoublyLinkedListTest, copyConstructor_copiesValues) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    lab6::DoublyLinkedList *copy = new lab6::DoublyLinkedList(*doublyLinkedListUT);

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(i + 10, doublyLinkedListUT->at(i));
        ASSERT_EQ(i + 10, copy->at(i));
    }
}

TEST_F(DoublyLinkedListTest, copyConstructor_hardCopiesValues) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    lab6::DoublyLinkedList *copy = new lab6::DoublyLinkedList(*doublyLinkedListUT);

    doublyLinkedListUT->append(20);
    ASSERT_EQ(20, doublyLinkedListUT->at(10));
    EXPECT_ANY_THROW(copy->at(10));

    doublyLinkedListUT->insert(100, 3);
    EXPECT_EQ(100, doublyLinkedListUT->at(3));
    EXPECT_EQ(13, copy->at(3));

    copy->append(20);
    EXPECT_EQ(19, doublyLinkedListUT->at(10));
    EXPECT_EQ(20, copy->at(10));

    copy->remove(5);
    EXPECT_EQ(14, doublyLinkedListUT->at(5));
    EXPECT_EQ(16, copy->at(5));
}

TEST_F(DoublyLinkedListTest, split_doesNotCrash) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT->split(5));
}

TEST_F(DoublyLinkedListTest, split_validIndex_splitsListAtIndex) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    auto *doublyLinkedList2UT = new lab6::DoublyLinkedList(doublyLinkedListUT->split(5));
    for (int i = 0; i < 5; i++) ASSERT_EQ(i + 10, doublyLinkedListUT->at(i));
    for (int i = 0; i < 5; i++) ASSERT_EQ(i + 15, doublyLinkedList2UT->at(i));
    EXPECT_ANY_THROW(doublyLinkedListUT->at(5));
    EXPECT_ANY_THROW(doublyLinkedList2UT->at(5));

    auto *doublyLinkedList3UT = new lab6::DoublyLinkedList(doublyLinkedList2UT->split(3));
    for (int i = 0; i < 5; i++) ASSERT_EQ(i + 10, doublyLinkedListUT->at(i));
    for (int i = 0; i < 3; i++) ASSERT_EQ(i + 15, doublyLinkedList2UT->at(i));
    for (int i = 0; i < 2; i++) ASSERT_EQ(i + 18, doublyLinkedList3UT->at(i));
    EXPECT_ANY_THROW(doublyLinkedListUT->at(5));
    EXPECT_ANY_THROW(doublyLinkedList2UT->at(3));
    EXPECT_ANY_THROW(doublyLinkedList3UT->at(2));

    auto *doublyLinkedList4UT = new lab6::DoublyLinkedList(doublyLinkedList3UT->split(1));
    for (int i = 0; i < 5; i++) ASSERT_EQ(i + 10, doublyLinkedListUT->at(i));
    for (int i = 0; i < 3; i++) ASSERT_EQ(i + 15, doublyLinkedList2UT->at(i));
    EXPECT_EQ(18, doublyLinkedList3UT->at(0));
    EXPECT_EQ(19, doublyLinkedList4UT->at(0));
    EXPECT_ANY_THROW(doublyLinkedListUT->at(5));
    EXPECT_ANY_THROW(doublyLinkedList2UT->at(3));
    EXPECT_ANY_THROW(doublyLinkedList3UT->at(1));
    EXPECT_ANY_THROW(doublyLinkedList4UT->at(1));
}

TEST_F(DoublyLinkedListTest, split_index0_splitsOffEntireList) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    auto *doublyLinkedList2UT = new lab6::DoublyLinkedList(doublyLinkedListUT->split(0));
    ASSERT_ANY_THROW(doublyLinkedListUT->at(0));
    for (int i = 0; i < 10; i++) ASSERT_EQ(i + 10, doublyLinkedList2UT->at(i));
    EXPECT_ANY_THROW(doublyLinkedList2UT->at(10));

    auto *doublyLinkedList3UT = new lab6::DoublyLinkedList(doublyLinkedList2UT->split(3));
    EXPECT_ANY_THROW(doublyLinkedListUT->at(0));
    for (int i = 0; i < 3; i++) ASSERT_EQ(i + 10, doublyLinkedList2UT->at(i));
    for (int i = 0; i < 7; i++) ASSERT_EQ(i + 13, doublyLinkedList3UT->at(i));
    EXPECT_ANY_THROW(doublyLinkedListUT->at(0));
    EXPECT_ANY_THROW(doublyLinkedList2UT->at(3));
    EXPECT_ANY_THROW(doublyLinkedList2UT->at(7));
}

TEST_F(DoublyLinkedListTest, split_invalidIndex_throws) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    ASSERT_ANY_THROW(doublyLinkedListUT->split(10));
    EXPECT_ANY_THROW(doublyLinkedListUT->split(-1));
    EXPECT_ANY_THROW(doublyLinkedListUT->split(1000000));
}

TEST_F(DoublyLinkedListTest, split_emptyList_throws) {
    ASSERT_ANY_THROW(doublyLinkedListUT->split(0));
    EXPECT_ANY_THROW(doublyLinkedListUT->split(10));
    EXPECT_ANY_THROW(doublyLinkedListUT->split(-1));
    EXPECT_ANY_THROW(doublyLinkedListUT->split(1000000));
}

TEST_F(DoublyLinkedListTest, splitSet_doesNotCrash) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT->splitSet(2, 5));
}

TEST_F(DoublyLinkedListTest, splitSet_validIndices_splitsSetOffList) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    auto *doublyLinkedList2UT = new lab6::DoublyLinkedList(doublyLinkedListUT->splitSet(2, 4));
    for (int i = 0; i < 2; i++) ASSERT_EQ(i + 10, doublyLinkedListUT->at(i));
    for (int i = 2; i < 5; i++) ASSERT_EQ(i + 13, doublyLinkedListUT->at(i));
    for (int i = 0; i < 3; i++) ASSERT_EQ(i + 12, doublyLinkedList2UT->at(i));
    EXPECT_ANY_THROW(doublyLinkedListUT->at(7));
    EXPECT_ANY_THROW(doublyLinkedList2UT->at(3));

    auto *doublyLinkedList3UT = new lab6::DoublyLinkedList(doublyLinkedList2UT->splitSet(0, 0));
    for (int i = 0; i < 2; i++) ASSERT_EQ(i + 10, doublyLinkedListUT->at(i));
    for (int i = 2; i < 5; i++) ASSERT_EQ(i + 13, doublyLinkedListUT->at(i));
    for (int i = 0; i < 2; i++) ASSERT_EQ(i + 13, doublyLinkedList2UT->at(i));
    ASSERT_EQ(12, doublyLinkedList3UT->at(0));
    EXPECT_ANY_THROW(doublyLinkedListUT->at(7));
    EXPECT_ANY_THROW(doublyLinkedList2UT->at(2));
    EXPECT_ANY_THROW(doublyLinkedList3UT->at(1));
}

TEST_F(DoublyLinkedListTest, splitSet_wronglyOrderedIndices_splitsSetOffList) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    auto *doublyLinkedList2UT = new lab6::DoublyLinkedList(doublyLinkedListUT->splitSet(4, 2));
    for (int i = 0; i < 2; i++) ASSERT_EQ(i + 10, doublyLinkedListUT->at(i));
    for (int i = 2; i < 5; i++) ASSERT_EQ(i + 13, doublyLinkedListUT->at(i));
    for (int i = 0; i < 3; i++) ASSERT_EQ(i + 12, doublyLinkedList2UT->at(i));
    EXPECT_ANY_THROW(doublyLinkedListUT->at(7));
    EXPECT_ANY_THROW(doublyLinkedList2UT->at(3));
}

TEST_F(DoublyLinkedListTest, splitSet_invalidIndices_throws) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    ASSERT_ANY_THROW(doublyLinkedListUT->splitSet(0, 10));
    EXPECT_ANY_THROW(doublyLinkedListUT->splitSet(2, 10));
    EXPECT_ANY_THROW(doublyLinkedListUT->splitSet(100, 200));
    EXPECT_ANY_THROW(doublyLinkedListUT->splitSet(10, 10));
    EXPECT_ANY_THROW(doublyLinkedListUT->splitSet(10, 0));
    EXPECT_ANY_THROW(doublyLinkedListUT->splitSet(10, 2));
    EXPECT_ANY_THROW(doublyLinkedListUT->splitSet(200, 100));
}

TEST_F(DoublyLinkedListTest, size_doesNotCrash) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT->size());
}

TEST_F(DoublyLinkedListTest, size_tracksAppendsInsertionsRemovalsAndSplits) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    ASSERT_EQ(10, doublyLinkedListUT->size());

    doublyLinkedListUT->insert(100, 1);
    EXPECT_EQ(11, doublyLinkedListUT->size());

    doublyLinkedListUT->remove(2);
    EXPECT_EQ(10, doublyLinkedListUT->size());

    doublyLinkedListUT->split(8);
    EXPECT_EQ(8, doublyLinkedListUT->size());

    doublyLinkedListUT->splitSet(2, 4);
    EXPECT_EQ(5, doublyLinkedListUT->size());
}

TEST_F(DoublyLinkedListTest, size_emptyList_0) {
    EXPECT_EQ(0, doublyLinkedListUT->size());
}

TEST_F(DoublyLinkedListTest, empty_doesNotCrash) {
    doublyLinkedListUT->append(10);
    doublyLinkedListUT->append(11);
    doublyLinkedListUT->append(12);
    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT->empty());
}

TEST_F(DoublyLinkedListTest, empty_tracksAppendsInsertionsRemovalsAndSplits) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    EXPECT_FALSE(doublyLinkedListUT->empty());

    doublyLinkedListUT->insert(100, 1);
    EXPECT_FALSE(doublyLinkedListUT->empty());

    doublyLinkedListUT->remove(2);
    EXPECT_FALSE(doublyLinkedListUT->empty());

    doublyLinkedListUT->split(8);
    EXPECT_FALSE(doublyLinkedListUT->empty());

    doublyLinkedListUT->splitSet(2, 4);
    EXPECT_FALSE(doublyLinkedListUT->empty());

    for (int i = 0; i < 5; i++) doublyLinkedListUT->remove(0);
    EXPECT_TRUE(doublyLinkedListUT->empty());
}

TEST_F(DoublyLinkedListTest, empty_emptyList_true) {
    EXPECT_TRUE(doublyLinkedListUT->empty());
}

TEST_F(DoublyLinkedListTest, swap_doesNotCrash) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT->swap(3, 6));
}

TEST_F(DoublyLinkedListTest, swap_validIndices_swapsValues) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    doublyLinkedListUT->swap(3, 6);
    ASSERT_EQ(16, doublyLinkedListUT->at(3));
    EXPECT_EQ(13, doublyLinkedListUT->at(6));

    doublyLinkedListUT->swap(0, 9);
    EXPECT_EQ(19, doublyLinkedListUT->at(0));
    EXPECT_EQ(10, doublyLinkedListUT->at(9));

    doublyLinkedListUT->swap(4, 4);
    EXPECT_EQ(14, doublyLinkedListUT->at(4));
}

TEST_F(DoublyLinkedListTest, swap_wronglyOrderedIndices_swapsValues) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    doublyLinkedListUT->swap(6, 3);
    ASSERT_EQ(16, doublyLinkedListUT->at(3));
    EXPECT_EQ(13, doublyLinkedListUT->at(6));

    doublyLinkedListUT->swap(9, 0);
    EXPECT_EQ(19, doublyLinkedListUT->at(0));
    EXPECT_EQ(10, doublyLinkedListUT->at(9));
}

TEST_F(DoublyLinkedListTest, swap_invalidIndices_throws) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    ASSERT_ANY_THROW(doublyLinkedListUT->swap(0, 10));
    EXPECT_ANY_THROW(doublyLinkedListUT->swap(2, 10));
    EXPECT_ANY_THROW(doublyLinkedListUT->swap(100, 200));
    EXPECT_ANY_THROW(doublyLinkedListUT->swap(10, 10));
    EXPECT_ANY_THROW(doublyLinkedListUT->swap(10, 0));
    EXPECT_ANY_THROW(doublyLinkedListUT->swap(10, 2));
    EXPECT_ANY_THROW(doublyLinkedListUT->swap(200, 100));
}

TEST_F(DoublyLinkedListTest, swapSet_doesNotCrash) {
    for (int i = 10; i < 60; i++) doublyLinkedListUT->append(i);
    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT->swapSet(2, 4, 6, 8));
}

TEST_F(DoublyLinkedListTest, swapSet_validIndices_swapsValues) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    doublyLinkedListUT->swap(3, 6);
    ASSERT_EQ(16, doublyLinkedListUT->at(3));
    EXPECT_EQ(13, doublyLinkedListUT->at(6));

    doublyLinkedListUT->swap(0, 9);
    EXPECT_EQ(19, doublyLinkedListUT->at(0));
    EXPECT_EQ(10, doublyLinkedListUT->at(9));

    doublyLinkedListUT->swap(4, 4);
    EXPECT_EQ(14, doublyLinkedListUT->at(4));
}

TEST_F(DoublyLinkedListTest, swapSet_wronglyOrderedIndices_swapsValues) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    doublyLinkedListUT->swap(6, 3);
    ASSERT_EQ(16, doublyLinkedListUT->at(3));
    EXPECT_EQ(13, doublyLinkedListUT->at(6));

    doublyLinkedListUT->swap(9, 0);
    EXPECT_EQ(19, doublyLinkedListUT->at(0));
    EXPECT_EQ(10, doublyLinkedListUT->at(9));
}

TEST_F(DoublyLinkedListTest, swapSet_overlappingIndices_throws) {
    for (int i = 10; i < 30; i++) doublyLinkedListUT->append(i);

    ASSERT_ANY_THROW(doublyLinkedListUT->swapSet(7, 10, 8, 12));
    EXPECT_ANY_THROW(doublyLinkedListUT->swapSet(10, 7, 8, 12));
    EXPECT_ANY_THROW(doublyLinkedListUT->swapSet(7, 10, 12, 8));
    EXPECT_ANY_THROW(doublyLinkedListUT->swapSet(10, 7, 12, 8));
    EXPECT_ANY_THROW(doublyLinkedListUT->swapSet(0, 20, 5, 15));
    EXPECT_ANY_THROW(doublyLinkedListUT->swapSet(0, 20, 0, 20));
}

TEST_F(DoublyLinkedListTest, swapSet_invalidIndices_throws) {
    for (int i = 10; i < 30; i++) doublyLinkedListUT->append(i);

    ASSERT_ANY_THROW(doublyLinkedListUT->swapSet(0, 12, 18, 24));
    EXPECT_ANY_THROW(doublyLinkedListUT->swapSet(12, 0, 18, 24));
    EXPECT_ANY_THROW(doublyLinkedListUT->swapSet(0, 12, 24, 18));
    EXPECT_ANY_THROW(doublyLinkedListUT->swapSet(12, 0, 24, 18));
    EXPECT_ANY_THROW(doublyLinkedListUT->swapSet(0, 40, 55, 80));
    EXPECT_ANY_THROW(doublyLinkedListUT->swapSet(40, 0, 55, 80));
    EXPECT_ANY_THROW(doublyLinkedListUT->swapSet(0, 40, 80, 55));
    EXPECT_ANY_THROW(doublyLinkedListUT->swapSet(40, 0, 80, 55));
}

TEST_F(DoublyLinkedListTest, sort_doesNotCrash) {
    std::vector<int> unsorted;
    for (int val = 10; val < 110; val++) unsorted.push_back(val);
    std::shuffle(unsorted.begin(), unsorted.end(), std::random_device());

    delete doublyLinkedListUT;
    doublyLinkedListUT = new lab6::DoublyLinkedList(unsorted);

    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT->sort());
}

TEST_F(DoublyLinkedListTest, sort_populatedList_sortsList) {
    std::vector<int> unsorted;
    for (int val = 10; val < 110; val++) unsorted.push_back(val);
    std::shuffle(unsorted.begin(), unsorted.end(), std::random_device());

    delete doublyLinkedListUT;
    doublyLinkedListUT = new lab6::DoublyLinkedList(unsorted);

    doublyLinkedListUT->sort();

    for (unsigned i = 0; i < 100; i++) ASSERT_EQ(i + 10, doublyLinkedListUT->at(i));
}

TEST_F(DoublyLinkedListTest, sort_emptyList_doesNothing) {
    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT->sort());
}

TEST_F(DoublyLinkedListTest, operatorPlus_doesNotCrash) {
    auto *doublyLinkedList2UT = new lab6::DoublyLinkedList;
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    for (int i = 20; i < 30; i++) doublyLinkedList2UT->append(i);

    EXPECT_NO_FATAL_FAILURE(*doublyLinkedListUT + *doublyLinkedList2UT);
}

TEST_F(DoublyLinkedListTest, operatorPlus_populatedLists_combinesLists) {
    auto *doublyLinkedList2UT = new lab6::DoublyLinkedList;
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    for (int i = 20; i < 30; i++) doublyLinkedList2UT->append(i);

    auto *doublyLinkedList3UT = new lab6::DoublyLinkedList(*doublyLinkedListUT + *doublyLinkedList2UT);
    for (unsigned i = 0; i < 20; i++) ASSERT_EQ(i + 10, doublyLinkedList3UT->at(i));
}

TEST_F(DoublyLinkedListTest, operatorPlus_sameLists_combinesLists) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    auto *doublyLinkedList3UT = new lab6::DoublyLinkedList(*doublyLinkedListUT + *doublyLinkedListUT);
    for (unsigned i = 0; i < 10; i++) ASSERT_EQ(i + 10, doublyLinkedList3UT->at(i));
    for (unsigned i = 10; i < 20; i++) ASSERT_EQ(i, doublyLinkedList3UT->at(i));
}

TEST_F(DoublyLinkedListTest, operatorPlus_emptyLists_doesNothing) {
    auto *doublyLinkedList2UT = new lab6::DoublyLinkedList;
    auto *doublyLinkedList3UT = new lab6::DoublyLinkedList(*doublyLinkedListUT + *doublyLinkedList2UT);
    EXPECT_ANY_THROW(doublyLinkedList3UT->at(0));
}

TEST_F(DoublyLinkedListTest, operatorEquals_doesNotCrash) {
    auto *doublyLinkedList2UT = new lab6::DoublyLinkedList(2);
    EXPECT_NO_FATAL_FAILURE(*doublyLinkedListUT = *doublyLinkedList2UT);
}

TEST_F(DoublyLinkedListTest, operatorEquals_populatedLists_copiesValues) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    lab6::DoublyLinkedList *copy = &*doublyLinkedListUT;

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(i + 10, doublyLinkedListUT->at(i));
        ASSERT_EQ(i + 10, copy->at(i));
    }
}

TEST_F(DoublyLinkedListTest, operatorEquals_populatedLists_hardCopiesValues) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    auto *copy = new lab6::DoublyLinkedList;
    copy->operator=(*doublyLinkedListUT);

    doublyLinkedListUT->append(20);
    ASSERT_EQ(20, doublyLinkedListUT->at(10));
    EXPECT_ANY_THROW(copy->at(10));

    doublyLinkedListUT->insert(100, 3);
    EXPECT_EQ(100, doublyLinkedListUT->at(3));
    EXPECT_EQ(13, copy->at(3));

    copy->append(20);
    EXPECT_EQ(19, doublyLinkedListUT->at(10));
    EXPECT_EQ(20, copy->at(10));

    copy->remove(5);
    EXPECT_EQ(14, doublyLinkedListUT->at(5));
    EXPECT_EQ(16, copy->at(5));
}

TEST_F(DoublyLinkedListTest, operatorEquals_selfAssignment_doesNothing) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    doublyLinkedListUT->operator=(*doublyLinkedListUT);

    doublyLinkedListUT->append(20);
    ASSERT_EQ(20, doublyLinkedListUT->at(10));

    doublyLinkedListUT->insert(100, 3);
    EXPECT_EQ(100, doublyLinkedListUT->at(3));

    doublyLinkedListUT->append(20);
    EXPECT_EQ(19, doublyLinkedListUT->at(10));

    doublyLinkedListUT->remove(5);
    EXPECT_EQ(15, doublyLinkedListUT->at(5));
}

TEST_F(DoublyLinkedListTest, operatorPlusEquals_doesNotCrash) {
    auto *doublyLinkedList2UT = new lab6::DoublyLinkedList(2);
    EXPECT_NO_FATAL_FAILURE(*doublyLinkedListUT += *doublyLinkedList2UT);
}

TEST_F(DoublyLinkedListTest, operatorPlusEquals_populatedLists_appendsList) {
    auto *doublyLinkedList2UT = new lab6::DoublyLinkedList;
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    for (int i = 20; i < 30; i++) doublyLinkedList2UT->append(i);

    doublyLinkedListUT->operator+=(*doublyLinkedList2UT);
    for (int i = 0; i < 20; i++) ASSERT_EQ(i + 10, doublyLinkedListUT->at(i));
}

TEST_F(DoublyLinkedListTest, operatorEqualsComparison_doesNotCrash) {
    auto *doublyLinkedList2UT = new lab6::DoublyLinkedList(2);
    EXPECT_NO_FATAL_FAILURE(doublyLinkedListUT->operator==(*doublyLinkedList2UT));
}

TEST_F(DoublyLinkedListTest, operatorEqualsComparison_populatedLists_comparesLists) {
    auto *doublyLinkedList2UT = new lab6::DoublyLinkedList;
    for (int i = 10; i < 20; i++) {
        doublyLinkedListUT->append(i);
        doublyLinkedList2UT->append(i);
    }
    ASSERT_TRUE(*doublyLinkedListUT == *doublyLinkedList2UT);

    doublyLinkedListUT->append(100);
    EXPECT_FALSE(*doublyLinkedListUT == *doublyLinkedList2UT);

    doublyLinkedList2UT->append(100);
    EXPECT_TRUE(*doublyLinkedListUT == *doublyLinkedList2UT);

    doublyLinkedList2UT->append(200);
    doublyLinkedList2UT->append(300);
    EXPECT_FALSE(*doublyLinkedListUT == *doublyLinkedList2UT);
}

TEST_F(DoublyLinkedListTest, operatorEqualsComparison_sameLists_true) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    EXPECT_TRUE(*doublyLinkedListUT == *doublyLinkedListUT);
}

TEST_F(DoublyLinkedListTest, operatorEqualsComparison_emptyLists_true) {
    auto *doublyLinkedList2UT = new lab6::DoublyLinkedList;
    EXPECT_TRUE(*doublyLinkedListUT == *doublyLinkedList2UT);
}

TEST_F(DoublyLinkedListTest, operatorInsertion_doesNotCrash) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    testing::internal::CaptureStdout();
    EXPECT_NO_FATAL_FAILURE(std::cout << *doublyLinkedListUT);
    testing::internal::GetCapturedStdout();
}

TEST_F(DoublyLinkedListTest, operatorInsertion_outputsList) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);

    testing::internal::CaptureStdout();
    std::cout << *doublyLinkedListUT;
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("NULL <- 10 <-> 11 <-> 12 <-> 13 <-> 14 <-> 15 <-> 16 <-> 17 <-> 18 <-> 19 -> NULL", output);
}

TEST_F(DoublyLinkedListTest, operatorExtraction_doesNotCrash) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    EXPECT_NO_FATAL_FAILURE(std::stringstream("100") >> *doublyLinkedListUT);
}

TEST_F(DoublyLinkedListTest, operatorExtraction_appendsInput) {
    for (int i = 10; i < 20; i++) doublyLinkedListUT->append(i);
    for (int i = 20; i < 30; i++) std::stringstream(std::to_string(i)) >> *doublyLinkedListUT;
    for (int i = 0; i < 20; i++) ASSERT_EQ(i + 10, doublyLinkedListUT->at(i));
}