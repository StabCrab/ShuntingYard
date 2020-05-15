//
// Created by trykr on 02.05.2020.
//

#ifndef DATASTRUCTURES_TOKENIZATION_H
#define DATASTRUCTURES_TOKENIZATION_H
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
    Token()
    {
        this->token ="ERROR";
        this->tokenType = TokenType::Number;
        this->value = 0;
    }
    Token(std::string token, TokenType tokenType) // конструктор для операторов
    {
        this->token = std::move(token);
        this->tokenType = tokenType;
        this->value = 0; //чисто по преколу
    }
    Token(std::string token, double value, TokenType tokenType) // конструктор для чисел
    {
        this->token = std::move(token);
        this->tokenType = tokenType;
        this->value = value;
    }
    ~Token()
    {

    }
    bool operator ==(Token token)
    {
        return this->tokenType == token.tokenType && this->token == token.token && this->value == token.value;
    }
    std::string getToken() const
    {
        return this->token;
    }
    double getValue() const
    {
        return this->value;
    }
    TokenType getTokenType() const
    {
        return this->tokenType;

    }
    void setValue(double val)
    {
        this->value = val;
    }
};


#endif //DATA_TOKENIZATION_H
