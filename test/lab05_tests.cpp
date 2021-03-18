#include "gtest/gtest.h"
#include "linked_list.h"
#include "queue.h"
#include "stack.h"
#include "fancy_calculator.h"

// Linked List Tests
class LinkedListTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        linkedListUT = new lab5::linked_list;
    }

    virtual void TearDown() {
        delete linkedListUT;
    }

public:
    lab5::linked_list *linkedListUT;
};

TEST(CrashTest, linkedList_crashTest) {
    auto *linkedListUT = new lab5::linked_list;
    delete linkedListUT;
}

TEST_F(LinkedListTest, getValueAt_doesNotCrash) {
    linkedListUT->append("foo");
    linkedListUT->getValueAt(0);
}

TEST_F(LinkedListTest, getValueAt_getsDataFromNodeAtLocation) {
    linkedListUT->append("foo");
    EXPECT_EQ("foo", linkedListUT->getValueAt(0));

    linkedListUT->insert("bar", 1);
    EXPECT_EQ("foo", linkedListUT->getValueAt(0));
    EXPECT_EQ("bar", linkedListUT->getValueAt(1));

    linkedListUT->append("baz");
    EXPECT_EQ("foo", linkedListUT->getValueAt(0));
    EXPECT_EQ("bar", linkedListUT->getValueAt(1));
    EXPECT_EQ("baz", linkedListUT->getValueAt(2));

    linkedListUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->getValueAt(0));
    EXPECT_EQ("baz", linkedListUT->getValueAt(1));

    linkedListUT->append("qux");
    EXPECT_EQ("bar", linkedListUT->getValueAt(0));
    EXPECT_EQ("baz", linkedListUT->getValueAt(1));
    EXPECT_EQ("qux", linkedListUT->getValueAt(2));

    linkedListUT->remove(2);
    EXPECT_EQ("bar", linkedListUT->getValueAt(0));
    EXPECT_EQ("baz", linkedListUT->getValueAt(1));

    linkedListUT->insert("quux", 2);
    EXPECT_EQ("bar", linkedListUT->getValueAt(0));
    EXPECT_EQ("baz", linkedListUT->getValueAt(1));
    EXPECT_EQ("quux", linkedListUT->getValueAt(2));
}

TEST_F(LinkedListTest, getValueAt_invalidIndex_crashes) {
    EXPECT_ANY_THROW(linkedListUT->getValueAt(0));
    EXPECT_ANY_THROW(linkedListUT->getValueAt(10));
    EXPECT_ANY_THROW(linkedListUT->getValueAt(-1));

    linkedListUT->append("foo");
    linkedListUT->insert("bar", 1);
    linkedListUT->remove(0);

    EXPECT_NO_THROW(linkedListUT->getValueAt(0));
    EXPECT_ANY_THROW(linkedListUT->getValueAt(1));
}

TEST_F(LinkedListTest, append_doesNotCrash) {
    linkedListUT->append("foo");
}

TEST_F(LinkedListTest, append_addsDataToEnd) {
    linkedListUT->append("foo");
    EXPECT_EQ("foo", linkedListUT->getValueAt(0));

    linkedListUT->append("bar");
    EXPECT_EQ("foo", linkedListUT->getValueAt(0));
    EXPECT_EQ("bar", linkedListUT->getValueAt(1));

    linkedListUT->append("baz");
    EXPECT_EQ("foo", linkedListUT->getValueAt(0));
    EXPECT_EQ("bar", linkedListUT->getValueAt(1));
    EXPECT_EQ("baz", linkedListUT->getValueAt(2));
}

TEST_F(LinkedListTest, insert_doesNotCrash) {
    linkedListUT->insert("foo");
}

TEST_F(LinkedListTest, insert_addsDataAtIndex) {
    linkedListUT->insert("foo", 0);
    EXPECT_EQ("foo", linkedListUT->getValueAt(0));

    linkedListUT->insert("bar", 1);
    EXPECT_EQ("foo", linkedListUT->getValueAt(0));
    EXPECT_EQ("bar", linkedListUT->getValueAt(1));

    linkedListUT->insert("baz", 0);
    EXPECT_EQ("baz", linkedListUT->getValueAt(0));
    EXPECT_EQ("foo", linkedListUT->getValueAt(1));
    EXPECT_EQ("bar", linkedListUT->getValueAt(2));
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
    ASSERT_EQ("foo", linkedListUT->getValueAt(0));
    ASSERT_EQ("bar", linkedListUT->getValueAt(1));
    ASSERT_EQ("baz", linkedListUT->getValueAt(2));

    linkedListUT->remove(2);
    EXPECT_EQ("foo", linkedListUT->getValueAt(0));
    EXPECT_EQ("bar", linkedListUT->getValueAt(1));
    EXPECT_ANY_THROW(linkedListUT->getValueAt(2));

    linkedListUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->getValueAt(0));
    EXPECT_ANY_THROW(linkedListUT->getValueAt(1));
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

TEST_F(LinkedListTest, isEmpty_afterDefaultConstructor_true) {
    EXPECT_TRUE(linkedListUT->isEmpty());
}

TEST_F(LinkedListTest, size_afterDefaultConstructor_0) {
    EXPECT_EQ(0, linkedListUT->listSize());
}

TEST_F(LinkedListTest, isEmptyAndSize_tracksAppendsAndInsertionsAndRemovals) {
    linkedListUT->append("foo");
    EXPECT_FALSE(linkedListUT->isEmpty());
    EXPECT_EQ(1, linkedListUT->listSize());

    linkedListUT->insert("bar", 1);
    EXPECT_FALSE(linkedListUT->isEmpty());
    EXPECT_EQ(2, linkedListUT->listSize());

    linkedListUT->append("baz");
    EXPECT_FALSE(linkedListUT->isEmpty());
    EXPECT_EQ(3, linkedListUT->listSize());

    linkedListUT->remove(0);
    EXPECT_FALSE(linkedListUT->isEmpty());
    EXPECT_EQ(2, linkedListUT->listSize());

    linkedListUT->append("qux");
    EXPECT_FALSE(linkedListUT->isEmpty());
    EXPECT_EQ(3, linkedListUT->listSize());

    linkedListUT->remove(2);
    EXPECT_FALSE(linkedListUT->isEmpty());
    EXPECT_EQ(2, linkedListUT->listSize());

    linkedListUT->insert("quux", 2);
    EXPECT_FALSE(linkedListUT->isEmpty());
    EXPECT_EQ(3, linkedListUT->listSize());

    linkedListUT->remove(0);
    linkedListUT->remove(0);
    linkedListUT->remove(0);
    EXPECT_TRUE(linkedListUT->isEmpty());
    EXPECT_EQ(0, linkedListUT->listSize());
}

TEST_F(LinkedListTest, insertionOperator_outputsContents) {
    std::stringstream("foo") >> *linkedListUT;
    std::stringstream("bar") >> *linkedListUT;
    std::stringstream("baz") >> *linkedListUT;

    EXPECT_EQ("foo", linkedListUT->getValueAt(0));
    EXPECT_EQ("bar", linkedListUT->getValueAt(1));
    EXPECT_EQ("baz", linkedListUT->getValueAt(2));
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

    auto otherLinkedListUT = new lab5::linked_list(*linkedListUT);
    EXPECT_EQ("foo", linkedListUT->getValueAt(0));
    EXPECT_EQ("foo", otherLinkedListUT->getValueAt(0));

    linkedListUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->getValueAt(0));
    EXPECT_EQ("foo", otherLinkedListUT->getValueAt(0));

    otherLinkedListUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->getValueAt(0));
    EXPECT_EQ("bar", otherLinkedListUT->getValueAt(0));

    linkedListUT->insert("qux", 0);
    EXPECT_EQ("qux", linkedListUT->getValueAt(0));
    EXPECT_EQ("bar", otherLinkedListUT->getValueAt(0));

    otherLinkedListUT->insert("qux", 0);
    EXPECT_EQ("qux", linkedListUT->getValueAt(0));
    EXPECT_EQ("qux", otherLinkedListUT->getValueAt(0));
}

TEST_F(LinkedListTest, copyConstructor_selfAssignment_doesNotChangeNodes) {
    linkedListUT->append("foo");
    linkedListUT->append("bar");
    linkedListUT->append("baz");

    linkedListUT = new lab5::linked_list(*linkedListUT);
    EXPECT_EQ("foo", linkedListUT->getValueAt(0));

    linkedListUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->getValueAt(0));

    linkedListUT->insert("qux", 0);
    EXPECT_EQ("qux", linkedListUT->getValueAt(0));
}

TEST_F(LinkedListTest, equalsOperator_hardCopiesNodes) {
    linkedListUT->append("foo");
    linkedListUT->append("bar");
    linkedListUT->append("baz");

    auto otherLinkedListUT = new lab5::linked_list;
    otherLinkedListUT->operator=(*linkedListUT);

    EXPECT_EQ("foo", linkedListUT->getValueAt(0));
    EXPECT_EQ("foo", otherLinkedListUT->getValueAt(0));

    linkedListUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->getValueAt(0));
    EXPECT_EQ("foo", otherLinkedListUT->getValueAt(0));

    otherLinkedListUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->getValueAt(0));
    EXPECT_EQ("bar", otherLinkedListUT->getValueAt(0));

    linkedListUT->insert("qux", 0);
    EXPECT_EQ("qux", linkedListUT->getValueAt(0));
    EXPECT_EQ("bar", otherLinkedListUT->getValueAt(0));

    otherLinkedListUT->insert("qux", 0);
    EXPECT_EQ("qux", linkedListUT->getValueAt(0));
    EXPECT_EQ("qux", otherLinkedListUT->getValueAt(0));
}

TEST_F(LinkedListTest, equalsOperator_selfAssignment_doesNotChangeNodes) {
    linkedListUT->append("foo");
    linkedListUT->append("bar");
    linkedListUT->append("baz");

    linkedListUT->operator=(*linkedListUT);
    EXPECT_EQ("foo", linkedListUT->getValueAt(0));

    linkedListUT->remove(0);
    EXPECT_EQ("bar", linkedListUT->getValueAt(0));

    linkedListUT->insert("qux", 0);
    EXPECT_EQ("qux", linkedListUT->getValueAt(0));
}

TEST_F(LinkedListTest, sort_sortsLinkedListData) {
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

    EXPECT_EQ("alfa", linkedListUT->getValueAt(0));
    EXPECT_EQ("bravo", linkedListUT->getValueAt(1));
    EXPECT_EQ("charlie", linkedListUT->getValueAt(2));
    EXPECT_EQ("delta", linkedListUT->getValueAt(3));
    EXPECT_EQ("echo", linkedListUT->getValueAt(4));
    EXPECT_EQ("foxtrot", linkedListUT->getValueAt(5));
    EXPECT_EQ("golf", linkedListUT->getValueAt(6));
    EXPECT_EQ("hotel", linkedListUT->getValueAt(7));
    EXPECT_EQ("india", linkedListUT->getValueAt(8));
    EXPECT_EQ("juliett", linkedListUT->getValueAt(9));
}

// Stack Tests
class StackTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        stackUT = new lab5::stack;
    }

    virtual void TearDown() {
        delete stackUT;
    }

public:
    lab5::stack *stackUT;
};

TEST(CrashTest, stack_crashTest) {
    auto stackUT = new lab5::stack;
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
    EXPECT_TRUE(stackUT->isEmpty());
}

TEST_F(StackTest, size_afterDefaultConstructor_0) {
    EXPECT_EQ(0, stackUT->stackSize());
}

TEST_F(StackTest, isEmptyAndSize_tracksPushesAndPops) {
    stackUT->push("foo");
    EXPECT_FALSE(stackUT->isEmpty());
    EXPECT_EQ(1, stackUT->stackSize());

    stackUT->push("bar");
    EXPECT_FALSE(stackUT->isEmpty());
    EXPECT_EQ(2, stackUT->stackSize());

    stackUT->pop();
    stackUT->pop();
    EXPECT_TRUE(stackUT->isEmpty());
    EXPECT_EQ(0, stackUT->stackSize());
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
    stackUT = new lab5::stack(input);
    EXPECT_EQ("foo", stackUT->top());
}

TEST_F(StackTest, copyConstructor_hardCopiesValues) {
    stackUT->push("foo");
    stackUT->push("bar");

    auto otherStackUT = new lab5::stack(*stackUT);

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
    auto otherStackUT = new lab5::stack;

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

// Queue Tests
class QueueTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        queueUT = new lab5::queue;
    }

    virtual void TearDown() {
        delete queueUT;
    }

public:
    lab5::queue *queueUT;
};

TEST(CrashTest, queue_crashTest) {
    auto queueUT = new lab5::queue;
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
    EXPECT_TRUE(queueUT->isEmpty());
}

TEST_F(QueueTest, size_afterDefaultConstructor_0) {
    EXPECT_EQ(0, queueUT->queueSize());
}

TEST_F(QueueTest, isEmptyAndSize_tracksEnqueuesAndDequeues) {
    queueUT->enqueue("foo");
    EXPECT_FALSE(queueUT->isEmpty());
    EXPECT_EQ(1, queueUT->queueSize());

    queueUT->enqueue("bar");
    EXPECT_FALSE(queueUT->isEmpty());
    EXPECT_EQ(2, queueUT->queueSize());

    queueUT->dequeue();
    queueUT->dequeue();
    EXPECT_TRUE(queueUT->isEmpty());
    EXPECT_EQ(0, queueUT->queueSize());
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
    queueUT = new lab5::queue(input);
    EXPECT_EQ("foo", queueUT->top());
}

TEST_F(QueueTest, copyConstructor_hardCopiesValues) {
    queueUT->enqueue("foo");
    queueUT->enqueue("bar");

    auto otherQueueUT = new lab5::queue(*queueUT);

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

    auto otherQueueUT = new lab5::queue;
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

// Linked List Calculator Tests
class FancyCalculatorTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        calculatorUT = new lab5::calculator;
    }

    virtual void TearDown() {
        delete calculatorUT;
    }

public:
    lab5::calculator *calculatorUT;
    std::string input;
};

TEST(CrashTest, fancyCalculator_crashTest) {
    auto fancyCalculatorUT = new lab5::calculator;
    delete fancyCalculatorUT;
}

TEST_F(FancyCalculatorTest, calculate_expressionsWithSingleOperations_calculatesCorrectAnswer) {
    delete calculatorUT;
    input = "1 + 2";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(3, calculatorUT->calculate());

    delete calculatorUT;
    input = "3 - 2";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(1, calculatorUT->calculate());

    delete calculatorUT;
    input = "2 * 3";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "6 / 3";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(2, calculatorUT->calculate());

    delete calculatorUT;
    input = "10 % 3";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(1, calculatorUT->calculate());

    delete calculatorUT;
    input = "2 ^ 3";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(8, calculatorUT->calculate());
}

TEST_F(FancyCalculatorTest, calculate_expressionsWithMultipleOperations_calculatesCorrectAnswer) {
    delete calculatorUT;
    input = "1 + 2 + 3";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "1 + 2 + 3 - 4";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(2, calculatorUT->calculate());

    delete calculatorUT;
    input = "10 * 2 - 3 + 10 / 5";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(19, calculatorUT->calculate());

    delete calculatorUT;
    input = "6 * 10 + 13 - 6 ^ 2 + 8 ^ 2 / 2 % 5";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(39, calculatorUT->calculate());
}

TEST_F(FancyCalculatorTest, calculate_expressionsWithParetheses_calculatesCorrectAnswer) {
    delete calculatorUT;
    input = "( 1 + 2 )";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(3, calculatorUT->calculate());

    delete calculatorUT;
    input = "( 1 + 2 + 3 )";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "( 1 + 2 ) + 3";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "1 + ( 2 + 3 )";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "8 + 7 * ( 7 - 2 )";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(43, calculatorUT->calculate());

    delete calculatorUT;
    input = "10 * ( 8 + 5 ) + 7 - 14 + 9";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(132, calculatorUT->calculate());

    delete calculatorUT;
    input = "15 - 10 * 6 + ( 14 - 7 % 2) * 7 ^ 2 + 11";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(603, calculatorUT->calculate());

    delete calculatorUT;
    input = "49 * ( 17 * ( 3 + 2 * ( 12 + 2 * ( 45 - 43 ) + 2 ) ) + 1 * ( 6 / 2 ) )";
    calculatorUT = new lab5::calculator(input);
    EXPECT_EQ(32634, calculatorUT->calculate());
}

TEST_F(FancyCalculatorTest, insertionAndExtractionOperator_outputsAndInputsInfixAndPostfixExpressions) {
    std::stringstream *stream;

    delete (calculatorUT);
    input = "1 + 2 + 3";
    calculatorUT = new lab5::calculator(input);

    testing::internal::CaptureStdout();
    std::cout << *calculatorUT;
    EXPECT_EQ("Infix: 1,+,2,+,3\nPostfix: 1,2,+,3,+", testing::internal::GetCapturedStdout());

    delete (calculatorUT);
    calculatorUT = new lab5::calculator();
    std::stringstream("1 + 2 + 3 - 4") >> *calculatorUT;

    testing::internal::CaptureStdout();
    std::cout << *calculatorUT;
    EXPECT_EQ("Infix: 1,+,2,+,3,-,4\nPostfix: 1,2,+,3,+,4,-", testing::internal::GetCapturedStdout());

    delete (calculatorUT);
    input = "49 * ( 17 * ( 3 + 2 * ( 12 + 2 * ( 45 - 43 ) + 2 ) ) + 1 * ( 6 / 2 ) )";
    calculatorUT = new lab5::calculator(input);

    testing::internal::CaptureStdout();
    std::cout << *calculatorUT;
    EXPECT_EQ("Infix: 49,*,(,17,*,(,3,+,2,*,(,12,+,2,*,(,45,-,43,),+,2,),),+,1,*,(,6,/,2,),)\nPostfix: 49,17,3,2,12,2,45,43,-,*,+,2,+,*,+,*,1,6,2,/,*,+,*", testing::internal::GetCapturedStdout());
}