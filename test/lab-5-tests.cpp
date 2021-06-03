#include "gtest/gtest.h"
#include "LinkedList.h"
#include "LinkedListQueue.h"
#include "LinkedListStack.h"
#include "LinkedListCalculator.h"

class LinkedListTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        linkedListUT = new lab5::LinkedList;
    }

    virtual void TearDown() {
        delete linkedListUT;
    }

public:
    lab5::LinkedList *linkedListUT;
};

TEST(CrashTest, linkedList_crashTest) {
    auto *linkedListUT = new lab5::LinkedList;
    delete linkedListUT;
}

TEST_F(LinkedListTest, at_doesNotCrash) {
    linkedListUT->append("foo");
    linkedListUT->at(0);
}

TEST_F(LinkedListTest, at_getsDataFromNodeAtLocation) {
    linkedListUT->append("foo");
    EXPECT_EQ("foo", linkedListUT->at(0));

    linkedListUT->insert("bar", 1);
    EXPECT_EQ("foo", linkedListUT->at(0));
    EXPECT_EQ("bar", linkedListUT->at(1));

    linkedListUT->append("baz");
    EXPECT_EQ("foo", linkedListUT->at(0));
    EXPECT_EQ("bar", linkedListUT->at(1));
    EXPECT_EQ("baz", linkedListUT->at(2));

    linkedListUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->at(0));
    EXPECT_EQ("baz", linkedListUT->at(1));

    linkedListUT->append("qux");
    EXPECT_EQ("bar", linkedListUT->at(0));
    EXPECT_EQ("baz", linkedListUT->at(1));
    EXPECT_EQ("qux", linkedListUT->at(2));

    linkedListUT->remove(2);
    EXPECT_EQ("bar", linkedListUT->at(0));
    EXPECT_EQ("baz", linkedListUT->at(1));

    linkedListUT->insert("quux", 2);
    EXPECT_EQ("bar", linkedListUT->at(0));
    EXPECT_EQ("baz", linkedListUT->at(1));
    EXPECT_EQ("quux", linkedListUT->at(2));
}

TEST_F(LinkedListTest, at_invalidIndex_crashes) {
    EXPECT_ANY_THROW(linkedListUT->at(0));
    EXPECT_ANY_THROW(linkedListUT->at(10));
    EXPECT_ANY_THROW(linkedListUT->at(-1));

    linkedListUT->append("foo");
    linkedListUT->insert("bar", 1);
    linkedListUT->remove(0);

    EXPECT_NO_THROW(linkedListUT->at(0));
    EXPECT_ANY_THROW(linkedListUT->at(1));
}

TEST_F(LinkedListTest, append_doesNotCrash) {
    linkedListUT->append("foo");
}

TEST_F(LinkedListTest, append_addsDataToEnd) {
    linkedListUT->append("foo");
    EXPECT_EQ("foo", linkedListUT->at(0));

    linkedListUT->append("bar");
    EXPECT_EQ("foo", linkedListUT->at(0));
    EXPECT_EQ("bar", linkedListUT->at(1));

    linkedListUT->append("baz");
    EXPECT_EQ("foo", linkedListUT->at(0));
    EXPECT_EQ("bar", linkedListUT->at(1));
    EXPECT_EQ("baz", linkedListUT->at(2));
}

TEST_F(LinkedListTest, insert_doesNotCrash) {
    linkedListUT->insert("foo");
}

TEST_F(LinkedListTest, insert_addsDataAtIndex) {
    linkedListUT->insert("foo", 0);
    EXPECT_EQ("foo", linkedListUT->at(0));

    linkedListUT->insert("bar", 1);
    EXPECT_EQ("foo", linkedListUT->at(0));
    EXPECT_EQ("bar", linkedListUT->at(1));

    linkedListUT->insert("baz", 0);
    EXPECT_EQ("baz", linkedListUT->at(0));
    EXPECT_EQ("foo", linkedListUT->at(1));
    EXPECT_EQ("bar", linkedListUT->at(2));
}

TEST_F(LinkedListTest, insert_atInvalidIndex_crashes) {
    EXPECT_ANY_THROW(linkedListUT->insert("foo", 1));
    EXPECT_ANY_THROW(linkedListUT->insert("foo", -1));

    linkedListUT->insert("foo", 0);
    linkedListUT->insert("bar", 1);
    linkedListUT->insert("baz", 2);

    EXPECT_ANY_THROW(linkedListUT->insert("foo", 4));
}

TEST_F(LinkedListTest, remove_doesNotCrash) {
    linkedListUT->append("foo");
    linkedListUT->remove(0);
}

TEST_F(LinkedListTest, remove_removesDataAtIndex) {
    linkedListUT->append("foo");
    linkedListUT->append("bar");
    linkedListUT->append("baz");
    ASSERT_EQ("foo", linkedListUT->at(0));
    ASSERT_EQ("bar", linkedListUT->at(1));
    ASSERT_EQ("baz", linkedListUT->at(2));

    linkedListUT->remove(2);
    EXPECT_EQ("foo", linkedListUT->at(0));
    EXPECT_EQ("bar", linkedListUT->at(1));
    EXPECT_ANY_THROW(linkedListUT->at(2));

    linkedListUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->at(0));
    EXPECT_ANY_THROW(linkedListUT->at(1));
}

TEST_F(LinkedListTest, remove_atInvalidIndex_crashes) {
    EXPECT_ANY_THROW(linkedListUT->remove(0));
    EXPECT_ANY_THROW(linkedListUT->remove(10));
    EXPECT_ANY_THROW(linkedListUT->remove(-1));

    linkedListUT->append("foo");
    linkedListUT->append("bar");
    linkedListUT->append("baz");

    EXPECT_ANY_THROW(linkedListUT->remove(3));
}

TEST_F(LinkedListTest, empty_afterDefaultConstructor_true) {
    EXPECT_TRUE(linkedListUT->empty());
}

TEST_F(LinkedListTest, size_afterDefaultConstructor_0) {
    EXPECT_EQ(0, linkedListUT->size());
}

TEST_F(LinkedListTest, emptyAndSize_tracksAppendsAndInsertionsAndRemovals) {
    linkedListUT->append("foo");
    EXPECT_FALSE(linkedListUT->empty());
    EXPECT_EQ(1, linkedListUT->size());

    linkedListUT->insert("bar", 1);
    EXPECT_FALSE(linkedListUT->empty());
    EXPECT_EQ(2, linkedListUT->size());

    linkedListUT->append("baz");
    EXPECT_FALSE(linkedListUT->empty());
    EXPECT_EQ(3, linkedListUT->size());

    linkedListUT->remove(0);
    EXPECT_FALSE(linkedListUT->empty());
    EXPECT_EQ(2, linkedListUT->size());

    linkedListUT->append("qux");
    EXPECT_FALSE(linkedListUT->empty());
    EXPECT_EQ(3, linkedListUT->size());

    linkedListUT->remove(2);
    EXPECT_FALSE(linkedListUT->empty());
    EXPECT_EQ(2, linkedListUT->size());

    linkedListUT->insert("quux", 2);
    EXPECT_FALSE(linkedListUT->empty());
    EXPECT_EQ(3, linkedListUT->size());

    linkedListUT->remove(0);
    linkedListUT->remove(0);
    linkedListUT->remove(0);
    EXPECT_TRUE(linkedListUT->empty());
    EXPECT_EQ(0, linkedListUT->size());
}

TEST_F(LinkedListTest, insertionOperator_outputsContents) {
    std::stringstream("foo") >> *linkedListUT;
    std::stringstream("bar") >> *linkedListUT;
    std::stringstream("baz") >> *linkedListUT;

    EXPECT_EQ("foo", linkedListUT->at(0));
    EXPECT_EQ("bar", linkedListUT->at(1));
    EXPECT_EQ("baz", linkedListUT->at(2));
}

TEST_F(LinkedListTest, extractionOperator_inputsContents) {
    linkedListUT->append("foo");
    linkedListUT->append("bar");
    linkedListUT->append("baz");

    testing::internal::CaptureStdout();
    std::cout << *linkedListUT;

    EXPECT_EQ("foo -> bar -> baz -> NULL", testing::internal::GetCapturedStdout());
}

TEST_F(LinkedListTest, copyConstructor_hardCopiesNodes) {
    linkedListUT->append("foo");
    linkedListUT->append("bar");
    linkedListUT->append("baz");

    auto otherlinked_listUT = new lab5::LinkedList(*linkedListUT);
    EXPECT_EQ("foo", linkedListUT->at(0));
    EXPECT_EQ("foo", otherlinked_listUT->at(0));

    linkedListUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->at(0));
    EXPECT_EQ("foo", otherlinked_listUT->at(0));

    otherlinked_listUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->at(0));
    EXPECT_EQ("bar", otherlinked_listUT->at(0));

    linkedListUT->insert("qux", 0);
    EXPECT_EQ("qux", linkedListUT->at(0));
    EXPECT_EQ("bar", otherlinked_listUT->at(0));

    otherlinked_listUT->insert("qux", 0);
    EXPECT_EQ("qux", linkedListUT->at(0));
    EXPECT_EQ("qux", otherlinked_listUT->at(0));
}

TEST_F(LinkedListTest, copyConstructor_selfAssignment_doesNotChangeNodes) {
    linkedListUT->append("foo");
    linkedListUT->append("bar");
    linkedListUT->append("baz");

    linkedListUT = new lab5::LinkedList(*linkedListUT);
    EXPECT_EQ("foo", linkedListUT->at(0));

    linkedListUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->at(0));

    linkedListUT->insert("qux", 0);
    EXPECT_EQ("qux", linkedListUT->at(0));
}

TEST_F(LinkedListTest, equalsOperator_hardCopiesNodes) {
    linkedListUT->append("foo");
    linkedListUT->append("bar");
    linkedListUT->append("baz");

    auto otherlinked_listUT = new lab5::LinkedList;
    otherlinked_listUT->operator=(*linkedListUT);

    EXPECT_EQ("foo", linkedListUT->at(0));
    EXPECT_EQ("foo", otherlinked_listUT->at(0));

    linkedListUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->at(0));
    EXPECT_EQ("foo", otherlinked_listUT->at(0));

    otherlinked_listUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->at(0));
    EXPECT_EQ("bar", otherlinked_listUT->at(0));

    linkedListUT->insert("qux", 0);
    EXPECT_EQ("qux", linkedListUT->at(0));
    EXPECT_EQ("bar", otherlinked_listUT->at(0));

    otherlinked_listUT->insert("qux", 0);
    EXPECT_EQ("qux", linkedListUT->at(0));
    EXPECT_EQ("qux", otherlinked_listUT->at(0));
}

TEST_F(LinkedListTest, equalsOperator_selfAssignment_doesNotChangeNodes) {
    linkedListUT->append("foo");
    linkedListUT->append("bar");
    linkedListUT->append("baz");

    linkedListUT->operator=(*linkedListUT);
    EXPECT_EQ("foo", linkedListUT->at(0));

    linkedListUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->at(0));

    linkedListUT->insert("qux", 0);
    EXPECT_EQ("qux", linkedListUT->at(0));
}

TEST_F(LinkedListTest, sort_sortslinked_listData) {
    linkedListUT->append("charlie");
    linkedListUT->append("echo");
    linkedListUT->append("alfa");
    linkedListUT->append("juliett");
    linkedListUT->append("delta");
    linkedListUT->append("foxtrot");
    linkedListUT->append("golf");
    linkedListUT->append("hotel");
    linkedListUT->append("bravo");
    linkedListUT->append("india");

    linkedListUT->sort();

    EXPECT_EQ("alfa", linkedListUT->at(0));
    EXPECT_EQ("bravo", linkedListUT->at(1));
    EXPECT_EQ("charlie", linkedListUT->at(2));
    EXPECT_EQ("delta", linkedListUT->at(3));
    EXPECT_EQ("echo", linkedListUT->at(4));
    EXPECT_EQ("foxtrot", linkedListUT->at(5));
    EXPECT_EQ("golf", linkedListUT->at(6));
    EXPECT_EQ("hotel", linkedListUT->at(7));
    EXPECT_EQ("india", linkedListUT->at(8));
    EXPECT_EQ("juliett", linkedListUT->at(9));
}

class LinkedListStackTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        linkedListStackUT = new lab5::LinkedListStack;
    }

    virtual void TearDown() {
        delete linkedListStackUT;
    }

public:
    lab5::LinkedListStack *linkedListStackUT;
};

TEST(CrashTest, stack_crashTest) {
    auto stackUT = new lab5::LinkedListStack;
    delete stackUT;
}

TEST_F(LinkedListStackTest, push_doesNotCrash) {
    linkedListStackUT->push("foo");
}

TEST_F(LinkedListStackTest, push_addsToStack) {
    linkedListStackUT->push("foo");
    EXPECT_EQ("foo", linkedListStackUT->top());
    linkedListStackUT->push("bar");
    EXPECT_EQ("bar", linkedListStackUT->top());
}

TEST_F(LinkedListStackTest, pop_doesNotCrash) {
    linkedListStackUT->push("foo");
    linkedListStackUT->pop();
}

TEST_F(LinkedListStackTest, pop_removesFromStack) {
    linkedListStackUT->push("foo");
    linkedListStackUT->push("bar");
    linkedListStackUT->pop();
    EXPECT_EQ("foo", linkedListStackUT->top());
}

TEST_F(LinkedListStackTest, pop_stackIsEmpty_crashes) {
    EXPECT_ANY_THROW(linkedListStackUT->pop());

    linkedListStackUT->push("foo");
    linkedListStackUT->push("bar");
    linkedListStackUT->pop();
    linkedListStackUT->pop();
    EXPECT_ANY_THROW(linkedListStackUT->pop());
}

TEST_F(LinkedListStackTest, top_doesNotCrash) {
    linkedListStackUT->push("foo");
    linkedListStackUT->top();
}

TEST_F(LinkedListStackTest, top_getsTopOfStack) {
    linkedListStackUT->push("foo");
    EXPECT_EQ("foo", linkedListStackUT->top());

    linkedListStackUT->push("bar");
    EXPECT_EQ("bar", linkedListStackUT->top());

    linkedListStackUT->pop();
    EXPECT_EQ("foo", linkedListStackUT->top());

    linkedListStackUT->push("baz");
    EXPECT_EQ("baz", linkedListStackUT->top());
}

TEST_F(LinkedListStackTest, top_stackIsEmpty_crashes) {
    EXPECT_ANY_THROW(linkedListStackUT->top());

    linkedListStackUT->push("foo");
    linkedListStackUT->push("bar");
    linkedListStackUT->pop();
    linkedListStackUT->pop();
    EXPECT_ANY_THROW(linkedListStackUT->top());
}

TEST_F(LinkedListStackTest, empty_afterDefaultConstructor_true) {
    EXPECT_TRUE(linkedListStackUT->empty());
}

TEST_F(LinkedListStackTest, size_afterDefaultConstructor_0) {
    EXPECT_EQ(0, linkedListStackUT->size());
}

TEST_F(LinkedListStackTest, emptyAndSize_tracksPushesAndPops) {
    linkedListStackUT->push("foo");
    EXPECT_FALSE(linkedListStackUT->empty());
    EXPECT_EQ(1, linkedListStackUT->size());

    linkedListStackUT->push("bar");
    EXPECT_FALSE(linkedListStackUT->empty());
    EXPECT_EQ(2, linkedListStackUT->size());

    linkedListStackUT->pop();
    linkedListStackUT->pop();
    EXPECT_TRUE(linkedListStackUT->empty());
    EXPECT_EQ(0, linkedListStackUT->size());
}

TEST_F(LinkedListStackTest, insertionOperator_outputsContents) {
    std::stringstream("foo") >> *linkedListStackUT;
    EXPECT_EQ("foo", linkedListStackUT->top());

    std::stringstream("bar") >> *linkedListStackUT;
    EXPECT_EQ("bar", linkedListStackUT->top());

    std::stringstream("baz") >> *linkedListStackUT;
    EXPECT_EQ("baz", linkedListStackUT->top());
}

TEST_F(LinkedListStackTest, extractionOperator_inputsContents) {
    linkedListStackUT->push("foo");
    linkedListStackUT->push("bar");
    linkedListStackUT->push("baz");

    testing::internal::CaptureStdout();
    std::cout << *linkedListStackUT;

    EXPECT_EQ("foo -> bar -> baz -> NULL", testing::internal::GetCapturedStdout());
}

TEST_F(LinkedListStackTest, parameterizedConstructor_pushesInitialValue) {
    std::string input = "foo";
    linkedListStackUT = new lab5::LinkedListStack(input);
    EXPECT_EQ("foo", linkedListStackUT->top());
}

TEST_F(LinkedListStackTest, copyConstructor_hardCopiesValues) {
    linkedListStackUT->push("foo");
    linkedListStackUT->push("bar");

    auto otherStackUT = new lab5::LinkedListStack(*linkedListStackUT);

    EXPECT_EQ("bar", linkedListStackUT->top());
    EXPECT_EQ("bar", otherStackUT->top());

    linkedListStackUT->pop();
    EXPECT_EQ("foo", linkedListStackUT->top());
    EXPECT_EQ("bar", otherStackUT->top());

    otherStackUT->pop();
    EXPECT_EQ("foo", linkedListStackUT->top());
    EXPECT_EQ("foo", otherStackUT->top());
}

TEST_F(LinkedListStackTest, equalsOperator_hardCopiesValues) {
    auto otherStackUT = new lab5::LinkedListStack;

    linkedListStackUT->push("foo");
    linkedListStackUT->push("bar");

    otherStackUT->operator=(*linkedListStackUT);

    EXPECT_EQ("bar", linkedListStackUT->top());
    EXPECT_EQ("bar", otherStackUT->top());

    linkedListStackUT->pop();
    EXPECT_EQ("foo", linkedListStackUT->top());
    EXPECT_EQ("bar", otherStackUT->top());

    otherStackUT->pop();
    EXPECT_EQ("foo", linkedListStackUT->top());
    EXPECT_EQ("foo", otherStackUT->top());
}

class LinkedListQueueTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        linkedListQueueUT = new lab5::LinkedListQueue;
    }

    virtual void TearDown() {
        delete linkedListQueueUT;
    }

public:
    lab5::LinkedListQueue *linkedListQueueUT;
};

TEST(CrashTest, queue_crashTest) {
    auto queueUT = new lab5::LinkedListQueue;
    delete queueUT;
}

TEST_F(LinkedListQueueTest, enqueue_doesNotCrash) {
    linkedListQueueUT->enqueue("foo");
}

TEST_F(LinkedListQueueTest, enqueue_addsToQueue) {
    linkedListQueueUT->enqueue("foo");
    EXPECT_EQ("foo", linkedListQueueUT->top());
    linkedListQueueUT->enqueue("bar");
    EXPECT_EQ("foo", linkedListQueueUT->top());
}

TEST_F(LinkedListQueueTest, dequeue_doesNotCrash) {
    linkedListQueueUT->enqueue("foo");
    linkedListQueueUT->dequeue();
}

TEST_F(LinkedListQueueTest, dequeue_removesFromQueue) {
    linkedListQueueUT->enqueue("foo");
    linkedListQueueUT->enqueue("bar");
    linkedListQueueUT->dequeue();
    EXPECT_EQ("bar", linkedListQueueUT->top());
}

TEST_F(LinkedListQueueTest, dequeue_queueIsEmpty_crashes) {
    EXPECT_ANY_THROW(linkedListQueueUT->dequeue());

    linkedListQueueUT->enqueue("foo");
    linkedListQueueUT->enqueue("bar");
    linkedListQueueUT->dequeue();
    linkedListQueueUT->dequeue();
    EXPECT_ANY_THROW(linkedListQueueUT->dequeue());
}

TEST_F(LinkedListQueueTest, top_doesNotCrash) {
    linkedListQueueUT->enqueue("foo");
    linkedListQueueUT->top();
}

TEST_F(LinkedListQueueTest, top_getsFrontOfQueue) {
    linkedListQueueUT->enqueue("foo");
    EXPECT_EQ("foo", linkedListQueueUT->top());

    linkedListQueueUT->enqueue("bar");
    EXPECT_EQ("foo", linkedListQueueUT->top());

    linkedListQueueUT->dequeue();
    EXPECT_EQ("bar", linkedListQueueUT->top());

    linkedListQueueUT->enqueue("baz");
    EXPECT_EQ("bar", linkedListQueueUT->top());
}

TEST_F(LinkedListQueueTest, top_queueIsEmpty_crashes) {
    EXPECT_ANY_THROW(linkedListQueueUT->top());

    linkedListQueueUT->enqueue("foo");
    linkedListQueueUT->enqueue("bar");
    linkedListQueueUT->dequeue();
    linkedListQueueUT->dequeue();
    EXPECT_ANY_THROW(linkedListQueueUT->top());
}

TEST_F(LinkedListQueueTest, empty_afterDefaultConstructor_true) {
    EXPECT_TRUE(linkedListQueueUT->empty());
}

TEST_F(LinkedListQueueTest, size_afterDefaultConstructor_0) {
    EXPECT_EQ(0, linkedListQueueUT->size());
}

TEST_F(LinkedListQueueTest, emptyAndSize_tracksEnqueuesAndDequeues) {
    linkedListQueueUT->enqueue("foo");
    EXPECT_FALSE(linkedListQueueUT->empty());
    EXPECT_EQ(1, linkedListQueueUT->size());

    linkedListQueueUT->enqueue("bar");
    EXPECT_FALSE(linkedListQueueUT->empty());
    EXPECT_EQ(2, linkedListQueueUT->size());

    linkedListQueueUT->dequeue();
    linkedListQueueUT->dequeue();
    EXPECT_TRUE(linkedListQueueUT->empty());
    EXPECT_EQ(0, linkedListQueueUT->size());
}

TEST_F(LinkedListQueueTest, insertionOperator_outputsContents) {
    std::stringstream("foo") >> *linkedListQueueUT;
    std::stringstream("bar") >> *linkedListQueueUT;
    std::stringstream("baz") >> *linkedListQueueUT;

    EXPECT_EQ("foo", linkedListQueueUT->top());
    linkedListQueueUT->dequeue();
    EXPECT_EQ("bar", linkedListQueueUT->top());
    linkedListQueueUT->dequeue();
    EXPECT_EQ("baz", linkedListQueueUT->top());
}

TEST_F(LinkedListQueueTest, extractionOperator_inputsContents) {
    linkedListQueueUT->enqueue("foo");
    linkedListQueueUT->enqueue("bar");
    linkedListQueueUT->enqueue("baz");

    testing::internal::CaptureStdout();
    std::cout << *linkedListQueueUT;

    EXPECT_EQ("foo -> bar -> baz -> NULL", testing::internal::GetCapturedStdout());
}

TEST_F(LinkedListQueueTest, parameterizedConstructor_enqueuesInitialValue) {
    delete linkedListQueueUT;
    std::string input = "foo";
    linkedListQueueUT = new lab5::LinkedListQueue(input);
    EXPECT_EQ("foo", linkedListQueueUT->top());
}

TEST_F(LinkedListQueueTest, copyConstructor_hardCopiesValues) {
    linkedListQueueUT->enqueue("foo");
    linkedListQueueUT->enqueue("bar");

    auto otherQueueUT = new lab5::LinkedListQueue(*linkedListQueueUT);

    EXPECT_EQ("foo", linkedListQueueUT->top());
    EXPECT_EQ("foo", otherQueueUT->top());

    linkedListQueueUT->dequeue();
    EXPECT_EQ("bar", linkedListQueueUT->top());
    EXPECT_EQ("foo", otherQueueUT->top());

    otherQueueUT->dequeue();
    EXPECT_EQ("bar", linkedListQueueUT->top());
    EXPECT_EQ("bar", otherQueueUT->top());
}

TEST_F(LinkedListQueueTest, equalsOperator_hardCopiesValues) {
    linkedListQueueUT->enqueue("foo");
    linkedListQueueUT->enqueue("bar");

    auto otherQueueUT = new lab5::LinkedListQueue;
    otherQueueUT->operator=(*linkedListQueueUT);

    EXPECT_EQ("foo", linkedListQueueUT->top());
    EXPECT_EQ("foo", otherQueueUT->top());

    linkedListQueueUT->dequeue();
    EXPECT_EQ("bar", linkedListQueueUT->top());
    EXPECT_EQ("foo", otherQueueUT->top());

    otherQueueUT->dequeue();
    EXPECT_EQ("bar", linkedListQueueUT->top());
    EXPECT_EQ("bar", otherQueueUT->top());
}

class LinkedListCalculatorTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        linkedListCalculatorUT = new lab5::LinkedListCalculator;
    }

    virtual void TearDown() {
        delete linkedListCalculatorUT;
    }

public:
    lab5::LinkedListCalculator *linkedListCalculatorUT;
    std::string input;
};

TEST(CrashTest, fancyCalculator_crashTest) {
    auto fancyCalculatorUT = new lab5::LinkedListCalculator;
    delete fancyCalculatorUT;
}

TEST_F(LinkedListCalculatorTest, calculate_expressionsWithSingleOperations_calculatesCorrectAnswer) {
    delete linkedListCalculatorUT;
    input = "1 + 2";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(3, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "3 - 2";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(1, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "2 * 3";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(6, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "6 / 3";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(2, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "10 % 3";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(1, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "2 ^ 3";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(8, linkedListCalculatorUT->calculate());
}

TEST_F(LinkedListCalculatorTest, calculate_expressionsWithMultipleOperations_calculatesCorrectAnswer) {
    delete linkedListCalculatorUT;
    input = "1 + 2 + 3";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(6, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "1 + 2 + 3 - 4";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(2, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "10 * 2 - 3 + 10 / 5";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(19, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "6 * 10 + 13 - 6 ^ 2 + 8 ^ 2 / 2 % 5";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(39, linkedListCalculatorUT->calculate());
}

TEST_F(LinkedListCalculatorTest, calculate_expressionsWithParetheses_calculatesCorrectAnswer) {
    delete linkedListCalculatorUT;
    input = "( 1 + 2 )";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(3, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "( 1 + 2 + 3 )";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(6, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "( 1 + 2 ) + 3";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(6, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "1 + ( 2 + 3 )";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(6, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "8 + 7 * ( 7 - 2 )";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(43, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "10 * ( 8 + 5 ) + 7 - 14 + 9";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(132, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "15 - 10 * 6 + ( 14 - 7 % 2) * 7 ^ 2 + 11";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(603, linkedListCalculatorUT->calculate());

    delete linkedListCalculatorUT;
    input = "49 * ( 17 * ( 3 + 2 * ( 12 + 2 * ( 45 - 43 ) + 2 ) ) + 1 * ( 6 / 2 ) )";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(32634, linkedListCalculatorUT->calculate());
}

TEST_F(LinkedListCalculatorTest, insertionAndExtractionOperator_outputsAndInputsInfixAndPostfixExpressions) {
    std::stringstream *stream;

    delete (linkedListCalculatorUT);
    input = "1 + 2 + 3";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);

    testing::internal::CaptureStdout();
    std::cout << *linkedListCalculatorUT;
    EXPECT_EQ("Infix: 1,+,2,+,3\nPostfix: 1,2,+,3,+", testing::internal::GetCapturedStdout());

    delete (linkedListCalculatorUT);
    linkedListCalculatorUT = new lab5::LinkedListCalculator();
    std::stringstream("1 + 2 + 3 - 4") >> *linkedListCalculatorUT;

    testing::internal::CaptureStdout();
    std::cout << *linkedListCalculatorUT;
    EXPECT_EQ("Infix: 1,+,2,+,3,-,4\nPostfix: 1,2,+,3,+,4,-", testing::internal::GetCapturedStdout());

    delete (linkedListCalculatorUT);
    input = "49 * ( 17 * ( 3 + 2 * ( 12 + 2 * ( 45 - 43 ) + 2 ) ) + 1 * ( 6 / 2 ) )";
    linkedListCalculatorUT = new lab5::LinkedListCalculator(input);

    testing::internal::CaptureStdout();
    std::cout << *linkedListCalculatorUT;
    EXPECT_EQ("Infix: 49,*,(,17,*,(,3,+,2,*,(,12,+,2,*,(,45,-,43,),+,2,),),+,1,*,(,6,/,2,),)\nPostfix: 49,17,3,2,12,2,45,43,-,*,+,2,+,*,+,*,1,6,2,/,*,+,*", testing::internal::GetCapturedStdout());
}