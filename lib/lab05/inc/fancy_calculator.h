#ifndef CMPE126S18_LABS_LAB5_CALCULATOR_H
#define CMPE126S18_LABS_LAB5_CALCULATOR_H

#include "stack.h"
#include "queue.h"
#include "expressionstream.h"
#include <iostream>

namespace lab5{
    class calculator{
        lab5::queue infix_expression;
        lab5::queue postfix_expression;

        void parse_to_infix(std::string &input_expression);
        void convert_to_postfix(lab5::queue infix_expression);
    public:
        calculator();
        calculator(std::string &input_expression);
        friend std::istream& operator>>(std::istream& stream, calculator& RHS);

        int calculate();
        friend std::ostream& operator<<(std::ostream& stream, calculator& RHS);
    };
}

#endif