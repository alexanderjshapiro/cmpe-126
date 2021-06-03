#ifndef STRINGVECTORCALCULATOR_H
#define STRINGVECTORCALCULATOR_H

#include "ExpressionStream.h"
#include "StringVectorStack.h"
#include "StringVectorQueue.h"

#include <iostream>

namespace lab4 {
    class StringVectorCalculator {
    private:
        lab3::StringVectorQueue infix;
        lab3::StringVectorQueue postfix;

        void toInfix(std::string &string);
        void toPostfix(lab3::StringVectorQueue infixExpression);

    public:
        StringVectorCalculator();
        explicit StringVectorCalculator(std::string &string);

        int calculate();

        friend std::istream &operator>>(std::istream &stream, StringVectorCalculator &calculator);
        friend std::ostream &operator<<(std::ostream &stream, StringVectorCalculator &calculator);
    };
}

#endif // STRINGVECTORCALCULATOR_H