#include "gtest/gtest.h"
#include "calculator.h"
#include <sstream>

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

TEST_F(CalculatorTest, simple) {
    input = "1 + 2 * 3 - 4";
    calculatorUT = new lab4::calculator(input);

    EXPECT_EQ(3, calculatorUT->calculate());
}

TEST_F(CalculatorTest, calc_calculator_simple_test) {
    delete calculatorUT;
    input = "1 + 2 + 3 - 3 - 2 - 1";
    calculatorUT = new lab4::calculator(input);

    EXPECT_EQ(0, calculatorUT->calculate());

    delete calculatorUT;
    input = "1 * 2 * 3 / 3 / 2 / 1";
    calculatorUT = new lab4::calculator(input);

    EXPECT_EQ(1, calculatorUT->calculate());

    delete calculatorUT;
    input = "2 * 3 + 5 - 1";
    calculatorUT = new lab4::calculator(input);

    EXPECT_EQ(10, calculatorUT->calculate());

    delete calculatorUT;
    input = "11 + 22 + 33 - 33 - 22 - 11";
    calculatorUT = new lab4::calculator(input);

    EXPECT_EQ(0, calculatorUT->calculate());

    delete calculatorUT;
    input = "11 * 22 * 33 / 33 / 22 / 11";
    calculatorUT = new lab4::calculator(input);

    EXPECT_EQ(1, calculatorUT->calculate());

    delete calculatorUT;
    input = "2 * 30 + 54 - 1";
    calculatorUT = new lab4::calculator(input);

    EXPECT_EQ(113, calculatorUT->calculate());
}

TEST_F(CalculatorTest, calc_calculator_test) {
    delete calculatorUT;
    input = "271 + 32 * ( 91 - 1 ) + 14 / 2";
    calculatorUT = new lab4::calculator(input);

    EXPECT_EQ(3158, calculatorUT->calculate());

    delete calculatorUT;
    input = "49 * ( 17 * ( 3 + 2 * ( 12 + 2 * ( 45 - 43 ) + 2 ) ) + 1 * ( 6 / 2 ) )";
    calculatorUT = new lab4::calculator(input);

    EXPECT_EQ(32634, calculatorUT->calculate());

    delete calculatorUT;
    input = "( 1 + ( 1 + ( 1 + ( 1 + ( 1 + ( 1 + ( 1 + ( 1 + ( 1 + ( 1 + 1 ) + 1 ) + 1 ) + 1 ) + 1 ) + 1 ) + 1 ) + 1 ) + 1 ) + 1 )";
    calculatorUT = new lab4::calculator(input);

    EXPECT_EQ(20, calculatorUT->calculate());
}


TEST_F(CalculatorTest, calculator_istream_ostream_test) {
    std::stringstream *stream;

    delete (calculatorUT);
    input = "1 + 2 + 3";
    calculatorUT = new lab4::calculator(input);

    testing::internal::CaptureStdout();
    std::cout << *calculatorUT;
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("Infix: 1,+,2,+,3\nPostfix: 1,2,+,3,+", output);

    stream = new std::stringstream(input);
    *stream >> *calculatorUT;

    testing::internal::CaptureStdout();
    std::cout << *calculatorUT;
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("Infix: 1,+,2,+,3\nPostfix: 1,2,+,3,+", output);

    delete (calculatorUT);
    input = "49 * ( 17 * ( 3 + 2 * ( 12 + 2 * ( 45 - 43 ) + 2 ) ) + 1 * ( 6 / 2 ) )";
    calculatorUT = new lab4::calculator(input);

    testing::internal::CaptureStdout();
    std::cout << *calculatorUT;
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(
            "Infix: 49,*,(,17,*,(,3,+,2,*,(,12,+,2,*,(,45,-,43,),+,2,),),+,1,*,(,6,/,2,),)\nPostfix: 49,17,3,2,12,2,45,43,-,*,+,2,+,*,+,*,1,6,2,/,*,+,*",
            output);

    stream = new std::stringstream(input);
    *stream >> *calculatorUT;

    testing::internal::CaptureStdout();
    std::cout << *calculatorUT;
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(
            "Infix: 49,*,(,17,*,(,3,+,2,*,(,12,+,2,*,(,45,-,43,),+,2,),),+,1,*,(,6,/,2,),)\nPostfix: 49,17,3,2,12,2,45,43,-,*,+,2,+,*,+,*,1,6,2,/,*,+,*",
            output);
}