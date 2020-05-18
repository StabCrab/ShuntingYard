//
// Created by trykr on 25.04.2020.
//

#pragma once
#include <cstdio>
#include "StackImplementation.h"
#include "ListStack.h"
#include "VectorStack.h"
#include <stdexcept>
// Уровень абстракции
// клиентский код подключает именно этот хедер

// тип значений в стеке

// на основе какого контейнера работает стек
enum class StackContainer {
    Vector = 0,
    List,
    // можно дополнять другими контейнерами
};

// декларация класса с реализацией
template<class ValueType>
class StackImplementation;

template<class ValueType>
class Stack
{
public:
    // Большая пятерка
    Stack(StackContainer container = StackContainer::Vector);
    // элементы массива последовательно подкладываются в стек
    Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container = StackContainer::Vector);

    explicit Stack(const Stack& copyStack);
    Stack& operator=(const Stack& copyStack);
    // Здесь как обычно
    Stack(Stack&& moveStack) noexcept;
     Stack& operator=(Stack&& moveStack) noexcept;

    ~Stack();

    // добавление в хвост
    virtual void push(const ValueType& value);
    // удаление с хвоста
    void pop();
    // посмотреть элемент в хвосте
    ValueType& top();
    // проверка на пустоту
    bool isEmpty() const;
    // размер
    size_t size() const;
private:
    // указатель на имплементацию (уровень реализации)
    StackImplementation<ValueType>* _pimpl = nullptr;
    // тип контейнера, наверняка понадобится
    StackContainer _containerType;
};

template<class ValueType>
Stack<ValueType>::Stack(StackContainer container)
{
    switch (container)
    {
        case StackContainer::List:{
            _pimpl = new ListStack<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::Vector:
        {
            _pimpl = new VectorStack<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
}
template<class ValueType>
Stack<ValueType>::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container)
{
    switch (container)
    {
        case StackContainer::List: {
            _pimpl = new ListStack<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::Vector: {
            _pimpl = new VectorStack<ValueType>(valueArray, arraySize);	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }// принцип тот же, что и в прошлом конструкторе
}
template<class ValueType>
Stack<ValueType>::Stack(const Stack& copyStack)
{
    *_pimpl = *(copyStack._pimpl);
}
template<class ValueType>
class Stack<ValueType>& Stack<ValueType>:: operator=(const Stack& copyStack)
{
    if (this == &copyStack)
        return *this;
    this->_containerType = copyStack._containerType;
    delete this->_pimpl;
    switch (this->_containerType)
    {
        case StackContainer::List: {
            _pimpl = new ListStack<ValueType>(
                    *(dynamic_cast<ListStack<ValueType> *>(copyStack._pimpl)));    // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::Vector: {
            _pimpl = new VectorStack<ValueType>(
                    *(dynamic_cast<VectorStack<ValueType> *>(copyStack._pimpl)));    // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
    return *this;
}
template<class ValueType>
Stack<ValueType>::Stack(Stack&& moveStack) noexcept
{
    _pimpl = moveStack._pimpl;
}
template<class ValueType>
class Stack<ValueType>& Stack<ValueType>::operator=(Stack&& moveStack) noexcept
{
    if (this == &moveStack)
        return *this;
    this->_containerType = moveStack._containerType;
    delete this->_pimpl;
    this->_pimpl = moveStack._pimpl;
    return *this;
}
template<class ValueType>
Stack<ValueType>::~Stack()
{
    delete _pimpl;
}
template<class ValueType>
void Stack<ValueType>:: push(const ValueType& value)
{
    _pimpl->push(value);
}
template<class ValueType>
void Stack<ValueType>:: pop()
{
    _pimpl->pop();
}
template<class ValueType>
ValueType& Stack<ValueType> :: top()
{
    return this->_pimpl->top();
}

template<class ValueType>
bool Stack<ValueType>::isEmpty() const
{
    return _pimpl->isEmpty();
}

template<class ValueType>
size_t Stack<ValueType>:: size() const
{
    return _pimpl->size();
}