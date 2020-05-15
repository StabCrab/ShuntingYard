//
// Created by trykr on 25.04.2020.
//

#ifndef DATASTRUCTURES_LISTSTACK_H
#define DATASTRUCTURES_LISTSTACK_H
#pragma once

#include "StackImplementation.h"
#include "LinkedList.h"// меняете на include вашего листа



// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
template<class ValueType>
class ListStack :  LinkedList<ValueType>, public StackImplementation<ValueType>
{
public:
    ListStack(const ValueType* valueArray, size_t arraySize)
    {
        for (int i = 0; i < arraySize; i++)
            push(valueArray[i]);
    }
    ListStack()
    {
        this->_size = 0;
    }
    ~ListStack() override
    {

    }
    void push(const ValueType &value) override
    {
        this->push(value);
    }
    void pop() override
    {
        this->removeBack();
    }
    ValueType& top() const override
    {
        return this->_lastNode->value;
    }
    size_t size() const
    {
        return this->_size;
    }
    bool isEmpty() const override
    {
        return this->size()== 0;
    }
};

#endif //DATASTRUCTURES_LISTSTACK_H
