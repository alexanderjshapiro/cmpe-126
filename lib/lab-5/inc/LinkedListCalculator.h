#ifndef LINKEDLISTCALCULATOR_H
#define LINKEDLISTCALCULATOR_H

#include "ExpressionStream.h"
#include "LinkedListQueue.h"
#include "LinkedListStack.h"

#include <cmath>

namespace lab5 {
    class LinkedListCalculator {
    private:
        lab5::LinkedListQueue infixExpression;
        lab5::LinkedListQueue postfixExpression;

        void toInfix(std::string &string);
        void toPostfix(lab5::LinkedListQueue infix);

    public:
        LinkedListCalculator() = default;
        explicit LinkedListCalculator(std::string &string);

        int calculate();

        friend std::istream &operator>>(std::istream &stream, LinkedListCalculator &linkedListCalculator);
        friend std::ostream &operator<<(std::ostream &stream, const LinkedListCalculator &linkedListCalculator);
    };
}

#endif // LINKEDLISTCALCULATOR_H