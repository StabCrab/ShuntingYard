//
// Created by trykr on 02.05.2020.
//

#include <string>
#include <iostream>
#include <utility>
enum class TokenType
{
    Number = 0,
    OperatorLeftParen,
    OperatorRightParen,
    OperatorLowPrecedence,
    OperatorMiddlePrecedence,
    OperatorHighPrecedence,
};
class Token{
private:
    std::string token;
    double value;
    TokenType tokenType;
public:
    Token();
    Token(std::string token, TokenType tokenType); // конструктор для операторов
    Token(std::string token, double value, TokenType tokenType); // конструктор для чисел
    ~Token();
    bool operator ==(Token token);
    std::string getToken() const;
    double getValue() const;
    TokenType getTokenType() const;
    void setValue(double val);
};
