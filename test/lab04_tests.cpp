#include "gtest/gtest.h"
#include "calculator.h"

class CalculatorTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        calculatorUT = new lab4::calculator;
    }

    virtual void TearDown() {
        delete calculatorUT;
    }

public:
    lab4::calculator *calculatorUT;
    std::string input;
};

TEST(CrashTest, calculator_crashTest) {
    auto *calculatorUT = new lab4::calculator;
    delete calculatorUT;
}

TEST_F(CalculatorTest, calculate_expressionsWithSingleOperations_calculatesCorrectAnswer) {
    delete calculatorUT;
    input = "1 + 2";
    calculatorUT = new lab4::calculator(input);
    EXPECT_EQ(3, calculatorUT->calculate());

    delete calculatorUT;
    input = "3 - 2";
    calculatorUT = new lab4::calculator(input);
    EXPECT_EQ(1, calculatorUT->calculate());

    delete calculatorUT;
    input = "2 * 3";
    calculatorUT = new lab4::calculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "6 / 3";
    calculatorUT = new lab4::calculator(input);
    EXPECT_EQ(2, calculatorUT->calculate());
}

TEST_F(CalculatorTest, calculate_expressionsWithMultipleOperations_calculatesCorrectAnswer) {
    delete calculatorUT;
    input = "1 + 2 + 3";
    calculatorUT = new lab4::calculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "1 + 2 + 3 - 4";
    calculatorUT = new lab4::calculator(input);
    EXPECT_EQ(2, calculatorUT->calculate());

    delete calculatorUT;
    input = "10 * 2 - 3 + 10 / 5";
    calculatorUT = new lab4::calculator(input);
    EXPECT_EQ(19, calculatorUT->calculate());
}

TEST_F(CalculatorTest, calculate_expressionsWithParetheses_calculatesCorrectAnswer) {
    delete calculatorUT;
    input = "( 1 + 2 )";
    calculatorUT = new lab4::calculator(input);
    EXPECT_EQ(3, calculatorUT->calculate());

    delete calculatorUT;
    input = "( 1 + 2 + 3 )";
    calculatorUT = new lab4::calculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "( 1 + 2 ) + 3";
    calculatorUT = new lab4::calculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "1 + ( 2 + 3 )";
    calculatorUT = new lab4::calculator(input);
    EXPECT_EQ(6, calculatorUT->calculate());

    delete calculatorUT;
    input = "8 + 7 * ( 7 - 2 )";
    calculatorUT = new lab4::calculator(input);
    EXPECT_EQ(43, calculatorUT->calculate());

    delete calculatorUT;
    input = "10 * ( 8 + 5 ) + 7 - 14 + 9";
    calculatorUT = new lab4::calculator(input);
    EXPECT_EQ(132, calculatorUT->calculate());

    delete calculatorUT;
    input = "49 * ( 17 * ( 3 + 2 * ( 12 + 2 * ( 45 - 43 ) + 2 ) ) + 1 * ( 6 / 2 ) )";
    calculatorUT = new lab4::calculator(input);
    EXPECT_EQ(32634, calculatorUT->calculate());
}


TEST_F(CalculatorTest, insertionAndExtractionOperator_outputsAndInputsInfixAndPostfixExpressions) {
    std::stringstream *stream;

    delete (calculatorUT);
    input = "1 + 2 + 3";
    calculatorUT = new lab4::calculator(input);

    testing::internal::CaptureStdout();
    std::cout << *calculatorUT;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Infix: 1,+,2,+,3\nPostfix: 1,2,+,3,+", output);

    delete (calculatorUT);
    calculatorUT = new lab4::calculator(input);
    input = "1 + 2 + 3 - 4";
    stream = new std::stringstream(input);
    *stream >> *calculatorUT;

    testing::internal::CaptureStdout();
    std::cout << *calculatorUT;
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Infix: 1,+,2,+,3,-,4\nPostfix: 1,2,+,3,+,4,-", output);

    delete (calculatorUT);
    input = "49 * ( 17 * ( 3 + 2 * ( 12 + 2 * ( 45 - 43 ) + 2 ) ) + 1 * ( 6 / 2 ) )";
    calculatorUT = new lab4::calculator(input);

    testing::internal::CaptureStdout();
    std::cout << *calculatorUT;
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Infix: 49,*,(,17,*,(,3,+,2,*,(,12,+,2,*,(,45,-,43,),+,2,),),+,1,*,(,6,/,2,),)\nPostfix: 49,17,3,2,12,2,45,43,-,*,+,2,+,*,+,*,1,6,2,/,*,+,*", output);
}