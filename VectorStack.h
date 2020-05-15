//
// Created by trykr on 25.04.2020.
//

#ifndef DATASTRUCTURES_VECTORSTACK_H
#define DATASTRUCTURES_VECTORSTACK_H
// меняете на include вашего вектора
#pragma once

#include "StackImplementation.h"
#include "MyVector.h"

// вариант с использованием ранее написанного вектора и множественного наследования
// если бы вектор не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
template<class ValueType>
class VectorStack: public StackImplementation<ValueType>, public MyVector<ValueType>
{
public:
    VectorStack(const ValueType* valueArray, size_t arraySize)
    {
        this->_data = new ValueType [arraySize];
        for (int i = 0; i < arraySize; i++)
        {
            this->_data[i] = valueArray[i];
        }
        this->_capacity = arraySize;
        this->_size = 0;
    }
    VectorStack()
    {
        this->_data = new ValueType[0];
        this->_capacity = 0;
        this->_size = 0;
    }
    ~VectorStack() override
    {
        delete [] this->_data;
    }
    void push(const ValueType &value) override
    {
        this->pushBack(value);
    }
    void pop() override
    {
        this->popBack();
    }
    ValueType& top() const override
    {
        return this->_data[this->_size - 1];
    }
    size_t size() const override
    {
        return this->_size;
    }
    bool isEmpty() const override
    {
        return this->_size == 0;
    }
};
#endif //DATASTRUCTURES_VECTORSTACK_H
