//
// Created by trykr on 29.04.2020.
//
#include "ShuntingYard.h"
#include <utility>

ShuntingYard::ShuntingYard(std::string expression)
{
    this->expression = std::move(expression);
}
ShuntingYard::~ShuntingYard()
{
    delete this->operatorStack;
    delete this->helpStack;
    delete this->tokenQueue;
    delete this->resultQueue;
}

void ShuntingYard::tokenization()
{
    double delta;
    double value;
    bool ifPlus;
    std::string token;
    MyVector<Token> tokenArray;
    TokenType tokenType;
    for (int i = 0; i < expression.size(); i++)
    {
        if (expression[i] == ' ')
            i++;
        if ((expression[i] >= '0' && expression[i] <= '9') || ((expression[i] == '-' || expression[i] =='+')&&(expression[i + 1] >= '0' && expression[i + 1] <= '9')))
        {
            if (expression[i] == '-')
            {
                token += '-';
                ifPlus = false;
                i++;
            }
            else if (expression[i] == '+')
            {
                ifPlus = true;
                i++;
            }
            else
                ifPlus = true;
            tokenType = TokenType::Number;
            delta = 1;
            value = 0;
            while(expression[i] >= '0' && expression[i] <= '9')
            {
                if(ifPlus)
                    value = value * delta + (expression[i] - '0');
                else
                    value = value * delta - (expression[i] - '0');
                token += expression[i];
                delta *= 10;
                i++;
            }
            if (expression[i] =='.')
            {
                token+='.';
                delta = 0.1;
            }
            while(expression[i] >= '0' && expression[i] <= '9')
            {
                if (ifPlus)
                    value = value * delta + (expression[i] - '0');
                else
                    value = value * delta - (expression[i] - '0');
                token += expression[i];
                delta /= 10;
                i++;
            }
        }
        else
        {
            switch (expression[i])
            {
                case'-':
                {
                    token += '-';
                    tokenType = TokenType::OperatorLowPrecedence;
                    break;
                }
                case '+':
                {
                    token += '+';
                    tokenType = TokenType::OperatorLowPrecedence;
                    break;
                }
                case '*':
                {
                    token += '*';
                    tokenType = TokenType::OperatorMiddlePrecedence;
                    break;
                }
                case '/':
                {
                    token += '/';
                    tokenType = TokenType::OperatorMiddlePrecedence;
                    break;
                }
                case'^':
                {
                    token += '^';
                    tokenType = TokenType::OperatorHighPrecedence;
                    break;
                }
                case '(':
                {
                    token += '(';
                    tokenType = TokenType::OperatorLeftParen;
                    break;
                }
                case ')':
                {
                    token += ')';
                    tokenType = TokenType::OperatorRightParen;
                    break;
                }
                default:
                {
                    std::cout <<"Error";
                    assert("Error");
                }
            }
        }
        if (tokenType == TokenType::Number)
        {
            tokenQueue->push(Token(token, value, tokenType));
        }
        else
        {
            tokenQueue->push(Token(token, tokenType));
        }
        token.clear();
    }
}

void ShuntingYard::printTokens()
{
    while (!tokenQueue->isEmpty())
    {
        std::cout << tokenQueue->back().getToken() << ' ';
        tokenQueue->pop();
    }
}

void ShuntingYard::parse()
{
    int countLeftParen = 0;
    int countRightParen = 0;
    std::string resultString;
    while (!tokenQueue->isEmpty()) //while there are tokens to be read do:
    {
        if (tokenQueue->back().getTokenType() == TokenType::Number) //if the token is a number, then:
        {
            resultQueue->push(tokenQueue->back());//push it to the output queue.
            resultString += tokenQueue->back().getToken();
        }
        if(tokenQueue->back().getTokenType() == TokenType::OperatorLowPrecedence ||
                 tokenQueue->back().getTokenType() == TokenType::OperatorMiddlePrecedence ||
                 tokenQueue->back().getTokenType() == TokenType::OperatorHighPrecedence)//if the token is an operator, then:
        {
            while ((!operatorStack->isEmpty())&&(operatorStack->top().getTokenType() > tokenQueue->back().getTokenType())//there is an operator at the top of the operator stack with greater precedence
            ||(operatorStack->top().getTokenType() == tokenQueue->back().getTokenType() && tokenQueue->back().getTokenType() != TokenType::OperatorHighPrecedence) // or the operator at the top of the operator stack has equal precedence and the token is left associative
            &&(operatorStack->top().getTokenType() != TokenType::OperatorLeftParen))// and the operator at the top of the operator stack is not a left parenthesis
            {
                resultQueue->push(operatorStack->top());
                resultString += operatorStack->top().getToken();
                operatorStack->pop();//pop operators from the operator stack onto the output queue.
            }
            operatorStack->push(tokenQueue->back()); //push it onto the operator stack.

        }
        if (tokenQueue->back().getTokenType() == TokenType::OperatorLeftParen) // if the token is a left paren (i.e. "("), then:
        {
            countLeftParen++;
            operatorStack->push(tokenQueue->back()); //push it onto the operator stack.
        }
        if (tokenQueue->back().getTokenType() == TokenType::OperatorRightParen)  // if the token is a right paren (i.e. ")"), then:
        {
            countRightParen++;
            if (operatorStack->isEmpty())
            {
                throw std::logic_error("NOT BALANCED");
            }
            while (operatorStack->top().getTokenType() != TokenType::OperatorLeftParen) //while the operator at the top of the operator stack is not a left paren:
            {
                resultQueue->push(operatorStack->top());
                resultString += operatorStack->top().getToken();//  pop the operator from the operator stack onto the output queue.
                operatorStack->pop();
                if (operatorStack->isEmpty()) // If the stack runs out without finding a left paren, then there are mismatched parentheses. */
                {
                    throw std::logic_error("NOT BALANCED");
                }
            }
            operatorStack->pop();
        }
        tokenQueue->pop();
    }
    while (!operatorStack->isEmpty())
    {
        if (operatorStack->top().getTokenType() == TokenType::OperatorRightParen)
        {
            throw std::logic_error("NOT BALANCED");
            return ;
        }
        if (operatorStack->top().getTokenType() == TokenType::OperatorLeftParen)  // if there is a left paren at the top of the operator stack, then:
        {
            operatorStack->pop(); //pop the operator from the operator stack and discard it
            continue;
        }
        resultQueue->push(operatorStack->top());
        resultString += operatorStack->top().getToken();
        operatorStack->pop();
    }
    if (countLeftParen != countRightParen)
        throw std::logic_error("NOT BALANCED");
    std :: cout << resultString << std::endl;
}

double ShuntingYard::calculate()
{
    double number;
    while(!resultQueue->isEmpty())
    {
        switch (resultQueue->back().getTokenType())
        {
            case (TokenType::Number):
            {
                helpStack->push(resultQueue->back());
                resultQueue->pop();
                break;
            }
            case (TokenType::OperatorLowPrecedence):
            {
                if (resultQueue->back().getToken() == "-")
                {
                    number = helpStack->top().getValue();
                    helpStack->pop();
                    helpStack->top().setValue(helpStack->top().getValue() - number);
                    resultQueue->pop();
                    break;
                }
                if (resultQueue->back().getToken() == "+")
                {
                    number = helpStack->top().getValue();
                    helpStack->pop();
                    helpStack->top().setValue(helpStack->top().getValue() + number);
                    resultQueue->pop();
                    break;
                }
            }
            case (TokenType::OperatorMiddlePrecedence):
            {
                if (resultQueue->back().getToken() == "/")
                {
                    number = helpStack->top().getValue();
                    helpStack->pop();
                    helpStack->top().setValue(helpStack->top().getValue() / number);
                    resultQueue->pop();
                    break;
                }
                if (resultQueue->back().getToken() == "*")
                {
                    number = helpStack->top().getValue();
                    helpStack->pop();
                    helpStack->top().setValue(helpStack->top().getValue() * number);
                    resultQueue->pop();
                    break;
                }
            }
            case (TokenType::OperatorHighPrecedence):
            {
                number = helpStack->top().getValue();
                helpStack->pop();
                helpStack->top().setValue(pow(helpStack->top().getValue(),number ));
                resultQueue->pop();
                break;
            }
        }
    }
    return helpStack->top().getValue();
}

Queue<Token>& ShuntingYard::getQueue()
{
    return *this->resultQueue;
}
