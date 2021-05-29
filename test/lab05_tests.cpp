#include "gtest/gtest.h"
#include "LinkedList.h"
#include "LinkedListQueue.h"
#include "LinkedListStack.h"
#include "LinkedListCalculator.h"

// Linked List Tests
class linked_listTest : public ::testing::Test {

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

TEST_F(linked_listTest, getValueAt_doesNotCrash) {
    linkedListUT->append("foo");
    linkedListUT->at(0);
}

TEST_F(linked_listTest, getValueAt_getsDataFromNodeAtLocation) {
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

TEST_F(linked_listTest, getValueAt_invalidIndex_crashes) {
    EXPECT_ANY_THROW(linkedListUT->at(0));
    EXPECT_ANY_THROW(linkedListUT->at(10));
    EXPECT_ANY_THROW(linkedListUT->at(-1));

    linkedListUT->append("foo");
    linkedListUT->insert("bar", 1);
    linkedListUT->remove(0);

    EXPECT_NO_THROW(linkedListUT->at(0));
    EXPECT_ANY_THROW(linkedListUT->at(1));
}

TEST_F(linked_listTest, append_doesNotCrash) {
    linkedListUT->append("foo");
}

TEST_F(linked_listTest, append_addsDataToEnd) {
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

TEST_F(linked_listTest, insert_doesNotCrash) {
    linkedListUT->insert("foo");
}

TEST_F(linked_listTest, insert_addsDataAtIndex) {
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

TEST_F(linked_listTest, insert_atInvalidIndex_crashes) {
    EXPECT_ANY_THROW(linkedListUT->insert("foo", 1));
    EXPECT_ANY_THROW(linkedListUT->insert("foo", -1));

    linkedListUT->insert("foo", 0);
    linkedListUT->insert("bar", 1);
    linkedListUT->insert("baz", 2);

    EXPECT_ANY_THROW(linkedListUT->insert("foo", 4));
}

TEST_F(linked_listTest, remove_doesNotCrash) {
    linkedListUT->append("foo");
    linkedListUT->remove(0);
}

TEST_F(linked_listTest, remove_removesDataAtIndex) {
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

TEST_F(linked_listTest, remove_atInvalidIndex_crashes) {
    EXPECT_ANY_THROW(linkedListUT->remove(0));
    EXPECT_ANY_THROW(linkedListUT->remove(10));
    EXPECT_ANY_THROW(linkedListUT->remove(-1));

    linkedListUT->append("foo");
    linkedListUT->append("bar");
    linkedListUT->append("baz");

    EXPECT_ANY_THROW(linkedListUT->remove(3));
}

TEST_F(linked_listTest, isEmpty_afterDefaultConstructor_true) {
    EXPECT_TRUE(linkedListUT->empty());
}

TEST_F(linked_listTest, size_afterDefaultConstructor_0) {
    EXPECT_EQ(0, linkedListUT->size());
}

TEST_F(linked_listTest, isEmptyAndSize_tracksAppendsAndInsertionsAndRemovals) {
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

TEST_F(linked_listTest, insertionOperator_outputsContents) {
    std::stringstream("foo") >> *linkedListUT;
    std::stringstream("bar") >> *linkedListUT;
    std::stringstream("baz") >> *linkedListUT;

    EXPECT_EQ("foo", linkedListUT->at(0));
    EXPECT_EQ("bar", linkedListUT->at(1));
    EXPECT_EQ("baz", linkedListUT->at(2));
}

TEST_F(linked_listTest, extractionOperator_inputsContents) {
    linkedListUT->append("foo");
    linkedListUT->append("bar");
    linkedListUT->append("baz");

    testing::internal::CaptureStdout();
    std::cout << *linkedListUT;

    EXPECT_EQ("foo -> bar -> baz -> NULL", testing::internal::GetCapturedStdout());
}

TEST_F(linked_listTest, copyConstructor_hardCopiesNodes) {
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

TEST_F(linked_listTest, copyConstructor_selfAssignment_doesNotChangeNodes) {
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

TEST_F(linked_listTest, equalsOperator_hardCopiesNodes) {
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

TEST_F(linked_listTest, equalsOperator_selfAssignment_doesNotChangeNodes) {
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

TEST_F(linked_listTest, sort_sortslinked_listData) {
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

// StringVectorStack Tests
class StackTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        stackUT = new lab5::LinkedListStack;
    }

    virtual void TearDown() {
        delete stackUT;
    }

public:
    lab5::LinkedListStack *stackUT;
};

TEST(CrashTest, stack_crashTest) {
    auto stackUT = new lab5::LinkedListStack;
    delete stackUT;
}

TEST_F(StackTest, push_doesNotCrash) {
    stackUT->push("foo");
}

TEST_F(StackTest, push_addsToStack) {
    stackUT->push("foo");
    EXPECT_EQ("foo", stackUT->top());
    stackUT->push("bar");
    EXPECT_EQ("bar", stackUT->top());
}

TEST_F(StackTest, pop_doesNotCrash) {
    stackUT->push("foo");
    stackUT->pop();
}

TEST_F(StackTest, pop_removesFromStack) {
    stackUT->push("foo");
    stackUT->push("bar");
    stackUT->pop();
    EXPECT_EQ("foo", stackUT->top());
}

TEST_F(StackTest, pop_stackIsEmpty_crashes) {
    EXPECT_ANY_THROW(stackUT->pop());

    stackUT->push("foo");
    stackUT->push("bar");
    stackUT->pop();
    stackUT->pop();
    EXPECT_ANY_THROW(stackUT->pop());
}

TEST_F(StackTest, top_doesNotCrash) {
    stackUT->push("foo");
    stackUT->top();
}

TEST_F(StackTest, top_getsTopOfStack) {
    stackUT->push("foo");
    EXPECT_EQ("foo", stackUT->top());

    stackUT->push("bar");
    EXPECT_EQ("bar", stackUT->top());

    stackUT->pop();
    EXPECT_EQ("foo", stackUT->top());

    stackUT->push("baz");
    EXPECT_EQ("baz", stackUT->top());
}

TEST_F(StackTest, top_stackIsEmpty_crashes) {
    EXPECT_ANY_THROW(stackUT->top());

    stackUT->push("foo");
    stackUT->push("bar");
    stackUT->pop();
    stackUT->pop();
    EXPECT_ANY_THROW(stackUT->top());
}

TEST_F(StackTest, isEmpty_afterDefaultConstructor_true) {
    EXPECT_TRUE(stackUT->empty());
}

TEST_F(StackTest, size_afterDefaultConstructor_0) {
    EXPECT_EQ(0, stackUT->size());
}

TEST_F(StackTest, isEmptyAndSize_tracksPushesAndPops) {
    stackUT->push("foo");
    EXPECT_FALSE(stackUT->empty());
    EXPECT_EQ(1, stackUT->size());

    stackUT->push("bar");
    EXPECT_FALSE(stackUT->empty());
    EXPECT_EQ(2, stackUT->size());

    stackUT->pop();
    stackUT->pop();
    EXPECT_TRUE(stackUT->empty());
    EXPECT_EQ(0, stackUT->size());
}

TEST_F(StackTest, insertionOperator_outputsContents) {
    std::stringstream("foo") >> *stackUT;
    EXPECT_EQ("foo", stackUT->top());

    std::stringstream("bar") >> *stackUT;
    EXPECT_EQ("bar", stackUT->top());

    std::stringstream("baz") >> *stackUT;
    EXPECT_EQ("baz", stackUT->top());
}

TEST_F(StackTest, extractionOperator_inputsContents) {
    stackUT->push("foo");
    stackUT->push("bar");
    stackUT->push("baz");

    testing::internal::CaptureStdout();
    std::cout << *stackUT;

    EXPECT_EQ("foo -> bar -> baz -> NULL", testing::internal::GetCapturedStdout());
}

TEST_F(StackTest, parameterizedConstructor_pushesInitialValue) {
    std::string input = "foo";
    stackUT = new lab5::LinkedListStack(input);
    EXPECT_EQ("foo", stackUT->top());
}

TEST_F(StackTest, copyConstructor_hardCopiesValues) {
    stackUT->push("foo");
    stackUT->push("bar");

    auto otherStackUT = new lab5::LinkedListStack(*stackUT);

    EXPECT_EQ("bar", stackUT->top());
    EXPECT_EQ("bar", otherStackUT->top());

    stackUT->pop();
    EXPECT_EQ("foo", stackUT->top());
    EXPECT_EQ("bar", otherStackUT->top());

    otherStackUT->pop();
    EXPECT_EQ("foo", stackUT->top());
    EXPECT_EQ("foo", otherStackUT->top());
}

TEST_F(StackTest, equalsOperator_hardCopiesValues) {
    auto otherStackUT = new lab5::LinkedListStack;

    stackUT->push("foo");
    stackUT->push("bar");

    otherStackUT->operator=(*stackUT);

    EXPECT_EQ("bar", stackUT->top());
    EXPECT_EQ("bar", otherStackUT->top());

    stackUT->pop();
    EXPECT_EQ("foo", stackUT->top());
    EXPECT_EQ("bar", otherStackUT->top());

    otherStackUT->pop();
    EXPECT_EQ("foo", stackUT->top());
    EXPECT_EQ("foo", otherStackUT->top());
}

// LinkedListQueue Tests
class QueueTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        queueUT = new lab5::LinkedListQueue;
    }

    virtual void TearDown() {
        delete queueUT;
    }

public:
    lab5::LinkedListQueue *queueUT;
};

TEST(CrashTest, queue_crashTest) {
    auto queueUT = new lab5::LinkedListQueue;
    delete queueUT;
}

TEST_F(QueueTest, enqueue_doesNotCrash) {
    queueUT->enqueue("foo");
}

TEST_F(QueueTest, enqueue_addsToQueue) {
    queueUT->enqueue("foo");
    EXPECT_EQ("foo", queueUT->top());
    queueUT->enqueue("bar");
    EXPECT_EQ("foo", queueUT->top());
}

TEST_F(QueueTest, dequeue_doesNotCrash) {
    queueUT->enqueue("foo");
    queueUT->dequeue();
}

TEST_F(QueueTest, dequeue_removesFromQueue) {
    queueUT->enqueue("foo");
    queueUT->enqueue("bar");
    queueUT->dequeue();
    EXPECT_EQ("bar", queueUT->top());
}

TEST_F(QueueTest, dequeue_queueIsEmpty_crashes) {
    EXPECT_ANY_THROW(queueUT->dequeue());

    queueUT->enqueue("foo");
    queueUT->enqueue("bar");
    queueUT->dequeue();
    queueUT->dequeue();
    EXPECT_ANY_THROW(queueUT->dequeue());
}

TEST_F(QueueTest, top_doesNotCrash) {
    queueUT->enqueue("foo");
    queueUT->top();
}

TEST_F(QueueTest, top_getsFrontOfQueue) {
    queueUT->enqueue("foo");
    EXPECT_EQ("foo", queueUT->top());

    queueUT->enqueue("bar");
    EXPECT_EQ("foo", queueUT->top());

    queueUT->dequeue();
    EXPECT_EQ("bar", queueUT->top());

    queueUT->enqueue("baz");
    EXPECT_EQ("bar", queueUT->top());
}

TEST_F(QueueTest, top_queueIsEmpty_crashes) {
    EXPECT_ANY_THROW(queueUT->top());

    queueUT->enqueue("foo");
    queueUT->enqueue("bar");
    queueUT->dequeue();
    queueUT->dequeue();
    EXPECT_ANY_THROW(queueUT->top());
}

TEST_F(QueueTest, isEmpty_afterDefaultConstructor_true) {
    EXPECT_TRUE(queueUT->empty());
}

TEST_F(QueueTest, size_afterDefaultConstructor_0) {
    EXPECT_EQ(0, queueUT->size());
}

TEST_F(QueueTest, isEmptyAndSize_tracksEnqueuesAndDequeues) {
    queueUT->enqueue("foo");
    EXPECT_FALSE(queueUT->empty());
    EXPECT_EQ(1, queueUT->size());

    queueUT->enqueue("bar");
    EXPECT_FALSE(queueUT->empty());
    EXPECT_EQ(2, queueUT->size());

    queueUT->dequeue();
    queueUT->dequeue();
    EXPECT_TRUE(queueUT->empty());
    EXPECT_EQ(0, queueUT->size());
}

TEST_F(QueueTest, insertionOperator_outputsContents) {
    std::stringstream("foo") >> *queueUT;
    std::stringstream("bar") >> *queueUT;
    std::stringstream("baz") >> *queueUT;

    EXPECT_EQ("foo", queueUT->top());
    queueUT->dequeue();
    EXPECT_EQ("bar", queueUT->top());
    queueUT->dequeue();
    EXPECT_EQ("baz", queueUT->top());
}

TEST_F(QueueTest, extractionOperator_inputsContents) {
    queueUT->enqueue("foo");
    queueUT->enqueue("bar");
    queueUT->enqueue("baz");

    testing::internal::CaptureStdout();
    std::cout << *queueUT;

    EXPECT_EQ("foo -> bar -> baz -> NULL", testing::internal::GetCapturedStdout());
}

TEST_F(QueueTest, parameterizedConstructor_enqueuesInitialValue) {
    delete queueUT;
    std::string input = "foo";
    queueUT = new lab5::LinkedListQueue(input);
    EXPECT_EQ("foo", queueUT->top());
}

TEST_F(QueueTest, copyConstructor_hardCopiesValues) {
    queueUT->enqueue("foo");
    queueUT->enqueue("bar");

    auto otherQueueUT = new lab5::LinkedListQueue(*queueUT);

    EXPECT_EQ("foo", queueUT->top());
    EXPECT_EQ("foo", otherQueueUT->top());

    queueUT->dequeue();
    EXPECT_EQ("bar", queueUT->top());
    EXPECT_EQ("foo", otherQueueUT->top());

    otherQueueUT->dequeue();
    EXPECT_EQ("bar", queueUT->top());
    EXPECT_EQ("bar", otherQueueUT->top());
}

TEST_F(QueueTest, equalsOperator_hardCopiesValues) {
    queueUT->enqueue("foo");
    queueUT->enqueue("bar");

    auto otherQueueUT = new lab5::LinkedListQueue;
    otherQueueUT->operator=(*queueUT);

    EXPECT_EQ("foo", queueUT->top());
    EXPECT_EQ("foo", otherQueueUT->top());

    queueUT->dequeue();
    EXPECT_EQ("bar", queueUT->top());
    EXPECT_EQ("foo", otherQueueUT->top());

    otherQueueUT->dequeue();
    EXPECT_EQ("bar", queueUT->top());
    EXPECT_EQ("bar", otherQueueUT->top());
}

// Linked List StringVectorCalculator Tests
class FancyCalculatorTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        calculatorUT = new lab5::LinkedListCalculator;
    }

    virtual void TearDown() {
        delete calculatorUT;
    }

public:
    lab5::LinkedListCalculator *calculatorUT;
    std::string input;
};

TEST(CrashTest, fancyCalculator_crashTest) {
    auto fancyCalculatorUT = new lab5::LinkedListCalculator;
    delete fancyCalculatorUT;
}

TEST_F(FancyCalculatorTest, calculate_expressionsWithSingleOperations_calculatesCorrectAnswer) {
    delete calculatorUT;
    input = "1 + 2";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(3, calculatorUT->calculate());

    delete calculatorUT;
    input = "3 - 2";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(1, calculatorUT->calculate());

    delete calculatorUT;
    input = "2 * 3";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "6 / 3";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(2, calculatorUT->calculate());

    delete calculatorUT;
    input = "10 % 3";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(1, calculatorUT->calculate());

    delete calculatorUT;
    input = "2 ^ 3";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(8, calculatorUT->calculate());
}

TEST_F(FancyCalculatorTest, calculate_expressionsWithMultipleOperations_calculatesCorrectAnswer) {
    delete calculatorUT;
    input = "1 + 2 + 3";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "1 + 2 + 3 - 4";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(2, calculatorUT->calculate());

    delete calculatorUT;
    input = "10 * 2 - 3 + 10 / 5";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(19, calculatorUT->calculate());

    delete calculatorUT;
    input = "6 * 10 + 13 - 6 ^ 2 + 8 ^ 2 / 2 % 5";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(39, calculatorUT->calculate());
}

TEST_F(FancyCalculatorTest, calculate_expressionsWithParetheses_calculatesCorrectAnswer) {
    delete calculatorUT;
    input = "( 1 + 2 )";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(3, calculatorUT->calculate());

    delete calculatorUT;
    input = "( 1 + 2 + 3 )";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "( 1 + 2 ) + 3";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "1 + ( 2 + 3 )";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "8 + 7 * ( 7 - 2 )";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(43, calculatorUT->calculate());

    delete calculatorUT;
    input = "10 * ( 8 + 5 ) + 7 - 14 + 9";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(132, calculatorUT->calculate());

    delete calculatorUT;
    input = "15 - 10 * 6 + ( 14 - 7 % 2) * 7 ^ 2 + 11";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(603, calculatorUT->calculate());

    delete calculatorUT;
    input = "49 * ( 17 * ( 3 + 2 * ( 12 + 2 * ( 45 - 43 ) + 2 ) ) + 1 * ( 6 / 2 ) )";
    calculatorUT = new lab5::LinkedListCalculator(input);
    EXPECT_EQ(32634, calculatorUT->calculate());
}

TEST_F(FancyCalculatorTest, insertionAndExtractionOperator_outputsAndInputsInfixAndPostfixExpressions) {
    std::stringstream *stream;

    delete (calculatorUT);
    input = "1 + 2 + 3";
    calculatorUT = new lab5::LinkedListCalculator(input);

    testing::internal::CaptureStdout();
    std::cout << *calculatorUT;
    EXPECT_EQ("Infix: 1,+,2,+,3\nPostfix: 1,2,+,3,+", testing::internal::GetCapturedStdout());

    delete (calculatorUT);
    calculatorUT = new lab5::LinkedListCalculator();
    std::stringstream("1 + 2 + 3 - 4") >> *calculatorUT;

    testing::internal::CaptureStdout();
    std::cout << *calculatorUT;
    EXPECT_EQ("Infix: 1,+,2,+,3,-,4\nPostfix: 1,2,+,3,+,4,-", testing::internal::GetCapturedStdout());

    delete (calculatorUT);
    input = "49 * ( 17 * ( 3 + 2 * ( 12 + 2 * ( 45 - 43 ) + 2 ) ) + 1 * ( 6 / 2 ) )";
    calculatorUT = new lab5::LinkedListCalculator(input);

    testing::internal::CaptureStdout();
    std::cout << *calculatorUT;
    EXPECT_EQ("Infix: 49,*,(,17,*,(,3,+,2,*,(,12,+,2,*,(,45,-,43,),+,2,),),+,1,*,(,6,/,2,),)\nPostfix: 49,17,3,2,12,2,45,43,-,*,+,2,+,*,+,*,1,6,2,/,*,+,*", testing::internal::GetCapturedStdout());
}