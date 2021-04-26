#include <cmath>
#include "fancy_calculator.h"
#include "stack.h"
#include "queue.h"

namespace lab5 {
    bool isNumber(std::string string);

    bool isOperator(const std::string &string);

    bool isParentheses(const std::string &string);

    bool isInvalid(const std::string &token);

    unsigned priorityOf(const std::string &theOperator);

    void calculator::parse_to_infix(std::string &input_expression) {
        infix_expression = lab5::queue();

        lab1::expressionstream stream(input_expression);

        // Loop through each token in input_expression until none remain
        std::string token = stream.get_current_token();
        while (!token.empty()) {
            // Ensure token is a number, operator, or parentheses
            if (isInvalid(token)) throw std::runtime_error("token \"" + token + "\" is invalid");

            infix_expression.enqueue(token);
            token = stream.get_next_token();
        }

        convert_to_postfix(infix_expression);
    }

    void calculator::convert_to_postfix(lab5::queue infix_expression) {
        postfix_expression = lab5::queue();

        lab5::stack operatorStack;

        // Loop through each element in infix_expression until none remain
        while (!infix_expression.isEmpty()) {
            std::string current = infix_expression.top();
            if (isNumber(current)) {
                postfix_expression.enqueue(current);
            } else if (isOperator(current)) {
                // If top of operator stack has higher priority than current element, pop from stack until it is not so
                while (!operatorStack.isEmpty() && priorityOf(operatorStack.top()) >= priorityOf(current) &&
                       operatorStack.top() != "(") {
                    postfix_expression.enqueue(operatorStack.top());
                    operatorStack.pop();
                }

                operatorStack.push(current);
            } else if (current == "(") {
                operatorStack.push(current);
            } else if (current == ")") {
                // Pop operators from the stack until we find the opening parentheses
                while (operatorStack.top() != "(") {
                    postfix_expression.enqueue(operatorStack.top());
                    operatorStack.pop();

                    // If we run out of elements before finding the opening parentheses, the parentheses are mismatched
                    if (operatorStack.isEmpty()) throw std::runtime_error("mismatched parentheses");
                }

                // Remove ( from the operator stack
                operatorStack.pop();
            }

            // Move on to the next number or operator
            infix_expression.dequeue();
        }

        // Pop remaining operators from stack
        while (!operatorStack.isEmpty()) {
            postfix_expression.enqueue(operatorStack.top());
            operatorStack.pop();
        }
    }

    calculator::calculator() = default;

    calculator::calculator(std::string &input_expression) {
        parse_to_infix(input_expression);
    }

    std::istream &operator>>(std::istream &stream, calculator &RHS) {
        std::string input = "";
        getline(stream, input);
        RHS.parse_to_infix(input);
        return stream;
    }

    int calculator::calculate() {
        lab5::queue postfix(postfix_expression);
        lab5::stack calculationStack;

        while (!postfix.isEmpty()) {
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

    std::ostream &operator<<(std::ostream &stream, calculator &RHS) {
        lab5::queue infix(RHS.infix_expression);
        lab5::queue postfix(RHS.postfix_expression);

        stream << std::string("Infix: ");
        while (infix.queueSize() > 1) {
            stream << infix.top() + ",";
            infix.dequeue();
        }
        stream << infix.top() + "\nPostfix: ";

        while (postfix.queueSize() > 1) {
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