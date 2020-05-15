//
// Created by trykr on 25.04.2020.
//

#ifndef DATASTRUCTURES_STACK_H
#define DATASTRUCTURES_STACK_H
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
    Stack(StackContainer container = StackContainer::Vector)
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
    // элементы массива последовательно подкладываются в стек
    Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container = StackContainer::Vector)
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

    explicit Stack(const Stack& copyStack)
    {
        *_pimpl = *(copyStack._pimpl);
    }
    Stack& operator=(const Stack& copyStack)
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
    // Здесь как обычно
     Stack(Stack&& moveStack) noexcept
    {
        _pimpl = moveStack._pimpl;
    }
     Stack& operator=(Stack&& moveStack) noexcept
     {
         if (this == &moveStack)
             return *this;
         this->_containerType = moveStack._containerType;
         delete this->_pimpl;
         this->_pimpl = moveStack._pimpl;
         return *this;
     }

    ~Stack()
    {
        delete _pimpl;
    }

    // добавление в хвост
    virtual void push(const ValueType& value)
    {
        _pimpl->push(value);
    }
    // удаление с хвоста
    void pop()
    {
        _pimpl->pop();
    }
    // посмотреть элемент в хвосте
    ValueType& top()
    {
        return this->_pimpl->top();
    }
    // проверка на пустоту
    bool isEmpty() const
    {
        return _pimpl->isEmpty();
    }
    // размер
    size_t size() const
    {
        return _pimpl->size();
    }
private:
    // указатель на имплементацию (уровень реализации)
    StackImplementation<ValueType>* _pimpl = nullptr;
    // тип контейнера, наверняка понадобится
    StackContainer _containerType;
};
#endif //DATASTRUCTURES_STACK_H
