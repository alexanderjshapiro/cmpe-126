#include "gtest/gtest.h"
#include "fifo.h"
#include "lifo.h"

class FifoTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        fifoUT = new lab3::fifo;
    }

    virtual void TearDown() {
        delete (fifoUT);
    }

public:
    lab3::fifo *fifoUT;
};

TEST(CrashTest, fifo_crashTest) {
    auto fifoUT = new lab3::fifo;
    delete fifoUT;
}

TEST_F(FifoTest, enqueue_doesNotCrash) {
    fifoUT->enqueue("foo");
}

TEST_F(FifoTest, enqueue_addsToQueue) {
    fifoUT->enqueue("foo");
    EXPECT_EQ("foo", fifoUT->top());
    fifoUT->enqueue("bar");
    EXPECT_EQ("foo", fifoUT->top());
}

TEST_F(FifoTest, enqueue_queueIsFull_crashes) {
    for (unsigned i = 0; i < 100; i++) {
        fifoUT->enqueue(std::to_string(i));
    }
    EXPECT_EQ("0", fifoUT->top());

    EXPECT_ANY_THROW(fifoUT->enqueue("100"));
    EXPECT_ANY_THROW(fifoUT->enqueue("101"));

    fifoUT->dequeue();
    EXPECT_NO_THROW(fifoUT->enqueue("99"));
}

TEST_F(FifoTest, dequeue_doesNotCrash) {
    fifoUT->enqueue("foo");
    fifoUT->dequeue();
}

TEST_F(FifoTest, dequeue_removesFromQueue) {
    fifoUT->enqueue("foo");
    fifoUT->enqueue("bar");
    fifoUT->dequeue();
    EXPECT_EQ("bar", fifoUT->top());
}

TEST_F(FifoTest, dequeue_queueIsEmpty_crashes) {
    EXPECT_ANY_THROW(fifoUT->dequeue());

    fifoUT->enqueue("foo");
    fifoUT->enqueue("bar");
    fifoUT->dequeue();
    fifoUT->dequeue();
    EXPECT_ANY_THROW(fifoUT->dequeue());
}

TEST_F(FifoTest, top_doesNotCrash) {
    fifoUT->enqueue("foo");
    fifoUT->top();
}

TEST_F(FifoTest, top_getsFrontOfQueue) {
    fifoUT->enqueue("foo");
    EXPECT_EQ("foo", fifoUT->top());

    fifoUT->enqueue("bar");
    EXPECT_EQ("foo", fifoUT->top());

    fifoUT->dequeue();
    EXPECT_EQ("bar", fifoUT->top());

    fifoUT->enqueue("baz");
    EXPECT_EQ("bar", fifoUT->top());
}

TEST_F(FifoTest, top_queueIsEmpty_crashes) {
    EXPECT_ANY_THROW(fifoUT->top());

    fifoUT->enqueue("foo");
    fifoUT->enqueue("bar");
    fifoUT->dequeue();
    fifoUT->dequeue();
    EXPECT_ANY_THROW(fifoUT->top());
}

TEST_F(FifoTest, isEmpty_afterDefaultConstructor_true) {
    EXPECT_TRUE(fifoUT->is_empty());
}

TEST_F(FifoTest, size_afterDefaultConstructor_0) {
    EXPECT_EQ(0, fifoUT->size());
}

TEST_F(FifoTest, isEmptyAndSize_tracksEnqueuesAndDequeues) {
    fifoUT->enqueue("foo");
    EXPECT_FALSE(fifoUT->is_empty());
    EXPECT_EQ(1, fifoUT->size());

    fifoUT->enqueue("bar");
    EXPECT_FALSE(fifoUT->is_empty());
    EXPECT_EQ(2, fifoUT->size());

    fifoUT->dequeue();
    fifoUT->dequeue();
    EXPECT_TRUE(fifoUT->is_empty());
    EXPECT_EQ(0, fifoUT->size());
}

TEST_F(FifoTest, parameterizedConstructor_enqueuesInitialValue) {
    fifoUT = new lab3::fifo("foo");
    EXPECT_EQ("foo", fifoUT->top());
}

TEST_F(FifoTest, copyConstructor_hardCopiesValues) {
    fifoUT->enqueue("foo");
    fifoUT->enqueue("bar");

    auto otherFifoUT = new lab3::fifo(*fifoUT);

    EXPECT_EQ("foo", fifoUT->top());
    EXPECT_EQ("foo", otherFifoUT->top());

    fifoUT->dequeue();
    EXPECT_EQ("bar", fifoUT->top());
    EXPECT_EQ("foo", otherFifoUT->top());

    otherFifoUT->dequeue();
    EXPECT_EQ("bar", fifoUT->top());
    EXPECT_EQ("bar", otherFifoUT->top());
}

TEST_F(FifoTest, equalsOperator_hardCopiesValues) {
    fifoUT->enqueue("foo");
    fifoUT->enqueue("bar");

    auto otherFifoUT = new lab3::fifo;
    otherFifoUT->operator=(*fifoUT);

    EXPECT_EQ("foo", fifoUT->top());
    EXPECT_EQ("foo", otherFifoUT->top());

    fifoUT->dequeue();
    EXPECT_EQ("bar", fifoUT->top());
    EXPECT_EQ("foo", otherFifoUT->top());

    otherFifoUT->dequeue();
    EXPECT_EQ("bar", fifoUT->top());
    EXPECT_EQ("bar", otherFifoUT->top());
}

TEST_F(FifoTest, fifo_loopback) {
    fifoUT->enqueue("test Input");
    for (int i = 0; i < 150; ++i) {
        ASSERT_NO_THROW(fifoUT->enqueue("test Input")) << "failed on iteration: " << i << "\n";
        ASSERT_EQ("test Input", fifoUT->top()) << "failed on iteration: " << i << "\n";
        ASSERT_NO_THROW(fifoUT->enqueue("test Input")) << "failed on iteration: " << i << "\n";
        ASSERT_EQ("test Input", fifoUT->top()) << "failed on iteration: " << i << "\n";
        ASSERT_NO_THROW(fifoUT->enqueue("test Input")) << "failed on iteration: " << i << "\n";
        ASSERT_EQ("test Input", fifoUT->top()) << "failed on iteration: " << i << "\n";

        ASSERT_EQ(4, fifoUT->size()) << "failed on iteration: " << i << "\n";
        ASSERT_FALSE(fifoUT->is_empty()) << "failed on iteration: " << i << "\n";

        ASSERT_EQ("test Input", fifoUT->top()) << "failed on iteration: " << i << "\n";
        ASSERT_NO_THROW(fifoUT->dequeue()) << "failed on iteration: " << i << "\n";
        ASSERT_EQ("test Input", fifoUT->top()) << "failed on iteration: " << i << "\n";
        ASSERT_NO_THROW(fifoUT->dequeue()) << "failed on iteration: " << i << "\n";
        ASSERT_EQ("test Input", fifoUT->top()) << "failed on iteration: " << i << "\n";
        ASSERT_NO_THROW(fifoUT->dequeue()) << "failed on iteration: " << i << "\n";

        ASSERT_EQ(1, fifoUT->size()) << "failed on iteration: " << i << "\n";
        ASSERT_FALSE(fifoUT->is_empty()) << "failed on iteration: " << i << "\n";
    }
    ASSERT_EQ("test Input", fifoUT->top());
    ASSERT_NO_THROW(fifoUT->dequeue());
}

class LifoTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        lifoUT = new lab3::lifo;
    }

    virtual void TearDown() {
        delete (lifoUT);
    }

public:
    lab3::lifo *lifoUT;
};


TEST(CrashTest, lifo_crashTest) {
    auto lifoUT = new lab3::lifo;
    delete lifoUT;
}

TEST_F(LifoTest, push_doesNotCrash) {
    lifoUT->push("foo");
}

TEST_F(LifoTest, push_addsToStack) {
    lifoUT->push("foo");
    EXPECT_EQ("foo", lifoUT->top());
    lifoUT->push("bar");
    EXPECT_EQ("bar", lifoUT->top());
}

TEST_F(LifoTest, push_stackIsFull_crashes) {
    for (unsigned i = 0; i < 100; i++) {
        lifoUT->push(std::to_string(i));
    }
    EXPECT_EQ("99", lifoUT->top());

    EXPECT_ANY_THROW(lifoUT->push("100"));
    EXPECT_ANY_THROW(lifoUT->push("101"));

    lifoUT->pop();
    EXPECT_NO_THROW(lifoUT->push("99"));
}

TEST_F(LifoTest, pop_doesNotCrash) {
    lifoUT->push("foo");
    lifoUT->pop();
}

TEST_F(LifoTest, pop_removesFromStack) {
    lifoUT->push("foo");
    lifoUT->push("bar");
    lifoUT->pop();
    EXPECT_EQ("foo", lifoUT->top());
}

TEST_F(LifoTest, pop_stackIsEmpty_crashes) {
    EXPECT_ANY_THROW(lifoUT->pop());

    lifoUT->push("foo");
    lifoUT->push("bar");
    lifoUT->pop();
    lifoUT->pop();
    EXPECT_ANY_THROW(lifoUT->pop());
}

TEST_F(LifoTest, top_doesNotCrash) {
    lifoUT->push("foo");
    lifoUT->top();
}

TEST_F(LifoTest, top_getsTopOfStack) {
    lifoUT->push("foo");
    EXPECT_EQ("foo", lifoUT->top());

    lifoUT->push("bar");
    EXPECT_EQ("bar", lifoUT->top());

    lifoUT->pop();
    EXPECT_EQ("foo", lifoUT->top());

    lifoUT->push("baz");
    EXPECT_EQ("baz", lifoUT->top());
}

TEST_F(LifoTest, top_stackIsEmpty_crashes) {
    EXPECT_ANY_THROW(lifoUT->top());

    lifoUT->push("foo");
    lifoUT->push("bar");
    lifoUT->pop();
    lifoUT->pop();
    EXPECT_ANY_THROW(lifoUT->top());
}

TEST_F(LifoTest, isEmpty_afterDefaultConstructor_true) {
    EXPECT_TRUE(lifoUT->is_empty());
}

TEST_F(LifoTest, size_afterDefaultConstructor_0) {
    EXPECT_EQ(0, lifoUT->size());
}

TEST_F(LifoTest, isEmptyAndSize_tracksPushesAndPops) {
    lifoUT->push("foo");
    EXPECT_FALSE(lifoUT->is_empty());
    EXPECT_EQ(1, lifoUT->size());

    lifoUT->push("bar");
    EXPECT_FALSE(lifoUT->is_empty());
    EXPECT_EQ(2, lifoUT->size());

    lifoUT->pop();
    lifoUT->pop();
    EXPECT_TRUE(lifoUT->is_empty());
    EXPECT_EQ(0, lifoUT->size());
}

TEST_F(LifoTest, parameterizedConstructor_pushesInitialValue) {
    lifoUT = new lab3::lifo("foo");
    EXPECT_EQ("foo", lifoUT->top());
}

TEST_F(LifoTest, copyConstructor_hardCopiesValues) {
    lifoUT->push("foo");
    lifoUT->push("bar");

    auto otherLifoUT = new lab3::lifo(*lifoUT);

    EXPECT_EQ("bar", lifoUT->top());
    EXPECT_EQ("bar", otherLifoUT->top());

    lifoUT->pop();
    EXPECT_EQ("foo", lifoUT->top());
    EXPECT_EQ("bar", otherLifoUT->top());

    otherLifoUT->pop();
    EXPECT_EQ("foo", lifoUT->top());
    EXPECT_EQ("foo", otherLifoUT->top());
}

TEST_F(LifoTest, equalsOperator_hardCopiesValues) {
    auto otherLifoObj = new lab3::lifo;

    lifoUT->push("foo");
    lifoUT->push("bar");

    otherLifoObj->operator=(*lifoUT);

    EXPECT_EQ("bar", lifoUT->top());
    EXPECT_EQ("bar", otherLifoObj->top());

    lifoUT->pop();
    EXPECT_EQ("foo", lifoUT->top());
    EXPECT_EQ("bar", otherLifoObj->top());

    otherLifoObj->pop();
    EXPECT_EQ("foo", lifoUT->top());
    EXPECT_EQ("foo", otherLifoObj->top());
}