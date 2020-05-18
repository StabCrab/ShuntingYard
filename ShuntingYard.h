//
// Created by trykr on 29.04.2020.
//

#pragma once
#include <string>
#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include "Token.h"
#include "MyVector.h"
class ShuntingYard
{
private:
    std::string expression;
    Queue<Token> *resultQueue = new Queue<Token>;
    Stack<Token> *operatorStack = new Stack<Token>;
    Queue<Token> *tokenQueue = new Queue<Token>;
    Stack<Token> *helpStack = new Stack <Token>;
public:
    ShuntingYard(std::string expression);
    ~ShuntingYard();
    void tokenization();
    void printTokens();
    void parse();
    double calculate();
    Queue<Token>& getQueue();

};

