//
// Created by trykr on 18.05.2020.
//

#include "Token.h"

Token::Token()
{
    this->token ="ERROR";
    this->tokenType = TokenType::Number;
    this->value = 0;
}

Token::Token(std::string token, TokenType tokenType)
{
    this->token = std::move(token);
    this->tokenType = tokenType;
    this->value = 0; //чисто по преколу
}

Token::Token(std::string token, double value, TokenType tokenType)
{
    this->token = std::move(token);
    this->tokenType = tokenType;
    this->value = value;
}

Token::~Token()
{

}

bool Token::operator==(Token token)
{
    return this->tokenType == token.tokenType && this->token == token.token && this->value == token.value;
}

std::string Token::getToken() const
{
    return this->token;
}

double Token::getValue() const {
    return this->value;
}

TokenType Token::getTokenType() const {
    return this->tokenType;
}

void Token::setValue(double val)
{
    this->value = val;
}
