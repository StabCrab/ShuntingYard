//
// Created by trykr on 25.04.2020.
//

#ifndef DATASTRUCTURES_LINKEDLIST_H
#define DATASTRUCTURES_LINKEDLIST_H
#pragma once
#include <cstdlib>
#include <iostream>
#include <cassert>
template <class ValueType>
class LinkedList
{
public:
    struct Node{
    public:
        Node()
        {
            this->next = nullptr;
            this->value = 0;
        }
        Node(const ValueType& value, Node* next = nullptr)
        {
            this->value = value;
            this->next = next;
        }
        ~Node()
        {

        }

        void insertNext(const ValueType& value)
        {
            Node* newNode = new Node(value, this->next);
            this->next = newNode;
        }
        void removeNext()
        {
            Node* removeNode = this->next;
            Node* newNext = removeNode->next;
            delete removeNode;
            this->next = newNext;
        }
        ValueType value;
        Node* next;
    };
    Node* _firstNode;
    size_t	_size;
    Node* _lastNode;

// класс узла списка
// по своей сути, может содержать любые данные,
// можно реализовать и ассоциативный массив, просто добавив
// поле с ключем в узел и, с учетом этого, поменять методы DoublyLinkedList
// (доступ по ключу, поиск по ключу и т.д.)
    ////
    LinkedList()
    {
        _firstNode = nullptr;
        this->_size = 0;
    }
    LinkedList(const LinkedList& copyList)
    {
        this->_size = copyList._size;
        if (this->_size == 0) {
            this->_firstNode = nullptr;
            return;
        }
        this->_firstNode = new Node(copyList._firstNode->value);

        Node* currentNode = this->_firstNode;
        Node* currentCopyNode = copyList._firstNode;

        while (currentCopyNode->next) {
            currentNode->next = new Node(currentCopyNode->value);
            currentCopyNode = currentCopyNode->next;
            currentNode = currentNode->next;
        }
    }
    LinkedList& operator=(const LinkedList& copyList)
    {
        if (this == &copyList) {
            return *this;
        }
        LinkedList bufList(copyList);
        this->_size = bufList._size;
        this->_firstNode = bufList._firstNode;

        return *this;
    }

    LinkedList(LinkedList&& moveList) noexcept
    {
        this->_size = moveList._size;
        this->_firstNode = moveList._firstNode;

        moveList._size = 0;
        moveList._firstNode = nullptr;
    }
    LinkedList& operator=(LinkedList&& moveList) noexcept
    {
        if (this == &moveList) {
            return *this;
        }
        forceNodeDelete(_firstNode);
        this->_size = moveList._size;
        this->_firstNode = moveList._firstNode;

        moveList._size = 0;
        moveList._firstNode = nullptr;

        return *this;
    }

    virtual ~LinkedList()
    {
        forceNodeDelete(_firstNode);
    }
    ////
    // доступ к значению элемента по индексу
    ValueType& operator[](const size_t pos) const
    {
        return getNode(pos)->value;
    }
    // доступ к узлу по индексу

    Node* getNode(const size_t pos) const
    {
        if (pos < 0) {
            assert(pos < 0);
        }
        else if (pos >= this->_size) {
            assert(pos >= this->_size);
        }

        Node* bufNode = this->_firstNode;
        for (int i = 0; i < pos; ++i) {
            bufNode = bufNode->next;
        }

        return bufNode;
    }
    // вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
    virtual void insert(const size_t pos, const ValueType& value)
    {
        if (pos < 0) {
            assert(pos < 0);
        }
        else if (pos > this->_size) {
            assert(pos > this->_size);
        }

        if (pos == 0) {
            pushFront(value);
        }
        else{
            Node* bufNode = this->_firstNode;
            for (size_t i = 0; i < pos-1; ++i) {
                bufNode = bufNode->next;
            }
            bufNode->insertNext(value);
            ++_size;
        }
    }
    // вставка элемента после узла, (O(1))
    virtual void insertAfterNode(Node* node, const ValueType& value)
    {
        node->insertNext(value);
    }
    // вставка в конец (О(n))
    virtual void pushBack(const ValueType& value)
    {
        if (_size == 0) {
            pushFront(value);
            return;
        }
        insert(_size, value);
    }
    // вставка в начало (О(1))
    virtual void pushFront(const ValueType& value)
    {
        _firstNode = new Node(value, _firstNode);
        ++_size;
    }

    // удаление
    virtual void remove(const size_t pos)
    {
        if (pos < 0)
            assert(pos< 0);

        if (pos > this->_size)
            assert(pos > this->_size);
        if (pos == 0) {
            removeFront();
        }
        else {
            Node* node = this->_firstNode;
            for (size_t i = 0; i < pos - 1; ++i) {
                node = node->next;
            }
            node->removeNext();
            this->_size--;
        }
    }
    virtual void removeNextNode(Node* node)
    {
        Node *deletedNode = node->next;
        node->next = node->next->next;
        delete deletedNode;
    }
    virtual void removeFront()
    {
        Node *node = _firstNode;
        this->_firstNode = this->_firstNode->next;
        delete node;
        this->_size--;
    }
    virtual void removeBack()
    {
        Node* node = _firstNode;
        for (int i = 0; i < this->_size - 2; i++)
        {
            node = node->next;
        }
        delete this->_lastNode;
        this->_lastNode = node;
        this->_lastNode->next = nullptr;
        this->_size--;
    }

    // поиск, О(n)
    virtual long long int findIndex(ValueType& value) const
    {
        long long int i = 0;
        Node *currentNode = _firstNode;
        while (i < _size)
        {
            if (currentNode->value == value)
                return i;
        }
        std:: cout << "No Node" << std :: endl;
        return -1;
    }
    virtual Node* findNode(ValueType& value) const
    {
        long long int i = 0;
        Node *currentNode = _firstNode;
        while (i < _size)
        {
            if (currentNode->value == value)
                return currentNode;
        }
        std:: cout << "No Node" << std :: endl;
        return nullptr;
    }

    // разворот списка
    virtual void reverse()
    {
        Node *previousNode= _firstNode;
        Node *currentNode = _firstNode->next;
        Node *nextNode = currentNode->next;
        _firstNode->next = nullptr;
        currentNode->next = previousNode;
        _lastNode = _firstNode;
        while (nextNode->next != nullptr)
        {
            previousNode = currentNode;
            currentNode = nextNode;
            nextNode = nextNode->next;
            currentNode->next = previousNode;
        }
        previousNode = currentNode;
        currentNode = nextNode;
        currentNode->next = previousNode;
        _firstNode = currentNode;
    }
    virtual LinkedList reverse() const
    {
        LinkedList reversedList = *this;
        reversedList.reverse();
        return reversedList;
    }// полчение нового списка (для константных объектов)
    virtual LinkedList getReverseList() const
    {
        LinkedList reversedList = *this;
        reversedList.reverse();
        return reversedList;
    }// чтобы неконстантный объект тоже мог возвращать новый развернутый список

    virtual size_t size() const
    {
        return _size;
    }
private:

    void forceNodeDelete(Node* node)
    {
        if (node == nullptr) {
            return;
        }

        Node* nextDeleteNode = node->next;
        delete node;
        forceNodeDelete(nextDeleteNode);
    }
};
#endif //DATASTRUCTURES_LINKEDLIST_H
