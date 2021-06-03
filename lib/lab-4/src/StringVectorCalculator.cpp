#include "StringVectorCalculator.h"

namespace lab4 {
    bool isNumber(std::string string);

    bool isOperator(const std::string &string);

    bool isParentheses(const std::string &string);

    bool isInvalid(const std::string &token);

    unsigned priorityOf(const std::string &theOperator);

    void StringVectorCalculator::toInfix(std::string &string) {
        infix = lab3::StringVectorQueue();
        lab1::ExpressionStream stream(string);

        // Loop through each token in string until none remain
        std::string token = stream.parseCurrentToken();
        while (!token.empty()) {
            // Ensure token is a number, operator, or parentheses
            if (isInvalid(token)) throw std::runtime_error("token \"" + token + "\" is invalid");

            infix.enqueue(token);
            token = stream.parseNextToken();
        }

        toPostfix(infix);
    }

    void StringVectorCalculator::toPostfix(lab3::StringVectorQueue infixExpression) {
        postfix = lab3::StringVectorQueue();
        // Shunting-yard algorithm
        lab3::StringVectorStack operatorStack;

        // Loop through each element in infix until none remain
        while (!infixExpression.empty()) {
            std::string current = infixExpression.front();
            if (isNumber(current)) {
                postfix.enqueue(current);
            } else if (isOperator(current)) {
                // If top of operator stack has higher priority than current element, pop from stack until it is not so
                while (!operatorStack.empty() && priorityOf(operatorStack.top()) >= priorityOf(current) &&
                       operatorStack.top() != "(") {
                    postfix.enqueue(operatorStack.top());
                    operatorStack.pop();
                }

                operatorStack.push(current);
            } else if (current == "(") {
                operatorStack.push(current);
            } else if (current == ")") {
                // Pop operators from the stack until we find the opening parentheses
                while (operatorStack.top() != "(") {
                    postfix.enqueue(operatorStack.top());
                    operatorStack.pop();

                    // If we run out of elements before finding the opening parentheses, the parentheses are mismatched
                    if (operatorStack.empty()) throw std::runtime_error("mismatched parentheses");
                }

                // Remove ( from the operator stack
                operatorStack.pop();
            }

            // Move on to the next number or operator
            infixExpression.dequeue();
        }

        // Pop remaining operators from stack
        while (!operatorStack.empty()) {
            postfix.enqueue(operatorStack.top());
            operatorStack.pop();
        }
    }

    StringVectorCalculator::StringVectorCalculator() = default;

    StringVectorCalculator::StringVectorCalculator(std::string &string) {
        toInfix(string);
    }

    std::istream &operator>>(std::istream &stream, StringVectorCalculator &RHS) {
        std::string input;
        getline(stream, input);
        RHS.toInfix(input);
        return stream;
    }

    int lab4::StringVectorCalculator::calculate() {
        lab3::StringVectorQueue postfixExpression(postfix);
        lab3::StringVectorStack calculationStack;

        while (!postfixExpression.empty()) {
            std::string current = postfixExpression.front();
            if (isOperator(current)) {
                int second = std::stoi(calculationStack.top());
                calculationStack.pop();
                int first = std::stoi(calculationStack.top());
                calculationStack.pop();

                if (current == "+") {
                    calculationStack.push(std::to_string(first + second));
                } else if (current == "-") {
                    calculationStack.push(std::to_string(first - second));
                } else if (current == "*") {
                    calculationStack.push(std::to_string(first * second));
                } else if (current == "/") {
                    calculationStack.push(std::to_string(first / second));
                }
            } else {
                calculationStack.push(current);
            }
            postfixExpression.dequeue();
        }

        return std::stoi(calculationStack.top());
    }

    std::ostream &operator<<(std::ostream &stream, StringVectorCalculator &calculator) {
        lab3::StringVectorQueue infix(calculator.infix);
        lab3::StringVectorQueue postfix(calculator.postfix);

        stream << std::string("Infix: ");
        while (infix.size() > 1) {
            stream << infix.front() + ",";
            infix.dequeue();
        }
        stream << infix.front() + "\nPostfix: ";

        while (postfix.size() > 1) {
            stream << postfix.front() + ",";
            postfix.dequeue();
        }
        stream << postfix.front();

        return stream;
    }

    bool isNumber(std::string string) {
        return std::all_of(string.begin(), string.end(), [](char c) { return isdigit(c); });
    }

    bool isOperator(const std::string &string) {
        return (string == "+" || string == "-" || string == "*" || string == "/");
    }

    bool isParentheses(const std::string &string) {
        return (string == "(" || string == ")");
    }

    unsigned priorityOf(const std::string &theOperator) {
        if (theOperator == "*" || theOperator == "/") {
            return 2;
        } else if (theOperator == "+" || theOperator == "-") {
            return 1;
        } else {
            return -1;
        }
    }

    bool isInvalid(const std::string &token) {
        return !(isNumber(token) || isOperator(token) || isParentheses(token));
    }
}