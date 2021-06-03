#include "gtest/gtest.h"
#include "StringVectorCalculator.h"

class StringVectorCalculatorTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        stringVectorCalculatorUT = new lab4::StringVectorCalculator;
    }

    virtual void TearDown() {
        delete stringVectorCalculatorUT;
    }

public:
    lab4::StringVectorCalculator *stringVectorCalculatorUT;
    std::string input;
};

TEST(CrashTest, calculator_crashTest) {
    auto *calculatorUT = new lab4::StringVectorCalculator;
    delete calculatorUT;
}

TEST_F(StringVectorCalculatorTest, calculate_expressionsWithSingleOperations_calculatesCorrectAnswer) {
    delete stringVectorCalculatorUT;
    input = "1 + 2";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    EXPECT_EQ(3, stringVectorCalculatorUT->calculate());

    delete stringVectorCalculatorUT;
    input = "3 - 2";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    EXPECT_EQ(1, stringVectorCalculatorUT->calculate());

    delete stringVectorCalculatorUT;
    input = "2 * 3";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    EXPECT_EQ(6, stringVectorCalculatorUT->calculate());

    delete stringVectorCalculatorUT;
    input = "6 / 3";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    EXPECT_EQ(2, stringVectorCalculatorUT->calculate());
}

TEST_F(StringVectorCalculatorTest, calculate_expressionsWithMultipleOperations_calculatesCorrectAnswer) {
    delete stringVectorCalculatorUT;
    input = "1 + 2 + 3";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    EXPECT_EQ(6, stringVectorCalculatorUT->calculate());

    delete stringVectorCalculatorUT;
    input = "1 + 2 + 3 - 4";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    EXPECT_EQ(2, stringVectorCalculatorUT->calculate());

    delete stringVectorCalculatorUT;
    input = "10 * 2 - 3 + 10 / 5";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    EXPECT_EQ(19, stringVectorCalculatorUT->calculate());
}

TEST_F(StringVectorCalculatorTest, calculate_expressionsWithParetheses_calculatesCorrectAnswer) {
    delete stringVectorCalculatorUT;
    input = "( 1 + 2 )";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    EXPECT_EQ(3, stringVectorCalculatorUT->calculate());

    delete stringVectorCalculatorUT;
    input = "( 1 + 2 + 3 )";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    EXPECT_EQ(6, stringVectorCalculatorUT->calculate());

    delete stringVectorCalculatorUT;
    input = "( 1 + 2 ) + 3";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    EXPECT_EQ(6, stringVectorCalculatorUT->calculate());

    delete stringVectorCalculatorUT;
    input = "1 + ( 2 + 3 )";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    EXPECT_EQ(6, stringVectorCalculatorUT->calculate());

    delete stringVectorCalculatorUT;
    input = "8 + 7 * ( 7 - 2 )";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    EXPECT_EQ(43, stringVectorCalculatorUT->calculate());

    delete stringVectorCalculatorUT;
    input = "10 * ( 8 + 5 ) + 7 - 14 + 9";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    EXPECT_EQ(132, stringVectorCalculatorUT->calculate());

    delete stringVectorCalculatorUT;
    input = "49 * ( 17 * ( 3 + 2 * ( 12 + 2 * ( 45 - 43 ) + 2 ) ) + 1 * ( 6 / 2 ) )";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    EXPECT_EQ(32634, stringVectorCalculatorUT->calculate());
}


TEST_F(StringVectorCalculatorTest, insertionAndExtractionOperator_outputsAndInputsInfixAndPostfixExpressions) {
    std::stringstream *stream;

    delete (stringVectorCalculatorUT);
    input = "1 + 2 + 3";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);

    testing::internal::CaptureStdout();
    std::cout << *stringVectorCalculatorUT;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Infix: 1,+,2,+,3\nPostfix: 1,2,+,3,+", output);

    delete (stringVectorCalculatorUT);
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);
    input = "1 + 2 + 3 - 4";
    stream = new std::stringstream(input);
    *stream >> *stringVectorCalculatorUT;

    testing::internal::CaptureStdout();
    std::cout << *stringVectorCalculatorUT;
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Infix: 1,+,2,+,3,-,4\nPostfix: 1,2,+,3,+,4,-", output);

    delete (stringVectorCalculatorUT);
    input = "49 * ( 17 * ( 3 + 2 * ( 12 + 2 * ( 45 - 43 ) + 2 ) ) + 1 * ( 6 / 2 ) )";
    stringVectorCalculatorUT = new lab4::StringVectorCalculator(input);

    testing::internal::CaptureStdout();
    std::cout << *stringVectorCalculatorUT;
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Infix: 49,*,(,17,*,(,3,+,2,*,(,12,+,2,*,(,45,-,43,),+,2,),),+,1,*,(,6,/,2,),)\nPostfix: 49,17,3,2,12,2,45,43,-,*,+,2,+,*,+,*,1,6,2,/,*,+,*", output);
}