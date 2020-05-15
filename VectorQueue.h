//
// Created by trykr on 01.05.2020.
//

#ifndef DATASTRUCTURES_VECTORQUEUE_H
#define DATASTRUCTURES_VECTORQUEUE_H
#pragma once
#include "MyVector.h"
#include "QueueImplementation.h"

template<class ValueType>
class VectorQueue: public QueueImplementation<ValueType>, public MyVector<ValueType>
{
public:
    VectorQueue(const ValueType* valueArray, size_t arraySize)
    {
        this->_data = new ValueType [arraySize];
        for (int i = 0; i < arraySize; i++)
        {
            this->_data[i] = valueArray[i];
        }
        this->_capacity = arraySize;
        this->_size = 0;
    }
    VectorQueue()
    {
        this->_data = new ValueType[0];
        this->_capacity = 0;
        this->_size = 0;
    }
    ~VectorQueue() override
    {
        delete [] this->_data;
    }
    void push(const ValueType &value) override
    {
        this->pushBack(value);
    }
    void pop() override
    {
        this->popFront();
    }
    ValueType& back() const override
    {
        return this->_data[0];
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


#endif //DATASTRUCTURES_VECTORQUEUE_H
