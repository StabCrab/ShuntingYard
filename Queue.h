//
// Created by trykr on 01.05.2020.
//

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
    Queue(QueueContainer container = QueueContainer::Vector);
    // элементы массива последовательно подкладываются в стек
    Queue(const ValueType* valueArray, const size_t arraySize, QueueContainer container = QueueContainer::Vector);
    explicit Queue(const Queue& copyQueue);
    Queue& operator = (const Queue& copyQueue);
    // Здесь как обычно
    Queue& operator=(Queue&& moveQueue) noexcept;
    explicit Queue(const Queue&& moveQueue);
    ~Queue();

    // добавление в хвост
    void push(const ValueType& value);
    // удаление с головы
    void pop();
    // посмотреть элемент в голове
    const ValueType& back() const;
    // проверка на пустоту
    bool isEmpty() const;
    // размер
    size_t size() const;
private:
    // указатель на имплементацию (уровень реализации)
    QueueImplementation<ValueType>* _pimpl = nullptr;
    // тип контейнера, наверняка понадобится
    QueueContainer _containerType;
};

template<class ValueType>
Queue<ValueType>::Queue(QueueContainer container)
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
template<class ValueType>
Queue<ValueType>::Queue(const ValueType* valueArray, const size_t arraySize, QueueContainer container)
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
template<class ValueType>
 Queue<ValueType>::Queue(const Queue& copyQueue)
{
    *this->_pimpl = *(copyQueue._pimpl);
}

template<class ValueType>
class Queue<ValueType>& Queue<ValueType>:: operator = (const Queue& copyQueue){
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
template<class ValueType>
class Queue<ValueType>& Queue<ValueType>:: operator=(Queue&& moveQueue) noexcept
{
    if (this == &moveQueue)
        return *this;
    this->_containerType = moveQueue._containerType;
    delete this->_pimpl;
    this->_pimpl = moveQueue._pimpl;
    return *this;
}
template<class ValueType>
Queue<ValueType>::Queue(const Queue&& moveQueue)
{
    _pimpl = moveQueue._pimpl;
}
template<class ValueType>
Queue<ValueType>::~Queue()
{
    delete _pimpl;
}
template<class ValueType>
void Queue<ValueType>::push(const ValueType& value)
{
    _pimpl->push(value);
}
template<class ValueType>
void Queue<ValueType>::pop()
{
    _pimpl->pop();
}
template<class ValueType>
const ValueType& Queue<ValueType>:: back() const
{
    return _pimpl->back();
}

template<class ValueType>
bool Queue<ValueType>::isEmpty() const
{
    return _pimpl->isEmpty();
}
template<class ValueType>
size_t Queue<ValueType>::size() const
{
    return _pimpl->size();
}