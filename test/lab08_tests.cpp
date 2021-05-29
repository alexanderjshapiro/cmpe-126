#include <random>
#include "gtest/gtest.h"
#include "../lib/lab08/inc/HashTable.h"
#include "../lib/lab08/src/sorts.cpp"

class HashTableTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        hashTableLUT = new lab8::HashTable('l');
        hashTableQUT = new lab8::HashTable('q');
        hashTableDUT = new lab8::HashTable('d');
    }

    virtual void TearDown() {
        delete hashTableLUT;
        delete hashTableQUT;
        delete hashTableDUT;
    }

public:
    lab8::HashTable *hashTableLUT, *hashTableQUT, *hashTableDUT;
};

TEST(CrashTest, hashTable_crashTest) {
    auto *hashTableUT = new lab8::HashTable('l');
    delete hashTableUT;
}

TEST_F(HashTableTest, hashTable_invalidProbingTechnique_throws) {
    EXPECT_ANY_THROW(auto *hashTableUT = new lab8::HashTable('z'));
}

TEST_F(HashTableTest, insert_doesNotCrash) {
    EXPECT_NO_FATAL_FAILURE(hashTableLUT->insert("foo", 1));
}

TEST_F(HashTableTest, insert_validKey_addsValueToTable) {
    ASSERT_TRUE(hashTableLUT->insert("foo", 1));
    EXPECT_TRUE(hashTableLUT->inTable("foo"));
}

TEST_F(HashTableTest, insert_linear_collidingKeys_addsValuesToTable) {
    std::string key;

    for (unsigned i = 1; i < 22; i++) {
        key = "key" + std::to_string(i);
        ASSERT_TRUE(hashTableLUT->insert(key, i));
        ASSERT_TRUE(hashTableLUT->inTable(key))
                                    << "\n     Key: \"" + key + "\""
                                    << "\n   Value: " + std::to_string(i)
                                    << "\nCur Size: " + std::to_string(hashTableLUT->getSize())
                                    << "\nMax Size: " + std::to_string(hashTableLUT->getMaxSize())
                                    << "\n\nArray: \n" + hashTableLUT->toString();
    }
}

TEST_F(HashTableTest, insert_quadratic_collidingKeys_addsValuesToTable) {
    std::string key;

    for (unsigned i = 1; i < 22; i++) {
        key = "key" + std::to_string(i);
        ASSERT_TRUE(hashTableQUT->insert(key, i));
        ASSERT_TRUE(hashTableQUT->inTable(key))
                                    << "\n     Key: \"" + key + "\""
                                    << "\n   Value: " + std::to_string(i)
                                    << "\nCur Size: " + std::to_string(hashTableQUT->getSize())
                                    << "\nMax Size: " + std::to_string(hashTableQUT->getMaxSize())
                                    << "\n\nArray: \n" + hashTableQUT->toString();
    }
}

TEST_F(HashTableTest, insert_double_collidingKeys_addsValuesToTable) {
    std::string key;

    for (unsigned i = 1; i < 22; i++) {
        key = "key" + std::to_string(i);
        ASSERT_TRUE(hashTableDUT->insert(key, i));
        ASSERT_TRUE(hashTableDUT->inTable(key))
                                    << "\n     Key: \"" + key + "\""
                                    << "\n   Value: " + std::to_string(i)
                                    << "\nCur Size: " + std::to_string(hashTableDUT->getSize())
                                    << "\nMax Size: " + std::to_string(hashTableDUT->getMaxSize())
                                    << "\n\nArray: \n" + hashTableDUT->toString();
    }
}

TEST_F(HashTableTest, insert_expand_copiesValuesToNewTable) {
    std::string key;

    for (unsigned i = 1; i < 22; i++) {
        key = "key" + std::to_string(i);
        ASSERT_TRUE(hashTableLUT->insert(key, i));
        ASSERT_TRUE(hashTableLUT->inTable(key))
                                    << "\n     Key: \"" + key + "\""
                                    << "\n   Value: " + std::to_string(i)
                                    << "\nCur Size: " + std::to_string(hashTableLUT->getSize())
                                    << "\nMax Size: " + std::to_string(hashTableLUT->getMaxSize())
                                    << "\n\nArray: \n" + hashTableLUT->toString();
    }

    ASSERT_TRUE(hashTableLUT->insert("key22", 22));

    for (unsigned i = 1; i < 23; i++) {
        key = "key" + std::to_string(i);
        ASSERT_TRUE(hashTableLUT->inTable(key))
                                    << "\n     Key: \"" + key + "\""
                                    << "\n   Value: " + std::to_string(i)
                                    << "\nCur Size: " + std::to_string(hashTableLUT->getSize())
                                    << "\nMax Size: " + std::to_string(hashTableLUT->getMaxSize())
                                    << "\n\nArray: \n" + hashTableDUT->toString();
    }

    for (unsigned i = 23; i < 47; i++) {
        key = "key" + std::to_string(i);
        ASSERT_TRUE(hashTableLUT->insert(key, i));
        ASSERT_TRUE(hashTableLUT->inTable(key))
                                    << "\n     Key: \"" + key + "\""
                                    << "\n   Value: " + std::to_string(i)
                                    << "\nCur Size: " + std::to_string(hashTableLUT->getSize())
                                    << "\nMax Size: " + std::to_string(hashTableLUT->getMaxSize())
                                    << "\n\nArray: \n" + hashTableLUT->toString();
    }

    ASSERT_TRUE(hashTableLUT->insert("key47", 47));

    for (unsigned i = 1; i < 48; i++) {
        key = "key" + std::to_string(i);
        ASSERT_TRUE(hashTableLUT->inTable(key))
                                    << "\n     Key: \"" + key + "\""
                                    << "\n   Value: " + std::to_string(i)
                                    << "\nCur Size: " + std::to_string(hashTableLUT->getSize())
                                    << "\nMax Size: " + std::to_string(hashTableLUT->getMaxSize())
                                    << "\n\nArray: \n" + hashTableLUT->toString();
    }
}

// Add "DISABLED_" to the front of the test names to skip them and work on other tests if they are taking too long
// e.g. "DISABLED_insert_linear_fullTable_throws"
TEST_F(HashTableTest, insert_linear_fullTable_throws) {
    std::string key;

    for (unsigned i = 1; i < 803621; i++) {
        key = "key-" + std::to_string(random()) + "-" + std::to_string(i);
        ASSERT_TRUE(hashTableLUT->insert(key, i));
        ASSERT_TRUE(hashTableLUT->inTable(key))
                                    << "\n     Key: \"" + key + "\""
                                    << "\n   Value: " + std::to_string(i)
                                    << "\nCur Size: " + std::to_string(hashTableLUT->getSize())
                                    << "\nMax Size: " + std::to_string(hashTableLUT->getMaxSize())
                                    << "\n\nArray: \n" + hashTableLUT->toString();
    }

    ASSERT_ANY_THROW(hashTableLUT->insert("key803621", 803621));
}

TEST_F(HashTableTest, insert_quadratic_fullTable_throws) {
    std::string key;

    for (unsigned i = 1; i < 803621; i++) {
        key = "key-" + std::to_string(random()) + "-" + std::to_string(i);
        ASSERT_TRUE(hashTableQUT->insert(key, i));
        ASSERT_TRUE(hashTableQUT->inTable(key))
                                    << "\n     Key: \"" + key + "\""
                                    << "\n   Value: " + std::to_string(i)
                                    << "\nCur Size: " + std::to_string(hashTableQUT->getSize())
                                    << "\nMax Size: " + std::to_string(hashTableQUT->getMaxSize())
                                    << "\n\nArray: \n" + hashTableQUT->toString();
    }

    ASSERT_ANY_THROW(hashTableQUT->insert("key803621", 803621));
}

TEST_F(HashTableTest, insert_double_fullTable_throws) {
    std::string key;

    for (unsigned i = 1; i < 803621; i++) {
        key = "key-" + std::to_string(random()) + "-" + std::to_string(i);
        ASSERT_TRUE(hashTableDUT->insert(key, i));
        ASSERT_TRUE(hashTableDUT->inTable(key))
                                    << "\n     Key: \"" + key + "\""
                                    << "\n   Value: " + std::to_string(i)
                                    << "\nCur Size: " + std::to_string(hashTableDUT->getSize())
                                    << "\nMax Size: " + std::to_string(hashTableDUT->getMaxSize())
                                    << "\n\nArray: \n" + hashTableDUT->toString();
    }

    ASSERT_ANY_THROW(hashTableDUT->insert("key803621", 803621));
}

TEST_F(HashTableTest, insert_duplicateKey_false) {
    EXPECT_TRUE(hashTableLUT->insert("foo", 1));
    EXPECT_FALSE(hashTableLUT->insert("foo", 1));

    EXPECT_TRUE(hashTableQUT->insert("foo", 1));
    EXPECT_FALSE(hashTableQUT->insert("foo", 1));

    EXPECT_TRUE(hashTableDUT->insert("foo", 1));
    EXPECT_FALSE(hashTableDUT->insert("foo", 1));
}

TEST_F(HashTableTest, insert_invalidKeyValuethrows) {
    EXPECT_ANY_THROW(hashTableLUT->insert("", 1));
    EXPECT_ANY_THROW(hashTableLUT->insert("foo", 0));
    EXPECT_ANY_THROW(hashTableLUT->insert("", 0));
}

TEST_F(HashTableTest, inTable_doesNotCrash) {
    ASSERT_TRUE(hashTableLUT->insert("foo", 1));
    EXPECT_NO_FATAL_FAILURE(hashTableLUT->inTable("foo"));
}

TEST_F(HashTableTest, inTable_keyExists_true) {
    ASSERT_TRUE(hashTableLUT->insert("foo", 1));
    EXPECT_TRUE(hashTableLUT->inTable("foo"));
}

TEST_F(HashTableTest, inTable_keyDoesNotExist_false) {
    EXPECT_FALSE(hashTableLUT->inTable("foo"));

    ASSERT_TRUE(hashTableLUT->insert("foo", 1));
    EXPECT_FALSE(hashTableLUT->inTable("bar"));
}

TEST_F(HashTableTest, inTable_invalidKey_throws) {
    EXPECT_ANY_THROW(hashTableLUT->inTable(""));
}

TEST_F(HashTableTest, get_doesNotCrash) {
    ASSERT_TRUE(hashTableLUT->insert("foo", 1));
    EXPECT_NO_FATAL_FAILURE(hashTableLUT->get("foo"));
}

TEST_F(HashTableTest, get_keyExists_keyValue) {
    ASSERT_TRUE(hashTableLUT->insert("foo", 1));
    EXPECT_EQ(1, hashTableLUT->get("foo"));
}

TEST_F(HashTableTest, get_keyDoesNotExist_0) {
    EXPECT_EQ(0, hashTableLUT->get("foo"));

    ASSERT_TRUE(hashTableLUT->insert("foo", 1));
    EXPECT_EQ(0, hashTableLUT->get("bar"));
}

TEST_F(HashTableTest, get_invalidKey_throws) {
    EXPECT_ANY_THROW(hashTableLUT->get(""));
}

TEST_F(HashTableTest, update_doesNotCrash) {
    ASSERT_TRUE(hashTableLUT->insert("foo", 1));
    EXPECT_NO_FATAL_FAILURE(hashTableLUT->update("foo", 1));
}

TEST_F(HashTableTest, update_keyExists_updatesValue) {
    ASSERT_TRUE(hashTableLUT->insert("foo", 1));
    hashTableLUT->update("foo", 2);
    EXPECT_EQ(2, hashTableLUT->get("foo"));
}

TEST_F(HashTableTest, update_keyDoesNotExist_insertsKeyValue) {
    hashTableLUT->update("foo", 1);
    EXPECT_TRUE(hashTableLUT->inTable("foo"));
}

TEST_F(HashTableTest, update_invalidKeyValue_throws) {
    EXPECT_ANY_THROW(hashTableLUT->update("", 1));
    EXPECT_ANY_THROW(hashTableLUT->update("foo", 0));
    EXPECT_ANY_THROW(hashTableLUT->update("", 0));
}

TEST_F(HashTableTest, remove_doesNotCrash) {
    ASSERT_TRUE(hashTableLUT->insert("foo", 1));
    EXPECT_NO_FATAL_FAILURE(hashTableLUT->remove("foo"));
}

TEST_F(HashTableTest, remove_keyExists_removesKeyValue) {
    ASSERT_TRUE(hashTableLUT->insert("foo", 1));
    ASSERT_NO_FATAL_FAILURE(hashTableLUT->remove("foo"));
    ASSERT_FALSE(hashTableLUT->inTable("foo"));

    std::string key;
    for (unsigned i = 1; i < 22; i++) {
        key = "key" + std::to_string(i);
        ASSERT_TRUE(hashTableLUT->insert(key, i));
        ASSERT_TRUE(hashTableLUT->inTable(key))
                                    << "\n     Key: \"" + key + "\""
                                    << "\n   Value: " + std::to_string(i)
                                    << "\nCur Size: " + std::to_string(hashTableLUT->getSize())
                                    << "\nMax Size: " + std::to_string(hashTableLUT->getMaxSize())
                                    << "\n\nArray: \n" + hashTableLUT->toString();
    }

    EXPECT_NO_FATAL_FAILURE(hashTableLUT->remove("key10"));
    EXPECT_FALSE(hashTableLUT->inTable("key10"));

    EXPECT_NO_FATAL_FAILURE(hashTableLUT->remove("key2"));
    EXPECT_FALSE(hashTableLUT->inTable("key2"));

    EXPECT_NO_FATAL_FAILURE(hashTableLUT->remove("key17"));
    EXPECT_FALSE(hashTableLUT->inTable("key17"));
}

TEST_F(HashTableTest, remove_keyDoesNotExist_doesNothing) {
    EXPECT_NO_FATAL_FAILURE(hashTableLUT->remove("foo"));
}

TEST_F(HashTableTest, remove_invalidKeyValue_throws) {
    EXPECT_ANY_THROW(hashTableLUT->remove(""));
}

TEST_F(HashTableTest, toString_doesNotCrash) {
    EXPECT_NO_FATAL_FAILURE(hashTableLUT->toString());
}

TEST_F(HashTableTest, toString_validTable_returnsFormattedString) {
    std::string key;

    for (unsigned i = 1; i < 10; i++) {
        key = "key" + std::to_string(i);
        ASSERT_TRUE(hashTableLUT->insert(key, i));
        ASSERT_TRUE(hashTableLUT->inTable(key)) << "on attempt " + std::to_string(i) + " where key = \"" + key + "\"";
    }

    std::string expectedOutput = "[6]key1:1\n[7]key2:2\n[8]key3:3\n[9]key4:4\n[10]key5:5\n[11]key6:6\n[12]key7:7\n[13]key8:8\n[14]key9:9\n";

    EXPECT_EQ(expectedOutput, hashTableLUT->toString());
}

TEST_F(HashTableTest, toString_emptyTable_doesNothing) {
    EXPECT_EQ("", hashTableLUT->toString());
}

class SortsTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        for (int i = 0; i < 10; i++) listSmallNumbers.push_back(i);
        std::shuffle(listSmallNumbers.begin(), listSmallNumbers.end(), std::random_device());
        listSmall = new lab6::DoublyLinkedList(listSmallNumbers);

        for (int i = 0; i < 3000; i++) listLargeNumbers.push_back(i);
        std::shuffle(listLargeNumbers.begin(), listLargeNumbers.end(), std::random_device());
        listLarge = new lab6::DoublyLinkedList(listLargeNumbers);
    }

    virtual void TearDown() {
        delete listSmall;
        delete listLarge;
    }

public:
    lab6::DoublyLinkedList *listSmall, *listLarge;
    std::vector<int> listSmallNumbers, listLargeNumbers;
};

TEST_F(SortsTest, quickSort_doesNotCrash) {
    EXPECT_NO_FATAL_FAILURE(lab6::quickSort(*listSmall, 0, listSmall->size() - 1));
}

TEST_F(SortsTest, quickSort_populatedLists_sortsValues) {
    lab6::quickSort(*listSmall, 0, listSmall->size() - 1);
    for (int i = 0; i < 10; i++) EXPECT_EQ(i, listSmall->at(i));

    lab6::quickSort(*listLarge, 0, listLarge->size() - 1);
    for (int i = 0; i < 3000; i++) EXPECT_EQ(i, listLarge->at(i));
}

TEST_F(SortsTest, quickSort_emptyList_doesNothing) {
    auto *list = new lab6::DoublyLinkedList;
    lab6::quickSort(*list, 0, list->size() - 1);
}

TEST_F(SortsTest, mergeSort_doesNotCrash) {
    EXPECT_NO_FATAL_FAILURE(lab6::mergeSort(*listSmall));
}

TEST_F(SortsTest, mergeSort_populatedLists_sortsValues) {
    lab6::mergeSort(*listSmall);
    for (int i = 0; i < 10; i++) EXPECT_EQ(i, listSmall->at(i));

    lab6::mergeSort(*listLarge);
    for (int i = 0; i < 3000; i++) EXPECT_EQ(i, listLarge->at(i));
}

TEST_F(SortsTest, mergeSort_emptyList_doesNothing) {
    auto *list = new lab6::DoublyLinkedList;
    lab6::mergeSort(*list);
}