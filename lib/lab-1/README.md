# Lab 1: Parsing Tokens

## `ExpressionStream`

`ExpressionStream` parses a string which contains a mathematical expression. It removes extraneous whitespace and parses
the expression one token at a time. A token is either a number or a mathematical operator. It is assumed that the raw
expression is mathematically valid but unformatted.

### private:

- `buffer` holds the raw expression

- `currentPosition` and `nextPosition` delimit a token

- `skipWhitespace()` skips whitespace between before a token

- `getNumber()` parses a token as an integer

- `negative()` determines if a token is a negative number or a minus sign

### public:

- `ExpressionStream(std::string)` loads the raw expression into `buffer` and starts `currentPosition` and `nextPosition`
  at the beginning of `buffer`

- `parseNextToken()` parses the next token

- `parseCurrentToken()` parses the current token

- `nextTokenIsInteger()` determines if the next token is an integer

- `nextTokenIsOperator()` determines if the next token is an operator

- `nextTokenIsOpenParenthesis()` determines if the next token is an open parenthesis

- `nextTokenIsCloseParenthesis()` determines if the next token is a close parenthesis