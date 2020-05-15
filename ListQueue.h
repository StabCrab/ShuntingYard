//
// Created by trykr on 01.05.2020.
//

#ifndef DATASTRUCTURES_LISTQUEUE_H
#define DATASTRUCTURES_LISTQUEUE_H
#pragma once

#include "QueueImplementation.h"
#include "LinkedList.h" // меняете на include вашего листа

// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
template<class ValueType>
class ListQueue : public QueueImplementation<ValueType>, public LinkedList<ValueType>
{
public:
    ListQueue(const ValueType* valueArray, size_t arraySize)
    {
        for (int i = 0; i < arraySize; i++)
        push(valueArray[i]);
    }
    ListQueue()
    {
        this->_size = 0;
    }
    ~ListQueue() override
    {

    }
    void push(const ValueType &value) override
    {
        this->pushBack(value);
    }
    void pop() override
    {
        this->removeFront();
    }
    ValueType& back() const override
    {
        return this->_firstNode->value;
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

#endif //DATASTRUCTURES_LISTQUEUE_H
