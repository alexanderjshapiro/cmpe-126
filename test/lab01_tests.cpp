#include "gtest/gtest.h"
#include "expressionstream.h"

class ExpressionStreamTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        streamUT1 = new lab1::expressionstream("1+2+3");
        streamUT2 = new lab1::expressionstream("1   + 2 *4+(2*3)");
        streamUT3 = new lab1::expressionstream("-1 +-2");
        streamUT4 = new lab1::expressionstream("-1-(-1-(1--1)-1)-1");
    }

    virtual void TearDown() {
        delete streamUT1;
        delete streamUT2;
        delete streamUT3;
        delete streamUT4;
    }

public:
    lab1::expressionstream *streamUT1, *streamUT2, *streamUT3, *streamUT4;
};

TEST(CrashTest, expressionStream_crashTest) {
    lab1::expressionstream streamUT1("1+2+3");
    lab1::expressionstream streamUT2("1   + 2 *4+(2*3)");
}

TEST_F(ExpressionStreamTest, basicNextToken) {
    //1+2+3
    EXPECT_EQ("1", streamUT1->get_next_token());
    EXPECT_EQ("+", streamUT1->get_next_token());
    EXPECT_EQ("2", streamUT1->get_next_token());
    EXPECT_EQ("+", streamUT1->get_next_token());
    EXPECT_EQ("3", streamUT1->get_next_token());
    EXPECT_EQ("\0", streamUT1->get_next_token());

    //1   + 2 *4+(2*3)
    EXPECT_EQ("1", streamUT2->get_next_token());
    EXPECT_EQ("+", streamUT2->get_next_token());
    EXPECT_EQ("2", streamUT2->get_next_token());
    EXPECT_EQ("*", streamUT2->get_next_token());
    EXPECT_EQ("4", streamUT2->get_next_token());
    EXPECT_EQ("+", streamUT2->get_next_token());
    EXPECT_EQ("(", streamUT2->get_next_token());
    EXPECT_EQ("2", streamUT2->get_next_token());
    EXPECT_EQ("*", streamUT2->get_next_token());
    EXPECT_EQ("3", streamUT2->get_next_token());
    EXPECT_EQ(")", streamUT2->get_next_token());

    //-1 +-2
    EXPECT_EQ("-1", streamUT3->get_next_token());
    EXPECT_EQ("+", streamUT3->get_next_token());
    EXPECT_EQ("-2", streamUT3->get_next_token());

    //-1-(-1-(1--1)-1)-1
    EXPECT_EQ("-1", streamUT4->get_next_token());
    EXPECT_EQ("-", streamUT4->get_next_token());
    EXPECT_EQ("(", streamUT4->get_next_token());
    EXPECT_EQ("-1", streamUT4->get_next_token());
    EXPECT_EQ("-", streamUT4->get_next_token());
    EXPECT_EQ("(", streamUT4->get_next_token());
    EXPECT_EQ("1", streamUT4->get_next_token());
    EXPECT_EQ("-", streamUT4->get_next_token());
    EXPECT_EQ("-1", streamUT4->get_next_token());
    EXPECT_EQ(")", streamUT4->get_next_token());
    EXPECT_EQ("-", streamUT4->get_next_token());
    EXPECT_EQ("1", streamUT4->get_next_token());
    EXPECT_EQ(")", streamUT4->get_next_token());
    EXPECT_EQ("-", streamUT4->get_next_token());
    EXPECT_EQ("1", streamUT4->get_next_token());
}

TEST_F(ExpressionStreamTest, multiDigitNextToken) {
    delete streamUT1;
    delete streamUT2;
    delete streamUT3;
    delete streamUT4;

    streamUT1 = new lab1::expressionstream("123+342+4233");
    streamUT2 = new lab1::expressionstream("134   + 232 *334+(224*533)");
    streamUT3 = new lab1::expressionstream("-781 +-2378");
    streamUT4 = new lab1::expressionstream("-178-(-61-(1--5671)-88671)--13");

    //123+342+4233
    EXPECT_EQ("123", streamUT1->get_next_token());
    EXPECT_EQ("+", streamUT1->get_next_token());
    EXPECT_EQ("342", streamUT1->get_next_token());
    EXPECT_EQ("+", streamUT1->get_next_token());
    EXPECT_EQ("4233", streamUT1->get_next_token());
    EXPECT_EQ("\0", streamUT1->get_next_token());

    //134   + 232 *334+(224*533)
    EXPECT_EQ("134", streamUT2->get_next_token());
    EXPECT_EQ("+", streamUT2->get_next_token());
    EXPECT_EQ("232", streamUT2->get_next_token());
    EXPECT_EQ("*", streamUT2->get_next_token());
    EXPECT_EQ("334", streamUT2->get_next_token());
    EXPECT_EQ("+", streamUT2->get_next_token());
    EXPECT_EQ("(", streamUT2->get_next_token());
    EXPECT_EQ("224", streamUT2->get_next_token());
    EXPECT_EQ("*", streamUT2->get_next_token());
    EXPECT_EQ("533", streamUT2->get_next_token());
    EXPECT_EQ(")", streamUT2->get_next_token());

    //-781 +-2378
    EXPECT_EQ("-781", streamUT3->get_next_token());
    EXPECT_EQ("+", streamUT3->get_next_token());
    EXPECT_EQ("-2378", streamUT3->get_next_token());

    //-178-(-61-(1--5671)-88671)--13
    EXPECT_EQ("-178", streamUT4->get_next_token());
    EXPECT_EQ("-", streamUT4->get_next_token());
    EXPECT_EQ("(", streamUT4->get_next_token());
    EXPECT_EQ("-61", streamUT4->get_next_token());
    EXPECT_EQ("-", streamUT4->get_next_token());
    EXPECT_EQ("(", streamUT4->get_next_token());
    EXPECT_EQ("1", streamUT4->get_next_token());
    EXPECT_EQ("-", streamUT4->get_next_token());
    EXPECT_EQ("-5671", streamUT4->get_next_token());
    EXPECT_EQ(")", streamUT4->get_next_token());
    EXPECT_EQ("-", streamUT4->get_next_token());
    EXPECT_EQ("88671", streamUT4->get_next_token());
    EXPECT_EQ(")", streamUT4->get_next_token());
    EXPECT_EQ("-", streamUT4->get_next_token());
    EXPECT_EQ("-13", streamUT4->get_next_token());
}

TEST_F(ExpressionStreamTest, multiDigitCurrentToken) {
    delete streamUT1;
    delete streamUT2;
    delete streamUT3;
    delete streamUT4;

    streamUT1 = new lab1::expressionstream("123+342+4233");
    streamUT2 = new lab1::expressionstream("134   + 232 *334+(224*533)");
    streamUT3 = new lab1::expressionstream("-781 +-2378");
    streamUT4 = new lab1::expressionstream("-178-(-61-(1--5671)-88671)--13");

    //123+342+4233
    streamUT1->get_next_token();
    EXPECT_EQ("123", streamUT1->get_current_token());
    streamUT1->get_next_token();
    EXPECT_EQ("+", streamUT1->get_current_token());
    streamUT1->get_next_token();
    EXPECT_EQ("342", streamUT1->get_current_token());
    streamUT1->get_next_token();
    EXPECT_EQ("+", streamUT1->get_current_token());
    streamUT1->get_next_token();
    EXPECT_EQ("4233", streamUT1->get_current_token());
    streamUT1->get_next_token();
    EXPECT_EQ("\0", streamUT1->get_current_token());
    streamUT1->get_next_token();

    //134   + 232 *334+(224*533)
    streamUT2->get_next_token();
    EXPECT_EQ("134", streamUT2->get_current_token());
    streamUT2->get_next_token();
    EXPECT_EQ("+", streamUT2->get_current_token());
    streamUT2->get_next_token();
    EXPECT_EQ("232", streamUT2->get_current_token());
    streamUT2->get_next_token();
    EXPECT_EQ("*", streamUT2->get_current_token());
    streamUT2->get_next_token();
    EXPECT_EQ("334", streamUT2->get_current_token());
    streamUT2->get_next_token();
    EXPECT_EQ("+", streamUT2->get_current_token());
    streamUT2->get_next_token();
    EXPECT_EQ("(", streamUT2->get_current_token());
    streamUT2->get_next_token();
    EXPECT_EQ("224", streamUT2->get_current_token());
    streamUT2->get_next_token();
    EXPECT_EQ("*", streamUT2->get_current_token());
    streamUT2->get_next_token();
    EXPECT_EQ("533", streamUT2->get_current_token());
    streamUT2->get_next_token();
    EXPECT_EQ(")", streamUT2->get_current_token());
    streamUT2->get_next_token();

    //-781 +-2378
    streamUT3->get_next_token();
    EXPECT_EQ("-781", streamUT3->get_current_token());
    streamUT3->get_next_token();
    EXPECT_EQ("+", streamUT3->get_current_token());
    streamUT3->get_next_token();
    EXPECT_EQ("-2378", streamUT3->get_current_token());
    streamUT3->get_next_token();

    //-178-(-61-(1--5671)-88671)--13
    streamUT4->get_next_token();
    EXPECT_EQ("-178", streamUT4->get_current_token());
    streamUT4->get_next_token();
    EXPECT_EQ("-", streamUT4->get_current_token());
    streamUT4->get_next_token();
    EXPECT_EQ("(", streamUT4->get_current_token());
    streamUT4->get_next_token();
    EXPECT_EQ("-61", streamUT4->get_current_token());
    streamUT4->get_next_token();
    EXPECT_EQ("-", streamUT4->get_current_token());
    streamUT4->get_next_token();
    EXPECT_EQ("(", streamUT4->get_current_token());
    streamUT4->get_next_token();
    EXPECT_EQ("1", streamUT4->get_current_token());
    streamUT4->get_next_token();
    EXPECT_EQ("-", streamUT4->get_current_token());
    streamUT4->get_next_token();
    EXPECT_EQ("-5671", streamUT4->get_current_token());
    streamUT4->get_next_token();
    EXPECT_EQ(")", streamUT4->get_current_token());
    streamUT4->get_next_token();
    EXPECT_EQ("-", streamUT4->get_current_token());
    streamUT4->get_next_token();
    EXPECT_EQ("88671", streamUT4->get_current_token());
    streamUT4->get_next_token();
    EXPECT_EQ(")", streamUT4->get_current_token());
    streamUT4->get_next_token();
    EXPECT_EQ("-", streamUT4->get_current_token());
    streamUT4->get_next_token();
    EXPECT_EQ("-13", streamUT4->get_current_token());
    streamUT4->get_next_token();
}

TEST_F(ExpressionStreamTest, CheckNextType) {
    EXPECT_TRUE(streamUT1->next_token_is_int());
    EXPECT_FALSE(streamUT1->next_token_is_op());
    EXPECT_FALSE(streamUT1->next_token_is_paren_close());
    EXPECT_FALSE(streamUT1->next_token_is_paren_open());
    EXPECT_TRUE(streamUT1->next_token_is_int());
    streamUT1->get_next_token();

    EXPECT_TRUE(streamUT1->next_token_is_op());
    EXPECT_FALSE(streamUT1->next_token_is_int());
    EXPECT_FALSE(streamUT1->next_token_is_paren_close());
    EXPECT_FALSE(streamUT1->next_token_is_paren_open());
    EXPECT_TRUE(streamUT1->next_token_is_op());
    streamUT1->get_next_token();

    EXPECT_TRUE(streamUT1->next_token_is_int());
    EXPECT_FALSE(streamUT1->next_token_is_op());
    EXPECT_FALSE(streamUT1->next_token_is_paren_close());
    EXPECT_FALSE(streamUT1->next_token_is_paren_open());
    EXPECT_TRUE(streamUT1->next_token_is_int());
    streamUT1->get_next_token();

    EXPECT_TRUE(streamUT1->next_token_is_op());
    EXPECT_FALSE(streamUT1->next_token_is_int());
    EXPECT_FALSE(streamUT1->next_token_is_paren_close());
    EXPECT_FALSE(streamUT1->next_token_is_paren_open());
    EXPECT_TRUE(streamUT1->next_token_is_op());
    streamUT1->get_next_token();

    EXPECT_TRUE(streamUT1->next_token_is_int());
    EXPECT_FALSE(streamUT1->next_token_is_op());
    EXPECT_FALSE(streamUT1->next_token_is_paren_close());
    EXPECT_FALSE(streamUT1->next_token_is_paren_open());
    EXPECT_TRUE(streamUT1->next_token_is_int());
    streamUT1->get_next_token();

    EXPECT_FALSE(streamUT1->next_token_is_int());
    EXPECT_FALSE(streamUT1->next_token_is_op());
    EXPECT_FALSE(streamUT1->next_token_is_paren_close());
    EXPECT_FALSE(streamUT1->next_token_is_paren_open());
    EXPECT_FALSE(streamUT1->next_token_is_int());

    EXPECT_TRUE(streamUT2->next_token_is_int());
    streamUT2->get_next_token();
    EXPECT_TRUE(streamUT2->next_token_is_op());
    streamUT2->get_next_token();
    EXPECT_TRUE(streamUT2->next_token_is_int());
    streamUT2->get_next_token();
    EXPECT_TRUE(streamUT2->next_token_is_op());
    streamUT2->get_next_token();
    EXPECT_TRUE(streamUT2->next_token_is_int());
    streamUT2->get_next_token();
    EXPECT_TRUE(streamUT2->next_token_is_op());
    streamUT2->get_next_token();

    EXPECT_FALSE(streamUT2->next_token_is_int());
    EXPECT_FALSE(streamUT2->next_token_is_op());
    EXPECT_FALSE(streamUT2->next_token_is_paren_close());
    EXPECT_TRUE(streamUT2->next_token_is_paren_open());
    EXPECT_FALSE(streamUT2->next_token_is_int());
    streamUT2->get_next_token();

    EXPECT_TRUE(streamUT2->next_token_is_int());
    streamUT2->get_next_token();
    EXPECT_TRUE(streamUT2->next_token_is_op());
    streamUT2->get_next_token();
    EXPECT_TRUE(streamUT2->next_token_is_int());
    streamUT2->get_next_token();

    EXPECT_FALSE(streamUT2->next_token_is_int());
    EXPECT_FALSE(streamUT2->next_token_is_op());
    EXPECT_TRUE(streamUT2->next_token_is_paren_close());
    EXPECT_FALSE(streamUT2->next_token_is_paren_open());
    EXPECT_FALSE(streamUT2->next_token_is_int());
    streamUT2->get_next_token();

    EXPECT_TRUE(streamUT4->next_token_is_int());
    EXPECT_FALSE(streamUT4->next_token_is_op());
    streamUT4->get_next_token();
    EXPECT_TRUE(streamUT4->next_token_is_op());
    streamUT4->get_next_token();
    EXPECT_TRUE(streamUT4->next_token_is_paren_open());
    EXPECT_FALSE(streamUT4->next_token_is_op());
    streamUT4->get_next_token();
    EXPECT_TRUE(streamUT4->next_token_is_int());
    EXPECT_FALSE(streamUT4->next_token_is_op());
    streamUT4->get_next_token();
    EXPECT_TRUE(streamUT4->next_token_is_op());
    streamUT4->get_next_token();
    EXPECT_TRUE(streamUT4->next_token_is_paren_open());
    EXPECT_FALSE(streamUT4->next_token_is_op());
    streamUT4->get_next_token();
    EXPECT_TRUE(streamUT4->next_token_is_int());
    EXPECT_FALSE(streamUT4->next_token_is_op());
    streamUT4->get_next_token();
    EXPECT_TRUE(streamUT4->next_token_is_op());
    EXPECT_FALSE(streamUT4->next_token_is_int());
    streamUT4->get_next_token();
    EXPECT_TRUE(streamUT4->next_token_is_int());
    EXPECT_FALSE(streamUT4->next_token_is_op());
    streamUT4->get_next_token();
    EXPECT_TRUE(streamUT4->next_token_is_paren_close());
    EXPECT_FALSE(streamUT4->next_token_is_paren_open());
    EXPECT_FALSE(streamUT4->next_token_is_op());
    streamUT4->get_next_token();
    EXPECT_TRUE(streamUT4->next_token_is_op());
    EXPECT_FALSE(streamUT4->next_token_is_int());
    streamUT4->get_next_token();
    EXPECT_TRUE(streamUT4->next_token_is_int());
    EXPECT_FALSE(streamUT4->next_token_is_op());
    streamUT4->get_next_token();
    EXPECT_TRUE(streamUT4->next_token_is_paren_close());
    EXPECT_FALSE(streamUT4->next_token_is_paren_open());
    EXPECT_FALSE(streamUT4->next_token_is_op());
    streamUT4->get_next_token();
    EXPECT_TRUE(streamUT4->next_token_is_op());
    EXPECT_FALSE(streamUT4->next_token_is_int());
    streamUT4->get_next_token();
    EXPECT_TRUE(streamUT4->next_token_is_int());
    EXPECT_FALSE(streamUT4->next_token_is_op());
    streamUT4->get_next_token();
}