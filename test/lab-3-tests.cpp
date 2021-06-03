#include "gtest/gtest.h"
#include "StringVectorQueue.h"
#include "StringVectorStack.h"

class StringVectorQueueTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        stringVectorQueueUT = new lab3::StringVectorQueue;
    }

    virtual void TearDown() {
        delete (stringVectorQueueUT);
    }

public:
    lab3::StringVectorQueue *stringVectorQueueUT;
};

TEST(CrashTest, fifo_crashTest) {
    auto fifoUT = new lab3::StringVectorQueue;
    delete fifoUT;
}

TEST_F(StringVectorQueueTest, enqueue_doesNotCrash) {
    stringVectorQueueUT->enqueue("foo");
}

TEST_F(StringVectorQueueTest, enqueue_addsToQueue) {
    stringVectorQueueUT->enqueue("foo");
    EXPECT_EQ("foo", stringVectorQueueUT->front());
    stringVectorQueueUT->enqueue("bar");
    EXPECT_EQ("foo", stringVectorQueueUT->front());
}

TEST_F(StringVectorQueueTest, enqueue_queueIsFull_crashes) {
    for (unsigned i = 0; i < 100; i++) {
        stringVectorQueueUT->enqueue(std::to_string(i));
    }
    EXPECT_EQ("0", stringVectorQueueUT->front());

    EXPECT_ANY_THROW(stringVectorQueueUT->enqueue("100"));
    EXPECT_ANY_THROW(stringVectorQueueUT->enqueue("101"));

    stringVectorQueueUT->dequeue();
    EXPECT_NO_THROW(stringVectorQueueUT->enqueue("99"));
}

TEST_F(StringVectorQueueTest, dequeue_doesNotCrash) {
    stringVectorQueueUT->enqueue("foo");
    stringVectorQueueUT->dequeue();
}

TEST_F(StringVectorQueueTest, dequeue_removesFromQueue) {
    stringVectorQueueUT->enqueue("foo");
    stringVectorQueueUT->enqueue("bar");
    stringVectorQueueUT->dequeue();
    EXPECT_EQ("bar", stringVectorQueueUT->front());
}

TEST_F(StringVectorQueueTest, dequeue_queueIsEmpty_crashes) {
    EXPECT_ANY_THROW(stringVectorQueueUT->dequeue());

    stringVectorQueueUT->enqueue("foo");
    stringVectorQueueUT->enqueue("bar");
    stringVectorQueueUT->dequeue();
    stringVectorQueueUT->dequeue();
    EXPECT_ANY_THROW(stringVectorQueueUT->dequeue());
}

TEST_F(StringVectorQueueTest, top_doesNotCrash) {
    stringVectorQueueUT->enqueue("foo");
    stringVectorQueueUT->front();
}

TEST_F(StringVectorQueueTest, top_getsFrontOfQueue) {
    stringVectorQueueUT->enqueue("foo");
    EXPECT_EQ("foo", stringVectorQueueUT->front());

    stringVectorQueueUT->enqueue("bar");
    EXPECT_EQ("foo", stringVectorQueueUT->front());

    stringVectorQueueUT->dequeue();
    EXPECT_EQ("bar", stringVectorQueueUT->front());

    stringVectorQueueUT->enqueue("baz");
    EXPECT_EQ("bar", stringVectorQueueUT->front());
}

TEST_F(StringVectorQueueTest, top_queueIsEmpty_crashes) {
    EXPECT_ANY_THROW(stringVectorQueueUT->front());

    stringVectorQueueUT->enqueue("foo");
    stringVectorQueueUT->enqueue("bar");
    stringVectorQueueUT->dequeue();
    stringVectorQueueUT->dequeue();
    EXPECT_ANY_THROW(stringVectorQueueUT->front());
}

TEST_F(StringVectorQueueTest, isEmpty_afterDefaultConstructor_true) {
    EXPECT_TRUE(stringVectorQueueUT->empty());
}

TEST_F(StringVectorQueueTest, size_afterDefaultConstructor_0) {
    EXPECT_EQ(0, stringVectorQueueUT->size());
}

TEST_F(StringVectorQueueTest, isEmptyAndSize_tracksEnqueuesAndDequeues) {
    stringVectorQueueUT->enqueue("foo");
    EXPECT_FALSE(stringVectorQueueUT->empty());
    EXPECT_EQ(1, stringVectorQueueUT->size());

    stringVectorQueueUT->enqueue("bar");
    EXPECT_FALSE(stringVectorQueueUT->empty());
    EXPECT_EQ(2, stringVectorQueueUT->size());

    stringVectorQueueUT->dequeue();
    stringVectorQueueUT->dequeue();
    EXPECT_TRUE(stringVectorQueueUT->empty());
    EXPECT_EQ(0, stringVectorQueueUT->size());
}

TEST_F(StringVectorQueueTest, parameterizedConstructor_enqueuesInitialValue) {
    stringVectorQueueUT = new lab3::StringVectorQueue("foo");
    EXPECT_EQ("foo", stringVectorQueueUT->front());
}

TEST_F(StringVectorQueueTest, copyConstructor_hardCopiesValues) {
    stringVectorQueueUT->enqueue("foo");
    stringVectorQueueUT->enqueue("bar");

    auto otherFifoUT = new lab3::StringVectorQueue(*stringVectorQueueUT);

    EXPECT_EQ("foo", stringVectorQueueUT->front());
    EXPECT_EQ("foo", otherFifoUT->front());

    stringVectorQueueUT->dequeue();
    EXPECT_EQ("bar", stringVectorQueueUT->front());
    EXPECT_EQ("foo", otherFifoUT->front());

    otherFifoUT->dequeue();
    EXPECT_EQ("bar", stringVectorQueueUT->front());
    EXPECT_EQ("bar", otherFifoUT->front());
}

TEST_F(StringVectorQueueTest, equalsOperator_hardCopiesValues) {
    stringVectorQueueUT->enqueue("foo");
    stringVectorQueueUT->enqueue("bar");

    auto otherFifoUT = new lab3::StringVectorQueue;
    otherFifoUT->operator=(*stringVectorQueueUT);

    EXPECT_EQ("foo", stringVectorQueueUT->front());
    EXPECT_EQ("foo", otherFifoUT->front());

    stringVectorQueueUT->dequeue();
    EXPECT_EQ("bar", stringVectorQueueUT->front());
    EXPECT_EQ("foo", otherFifoUT->front());

    otherFifoUT->dequeue();
    EXPECT_EQ("bar", stringVectorQueueUT->front());
    EXPECT_EQ("bar", otherFifoUT->front());
}

TEST_F(StringVectorQueueTest, fifo_cirularlyLoopsBack) {
    stringVectorQueueUT->enqueue("test Input");
    for (int i = 0; i < 150; ++i) {
        ASSERT_NO_THROW(stringVectorQueueUT->enqueue("test Input")) << "failed on iteration: " << i << "\n";
        ASSERT_EQ("test Input", stringVectorQueueUT->front()) << "failed on iteration: " << i << "\n";
        ASSERT_NO_THROW(stringVectorQueueUT->enqueue("test Input")) << "failed on iteration: " << i << "\n";
        ASSERT_EQ("test Input", stringVectorQueueUT->front()) << "failed on iteration: " << i << "\n";
        ASSERT_NO_THROW(stringVectorQueueUT->enqueue("test Input")) << "failed on iteration: " << i << "\n";
        ASSERT_EQ("test Input", stringVectorQueueUT->front()) << "failed on iteration: " << i << "\n";

        ASSERT_EQ(4, stringVectorQueueUT->size()) << "failed on iteration: " << i << "\n";
        ASSERT_FALSE(stringVectorQueueUT->empty()) << "failed on iteration: " << i << "\n";

        ASSERT_EQ("test Input", stringVectorQueueUT->front()) << "failed on iteration: " << i << "\n";
        ASSERT_NO_THROW(stringVectorQueueUT->dequeue()) << "failed on iteration: " << i << "\n";
        ASSERT_EQ("test Input", stringVectorQueueUT->front()) << "failed on iteration: " << i << "\n";
        ASSERT_NO_THROW(stringVectorQueueUT->dequeue()) << "failed on iteration: " << i << "\n";
        ASSERT_EQ("test Input", stringVectorQueueUT->front()) << "failed on iteration: " << i << "\n";
        ASSERT_NO_THROW(stringVectorQueueUT->dequeue()) << "failed on iteration: " << i << "\n";

        ASSERT_EQ(1, stringVectorQueueUT->size()) << "failed on iteration: " << i << "\n";
        ASSERT_FALSE(stringVectorQueueUT->empty()) << "failed on iteration: " << i << "\n";
    }
    ASSERT_EQ("test Input", stringVectorQueueUT->front());
    ASSERT_NO_THROW(stringVectorQueueUT->dequeue());
}

class StringVectorStackTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        stringVectorStackUT = new lab3::StringVectorStack;
    }

    virtual void TearDown() {
        delete (stringVectorStackUT);
    }

public:
    lab3::StringVectorStack *stringVectorStackUT;
};


TEST(CrashTest, lifo_crashTest) {
    auto lifoUT = new lab3::StringVectorStack;
    delete lifoUT;
}

TEST_F(StringVectorStackTest, push_doesNotCrash) {
    stringVectorStackUT->push("foo");
}

TEST_F(StringVectorStackTest, push_addsToStack) {
    stringVectorStackUT->push("foo");
    EXPECT_EQ("foo", stringVectorStackUT->top());
    stringVectorStackUT->push("bar");
    EXPECT_EQ("bar", stringVectorStackUT->top());
}

TEST_F(StringVectorStackTest, push_stackIsFull_crashes) {
    for (unsigned i = 0; i < 100; i++) {
        stringVectorStackUT->push(std::to_string(i));
    }
    EXPECT_EQ("99", stringVectorStackUT->top());

    EXPECT_ANY_THROW(stringVectorStackUT->push("100"));
    EXPECT_ANY_THROW(stringVectorStackUT->push("101"));

    stringVectorStackUT->pop();
    EXPECT_NO_THROW(stringVectorStackUT->push("99"));
}

TEST_F(StringVectorStackTest, pop_doesNotCrash) {
    stringVectorStackUT->push("foo");
    stringVectorStackUT->pop();
}

TEST_F(StringVectorStackTest, pop_removesFromStack) {
    stringVectorStackUT->push("foo");
    stringVectorStackUT->push("bar");
    stringVectorStackUT->pop();
    EXPECT_EQ("foo", stringVectorStackUT->top());
}

TEST_F(StringVectorStackTest, pop_stackIsEmpty_crashes) {
    EXPECT_ANY_THROW(stringVectorStackUT->pop());

    stringVectorStackUT->push("foo");
    stringVectorStackUT->push("bar");
    stringVectorStackUT->pop();
    stringVectorStackUT->pop();
    EXPECT_ANY_THROW(stringVectorStackUT->pop());
}

TEST_F(StringVectorStackTest, top_doesNotCrash) {
    stringVectorStackUT->push("foo");
    stringVectorStackUT->top();
}

TEST_F(StringVectorStackTest, top_getsTopOfStack) {
    stringVectorStackUT->push("foo");
    EXPECT_EQ("foo", stringVectorStackUT->top());

    stringVectorStackUT->push("bar");
    EXPECT_EQ("bar", stringVectorStackUT->top());

    stringVectorStackUT->pop();
    EXPECT_EQ("foo", stringVectorStackUT->top());

    stringVectorStackUT->push("baz");
    EXPECT_EQ("baz", stringVectorStackUT->top());
}

TEST_F(StringVectorStackTest, top_stackIsEmpty_crashes) {
    EXPECT_ANY_THROW(stringVectorStackUT->top());

    stringVectorStackUT->push("foo");
    stringVectorStackUT->push("bar");
    stringVectorStackUT->pop();
    stringVectorStackUT->pop();
    EXPECT_ANY_THROW(stringVectorStackUT->top());
}

TEST_F(StringVectorStackTest, isEmpty_afterDefaultConstructor_true) {
    EXPECT_TRUE(stringVectorStackUT->empty());
}

TEST_F(StringVectorStackTest, size_afterDefaultConstructor_0) {
    EXPECT_EQ(0, stringVectorStackUT->size());
}

TEST_F(StringVectorStackTest, isEmptyAndSize_tracksPushesAndPops) {
    stringVectorStackUT->push("foo");
    EXPECT_FALSE(stringVectorStackUT->empty());
    EXPECT_EQ(1, stringVectorStackUT->size());

    stringVectorStackUT->push("bar");
    EXPECT_FALSE(stringVectorStackUT->empty());
    EXPECT_EQ(2, stringVectorStackUT->size());

    stringVectorStackUT->pop();
    stringVectorStackUT->pop();
    EXPECT_TRUE(stringVectorStackUT->empty());
    EXPECT_EQ(0, stringVectorStackUT->size());
}

TEST_F(StringVectorStackTest, parameterizedConstructor_pushesInitialValue) {
    stringVectorStackUT = new lab3::StringVectorStack("foo");
    EXPECT_EQ("foo", stringVectorStackUT->top());
}

TEST_F(StringVectorStackTest, copyConstructor_hardCopiesValues) {
    stringVectorStackUT->push("foo");
    stringVectorStackUT->push("bar");

    auto otherLifoUT = new lab3::StringVectorStack(*stringVectorStackUT);

    EXPECT_EQ("bar", stringVectorStackUT->top());
    EXPECT_EQ("bar", otherLifoUT->top());

    stringVectorStackUT->pop();
    EXPECT_EQ("foo", stringVectorStackUT->top());
    EXPECT_EQ("bar", otherLifoUT->top());

    otherLifoUT->pop();
    EXPECT_EQ("foo", stringVectorStackUT->top());
    EXPECT_EQ("foo", otherLifoUT->top());
}

TEST_F(StringVectorStackTest, equalsOperator_hardCopiesValues) {
    auto otherLifoObj = new lab3::StringVectorStack;

    stringVectorStackUT->push("foo");
    stringVectorStackUT->push("bar");

    otherLifoObj->operator=(*stringVectorStackUT);

    EXPECT_EQ("bar", stringVectorStackUT->top());
    EXPECT_EQ("bar", otherLifoObj->top());

    stringVectorStackUT->pop();
    EXPECT_EQ("foo", stringVectorStackUT->top());
    EXPECT_EQ("bar", otherLifoObj->top());

    otherLifoObj->pop();
    EXPECT_EQ("foo", stringVectorStackUT->top());
    EXPECT_EQ("foo", otherLifoObj->top());
}