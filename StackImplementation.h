//
// Created by trykr on 25.04.2020.
//

#pragma once
#include <cstdio>
// приходится тянуть ValueType во все места,
// наглядная демонстрация того, почему с шаблонами было бы легче.
// Ждем, когда дойдете до этого на МиСП.
// интерфейс для конкретных реализаций контейнера для стека
template <class ValueType>
class StackImplementation {
public:
    // добавление в хвост
    virtual void push(const ValueType& value) = 0;
    // удаление с хвоста
    virtual void pop() = 0;
    // посмотреть элемент в хвосте
    virtual ValueType& top() const = 0;
    // проверка на пустоту
    virtual bool isEmpty() const = 0;
    // размер
    virtual size_t size() const = 0;
    // виртуальный деструктор
    virtual ~StackImplementation() {};
};

