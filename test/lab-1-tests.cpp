#include "gtest/gtest.h"
#include "ExpressionStream.h"

class ExpressionStreamTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        streamUT1 = new lab1::ExpressionStream("1+2+3");
        streamUT2 = new lab1::ExpressionStream("1   + 2 *4+(2*3)");
        streamUT3 = new lab1::ExpressionStream("-1 +-2");
        streamUT4 = new lab1::ExpressionStream("-1-(-1-(1--1)-1)-1");
    }

    virtual void TearDown() {
        delete streamUT1;
        delete streamUT2;
        delete streamUT3;
        delete streamUT4;
    }

public:
    lab1::ExpressionStream *streamUT1, *streamUT2, *streamUT3, *streamUT4;
};

TEST(CrashTest, expressionStream_crashTest) {
    lab1::ExpressionStream streamUT1("2 + 2");
}

TEST_F(ExpressionStreamTest, basicNextToken) {
    //1+2+3
    EXPECT_EQ("1", streamUT1->parseNextToken());
    EXPECT_EQ("+", streamUT1->parseNextToken());
    EXPECT_EQ("2", streamUT1->parseNextToken());
    EXPECT_EQ("+", streamUT1->parseNextToken());
    EXPECT_EQ("3", streamUT1->parseNextToken());
    EXPECT_EQ("\0", streamUT1->parseNextToken());

    //1   + 2 *4+(2*3)
    EXPECT_EQ("1", streamUT2->parseNextToken());
    EXPECT_EQ("+", streamUT2->parseNextToken());
    EXPECT_EQ("2", streamUT2->parseNextToken());
    EXPECT_EQ("*", streamUT2->parseNextToken());
    EXPECT_EQ("4", streamUT2->parseNextToken());
    EXPECT_EQ("+", streamUT2->parseNextToken());
    EXPECT_EQ("(", streamUT2->parseNextToken());
    EXPECT_EQ("2", streamUT2->parseNextToken());
    EXPECT_EQ("*", streamUT2->parseNextToken());
    EXPECT_EQ("3", streamUT2->parseNextToken());
    EXPECT_EQ(")", streamUT2->parseNextToken());

    //-1 +-2
    EXPECT_EQ("-1", streamUT3->parseNextToken());
    EXPECT_EQ("+", streamUT3->parseNextToken());
    EXPECT_EQ("-2", streamUT3->parseNextToken());

    //-1-(-1-(1--1)-1)-1
    EXPECT_EQ("-1", streamUT4->parseNextToken());
    EXPECT_EQ("-", streamUT4->parseNextToken());
    EXPECT_EQ("(", streamUT4->parseNextToken());
    EXPECT_EQ("-1", streamUT4->parseNextToken());
    EXPECT_EQ("-", streamUT4->parseNextToken());
    EXPECT_EQ("(", streamUT4->parseNextToken());
    EXPECT_EQ("1", streamUT4->parseNextToken());
    EXPECT_EQ("-", streamUT4->parseNextToken());
    EXPECT_EQ("-1", streamUT4->parseNextToken());
    EXPECT_EQ(")", streamUT4->parseNextToken());
    EXPECT_EQ("-", streamUT4->parseNextToken());
    EXPECT_EQ("1", streamUT4->parseNextToken());
    EXPECT_EQ(")", streamUT4->parseNextToken());
    EXPECT_EQ("-", streamUT4->parseNextToken());
    EXPECT_EQ("1", streamUT4->parseNextToken());
}

TEST_F(ExpressionStreamTest, multiDigitNextToken) {
    delete streamUT1;
    delete streamUT2;
    delete streamUT3;
    delete streamUT4;

    streamUT1 = new lab1::ExpressionStream("123+342+4233");
    streamUT2 = new lab1::ExpressionStream("134   + 232 *334+(224*533)");
    streamUT3 = new lab1::ExpressionStream("-781 +-2378");
    streamUT4 = new lab1::ExpressionStream("-178-(-61-(1--5671)-88671)--13");

    //123+342+4233
    EXPECT_EQ("123", streamUT1->parseNextToken());
    EXPECT_EQ("+", streamUT1->parseNextToken());
    EXPECT_EQ("342", streamUT1->parseNextToken());
    EXPECT_EQ("+", streamUT1->parseNextToken());
    EXPECT_EQ("4233", streamUT1->parseNextToken());
    EXPECT_EQ("\0", streamUT1->parseNextToken());

    //134   + 232 *334+(224*533)
    EXPECT_EQ("134", streamUT2->parseNextToken());
    EXPECT_EQ("+", streamUT2->parseNextToken());
    EXPECT_EQ("232", streamUT2->parseNextToken());
    EXPECT_EQ("*", streamUT2->parseNextToken());
    EXPECT_EQ("334", streamUT2->parseNextToken());
    EXPECT_EQ("+", streamUT2->parseNextToken());
    EXPECT_EQ("(", streamUT2->parseNextToken());
    EXPECT_EQ("224", streamUT2->parseNextToken());
    EXPECT_EQ("*", streamUT2->parseNextToken());
    EXPECT_EQ("533", streamUT2->parseNextToken());
    EXPECT_EQ(")", streamUT2->parseNextToken());

    //-781 +-2378
    EXPECT_EQ("-781", streamUT3->parseNextToken());
    EXPECT_EQ("+", streamUT3->parseNextToken());
    EXPECT_EQ("-2378", streamUT3->parseNextToken());

    //-178-(-61-(1--5671)-88671)--13
    EXPECT_EQ("-178", streamUT4->parseNextToken());
    EXPECT_EQ("-", streamUT4->parseNextToken());
    EXPECT_EQ("(", streamUT4->parseNextToken());
    EXPECT_EQ("-61", streamUT4->parseNextToken());
    EXPECT_EQ("-", streamUT4->parseNextToken());
    EXPECT_EQ("(", streamUT4->parseNextToken());
    EXPECT_EQ("1", streamUT4->parseNextToken());
    EXPECT_EQ("-", streamUT4->parseNextToken());
    EXPECT_EQ("-5671", streamUT4->parseNextToken());
    EXPECT_EQ(")", streamUT4->parseNextToken());
    EXPECT_EQ("-", streamUT4->parseNextToken());
    EXPECT_EQ("88671", streamUT4->parseNextToken());
    EXPECT_EQ(")", streamUT4->parseNextToken());
    EXPECT_EQ("-", streamUT4->parseNextToken());
    EXPECT_EQ("-13", streamUT4->parseNextToken());
}

TEST_F(ExpressionStreamTest, multiDigitCurrentToken) {
    delete streamUT1;
    delete streamUT2;
    delete streamUT3;
    delete streamUT4;

    streamUT1 = new lab1::ExpressionStream("123+342+4233");
    streamUT2 = new lab1::ExpressionStream("134   + 232 *334+(224*533)");
    streamUT3 = new lab1::ExpressionStream("-781 +-2378");
    streamUT4 = new lab1::ExpressionStream("-178-(-61-(1--5671)-88671)--13");

    //123+342+4233
    streamUT1->parseNextToken();
    EXPECT_EQ("123", streamUT1->parseCurrentToken());
    streamUT1->parseNextToken();
    EXPECT_EQ("+", streamUT1->parseCurrentToken());
    streamUT1->parseNextToken();
    EXPECT_EQ("342", streamUT1->parseCurrentToken());
    streamUT1->parseNextToken();
    EXPECT_EQ("+", streamUT1->parseCurrentToken());
    streamUT1->parseNextToken();
    EXPECT_EQ("4233", streamUT1->parseCurrentToken());
    streamUT1->parseNextToken();
    EXPECT_EQ("\0", streamUT1->parseCurrentToken());
    streamUT1->parseNextToken();

    //134   + 232 *334+(224*533)
    streamUT2->parseNextToken();
    EXPECT_EQ("134", streamUT2->parseCurrentToken());
    streamUT2->parseNextToken();
    EXPECT_EQ("+", streamUT2->parseCurrentToken());
    streamUT2->parseNextToken();
    EXPECT_EQ("232", streamUT2->parseCurrentToken());
    streamUT2->parseNextToken();
    EXPECT_EQ("*", streamUT2->parseCurrentToken());
    streamUT2->parseNextToken();
    EXPECT_EQ("334", streamUT2->parseCurrentToken());
    streamUT2->parseNextToken();
    EXPECT_EQ("+", streamUT2->parseCurrentToken());
    streamUT2->parseNextToken();
    EXPECT_EQ("(", streamUT2->parseCurrentToken());
    streamUT2->parseNextToken();
    EXPECT_EQ("224", streamUT2->parseCurrentToken());
    streamUT2->parseNextToken();
    EXPECT_EQ("*", streamUT2->parseCurrentToken());
    streamUT2->parseNextToken();
    EXPECT_EQ("533", streamUT2->parseCurrentToken());
    streamUT2->parseNextToken();
    EXPECT_EQ(")", streamUT2->parseCurrentToken());
    streamUT2->parseNextToken();

    //-781 +-2378
    streamUT3->parseNextToken();
    EXPECT_EQ("-781", streamUT3->parseCurrentToken());
    streamUT3->parseNextToken();
    EXPECT_EQ("+", streamUT3->parseCurrentToken());
    streamUT3->parseNextToken();
    EXPECT_EQ("-2378", streamUT3->parseCurrentToken());
    streamUT3->parseNextToken();

    //-178-(-61-(1--5671)-88671)--13
    streamUT4->parseNextToken();
    EXPECT_EQ("-178", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
    EXPECT_EQ("-", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
    EXPECT_EQ("(", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
    EXPECT_EQ("-61", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
    EXPECT_EQ("-", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
    EXPECT_EQ("(", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
    EXPECT_EQ("1", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
    EXPECT_EQ("-", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
    EXPECT_EQ("-5671", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
    EXPECT_EQ(")", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
    EXPECT_EQ("-", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
    EXPECT_EQ("88671", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
    EXPECT_EQ(")", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
    EXPECT_EQ("-", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
    EXPECT_EQ("-13", streamUT4->parseCurrentToken());
    streamUT4->parseNextToken();
}

TEST_F(ExpressionStreamTest, CheckNextType) {
    EXPECT_TRUE(streamUT1->nextTokenIsInteger());
    EXPECT_FALSE(streamUT1->nextTokenIsOperator());
    EXPECT_FALSE(streamUT1->nextTokenIsCloseParentheses());
    EXPECT_FALSE(streamUT1->nextTokenIsOpenParentheses());
    EXPECT_TRUE(streamUT1->nextTokenIsInteger());
    streamUT1->parseNextToken();

    EXPECT_TRUE(streamUT1->nextTokenIsOperator());
    EXPECT_FALSE(streamUT1->nextTokenIsInteger());
    EXPECT_FALSE(streamUT1->nextTokenIsCloseParentheses());
    EXPECT_FALSE(streamUT1->nextTokenIsOpenParentheses());
    EXPECT_TRUE(streamUT1->nextTokenIsOperator());
    streamUT1->parseNextToken();

    EXPECT_TRUE(streamUT1->nextTokenIsInteger());
    EXPECT_FALSE(streamUT1->nextTokenIsOperator());
    EXPECT_FALSE(streamUT1->nextTokenIsCloseParentheses());
    EXPECT_FALSE(streamUT1->nextTokenIsOpenParentheses());
    EXPECT_TRUE(streamUT1->nextTokenIsInteger());
    streamUT1->parseNextToken();

    EXPECT_TRUE(streamUT1->nextTokenIsOperator());
    EXPECT_FALSE(streamUT1->nextTokenIsInteger());
    EXPECT_FALSE(streamUT1->nextTokenIsCloseParentheses());
    EXPECT_FALSE(streamUT1->nextTokenIsOpenParentheses());
    EXPECT_TRUE(streamUT1->nextTokenIsOperator());
    streamUT1->parseNextToken();

    EXPECT_TRUE(streamUT1->nextTokenIsInteger());
    EXPECT_FALSE(streamUT1->nextTokenIsOperator());
    EXPECT_FALSE(streamUT1->nextTokenIsCloseParentheses());
    EXPECT_FALSE(streamUT1->nextTokenIsOpenParentheses());
    EXPECT_TRUE(streamUT1->nextTokenIsInteger());
    streamUT1->parseNextToken();

    EXPECT_FALSE(streamUT1->nextTokenIsInteger());
    EXPECT_FALSE(streamUT1->nextTokenIsOperator());
    EXPECT_FALSE(streamUT1->nextTokenIsCloseParentheses());
    EXPECT_FALSE(streamUT1->nextTokenIsOpenParentheses());
    EXPECT_FALSE(streamUT1->nextTokenIsInteger());

    EXPECT_TRUE(streamUT2->nextTokenIsInteger());
    streamUT2->parseNextToken();
    EXPECT_TRUE(streamUT2->nextTokenIsOperator());
    streamUT2->parseNextToken();
    EXPECT_TRUE(streamUT2->nextTokenIsInteger());
    streamUT2->parseNextToken();
    EXPECT_TRUE(streamUT2->nextTokenIsOperator());
    streamUT2->parseNextToken();
    EXPECT_TRUE(streamUT2->nextTokenIsInteger());
    streamUT2->parseNextToken();
    EXPECT_TRUE(streamUT2->nextTokenIsOperator());
    streamUT2->parseNextToken();

    EXPECT_FALSE(streamUT2->nextTokenIsInteger());
    EXPECT_FALSE(streamUT2->nextTokenIsOperator());
    EXPECT_FALSE(streamUT2->nextTokenIsCloseParentheses());
    EXPECT_TRUE(streamUT2->nextTokenIsOpenParentheses());
    EXPECT_FALSE(streamUT2->nextTokenIsInteger());
    streamUT2->parseNextToken();

    EXPECT_TRUE(streamUT2->nextTokenIsInteger());
    streamUT2->parseNextToken();
    EXPECT_TRUE(streamUT2->nextTokenIsOperator());
    streamUT2->parseNextToken();
    EXPECT_TRUE(streamUT2->nextTokenIsInteger());
    streamUT2->parseNextToken();

    EXPECT_FALSE(streamUT2->nextTokenIsInteger());
    EXPECT_FALSE(streamUT2->nextTokenIsOperator());
    EXPECT_TRUE(streamUT2->nextTokenIsCloseParentheses());
    EXPECT_FALSE(streamUT2->nextTokenIsOpenParentheses());
    EXPECT_FALSE(streamUT2->nextTokenIsInteger());
    streamUT2->parseNextToken();

    EXPECT_TRUE(streamUT4->nextTokenIsInteger());
    EXPECT_FALSE(streamUT4->nextTokenIsOperator());
    streamUT4->parseNextToken();
    EXPECT_TRUE(streamUT4->nextTokenIsOperator());
    streamUT4->parseNextToken();
    EXPECT_TRUE(streamUT4->nextTokenIsOpenParentheses());
    EXPECT_FALSE(streamUT4->nextTokenIsOperator());
    streamUT4->parseNextToken();
    EXPECT_TRUE(streamUT4->nextTokenIsInteger());
    EXPECT_FALSE(streamUT4->nextTokenIsOperator());
    streamUT4->parseNextToken();
    EXPECT_TRUE(streamUT4->nextTokenIsOperator());
    streamUT4->parseNextToken();
    EXPECT_TRUE(streamUT4->nextTokenIsOpenParentheses());
    EXPECT_FALSE(streamUT4->nextTokenIsOperator());
    streamUT4->parseNextToken();
    EXPECT_TRUE(streamUT4->nextTokenIsInteger());
    EXPECT_FALSE(streamUT4->nextTokenIsOperator());
    streamUT4->parseNextToken();
    EXPECT_TRUE(streamUT4->nextTokenIsOperator());
    EXPECT_FALSE(streamUT4->nextTokenIsInteger());
    streamUT4->parseNextToken();
    EXPECT_TRUE(streamUT4->nextTokenIsInteger());
    EXPECT_FALSE(streamUT4->nextTokenIsOperator());
    streamUT4->parseNextToken();
    EXPECT_TRUE(streamUT4->nextTokenIsCloseParentheses());
    EXPECT_FALSE(streamUT4->nextTokenIsOpenParentheses());
    EXPECT_FALSE(streamUT4->nextTokenIsOperator());
    streamUT4->parseNextToken();
    EXPECT_TRUE(streamUT4->nextTokenIsOperator());
    EXPECT_FALSE(streamUT4->nextTokenIsInteger());
    streamUT4->parseNextToken();
    EXPECT_TRUE(streamUT4->nextTokenIsInteger());
    EXPECT_FALSE(streamUT4->nextTokenIsOperator());
    streamUT4->parseNextToken();
    EXPECT_TRUE(streamUT4->nextTokenIsCloseParentheses());
    EXPECT_FALSE(streamUT4->nextTokenIsOpenParentheses());
    EXPECT_FALSE(streamUT4->nextTokenIsOperator());
    streamUT4->parseNextToken();
    EXPECT_TRUE(streamUT4->nextTokenIsOperator());
    EXPECT_FALSE(streamUT4->nextTokenIsInteger());
    streamUT4->parseNextToken();
    EXPECT_TRUE(streamUT4->nextTokenIsInteger());
    EXPECT_FALSE(streamUT4->nextTokenIsOperator());
    streamUT4->parseNextToken();
}