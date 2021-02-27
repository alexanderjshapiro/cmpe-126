#include "gtest/gtest.h"
#include "stringVector.h"

class StringVectorTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        stringVectorUT = new lab2::stringVector;
    }

    virtual void TearDown() {
        delete stringVectorUT;
    }

public:
    lab2::stringVector *stringVectorUT;
};

TEST(CrashTest, stringVectorCrashTest) {
    auto *stringVectorUT = new lab2::stringVector;
    delete stringVectorUT;
}

TEST_F(StringVectorTest, capacity_getsAllocatedLength) {
    EXPECT_EQ(0, stringVectorUT->capacity());
}

TEST_F(StringVectorTest, reserve_setsAllocatedLength) {
    stringVectorUT->reserve(10);
    EXPECT_EQ(10, stringVectorUT->capacity());

    stringVectorUT->reserve(1000000);
    EXPECT_EQ(1000000, stringVectorUT->capacity());

    stringVectorUT->reserve(5);
    EXPECT_EQ(5, stringVectorUT->capacity());
}

TEST_F(StringVectorTest, reserve_reservesMemory) {
    EXPECT_ANY_THROW(stringVectorUT->operator[](0));

    stringVectorUT->reserve(2);
    stringVectorUT->append("foo");
    stringVectorUT->append("bar");
    EXPECT_NO_THROW(stringVectorUT->operator[](0));
    EXPECT_NO_THROW(stringVectorUT->operator[](1));
    EXPECT_ANY_THROW(stringVectorUT->operator[](2));

    stringVectorUT->reserve(0);
    EXPECT_ANY_THROW(stringVectorUT->operator[](0));
    EXPECT_ANY_THROW(stringVectorUT->operator[](1));
}

TEST_F(StringVectorTest, reserve_newSizeIsLessThanAllocatedLength_truncatesData) {
    EXPECT_ANY_THROW(stringVectorUT->operator[](0));

    stringVectorUT->reserve(3);
    stringVectorUT->append("foo");
    stringVectorUT->append("bar");
    stringVectorUT->append("baz");
    EXPECT_EQ("foo", stringVectorUT->operator[](0));
    EXPECT_EQ("bar", stringVectorUT->operator[](1));
    EXPECT_EQ("baz", stringVectorUT->operator[](2));

    stringVectorUT->reserve(2);
    EXPECT_EQ("foo", stringVectorUT->operator[](0));
    EXPECT_EQ("bar", stringVectorUT->operator[](1));
    EXPECT_ANY_THROW(stringVectorUT->operator[](2));

    stringVectorUT->reserve(0);
    EXPECT_ANY_THROW(stringVectorUT->operator[](0));
    EXPECT_ANY_THROW(stringVectorUT->operator[](1));
    EXPECT_ANY_THROW(stringVectorUT->operator[](2));
}

TEST_F(StringVectorTest, append_doesNotCrash) {
    stringVectorUT->append(std::string("foo"));
}

TEST_F(StringVectorTest, append_addsToEndOfData) {
    stringVectorUT->reserve(2);

    stringVectorUT->append("foo");
    EXPECT_EQ("foo", stringVectorUT->operator[](0));

    stringVectorUT->append("bar");
    EXPECT_EQ("foo", stringVectorUT->operator[](0));
    EXPECT_EQ("bar", stringVectorUT->operator[](1));
}

TEST_F(StringVectorTest, append_allocatedLengthAfterDefaultConstructor_1) {
    stringVectorUT->append("foo");
    EXPECT_EQ(1, stringVectorUT->capacity());
}

TEST_F(StringVectorTest, append_doublesAllocatedLengthIfFull) {
    stringVectorUT->reserve(1);

    stringVectorUT->append("foo");
    EXPECT_EQ(1, stringVectorUT->capacity());

    stringVectorUT->append("bar");
    EXPECT_EQ(2, stringVectorUT->capacity());

    stringVectorUT->append("baz");
    EXPECT_EQ(4, stringVectorUT->capacity());
}

TEST_F(StringVectorTest, size_afterDefaultConstructor_0) {
    EXPECT_EQ(0, stringVectorUT->size());
}

TEST_F(StringVectorTest, emptyAndSize_tracksAppends) {
    EXPECT_TRUE(stringVectorUT->empty());

    stringVectorUT->append("foo");
    EXPECT_EQ(1, stringVectorUT->size());
    EXPECT_FALSE(stringVectorUT->empty());

    stringVectorUT->append("bar");
    EXPECT_EQ(2, stringVectorUT->size());
    EXPECT_FALSE(stringVectorUT->empty());

    stringVectorUT->append("baz");
    stringVectorUT->append("qux");
    EXPECT_EQ(4, stringVectorUT->size());
    EXPECT_FALSE(stringVectorUT->empty());
}

TEST_F(StringVectorTest, bracketsOperator_accessesData) {
    EXPECT_ANY_THROW(stringVectorUT->operator[](0));
    EXPECT_ANY_THROW(stringVectorUT->operator[](3));
    EXPECT_ANY_THROW(stringVectorUT->operator[](1000000));
    EXPECT_ANY_THROW(stringVectorUT->operator[](-1));
    EXPECT_ANY_THROW(stringVectorUT->operator[](-100));

    stringVectorUT->append("foo");
    EXPECT_EQ("foo", stringVectorUT->operator[](0));

    stringVectorUT->append("bar");
    EXPECT_EQ("foo", stringVectorUT->operator[](0));
    EXPECT_EQ("bar", stringVectorUT->operator[](1));

    stringVectorUT->append("baz");
    EXPECT_EQ("foo", stringVectorUT->operator[](0));
    EXPECT_EQ("bar", stringVectorUT->operator[](1));
    EXPECT_EQ("baz", stringVectorUT->operator[](2));

    stringVectorUT->operator[](1) = "qux";
    EXPECT_EQ("foo", stringVectorUT->operator[](0));
    EXPECT_EQ("qux", stringVectorUT->operator[](1));
    EXPECT_EQ("baz", stringVectorUT->operator[](2));

    EXPECT_NO_THROW(stringVectorUT->operator[](0));
    EXPECT_ANY_THROW(stringVectorUT->operator[](3));
    EXPECT_ANY_THROW(stringVectorUT->operator[](1000000));
    EXPECT_ANY_THROW(stringVectorUT->operator[](-1));
    EXPECT_ANY_THROW(stringVectorUT->operator[](-100));
}

TEST_F(StringVectorTest, equalsOperator_hardCopiesData) {
    stringVectorUT->reserve(3);
    stringVectorUT->append("foo");
    stringVectorUT->append("bar");

    stringVectorUT->operator=(*stringVectorUT);

    EXPECT_EQ("foo", stringVectorUT->operator[](0));
    EXPECT_EQ("bar", stringVectorUT->operator[](1));
    EXPECT_EQ(3, stringVectorUT->capacity());
    EXPECT_EQ(2, stringVectorUT->size());

    auto *otherStringVectorUT = new lab2::stringVector();
    EXPECT_EQ(0, otherStringVectorUT->capacity());
    EXPECT_EQ(0, otherStringVectorUT->size());

    otherStringVectorUT->operator=(*stringVectorUT);

    EXPECT_EQ("foo", stringVectorUT->operator[](0));
    EXPECT_EQ("bar", stringVectorUT->operator[](1));
    EXPECT_EQ(3, stringVectorUT->capacity());
    EXPECT_EQ(2, stringVectorUT->size());
    EXPECT_EQ("foo", otherStringVectorUT->operator[](0));
    EXPECT_EQ("bar", otherStringVectorUT->operator[](1));
    EXPECT_EQ(3, otherStringVectorUT->capacity());
    EXPECT_EQ(2, otherStringVectorUT->size());

    stringVectorUT->append("baz");
    EXPECT_EQ("baz", stringVectorUT->operator[](2));
    EXPECT_ANY_THROW(otherStringVectorUT->operator[](2));

    otherStringVectorUT->append("baz");
    EXPECT_EQ("baz", stringVectorUT->operator[](2));
    EXPECT_EQ("baz", otherStringVectorUT->operator[](2));
}

TEST_F(StringVectorTest, swap_swapsDataValues) {
    stringVectorUT->append("some string");
    stringVectorUT->append("some other string");
    stringVectorUT->append("some other other string");
    stringVectorUT->append("some other other other string");

    stringVectorUT->swap(0, 3);
    stringVectorUT->swap(1, 2);

    EXPECT_EQ("some string", stringVectorUT->operator[](3));
    EXPECT_EQ("some other string", stringVectorUT->operator[](2));
    EXPECT_EQ("some other other string", stringVectorUT->operator[](1));
    EXPECT_EQ("some other other other string", stringVectorUT->operator[](0));
}

TEST_F(StringVectorTest, sort_sortsDataValues) {
    stringVectorUT->append("yellow");
    stringVectorUT->append("glad");
    stringVectorUT->append("california");
    stringVectorUT->append("question");
    stringVectorUT->append("bear");
    stringVectorUT->append("restful");
    stringVectorUT->append("extra");
    stringVectorUT->append("nugget");
    stringVectorUT->append("door");
    stringVectorUT->append("vehicle");
    stringVectorUT->append("full");
    stringVectorUT->append("know");
    stringVectorUT->append("later");
    stringVectorUT->append("apple");
    stringVectorUT->append("true");
    stringVectorUT->append("joker");
    stringVectorUT->append("xeon");
    stringVectorUT->append("welcome");
    stringVectorUT->append("mannequin");
    stringVectorUT->append("oriented");
    stringVectorUT->append("programming");
    stringVectorUT->append("hello");
    stringVectorUT->append("sleep");
    stringVectorUT->append("igloo");
    stringVectorUT->append("object");
    stringVectorUT->append("under");
    stringVectorUT->append("fail");

    stringVectorUT->sort();

    EXPECT_EQ("apple", stringVectorUT->operator[](0));
    EXPECT_EQ("bear", stringVectorUT->operator[](1));
    EXPECT_EQ("california", stringVectorUT->operator[](2));
    EXPECT_EQ("door", stringVectorUT->operator[](3));
    EXPECT_EQ("extra", stringVectorUT->operator[](4));
    EXPECT_EQ("fail", stringVectorUT->operator[](5));
    EXPECT_EQ("full", stringVectorUT->operator[](6));
    EXPECT_EQ("glad", stringVectorUT->operator[](7));
    EXPECT_EQ("hello", stringVectorUT->operator[](8));
    EXPECT_EQ("igloo", stringVectorUT->operator[](9));
    EXPECT_EQ("joker", stringVectorUT->operator[](10));
    EXPECT_EQ("know", stringVectorUT->operator[](11));
    EXPECT_EQ("later", stringVectorUT->operator[](12));
    EXPECT_EQ("mannequin", stringVectorUT->operator[](13));
    EXPECT_EQ("nugget", stringVectorUT->operator[](14));
    EXPECT_EQ("object", stringVectorUT->operator[](15));
    EXPECT_EQ("oriented", stringVectorUT->operator[](16));
    EXPECT_EQ("programming", stringVectorUT->operator[](17));
    EXPECT_EQ("question", stringVectorUT->operator[](18));
    EXPECT_EQ("restful", stringVectorUT->operator[](19));
    EXPECT_EQ("sleep", stringVectorUT->operator[](20));
    EXPECT_EQ("true", stringVectorUT->operator[](21));
    EXPECT_EQ("under", stringVectorUT->operator[](22));
    EXPECT_EQ("vehicle", stringVectorUT->operator[](23));
    EXPECT_EQ("welcome", stringVectorUT->operator[](24));
    EXPECT_EQ("xeon", stringVectorUT->operator[](25));
    EXPECT_EQ("yellow", stringVectorUT->operator[](26));

    stringVectorUT = new lab2::stringVector();
    stringVectorUT->append("apple");
    stringVectorUT->append("Carousel");
    stringVectorUT->append("Apply");
    stringVectorUT->append("AP");
    stringVectorUT->append("car");
    stringVectorUT->append("Apple");
    stringVectorUT->append("cars");
    stringVectorUT->append("app");


    stringVectorUT->sort();


    EXPECT_EQ("app", stringVectorUT->operator[](0));
    EXPECT_EQ("apple", stringVectorUT->operator[](1));
    EXPECT_EQ("car", stringVectorUT->operator[](2));
    EXPECT_EQ("cars", stringVectorUT->operator[](3));
    EXPECT_EQ("Apple", stringVectorUT->operator[](4));
    EXPECT_EQ("Apply", stringVectorUT->operator[](5));
    EXPECT_EQ("AP", stringVectorUT->operator[](6));
    EXPECT_EQ("Carousel", stringVectorUT->operator[](7));
}