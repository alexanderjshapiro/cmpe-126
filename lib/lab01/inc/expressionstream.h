#ifndef EXPRESSIONSTREAM_H
#define EXPRESSIONSTREAM_H

#include <string>

namespace lab1 {
    class ExpressionStream {
    private:
        std::string buffer;
        std::string::iterator currentPosition;
        std::string::iterator nextPosition;

        void skipWhitespace();
        std::string getNumber();
        bool negative();

    public:
        explicit ExpressionStream(std::string input);

        std::string parseNextToken();
        std::string parseCurrentToken();

        bool nextTokenIsInteger();
        bool nextTokenIsOperator();
        bool nextTokenIsOpenParentheses();
        bool nextTokenIsCloseParentheses();
    };
}

#endif // EXPRESSIONSTREAM_H
