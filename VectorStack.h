//
// Created by trykr on 25.04.2020.
//

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
    VectorStack(const ValueType* valueArray, size_t arraySize);
    VectorStack();
    ~VectorStack() override;
    void push(const ValueType &value) override;
    void pop() override;
    ValueType& top() const override;
    size_t size() const override;
    bool isEmpty() const override;
};

template<class ValueType>
VectorStack<ValueType>::VectorStack(const ValueType* valueArray, size_t arraySize)
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
VectorStack<ValueType>::VectorStack()
{
    this->_data = new ValueType[0];
    this->_capacity = 0;
    this->_size = 0;
}
template<class ValueType>
VectorStack<ValueType>::~VectorStack()
{
    delete [] this->_data;
}
template<class ValueType>
void VectorStack<ValueType>::push(const ValueType &value)
{
    this->pushBack(value);
}
template<class ValueType>
void VectorStack<ValueType>:: pop()
{
    this->popBack();
}

template<class ValueType>
ValueType& VectorStack<ValueType>::top() const
{
    return this->_data[this->_size - 1];
}
template<class ValueType>
size_t VectorStack<ValueType>::size() const
{
    return this->_size;
}
template<class ValueType>
bool VectorStack<ValueType>::isEmpty() const
{
    return this->_size == 0;
}