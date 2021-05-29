#include "ExpressionStream.h"

namespace lab1 {
    ExpressionStream::ExpressionStream(std::string input) : buffer(std::move(input)) {
        currentPosition = buffer.begin();
        nextPosition = currentPosition;

        // Remove leading whitespace
        skipWhitespace();
    }

    void ExpressionStream::skipWhitespace() {
        while (*currentPosition == ' ' && currentPosition < buffer.end()) currentPosition++;
        while (*nextPosition == ' ' && nextPosition < buffer.end()) nextPosition++;
    }

    std::string ExpressionStream::getNumber() {
        bool isNegative = *currentPosition == '-';

        // Find start of number
        std::string::iterator numberStart = currentPosition;
        while (numberStart < buffer.end() && !std::isdigit(*numberStart)) numberStart++;

        // Find end of number
        nextPosition = numberStart;
        while (nextPosition < buffer.end() && std::isdigit(*nextPosition)) nextPosition++;

        // Reconstruct number with proper formatting
        return (isNegative ? "-" : "") + std::string(numberStart, nextPosition);
    }

    bool ExpressionStream::negative() {
        // Check if negative number or minus by checking if previous token is a number
        std::string::iterator negativeCheck = nextPosition - 1;
        while (negativeCheck > buffer.begin() && *negativeCheck == ' ') negativeCheck--;
        return (!std::isdigit(*negativeCheck) && *negativeCheck != ')');
    }

    std::string ExpressionStream::parseNextToken() {
        currentPosition = nextPosition;
        return parseCurrentToken();
    }

    std::string ExpressionStream::parseCurrentToken() {
        skipWhitespace();

        if (currentPosition >= buffer.end()) return std::string();

        nextPosition = currentPosition;
        if (nextTokenIsInteger()) return getNumber();
        else return std::string(currentPosition, ++nextPosition);
    }

    bool ExpressionStream::nextTokenIsInteger() {
        skipWhitespace();
        if (std::isdigit(*nextPosition)) return true;
        else if (*nextPosition == '-') return negative();
        else return false;
    }

    bool ExpressionStream::nextTokenIsOperator() {
        skipWhitespace();

        // Avoid viewing a negative number as a minus operator
        if (nextTokenIsInteger()) return false;

        return (*nextPosition == '+' || *nextPosition == '-' || *nextPosition == '*' || *nextPosition == '/');
    }

    bool ExpressionStream::nextTokenIsOpenParentheses() {
        skipWhitespace();
        return *nextPosition == '(';
    }

    bool ExpressionStream::nextTokenIsCloseParentheses() {
        skipWhitespace();
        return *nextPosition == ')';
    }
}