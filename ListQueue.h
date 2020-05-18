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
    ListQueue(const ValueType* valueArray, size_t arraySize);
    ListQueue();
    ~ListQueue() override;
    void push(const ValueType &value) override;
    void pop() override;
    ValueType& back() const override;
    size_t size() const override;
    bool isEmpty() const override;
};

template<class ValueType>
ListQueue<ValueType>::ListQueue(const ValueType* valueArray, size_t arraySize)
{
    for (int i = 0; i < arraySize; i++)
        push(valueArray[i]);
}
template<class ValueType>
ListQueue<ValueType>::ListQueue()
{
    this->_size = 0;
}
template<class ValueType>
ListQueue<ValueType>::~ListQueue()
{

}
template<class ValueType>
void ListQueue<ValueType>::push(const ValueType &value)
{
    this->pushBack(value);
}

template<class ValueType>
void ListQueue<ValueType>::pop()
{
    this->removeFront();
}

template<class ValueType>
ValueType& ListQueue<ValueType>::back() const
{
    return this->_firstNode->value;
}
template<class ValueType>
size_t ListQueue<ValueType>::size() const
{
    return this->_size;
}
template<class ValueType>
bool ListQueue<ValueType>::isEmpty() const
{
    return this->_size == 0;
}