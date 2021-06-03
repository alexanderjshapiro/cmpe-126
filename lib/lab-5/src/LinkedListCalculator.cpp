#include "LinkedListCalculator.h"

namespace lab5 {
    bool isNumber(std::string string);
    bool isOperator(const std::string &string);
    bool isParentheses(const std::string &string);
    bool isInvalid(const std::string &token);
    unsigned priorityOf(const std::string &theOperator);

    void LinkedListCalculator::toInfix(std::string &string) {
        infixExpression = lab5::LinkedListQueue();

        lab1::ExpressionStream stream(string);

        // Loop through each token in string until none remain
        std::string token = stream.parseCurrentToken();
        while (!token.empty()) {
            // Ensure token is a number, operator, or parentheses
            if (isInvalid(token)) throw std::runtime_error("token \"" + token + "\" is invalid");

            infixExpression.enqueue(token);
            token = stream.parseNextToken();
        }

        toPostfix(infixExpression);
    }

    void LinkedListCalculator::toPostfix(lab5::LinkedListQueue infix) {
        postfixExpression = lab5::LinkedListQueue();

        lab5::LinkedListStack operatorStack;

        // Loop through each element in infix until none remain
        while (!infix.empty()) {
            std::string current = infix.top();
            if (isNumber(current)) {
                postfixExpression.enqueue(current);
            } else if (isOperator(current)) {
                // If top of operator stack has higher priority than current element, pop from stack until it is not so
                while (!operatorStack.empty() && priorityOf(operatorStack.top()) >= priorityOf(current) &&
                       operatorStack.top() != "(") {
                    postfixExpression.enqueue(operatorStack.top());
                    operatorStack.pop();
                }

                operatorStack.push(current);
            } else if (current == "(") {
                operatorStack.push(current);
            } else if (current == ")") {
                // Pop operators from the stack until we find the opening parentheses
                while (operatorStack.top() != "(") {
                    postfixExpression.enqueue(operatorStack.top());
                    operatorStack.pop();

                    // If we run out of elements before finding the opening parentheses, the parentheses are mismatched
                    if (operatorStack.empty()) throw std::runtime_error("mismatched parentheses");
                }

                // Remove ( from the operator stack
                operatorStack.pop();
            }

            // Move on to the next number or operator
            infix.dequeue();
        }

        // Pop remaining operators from stack
        while (!operatorStack.empty()) {
            postfixExpression.enqueue(operatorStack.top());
            operatorStack.pop();
        }
    }

    LinkedListCalculator::LinkedListCalculator(std::string &string) {
        toInfix(string);
    }

    int LinkedListCalculator::calculate() {
        lab5::LinkedListQueue postfix(postfixExpression);
        lab5::LinkedListStack calculationStack;

        while (!postfix.empty()) {
            std::string current = postfix.top();
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
                } else if (current == "%") {
                    calculationStack.push(std::to_string(first % second));
                } else if (current == "^") {
                    calculationStack.push(std::to_string(pow(first, second)));
                }
            } else {
                calculationStack.push(current);
            }
            postfix.dequeue();
        }

        return std::stoi(calculationStack.top());
    }

    std::istream &operator>>(std::istream &stream, LinkedListCalculator &linkedListCalculator) {
        std::string input;
        getline(stream, input);
        linkedListCalculator.toInfix(input);
        return stream;
    }

    std::ostream &operator<<(std::ostream &stream, const LinkedListCalculator &linkedListCalculator) {
        lab5::LinkedListQueue infix(linkedListCalculator.infixExpression);
        lab5::LinkedListQueue postfix(linkedListCalculator.postfixExpression);

        stream << std::string("Infix: ");
        while (infix.size() > 1) {
            stream << infix.top() + ",";
            infix.dequeue();
        }
        stream << infix.top() + "\nPostfix: ";

        while (postfix.size() > 1) {
            stream << postfix.top() + ",";
            postfix.dequeue();
        }
        stream << postfix.top();

        return stream;
    }

    bool isNumber(std::string string) {
        return std::all_of(string.begin(), string.end(), [](char c) { return isdigit(c); });
    }

    bool isOperator(const std::string &string) {
        return (string == "+" || string == "-" || string == "*" || string == "/" || string == "%" || string == "^");
    }

    bool isParentheses(const std::string &string) {
        return (string == "(" || string == ")");
    }

    unsigned priorityOf(const std::string &theOperator) {
        if (theOperator == "^") {
            return 3;
        } else if (theOperator == "*" || theOperator == "/" || theOperator == "%") {
            return 2;
        } else if (theOperator == "+" || theOperator == "-") {
            return 1;
        } else {
            return 0;
        }
    }

    bool isInvalid(const std::string &token) {
        return !(isNumber(token) || isOperator(token) || isParentheses(token));
    }
}