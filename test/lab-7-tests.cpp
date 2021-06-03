#include "gtest/gtest.h"
#include "Tree.h"

class TreeTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        values = std::vector<int>({12, 8, 14, 15, 18, 16, 17, 19, 22, 20, 4, 10, 9, 13, 11, 5, 7, 6, 2, 1, 3});
        treeUT1 = new lab7::Tree();

        treeUT2 = new lab7::Tree();
        for (int val : values) treeUT2->insert(val);
    }

public:
    lab7::Tree *treeUT1, *treeUT2;
    std::vector<int> values;
};

TEST(CrashTest, tree_crashTest) {
    auto *treeUT = new lab7::Tree;
    delete treeUT;
}

TEST_F(TreeTest, inTree_validValue_true) {
    EXPECT_TRUE(treeUT2->inTree(12));
    EXPECT_TRUE(treeUT2->inTree(22));
    EXPECT_TRUE(treeUT2->inTree(16));
    EXPECT_TRUE(treeUT2->inTree(4));
    EXPECT_TRUE(treeUT2->inTree(11));
}

TEST_F(TreeTest, inTree_invalidValue_false) {
    EXPECT_FALSE(treeUT2->inTree(0));
    EXPECT_FALSE(treeUT2->inTree(21));
    EXPECT_FALSE(treeUT2->inTree(23));
    EXPECT_FALSE(treeUT2->inTree(-1));
    EXPECT_FALSE(treeUT2->inTree(1000000));
}

TEST_F(TreeTest, inTree_emptyTree_false) {
    EXPECT_FALSE(treeUT1->inTree(12));
    EXPECT_FALSE(treeUT1->inTree(22));
    EXPECT_FALSE(treeUT1->inTree(16));
    EXPECT_FALSE(treeUT1->inTree(4));
    EXPECT_FALSE(treeUT1->inTree(11));
    EXPECT_FALSE(treeUT1->inTree(0));
    EXPECT_FALSE(treeUT1->inTree(21));
    EXPECT_FALSE(treeUT1->inTree(23));
    EXPECT_FALSE(treeUT1->inTree(-1));
    EXPECT_FALSE(treeUT1->inTree(1000000));
}

TEST_F(TreeTest, insert_newValue_insertsNodeIntoTreeAtCorrectLocation) {
    treeUT1->insert(10);
    EXPECT_TRUE(treeUT1->inTree(10));
    EXPECT_EQ(treeUT1->size(), 1);
    treeUT1->insert(5);
    EXPECT_TRUE(treeUT1->inTree(5));
    EXPECT_EQ(treeUT1->size(), 2);
}

TEST_F(TreeTest, frequency_validValue_getsValueFrequency) {
    EXPECT_EQ(treeUT2->frequency(12), 1);
    EXPECT_EQ(treeUT2->frequency(22), 1);
    EXPECT_EQ(treeUT2->frequency(16), 1);
    EXPECT_EQ(treeUT2->frequency(4), 1);
    EXPECT_EQ(treeUT2->frequency(11), 1);
}

TEST_F(TreeTest, frequency_invalidValue_0) {
    EXPECT_EQ(treeUT2->frequency(0), 0);
    EXPECT_EQ(treeUT2->frequency(21), 0);
    EXPECT_EQ(treeUT2->frequency(23), 0);
    EXPECT_EQ(treeUT2->frequency(-1), 0);
    EXPECT_EQ(treeUT2->frequency(1000000), 0);
}

TEST_F(TreeTest, insert_sameValue_incrementsValueFrequency) {
    treeUT2->insert(12);
    EXPECT_EQ(treeUT2->frequency(12), 2);

    treeUT2->insert(22);
    EXPECT_EQ(treeUT2->frequency(22), 2);

    treeUT2->insert(16);
    EXPECT_EQ(treeUT2->frequency(16), 2);

    treeUT2->insert(4);
    EXPECT_EQ(treeUT2->frequency(4), 2);

    treeUT2->insert(11);
    EXPECT_EQ(treeUT2->frequency(11), 2);

    treeUT2->insert(12);
    EXPECT_EQ(treeUT2->frequency(12), 3);
}

TEST_F(TreeTest, remove_valueWithFrequencyOne_removesNodeFromTree) {
    EXPECT_TRUE(treeUT2->remove(6));
    EXPECT_FALSE(treeUT2->inTree(6));
    EXPECT_EQ(treeUT2->frequency(6), 0);
    EXPECT_EQ(treeUT2->size(), 20);
}

TEST_F(TreeTest, remove_valueWithFrequencyMoreThanOne_decrementsValueFrequency) {
    treeUT2->insert(6);
    EXPECT_EQ(treeUT2->frequency(6), 2);
    EXPECT_EQ(treeUT2->size(), 22);

    EXPECT_TRUE(treeUT2->remove(6));
    EXPECT_TRUE(treeUT2->inTree(6));
    EXPECT_EQ(treeUT2->frequency(6), 1);
    EXPECT_EQ(treeUT2->size(), 21);
}

TEST_F(TreeTest, remove_invalidValue_false) {
    EXPECT_FALSE(treeUT2->remove(21));
}

TEST_F(TreeTest, remove_parentNode_doesNotOrphanChildNodes) {
    EXPECT_TRUE(treeUT2->remove(4));
    EXPECT_FALSE(treeUT2->inTree(4));
    EXPECT_EQ(treeUT2->size(), 20);

    EXPECT_TRUE(treeUT2->inTree(1));
    EXPECT_TRUE(treeUT2->inTree(2));
    EXPECT_TRUE(treeUT2->inTree(3));
    EXPECT_TRUE(treeUT2->inTree(5));
    EXPECT_TRUE(treeUT2->inTree(6));
    EXPECT_TRUE(treeUT2->inTree(7));
    EXPECT_TRUE(treeUT2->inTree(8));
}

TEST_F(TreeTest, remove_root_doesNotOrphanChildNodes) {
    EXPECT_TRUE(treeUT2->remove(12));
    EXPECT_FALSE(treeUT2->inTree(12));
    EXPECT_EQ(treeUT2->size(), 20);

    EXPECT_TRUE(treeUT2->inTree(8));
    EXPECT_TRUE(treeUT2->inTree(4));
    EXPECT_TRUE(treeUT2->inTree(10));
    EXPECT_TRUE(treeUT2->inTree(14));
    EXPECT_TRUE(treeUT2->inTree(15));
    EXPECT_TRUE(treeUT2->inTree(1));
    EXPECT_TRUE(treeUT2->inTree(22));
}

TEST_F(TreeTest, size_afterInsertionsAndDeletions_tracksSize) {
    EXPECT_EQ(treeUT2->size(), 21);

    treeUT2->insert(23);
    EXPECT_EQ(treeUT2->size(), 22);

    treeUT2->insert(21);
    EXPECT_EQ(treeUT2->size(), 23);

    treeUT2->insert(12);
    EXPECT_EQ(treeUT2->size(), 24);

    treeUT2->remove(23);
    EXPECT_EQ(treeUT2->size(), 23);

    treeUT2->remove(21);
    EXPECT_EQ(treeUT2->size(), 22);

    treeUT2->remove(12);
    EXPECT_EQ(treeUT2->size(), 21);
}

TEST_F(TreeTest, size_empty_0) {
    EXPECT_EQ(treeUT1->size(), 0);
}

TEST_F(TreeTest, depth_afterInsertionsAndDeletions_tracksSize) {
    EXPECT_EQ(treeUT2->depth(), 7);

    treeUT2->insert(23);
    EXPECT_EQ(treeUT2->depth(), 7);

    treeUT2->insert(21);
    EXPECT_EQ(treeUT2->depth(), 8);

    treeUT2->insert(12);
    EXPECT_EQ(treeUT2->depth(), 8);

    treeUT2->remove(23);
    EXPECT_EQ(treeUT2->depth(), 8);

    treeUT2->remove(21);
    EXPECT_EQ(treeUT2->depth(), 7);

    treeUT2->remove(12);
    EXPECT_EQ(treeUT2->depth(), 7);
}

TEST_F(TreeTest, depth_empty_0) {
    EXPECT_EQ(treeUT1->depth(), 0);
}

TEST_F(TreeTest, level_validValue_getsLevelOfValue) {
    EXPECT_EQ(treeUT2->level(12), 0);
    EXPECT_EQ(treeUT2->level(8), 1);
    EXPECT_EQ(treeUT2->level(15), 2);
    EXPECT_EQ(treeUT2->level(9), 3);
    EXPECT_EQ(treeUT2->level(19), 4);
    EXPECT_EQ(treeUT2->level(22), 5);
    EXPECT_EQ(treeUT2->level(20), 6);
}

TEST_F(TreeTest, level_invalidValue_negative1) {
    EXPECT_EQ(treeUT2->level(0), -1);
    EXPECT_EQ(treeUT2->level(21), -1);
    EXPECT_EQ(treeUT2->level(23), -1);
    EXPECT_EQ(treeUT2->level(-1), -1);
    EXPECT_EQ(treeUT2->level(1000), -1);
}

TEST_F(TreeTest, pathTo_validValue_printsPathToConsole) {
    testing::internal::CaptureStdout();
    treeUT2->pathTo(8);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string("12 -> 8\n"));

    testing::internal::CaptureStdout();
    treeUT2->pathTo(6);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string("12 -> 8 -> 4 -> 5 -> 7 -> 6\n"));

    testing::internal::CaptureStdout();
    treeUT2->pathTo(18);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string("12 -> 14 -> 15 -> 18\n"));

    testing::internal::CaptureStdout();
    treeUT2->pathTo(13);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string("12 -> 14 -> 13\n"));

    treeUT2->insert(8);
    testing::internal::CaptureStdout();
    treeUT2->pathTo(4);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string("12 -> 8 -> 4\n"));

    treeUT2->insert(16);
    testing::internal::CaptureStdout();
    treeUT2->pathTo(16);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string("12 -> 14 -> 15 -> 18 -> 16\n"));
}

TEST_F(TreeTest, pathTo_invalidValue_printsNothing) {
    testing::internal::CaptureStdout();
    treeUT2->pathTo(0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string(""));
}

TEST_F(TreeTest, print_validTree_printsTreeToConsole) {
    testing::internal::CaptureStdout();
    treeUT2->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 22 \n"));

    treeUT2->insert(4);
    treeUT2->insert(4);
    treeUT2->insert(4);
    treeUT2->insert(11);
    treeUT2->insert(16);

    testing::internal::CaptureStdout();
    treeUT2->print();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string("1 2 3 4 4 4 4 5 6 7 8 9 10 11 11 12 13 14 15 16 16 17 18 19 20 22 \n"));
}

TEST_F(TreeTest, print_emptyTree_printsNothing) {
    testing::internal::CaptureStdout();
    treeUT1->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string(""));
}

TEST_F(TreeTest, equalsOperator_validTree_hardCopiesValues) {
    treeUT2->insert(8);
    *treeUT1 = *treeUT2;

    EXPECT_TRUE(treeUT2->inTree(15));
    EXPECT_TRUE(treeUT1->inTree(15));

    treeUT2->remove(15);
    EXPECT_FALSE(treeUT2->inTree(15));
    EXPECT_TRUE(treeUT1->inTree(15));

    EXPECT_FALSE(treeUT2->inTree(21));
    EXPECT_FALSE(treeUT1->inTree(21));

    treeUT1->insert(21);
    EXPECT_FALSE(treeUT2->inTree(21));
    EXPECT_TRUE(treeUT1->inTree(21));

    EXPECT_EQ(treeUT2->frequency(8), 2);
    EXPECT_EQ(treeUT1->frequency(8), 2);
}

//TEST_F(TreeTest, values_above) {
//    std::vector<int> compare = std::vector<int>({13, 14, 15, 16, 17, 18, 19, 20, 22});
//    EXPECT_EQ(treeUT2->values_above(12), compare);
//
//    treeUT2->values_above(13);
//    treeUT2->insert(10);
//    treeUT2->insert(13);
//    treeUT2->insert(13);
//    treeUT2->insert(15);
//    treeUT2->insert(19);
//
//    compare = std::vector<int>({17, 18, 19, 19, 20, 22});
//    EXPECT_EQ(treeUT2->values_above(16), compare);
//
//    compare = std::vector<int>({11, 12, 13, 13, 13, 14, 15, 15, 16, 17, 18, 19, 19, 20, 22});
//    EXPECT_EQ(treeUT2->values_above(10), compare);
//
//    compare = std::vector<int>({22});
//    EXPECT_EQ(treeUT2->values_above(20), compare);
//
//    compare = std::vector<int>({7, 8, 9, 10, 10, 11, 12, 13, 13, 13, 14, 15, 15, 16, 17, 18, 19, 19, 20, 22});
//    EXPECT_EQ(treeUT2->values_above(6), compare);
//}