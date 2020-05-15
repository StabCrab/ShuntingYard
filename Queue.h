//
// Created by trykr on 01.05.2020.
//

#ifndef DATASTRUCTURES_QUEUE_H
#define DATASTRUCTURES_QUEUE_H
#pragma once
#include <cstdio>
#include "QueueImplementation.h"
#include "ListQueue.h"
#include "VectorQueue.h"
#include <stdexcept>
// Уровень абстракции
// клиентский код подключает именно этот хедер
enum class QueueContainer {
    Vector = 0,
    List,
    // можно дополнять другими контейнерами
};
// тип значений в стеке


// на основе какого контейнера работает стек

// декларация класса с реализацией
template<typename ValueType>
class QueueImplementation;

template<class ValueType>
class Queue
{
public:
    // Большая пятерка
    Queue(QueueContainer container = QueueContainer::Vector)
    {
        switch (container)
        {
            case QueueContainer::List: {
                this->_pimpl = new ListQueue<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
                break;
            }
            case QueueContainer::Vector: {
                this->_pimpl = new VectorQueue<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
                break;
            }
            default:
                throw std::runtime_error("Неизвестный тип контейнера");
        }
    }
    // элементы массива последовательно подкладываются в стек
    Queue(const ValueType* valueArray, const size_t arraySize, QueueContainer container = QueueContainer::Vector)
    {
        switch (container)
        {
            case QueueContainer::List: {
                this->_pimpl = new ListQueue<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
                break;
            }
            case QueueContainer::Vector: {
                this->_pimpl = new VectorQueue<ValueType>(valueArray, arraySize);	// конкретизируйте под ваши конструкторы, если надо
                break;
            }
            default:
                throw std::runtime_error("Неизвестный тип контейнера");
        }// принцип тот же, что и в прошлом конструкторе
    }

    explicit Queue(const Queue& copyQueue)
    {
        *this->_pimpl = *(copyQueue._pimpl);
    }
    Queue& operator = (const Queue& copyQueue){
        if (this == &copyQueue)
            return *this;
        this->_containerType = copyQueue._containerType;
        delete this->_pimpl;
        switch (this->_containerType) {
            case QueueContainer::List: {
                this->_pimpl = new ListQueue<ValueType>(
                        *(dynamic_cast<ListQueue<ValueType> *>(copyQueue._pimpl)));    // конкретизируйте под ваши конструкторы, если надо
                break;
            }
            case QueueContainer::Vector: {
                this->_pimpl = new VectorQueue<ValueType>(
                        *(dynamic_cast<VectorQueue<ValueType> *>(copyQueue._pimpl)));    // конкретизируйте под ваши конструкторы, если надо
                break;
            }
            default:
                throw std::runtime_error("Неизвестный тип контейнера");
        }
    }
    // Здесь как обычно
    Queue& operator=(Queue&& moveQueue) noexcept
    {
        if (this == &moveQueue)
            return *this;
        this->_containerType = moveQueue._containerType;
        delete this->_pimpl;
        this->_pimpl = moveQueue._pimpl;
        return *this;
    }
    explicit Queue(const Queue&& moveQueue)
    {
        _pimpl = moveQueue._pimpl;
    }
    ~Queue()
    {
        delete _pimpl;
    }

    // добавление в хвост
    void push(const ValueType& value)
    {
        _pimpl->push(value);
    }
    // удаление с головы
    void pop()
    {
        _pimpl->pop();
    }
    // посмотреть элемент в голове
    const ValueType& back() const
    {
        return _pimpl->back();
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
    QueueImplementation<ValueType>* _pimpl = nullptr;
    // тип контейнера, наверняка понадобится
    QueueContainer _containerType;
};
#endif //DATASTRUCTURES_QUEUE_H
