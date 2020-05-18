//
// Created by trykr on 01.05.2020.
//

#pragma once
#include "MyVector.h"
#include "QueueImplementation.h"

template<class ValueType>
class VectorQueue: public QueueImplementation<ValueType>, public MyVector<ValueType>
{
public:
    VectorQueue(const ValueType* valueArray, size_t arraySize);
    VectorQueue();
    ~VectorQueue() override;
    void push(const ValueType &value) override;
    void pop() override;
    ValueType& back() const override;
    size_t size() const override;
    bool isEmpty() const override;
};

template<class ValueType>
VectorQueue<ValueType>::VectorQueue(const ValueType* valueArray, size_t arraySize)
{
    this->_data = new ValueType [arraySize];
    for (int i = 0; i < arraySize; i++)
    {
        this->_data[i] = valueArray[i];
    }
    this->_capacity = arraySize;
    this->_size = 0;
}
template<class ValueType>
VectorQueue<ValueType>::VectorQueue()
{
    this->_data = new ValueType[0];
    this->_capacity = 0;
    this->_size = 0;
}
template<class ValueType>
VectorQueue<ValueType>::~VectorQueue()
{
    delete [] this->_data;
}
template<class ValueType>
void VectorQueue<ValueType>::push(const ValueType &value)
{
    this->pushBack(value);
}
template<class ValueType>
void VectorQueue<ValueType>:: pop()
{
    this->popFront();
}
template<class ValueType>
ValueType& VectorQueue<ValueType>::back() const
{
    return this->_data[0];
}
template<class ValueType>
size_t VectorQueue<ValueType>::size() const
{
    return this->_size;
}
template<class ValueType>
bool VectorQueue<ValueType>::isEmpty() const
{
    return this->_size == 0;
}
