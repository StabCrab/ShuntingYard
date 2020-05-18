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
    ListStack(const ValueType* valueArray, size_t arraySize);
    ListStack();
    ~ListStack() override
    {

    }
    void push(const ValueType &value) override;
    void pop() override;
    ValueType& top() const override;
    size_t size() const;
    bool isEmpty() const override;
};
template<class ValueType>
ListStack<ValueType>::ListStack(const ValueType* valueArray, size_t arraySize)
{
    for (int i = 0; i < arraySize; i++)
        push(valueArray[i]);
}
template<class ValueType>
ListStack<ValueType>::ListStack()
{
    this->_size = 0;
}
template<class ValueType>
void ListStack<ValueType>::push(const ValueType &value)
{
    this->push(value);
}
template<class ValueType>
void ListStack<ValueType>::pop()
{
    this->removeBack();
}
template<class ValueType>
ValueType& ListStack<ValueType>::top() const
{
    return this->_lastNode->value;
}
template<class ValueType>
size_t ListStack<ValueType>::size() const
{
    return this->_size;
}
template<class ValueType>
bool ListStack<ValueType>::isEmpty() const
{
    return this->size()== 0;
}